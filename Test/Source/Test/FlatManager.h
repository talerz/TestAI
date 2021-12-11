// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FlatManager.generated.h"

class ARoom;
UCLASS()
class TEST_API AFlatManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFlatManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = Components)
	class UBoxComponent* BoxCollision;

	UPROPERTY(EditAnywhere, Category = "Default")
	TArray<class ARoom*> AllRooms;

	UFUNCTION(BlueprintCallable)
	class ARoom* FindRoom (bool bRandom = true, bool bSleepRoom = false);
	UPROPERTY()
	class ARoom* SleepRoom;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


};

