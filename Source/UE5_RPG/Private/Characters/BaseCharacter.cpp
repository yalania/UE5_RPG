// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/BaseCharacter.h"
#include "GameplayAbilitySystem/Attributes/BaseAttributeSet.h"

#include "AbilitySystemComponent.h"

ABaseCharacter::ABaseCharacter() 
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystem"));
	BaseAttributeSet = CreateDefaultSubobject<UBaseAttributeSet>(TEXT("BaseAttributes"));
}

// IAbilitySystemInterface
UAbilitySystemComponent *ABaseCharacter::GetAbilitySystemComponent() const
{
    return AbilitySystemComponent;
}

TArray<FGameplayAbilitySpecHandle> ABaseCharacter::GrantAbilities(const TArray<TSubclassOf<UGameplayAbility>>& AbilityClasses) const
{
	TArray<FGameplayAbilitySpecHandle> AbilityHandleSpecs;
	for (const auto& AbilityClass : AbilityClasses)
	{
		const FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, 1, -1);
		AbilityHandleSpecs.Add(AbilitySystemComponent->GiveAbility(AbilitySpec));	
	}
	
	return AbilityHandleSpecs;
}

void ABaseCharacter::RemoveAbilities(TArray<FGameplayAbilitySpecHandle>& AbilitySpecHandles) const
{
	for (const auto& AbilitySpecHandle : AbilitySpecHandles)
	{
		AbilitySystemComponent->ClearAbility(AbilitySpecHandle);
	}
	
	AbilitySpecHandles.Empty();
}

void ABaseCharacter::PossessedBy(AController *NewController)
{
	if(AbilitySystemComponent != nullptr)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
	}
}

void ABaseCharacter::OnRep_PlayerState()
{
	if(AbilitySystemComponent != nullptr)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
	}
}
