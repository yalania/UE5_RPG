// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/Interactable.h"
#include "CheckpointActor.generated.h"

class UGameplayEffect;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCheckpointNotification, AActor*, InteractingActor);

UCLASS()
class UE5_RPG_API ACheckpointActor : public AActor, public IInteractable
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACheckpointActor();
	
	virtual bool CanInteract(AActor* InteractingActor) override;
	
	UFUNCTION(BlueprintCallable)
	void SetCanInteract(bool newValue);
	
	UPROPERTY(EditAnywhere)
	FText PromptTextWhenInactive = INVTEXT("Activate Checkpoint");
	
	UPROPERTY(EditAnywhere)
	FText PromptTextWhenActive = INVTEXT("Use Checkpoint");
	
	UPROPERTY(BlueprintAssignable)
	FCheckpointNotification OnCheckpointActivated;
	
	UPROPERTY(BlueprintAssignable)
	FCheckpointNotification OnCheckpointUse;


private:
	virtual bool Interact_Implementation(AActor* InteractingActor) override;
	virtual FText GetInteractPromptText_Implementation() const override;
	
	UPROPERTY(SaveGame)
	bool bIsActive = false;
	
	UPROPERTY(EditAnywhere)
	bool bCanIntearct = true;
};
