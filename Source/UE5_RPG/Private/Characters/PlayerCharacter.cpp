// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/PlayerCharacter.h"

#include "GameplayAbilitySystem/Attributes/PlayerAttributeSet.h"
#include "GameplayAbilitySystem/Data/PlayerAbilitiesSet.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Components/EquipmentComponent.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	SpringArmComponent->SetupAttachment(GetCapsuleComponent());

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent);

	EquipmentComponent = CreateDefaultSubobject<UEquipmentComponent>("Equipment");
	PlayerAttributeSet = CreateDefaultSubobject<UPlayerAttributeSet>(TEXT("PlayerAttributes"));
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	InitAbilitySystem();
}

void APlayerCharacter::InitAbilitySystem()
{
	if (PlayerAbilitiesSet && HasAuthority())
	{
		constexpr int32 AbilityLevel = 1;
		for (const FInputAbilityInfo& InputAbility : PlayerAbilitiesSet->GetInputAbilities())
		{
			if (InputAbility.IsValid())
			{
				const FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(InputAbility.GameplayAbilityClass, AbilityLevel, GetTypeHash(InputAbility));
				AbilitySystemComponent->GiveAbility(AbilitySpec);
			}
		}
	}
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void APlayerCharacter::NotifyControllerChanged()
{
	Super::NotifyControllerChanged();

	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{	
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Look);

		// Abilities
		if (PlayerAbilitiesSet != nullptr)
		{
			for (const FInputAbilityInfo& InputAbility : PlayerAbilitiesSet->GetInputAbilities())
			{
				if (InputAbility.IsValid())
				{
					const UInputAction* InputAction = InputAbility.InputAction;
					const int32 InputID = GetTypeHash(InputAbility);

					EnhancedInputComponent->BindAction(InputAction, ETriggerEvent::Started, this, &APlayerCharacter::OnAbilityInputPressed, InputID);
					EnhancedInputComponent->BindAction(InputAction, ETriggerEvent::Completed, this, &APlayerCharacter::OnAbilityInputReleased, InputID);
				}
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void APlayerCharacter::OnAbilityInputPressed(int32 InputID)
{
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->AbilityLocalInputPressed(InputID);
	}
}

void APlayerCharacter::OnAbilityInputReleased(int32 InputID)
{
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->AbilityLocalInputReleased(InputID);
	}
}

void APlayerCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		FRotator ControlRotation = Controller->GetControlRotation();
		FRotator YawRotation(0.0f, ControlRotation.Yaw, 0.0f);

		FVector NewForward = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		FVector NewRight = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		
		// add movement 
		AddMovementInput(NewForward, MovementVector.Y);
		AddMovementInput(NewRight, MovementVector.X);
	}
}

void APlayerCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

