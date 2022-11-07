// Fill out your copyright notice in the Description page of Project Settings.


#include "CheckpointManager.h"

#include "EngineUtils.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"

// Called when the game starts or when spawned
void ACheckpointManager::BeginPlay()
{
	if(m_Checkpoints.Num() == 0 && !m_bAntiCheatLinearGames)
	{
		for(TActorIterator<ACheckpoint> It(GetWorld()); It; ++It)
		{
			m_Checkpoints.Add(*It);
		}
	}
	else if(m_bAntiCheatLinearGames && m_Checkpoints.Num() != 0)
	{
		m_Checkpoints[0]->m_CheckpointCollider->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	}

	for(ACheckpoint* col : m_Checkpoints)
	{
		col->onCheckpointActivated.AddDynamic(this, &ACheckpointManager::CheckpointActivated);

		if(!m_bAntiCheatLinearGames)
		{
			col->m_CheckpointCollider->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
		}
	}
	
	Super::BeginPlay();
	
}

void ACheckpointManager::CheckpointActivated_Implementation(ACheckpoint* checkpointCollided, AActor* pawnInstigator)
{
	//This code sets the particle system to the one desired to check if the checkpoint has been activated
	if(checkpointCollided->m_CheckpointActivationCheck->Template != checkpointCollided->m_ParticleSytemToSet)
	{
		checkpointCollided->m_CheckpointActivationCheck->SetTemplate(checkpointCollided->m_ParticleSytemToSet);
	}

	//This code is for the control of what the checkpoints that are not being collided should do when a checkpoint is activated
	for(ACheckpoint* col : m_Checkpoints)
	{
		//In case that the designer doesnt want the anti-cheat mode for linear games
		if(col != checkpointCollided && !m_bAntiCheatLinearGames)
		{
			col->m_CheckpointActivationCheck->SetTemplate(nullptr);
		}
		else if(col != checkpointCollided && m_bAntiCheatLinearGames) //In case that the designer wants the anti-chat mode for linear games activated
		{
			for(int i = 0 ; i < m_Checkpoints.Find(checkpointCollided); i++)
			{
				if(m_Checkpoints[i]->m_CheckpointCollider != nullptr)
				{
					m_Checkpoints[i]->m_CheckpointCollider->DestroyComponent();
				}
			}

			if(checkpointCollided != m_Checkpoints[m_Checkpoints.Num() - 1])
			{
				m_Checkpoints[m_Checkpoints.Find(checkpointCollided) + 1]->m_CheckpointCollider->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
			}
			
		}
	}
}

