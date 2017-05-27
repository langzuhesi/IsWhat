// Fill out your copyright notice in the Description page of Project Settings.

#include "IsWhat.h"
#include "FPSCharacter.h"
#include "FPSProjectile.h"
#include "Animation/AnimInstance.h"
#include "GameFramework/InputSettings.h"
#include "Kismet/HeadMountedDisplayFunctionLibrary.h"



// Sets default values   �������ļ����������أ�������������.h�ļ���-��-����������
AFPSCharacter::AFPSCharacter()
{//�����������ߵ� FPSCharacter.h��ߵĺ���

 



 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//���������ɫ�� Tickÿ֡  ����㲻��Ҫ�Ļ�������Թر�����������ܡ� 
	PrimaryActorTick.bCanEverTick = true;
	//����� FTickFunction���ﱻ����  ��ʼ�������������� ��uint8 bCanEverTick:1;
	//����ʦ����˵���ǡ����FALSE���˺�������Զ����ע�ᣬ��Զ����������ֻ����Ĭ�����á� ������ ����ˢ��֡��

	//����Ϊʲô��������ָ�����в����任�������ģ��� ��������Ȼ���԰� ֻ��������һ��ָ��ָ����Щֵ����
	
	// ����һ����һ�˳�����������
	FPSCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	//��ʾָ������ģ��ʵ�� �����ǲ��ܹ����Դ���ļ���

	// �������������ӵ������������
	FPSCameraComponent->AttachTo(GetCapsuleComponent());
	//GetCapsuleComponent ���ؽ�����ɵ��Ӷ���
	// ��return CapsuleComponent������ķ���ֵ�ǡ�����һ����ײ���ָ�� ʲô��class UCapsuleComponent* CapsuleComponent;��
	//�����˼����ָ�����˭��  ���Ե�����ʲô��==???

	// ��������������۾��Ϸ���Զ����
	FPSCameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f + BaseEyeHeight));
	//SetRelativeLocation(FVector NewLocation, bool bSweep, FHitResult* OutSweepHitResult, ETeleportType Teleport)
	//FORCEINLINE FVector(float InX, float InY, float InZ);
	//������õ������Ǹ������� ���Ǹ����ĸ�λ�õ���˼  ��ʹ��ÿ������ĳ�ʼֵ 
	//BaseEyeHeight�ٷ������Ǹ�����ײ���Ļ��۸߶ȡ���ô��⣿�������� ���ϸ߲��� ����֮ǰ����ǻȻ����ǻ�߶�+50

	// �� pawn �����������ת��
	FPSCameraComponent->bUsePawnControlRotation = true;
	//�����Ա���׼ ��uint32 bUseAdditiveOffset : 1; ����ô��⣿������������1 ���� true �𣿡�



	// Ϊӵ����Ҵ���һ����һ�˳�ģ�������
	FPSMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FirstPersonMesh"));
	//������ɶ����������

	// ��ģ�ͽ���ӵ����ҿɼ���
	FPSMesh->SetOnlyOwnerSee(true);


	// �� FPS ģ����ӵ� FPS �������
	FPSMesh->AttachTo(FPSCameraComponent);


	// ���ò��ֻ�����Ӱ��������һģ�ʹ��ڵļ���
	FPSMesh->bCastDynamicShadow = false;
	FPSMesh->CastShadow = false;


	// ӵ������޷�������ͨ�������˳ƣ�����ģ�͡�
	GetMesh()->SetOwnerNoSee(true);


	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
}

// Called when the game starts or when spawned
void AFPSCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (GEngine)
	{
		// ��ʾ������Ϣ���롣-1������ֵ���׸�������˵������������»�ˢ�´���Ϣ��
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
	//����������
}

