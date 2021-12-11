// Fill out your copyright notice in the Description page of Project Settings.


#include "TestAIController.h"

#include "AICharacter.h"
#include "FlatManager.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

ATestAIController::ATestAIController(const FObjectInitializer& ObjectInitializer)
{
	CurrentFlat = nullptr;
	bSleepingTime = false;
	AIBehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));
	AIBlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackBoardComp"));
}

void ATestAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	AAICharacter* AIChar = Cast<AAICharacter>(InPawn);

	if (!AIBehaviorTreeComponent || !AIBlackboardComponent || !AIBehaviorTree)
		return;
	
	AIBlackboardComponent->InitializeBlackboard(*AIBehaviorTree->BlackboardAsset);
	AIBehaviorTreeComponent->StartTree(*AIBehaviorTree);
	


	//PlayerState
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(),  AFlatManager::StaticClass(), FoundActors);
	if (FoundActors[0])
		CurrentFlat = Cast< AFlatManager>(FoundActors[0]);

	AIBlackboardComponent->ClearValue("CurrFlat");

	if(CurrentFlat)
		AIBlackboardComponent->SetValueAsObject("CurrFlat", CurrentFlat);

}

void ATestAIController::SetSleepingTime(bool bNewSleepingTime)
{
	bSleepingTime = bNewSleepingTime;
	 if(AIBlackboardComponent)
	AIBlackboardComponent->ClearValue("bSleepTime");
	AIBlackboardComponent->SetValueAsBool("bSleepTime", bSleepingTime);
}
