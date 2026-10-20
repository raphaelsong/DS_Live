// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotifyState/AnimNotifyState_DSComboWindow.h"
#include "Characters/DSCharacter.h"

UAnimNotifyState_DSComboWindow::UAnimNotifyState_DSComboWindow()
{
}

void UAnimNotifyState_DSComboWindow::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	ADSCharacter* OwnerCharacter = Cast<ADSCharacter>(MeshComp->GetOwner());
	if (OwnerCharacter)
	{
		OwnerCharacter->EnableComboWindow();
	}
}

void UAnimNotifyState_DSComboWindow::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	ADSCharacter* OwnerCharacter = Cast<ADSCharacter>(MeshComp->GetOwner());
	if (OwnerCharacter)
	{
		OwnerCharacter->DisableComboWindow();
	}
}
