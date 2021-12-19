// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractiveObject.h"

#include "Activity.h"
#include "Room.h"
#include "Spot.h"
#include "Components/BoxComponent.h"

// Sets default values
AInteractiveObject::AInteractiveObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>("Box");
	SetRootComponent(BoxCollision);
	CachedRoom = nullptr;
	InteractingAICounter = 0;
	StaringSpotsNumber = 0;
	bFullObject = false;

}


bool AInteractiveObject::IsAnySpotAvailable()
{
	if(SpotsStateMap.Num() <= 0)
		return false;
	for (const TPair<class ASpot*, bool>& Elem : SpotsStateMap)
	{
		if (Elem.Value == false)
		{
			ChangeObjectFull(false);
			return true;
		}
	}
	ChangeObjectFull(true);
	InteractingAICounter = StaringSpotsNumber;
	return false;
}

void AInteractiveObject::FreeSpot(class ASpot* Spot)
{
	if (SpotsStateMap.Num() <= 0 || !Spot)
		return;
//
	UE_LOG(LogTemp, Warning, L"Map L %d, key %s value %d ", SpotsStateMap.Num(), *Spot->GetName(), SpotsStateMap[Spot])
	SpotsStateMap.Add(Spot, false);
	InteractingAICounter--;
	UE_LOG(LogTemp, Warning, L"Map L %d, key %s value %d ", SpotsStateMap.Num(), *Spot->GetName(), SpotsStateMap[Spot])
	ChangeObjectFull(false);
}

void AInteractiveObject::ChangeObjectFull(bool bNewFull)
{
	if (bFullObject == bNewFull)
		return;

	bFullObject = bNewFull;
	if (CachedRoom)
		CachedRoom->ChangeOccupiedInteractiveObjects(bFullObject? 1 : -1);

}

void AInteractiveObject::FreeWholeInterObject()
{
	if (SpotsStateMap.Num() <= 0)
		return;
	for (const TPair<class ASpot*, bool>& Elem : SpotsStateMap)
	{
		if (Elem.Value == true && Elem.Key)
		{
			UE_LOG(LogTemp, Warning, L"Map L %d, key %s value %d ", SpotsStateMap.Num(), *Elem.Key->GetName(), Elem.Value)
			SpotsStateMap.Add(Elem.Key, false);
			UE_LOG(LogTemp, Warning, L"Map L %d, key %s value %d ", SpotsStateMap.Num(), *Elem.Key->GetName(), Elem.Value)
		}
	}
	bFullObject = false;
	InteractingAICounter = 0;
}

ASpot* AInteractiveObject::FindAvailableSpot()
{
	if (SpotsStateMap.Num() <= 0)
		return nullptr;
	for (const TPair<class ASpot*, bool>& Elem : SpotsStateMap)
	{
		if (Elem.Value == false && Elem.Key != nullptr)
		{
			UE_LOG(LogTemp, Error, L"Map L %d, key %s value %d ", SpotsStateMap.Num(), *Elem.Key->GetName(), Elem.Value )
			SpotsStateMap.Add(Elem.Key, true);
			InteractingAICounter++;
			if (InteractingAICounter >= StaringSpotsNumber)
				ChangeObjectFull(true);
			UE_LOG(LogTemp, Error, L"Map L %d, key %s value %d ", SpotsStateMap.Num(), *Elem.Key->GetName(), Elem.Value)
			return Elem.Key;
		}
	}
	return nullptr;
}


void AInteractiveObject::InitSpotsStateMap(const TArray<ASpot*>& StartingSpots)
{
	SpotsStateMap.Empty(StartingSpots.Num()-1);
	for (ASpot* Spot: StartingSpots)
{
	if (Spot != nullptr)
	{
		SpotsStateMap.Add(Spot,false);

	}
}
StaringSpotsNumber = SpotsStateMap.Num();

UE_LOG(LogTemp, Error, L"StaringSpotsNumber %d,  ", StaringSpotsNumber)
}

UActivity* AInteractiveObject::FindActivity(int32 AICharType)
{
	if (Activities.Num() <= 0)
		return nullptr;
	TArray<UActivity*> PossibleChoices;

	for (UActivity* activity : Activities)
	{
		if(!activity || activity->ActivityStruct.ActivityType == AICharType || activity->ActivityStruct.ActivityType == 0 || AICharType==0 )
		PossibleChoices.AddUnique(activity);
	}

	if(PossibleChoices.Num() > 0)
	{
		UActivity* PotentialActivity = nullptr; 
		while(!PotentialActivity)
		{
			PotentialActivity = PossibleChoices[FMath::RandRange(0, PossibleChoices.Num() - 1)];
		}
		return  PotentialActivity;
	}

	return nullptr;
}

