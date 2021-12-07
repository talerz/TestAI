// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Activity.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TEST_API UActivity : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UActivity();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
		float TimeNeeded;
	UPROPERTY(EditAnywhere)
		uint8 ActivityType;


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	//TODO: RETHINK 
	virtual void PerformActivity() {}

	uint8 CheckActivityType() const { return ActivityType; }
	float CheckTimeNeeded() const { return  TimeNeeded;  }


};
