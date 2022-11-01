// Copyright Epic Games, Inc. All Rights Reserved.

#include "CheckpointSystemUE5GameMode.h"
#include "CheckpointSystemUE5Character.h"
#include "UObject/ConstructorHelpers.h"

ACheckpointSystemUE5GameMode::ACheckpointSystemUE5GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
