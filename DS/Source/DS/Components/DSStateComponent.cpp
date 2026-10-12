// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/DSStateComponent.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values for this component's properties
UDSStateComponent::UDSStateComponent()
{
}

void UDSStateComponent::ClearState()
{
	CurrentState = FGameplayTag::EmptyTag;
}

bool UDSStateComponent::IsCurrentStateEqualToAny(const FGameplayTagContainer& TagsToCheck) const
{
	return TagsToCheck.HasTagExact(CurrentState);
}

void UDSStateComponent::ToggleMovementInput(bool bEnabled, float Duration)
{
	if (bEnabled)
	{
		FLatentActionInfo LatenAction;
		LatenAction.CallbackTarget = this;
		LatenAction.ExecutionFunction = "MovementInputEnableAction";
		LatenAction.Linkage = 0;
		LatenAction.UUID = 0;

		UKismetSystemLibrary::RetriggerableDelay(GetWorld(), Duration, LatenAction);
	}
	else
	{
		bMovementInputEnabled = false;
	}
}

void UDSStateComponent::MovementInputEnableAction()
{
	bMovementInputEnabled = true;
	ClearState();
}


