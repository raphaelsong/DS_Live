// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Task/BTTask_UpdateMoveSpeed.h"
#include "AIController.h"
#include "GameFramework/CharacterMovementComponent.h"

UBTTask_UpdateMoveSpeed::UBTTask_UpdateMoveSpeed()
{
}

EBTNodeResult::Type UBTTask_UpdateMoveSpeed::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	APawn* ControlledPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControlledPawn)
	{
		return EBTNodeResult::Failed;
	}

	UCharacterMovementComponent* MovementComponent = ControlledPawn->GetComponentByClass<UCharacterMovementComponent>();
	if (MovementComponent)
	{
		MovementComponent->MaxWalkSpeed = MaxWalkSpeed;
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
