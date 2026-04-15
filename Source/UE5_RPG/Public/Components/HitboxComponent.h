// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "Components/BoxComponent.h"
#include "HitboxComponent.generated.h"

struct FGameplayEffectSpec;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE5_RPG_API UHitboxComponent : public UBoxComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHitboxComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
private:
	bool IsInsideHitbox(TArray<FHitResult>& OutResults) const;
	
public:
	UFUNCTION(BlueprintCallable)
	void StartTrace(const FGameplayEffectSpecHandle & EffectSpecHandle);
	
	UFUNCTION(BlueprintCallable)
	void EndTrace();

protected:
	UPROPERTY(VisibleAnywhere)
	FVector LastFramePosition;
	
private:
	FGameplayEffectSpecHandle CurrentEffectSpecHandle;
	FCollisionQueryParams CollisionParams;
};
