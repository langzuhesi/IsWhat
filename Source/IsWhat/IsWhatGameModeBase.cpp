// Fill out your copyright notice in the Description page of Project Settings.

#include "IsWhat.h"
#include "IsWhatGameModeBase.h"
#include <iostream>
using namespace std;
void AIsWhatGameModeBase::StartPlay()
{
	Super::StartPlay();

	if (GEngine)
	{
		// ��ʾ������Ϣ���롣 
		// -1������ֵ���׸�������˵������������»�ˢ�´���Ϣ��
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Hello World, this is FPSGameMode!"));
		std::cout << "???????"<<std::endl;
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Hi~it's a game?oh,i like is!"));
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Wo,you look the game,Do you batter good ider for game?push my 2502514088@qq.com,please.Thank you!"));
	}
}


