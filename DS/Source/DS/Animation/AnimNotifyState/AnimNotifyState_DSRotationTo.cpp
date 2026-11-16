// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotifyState/AnimNotifyState_DSRotationTo.h"
#include "Components/DSRotationComponent.h"

UAnimNotifyState_DSRotationTo::UAnimNotifyState_DSRotationTo()
{
}

void UAnimNotifyState_DSRotationTo::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	UDSRotationComponent* RotationComponent = MeshComp->GetOwner()->GetComponentByClass<UDSRotationComponent>();
	if (RotationComponent)
	{
		RotationComponent->ToggleShouldRotate(true);
	}
}

void UAnimNotifyState_DSRotationTo::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	UDSRotationComponent* RotationComponent = MeshComp->GetOwner()->GetComponentByClass<UDSRotationComponent>();
	if (RotationComponent)
	{
		RotationComponent->ToggleShouldRotate(false);
	}
}
