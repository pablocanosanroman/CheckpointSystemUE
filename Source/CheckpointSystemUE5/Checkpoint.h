// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "GameFramework/Actor.h"
#include "Checkpoint.generated.h"


class USceneComponent;
class UStaticMeshComponent;
class UParticleSystemComponent;
class USphereComponent;
class ACheckpoint;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnCheckpointActivatedSignature,ACheckpoint*, checkpointCollided, APawn*, pawnInstigator);
//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCheckpointDeactivatedSignature, ACheckpoint*, checkpointCollided);

UCLASS()
class CHECKPOINTSYSTEMUE5_API ACheckpoint : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACheckpoint();

	UPROPERTY(BlueprintAssignable, Category = "CheckpointEvents")
	FOnCheckpointActivatedSignature onCheckpointActivated;

	UPROPERTY(BlueprintAssignable, Category = "CheckpointEvents")
	FOnCheckpointActivatedSignature onCheckpointInteracted;

	/*UPROPERTY(BlueprintAssignable, Category= "CheckpoinEvents")
	FOnCheckpointDeactivatedSignature onCheckpointDeactivated;*/

	virtual void BeginPlay() override;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	USceneComponent* m_Root;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UStaticMeshComponent* m_CheckpointMesh;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UParticleSystemComponent* m_CheckpointActivationCheck;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	USphereComponent* m_CheckpointCollider;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UParticleSystem* m_ParticleSytemToSet;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool m_bHasCheckpointBeenActivated;
		
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyindex, bool bFromSweep, const FHitResult& SweepResult);

	virtual void Interact_Implementation(APawn* instigator) override;
	
};
