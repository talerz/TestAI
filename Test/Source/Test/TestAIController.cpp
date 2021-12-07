// Fill out your copyright notice in the Description page of Project Settings.


#include "TestAIController.h"

#include "AICharacter.h"

ATestAIController::ATestAIController(const FObjectInitializer& ObjectInitializer)
{

}

void ATestAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	AAICharacter* AIChar = Cast<AAICharacter>(InPawn);

	if (AIChar && AIChar->AIBehaviorTree)
		RunBehaviorTree(AIChar->AIBehaviorTree);
}
