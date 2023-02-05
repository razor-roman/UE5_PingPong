// Fill out your copyright notice in the Description page of Project Settings.


#include "PingPongGameStateBase.h"

void APingPongGameStateBase::AddScoreToGreenPlayer(int Value)
{
	ScoreGreen+=Value;
}

void APingPongGameStateBase::AddScoreToBluePlayer(int Value)
{
	ScoreBlue=+Value;
}
