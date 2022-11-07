// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Checkpoint.h"
#include "Command.h"
#include "Command_Spawn.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class CHECKPOINTSYSTEMUE5_API ACommand_Spawn : public ACommand
{
	GENERATED_BODY()

public:
	UFUNCTION()
	virtual void Execute(AActor* actorToExecute, ACheckpoint* checkpointToReference) override;
	
};
