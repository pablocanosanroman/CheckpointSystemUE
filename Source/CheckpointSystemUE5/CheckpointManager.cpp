// Fill out your copyright notice in the Description page of Project Settings.


#include "CheckpointManager.h"

#include "EngineUtils.h"

// Called when the game starts or when spawned
void ACheckpointManager::BeginPlay()
{
	if(m_Checkpoints.Num() == 0)
	{
		for(TActorIterator<ACheckpoint> It(GetWorld()); It; ++It)
		{
			m_Checkpoints.Add(*It);
		}
	}

	for(ACheckpoint* col : m_Checkpoints)
	{
		col->onCheckpointActivated.AddDynamic(this, &ACheckpointManager::CheckpointActivated);
		
	}
	
	Super::BeginPlay();
	
}

void ACheckpointManager::CheckpointActivated_Implementation(AActor* pawnInstigator)
{
	
}
