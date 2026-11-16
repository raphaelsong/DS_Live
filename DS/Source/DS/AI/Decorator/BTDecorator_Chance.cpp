// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Decorator/BTDecorator_Chance.h"

UBTDecorator_Chance::UBTDecorator_Chance()
{
    NodeName = TEXT("Chance");
}

bool UBTDecorator_Chance::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
    return ChanceRate >= FMath::RandRange(1, 100);
}
