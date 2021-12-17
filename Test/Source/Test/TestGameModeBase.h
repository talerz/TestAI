// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TestGameModeBase.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDayNightChanged, bool, bDay);
UCLASS()
class TEST_API ATestGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	ATestGameModeBase();
public:
	virtual void PreInitializeComponents() override;
	virtual void DefaultTimer();

	UPROPERTY(Transient)
	int32 RemainingTime;
	UPROPERTY(Transient)
	bool bDay;
	UPROPERTY(BlueprintAssignable)
	FDayNightChanged OnDayNightChanged;
protected:
	FTimerHandle TimerHandle_Day;
	UPROPERTY(EditDefaultsOnly)
	int32 DayDurationSeconds;
	UPROPERTY(EditDefaultsOnly)
	int32 NightDurationSeconds;
	void ChangeDayNight(bool bJustFinishedDay);

};
