// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DSDefine.h"
#include "Blueprint/UserWidget.h"
#include "DSPlayerHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class DS_API UDSPlayerHUDWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UDSPlayerHUDWidget(const FObjectInitializer& ObjectInitializer);

public:
	virtual void NativeConstruct() override;

public:
	void OnAttributeChanged(EDSAttributeType AttributeType, float InValue);

protected:
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	TObjectPtr<class UDSStatBarWidget> StaminaBarWidget;
};
