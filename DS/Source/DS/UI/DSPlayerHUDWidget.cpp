// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/DSPlayerHUDWidget.h"
#include "UI/DSStatBarWidget.h"
#include "Components/DSAttributeComponent.h"

UDSPlayerHUDWidget::UDSPlayerHUDWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UDSPlayerHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	APawn* OwningPawn = GetOwningPlayerPawn();
	if (OwningPawn)
	{
		UDSAttributeComponent* Attribute = OwningPawn->GetComponentByClass<UDSAttributeComponent>();
		if (Attribute)
		{
			Attribute->OnAttributeChanged.AddUObject(this, &UDSPlayerHUDWidget::OnAttributeChanged);
			Attribute->BroadcastAttributeChanged(EDSAttributeType::Stamina);
		}
	}
}

void UDSPlayerHUDWidget::OnAttributeChanged(EDSAttributeType AttributeType, float InValue)
{
	switch (AttributeType)
	{
	case EDSAttributeType::Stamina:
		StaminaBarWidget->SetRatio(InValue);
		break;
	case EDSAttributeType::Health:
		break;
	default:
		break;
	}
}
