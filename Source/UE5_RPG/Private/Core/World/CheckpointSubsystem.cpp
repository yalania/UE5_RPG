// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/World/CheckpointSubsystem.h"

#include "AbilitySystemComponent.h"
#include "Characters/EnemyCharacter.h"
#include "Kismet/GameplayStatics.h"

void UCheckpointSubsystem::ResetEnemies()
{
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemyCharacter::StaticClass(), FoundActors);
	
	for (AActor* Actor : FoundActors)
	{
		UAbilitySystemComponent* AbilitySystemComponent = Actor->GetComponentByClass<UAbilitySystemComponent>();
		if (AbilitySystemComponent == nullptr)
		{
			continue;
		}
		
		FGameplayTagContainer ReviveAbilityTagContainer;
		ReviveAbilityTagContainer.AddTag(FGameplayTag::RequestGameplayTag(FName("GameplayAbility.States.Revive")));
		AbilitySystemComponent->TryActivateAbilitiesByTag(ReviveAbilityTagContainer);;
	}
}
