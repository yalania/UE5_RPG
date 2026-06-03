// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BaseAIController.generated.h"

class UStateTreeAIComponent;
/**
 * 
 */
UCLASS()
class UE5_RPG_API ABaseAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	ABaseAIController(const FObjectInitializer& OI);
	
	UPROPERTY(VisibleAnywhere)
	UStateTreeAIComponent* StateTreeAIComponent;
};
