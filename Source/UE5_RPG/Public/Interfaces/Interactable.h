// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Interactable.generated.h"

UINTERFACE(MinimalAPI, Blueprintable)
class UInteractable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class UE5_RPG_API IInteractable
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool Interact(AActor* InteractingActor);
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	FText GetInteractPromptText() const;
	
private:
	virtual bool Interact_Implementation(AActor* InteractingActor) = 0;
	virtual FText GetInteractPromptText_Implementation() const = 0;
};

