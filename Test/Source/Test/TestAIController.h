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
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UFUNCTION()
	void ChangeSleepingState(bool bDay);

protected:
	UPROPERTY()
		class UBehaviorTreeComponent* AIBehaviorTreeComponent;
	UPROPERTY()
	class UBlackboardComponent* AIBlackboardComponent;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	class UBehaviorTree* AIBehaviorTree;

	UPROPERTY()
	class ATestGameModeBase* CurrentGameMode;
	UPROPERTY()
	class AFlatManager* CurrentFlat;
	UPROPERTY()
	class ARoom* CurrentRoom;
	UPROPERTY()
	class AInteractiveObject* CurrentObject;

	UFUNCTION(BlueprintCallable)
	class AFlatManager* GetCurrentFlat() const { return CurrentFlat; }
	UFUNCTION(BlueprintCallable)
	class ARoom* GetCurrentRoom() const { return CurrentRoom; }
	UFUNCTION(BlueprintCallable)
	class AInteractiveObject* GetCurrentObject() const { return CurrentObject; }

	UFUNCTION(BlueprintCallable)
	void SetCurrentRoom(class ARoom* NewRoom)  {  CurrentRoom = NewRoom; }
	UFUNCTION(BlueprintCallable)
	void SetCurrentObject(class AInteractiveObject* NewInteractiveObj)  {  CurrentObject = NewInteractiveObj; }
};
