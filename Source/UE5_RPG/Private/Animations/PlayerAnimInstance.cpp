// Fill out your copyright notice in the Description page of Project Settings.


#include "Animations/PlayerAnimInstance.h"

#include "KismetAnimationLibrary.h"
#include "Animations/AdditiveAnimationDataAsset.h"
#include "Animations/AdditiveAnimationTypes.h"

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

bool UPlayerAnimInstance::PlayAdditiveAnimation(EAdditiveAnimationID AnimationID)
{
    if (!AdditiveAnimData) return false;

    UAnimSequence* Anim = AdditiveAnimData->FindAnimation(AnimationID);
    if (!Anim) return false;
    
    StopAdditiveAnimation();

    CurrentAdditiveAnimation = Anim;
    AdditiveWeight = 1.0f;

    GetWorld()->GetTimerManager().SetTimer(
        AdditiveResetTimer,
        [this]()
        {
            AdditiveWeight = 0.0f;
            OnAdditiveAnimationFinished.Broadcast(); // notifica a quien esté suscrito
        },
        Anim->GetPlayLength(),
        false
    );

    return true;
}

void UPlayerAnimInstance::StopAdditiveAnimation()
{
    GetWorld()->GetTimerManager().ClearTimer(AdditiveResetTimer);
    AdditiveWeight = 0.0f;
}
