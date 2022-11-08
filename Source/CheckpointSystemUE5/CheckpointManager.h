// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Checkpoint.h"
#include "GameFramework/Actor.h"
#include "CheckpointManager.generated.h"

class ACheckpoint;

UCLASS()
class CHECKPOINTSYSTEMUE5_API ACheckpointManager : public AActor
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<ACheckpoint*> m_Checkpoints;

	TMap<AController*, int> m_CheckpointLookUp;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool m_bAntiCheatLinearGames;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool m_bParticleSystemCheck;
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void CheckpointActivated(ACheckpoint* checkpointCollided, APawn* pawnInstigator);
	virtual void CheckpointActivated_Implementation(ACheckpoint* checkpointCollided, APawn* pawnInstigator);
public:
	UFUNCTION()
	FTransform FindPlayerStart(AController* player); 
};
