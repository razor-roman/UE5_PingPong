// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PingPong/Pawns/PingPongPlayerPawn.h"
#include "PingPongBall.generated.h"

struct FStreamableHandle;
class APingPongGameStateBase;
class USphereComponent;
UCLASS()
class PINGPONG_API APingPongBall : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APingPongBall();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* BodyMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ball params")
	UParticleSystem* HitEffect;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ball params")
	UAudioComponent* BallCollideSound;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSoftObjectPtr<UStaticMesh> BodyMeshRef;
	TSharedPtr<FStreamableHandle> AssetHandle;
	UFUNCTION(CallInEditor,BlueprintCallable)
	void LoadBodyMesh();
	void OnBodyMeshLoaded();
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	TSoftObjectPtr<UParticleSystem> ParticleEffectRef;
	TSharedPtr<FStreamableHandle> ParticleEffectAssetHandle;
	UFUNCTION(CallInEditor,BlueprintCallable)
	void LoadParticleEffect();
	void OnParticleEffectLoaded();
	
	UPROPERTY(Replicated)
	bool isMoving = true;	
	
	FVector forward;
	FVector currLoc;
	FVector newLoc ;
protected:
	UFUNCTION(Server, Reliable, WithValidation)
	void Server_Move(float DeltaTime);
	UFUNCTION(Server, Reliable, WithValidation)
	void Server_StartMove();
	UFUNCTION(Server, Reliable, WithValidation)
	void Server_StopMove();
	UFUNCTION(NetMulticast, Unreliable)
	void Multicast_HitEffect();
	virtual void GetLifetimeReplicatedProps(TArray < class FLifetimeProperty >& OutLifetimeProps) const override;
	
public:
	UFUNCTION(BlueprintCallable)
	void StartMove();
	UFUNCTION(BlueprintCallable)
	void StopMove();
		
public:
	void ResetBall();
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ball params")
	float MoveSpeed;
	UPROPERTY(EditAnywhere)
	float DefaultMoveSpeed = 2500;
	UPROPERTY(EditAnywhere)
	float SpeedUp = 300;
	
	FVector StartPosition;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ball params")
	FVector Direction;	
	
	FVector NewDirection;
	UPROPERTY()
	APingPongPlayerPawn* PlayerPawn;
protected:
	UPROPERTY()
	APingPongGameStateBase* PingPongGameState;

};

