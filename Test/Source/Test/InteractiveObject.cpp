// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractiveObject.h"

#include "Activity.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
AInteractiveObject::AInteractiveObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>("Box");
	BoxCollision->SetupAttachment(RootComponent);

	InteractingAICounter = 0;
	bFullObject = false;

}

// Called when the game starts or when spawned
void AInteractiveObject::BeginPlay()
{
	Super::BeginPlay();

	for (auto Component : GetComponents())
	{
		if (Component && Cast<class UArrowComponent>(Component))
			StartingSpots.AddUnique(Cast<class UArrowComponent>(Component));
	}
	StaringSpotsNumber = StartingSpots.Num();

	for (class UArrowComponent* Spot : StartingSpots)
	{
		if(Spot)
		SpotsOccupation.Add(Spot,false);
	}
}

// Called every frame
void AInteractiveObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


bool AInteractiveObject::IsAnySpotAvailable()
{
	if(SpotsOccupation.Num() <= 0)
		return false;
	for (auto Elem : SpotsOccupation)
	{
		if (Elem.Value == false)
			return true;
	}
	bFullObject = true;
	return false;
}

void AInteractiveObject::FreeSpot(class UArrowComponent* Spot)
{
	if (SpotsOccupation.Num() <= 0 || !Spot)
		return;
	SpotsOccupation.Add(Spot, false);
	bFullObject = false;
}

UArrowComponent* AInteractiveObject::FindAvailableSpot()
{
	if (SpotsOccupation.Num() <= 0)
		return nullptr;
	for (auto Elem : SpotsOccupation)
	{
		if (Elem.Value == false && Elem.Key)
		{
			SpotsOccupation.Add(Elem.Key, true);
			return Elem.Key;
		}
	}
	return nullptr;
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
		UActivity* PotentailActivity = nullptr; 
		while(!PotentailActivity)
			PotentailActivity = PossibleChoices[FMath::RandRange(0, PossibleChoices.Num() - 1)];
		return  PotentailActivity;
	}

	return nullptr;
}

