// Fill out your copyright notice in the Description page of Project Settings.

#include "IsWhat.h"
#include "FPSProjectile.h"


// Sets default values
AFPSProjectile::AFPSProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//�Ƿ�ÿ֡����ˢ�£����ũd (o �� �� �� O ) ��?


	// ʹ������������ײ��
	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	/*
	���õ�Ӧ���������ģ�壬Ȼ��ٷ����Ľ����������ġ�����
	template<class TReturnType>
	TReturnType* CreateDefaultSubobject(FName SubobjectName, bool bTransient = false)
	{
		UClass* ReturnType = TReturnType::StaticClass();
		return static_cast<TReturnType*>(CreateDefaultSubobject(SubobjectName, ReturnType, ReturnType,  true,  false, bTransient));
     }
	*/
	/**
	* Create a component or subobject ����һ����������
	* @param	TReturnType					class of return type, all overrides must be of this type �Զ������͵ģ����и������ͱ������Զ���ģ����������
	* @param	Outer						outer to construct the subobject in �⹹���Ӷ����� Object.h���
	* @param	SubobjectName				name of the new component ���Ƶ������ 
	* @param bTransient		true if the component is being assigned to a transient property �����������䵽һ��˲̬���� 

	Ȼ������ֻ�Ǽ򵥵ĸ������˸�����(o�b���b)o�� ������Ӧ�ð���Ĭ�����˰�-��-

	*/

	CollisionComponent->BodyInstance.SetCollisionProfileName(TEXT("Projectile"));
	/*
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Collision, meta=(ShowOnlyInnerProperties))
	FBodyInstance BodyInstance;
	����������������Ϣ��ӵ��һ����һ�ĸ���������״�� 

	����_��......��


	*/
	
	
	
	//CollisionComponent->OnComponentHit.AddDynamic(this , &AFPSProjectile::OnHit);
	//[0.0????]







	// �����������ײ�뾶��
	CollisionComponent->InitSphereRadius(15.0f);
	//UPROPERTY(EditAnywhere, BlueprintReadOnly, export, Category=Shape)
	//float SphereRadius;
	//���ֵ��¶����ͼ����ֻ�� �����޸�
	//FORCEINLINE void InitSphereRadius(float InSphereRadius) { SphereRadius = InSphereRadius; }
	//Sets the sphere radius without triggering a render or physics update.
	//��������뾶����������Ⱦ��������¡� 


	// ����ײ�����Ϊ�������
	RootComponent = CollisionComponent;
	//RootComponent �Ǹ������

	/*
	    // ���ǵĸ������һ�����������Ϊ������Ӧ������
    USphereComponent* SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent"));
    RootComponent = SphereComponent;
    SphereComponent->InitSphereRadius(40.0f);
    SphereComponent->SetCollisionProfileName(TEXT("Pawn"));
	
	��˵�������ײ��һ�ڣ��и����Ƶ�  ���ȸ�SphereComponent���˸�������RootComponent��������һЩ������������Ը���
	Ȼ���SphereComponent��Ϊ�����
	
	*/





	// ʹ�ô���������÷�������˶���
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	//���������˶�����Ĭ��

	ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);
	/*
	void UMovementComponent::SetUpdatedComponent(USceneComponent* NewUpdatedComponent)
	USphereComponent* CollisionComponent;<---- ���ļ������ϼ̳���USceneComponent

	Ȼ�����ݺܸ��ӣ������ ��ProjectileMovementComponent�ŵ������CollisionComponent����
	//ProjectileMovementComponent�ǿ����˶���
	*/

	ProjectileMovementComponent->InitialSpeed = 3000.0f;
	/*
	�ӵ���ʼ�ٶ�. ��������㣬�⽫���ǳ�ʼ�ٶ�ֵ�������ٶ���Ϊһ������ 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Projectile)
		float InitialSpeed;
	//���Ǹ��˳�ʼ�ٶȰ�0.0....
	*/

	ProjectileMovementComponent->MaxSpeed = 3000.0f;
	/*
	//�ӵ��ļ����ٶȣ�0��ʾû�����ƣ� 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Projectile)
		float MaxSpeed;
	//��Ĭ��ֵ
	*/

	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	/*
	//���TRUE��������轫��������ת����ÿ��֡����������ٶȵķ��� 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Projectile)
		uint32 bRotationFollowsVelocity : 1;
	//Ĭ����ת
	*/

	ProjectileMovementComponent->bShouldBounce = true;
	/*
	 //���TRUE���򵥵ķ�����ģ�⡣����Ϊfalseֹͣģ��Ӵ��� 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ProjectileBounces)
		uint32 bShouldBounce : 1;
	//Ĭ��Ϊ��
	*/

	ProjectileMovementComponent->Bounciness = 0.3f;
	/*
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=ProjectileBounces, meta=(ClampMin="0", UIMin="0"))
	//��¶��һЩ���ԣ������ڱ༭���ڿ�������ͼ����ֻ���� ����� ������ �������Ǹ�...��HUD�йأ�
	float Bounciness; ���Է���

	�������������ķ����󱣳ֵ��ٶȰٷֱȣ��ָ�ϵ������            
	* 1 =û���ٶȶ�ʧ��0 =û�з������������BӦ�÷����Ǽٵġ�
	//���Թٵ�����˼��0-1����д��ֵ 0.0��
	*/

	// 3 ���������
	InitialLifeSpan = 3.0f;
	/*
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Actor)
	float InitialLifeSpan;
	�����Ա��ǰ���˶�ã�0 =��Զ��ע�����ǳ�ʼֵ����Ӧ������Ϸ��ʼ���޸ġ� 
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


// �ڷ��䷽�������÷�������ٶȵĺ�����
void AFPSProjectile::FireInDirection(const FVector& ShootDirection)
{
	ProjectileMovementComponent->Velocity = ShootDirection * ProjectileMovementComponent->InitialSpeed;
	/*
	�ռ�λ�� ��ֵΪ һ���ٶ� 0.0������

	//Current velocity of updated component. 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Velocity)
		FVector Velocity;//��һ���ռ�λ�� (x,y,z)
	


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Projectile)
		float InitialSpeed;
	
	*/

}
//����------------------------------------------------------------------------------------------------------��

void AFPSProjectile::OnHit ( AActor * OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor != this && OtherComponent->IsSimulatingPhysics())
	{
		OtherComponent->AddImpulseAtLocation(ProjectileMovementComponent->Velocity * 100.0f, Hit.ImpactPoint);
	}
}

//<!------------------------------------------------------------------------------------------------------------------>

