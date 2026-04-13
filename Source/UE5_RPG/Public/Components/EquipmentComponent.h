// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EquipmentComponent.generated.h"

class ABaseWeapon;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE5_RPG_API UEquipmentComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEquipmentComponent();

	UFUNCTION( BlueprintCallable )
	void EquipWeapon(const TSubclassOf<ABaseWeapon>& NewWeaponClass);
	
	UFUNCTION( BlueprintCallable )
	void UnequipWeapon();
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<ABaseWeapon> EquippedWeaponClass;

private:
	void SpawnEquippedWeapon();
	void UnspawnEquippedWeapon();
	
	ABaseWeapon* SpawnedEquippedWeapon = nullptr;
};
