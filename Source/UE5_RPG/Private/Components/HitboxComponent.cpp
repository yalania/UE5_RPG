// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/HitboxComponent.h"

#include "AbilitySystemComponent.h"
#include "Components/BoxComponent.h"

// Sets default values for this component's properties
UHitboxComponent::UHitboxComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called every frame
void UHitboxComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (IsActive())
	{
		FGameplayEffectSpec* CurrentEffectSpec = CurrentEffectSpecHandle.Data.Get();
		if (CurrentEffectSpec == nullptr)
		{
			EndTrace();
			return;
		}
	
		TArray<FHitResult> OutResults;
		if(IsInsideHitbox(OutResults))
		{
			for (const FHitResult& Result : OutResults)
			{
				const AActor* HitActor = Result.GetActor();
				if (UAbilitySystemComponent* AbilitySystemComponent = HitActor->FindComponentByClass<UAbilitySystemComponent>())
				{
					AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*CurrentEffectSpec);
				}
				
				CollisionParams.AddIgnoredActor(Result.GetActor());
			}
		}
	}
	
	LastFramePosition = GetComponentLocation();
}

void UHitboxComponent::BeginPlay()
{
	Super::BeginPlay();
	SetActive(false);
	LastFramePosition = GetComponentLocation();
	CollisionParams =
	{
		FName{TEXT("Ignore Collision Params")},
		false
	};
}

void UHitboxComponent::StartTrace(const FGameplayEffectSpecHandle& EffectSpecHandle)
{
	SetActive(true);
	CollisionParams.AddIgnoredActor(GetOwner());
	CollisionParams.AddIgnoredActor(GetOwner()->GetInstigator());
	CurrentEffectSpecHandle = EffectSpecHandle;
}

void UHitboxComponent::EndTrace()
{
	CollisionParams.ClearIgnoredSourceObjects();
	CurrentEffectSpecHandle.Clear();
	SetActive(false);
}

bool UHitboxComponent::IsInsideHitbox(TArray<FHitResult>& OutResults) const
{
	const FVector& ShapeCurrentCenterPosition = GetComponentLocation();
	const FVector& ShapeExtends = GetScaledBoxExtent();
	const FQuat ShapeRotation = GetComponentQuat();
	
	const bool bHasTarget = GetWorld()->SweepMultiByChannel(OutResults,
		LastFramePosition,
		ShapeCurrentCenterPosition,
		ShapeRotation,
		ECC_GameTraceChannel1, 
		GetCollisionShape(),
		CollisionParams);
	
	DrawDebugBox(
		GetWorld(),
		ShapeCurrentCenterPosition,
		ShapeExtends,
		ShapeRotation,
		bHasTarget ? FColor::Green : FColor::Red,
		false,
		0.1f
	);
	return bHasTarget;
}

