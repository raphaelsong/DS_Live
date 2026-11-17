// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipments/DSShield.h"
#include "Components/DSCombatComponent.h"

ADSShield::ADSShield()
{
}

void ADSShield::EquipItem()
{
	Super::EquipItem();

	UDSCombatComponent* CombatComponent = GetOwner()->GetComponentByClass<UDSCombatComponent>();
	if (CombatComponent)
	{
		CombatComponent->SetShield(this);

		const FName AttachSocket = CombatComponent->IsCombatEnabled() ? EquipSocketName : UnequipSocketName;

		AttachToOwner(AttachSocket);
	}
}
