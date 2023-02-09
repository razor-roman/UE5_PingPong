// Fill out your copyright notice in the Description page of Project Settings.


#include "PingPongGameStateBase.h"
#include "Net/UnrealNetwork.h"

void APingPongGameStateBase::AddScoreToGreenPlayer(int Value)
{
	if(ScoreGreen<MaxScore)
	ScoreGreen+=Value;
}

void APingPongGameStateBase::AddScoreToBluePlayer(int Value)
{
	if(ScoreBlue<MaxScore)
	ScoreBlue+=Value;
}

void APingPongGameStateBase::AddValueToBallHits(int Value)
{
	if(BallHits<MaxScore)
	BallHits+=Value;	
}

void APingPongGameStateBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME( APingPongGameStateBase, ScoreGreen );
	DOREPLIFETIME( APingPongGameStateBase, ScoreBlue );
	DOREPLIFETIME( APingPongGameStateBase, BallHits );
}

APingPongGameStateBase::APingPongGameStateBase()
{
	bReplicates=true;
}

