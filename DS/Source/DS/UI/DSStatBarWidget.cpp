// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/DSStatBarWidget.h"
#include "Components/ProgressBar.h"

UDSStatBarWidget::UDSStatBarWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UDSStatBarWidget::NativeConstruct()
{
	Super::NativeConstruct();

	SetStatBarColor(StatBarColor);
}

void UDSStatBarWidget::SetRatio(float Ratio) const
{
	if (StatBar)
	{
		StatBar->SetPercent(Ratio);
	}
}

void UDSStatBarWidget::SetStatBarColor(FLinearColor NewColor)
{
	if (StatBar)
	{
		StatBar->SetFillColorAndOpacity(NewColor);
	}
}
