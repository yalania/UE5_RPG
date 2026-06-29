// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/InteractManagerComponent.h"

#include "Camera/CameraComponent.h"
#include "Interfaces/Interactable.h"

// Sets default values for this component's properties
UInteractManagerComponent::UInteractManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UInteractManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	if ((OwnerCameraComponent = Cast<UCameraComponent>(GetOwner()->GetComponentByClass(UCameraComponent::StaticClass()))))
	{
		GetWorld()->GetTimerManager().SetTimer(
			SearchTimerHandle,
			this,
			&UInteractManagerComponent::SearchInteractiveObjects,
			0.05f,
			true
		);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("UInteractComponent: No UCameraComponent found on %s"), *GetOwner()->GetName());
	}
}

void UInteractManagerComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	GetWorld()->GetTimerManager().ClearTimer(SearchTimerHandle);
	
	Super::EndPlay(EndPlayReason);
}

bool UInteractManagerComponent::InteractWithCurrentInteractable()
{
	if (CurrentInteractable == nullptr)
	{
		return false;
	}
	
	return IInteractable::Execute_Interact(CurrentInteractable, GetOwner());
}

void UInteractManagerComponent::SearchInteractiveObjects()
{
	const UWorld* World = GetWorld();
	const FVector CurrentLocation = OwnerCameraComponent->GetComponentLocation();
	const FVector LineEnd = CurrentLocation + OwnerCameraComponent->GetForwardVector() * MaxInteractDistance;
	const FCollisionShape CollisionShape = FCollisionShape::MakeSphere(MaxInteractRadius);
    
	FHitResult Hit;
	World->SweepSingleByChannel(Hit, CurrentLocation, LineEnd, FQuat::Identity, InteractTraceChannel, CollisionShape);

	AActor* CurrentActor = Hit.GetActor();
	
	AActor* NewInteractable = nullptr;
	if (Hit.bBlockingHit && IsValid(CurrentActor) && CurrentActor->Implements<UInteractable>())
	{
		NewInteractable = CurrentActor;
	}

	if (NewInteractable != CurrentInteractable)
	{
		CurrentInteractable = NewInteractable;
		OnInteractableChanged.Broadcast(CurrentInteractable);
	}
}

