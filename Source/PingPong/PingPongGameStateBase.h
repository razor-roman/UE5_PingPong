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
	UPROPERTY(EditAnywhere,Replicated)
	int ScoreGreen;
	UPROPERTY(EditAnywhere,Replicated)
	int ScoreBlue;
	UPROPERTY(EditAnywhere,Replicated)
	int BallHits;
	UPROPERTY(EditAnywhere,Replicated)
	int MaxScore=10;
public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool PlayingGame;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	uint8  Timer=3;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool AllPlayerConnected;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	uint8  Players;
	
public:
	UFUNCTION(BlueprintCallable)
	void AddScoreToGreenPlayer(int Value);
	UFUNCTION(BlueprintCallable)
	void AddScoreToBluePlayer(int Value);
	UFUNCTION(BlueprintCallable)
	void AddValueToBallHits(int Value);
	UFUNCTION(BlueprintCallable)
	int GetScoreBluePlayer()  {return ScoreBlue;}
	UFUNCTION(BlueprintCallable) 
	int GetScoreGreenPlayer()  {return ScoreGreen;}
	UFUNCTION(BlueprintCallable) 
	int GetBallHits()  {return BallHits;}
	UFUNCTION(BlueprintCallable) 
	void ResetBallHits()  {BallHits=1;}
	int GetMaxScore() {return MaxScore;}
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty > & OutLifetimeProps ) const override;
	APingPongGameStateBase();
};
