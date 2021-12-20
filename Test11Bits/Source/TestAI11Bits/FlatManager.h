// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FlatManager.generated.h"

class ARoom;
UCLASS()
class TESTAI11BITS_API AFlatManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFlatManager();

	TArray<class ATargetPoint*> GetSpawnPoints() const { return SpawnPoints; }

	UFUNCTION()
	void FreeWholeFlat();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = Components)
	class UBoxComponent* BoxCollision;

	UPROPERTY(EditAnywhere, Category = "Default")
	TArray<class ARoom*> AllRooms;

	UPROPERTY(EditAnywhere, Category = "Default")
	class ARoom* SleepRoom;

	UPROPERTY(EditAnywhere, Category = "Default")
	TArray<class ATargetPoint*> SpawnPoints;

	UFUNCTION(BlueprintCallable)
	class ARoom* FindRoom (bool bRandom = true, bool bSleepTime = false);

	UPROPERTY()
	class ATestPlayerController* PlayerCtrl;
};

