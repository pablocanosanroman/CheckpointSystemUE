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
	
	m_CurrentCheckpoint = checkpointCollided;
	m_ControllerInstigator = pawnInstigator->Controller;
	

	if(!m_bAntiCheatLinearGames)
	{
		if(!m_bInteractableCheckpoints)
		{
			CheckpointActivation();

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
			
		}
		
	}
	else
	{
		if(!m_bInteractableCheckpoints)
		{
			if(!m_CheckpointLookUp.Contains(m_ControllerInstigator))
			{
				if(m_CurrentCheckpoint == m_Checkpoints[0])
				{
					CheckpointActivation();
				}
			}
			else
			{
				for(ACheckpoint* checkpoint : m_Checkpoints)
				{
					if(m_CurrentCheckpoint == m_NextCheckpoint)
					{
						CheckpointActivation();

						if(checkpoint != m_CurrentCheckpoint && m_bParticleSystemCheck)
						{
							checkpoint->m_CheckpointActivationCheck->SetTemplate(nullptr);
			
						}
					}

					if(m_Checkpoints.Find(m_CurrentCheckpoint) < m_Checkpoints.Find(m_NextCheckpoint) && m_Checkpoints.Find(m_CurrentCheckpoint) > m_Checkpoints.Find(m_Checkpoints[0]))
					{
						CheckpointActivation();

						if(checkpoint != m_CurrentCheckpoint && m_bParticleSystemCheck)
						{
							checkpoint->m_CheckpointActivationCheck->SetTemplate(nullptr);
		
						}
					}

					if(m_CurrentCheckpoint == m_Checkpoints[0])
					{
						CheckpointActivation();

						if(checkpoint != m_CurrentCheckpoint && m_bParticleSystemCheck)
						{
							checkpoint->m_CheckpointActivationCheck->SetTemplate(nullptr);
		
						}
					}
				
				}
			
			}
		}
		else
		{
			
		}
		
		
	}
	
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

void ACheckpointManager::CheckpointActivation()
{
	if(m_CurrentCheckpoint->m_CheckpointActivationCheck->Template != m_CurrentCheckpoint->m_ParticleSytemToSet
								&& m_bParticleSystemCheck)
	{
		if(m_CurrentCheckpoint != m_Checkpoints[m_Checkpoints.Num() - 1])
		{
			if(!m_CurrentCheckpoint->m_bHasCheckpointBeenActivated)
			{
				m_NextCheckpoint = m_Checkpoints[m_Checkpoints.Find(m_CurrentCheckpoint) + 1];
			
			}
		}
		m_CurrentCheckpoint->m_bHasCheckpointBeenActivated = true;
		m_CurrentCheckpoint->m_CheckpointActivationCheck->SetTemplate(m_CurrentCheckpoint->m_ParticleSytemToSet);
		UpdateCheckpointLookUp();
		
		
	}
	else if(!m_bParticleSystemCheck)
	{
		if(m_CurrentCheckpoint != m_Checkpoints[m_Checkpoints.Num() - 1])
		{
			if(!m_CurrentCheckpoint->m_bHasCheckpointBeenActivated)
			{
				m_NextCheckpoint = m_Checkpoints[m_Checkpoints.Find(m_CurrentCheckpoint) + 1];
			
			}
		}
		m_CurrentCheckpoint->m_bHasCheckpointBeenActivated = true;
		
		UpdateCheckpointLookUp();
		
	}
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


