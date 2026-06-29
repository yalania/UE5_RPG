// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/World/CheckpointSubsystem.h"

#include "AbilitySystemComponent.h"
#include "Characters/EnemyCharacter.h"
#include "Kismet/GameplayStatics.h"

void UCheckpointSubsystem::ResetEnemies()
{
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), TSubclassOf<AEnemyCharacter>(), FoundActors);
	
	for (AActor* Actor : FoundActors)
	{
		UAbilitySystemComponent* AbilitySystemComponent = Actor->GetComponentByClass<UAbilitySystemComponent>();
		if (AbilitySystemComponent == nullptr)
		{
			continue;
		}
		
		FGameplayTagContainer DeathAbilityTagContainer;
		DeathAbilityTagContainer.AddTag(FGameplayTag::RequestGameplayTag(FName("GameplayAbility.Reset")));
		AbilitySystemComponent->TryActivateAbilitiesByTag(DeathAbilityTagContainer);;
	}
}
