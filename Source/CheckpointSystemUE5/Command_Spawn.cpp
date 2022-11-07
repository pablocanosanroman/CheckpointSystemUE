// Fill out your copyright notice in the Description page of Project Settings.


#include "Command_Spawn.h"

void ACommand_Spawn::Execute(AActor* actorToExecute, ACheckpoint* checkpointToReference)
{
	actorToExecute->SetActorLocation(FVector(checkpointToReference->m_SpawnPoint->GetComponentLocation().X,
		checkpointToReference->GetActorLocation().Y, actorToExecute->GetActorLocation().Z));
	
	Super::Execute(actorToExecute, checkpointToReference);
}
