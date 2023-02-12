// Fill out your copyright notice in the Description page of Project Settings.


#include "PingPongBall.h"
#include "PingPongGoal.h"
#include "Components/AudioComponent.h"
#include "Engine/AssetManager.h"
#include "Engine/StreamableManager.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Net/UnrealNetwork.h"
#include "Particles/ParticleSystem.h"
#include "PingPong/PingPongGameStateBase.h"

// Sets default values
APingPongBall::APingPongBall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ball Body	Mesh"));
	BodyMesh->SetIsReplicated(true);	
	// ConstructorHelpers::FObjectFinder<UStaticMesh> LoadedBallMeshObj(TEXT("/Engine/VREditor/BasicMeshes/SM_Ball_01.SM_Ball_01"));
	// BodyMesh->SetStaticMesh(LoadedBallMeshObj.Object);
	BallCollideSound = CreateDefaultSubobject<UAudioComponent>(TEXT("OnDestroyAudioEffect"));
	BallCollideSound->SetupAttachment(BodyMesh);
	BallCollideSound->SetAutoActivate(false);
	SetRootComponent(BodyMesh);
	SetReplicateMovement(true);
	bReplicates=true;
	
}

// Called when the game starts or when spawned
void APingPongBall::BeginPlay()
{
	Super::BeginPlay();
	LoadBodyMesh();
	LoadParticleEffect();
	StartPosition = GetActorLocation();
	PingPongGameState = Cast<APingPongGameStateBase>(UGameplayStatics::GetGameState(GetWorld()));
	verify(PingPongGameState);
	ResetBall();
}

// Called every frame
void APingPongBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);	
	if (GetNetMode() != ENetMode::NM_Client && PingPongGameState->PlayingGame)
	{
		Server_Move(DeltaTime);
	}

}

void APingPongBall::LoadBodyMesh()
{
	FStreamableDelegate LoadMeshDelegate;
	LoadMeshDelegate.BindUObject(this,&APingPongBall::OnBodyMeshLoaded);
	UAssetManager& assetManager = UAssetManager::Get();
	FStreamableManager& streamableManager = assetManager.GetStreamableManager();
	AssetHandle = streamableManager.RequestAsyncLoad(BodyMeshRef.ToString(),LoadMeshDelegate);
}

void APingPongBall::OnBodyMeshLoaded()
{
	UStaticMesh* loadedMesh = Cast<UStaticMesh>(AssetHandle.Get()->GetLoadedAsset());
	if(loadedMesh)
	{
		BodyMesh->SetStaticMesh(loadedMesh);
	}
}

void APingPongBall::LoadParticleEffect()
{
	FStreamableDelegate LoadParticleDelegate;
	LoadParticleDelegate.BindUObject(this,&APingPongBall::OnParticleEffectLoaded);
	UAssetManager& assetManager = UAssetManager::Get();
	FStreamableManager& streamableManager = assetManager.GetStreamableManager();
	ParticleEffectAssetHandle = streamableManager.RequestAsyncLoad(ParticleEffectRef.ToString(),LoadParticleDelegate);

}

void APingPongBall::OnParticleEffectLoaded()
{
	HitEffect = Cast<UParticleSystem>(ParticleEffectAssetHandle.Get()->GetLoadedAsset());	
}

void APingPongBall::StartMove()
{
	Server_StartMove();
}

void APingPongBall::StopMove()
{
	Server_StopMove();
}

void APingPongBall::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(APingPongBall,isMoving);
}

void APingPongBall::ResetBall()
{
	SetActorLocation(StartPosition);
	PingPongGameState->ResetBallHits();
	Direction.X=UKismetMathLibrary::RandomFloat();
	Direction.Y=UKismetMathLibrary::RandomFloat();
	MoveSpeed=DefaultMoveSpeed;
	BallCollideSound->SetPitchMultiplier(1);
}

void APingPongBall::Multicast_HitEffect_Implementation()
{
	UWorld * world = GetWorld();
	if(world && HitEffect)
	{
		if(PingPongGameState->GetMaxScore()!=PingPongGameState->GetBallHits()) return;
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitEffect,GetActorLocation());
	}
}

void APingPongBall::Server_StopMove_Implementation()
{
	isMoving = false;
}

bool APingPongBall::Server_StopMove_Validate()
{
	return true;
}

void APingPongBall::Server_StartMove_Implementation()
{
	isMoving = true;
	
}

bool APingPongBall::Server_StartMove_Validate()
{
	return true;
}

void APingPongBall::Server_Move_Implementation(float DeltaTime)
{	
	if(!isMoving) return;
	currLoc = GetActorLocation();
	FVector MovePos = Direction*MoveSpeed*DeltaTime;
	newLoc = MovePos+currLoc;
	newLoc.Z=50;
	FHitResult HitResult;
	if(!SetActorLocation(newLoc, true, &HitResult))
	{	
		Multicast_HitEffect();
		if(PingPongGameState->GetBallHits()<PingPongGameState->GetMaxScore())
		{
			PingPongGameState->AddValueToBallHits(1);
			BallCollideSound->PitchMultiplier+=0.1;
			MoveSpeed+=500;
		}		
		BallCollideSound->Play();		
		FVector newDirection = UKismetMathLibrary::GetReflectionVector(Direction,HitResult.Normal);
		newDirection.Z=50;
		Direction=newDirection;
		if(APingPongGoal* PingPongGoal = Cast<APingPongGoal>(HitResult.GetActor()))
		{
			if(PingPongGoal->Tags[0]=="Blue" && PingPongGameState)
			{
				PingPongGameState->AddScoreToGreenPlayer(PingPongGameState->GetBallHits());
				ResetBall();
			}
			else
			{
				PingPongGameState->AddScoreToBluePlayer(PingPongGameState->GetBallHits());
				ResetBall();
			}
		}
	}
}

bool APingPongBall::Server_Move_Validate(float DeltaTime)
{
	return true;
}

