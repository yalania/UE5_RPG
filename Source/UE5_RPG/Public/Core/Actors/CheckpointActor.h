// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/Interactable.h"
#include "CheckpointActor.generated.h"

UCLASS()
class UE5_RPG_API ACheckpointActor : public AActor, public IInteractable
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACheckpointActor();
	
	UPROPERTY(EditAnywhere)
	FText PromptTextWhenInactive = INVTEXT("Activate Checkpoint");
	
	UPROPERTY(EditAnywhere)
	FText PromptTextWhenActive = INVTEXT("Use Checkpoint");

private:
	virtual bool Interact_Implementation(AActor* InteractingActor) override;
	virtual FText GetInteractPromptText_Implementation() const override;
	
	UPROPERTY(SaveGame)
	bool bIsActive = false;
};
