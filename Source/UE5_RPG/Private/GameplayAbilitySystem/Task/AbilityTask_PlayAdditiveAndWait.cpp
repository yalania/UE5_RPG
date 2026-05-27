// Fill out your copyright notice in the Description page of Project Settings.

#include "GameplayAbilitySystem/Task/AbilityTask_PlayAdditiveAndWait.h"

#include "Animations/PlayerAnimInstance.h"
#include "GameFramework/Character.h"

UAbilityTask_PlayAdditiveAndWait* UAbilityTask_PlayAdditiveAndWait::CreatePlayAdditiveAndWait(UGameplayAbility* OwningAbility, EAdditiveAnimationID InAnimationID)
{
	UAbilityTask_PlayAdditiveAndWait* Task = NewAbilityTask<UAbilityTask_PlayAdditiveAndWait>(OwningAbility);
	Task->AnimationID = InAnimationID;
	return Task;
}

void UAbilityTask_PlayAdditiveAndWait::Activate()
{
	UPlayerAnimInstance* AnimInstance = GetAnimInstance();
	if (!AnimInstance || !AnimInstance->PlayAdditiveAnimation(AnimationID))
	{
		OnCancelled.Broadcast();
		EndTask();
		return;
	}

	AnimInstance->OnAdditiveAnimationFinished.AddDynamic(this, &UAbilityTask_PlayAdditiveAndWait::HandleAdditiveFinished);
}

void UAbilityTask_PlayAdditiveAndWait::HandleAdditiveFinished()
{
	if (UPlayerAnimInstance* AnimInstance = GetAnimInstance())
	{
		AnimInstance->OnAdditiveAnimationFinished.RemoveDynamic(this, &UAbilityTask_PlayAdditiveAndWait::HandleAdditiveFinished);
	}

	OnCompleted.Broadcast();
	EndTask();
}

void UAbilityTask_PlayAdditiveAndWait::OnDestroy(bool bInOwnerFinished)
{
	if (UPlayerAnimInstance* AnimInstance = GetAnimInstance())
	{
		AnimInstance->OnAdditiveAnimationFinished.RemoveDynamic(this, &UAbilityTask_PlayAdditiveAndWait::HandleAdditiveFinished);

		if (!bInOwnerFinished)
		{
			AnimInstance->StopAdditiveAnimation();
			OnCancelled.Broadcast();
		}
	}

	Super::OnDestroy(bInOwnerFinished);
}

UPlayerAnimInstance* UAbilityTask_PlayAdditiveAndWait::GetAnimInstance() const
{
	const ACharacter* Character = Cast<ACharacter>(GetAvatarActor());
	return Character ? Cast<UPlayerAnimInstance>(Character->GetMesh()->GetAnimInstance()) : nullptr;
}