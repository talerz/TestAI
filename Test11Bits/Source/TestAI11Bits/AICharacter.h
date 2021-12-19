// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AICharacter.generated.h"
enum class EActivityNames : uint8;
struct FActivityS;
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FActivityFinished);
UCLASS()
class TESTAI11BITS_API AAICharacter : public ACharacter
{
	GENERATED_BODY()
public:
	// Sets default values for this character's properties
	AAICharacter();
	void SetupAI(int32 SpawnedPersonalityType);
	UPROPERTY(BlueprintAssignable)
	FActivityFinished OnActivityFinished;

	UFUNCTION(BlueprintCallable)
	void FinishActivity();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced)
	TArray<class UActivity*> Activities;
	UPROPERTY(BlueprintReadOnly)
	int32 PersonalityType;
	UPROPERTY(BlueprintReadWrite)
	EActivityNames CurrentAnim;
	UPROPERTY(BlueprintReadWrite)
	class UAnimSequence* AlterAnim;
	UPROPERTY(BlueprintReadWrite)
	bool bPlayActivityAnim;
	UFUNCTION(BlueprintCallable)
	void StartActivity(class UActivity* NewActivity);

	UFUNCTION(BlueprintCallable)
	bool IsBusy() const { return  bBusy; }
	UFUNCTION(BlueprintCallable)
	bool WantToTalkWithSomeone() const { return  bFoundConvPartner; }
	UFUNCTION(BlueprintCallable)
	void SetFoundConvPartner(bool bNewFound) { bFoundConvPartner = bNewFound; }

	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	bool bBusy;
	bool bFoundConvPartner;
	float ActivityTimeNeeded;
	float CurrentActivityTime;

};


