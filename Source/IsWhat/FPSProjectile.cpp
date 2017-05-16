// Fill out your copyright notice in the Description page of Project Settings.

#include "IsWhat.h"
#include "FPSProjectile.h"


// Sets default values
AFPSProjectile::AFPSProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//是否每帧调用刷新？嗯呐ヾ (o ° ω ° O ) ノ?


	// 使用球体代表简单碰撞。
	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	/*
	调用的应该是这个类模板，然后官方大大的解释是这样的↓↓↓
	template<class TReturnType>
	TReturnType* CreateDefaultSubobject(FName SubobjectName, bool bTransient = false)
	{
		UClass* ReturnType = TReturnType::StaticClass();
		return static_cast<TReturnType*>(CreateDefaultSubobject(SubobjectName, ReturnType, ReturnType,  true,  false, bTransient));
     }
	*/
	/**
	* Create a component or subobject 创建一个组件或对象
	* @param	TReturnType					class of return type, all overrides must be of this type 自定义类型的，所有覆盖类型必须是自定义的，而且是这个
	* @param	Outer						outer to construct the subobject in 外构建子对象在 Object.h里边
	* @param	SubobjectName				name of the new component 名称的新组件 
	* @param bTransient		true if the component is being assigned to a transient property 如果组件被分配到一个瞬态特性 

	然而我们只是简单的给他起了个名？(o゜▽゜)o？ 其他的应该按照默认走了吧-，-

	*/

	CollisionComponent->BodyInstance.SetCollisionProfileName(TEXT("Projectile"));
	/*
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Collision, meta=(ShowOnlyInnerProperties))
	FBodyInstance BodyInstance;
	这个组件的物理场景信息，拥有一个单一的刚体与多个形状。 

	【？_？......】


	*/
	
	
	
	//CollisionComponent->OnComponentHit.AddDynamic(this , &AFPSProjectile::OnHit);
	//[0.0????]







	// 设置球体的碰撞半径。
	CollisionComponent->InitSphereRadius(15.0f);
	//UPROPERTY(EditAnywhere, BlueprintReadOnly, export, Category=Shape)
	//float SphereRadius;
	//这个值暴露给蓝图，但只读 不可修改
	//FORCEINLINE void InitSphereRadius(float InSphereRadius) { SphereRadius = InSphereRadius; }
	//Sets the sphere radius without triggering a render or physics update.
	//设置球体半径，不触发渲染或物理更新。 


	// 将碰撞组件设为根组件。
	RootComponent = CollisionComponent;
	//RootComponent 是根组件的

	/*
	    // 我们的根组件是一个会对物理行为进行响应的球体
    USphereComponent* SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent"));
    RootComponent = SphereComponent;
    SphereComponent->InitSphereRadius(40.0f);
    SphereComponent->SetCollisionProfileName(TEXT("Pawn"));
	
	话说组件和碰撞那一节，有个类似的  首先给SphereComponent起了个名，叫RootComponent，付给它一些关于球体的属性给它
	然后把SphereComponent设为根组件
	
	*/





	// 使用此组件驱动该发射物的运动。
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	//让他等于运动啊的默认

	ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);
	/*
	void UMovementComponent::SetUpdatedComponent(USceneComponent* NewUpdatedComponent)
	USphereComponent* CollisionComponent;<---- 他的家族谱上继承了USceneComponent

	然后内容很复杂，大概是 将ProjectileMovementComponent放到根组件CollisionComponent下面
	//ProjectileMovementComponent是控制运动的
	*/

	ProjectileMovementComponent->InitialSpeed = 3000.0f;
	/*
	子弹初始速度. 如果大于零，这将覆盖初始速度值，而把速度作为一个方向。 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Projectile)
		float InitialSpeed;
	//就是改了初始速度吧0.0....
	*/

	ProjectileMovementComponent->MaxSpeed = 3000.0f;
	/*
	//子弹的极限速度（0表示没有限制） 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Projectile)
		float MaxSpeed;
	//无默认值
	*/

	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	/*
	//如果TRUE，这个弹丸将有它的旋转更新每个帧，以配合其速度的方向。 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Projectile)
		uint32 bRotationFollowsVelocity : 1;
	//默认旋转
	*/

	ProjectileMovementComponent->bShouldBounce = true;
	/*
	 //如果TRUE，简单的反弹将模拟。设置为false停止模拟接触。 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ProjectileBounces)
		uint32 bShouldBounce : 1;
	//默认为真
	*/

	ProjectileMovementComponent->Bounciness = 0.3f;
	/*
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=ProjectileBounces, meta=(ClampMin="0", UIMin="0"))
	//暴露了一些属性，可以在编辑器内看到，蓝图里面只读， 类别是 弹弹弹 ，后面那个...跟HUD有关？
	float Bounciness; 弹性反弹

	在正常冲击方向的反弹后保持的速度百分比（恢复系数）。            
	* 1 =没有速度丢失，0 =没有反弹。忽略如果B应该反弹是假的。
	//所以官爹的意思是0-1里面写个值 0.0？
	*/

	// 3 秒后消亡。
	InitialLifeSpan = 3.0f;
	/*
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Actor)
	float InitialLifeSpan;
	这个演员死前活了多久，0 =永远。注意这是初始值，不应该在游戏开始后修改。 
	*/



}

// Called when the game starts or when spawned
void AFPSProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFPSProjectile::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}


// 在发射方向上设置发射物初速度的函数。
void AFPSProjectile::FireInDirection(const FVector& ShootDirection)
{
	ProjectileMovementComponent->Velocity = ShootDirection * ProjectileMovementComponent->InitialSpeed;
	/*
	空间位置 赋值为 一个速度 0.0？？？

	//Current velocity of updated component. 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Velocity)
		FVector Velocity;//是一个空间位置 (x,y,z)
	


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Projectile)
		float InitialSpeed;
	
	*/

}
//《！------------------------------------------------------------------------------------------------------》

void AFPSProjectile::OnHit ( AActor * OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor != this && OtherComponent->IsSimulatingPhysics())
	{
		OtherComponent->AddImpulseAtLocation(ProjectileMovementComponent->Velocity * 100.0f, Hit.ImpactPoint);
	}
}

//<!------------------------------------------------------------------------------------------------------------------>

