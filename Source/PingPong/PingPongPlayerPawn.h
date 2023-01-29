// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "PingPongGoal.h"
#include "PingPongHUD.h"
#include "PingPongPlayerState.h"
#include "Components/Widget.h"
#include "GameFramework/Pawn.h"
#include "PingPongPlayerPawn.generated.h"

class UMainScreenWidget;
UCLASS()
class PINGPONG_API APingPongPlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APingPongPlayerPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category ="Components")
	class USpringArmComponent * SpringArm;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category ="Components")
	class UCameraComponent * Camera;
	
	UPROPERTY(EditAnywhere, Category = UI)
	TSubclassOf<UMainScreenWidget> WidgetTemplate;

	UPROPERTY()
	UMainScreenWidget* WidgetInstance;
	
	// UPROPERTY()
	// APingPongPlayerState* PingPongPlayerStatePlayerState;
	
public:
	UFUNCTION()
	void ScoreUpdate(int value);
};
