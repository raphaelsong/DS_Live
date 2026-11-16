// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_InRangeCheck.generated.h"

/**
 * 
 */
UCLASS()
class DS_API UBTDecorator_InRangeCheck : public UBTDecorator
{
	GENERATED_BODY()
	
public:
	UBTDecorator_InRangeCheck();

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FBlackboardKeySelector TargetActorKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RangeMin = 300.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RangeMax = 500.0f;
};
