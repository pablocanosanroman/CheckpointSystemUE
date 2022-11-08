// Fill out your copyright notice in the Description page of Project Settings.


#include "Checkpoint.h"

#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
ACheckpoint::ACheckpoint()
{
 	m_Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = m_Root;

	m_CheckpointMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	m_CheckpointMesh->SetupAttachment(m_Root);

	m_CheckpointActivationCheck = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("CheckpointActivationParticle"));
	m_CheckpointActivationCheck->SetupAttachment(m_Root);

	m_CheckpointCollider = CreateDefaultSubobject<USphereComponent>(TEXT("CheckpointCollider"));
	m_CheckpointCollider->SetupAttachment(m_Root);

	

}

void ACheckpoint::BeginPlay()
{
	m_CheckpointCollider->OnComponentBeginOverlap.AddDynamic(this, &ACheckpoint::OnOverlapBegin);
	Super::BeginPlay();
}

void ACheckpoint::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                 UPrimitiveComponent* OtherComp, int32 OtherBodyindex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor->IsA(APawn::StaticClass()) && m_bOverlapAvailable)
	{
		onCheckpointActivated.Broadcast(this, Cast<APawn>(OtherActor));
	}
	
}




