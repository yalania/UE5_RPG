// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Actors/CheckpointActor.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Characters/PlayerCharacter.h"
#include "Core/World/CheckpointSubsystem.h"
#include "GameplayAbilitySystem/Attributes/BaseAttributeSet.h"


// Sets default values
ACheckpointActor::ACheckpointActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

bool ACheckpointActor::CanInteract(AActor* InteractingActor)
{
	return bCanIntearct;
}

void ACheckpointActor::SetCanInteract(bool newValue)
{
	bCanIntearct = newValue;
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
		
		APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(InteractingActor);
		if (PlayerCharacter == nullptr)
		{
			return false;
		}
		
		OnCheckpointUse.Broadcast(InteractingActor);
	}
	else
	{
		bIsActive = true;
		OnCheckpointActivated.Broadcast(InteractingActor);
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

