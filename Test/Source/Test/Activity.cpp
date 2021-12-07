// Fill out your copyright notice in the Description page of Project Settings.


#include "Activity.h"

// Sets default values for this component's properties
UActivity::UActivity()
{
	TimeNeeded = 0;
	ActivityType = 0;
}


// Called when the game starts
void UActivity::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UActivity::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

