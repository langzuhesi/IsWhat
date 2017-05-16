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
	//这一步是那边的那个主函数 这里声明一下 调用方法【怎么调用类里面的函数 还是//】
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	//.cpp里面对应的BeginPlay  声明的
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;
	//同样是对应.cpp文件中的Tick
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// 处理前后移动的输入。
	//对应.cpp

	
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
	UPROPERTY(VisibleAnywhere)// VisibleAnywhere 指示此属性在“属性”窗口中可见，但不能完全编辑 
		UCameraComponent* FPSCameraComponent;
	//这似乎是一个指针 类指针 这个指针名字叫 FPSCameraComponent 指向UCameraComponent类 把这个指针传递进去。。。

	// 第一人称模型（手臂），仅对拥有玩家可见。
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)//VisibleDefaultsOnly 指示该属性在原型属性窗口是可见的，并且不能被编辑，
		//【第二个参数什么意思？不能够理解】
		USkeletalMeshComponent* FPSMesh;
	//指向类的指针 这个类跟骨骼网络有关。。。

	// 处理开火的函数。
	UFUNCTION()
		void Fire();

	// 从摄像机位置的枪口偏移。//CSCSCSC
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		FVector MuzzleOffset;

	// 生成的发射物类。
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
		TSubclassOf<class AFPSProjectile> ProjectileClass;

	/** Gun mesh: 1st person view (seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USkeletalMeshComponent* Mesh1P;


};
