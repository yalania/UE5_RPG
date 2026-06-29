// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/EnemyCharacter.h"

#include "Components/StateTreeAIComponent.h"
#include "Core/AI/BaseAIController.h"

void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	AIController = Cast<ABaseAIController>(GetController());
	InitialTransform = GetActorTransform();
}

void AEnemyCharacter::HandleDeath()
{
	Super::HandleDeath();
	if (AIController != nullptr)
	{
		AIController->Stop(TEXT("Death"));
	}
}

void AEnemyCharacter::HandleRevive()
{
	Super::HandleRevive();
	
	TeleportTo(InitialTransform.GetLocation(), InitialTransform.Rotator());
	if (AIController != nullptr)
	{
		AIController->Restart();
	}
}
