// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AdditiveAnimationTypes.generated.h"

UENUM(BlueprintType)
enum class EAdditiveAnimationID : uint8
{
	None        UMETA(DisplayName = "None"),
	Parry       UMETA(DisplayName = "Parry"),
	UseFlask    UMETA(DisplayName = "Use Flask"),
};