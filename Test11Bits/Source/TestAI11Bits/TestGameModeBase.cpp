// Copyright Epic Games, Inc. All Rights Reserved.


#include "TestGameModeBase.h"

#include "FlatManager.h"
#include "TestPlayerController.h"
#include "Kismet/GameplayStatics.h"

ATestGameModeBase::ATestGameModeBase()
{
	PlayerControllerClass = ATestPlayerController::StaticClass();
	CurrentFlat = nullptr;
	DayDurationSeconds = 240;
	NightDurationSeconds = 120;
	MaxAI = 20;
	RemainingTime = DayDurationSeconds;
	bDay = true;
	SpawnedAIType0Counter = 0;
	SpawnedAIType1Counter = 0;
	SpawnedAIType2Counter = 0;
	TimeRate = 1;
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
void ATestGameModeBase::ChangeTimeRate(float TimeRateChange)
{
	TimeRate = FMath::Clamp((TimeRate + TimeRateChange), 0.5f, 2.f);
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), TimeRate);
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

bool ATestGameModeBase::IsMaxAIOfType(const int32 PersonalityType) const
{
	switch (PersonalityType)
	{
	case 0:
		return SpawnedAIType0Counter >= MaxAI;
	case 1:
		return SpawnedAIType1Counter >= MaxAI;
	case 2:
		return SpawnedAIType2Counter >= MaxAI;
	default:
		return false;
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
