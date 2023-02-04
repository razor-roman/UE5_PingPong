// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "Pawns/PingPongPlayerPawn.h"
#include "PingPongGameState.generated.h"

/**
 * 
 */
UCLASS()
class PINGPONG_API APingPongGameState : public AGameState
{
	GENERATED_BODY()
protected:
	UPROPERTY()
	int ScoreGreen=0,ScoreBlue=0;
 public:
	void AddScoreToGreenPlayer(int Value);
	void AddScoreToBluePlayer(int Value);
};
