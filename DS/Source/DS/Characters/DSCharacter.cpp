// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/DSCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/DSAttributeComponent.h"
#include "UI/DSPlayerHUDWidget.h"

// Sets default values
ADSCharacter::ADSCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCharacterMovement()->MaxWalkSpeed = NormalSpeed;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.0f;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->TargetArmLength = 500.0f;
	SpringArm->SetRelativeRotation(FRotator(-30, 0, 0));

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	// 캐릭터 컴포넌트
	AttributeComponent = CreateDefaultSubobject<UDSAttributeComponent>(TEXT("Attribute"));

}

// Called when the game starts or when spawned
void ADSCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController)
	{
		auto* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());

		if (Subsystem)
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	if (WBP_PlayerHUDWidget)
	{
		PlayerHUDWidget = CreateWidget<UDSPlayerHUDWidget>(GetWorld(), WBP_PlayerHUDWidget);

		if (PlayerHUDWidget)
		{
			PlayerHUDWidget->AddToViewport();
		}
	}
}

// Called every frame
void ADSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ADSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	auto* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (EnhancedInputComponent)
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ADSCharacter::Input_Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ADSCharacter::Input_Look);

		EnhancedInputComponent->BindAction(SprintRollingAction, ETriggerEvent::Triggered, this, &ADSCharacter::Sprinting);
		EnhancedInputComponent->BindAction(SprintRollingAction, ETriggerEvent::Completed, this, &ADSCharacter::StopSprint);
		EnhancedInputComponent->BindAction(SprintRollingAction, ETriggerEvent::Canceled, this, &ADSCharacter::Rolling);
	}
}

bool ADSCharacter::IsMoving()
{
	UCharacterMovementComponent* MovementComp = GetCharacterMovement();
	if (MovementComp)
	{
		return MovementComp->Velocity.Size2D() > 3.0f && MovementComp->GetCurrentAcceleration() != FVector::ZeroVector;
	}

	return false;
}

bool ADSCharacter::IsSpringing()
{
	return bSprinting;
}

void ADSCharacter::Input_Move(const FInputActionValue& InputValue)
{
	FVector2D MovementVector = InputValue.Get<FVector2D>();

	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation = FRotator(0, Rotation.Yaw, 0);

	const FVector ForwardVector = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightVector = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(ForwardVector, MovementVector.X);
	AddMovementInput(RightVector, MovementVector.Y);
}

void ADSCharacter::Input_Look(const FInputActionValue& InputValue)
{
	FVector2D LookVector = InputValue.Get<FVector2D>();

	AddControllerYawInput(LookVector.X);
	AddControllerPitchInput(LookVector.Y);
}

void ADSCharacter::Sprinting()
{
	check(AttributeComponent);
	if (AttributeComponent->CheckHasEnoughStamina(BaseStaminaCost) && IsMoving())
	{
		GetCharacterMovement()->MaxWalkSpeed = SprintingSpeed;

		AttributeComponent->DecreaseStamina(BaseStaminaCost);

		AttributeComponent->ToggleStaminaRegen(false);
		
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Magenta, FString::Printf(TEXT("Stamina : %f"), AttributeComponent->GetBaseStamina()));
	}
	else
	{
		StopSprint();
	}
}

void ADSCharacter::StopSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = NormalSpeed;

	check(AttributeComponent);

	AttributeComponent->ToggleStaminaRegen(true);
}

void ADSCharacter::Rolling()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Cyan, TEXT("Rolling"));
}

