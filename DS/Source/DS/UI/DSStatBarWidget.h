// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DSStatBarWidget.generated.h"

/**
 * 
 */
UCLASS()
class DS_API UDSStatBarWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UDSStatBarWidget(const FObjectInitializer& ObjectInitializer);

public:
	virtual void NativeConstruct() override;

public:
	void SetRatio(float Ratio) const;
	void SetStatBarColor(FLinearColor NewColor);

protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UProgressBar> StatBar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = StatBar)
	FLinearColor StatBarColor = FLinearColor::Red;
};
