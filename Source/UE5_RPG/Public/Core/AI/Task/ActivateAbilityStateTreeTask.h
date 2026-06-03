// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/StateTreeTaskBlueprintBase.h"
#include "ActivateAbilityStateTreeTask.generated.h"

class UGameplayAbility;
class AEnemyCharacter;
class UAbilitySystemComponent;
/**
 * 
 */
UCLASS()
class UE5_RPG_API UActivateAbilityStateTreeTask : public UStateTreeTaskBlueprintBase
{
	GENERATED_BODY()
	
public:
	virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) override;
	virtual void ExitState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) override;
	
	UPROPERTY(EditAnywhere, Category = "Context")
	AEnemyCharacter* Owner;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UGameplayAbility> Ability;
private:
	UPROPERTY(VisibleAnywhere)
	UAbilitySystemComponent* AbilitySystemComponent = nullptr;
	
	FDelegateHandle OnAbilityEnded;
};
