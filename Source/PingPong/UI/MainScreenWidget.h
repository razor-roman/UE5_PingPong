// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "MainScreenWidget.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class PINGPONG_API UMainScreenWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(meta=(BindWidget))
	UTextBlock* ScoreBlue;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* ScoreGreen;
	UPROPERTY(meta=(BindWidget))
	UProgressBar* TouchCountBar;
public:
	UFUNCTION(BlueprintCallable)
	void SetScoreBlue(int Value);
	UFUNCTION(BlueprintCallable)
	void SetScoreGreen(int Value);
	UFUNCTION(BlueprintCallable)
	void SetTouchCountBar(float Value);
	
};
