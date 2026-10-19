// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/DSCharacterAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/DSStateComponent.h"

UDSCharacterAnimInstance::UDSCharacterAnimInstance()
{
}

void UDSCharacterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	OwnerCharacter = Cast<ACharacter>(GetOwningActor());

	if (OwnerCharacter)
	{
		MovementComponent = OwnerCharacter->GetCharacterMovement();
	}
}

void UDSCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (MovementComponent)
	{
		Velocity = MovementComponent->Velocity;

		GroundSpeed = Velocity.Size2D();

		bShouldMove = GroundSpeed > 3.0f && MovementComponent->GetCurrentAcceleration() != FVector::ZeroVector;

		bIsFalling = MovementComponent->IsFalling();
	}
}

void UDSCharacterAnimInstance::AnimNotify_ResetMovementInput()
{
	UDSStateComponent* StateComponent = GetOwningActor()->GetComponentByClass<UDSStateComponent>();
	if (StateComponent)
	{
		StateComponent->ToggleMovementInput(true);
	}
}

void UDSCharacterAnimInstance::AnimNotify_ResetState()
{
	UDSStateComponent* StateComponent = GetOwningActor()->GetComponentByClass<UDSStateComponent>();
	if (StateComponent)
	{
		StateComponent->ClearState();
	}
}
