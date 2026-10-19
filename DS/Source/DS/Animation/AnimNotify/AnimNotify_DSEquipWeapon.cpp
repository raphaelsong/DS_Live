// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotify/AnimNotify_DSEquipWeapon.h"
#include "Components/DSCombatComponent.h"
#include "Equipments/DSWeapon.h"

UAnimNotify_DSEquipWeapon::UAnimNotify_DSEquipWeapon()
{
}

void UAnimNotify_DSEquipWeapon::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	const AActor* OwnerActor = MeshComp->GetOwner();
	if (OwnerActor)
	{
		UDSCombatComponent* CombatComponent = OwnerActor->GetComponentByClass<UDSCombatComponent>();
		if (CombatComponent)
		{
			ADSWeapon* MainWeapon = CombatComponent->GetMainWeapon();
			if (MainWeapon)
			{
				bool bCombatEnabled = CombatComponent->IsCombatEnabled();
				FName WeaponSocketName;

				if (bToggleEquip)
				{
					bCombatEnabled = true;
					WeaponSocketName = MainWeapon->GetEquipSocketName();
				}
				else
				{
					bCombatEnabled = false;
					WeaponSocketName = MainWeapon->GetUnEquipSocketName();
				}

				CombatComponent->SetCombatEnabled(bCombatEnabled);
				MainWeapon->AttachToOwner(WeaponSocketName);
			}
		}
	}
}
