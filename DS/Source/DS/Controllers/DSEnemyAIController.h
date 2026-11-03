// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "DSEnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class DS_API ADSEnemyAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	ADSEnemyAIController();

protected:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

public:
	void RunAI();
	void StopAI();

protected:
	UPROPERTY(EditAnywhere, Category = AI)
	TObjectPtr<class UBlackboardData> BBAsset;

	UPROPERTY(EditAnywhere, Category = AI)
	TObjectPtr<class UBehaviorTree> BTAsset;
};
