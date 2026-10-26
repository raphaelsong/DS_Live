// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipments/DSWeapon.h"
#include "Components/DSCombatComponent.h"
#include "Components/DSWeaponCollisionComponent.h"
#include "Data/DSMontageActionData.h"

ADSWeapon::ADSWeapon()
{
	WeaponCollisionComponent = CreateDefaultSubobject<UDSWeaponCollisionComponent>(TEXT("WeaponCollision"));

	WeaponCollisionComponent->OnHitActor.AddUObject(this, &ADSWeapon::OnHitActor);
}

void ADSWeapon::EquipItem()
{
	Super::EquipItem();

	UDSCombatComponent* CombatComponent = GetOwner()->GetComponentByClass<UDSCombatComponent>();

	if (CombatComponent)
	{
		CombatComponent->SetWeapon(this);

		const FName AttachSocket = CombatComponent->IsCombatEnabled() ? EquipSocketName : UnequipSocketName;

		AttachToOwner(AttachSocket);

		if (WeaponCollisionComponent)
		{
			WeaponCollisionComponent->SetWeaponMesh(Mesh);
			WeaponCollisionComponent->AddIgnoreActor(GetOwner());
		}
	}
}

UAnimMontage* ADSWeapon::GetMontageForTag(const FGameplayTag& GroupTag, const int32 Index)
{
	if (MontageActionData)
	{
		return MontageActionData->GetMontageGroupForTag(GroupTag, Index);
	}

	return nullptr;
}

float ADSWeapon::GetStaminaCost(const FGameplayTag& InTag) const
{
	if (MontageActionData)
	{
		return MontageActionData->GetStaminaCost(InTag);
	}

	return 0.0f;
}

void ADSWeapon::TurnOnWeaponCollision()
{
	if (WeaponCollisionComponent)
	{
		WeaponCollisionComponent->TurnOnCollision();
	}
}

void ADSWeapon::TurnOffWeaponCollision()
{
	if (WeaponCollisionComponent)
	{
		WeaponCollisionComponent->TurnOffCollision();
	}
}

void ADSWeapon::OnHitActor(const FHitResult& Hit)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, TEXT("OutHitActor"));
}
