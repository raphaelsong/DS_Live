// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotifyState/AnimNotifyState_WeaponCollision.h"
#include "Components/DSCombatComponent.h"
#include "Equipments/DSWeapon.h"

UAnimNotifyState_WeaponCollision::UAnimNotifyState_WeaponCollision()
{
}

void UAnimNotifyState_WeaponCollision::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	const AActor* OwnerActor = MeshComp->GetOwner();
	if (OwnerActor)
	{
		const UDSCombatComponent* CombatComponent = OwnerActor->GetComponentByClass<UDSCombatComponent>();
		if (CombatComponent)
		{
			ADSWeapon* Weapon = CombatComponent->GetMainWeapon();
			if (::IsValid(Weapon))
			{
				Weapon->TurnOnWeaponCollision();
			}
		}
	}
}

void UAnimNotifyState_WeaponCollision::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	const AActor* OwnerActor = MeshComp->GetOwner();
	if (OwnerActor)
	{
		const UDSCombatComponent* CombatComponent = OwnerActor->GetComponentByClass<UDSCombatComponent>();
		if (CombatComponent)
		{
			ADSWeapon* Weapon = CombatComponent->GetMainWeapon();
			if (::IsValid(Weapon))
			{
				Weapon->TurnOffWeaponCollision();
			}
		}
	}
}
