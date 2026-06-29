// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Actors/CheckpointActor.h"

#include "AbilitySystemComponent.h"
#include "GameplayTagContainer.h"
#include "Core/World/CheckpointSubsystem.h"


// Sets default values
ACheckpointActor::ACheckpointActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

bool ACheckpointActor::Interact_Implementation(AActor* InteractingActor)
{
	if (bIsActive)
	{
		//For now just revive enemies
		if (UCheckpointSubsystem* CheckpointSubsystem = GetWorld()->GetSubsystem<UCheckpointSubsystem>())
		{
			CheckpointSubsystem->ResetEnemies();
		}
	}
	else
	{
		bIsActive = true;
	}
	return true;
}

FText ACheckpointActor::GetInteractPromptText_Implementation() const
{
	if (bIsActive)
	{
		return PromptTextWhenActive;
	}
	else
	{
		return PromptTextWhenInactive;
	}
}

