// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "MyProject.h"
#include "MyProjectGameMode.h"
#include "MyProjectCharacter.h"
#include "Information.h"

AMyProjectGameMode::AMyProjectGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	/*
	static ConstructorHelpers::FClassFinder<APlayerController> MyController(TEXT("/Script/MyPlayerController"));
	if (MyController.Class != NULL)
	{
		PlayerControllerClass = MyController.Class;
	}
	*/

	HUDClass = AInformation::StaticClass();
}
