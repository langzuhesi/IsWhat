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

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// ����ǰ���ƶ������롣


	
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
	UPROPERTY(VisibleAnywhere)
		UCameraComponent* FPSCameraComponent;

	// ��һ�˳�ģ�ͣ��ֱۣ�������ӵ����ҿɼ���
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		USkeletalMeshComponent* FPSMesh;
};
