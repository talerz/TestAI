// Fill out your copyright notice in the Description page of Project Settings.


#include "FlatManager.h"

#include "Room.h"
#include "TestGameModeBase.h"
#include "TestPlayerController.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AFlatManager::AFlatManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>("Box");
	BoxCollision->SetupAttachment(RootComponent);

	SleepRoom = nullptr;
	PlayerCtrl = nullptr;
}

// Called when the game starts or when spawned
void AFlatManager::BeginPlay()
{
	Super::BeginPlay();
	if (!GetWorld()->GetFirstPlayerController())
		return;
	
	PlayerCtrl = Cast<ATestPlayerController>(GetWorld()->GetFirstPlayerController());
	if (PlayerCtrl)
		PlayerCtrl->SetSpawnPoints(this);

	ATestGameModeBase* GameMode = Cast<ATestGameModeBase>(GetWorld()->GetAuthGameMode());
	if (GameMode)
		GameMode->SetCurrentFlat(this);

}

ARoom* AFlatManager::FindRoom(bool bRandom, bool bSleepTime)
{
	if (AllRooms.Num() <= 0)
		return nullptr;

	if(bSleepTime && SleepRoom)
		return  SleepRoom;

	return AllRooms[FMath::RandRange(0, AllRooms.Num() - 1)];
}

void AFlatManager::FreeWholeFlat()
{
	if (AllRooms.Num() <= 0)
		return;
	
	for (ARoom* Room : AllRooms)
	{
		if (Room)
			Room->FreeWholeRoom();
	}
	if(SleepRoom)
		SleepRoom->FreeWholeRoom();
}

