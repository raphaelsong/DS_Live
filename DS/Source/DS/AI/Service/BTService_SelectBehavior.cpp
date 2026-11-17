// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Service/BTService_SelectBehavior.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/DSEnemy.h"

UBTService_SelectBehavior::UBTService_SelectBehavior()
{
}

void UBTService_SelectBehavior::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	ADSEnemy* ControlledPawn = Cast<ADSEnemy>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == ControlledPawn)
	{
		return;
	}

	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	if (nullptr == BlackboardComp)
	{
		return;
	}

	AActor* TargetActor = Cast<AActor>(BlackboardComp->GetValueAsObject(TargetActorKey.SelectedKeyName));
	if (IsValid(TargetActor))
	{
		const float Distance = TargetActor->GetDistanceTo(ControlledPawn);
		if (Distance <= AttackRangeDistance)
		{
			SetBehaviorKey(BlackboardComp, EDSAIBehavior::MeleeAttack);
		}
		else
		{
			SetBehaviorKey(BlackboardComp, EDSAIBehavior::Approach);
		}
	}
	else
	{
		if (ControlledPawn->GetPatrolPoint() != nullptr)
		{
			SetBehaviorKey(BlackboardComp, EDSAIBehavior::Patrol);
		}
		else
		{
			SetBehaviorKey(BlackboardComp, EDSAIBehavior::Idle);
		}
	}
}

void UBTService_SelectBehavior::SetBehaviorKey(UBlackboardComponent* BlackboardComp, EDSAIBehavior Behavior) const
{
	BlackboardComp->SetValueAsEnum(BehaviorKey.SelectedKeyName, static_cast<uint8>(Behavior));
}
