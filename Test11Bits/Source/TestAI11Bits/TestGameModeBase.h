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
	void SetCurrentFlat(class AFlatManager* NewFlat) { CurrentFlat = NewFlat; }
	virtual void Reset() override;
	UPROPERTY(Transient, BlueprintReadOnly)
	int32 RemainingTime;
	UPROPERTY(Transient, BlueprintReadOnly)
	bool bDay;
	UPROPERTY(BlueprintAssignable)
	FDayNightChanged OnDayNightChanged;
	void IncreaseSpawnedAICounter(const int32 PersonalityType);
protected:
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
	UPROPERTY()
	class AFlatManager* CurrentFlat;

	UFUNCTION()
	void ChangeDayNight(bool bJustFinishedDay);

};

inline void ATestGameModeBase::Reset()
{
	Super::Reset();
}
