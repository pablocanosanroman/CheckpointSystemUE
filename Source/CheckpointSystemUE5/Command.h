// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Checkpoint.h"
#include "GameFramework/Actor.h"
#include "Command.generated.h"

UCLASS(Abstract)
class CHECKPOINTSYSTEMUE5_API ACommand : public AActor
{
	GENERATED_BODY()
	
public:
	UFUNCTION()
	virtual void Execute(AActor* actorToExecute, ACheckpoint* checkpointToReference);

};
