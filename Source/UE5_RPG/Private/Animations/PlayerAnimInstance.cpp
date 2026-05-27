// Fill out your copyright notice in the Description page of Project Settings.


#include "Animations/PlayerAnimInstance.h"

#include "KismetAnimationLibrary.h"

void UPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
    const APawn* SelfPawn = TryGetPawnOwner();
    if(!IsValid(SelfPawn))
    {
        return;
    }

    CurrentSpeed = static_cast<float>(SelfPawn->GetVelocity().Length());
    CurrentDirection = UKismetAnimationLibrary::CalculateDirection(SelfPawn->GetVelocity(), SelfPawn->GetActorRotation());
}
