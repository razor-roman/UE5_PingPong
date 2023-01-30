// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Widget.h"
#include "GameFramework/Pawn.h"
#include "PingPong/PingPongPlayerState.h"
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

public:
	UFUNCTION()
	void ScoreUpdate(int value);
};
