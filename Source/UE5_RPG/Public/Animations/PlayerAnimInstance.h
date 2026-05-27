// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AdditiveAnimationTypes.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnimInstance.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAdditiveAnimationFinished);

class UAdditiveAnimationDataAsset;
/**
 * 
 */
UCLASS()
class UE5_RPG_API UPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	void NativeUpdateAnimation(float DeltaSeconds) override;
	bool PlayAdditiveAnimation(EAdditiveAnimationID AnimationID);
	void StopAdditiveAnimation();

	UPROPERTY(BlueprintAssignable)
	FOnAdditiveAnimationFinished OnAdditiveAnimationFinished;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UBlendSpace* StrafeBlendSpace = nullptr;
protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float CurrentSpeed = 0.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float CurrentDirection = 0.0f;
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UAnimSequence> CurrentAdditiveAnimation = nullptr;

	UPROPERTY(BlueprintReadOnly)
	float AdditiveWeight = 0.0f;

private:
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess))
	TObjectPtr<UAdditiveAnimationDataAsset> AdditiveAnimData;

	FTimerHandle AdditiveResetTimer;
};
