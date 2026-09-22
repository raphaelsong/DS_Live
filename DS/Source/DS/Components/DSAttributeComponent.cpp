// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/DSAttributeComponent.h"

// Sets default values for this component's properties
UDSAttributeComponent::UDSAttributeComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

bool UDSAttributeComponent::CheckHasEnoughStamina(float StaminaCost) const
{
	return BaseStamina >= StaminaCost;
}

void UDSAttributeComponent::DecreaseStamina(float StaminaCost)
{
	BaseStamina = FMath::Clamp(BaseStamina - StaminaCost, 0.0f, MaxStamina);

	BroadcastAttributeChanged(EDSAttributeType::Stamina);
}

void UDSAttributeComponent::ToggleStaminaRegen(bool bEnabled, float StartDelay)
{
	if (bEnabled)
	{
		if (GetWorld()->GetTimerManager().IsTimerActive(StaminaRegenTimerHandle) == false)
		{
			GetWorld()->GetTimerManager().SetTimer(StaminaRegenTimerHandle, this, &UDSAttributeComponent::RegenerateStaminaHandler, 0.1f, true, StartDelay);
		}
	}
	else
	{
		GetWorld()->GetTimerManager().ClearTimer(StaminaRegenTimerHandle);
	}
}

void UDSAttributeComponent::RegenerateStaminaHandler()
{
	BaseStamina = FMath::Clamp(BaseStamina + StaminaRegenRate, 0.0f, MaxStamina);

	BroadcastAttributeChanged(EDSAttributeType::Stamina);

	if (BaseStamina >= MaxStamina)
	{
		ToggleStaminaRegen(false);
	}
}

void UDSAttributeComponent::BroadcastAttributeChanged(EDSAttributeType InAttributeType) const
{
	if (OnAttributeChanged.IsBound())
	{
		float Ratio = 0.f;

		switch (InAttributeType)
		{
		case EDSAttributeType::Stamina:
			Ratio = GetStaminaRatio();
			break;
		case EDSAttributeType::Health:
			break;
		default:
			break;
		}

		OnAttributeChanged.Broadcast(InAttributeType, Ratio);
	}
}


