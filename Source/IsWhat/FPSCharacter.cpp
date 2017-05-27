// Fill out your copyright notice in the Description page of Project Settings.

#include "IsWhat.h"
#include "FPSCharacter.h"
#include "FPSProjectile.h"
#include "Animation/AnimInstance.h"
#include "GameFramework/InputSettings.h"
#include "Kismet/HeadMountedDisplayFunctionLibrary.h"



// Sets default values   【这类文件声明在哪呢？？】（声明在.h文件里-，-。。。）√
AFPSCharacter::AFPSCharacter()
{//这个调用类里边的 FPSCharacter.h里边的函数

 



 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//设置这个角色叫 Tick每帧  如果你不需要的话，你可以关闭它来提高性能。 
	PrimaryActorTick.bCanEverTick = true;
	//这个在 FTickFunction类里被调用  初始的样子是这样的 →uint8 bCanEverTick:1;
	//工程师给的说法是→如果FALSE，此函数将永远不会注册，永远不会修正。只有在默认设置。 好像是 不用刷新帧了

	//【他为什么可以连续指向，其中操作变换是怎样的？】 啊。。当然可以啊 只是声明了一个指针指向这些值而已
	
	// 创建一个第一人称摄像机组件。
	FPSCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	//显示指定函数模板实参 【但是不能够理解源码文件】

	// 将摄像机组件附加到胶囊体组件。
	FPSCameraComponent->AttachTo(GetCapsuleComponent());
	//GetCapsuleComponent 返回胶囊组成的子对象
	// 【return CapsuleComponent←里面的返回值是→这是一个碰撞检查指针 什么鬼？class UCapsuleComponent* CapsuleComponent;】
	//大概意思是用指针调用谁了  可以调用了什么鬼啊==???

	// 将摄像机放置在眼睛上方不远处。
	FPSCameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f + BaseEyeHeight));
	//SetRelativeLocation(FVector NewLocation, bool bSweep, FHitResult* OutSweepHitResult, ETeleportType Teleport)
	//FORCEINLINE FVector(float InX, float InY, float InZ);
	//好像调用的上面那个函数↑ 就是给他改改位置的意思  是使用每个组件的初始值 
	//BaseEyeHeight官方翻译是高于碰撞中心基眼高度【怎么理解？】可能是 加上高差了 比如之前在胸腔然后胸腔高度+50

	// 用 pawn 控制摄像机旋转。
	FPSCameraComponent->bUsePawnControlRotation = true;
	//可能性被批准 【uint32 bUseAdditiveOffset : 1; 这则么理解？他不本来就是1 就是 true 吗？】



	// 为拥有玩家创建一个第一人称模型组件。
	FPSMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FirstPersonMesh"));
	//【这是啥。。。。】

	// 该模型仅对拥有玩家可见。
	FPSMesh->SetOnlyOwnerSee(true);


	// 将 FPS 模型添加到 FPS 摄像机。
	FPSMesh->AttachTo(FPSCameraComponent);


	// 禁用部分环境阴影，保留单一模型存在的假象。
	FPSMesh->bCastDynamicShadow = false;
	FPSMesh->CastShadow = false;


	// 拥有玩家无法看到普通（第三人称）身体模型。
	GetMesh()->SetOwnerNoSee(true);


	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
}

// Called when the game starts or when spawned
void AFPSCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (GEngine)
	{
		// 显示调试信息五秒。-1“键”值（首个参数）说明我们无需更新或刷新此消息。
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("We are using FPSCharacter."));
	}
	//FPSMesh->AttachToComponent()
	Mesh1P->AttachToComponent(FPSMesh, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));
	//FP_Gun->AttachTo(FPSMesh);
	//KeepRelativeTransform
}

// Called every frame
void AFPSCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	//【？？？】
}

// Called to bind functionality to input
void AFPSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	//【？？？】
	PlayerInputComponent->BindAxis("MoveForward", this, &AFPSCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AFPSCharacter::MoveRight);


	// 设置“动作”绑定。
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AFPSCharacter::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AFPSCharacter::StopJump);



	PlayerInputComponent->BindAxis("Turn", this, &AFPSCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &AFPSCharacter::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AFPSCharacter::Fire);
}
void AFPSCharacter::MoveForward(float Value)
{
	// 明确哪个方向是“前进”，并记录玩家试图向此方向移动。
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, Value);
}
void AFPSCharacter::MoveRight(float Value)
{
	// 明确哪个方向是“向右”，并记录玩家试图向此方向移动。
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, Value);
}


void AFPSCharacter::StartJump()
{
	bPressedJump = true;
}

void AFPSCharacter::StopJump()
{
	bPressedJump = false;
}

