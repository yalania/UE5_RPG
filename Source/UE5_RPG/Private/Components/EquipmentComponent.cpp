// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/EquipmentComponent.h"

#include "Combat/Weapons/BaseWeapon.h"
#include "GameFramework/Character.h"

// Sets default values for this component's properties
UEquipmentComponent::UEquipmentComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

// Called when the game starts
void UEquipmentComponent::BeginPlay()
{
	Super::BeginPlay();
	SpawnEquippedWeapon();
}

void UEquipmentComponent::EquipWeapon(const TSubclassOf<ABaseWeapon>& NewWeaponClass)
{
	if (NewWeaponClass == EquippedWeaponClass)
	{
		return;
	}
	
	UnequipWeapon();
	EquippedWeaponClass = NewWeaponClass;
	SpawnEquippedWeapon();
}

void UEquipmentComponent::UnequipWeapon()
{
	EquippedWeaponClass = TSubclassOf<ABaseWeapon>();
	UnspawnEquippedWeapon();
}

void UEquipmentComponent::SpawnEquippedWeapon()
{
	SpawnedEquippedWeapon = Cast<ABaseWeapon>(GetWorld()->SpawnActor(EquippedWeaponClass));
	if (SpawnedEquippedWeapon == nullptr)
	{
		return;
	}
	
	if (ACharacter* OwnerCharacter = Cast<ACharacter>(GetOwner()))
	{
		SpawnedEquippedWeapon->Sheathe(*OwnerCharacter);
	}
}

void UEquipmentComponent::UnspawnEquippedWeapon()
{
	if (SpawnedEquippedWeapon == nullptr)
	{
		return;
	}
	
	if (ACharacter* OwnerCharacter = Cast<ACharacter>(GetOwner()))
	{
		SpawnedEquippedWeapon->Unsheathe(*OwnerCharacter);
	}
	SpawnedEquippedWeapon->Destroy();
}

