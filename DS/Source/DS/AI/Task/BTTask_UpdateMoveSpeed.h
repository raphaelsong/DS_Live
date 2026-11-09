// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_UpdateMoveSpeed.generated.h"

/**
 * 
 */
UCLASS()
class DS_API UBTTask_UpdateMoveSpeed : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTask_UpdateMoveSpeed();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxWalkSpeed = 300.0f;
};
