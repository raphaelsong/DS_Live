// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Task/BTTask_PerformAttack.h"
#include "AIController.h"
#include "Components/DSStateComponent.h"
#include "Interface/DSAICombatInterface.h"

UBTTask_PerformAttack::UBTTask_PerformAttack()
{
}

EBTNodeResult::Type UBTTask_PerformAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	APawn* ControlledPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControlledPawn)
	{
		return EBTNodeResult::Failed;
	}

	IDSAICombatInterface* CombatInterface = Cast<IDSAICombatInterface>(ControlledPawn);
	if (CombatInterface)
	{
		FOnMontageEnded MontageEndedDelegate;
		MontageEndedDelegate.BindLambda(
			[this, &OwnerComp, ControlledPawn](UAnimMontage* Montage, bool bInterrupted)
			{
				if (::IsValid(&OwnerComp) == false)
				{
					return;
				}

				UDSStateComponent* StateComponent = ControlledPawn->GetComponentByClass<UDSStateComponent>();
				if (StateComponent)
				{
					StateComponent->ClearState();
				}

				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
			}
		);

		CombatInterface->PerformAttack(AttackTypeTag, MontageEndedDelegate);
		return EBTNodeResult::InProgress;
	}
	
	return EBTNodeResult::Failed;
}
