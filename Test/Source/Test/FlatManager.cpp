// Fill out your copyright notice in the Description page of Project Settings.


#include "FlatManager.h"

#include "Room.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AFlatManager::AFlatManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>("Box");
	BoxCollision->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AFlatManager::BeginPlay()
{
	Super::BeginPlay();
}

ARoom* AFlatManager::FindRoom(bool bRandom)
{
	if (AllRooms.Num() <= 0)
		return nullptr;

	return AllRooms[FMath::RandRange(0, AllRooms.Num() - 1)];
}

// Called every frame
void AFlatManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

