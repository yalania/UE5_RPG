// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractManagerComponent.generated.h"


class UCameraComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInteractableChanged, AActor*, NewInteractable);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE5_RPG_API UInteractManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInteractManagerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	UFUNCTION(BlueprintCallable, Category = "Interact")
	bool InteractWithCurrentInteractable();
	
	UPROPERTY(VisibleAnywhere, Category = "Interact")
	TEnumAsByte<ECollisionChannel> InteractTraceChannel = ECC_GameTraceChannel2;
	
	UPROPERTY(VisibleAnywhere, Category = "Interact")
	float MaxInteractDistance = 500.0f;
	
	UPROPERTY(VisibleAnywhere, Category = "Interact")
	float MaxInteractRadius = 100.0f;
	
	UPROPERTY(BlueprintAssignable, Category = "Interact")
	FOnInteractableChanged OnInteractableChanged;

private:
	void SearchInteractiveObjects();
	
	AActor* CurrentInteractable = nullptr;
	UCameraComponent* OwnerCameraComponent = nullptr;
	FTimerHandle SearchTimerHandle;
};
