// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractiveObject.generated.h"



UCLASS()
class TEST_API AInteractiveObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractiveObject();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = Components)
	class UBoxComponent* BoxCollision;
	UPROPERTY(EditAnywhere, Instanced)
	TArray<class UActivity*> Activities;
	UPROPERTY()
	int32 StaringSpotsNumber;
	UPROPERTY(BlueprintReadWrite)
	TArray<class UArrowComponent*> StartingSpots;

	//true = occupied, false = free
	UPROPERTY()
	TMap<class UArrowComponent*, bool> SpotsOccupation;

	UFUNCTION(BlueprintCallable)
	class UActivity* FindActivity(int32 AICharType);
	UFUNCTION(BlueprintCallable)
	bool IsObjectFull() const { return bFullObject; }
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	bool CheckIfSomeoneUses() const { return InteractingAICounter > 0; }
	bool IsAnySpotAvailable();
	UFUNCTION(BlueprintCallable)
	void FreeSpot(class UArrowComponent* Spot);
	UFUNCTION(BlueprintCallable)
	class UArrowComponent* FindAvailableSpot();
	bool CheckIfObjectFull()const { return bFullObject; }
	//CHECK AVAILABLE ACTIVITIES
private:
	int32 InteractingAICounter;
	bool bFullObject;

};
