// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "PingPongGameStateBase.generated.h"

/**
 * 
 */
UCLASS()
class PINGPONG_API APingPongGameStateBase : public AGameStateBase
{
	GENERATED_BODY()
	
protected:
	UPROPERTY()
	int ScoreGreen=0,ScoreBlue=0;
public:
	void AddScoreToGreenPlayer(int Value);
	void AddScoreToBluePlayer(int Value);
};
