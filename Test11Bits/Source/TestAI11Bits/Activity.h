// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Activity.generated.h"

UENUM(BlueprintType)
enum class EActivityNames : uint8
{
	None,
	Sleep UMETA(DisplayName = "Sleep"),
	Read UMETA(DisplayName = "Book reading"),
	Drink UMETA(DisplayName = "DrinkCofee"),
	Seat UMETA(DisplayName = "Seat"),
	Conversation UMETA(DisplayName = "Conversation"),
	PlayPP UMETA(DisplayName = "Play Ping-Pong"),
	Console_Lonely UMETA(DisplayName = "A lonely goame on the console"),
	Console_Group UMETA(DisplayName = "Group game on the console"),
};

USTRUCT(BlueprintType)
struct FActivityS
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EActivityNames ActivityName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ActivityType = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MinNumberOfCharsNeeded = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxNumberOfCharsInvolved = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TimeNeeded = 0.;
};

UCLASS(Blueprintable, DefaultToInstanced, EditInlineNew)
class TESTAI11BITS_API UActivity : public UObject
{
	GENERATED_BODY()

public:	
	UActivity();
	UPROPERTY(EditAnywhere)
	FActivityS ActivityStruct;
};
