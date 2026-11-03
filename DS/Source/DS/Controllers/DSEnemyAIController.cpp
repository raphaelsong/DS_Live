// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/DSEnemyAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

ADSEnemyAIController::ADSEnemyAIController()
{
}

void ADSEnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	RunAI();
}

void ADSEnemyAIController::OnUnPossess()
{
	Super::OnUnPossess();


}

void ADSEnemyAIController::RunAI()
{
	UBlackboardComponent* BlackboardPtr = Blackboard.Get();
	if (UseBlackboard(BBAsset, BlackboardPtr))
	{
		bool IsResult = RunBehaviorTree(BTAsset);
		ensure(IsResult);
	}
}

void ADSEnemyAIController::StopAI()
{
	UBehaviorTreeComponent* BTComponent = Cast<UBehaviorTreeComponent>(BrainComponent);
	if (BTComponent)
	{
		BTComponent->StopTree();
	}
}
