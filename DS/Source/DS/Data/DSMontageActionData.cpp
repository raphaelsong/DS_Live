// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/DSMontageActionData.h"

UDSMontageActionData::UDSMontageActionData()
{
}

UAnimMontage* UDSMontageActionData::GetMontageGroupForTag(const FGameplayTag& GroupTag, const int32 Index)
{
	if (MontageGroupMap.Contains(GroupTag))
	{
		const FDSMontageGroup& MontageGroup = MontageGroupMap[GroupTag];

		if (MontageGroup.Animations.Num() > 0 && MontageGroup.Animations.Num() > Index)
		{
			return MontageGroup.Animations[Index];
		}
	}

	return nullptr;
}

float UDSMontageActionData::GetStaminaCost(const FGameplayTag& GroupTag)
{
	if (MontageGroupMap.Contains(GroupTag))
	{
		return MontageGroupMap[GroupTag].StaminaCost;
	}

	return 0.0f;
}
