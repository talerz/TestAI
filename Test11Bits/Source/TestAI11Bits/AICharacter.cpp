// Fill out your copyright notice in the Description page of Project Settings.


#include "AICharacter.h"

#include "Activity.h"
#include "FlatManager.h"
#include "TestAIController.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AAICharacter::AAICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	bBusy = false;
	bActivityStarted = false;
	ActivityTimeNeeded = 0.;
	CurrentActivityTime = 0.;

	PersonalityType = 0;
	CurrentAnim = EActivityNames::None;
	bPlayActivityAnim = false;
	AlterAnim = nullptr;
}

void AAICharacter::SetupAI(int32 SpawnedPersonalityType)
{
	PersonalityType = SpawnedPersonalityType;
}


// Called when the game starts or when spawned
void AAICharacter::BeginPlay()
{
	Super::BeginPlay();

}

void AAICharacter::StartActivity(UActivity* NewActivity)
{
	if(!NewActivity)
		return;
	CurrentAnim = NewActivity->ActivityStruct.ActivityName;
	bPlayActivityAnim = true;
	CurrentActivityTime = 0.;
	ActivityTimeNeeded = NewActivity->ActivityStruct.TimeNeeded;
	
	bBusy = true;
	PrimaryActorTick.bCanEverTick = true;
	bActivityStarted = true;
}

void AAICharacter::FinishActivity()
{
	bActivityStarted = false;
	PrimaryActorTick.bCanEverTick = false;
	bBusy = false;
	ActivityTimeNeeded = 0.;
	CurrentActivityTime = 0.;
	CurrentAnim = EActivityNames::None;
	bPlayActivityAnim = false;
	OnActivityFinished.Broadcast();
}

// Called every frame
void AAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bActivityStarted)
	{
		CurrentActivityTime += DeltaTime;

		if (CurrentActivityTime >= ActivityTimeNeeded)
			FinishActivity();
	}
}



