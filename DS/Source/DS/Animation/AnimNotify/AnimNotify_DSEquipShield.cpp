// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotify/AnimNotify_DSEquipShield.h"
#include "Components/DSCombatComponent.h"
#include "Equipments/DSShield.h"

UAnimNotify_DSEquipShield::UAnimNotify_DSEquipShield()
{
}

void UAnimNotify_DSEquipShield::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	const AActor* OwnerActor = MeshComp->GetOwner();
	if (OwnerActor)
	{
		UDSCombatComponent* CombatComponent = OwnerActor->GetComponentByClass<UDSCombatComponent>();
		if (CombatComponent && CombatComponent->GetMainWeapon())
		{
			ADSShield* Shield = CombatComponent->GetShield();
			if (Shield)
			{
				FName ShieldSocketName;

				if (bToggleEquip)
				{
					ShieldSocketName = Shield->GetEquipSocketName();
				}
				else
				{
					ShieldSocketName = Shield->GetUnequipSocketName();
				}

				Shield->AttachToOwner(ShieldSocketName);
			}
		}
	}
}