// Called to bind functionality to input
void AFPSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	//����������
	PlayerInputComponent->BindAxis("MoveForward", this, &AFPSCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AFPSCharacter::MoveRight);


	// ���á��������󶨡�
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AFPSCharacter::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AFPSCharacter::StopJump);



	PlayerInputComponent->BindAxis("Turn", this, &AFPSCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &AFPSCharacter::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AFPSCharacter::Fire);
}
void AFPSCharacter::MoveForward(float Value)
{
	// ��ȷ�ĸ������ǡ�ǰ����������¼�����ͼ��˷����ƶ���
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, Value);
}
void AFPSCharacter::MoveRight(float Value)
{
	// ��ȷ�ĸ������ǡ����ҡ�������¼�����ͼ��˷����ƶ���
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
	/* ������Ҫд������ �󶨶��� */

	// try and play a firing animation if specified
	if (FireAnimation != NULL)
	{
		// Get the animation object for the arms mesh
		UAnimInstance* AnimInstance = FPSMesh->GetAnimInstance();
		//Ҫ�ر�ע����˭���˶���
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


	// ���Է������塣
	if (ProjectileClass)
	{
		// ��ȡ������任��
		FVector CameraLocation;
		//����λ��

		FRotator CameraRotation;
		//������ת
		
		GetActorEyesViewPoint(CameraLocation, CameraRotation);
		/*
		���Ե�һ��ֵ��˵�ˣ��������λ�ú������ƽ��[��BaseEyeHeight��������]
		�ڶ����ǻ�ȡ���������ת�Ƕ�

		λ���� 
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
	���ش���Ա�ĸ������λ��
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
		���ظ��������ת
		
		*/


		// �� MuzzleOffset ��������ռ�任������ռ䡣
		FVector MuzzleLocation = CameraLocation + FTransform(CameraRotation).TransformVector(MuzzleOffset);
		// MuzzleLocation��λ��(ǹ��λ��) = ��ȡ������任 +  ������
		/*
		���г�ʼ��ת�Ĺ��캯��
		@��תʹ����ת�����ֵ������ת��Ϊһ����Ԫ���� 
		�����ٵ��Ľ��� == ������
		*/

		FRotator MuzzleRotation = CameraRotation;
		//ǹ����ת���� �����ת ǹ�������������ˡ�

		// ��׼����΢��̧��
		MuzzleRotation.Pitch += 10.0f;
		/*
		��������ת����Y�ᣩ�����Ϻ����¿���0 =ǰ����+��-�� 
		float Pitch; 
		
		*/



		UWorld* World = GetWorld();
		//������
		
		
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
			��������������캯��������һ��
			*/

			SpawnParams.Owner = this;
			/*
			�����Ա����Ա�����ɱ���Ϊ�գ� 
			AActor* Owner;
			*/

			SpawnParams.Instigator = Instigator;
			/*
			APawn*	Instigator;
			һ���ɸ������Ա����𺦵����ӡ����ɱ���Ϊ�գ� 
			
			UPROPERTY(BlueprintReadWrite, replicatedUsing=OnRep_Instigator, meta=(ExposeOnSpawn=true), Category=Actor)
			class APawn* Instigator;
			�������Ա��ɵ��𻵵����ӡ�

			�����ӵ�ӵ�в����˺���������
			*/

			// ��ǹ�ڴ����ɷ����
			AFPSProjectile* Projectile = World->SpawnActor<AFPSProjectile>(ProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParams);
			/*
			ģ��汾����������Ա����������ָ����ת�Ͷ�λ            
			*��ͨ�������������������Ǹ����͵ĸ��� 
			template< class T >
			T* SpawnActor( UClass* Class, FVector const& Location, FRotator const& Rotation, const FActorSpawnParameters& SpawnParameters = FActorSpawnParameters() )
			{
			return CastChecked<T>(SpawnActor(Class, &Location, &Rotation, SpawnParameters),ECastCheckedType::NullAllowed);
			}
			���ĸ����� ��/λ��/��ת/��������
			
			//��˼���Ǹ�������ָ��λ�����������ɡ�
			*/

			if (Projectile)
			{
				// ���÷�����ĳ�ʼ�����
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
				//Ȼ���������ľ���ļ��㹫ʽ��....
				��Ϊ�Ǵ�ǹ���������ȥ�ģ������õ���MuzzleRotation.
				*/

				Projectile->FireInDirection(LaunchDirection);
				//����һ���������....����֮ǰ���Ǹ�



			}
		}
	}
}