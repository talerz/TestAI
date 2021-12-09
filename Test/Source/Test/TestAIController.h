// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TestAIController.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = AI, BlueprintType, Blueprintable)
class TEST_API ATestAIController : public AAIController
{
	GENERATED_BODY()
public:
	ATestAIController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void OnPossess(APawn* InPawn) override;

protected:

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	class UBehaviorTree* AIBehaviorTree;

	UPROPERTY()
	class AFlatManager* CurrentFlat;

	UFUNCTION(BlueprintCallable)
	class AFlatManager* GetCurrentFlat() const { return CurrentFlat; }

public:
	UPROPERTY(EditAnywhere, Category = Behavior)
	class UBehaviorTreeComponent* AIBehaviorTreeComponent;
	UPROPERTY(EditAnywhere, Category = Behavior)
	class UBlackboardComponent* AIBlackboardComponent;
};