void AFPSCharacter::Fire()
{
	/* 这里主要写，关于 绑定动画 */

	// try and play a firing animation if specified
	if (FireAnimation != NULL)
	{
		// Get the animation object for the arms mesh
		UAnimInstance* AnimInstance = FPSMesh->GetAnimInstance();
		//要特别注意是谁绑定了动画
		if (AnimInstance != NULL)
		{
			AnimInstance->Montage_Play(FireAnimation, 1.f);
		}
	}
	// try and play the sound if specified
	if (FireSound != NULL)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
	}


	// 尝试发射物体。
	if (ProjectileClass)
	{
		// 获取摄像机变换。
		FVector CameraLocation;
		//储存位置

		FRotator CameraRotation;
		//储存旋转
		
		GetActorEyesViewPoint(CameraLocation, CameraRotation);
		/*
		所以第一个值是说了，发射体的位置和摄像机平齐[由BaseEyeHeight决定而来]
		第二个是获取根组件的旋转角度

		位置是 
		void APawn::GetActorEyesViewPoint( FVector& out_Location, FRotator& out_Rotation ) const
			{
				out_Location = GetPawnViewLocation();
				out_Rotation = GetViewRotation();
			}

			FVector APawn::GetPawnViewLocation() const
			{
			return GetActorLocation() + FVector(0.f,0.f,BaseEyeHeight);
			}
		FORCEINLINE FVector GetActorLocation() const
	{
		return GetActorLocation(RootComponent);
	}
	返回此演员的根组件的位置
		======================
		FRotator APawn::GetViewRotation() const
		{
		if (Controller != NULL)
		{
		return Controller->GetControlRotation();
		}
		else if (Role < ROLE_Authority)
		{
		// check if being spectated
		for( FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator )
		{
		APlayerController* PlayerController = *Iterator;
		if(PlayerController && PlayerController->PlayerCameraManager->GetViewTargetPawn() == this)
		{
		return PlayerController->BlendedTargetViewRotation;
		}
		}
		}

		return GetActorRotation();
		}


		FORCEINLINE FRotator GetActorRotation() const
		{
		return GetActorRotation(RootComponent);
		}
		返回根组件的旋转
		
		*/


		// 将 MuzzleOffset 从摄像机空间变换到世界空间。
		FVector MuzzleLocation = CameraLocation + FTransform(CameraRotation).TransformVector(MuzzleOffset);
		// MuzzleLocation新位置(枪口位置) = 获取摄像机变换 +  ？？？
		/*
		具有初始旋转的构造函数
		@旋转使用旋转组件的值参数（转换为一个四元数后） 
		↑↑官爹的解释 == ？？？
		*/

		FRotator MuzzleRotation = CameraRotation;
		//枪口旋转等于 相机旋转 枪口在上面生成了↑

		// 将准星稍微上抬。
		MuzzleRotation.Pitch += 10.0f;
		/*
		在右轴旋转（绕Y轴），向上和向下看（0 =前方，+，-） 
		float Pitch; 
		
		*/



		UWorld* World = GetWorld();
		//？？？
		
		
		if (World)
		{
			FActorSpawnParameters SpawnParams;
			/*
			FActorSpawnParameters::FActorSpawnParameters()
			: Name(NAME_None)
			, Template(NULL)
			, Owner(NULL)
			, Instigator(NULL)
			, OverrideLevel(NULL)
			, SpawnCollisionHandlingOverride(ESpawnActorCollisionHandlingMethod::Undefined)
			, bRemoteOwned(false)
			, bNoFail(false)
			, bDeferConstruction(false)
			, bAllowDuringConstructionScript(false)
			, ObjectFlags(RF_Transactional)
			{
			}
			他调用了这个构造函数，在这一步
			*/

			SpawnParams.Owner = this;
			/*
			这个演员的演员。（可保留为空） 
			AActor* Owner;
			*/

			SpawnParams.Instigator = Instigator;
			/*
			APawn*	Instigator;
			一个由负责的演员造成损害的棋子。（可保留为空） 
			
			UPROPERTY(BlueprintReadWrite, replicatedUsing=OnRep_Instigator, meta=(ExposeOnSpawn=true), Category=Actor)
			class APawn* Instigator;
			负责此演员造成的损坏的棋子。

			【让子弹拥有产生伤害的能力】
			*/

			// 在枪口处生成发射物。
			AFPSProjectile* Projectile = World->SpawnActor<AFPSProjectile>(ProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParams);
			/*
			模板版本的再生的演员，可以另外指定旋转和定位            
			*类通过参数，而返回类型是该类型的父类 
			template< class T >
			T* SpawnActor( UClass* Class, FVector const& Location, FRotator const& Rotation, const FActorSpawnParameters& SpawnParameters = FActorSpawnParameters() )
			{
			return CastChecked<T>(SpawnActor(Class, &Location, &Rotation, SpawnParameters),ECastCheckedType::NullAllowed);
			}
			有四个参数 类/位置/旋转/再生参数
			
			//意思是那个球球，在指定位置重生【生成】
			*/

			if (Projectile)
			{
				// 设置发射物的初始轨道。
				FVector LaunchDirection = MuzzleRotation.Vector();
				/*
				FORCEINLINE FVector FQuat::Vector() const
				{
					return GetAxisX();
				}
				
				FORCEINLINE FVector FQuat::GetAxisX() const
				{
					return RotateVector(FVector(1.f, 0.f, 0.f));
				}
				//然后就是物理的具体的计算公式了....
				因为是从枪口上买发射出去的，所以用的是MuzzleRotation.
				*/

				Projectile->FireInDirection(LaunchDirection);
				//这是一个物理计算....用了之前的那个



			}
		}
	}
}