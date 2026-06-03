// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/AI/BaseAIController.h"
#include "Components/StateTreeAIComponent.h"
#include "Perception/AIPerceptionComponent.h"

ABaseAIController::ABaseAIController(const FObjectInitializer& OI)
{
	StateTreeAIComponent = OI.CreateDefaultSubobject<UStateTreeAIComponent>(this, TEXT("StateTreeAIComponent"));
	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerception"));
}
