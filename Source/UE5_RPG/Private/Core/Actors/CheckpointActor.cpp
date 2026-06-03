// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Actors/CheckpointActor.h"


// Sets default values
ACheckpointActor::ACheckpointActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

bool ACheckpointActor::Interact_Implementation()
{
	if (bIsActive)
	{
		//Do Stuff
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

