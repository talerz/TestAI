// Copyright Epic Games, Inc. All Rights Reserved.


#include "TestGameModeBase.h"

#include "TestPlayerController.h"

ATestGameModeBase::ATestGameModeBase()
{
	PlayerControllerClass = ATestPlayerController::StaticClass();
	DayDurationSeconds = 40;
	NightDurationSeconds = 20;
	RemainingTime = DayDurationSeconds;
	bDay = true;
}

void ATestGameModeBase::PreInitializeComponents()
{
	Super::PreInitializeComponents();

	GetWorldTimerManager().SetTimer(TimerHandle_Day, this, &ATestGameModeBase::DefaultTimer, GetWorldSettings()->GetEffectiveTimeDilation(), true);
}

void ATestGameModeBase::DefaultTimer()
{
	RemainingTime--;
	UE_LOG(LogTemp, Error, L"TIME: %d", RemainingTime)
	if (RemainingTime <= 0)
		ChangeDayNight(bDay);
}

void ATestGameModeBase::ChangeDayNight(bool bJustFinishedDay)
{
	bDay = !bJustFinishedDay;
	RemainingTime = bDay? DayDurationSeconds: NightDurationSeconds;
	OnDayNightChanged.Broadcast(bDay);
}
