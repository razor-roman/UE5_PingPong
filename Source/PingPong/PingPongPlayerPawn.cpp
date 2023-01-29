// Fill out your copyright notice in the Description page of Project Settings.


#include "PingPongPlayerPawn.h"
#include "MainScreenWidget.h"
#include "PingPongPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
APingPongPlayerPawn::APingPongPlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	USceneComponent * root =CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = root;
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetRootComponent());
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
	SetReplicates(true);
}

// Called when the game starts or when spawned
void APingPongPlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	if (WidgetTemplate)
	{
		if (!WidgetInstance)
		{
			WidgetInstance = CreateWidget<UMainScreenWidget>(GetWorld()->GetFirstPlayerController(), WidgetTemplate);
		}
		if (!WidgetInstance->GetIsVisible())
		{
			WidgetInstance->AddToViewport();
		}
	}
}

// Called every frame
void APingPongPlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

// Called to bind functionality to input
void APingPongPlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
}

void APingPongPlayerPawn::ScoreUpdate(int value)
{
	APingPongPlayerState* PingPongPlayerState = GetPlayerStateChecked<APingPongPlayerState>();
    PingPongPlayerState->AddToScore(value);
	WidgetInstance->SetScoreText(PingPongPlayerState->GetScore());
}
