// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/LockOnTargetComponent.h"

#include "GameplayCueNotifyTypes.h"
#include "Characters/EnemyCharacter.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Interfaces/Enemy.h"
#include "Kismet/KismetMathLibrary.h"

class USpringArmComponent;

ULockOnTargetComponent::ULockOnTargetComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void ULockOnTargetComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerRef = GetOwner<ACharacter>();
	PlayerController = GetWorld()->GetFirstPlayerController();
	MovementComponent = OwnerRef->GetCharacterMovement();
	SpringArm = OwnerRef->FindComponentByClass<USpringArmComponent>();
}

bool ULockOnTargetComponent::StartLockon(float Radius)
{
	TArray<FHitResult> HitResults;
	const FVector& CurrentLocation = OwnerRef->GetActorLocation();
	const FCollisionShape SphereCast = FCollisionShape::MakeSphere(Radius);
	const FCollisionQueryParams CollisionParams
	{
		FName{TEXT("Ignore Collision Params")},
		false,
		OwnerRef
	};
	
	const bool bTargetFound = GetWorld()->SweepMultiByChannel(HitResults, CurrentLocation,CurrentLocation, FQuat::Identity, ECC_GameTraceChannel1, SphereCast, CollisionParams);
	if(bTargetFound == false)
	{
		return false;
	}

	AActor* BestTarget = nullptr;
	float BestDot = -1.f;
	for (const FHitResult& Hit : HitResults)
	{   
		if (Hit.GetActor()->Implements<UEnemy>() == false)
		{
			continue;
		}
    
		const FVector ToTarget = (Hit.GetActor()->GetActorLocation() - CurrentLocation).GetSafeNormal();
		const float Dot = FVector::DotProduct(OwnerRef->GetActorForwardVector(), ToTarget);
    
		if (Dot > BestDot)
		{
			BestDot = Dot;
			BestTarget = Hit.GetActor();
		}
	}

	if (IsValid(BestTarget) == false)
	{
		return false;
	}
	
	TargetActor = Cast<ABaseCharacter>(BestTarget);
	IEnemy::Execute_OnSelect(TargetActor);
	
	UE_LOGFMT(LogTemp, Warning, "Found target {Name}", TargetActor->GetName());
	PlayerController->SetIgnoreLookInput(true);
	MovementComponent->bOrientRotationToMovement = false;
	MovementComponent->bUseControllerDesiredRotation = true;

	SetComponentTickEnabled(true);
	//SpringArm->TargetOffset = FVector{0.0f, 0.0f, 50.0f};
	return true;
}

void ULockOnTargetComponent::EndLockon()
{
	SetComponentTickEnabled(false);
	//SpringArm->TargetOffset = FVector::ZeroVector;

	MovementComponent->bUseControllerDesiredRotation = false;
	MovementComponent->bOrientRotationToMovement = true;
	PlayerController->ResetIgnoreLookInput();

	if (IsValid(TargetActor))
	{
		IEnemy::Execute_OnDeselect(TargetActor);
		TargetActor = nullptr;
	}
}

// Called every frame
void ULockOnTargetComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if(IsValid(TargetActor))
	{
		if (TargetActor->IsDead())
		{
			OnLockOnBroken.Broadcast();
			return;
		}
		
		FVector TargetLocation = TargetActor->GetActorLocation();
		const FVector& OwnerLocation = OwnerRef->GetActorLocation();
		const double DistanceToTarget = FVector::Distance(OwnerLocation, TargetLocation);
		
		if(DistanceToTarget >= BreakingDistance)
		{
			OnLockOnBroken.Broadcast();
			return;
		}
		
		TargetLocation.Z -= 125.0f;

		FRotator NewRot = UKismetMathLibrary::FindLookAtRotation(OwnerLocation,TargetLocation);
		PlayerController->SetControlRotation(NewRot);
	}
}

