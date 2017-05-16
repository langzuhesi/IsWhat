// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "FPSCharacter.generated.h"

UCLASS()
class ISWHAT_API AFPSCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPSCharacter();
	//��һ�����Ǳߵ��Ǹ������� ��������һ�� ���÷�������ô����������ĺ��� ����//��
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	//.cpp�����Ӧ��BeginPlay  ������
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;
	//ͬ���Ƕ�Ӧ.cpp�ļ��е�Tick
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// ����ǰ���ƶ������롣
	//��Ӧ.cpp

	
	//����ָ����ovo

	// ����ǰ���ͺ��˵����롣
	//UFUNCTION()
		//void MoveForward(float Value);

	// ���������ƶ������롣
	//UFUNCTION()
		//void AFPSCharacter::MoveRight(float Value)void MoveRight(float Value);
	void AFPSCharacter::MoveRight(float Value);
	void AFPSCharacter::MoveForward(float Value);


	//�������� ���ɳɹ����ǲ�����Ծ
	void AFPSCharacter::StartJump();
	void AFPSCharacter::StopJump();

	// FPS �������
	UPROPERTY(VisibleAnywhere)// VisibleAnywhere ָʾ�������ڡ����ԡ������пɼ�����������ȫ�༭ 
		UCameraComponent* FPSCameraComponent;
	//���ƺ���һ��ָ�� ��ָ�� ���ָ�����ֽ� FPSCameraComponent ָ��UCameraComponent�� �����ָ�봫�ݽ�ȥ������

	// ��һ�˳�ģ�ͣ��ֱۣ�������ӵ����ҿɼ���
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)//VisibleDefaultsOnly ָʾ��������ԭ�����Դ����ǿɼ��ģ����Ҳ��ܱ��༭��
		//���ڶ�������ʲô��˼�����ܹ���⡿
		USkeletalMeshComponent* FPSMesh;
	//ָ�����ָ�� ���������������йء�����

	// ������ĺ�����
	UFUNCTION()
		void Fire();

	// �������λ�õ�ǹ��ƫ�ơ�//CSCSCSC
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		FVector MuzzleOffset;

	// ���ɵķ������ࡣ
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
		TSubclassOf<class AFPSProjectile> ProjectileClass;

	/** Gun mesh: 1st person view (seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USkeletalMeshComponent* Mesh1P;


};
