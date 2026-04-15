// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayAbilitySpecHandle.h"
#include "GameFramework/Actor.h"
#include "BaseWeapon.generated.h"

class ABaseCharacter;
class UBlendSpace;
class UGameplayAbility;
class UPlayerAnimInstance;
class UHitboxComponent;

UCLASS()
class UE5_RPG_API ABaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseWeapon();
	
	void ApplyProperties(const ABaseCharacter& WeaponOwner);
	void ClearProperties(const ABaseCharacter& WeaponOwner);
private:
	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* WeaponMesh = nullptr;
	
	UPROPERTY(EditAnywhere)
	UHitboxComponent* HitboxComponent = nullptr;
	
	UPROPERTY(EditAnywhere, Category= "Abilities")
	TArray<TSubclassOf<UGameplayAbility>> WeaponAbilities;
	
	UPROPERTY(VisibleAnywhere, Category= "Abilities")
	TArray<FGameplayAbilitySpecHandle> GrantedAbilities;
	
	UPROPERTY(EditAnywhere, Category= "Animation")
	FName EquippedSocketName;
	
	UPROPERTY(EditAnywhere, Category= "Animation")
	UBlendSpace* StrafeBlendSpace = nullptr;
	
	UBlendSpace* OriginalBlendSpace = nullptr;
};
