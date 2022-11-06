// Fill out your copyright notice in the Description page of Project Settings.


#include "CheckpointManager.h"

#include "EngineUtils.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"

// Called when the game starts or when spawned
void ACheckpointManager::BeginPlay()
{
	if(m_Checkpoints.Num() == 0 && m_bReactivationOfCheckpoints)
	{
		for(TActorIterator<ACheckpoint> It(GetWorld()); It; ++It)
		{
			m_Checkpoints.Add(*It);
		}
	}
	else if(!m_bReactivationOfCheckpoints && m_Checkpoints.Num() != 0)
	{
		m_Checkpoints[0]->m_CheckpointCollider->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	}

	for(ACheckpoint* col : m_Checkpoints)
	{
		col->onCheckpointActivated.AddDynamic(this, &ACheckpointManager::CheckpointActivated);

		if(m_bReactivationOfCheckpoints)
		{
			col->m_CheckpointCollider->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
		}
	}
	
	Super::BeginPlay();
	
}

void ACheckpointManager::CheckpointActivated_Implementation(ACheckpoint* checkpointCollided, AActor* pawnInstigator)
{
	if(checkpointCollided->m_CheckpointActivationCheck->Template != checkpointCollided->m_ParticleSytemToSet)
	{
		checkpointCollided->m_CheckpointActivationCheck->SetTemplate(checkpointCollided->m_ParticleSytemToSet);
	}
	
	for(ACheckpoint* col : m_Checkpoints)
	{
		if(col != checkpointCollided && m_bReactivationOfCheckpoints)
		{
			col->m_CheckpointActivationCheck->SetTemplate(nullptr);
		}
		else if(col != checkpointCollided && !m_bReactivationOfCheckpoints)
		{
			for(int i = 0 ; i < m_Checkpoints.Find(checkpointCollided); i++)
			{
				m_Checkpoints[i]->m_CheckpointCollider->DestroyComponent();
			}

			if(checkpointCollided != m_Checkpoints[m_Checkpoints.Num() - 1])
			{
				m_Checkpoints[m_Checkpoints.Find(checkpointCollided) + 1]->m_CheckpointCollider->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
			}
			
			
			
			//if(m_Checkpoints[m_Checkpoints.Find(checkpointCollided)] > m_Checkpoints[m_Checkpoints.Find(col)])
			//{
			//	m_Checkpoints[m_Checkpoints.Find(col)]->m_CheckpointCollider->DestroyComponent();
			//}
			
		}
	}
}

