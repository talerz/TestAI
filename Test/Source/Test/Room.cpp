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


	bSleepingRoom = false;
	InteractiveObjectsCounter = 0;
	OccupiedInteractiveObjects = 0;
	MaxRoomAI = 100;
}

// Called when the game starts or when spawned
void ARoom::BeginPlay()
{
	Super::BeginPlay();

	InteractiveObjectsCounter = InteractiveObjects.Num();
	if (InteractiveObjects.Num() <= 0)
		return;
	for (AInteractiveObject* InteractiveObject : InteractiveObjects)
	{
		if (InteractiveObject)
			InteractiveObject->SetRoom(this);
	}
}

AInteractiveObject* ARoom::FindInteractiveObject()
{
	if (InteractiveObjects.Num() <= 0)
		return nullptr;

	AInteractiveObject* PotentialInterObj = nullptr;

	while (!PotentialInterObj || PotentialInterObj->IsObjectFull())
	{
		if(!IsAnyObjectFree())
			return nullptr;
		PotentialInterObj = InteractiveObjects[FMath::RandRange(0, InteractiveObjects.Num() - 1)];
	}
	return PotentialInterObj;
}

bool ARoom::IsAnyObjectFree() const
{
	return OccupiedInteractiveObjects < InteractiveObjectsCounter;
}

void ARoom::ChangeOccupiedInteractiveObjects(int32 ChangeValue)
{ 
	if(OccupiedInteractiveObjects <= 0 && ChangeValue < 0)
		return;

	OccupiedInteractiveObjects = FMath::Clamp((OccupiedInteractiveObjects + ChangeValue), 0, InteractiveObjectsCounter);
}

void ARoom::FreeWholeRoom()
{
	if (InteractiveObjects.Num() <= 0)
		return;
	for (AInteractiveObject* const InterObj : InteractiveObjects)
	{
		if (InterObj)
			InterObj->FreeWholeInterObject();
	}
	OccupiedInteractiveObjects = 0;
}

