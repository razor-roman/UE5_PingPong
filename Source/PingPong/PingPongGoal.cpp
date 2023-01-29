// Fill out your copyright notice in the Description page of Project Settings.


#include "PingPongGoal.h"

#include "PingPongBall.h"
#include "PingPongPlayerPawn.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
APingPongGoal::APingPongGoal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;	
	
	BoxCollision = CreateDefaultSubobject<UBoxComponent>("BoxCollision");
	BoxCollision->SetupAttachment(RootComponent);
	BoxCollision->OnComponentBeginOverlap.AddDynamic(this,&APingPongGoal::OnBeginOverlap);
	BoxCollision->OnComponentEndOverlap.AddDynamic(this,&APingPongGoal::OnEndOverlap);
	bReplicates=true;
	SetReplicateMovement(true);
}

// Called when the game starts or when spawned
void APingPongGoal::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APingPongGoal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void APingPongGoal::OnEndOverlap_Implementation(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if(OtherActor==OverlappedActor) OverlappedActor=nullptr;
}

void APingPongGoal::OnBeginOverlap_Implementation(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                                  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OverlappedActor!=OtherActor) OverlappedActor=OtherActor;
	else return;
	if(!PlayerPawn && Cast<APingPongBall>(OtherActor))
	{
		TArray<AActor*> Actors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(),APingPongPlayerPawn::StaticClass(),Actors);
		FVector Distance1,Distance2;
		double Vec1Size=0, Vec2Size=0;	
		if(Actors[0])
		{
			FVector PawnLocation = Actors[0]->GetActorLocation();
			FVector GoalLocation = GetActorLocation();
			Distance1 = GoalLocation-PawnLocation;		
			Vec1Size = UKismetMathLibrary::Vector4_Size(Distance1);
		}
		if(Actors[1])
		{
			FVector PawnLocation = Actors[1]->GetActorLocation();
			FVector GoalLocation = GetActorLocation();
			Distance2 = GoalLocation-PawnLocation;
			Vec2Size = UKismetMathLibrary::Vector4_Size(Distance2);
		}
		if(Vec1Size<Vec2Size)
		{
			PlayerPawn=Cast<APingPongPlayerPawn>(Actors[0]);
		}
		else
		{
			PlayerPawn=Cast<APingPongPlayerPawn>(Actors[1]);
		}
	}
	if(Cast<APingPongBall>(OtherActor))
	{
		PlayerPawn->ScoreUpdate(1);
	}
}