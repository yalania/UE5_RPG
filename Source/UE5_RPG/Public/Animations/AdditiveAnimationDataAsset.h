// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AdditiveAnimationTypes.h"
#include "Engine/DataAsset.h"
#include "AdditiveAnimationDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class UE5_RPG_API UAdditiveAnimationDataAsset : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TMap<EAdditiveAnimationID, UAnimSequence*> AdditiveAnimations;
	UAnimSequence* FindAnimation(EAdditiveAnimationID AnimationID);
};
