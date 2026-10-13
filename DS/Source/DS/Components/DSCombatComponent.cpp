// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/DSCombatComponent.h"
#include "Characters/DSCharacter.h"
#include "Equipments/DSWeapon.h"
#include "Item/DSPickupItem.h"

// Sets default values for this component's properties
UDSCombatComponent::UDSCombatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDSCombatComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UDSCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UDSCombatComponent::SetWeapon(ADSWeapon* NewWeapon)
{
	if (::IsValid(MainWeapon))
	{
		ADSCharacter* OwnerCharacter = Cast<ADSCharacter>(GetOwner());
		if (OwnerCharacter)
		{
			ADSPickupItem* PickupItem = GetWorld()->SpawnActorDeferred<ADSPickupItem>(ADSPickupItem::StaticClass(), OwnerCharacter->GetActorTransform(), nullptr, nullptr, ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);

			if (PickupItem)
			{
				PickupItem->SetEquipmentClass(MainWeapon->GetClass());
				PickupItem->FinishSpawning(OwnerCharacter->GetActorTransform());

				MainWeapon->Destroy();
			}
		}
	}

	MainWeapon = NewWeapon;
}

