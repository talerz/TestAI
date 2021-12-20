// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractiveObject.generated.h"

UCLASS()
class TESTAI11BITS_API AInteractiveObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractiveObject();

protected:
	UPROPERTY(EditAnywhere, Category = Components)
	class UBoxComponent* BoxCollision;
	UPROPERTY(EditAnywhere, Instanced)
	TArray<class UActivity*> Activities;

	UPROPERTY()
	class ARoom* CachedRoom;
	//true = occupied, false = free
	UPROPERTY()
	TMap<class ASpot*, bool> SpotsStateMap;
	UPROPERTY(meta = (ClampMin = "0", ClampMax = "5"))
	int32 InteractingAICounter;

	UFUNCTION(BlueprintCallable)
	void InitSpotsStateMap(const TArray<class ASpot*>& StartingSpots);
	UFUNCTION(BlueprintCallable)
	class UActivity* FindActivity(int32 AICharType);

public:	
	UFUNCTION(BlueprintCallable)
	bool IsAnySpotAvailable();
	UFUNCTION(BlueprintCallable)
	void FreeSpot(class ASpot* Spot);
	UFUNCTION(BlueprintCallable)
	class ASpot* FindAvailableSpot();

	UFUNCTION(BlueprintCallable)
	bool IsObjectFull() const { return bFullObject; }
	void ChangeObjectFull(bool bNewFull);

	void SetRoom(class ARoom* NewRoom) { CachedRoom = NewRoom; }

	UFUNCTION()
	void FreeWholeInterObject();

private:
	int32 StaringSpotsNumber;
	bool bFullObject;

	bool CheckIfSomeoneUses() const { return InteractingAICounter > 0; }
};
