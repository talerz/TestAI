// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TestPlayerController.generated.h"

/**
 * 
 */
DECLARE_DELEGATE_OneParam(FSpawnAIDelegate, const int32);

UCLASS()
class TEST_API ATestPlayerController : public APlayerController
{
	GENERATED_BODY()
	ATestPlayerController();

public:
	virtual void SetupInputComponent() override;
	UFUNCTION()
	void OnSpawnAICharacter(const int32 PersonalityType);

	void SetSpawnPoints(class AFlatManager* CurrFlatManager);

protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AAICharacter> SpawnAI_BPClass;
	UPROPERTY()
	TArray<class ATargetPoint*> SpawnPoints;
private:
	FTransform SpawnTransform;
};
