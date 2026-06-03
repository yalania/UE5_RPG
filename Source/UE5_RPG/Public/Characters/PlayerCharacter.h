// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "Characters/BaseCharacter.h"

#include "PlayerCharacter.generated.h"

class UInteractManagerComponent;
class ULockOnTargetComponent;
class UEquipmentComponent;
class UCameraComponent;
class USpringArmComponent;
class UInputAction;
class UInputMappingContext;
class UPlayerAttributeSet;
class UPlayerAbilitiesSet;
struct FInputActionValue;

UCLASS()
class UE5_RPG_API APlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void InitAbilitySystem();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	// APawn interface
	virtual void NotifyControllerChanged() override;
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	
protected:
	void OnAbilityInputPressed(int32 InputID);
	void OnAbilityInputReleased(int32 InputID);

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Abilities")
	TObjectPtr<UPlayerAbilitiesSet> PlayerAbilitiesSet;

	UPROPERTY(VisibleAnywhere, Category = Attributes)
	const UPlayerAttributeSet* PlayerAttributeSet;

	UPROPERTY(EditAnywhere)
	USpringArmComponent* SpringArmComponent = nullptr;

	UPROPERTY(EditAnywhere)
	UCameraComponent* CameraComponent = nullptr;

	UPROPERTY(EditAnywhere)
	ULockOnTargetComponent* LockOnTargetComponent = nullptr;
	
	UInteractManagerComponent* InteractManagerComponent = nullptr;
	// Inputs
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;
	
};
