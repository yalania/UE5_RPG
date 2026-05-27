// AbilityTask_PlayAdditiveAndWait.h
#pragma once
#include "Abilities/Tasks/AbilityTask.h"
#include "AbilityTask_PlayAdditiveAndWait.generated.h"

class UPlayerAnimInstance;
enum class EAdditiveAnimationID : uint8;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPlayAdditiveAndWaitDelegate);

UCLASS()
class UAbilityTask_PlayAdditiveAndWait : public UAbilityTask
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FPlayAdditiveAndWaitDelegate OnCompleted;

	UPROPERTY(BlueprintAssignable)
	FPlayAdditiveAndWaitDelegate OnCancelled;

	UFUNCTION(BlueprintCallable,Category = "Ability|Tasks", meta = (DisplayName = "Play Additive And Wait", HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "true"))
	static UAbilityTask_PlayAdditiveAndWait* CreatePlayAdditiveAndWait(UGameplayAbility* OwningAbility,EAdditiveAnimationID AnimationID);

	virtual void Activate() override;
	virtual void OnDestroy(bool bInOwnerFinished) override;

private:
	EAdditiveAnimationID AnimationID;
	UPlayerAnimInstance* GetAnimInstance() const;
	
	UFUNCTION()
	void HandleAdditiveFinished();
};
