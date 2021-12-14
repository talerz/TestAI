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
	PrimaryActorTick.bCanEverTick = true;
	bBusy = false;
	ActivityTimeNeeded = 0.;
	CurrentActivityTime = 0.;

	PersonalityType = 0;
	CurrentAnim = EActivityNames::None;
	bPlayActivityAnim = false;
	AlterAnim = nullptr;
}

void AAICharacter::SetupAI(int8 SpawnedPersonalityType)
{
	PersonalityType = static_cast<int8>(SpawnedPersonalityType);
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
}

void AAICharacter::FinishActivity()
{
	bBusy = false;
	ActivityTimeNeeded = 0.;
	CurrentActivityTime = 0.;
	PersonalityType = 0;
	CurrentAnim = EActivityNames::None;
	bPlayActivityAnim = false;
	OnActivityFinished.Broadcast();

}

// Called every frame
void AAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CurrentActivityTime += DeltaTime;

	if (CurrentActivityTime >= ActivityTimeNeeded)
		FinishActivity();

	//GetGameInstance();
	//GetWorld()->GetAuthGameMode()
	//	GetWorld()->GetGameState();
}

// Called to bind functionality to input
void AAICharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


