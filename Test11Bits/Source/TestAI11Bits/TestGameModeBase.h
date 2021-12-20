// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TestGameModeBase.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDayNightChanged, bool, bDay);
UCLASS()
class TESTAI11BITS_API ATestGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	ATestGameModeBase();
public:
	virtual void PreInitializeComponents() override;
	virtual void DefaultTimer();
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UPROPERTY(Transient, BlueprintReadOnly)
	int32 RemainingTime;
	UPROPERTY(Transient, BlueprintReadOnly, meta = (ClampMin = "1", ClampMax = "3"))
	float TimeRate = 1.;
	UPROPERTY(Transient, BlueprintReadOnly)
	bool bDay;
	UPROPERTY(BlueprintAssignable)
	FDayNightChanged OnDayNightChanged;

	void SetCurrentFlat(class AFlatManager* NewFlat) { CurrentFlat = NewFlat; }
	void IncreaseSpawnedAICounter(const int32 PersonalityType);
	bool IsMaxAIOfType(const int32 PersonalityType) const;
	void ChangeTimeRate(float TimeRateChange);
protected:
	UPROPERTY()
	FTimerHandle TimerHandle_Day;
	UPROPERTY(EditDefaultsOnly)
	int32 DayDurationSeconds;
	UPROPERTY(EditDefaultsOnly)
	int32 NightDurationSeconds;
	UPROPERTY(Transient, BlueprintReadOnly)
	int32 SpawnedAIType0Counter;
	UPROPERTY(Transient, BlueprintReadOnly)
	int32 SpawnedAIType1Counter;
	UPROPERTY(Transient, BlueprintReadOnly)
	int32 SpawnedAIType2Counter;
	UPROPERTY(Transient, BlueprintReadOnly)
	int32 MaxAI;
	UPROPERTY()
	class AFlatManager* CurrentFlat;

	UFUNCTION()
	void ChangeDayNight(bool bJustFinishedDay);

};

