// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/EquipmentComponent.h"

#include "Characters/BaseCharacter.h"
#include "Combat/Weapons/BaseWeapon.h"

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

ABaseWeapon* UEquipmentComponent::GetEquippedWeapon() const
{
	return SpawnedEquippedWeapon;
}

void UEquipmentComponent::SpawnEquippedWeapon()
{
	ABaseCharacter* OwnerCharacter = Cast<ABaseCharacter>(GetOwner());
	FActorSpawnParameters SpawnParams;
	SpawnParams.Instigator = OwnerCharacter;
	SpawnParams.Owner = GetOwner();
	SpawnedEquippedWeapon = Cast<ABaseWeapon>(GetWorld()->SpawnActor(EquippedWeaponClass, &GetOwner()->GetActorTransform(),SpawnParams));
	if (SpawnedEquippedWeapon == nullptr)
	{
		return;
	}
	
	if (OwnerCharacter != nullptr)
	{
		SpawnedEquippedWeapon->ApplyProperties(*OwnerCharacter);
	}
}

void UEquipmentComponent::UnspawnEquippedWeapon()
{
	if (SpawnedEquippedWeapon == nullptr)
	{
		return;
	}
	
	if (const ABaseCharacter* OwnerCharacter = Cast<ABaseCharacter>(GetOwner()))
	{
		SpawnedEquippedWeapon->ClearProperties(*OwnerCharacter);
	}
	SpawnedEquippedWeapon->Destroy();
}

