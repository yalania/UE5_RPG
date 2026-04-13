// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayAbilitySystem/Attributes/PlayerAttributeSet.h"

#include "GameplayEffectExtension.h"

void UPlayerAttributeSet::PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const
{
	Super::PreAttributeBaseChange(Attribute, NewValue);
	if (Attribute == GetStaminaAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxStamina());
	}
	
	if (Attribute == GetHealingFlaskAmountAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxHealingFlaskAmount());
	}
}

void UPlayerAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	if (Data.EvaluatedData.Attribute == GetStaminaAttribute())
	{
		SetStamina(GetStamina());
	}
	
	if (Data.EvaluatedData.Attribute == GetHealingFlaskAmountAttribute())
	{
		SetHealingFlaskAmount(GetHealingFlaskAmount());
	}
}
