// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseCharacter.h"
#include "Interfaces/Enemy.h"
#include "EnemyCharacter.generated.h"

class ABaseAIController;
/**
 * 
 */
UCLASS()
class UE5_RPG_API AEnemyCharacter : public ABaseCharacter, public IEnemy
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;
	virtual void HandleDeath() override;
	virtual void HandleRevive() override;
	
private:
	ABaseAIController* AIController = nullptr;
	FTransform InitialTransform;
};
