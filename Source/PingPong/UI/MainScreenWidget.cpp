// Fill out your copyright notice in the Description page of Project Settings.


#include "MainScreenWidget.h"


void UMainScreenWidget::SetScoreBlue(int Value)
{
	ScoreBlue->SetText(FText::AsNumber(Value));
}

void UMainScreenWidget::SetScoreGreen(int Value)
{
	ScoreGreen->SetText(FText::AsNumber(Value));
}

void UMainScreenWidget::SetTouchCountBar(float Value)
{
	TouchCountBar->SetPercent(Value);
}
