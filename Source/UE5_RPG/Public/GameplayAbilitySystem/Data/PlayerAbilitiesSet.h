// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PlayerAbilitiesSet.generated.h"

class UInputAction;
class UGameplayAbility;

USTRUCT()
struct FInputAbilityInfo
{
 	GENERATED_USTRUCT_BODY()
 
	friend uint32 GetTypeHash(const FInputAbilityInfo& Item);
	bool IsValid() const;

	UPROPERTY(EditAnywhere, Category = "InputAbilityInfo")
	TSubclassOf<UGameplayAbility> GameplayAbilityClass;

	UPROPERTY(EditAnywhere, Category = "InputAbilityInfo")
	TObjectPtr<UInputAction> InputAction;
};

/**
 * 
 */
UCLASS()
class UE5_RPG_API UPlayerAbilitiesSet : public UDataAsset
{
	GENERATED_BODY()

public:
	 const TSet<FInputAbilityInfo>& GetInputAbilities() const;
protected:
	UPROPERTY(EditAnywhere, Category = "Abilities")
	TSet<FInputAbilityInfo> InputAbilities;
};
