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

public:
	void SetTarget(AActor* NewTarget);

	UFUNCTION()
	void TargetPerceptionUpdated(AActor* Actor, struct FAIStimulus Stimulus);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UAIPerceptionComponent> AIPerceptionComponent;

	// 플레이어 시각 감지 타이머
	FTimerHandle SightTimerHandle;

	// 소실 타임
	float SightLossTime = 3.0f;

protected:
	UPROPERTY(EditAnywhere, Category = AI)
	TObjectPtr<class UBlackboardData> BBAsset;

	UPROPERTY(EditAnywhere, Category = AI)
	TObjectPtr<class UBehaviorTree> BTAsset;
};
