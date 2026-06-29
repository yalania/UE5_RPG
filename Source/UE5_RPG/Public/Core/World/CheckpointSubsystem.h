// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "CheckpointSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class UE5_RPG_API UCheckpointSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
	
public:
	void ResetEnemies();
};
