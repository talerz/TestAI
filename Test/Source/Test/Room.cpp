// Fill out your copyright notice in the Description page of Project Settings.


#include "Room.h"

#include "AICharacter.h"
#include "InteractiveObject.h"
#include "Components/BoxComponent.h"

// Sets default values
ARoom::ARoom()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>("Box");
	BoxCollision->SetupAttachment(RootComponent);
	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &ARoom::OnBeginOverlap);
	BoxCollision->OnComponentEndOverlap.AddDynamic(this, &ARoom::OnEndOverlap);

	bSleepingRoom = false;
	AIRoomCounter = 0;
	MaxRoomAI = 100;
}

void ARoom::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor)
		return;

	AAICharacter* NewAIChar = Cast< AAICharacter>(OtherActor);
	if (NewAIChar)
		OnAIEnterRoom();
}

void ARoom::OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!OtherActor)
		return;

	AAICharacter* NewAIChar = Cast< AAICharacter>(OtherActor);
	if (NewAIChar)
		OnAIExitRoom();
}

// Called when the game starts or when spawned
void ARoom::BeginPlay()
{
	Super::BeginPlay();

}

void ARoom::ChangeAIRoomCounter(bool bEnter)
{
	if (bEnter)
		AIRoomCounter++;
	else
		AIRoomCounter = FMath::Clamp(AIRoomCounter--, 0, MaxRoomAI);
}

void ARoom::OnAIEnterRoom()
{
	ChangeAIRoomCounter( true);
}

void ARoom::OnAIExitRoom()
{
	ChangeAIRoomCounter(false);
}

AInteractiveObject* ARoom::FindInteractiveObject()
{
	if (InteractiveObjects.Num() <= 0)
		return nullptr;

	AInteractiveObject* PotentialInterObj = nullptr;
	//inf loop prevented in BT
	while (!PotentialInterObj || !PotentialInterObj->IsAnySpotAvailable())
	{
		PotentialInterObj = InteractiveObjects[FMath::RandRange(0, InteractiveObjects.Num() - 1)];
	}
	return PotentialInterObj;
}

bool ARoom::IsAnyObjectFree() const
{
	if (InteractiveObjects.Num() <= 0)
		return false;
	for (AInteractiveObject* const InterObj : InteractiveObjects)
	{
		if(InterObj && InterObj->IsAnySpotAvailable())
			return true;
	}
	return false;
}

void ARoom::SetInteractiveObjects()
{
	TArray<AActor*> OverlappingActors;
	GetOverlappingActors(OverlappingActors, AInteractiveObject::StaticClass());
	for (AActor* OverlappingActor : OverlappingActors)
	{
		if (OverlappingActor)
			InteractiveObjects.AddUnique(Cast<AInteractiveObject>(OverlappingActor));
	}

}

// Called every frame
void ARoom::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

