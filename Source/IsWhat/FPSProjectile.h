// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "FPSProjectile.generated.h"

//��ɫ��ȫ�Ǳ�¶��UE4��
UCLASS()
class ISWHAT_API AFPSProjectile : public AActor//A��һ��Ĭ��ǰ׺�����ǵĺ����̳���Actor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFPSProjectile();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;


	// ������ײ�����
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
	USphereComponent* CollisionComponent;

	// �������˶������
	UPROPERTY(VisibleAnywhere, Category = Movement)
	UProjectileMovementComponent* ProjectileMovementComponent;
	//ֻҪ��Vis�Ķ������Ա༭ ��E��ͷ���г�ͻ


	// �ڷ��䷽�������÷�������ٶȵĺ�����
	void FireInDirection(const FVector& ShootDirection);

	// ��������������ʱ���õĺ�����
	//����----------------------------------------------------------------------------------------------------------��

	//UFUNCTION()
	void OnHit(class AActor* OtherActor, class UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);


	
};
//<!------------------------------------------------------------------------------------------------------------------>