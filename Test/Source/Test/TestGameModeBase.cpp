// Copyright Epic Games, Inc. All Rights Reserved.


#include "TestGameModeBase.h"

#include "TestPlayerController.h"

ATestGameModeBase::ATestGameModeBase()
{
	PlayerControllerClass = ATestPlayerController::StaticClass();
}
