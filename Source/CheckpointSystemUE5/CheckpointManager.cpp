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
	/*else if(m_bAntiCheatLinearGames && m_Checkpoints.Num() != 0)
	{
		m_Checkpoints[0]->m_CheckpointCollider->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	}*/

	for(ACheckpoint* col : m_Checkpoints)
	{
		col->onCheckpointActivated.AddDynamic(this, &ACheckpointManager::CheckpointActivated);

		/*if(!m_bAntiCheatLinearGames)
		{
			col->m_CheckpointCollider->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
		}*/
	}
	
	Super::BeginPlay();
	
}

void ACheckpointManager::CheckpointActivated_Implementation(ACheckpoint* checkpointCollided, APawn* pawnInstigator)
{
	m_ControllerInstigator = pawnInstigator->Controller;
	m_CurrentCheckpoint = checkpointCollided;

	if(!m_bAntiCheatLinearGames)
	{
		if(m_CurrentCheckpoint->m_CheckpointActivationCheck->Template != m_CurrentCheckpoint->m_ParticleSytemToSet && m_bParticleSystemCheck)
		{
			m_CurrentCheckpoint->m_CheckpointActivationCheck->SetTemplate(m_CurrentCheckpoint->m_ParticleSytemToSet);
			UpdateCheckpointLookUp();
		}

		for(ACheckpoint* checkpoint : m_Checkpoints)
		{
			if(checkpoint != m_CurrentCheckpoint && m_bParticleSystemCheck)
			{
				checkpoint->m_CheckpointActivationCheck->SetTemplate(nullptr);
			
			}
		}
	}
	else
	{
		for(ACheckpoint* checkpoint : m_Checkpoints)
		{
			if(m_Checkpoints.Find(m_CurrentCheckpoint) > m_Checkpoints.Find(checkpoint))
			{
				if(m_CurrentCheckpoint->m_CheckpointActivationCheck->Template != m_CurrentCheckpoint->m_ParticleSytemToSet && m_bParticleSystemCheck)
				{
					m_CurrentCheckpoint->m_CheckpointActivationCheck->SetTemplate(m_CurrentCheckpoint->m_ParticleSytemToSet);
					UpdateCheckpointLookUp();
				}
				else if(!m_bParticleSystemCheck)
				{
					UpdateCheckpointLookUp();
				}
			}
			
			if(m_CurrentCheckpoint != m_Checkpoints[m_Checkpoints.Num() - 1])
			{
				
				if(m_Checkpoints.Find(m_CurrentCheckpoint) > m_Checkpoints.Find(checkpoint))
				{
					if(m_Checkpoints.Find(checkpoint) == m_Checkpoints.Find(m_CurrentCheckpoint + 1))
					{
						if(m_CurrentCheckpoint->m_CheckpointActivationCheck->Template != m_CurrentCheckpoint->m_ParticleSytemToSet && m_bParticleSystemCheck)
						{
							m_CurrentCheckpoint->m_CheckpointActivationCheck->SetTemplate(m_CurrentCheckpoint->m_ParticleSytemToSet);
							UpdateCheckpointLookUp();
						}
						else if(!m_bParticleSystemCheck)
						{
							UpdateCheckpointLookUp();
						}
					}
				}
			}
		}
	}
	
	//This code sets the particle system to the one desired to check if the checkpoint has been activated
	/*if(m_CurrentCheckpoint->m_CheckpointActivationCheck->Template != m_CurrentCheckpoint->m_ParticleSytemToSet && m_bParticleSystemCheck)
	{
		m_CurrentCheckpoint->m_CheckpointActivationCheck->SetTemplate(m_CurrentCheckpoint->m_ParticleSytemToSet);
		UpdateCheckpointLookUp();
	}*/

	//This code is for the control of what the checkpoints that are not being collided should do when a checkpoint is activated
	/*for(ACheckpoint* checkpoint : m_Checkpoints)
	{
		//In case that the designer doesnt want the anti-cheat mode for linear games
		if(checkpoint != m_CurrentCheckpoint && !m_bAntiCheatLinearGames && m_bParticleSystemCheck)
		{
			checkpoint->m_CheckpointActivationCheck->SetTemplate(nullptr);
			
		}

		if(checkpoint != m_CurrentCheckpoint && m_bAntiCheatLinearGames) //In case that the designer wants the anti-chat mode for linear games activated
		{
			for(int i = 0 ; i < m_Checkpoints.Find(checkpointCollided); i++)
			{
				if(m_Checkpoints[i]->m_CheckpointCollider != nullptr)
				{
					m_Checkpoints[i]->m_CheckpointCollider->DestroyComponent();
				}
			}

			//TODO: Go through all the invalid checkpoints calls, put the lines in a separate function, if whatever invalid call go through, dont do anything 
			if(m_CurrentCheckpoint != m_Checkpoints[m_Checkpoints.Num() - 1])
			{
				if(m_Checkpoints.Find(checkpoint) < m_Checkpoints.Find(m_CurrentCheckpoint))
				{
					UpdateCheckpointLookUp();
				}
				//m_Checkpoints[m_Checkpoints.Find(checkpointCollided) + 1]->m_CheckpointCollider->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
				
			}
			
		}
	}*/
	
}

//This lines of code are for updating the checkpoint that a specific controller is looking, to then set the player start on that checkpoint (Up to the designer)

void ACheckpointManager::UpdateCheckpointLookUp()
{
	if(!m_CheckpointLookUp.Contains(m_ControllerInstigator))
	{
		m_CheckpointLookUp.Add(m_ControllerInstigator, NULL);
	}
	m_CheckpointLookUp[m_ControllerInstigator] = m_Checkpoints.Find(m_CurrentCheckpoint);
}

//Sets where a player needs to start when it dies
FTransform ACheckpointManager::FindPlayerStart(AController* player)
{
	if(m_CheckpointLookUp.Contains(player))
	{
		return m_Checkpoints[m_CheckpointLookUp[player]]->GetTransform();
	}
	return m_Checkpoints[0]->GetTransform();;
}

