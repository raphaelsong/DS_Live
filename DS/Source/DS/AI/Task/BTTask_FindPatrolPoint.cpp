// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Task/BTTask_FindPatrolPoint.h"
#include "AIController.h"
#include "Engine/TargetPoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/DSEnemy.h"

UBTTask_FindPatrolPoint::UBTTask_FindPatrolPoint()
{
}

EBTNodeResult::Type UBTTask_FindPatrolPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	APawn* ControlledPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControlledPawn)
	{
		return EBTNodeResult::Failed;
	}

	ADSEnemy* DSEnemy = Cast<ADSEnemy>(ControlledPawn);
	if (DSEnemy)
	{
		if (DSEnemy->GetPatrolPoint())
		{
			FVector NewPatrolLocation = DSEnemy->GetPatrolPoint()->GetActorLocation();

			OwnerComp.GetBlackboardComponent()->SetValueAsVector(PatrolLocationKey.SelectedKeyName, NewPatrolLocation);

			DSEnemy->IncrementPatrolIndex();

			return EBTNodeResult::Succeeded;
		}
	}

	return EBTNodeResult::Failed;
}
