// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayAbilitySystem/Data/PlayerAbilitiesSet.h"
#include "Abilities/GameplayAbility.h"

uint32 GetTypeHash(const FInputAbilityInfo &Item)
{
    return HashCombine(GetTypeHash(Item.GameplayAbilityClass), GetTypeHash(Item.InputAction));
}

bool FInputAbilityInfo::IsValid() const
{
    return InputAction != nullptr && GameplayAbilityClass != nullptr;
}

const TSet<FInputAbilityInfo>& UPlayerAbilitiesSet::GetInputAbilities() const
{
    return InputAbilities;
}