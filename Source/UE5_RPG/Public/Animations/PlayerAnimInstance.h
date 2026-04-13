// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class UE5_RPG_API UPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	 void NativeUpdateAnimation(float DeltaSeconds) override;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UBlendSpace* StrafeBlendSpace = nullptr;
protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float CurrentSpeed = 0.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float CurrentDirection = 0.0f;
};
