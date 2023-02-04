// Fill out your copyright notice in the Description page of Project Settings.


#include "PingPongGameState.h"

void APingPongGameState::AddScoreToGreenPlayer(int Value)
{
	ScoreGreen+=Value;
}

void APingPongGameState::AddScoreToBluePlayer(int Value)
{
	ScoreBlue=+Value;
}
