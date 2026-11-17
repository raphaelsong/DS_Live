// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DSDefine.h"
#include "BehaviorTree/BTService.h"
#include "BTService_SelectBehavior.generated.h"

/**
 * 
 */
UCLASS()
class DS_API UBTService_SelectBehavior : public UBTService
{
	GENERATED_BODY()
	
public:
	UBTService_SelectBehavior();

public:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

public:
	void SetBehaviorKey(UBlackboardComponent* BlackboardComp, EDSAIBehavior Behavior) const;

protected:
	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector BehaviorKey;

	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector TargetActorKey;

	UPROPERTY(EditAnywhere)
	float AttackRangeDistance = 500.0f;
};
