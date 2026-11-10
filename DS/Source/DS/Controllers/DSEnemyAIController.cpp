// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/DSEnemyAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Characters/DSCharacter.h"

ADSEnemyAIController::ADSEnemyAIController()
{
	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerception"));

	AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &ADSEnemyAIController::TargetPerceptionUpdated);
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

void ADSEnemyAIController::SetTarget(AActor* NewTarget)
{
	if (IsValid(Blackboard))
	{
		Blackboard->SetValueAsObject(FName("TargetActor"), NewTarget);
	}
}

void ADSEnemyAIController::TargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	ADSCharacter* DSCharacter = Cast<ADSCharacter>(Actor);
	if (nullptr == DSCharacter)
	{
		return;
	}

	if (Stimulus.WasSuccessfullySensed() && DSCharacter->IsDeath() == false)
	{
		SetTarget(Actor);

		GetWorld()->GetTimerManager().ClearTimer(SightTimerHandle);
	}
	else
	{
		float LossTime = SightLossTime;

		if (DSCharacter->IsDeath())
		{
			LossTime = 0.1f;
		}

		GetWorld()->GetTimerManager().SetTimer(
			SightTimerHandle,
			FTimerDelegate::CreateLambda(
				[this]()
				{
					SetTarget(nullptr);
				}
			), LossTime, false);
	}
}
