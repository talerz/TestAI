// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Room.generated.h"

UCLASS()
class TESTAI11BITS_API ARoom : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARoom();

	//UFUNCTION()
	//void OnBeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	//UFUNCTION()
	//void OnEndOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	bool IsSleepingRoom() const { return bSleepingRoom; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = Components)
	class UBoxComponent* BoxCollision;
	UPROPERTY(EditAnywhere, Category = "Defaults")
	TArray<class ATargetPoint*> Entrances;
	UPROPERTY(EditAnywhere, Category = "Defaults")
	bool bSleepingRoom;
	UPROPERTY(EditAnywhere, Category = "Defaults")
	int32 MaxRoomAI;

	UPROPERTY(EditAnywhere, Category = "Defaults")
	TArray<class AInteractiveObject*> InteractiveObjects;
	UPROPERTY(meta = (ClampMin = "0", ClampMax = "10"))
	int32 OccupiedInteractiveObjects;
	UFUNCTION(BlueprintCallable)
	class AInteractiveObject* FindInteractiveObject();

	UFUNCTION(BlueprintCallable)
	bool IsAnyObjectFree() const;

	UFUNCTION(BlueprintCallable)
		int32 GetOcuppied() const {	return OccupiedInteractiveObjects;	}
public:	
	UFUNCTION()
	void FreeWholeRoom();

	void ChangeOccupiedInteractiveObjects(int32 ChangeValue);
private:

	int32 InteractiveObjectsCounter;
};
