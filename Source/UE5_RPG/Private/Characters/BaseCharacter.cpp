// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/BaseCharacter.h"
#include "GameplayAbilitySystem/Attributes/BaseAttributeSet.h"

#include "AbilitySystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/EquipmentComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

ABaseCharacter::ABaseCharacter() 
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystem"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->ReplicationMode = EGameplayEffectReplicationMode::Minimal;
	
	EquipmentComponent = CreateDefaultSubobject<UEquipmentComponent>("Equipment");
	
	BaseAttributeSet = CreateDefaultSubobject<UBaseAttributeSet>(TEXT("BaseAttributes"));
}

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
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

void ABaseCharacter::HandleDeath()
{
	GetCharacterMovement()->DisableMovement();
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetMesh()->SetSimulatePhysics(true);
	bIsDead = true;
	
	UE_LOG(LogTemp, Warning, TEXT("HandleDeath called on: %s"), *GetName());
}

void ABaseCharacter::PossessedBy(AController *NewController)
{
	Super::PossessedBy(NewController);
	InitAbilitySystemComponent();
}

void ABaseCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	InitAbilitySystemComponent();
}

void ABaseCharacter::InitAbilitySystemComponent()
{
	if(AbilitySystemComponent != nullptr)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
		AbilitySystemComponent->RegisterGameplayTagEvent(FGameplayTag::RequestGameplayTag("State.Death"), EGameplayTagEventType::NewOrRemoved).AddUObject(this, &ABaseCharacter::OnDeathStateChanged);
	
		GrantAbilities(StartingGameplayAbilities);
	}
}

void ABaseCharacter::OnDeathStateChanged(FGameplayTag GameplayTag, int Count)
{
	if (Count > 0)
	{
		HandleDeath();
	}
}
