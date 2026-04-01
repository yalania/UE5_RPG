// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "PlayerAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class UE5_RPG_API UPlayerAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	// Stamina
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData Stamina = 50.0f;
	ATTRIBUTE_ACCESSORS_BASIC(UPlayerAttributeSet, Stamina);
 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData MaxStamina = 50.0f;
	ATTRIBUTE_ACCESSORS_BASIC(UPlayerAttributeSet, MaxStamina);
};
