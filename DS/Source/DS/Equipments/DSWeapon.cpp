// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipments/DSWeapon.h"
#include "Components/DSCombatComponent.h"

ADSWeapon::ADSWeapon()
{
}

void ADSWeapon::EquipItem()
{
	Super::EquipItem();

	UDSCombatComponent* CombatComponent = GetOwner()->GetComponentByClass<UDSCombatComponent>();

	if (CombatComponent)
	{
		CombatComponent->SetWeapon(this);

		AttachToOwner(UnequipSocketName);
	}
}
