// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_Chance.generated.h"

/**
 * 
 */
UCLASS()
class DS_API UBTDecorator_Chance : public UBTDecorator
{
	GENERATED_BODY()
	
public:
	UBTDecorator_Chance();

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ChanceRate = 30;
};
