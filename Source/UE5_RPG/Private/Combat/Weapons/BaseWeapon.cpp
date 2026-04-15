// Fill out your copyright notice in the Description page of Project Settings.


#include "Combat/Weapons/BaseWeapon.h"

#include "Animations/PlayerAnimInstance.h"
#include "Characters/BaseCharacter.h"
#include "Components/HitboxComponent.h"

// Sets default values
ABaseWeapon::ABaseWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SetRootComponent(WeaponMesh);
	
	HitboxComponent = CreateDefaultSubobject<UHitboxComponent>(TEXT("Hitbox"));
	HitboxComponent->SetupAttachment(GetRootComponent());
}

void ABaseWeapon::ApplyProperties(const ABaseCharacter& WeaponOwner)
{
	WeaponMesh->SetVisibility(true);
	GrantedAbilities = WeaponOwner.GrantAbilities(WeaponAbilities);
	if (USkeletalMeshComponent* CharacterMesh = WeaponOwner.GetMesh())
	{
		AttachToComponent(CharacterMesh, FAttachmentTransformRules::SnapToTargetIncludingScale, EquippedSocketName);
		UPlayerAnimInstance* OwnerAnimInstance = Cast<UPlayerAnimInstance>(CharacterMesh->GetAnimInstance());
		OriginalBlendSpace = OwnerAnimInstance->StrafeBlendSpace;
		OwnerAnimInstance->StrafeBlendSpace = StrafeBlendSpace;
	}
}

void ABaseWeapon::ClearProperties(const ABaseCharacter& WeaponOwner)
{
	WeaponMesh->SetVisibility(false);
	WeaponOwner.RemoveAbilities(GrantedAbilities);
	if (const USkeletalMeshComponent* CharacterMesh = WeaponOwner.GetMesh())
	{
		DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		UPlayerAnimInstance* OwnerAnimInstance = Cast<UPlayerAnimInstance>(CharacterMesh->GetAnimInstance());
		OwnerAnimInstance->StrafeBlendSpace = OriginalBlendSpace;
	}
}

