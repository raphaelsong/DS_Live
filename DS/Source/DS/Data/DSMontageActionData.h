// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "DSMontageActionData.generated.h"


USTRUCT(BlueprintType)
struct FDSMontageGroup
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float StaminaCost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UAnimMontage*> Animations;
};

/**
 * 
 */
UCLASS()
class DS_API UDSMontageActionData : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UDSMontageActionData();

public:
	UAnimMontage* GetMontageGroupForTag(const FGameplayTag& GroupTag, const int32 Index = 0);

	float GetStaminaCost(const FGameplayTag& GroupTag);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Montage Groups")
	TMap<FGameplayTag, FDSMontageGroup> MontageGroupMap;
};
