// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "PingPongPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class PINGPONG_API APingPongPlayerState : public APlayerState
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite);
	int PlayerScore;
public:
	UFUNCTION(BlueprintCallable)
	void SetScore(int value) {PlayerScore=value;}
	UFUNCTION()
	int GetScore() const {return PlayerScore;}
	UFUNCTION()
	void AddToScore(int value) {PlayerScore=PlayerScore+value;} 
};
