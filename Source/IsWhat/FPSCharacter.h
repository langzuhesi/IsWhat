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
	// 处理前后移动的输入。


	
	//错误分割符号ovo

	// 处理前进和后退的输入。
	//UFUNCTION()
		//void MoveForward(float Value);

	// 处理左右移动的输入。
	//UFUNCTION()
		//void AFPSCharacter::MoveRight(float Value)void MoveRight(float Value);
	void AFPSCharacter::MoveRight(float Value);
	void AFPSCharacter::MoveForward(float Value);


	//遗留问题 生成成功但是不能跳跃
	void AFPSCharacter::StartJump();
	void AFPSCharacter::StopJump();

	// FPS 摄像机。
	UPROPERTY(VisibleAnywhere)
		UCameraComponent* FPSCameraComponent;

	// 第一人称模型（手臂），仅对拥有玩家可见。
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		USkeletalMeshComponent* FPSMesh;
};
