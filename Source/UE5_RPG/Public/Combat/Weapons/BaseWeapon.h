// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseWeapon.generated.h"

class ACharacter;
class UBlendSpace;
class UGameplayAbility;
class UPlayerAnimInstance;

UCLASS()
class UE5_RPG_API ABaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseWeapon();
	
	void Sheathe(ACharacter& WeaponOwner);
	void Unsheathe(ACharacter& WeaponOwner);
private:
	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* WeaponMesh = nullptr;
	
	UPROPERTY(EditAnywhere, Category= "Abilities")
	TArray<UGameplayAbility*> GrantedAbilities;
	
	UPROPERTY(EditAnywhere, Category= "Animation")
	FName EquippedSocketName;
	
	UPROPERTY(EditAnywhere, Category= "Animation")
	UBlendSpace* StrafeBlendSpace = nullptr;
	
	UBlendSpace* OriginalBlendSpace = nullptr;
};
