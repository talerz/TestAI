// Fill out your copyright notice in the Description page of Project Settings.


#include "TestPlayerController.h"

#include "AICharacter.h"
#include "FlatManager.h"
#include "Engine/TargetPoint.h"

ATestPlayerController::ATestPlayerController()
{
}

void ATestPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	check(InputComponent);

	InputComponent->BindAction<FSpawnAIDelegate>("SpawnAIType0", IE_Pressed, this, &ATestPlayerController::OnSpawnAICharacter, 0);
	InputComponent->BindAction<FSpawnAIDelegate>("SpawnAIType1", IE_Pressed, this, &ATestPlayerController::OnSpawnAICharacter, 1);
	InputComponent->BindAction<FSpawnAIDelegate>("SpawnAIType2", IE_Pressed, this, &ATestPlayerController::OnSpawnAICharacter, 2);
}

void ATestPlayerController::OnSpawnAICharacter(const int32 PersonalityType)
{
	if(!GetWorld() || !GetPawn())
		return;
	if (SpawnPoints.Num() <= 0)
		SpawnTransform = GetPawn()->GetTransform();
	
	if (SpawnPoints.Num() > 0 && !SpawnPoints[PersonalityType])
		SpawnTransform = SpawnPoints.Last()->GetTransform();

	if (SpawnPoints.Num() > 0 && SpawnPoints[PersonalityType])
		SpawnTransform = SpawnPoints[PersonalityType]->GetTransform();
	
	class AAICharacter* NewAI = GetWorld()->SpawnActorDeferred<AAICharacter>(SpawnAI_BPClass, SpawnTransform);
	if(NewAI)
	{
		NewAI->SetupAI(PersonalityType);
		NewAI->FinishSpawning(SpawnTransform);
	}
}

void ATestPlayerController::SetSpawnPoints(AFlatManager* CurrFlatManger)
{
	if (!CurrFlatManger)
		return;
	SpawnPoints = CurrFlatManger->GetSpawnPoints();
}
