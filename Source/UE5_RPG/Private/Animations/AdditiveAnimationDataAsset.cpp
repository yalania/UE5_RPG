// Fill out your copyright notice in the Description page of Project Settings.


#include "Animations/AdditiveAnimationDataAsset.h"
UAnimSequence* UAdditiveAnimationDataAsset::FindAnimation(EAdditiveAnimationID AnimationID)
{
	UAnimSequence** Found = AdditiveAnimations.Find(AnimationID);
	return Found != nullptr ? *Found : nullptr;
}