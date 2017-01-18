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
		// 显示调试信息五秒。 
		// -1“键”值（首个参数）说明我们无需更新或刷新此消息。
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Hello World, this is FPSGameMode!"));
		std::cout << "???????"<<std::endl;
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Hi~it's a game?oh,i like is!"));
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Wo,you look the game,Do you batter good ider for game?push my 2502514088@qq.com,please.Thank you!"));
	}
}


