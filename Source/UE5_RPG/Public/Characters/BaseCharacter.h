// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "AbilitySystemInterface.h"
#include "GameplayTagContainer.h"

#include "BaseCharacter.generated.h"

class UBaseAttributeSet;
class UGameplayAbility;
struct FGameplayAbilitySpecHandle;

UCLASS()
class UE5_RPG_API ABaseCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()
public:
	// Sets default values for this character's properties
	ABaseCharacter();
	void BeginPlay();

	// IAbilitySystemInterface
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
		
	// Gameplay Abilities
	TArray<FGameplayAbilitySpecHandle> GrantAbilities(const TArray<TSubclassOf<UGameplayAbility>>& AbilityClasses) const;
	void RemoveAbilities(TArray<FGameplayAbilitySpecHandle>& AbilitySpecHandles) const;
	
	//To override
	UFUNCTION(BlueprintCallable, Category = "Damage")
	virtual void HandleDeath();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Damage")
	bool IsDead() const { return bIsDead; }
	
protected:
	// Called when the game starts or when spawned
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
	
	void InitAbilitySystemComponent();
	void OnDeathStateChanged(FGameplayTag GameplayTag, int Count);
	
	UPROPERTY(EditAnywhere, Category = "InputAbilityInfo")
	TArray<TSubclassOf<UGameplayAbility>> StartingGameplayAbilities;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Abilities)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, Category = Attributes)
	const UBaseAttributeSet* BaseAttributeSet;

private:
	bool bIsDead = false;
};
