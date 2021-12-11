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
	UPROPERTY(EditAnywhere)
	TArray<class ATargetPoint*> StaringSpots;
	UPROPERTY()
	TMap<class ATargetPoint*, bool> SpotsOccupation;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	bool CheckIfSomeoneUses() const { return InteractingAICounter>0; }
	bool IsSpotAvaliable() const;
	//CHECK AVAILABLE ACTIVITIES
private:
	int32 InteractingAICounter;

};
