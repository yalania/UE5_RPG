// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "BaseAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class UE5_RPG_API UBaseAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	// Health 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData Health = 100.0f;
	ATTRIBUTE_ACCESSORS_BASIC(UBaseAttributeSet, Health);
 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData MaxHealth = 100.0f;
	ATTRIBUTE_ACCESSORS_BASIC(UBaseAttributeSet, MaxHealth);
	
	void PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const override;
	void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;
};
