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

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool m_bAntiCheatLinearGames;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void CheckpointActivated(ACheckpoint* checkpointCollided, AActor* pawnInstigator);
	virtual void CheckpointActivated_Implementation(ACheckpoint* checkpointCollided, AActor* pawnInstigator);
};
