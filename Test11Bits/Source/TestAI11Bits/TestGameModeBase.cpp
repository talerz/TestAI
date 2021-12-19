// Copyright Epic Games, Inc. All Rights Reserved.


#include "TestGameModeBase.h"

#include "FlatManager.h"
#include "TestPlayerController.h"

ATestGameModeBase::ATestGameModeBase()
{
	PlayerControllerClass = ATestPlayerController::StaticClass();
	CurrentFlat = nullptr;
	DayDurationSeconds = 40;
	NightDurationSeconds = 20;
	RemainingTime = DayDurationSeconds;
	bDay = true;
	SpawnedAIType0Counter = 0;
	SpawnedAIType1Counter = 0;
	SpawnedAIType2Counter = 0;
}

void ATestGameModeBase::PreInitializeComponents()
{
	Super::PreInitializeComponents();

	GetWorldTimerManager().SetTimer(TimerHandle_Day, this, &ATestGameModeBase::DefaultTimer, GetWorldSettings()->GetEffectiveTimeDilation(), true);
}

void ATestGameModeBase::DefaultTimer()
{
	RemainingTime--;
	if (RemainingTime <= 0)
		ChangeDayNight(bDay);
}

void ATestGameModeBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	GetWorldTimerManager().ClearTimer(TimerHandle_Day);
	Super::EndPlay(EndPlayReason);
}

void ATestGameModeBase::IncreaseSpawnedAICounter(const int32 PersonalityType)
{
	switch(PersonalityType)
	{
	case 0:
		SpawnedAIType0Counter++;
		break;
	case 1:
		SpawnedAIType1Counter++;
		break;
	case 2:
		SpawnedAIType2Counter++;
		break;
	default:
		break;
	}

}

void ATestGameModeBase::ChangeDayNight(bool bJustFinishedDay)
{
	bDay = !bJustFinishedDay;
	RemainingTime = bDay? DayDurationSeconds: NightDurationSeconds;
	OnDayNightChanged.Broadcast(bDay);

	if (CurrentFlat)
		CurrentFlat->FreeWholeFlat();
}
