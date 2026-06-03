// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/AI/Task/ActivateAbilityStateTreeTask.h"

#include "AbilitySystemComponent.h"
#include "Characters/EnemyCharacter.h"

EStateTreeRunStatus UActivateAbilityStateTreeTask::EnterState(FStateTreeExecutionContext& Context,
                                                              const FStateTreeTransitionResult& Transition)
{
	EStateTreeRunStatus bSuccess = Super::EnterState(Context, Transition);

	if (Owner == nullptr)
	{
		return EStateTreeRunStatus::Failed;
	}
	AbilitySystemComponent = Owner->GetAbilitySystemComponent();
	if (AbilitySystemComponent == nullptr)
	{
		return EStateTreeRunStatus::Failed;
	}

	// Activate the desired ability here. For example:
	if (AbilitySystemComponent->TryActivateAbilityByClass(Ability))
	{
		OnAbilityEnded = AbilitySystemComponent->AbilityEndedCallbacks.AddLambda(
			[this](UGameplayAbility* InGameplayAbility)
			{
				if (InGameplayAbility && InGameplayAbility->GetClass() == Ability)
				{
					UE_LOGFMT(LogTemp, Log, "Ability {AbilityName} ended.", *InGameplayAbility->GetName());
					FinishTask();
				}
			});
		bSuccess = EStateTreeRunStatus::Running;
	}
	else
	{
		bSuccess = EStateTreeRunStatus::Failed;
	}
	
	return bSuccess;
}

void UActivateAbilityStateTreeTask::ExitState(FStateTreeExecutionContext& Context,
	const FStateTreeTransitionResult& Transition)
{
	Super::ExitState(Context, Transition);
	AbilitySystemComponent->AbilityEndedCallbacks.Remove(OnAbilityEnded);
}
