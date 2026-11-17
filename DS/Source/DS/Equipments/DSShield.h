// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Equipments/DSEquipment.h"
#include "DSShield.generated.h"

/**
 * 
 */
UCLASS()
class DS_API ADSShield : public ADSEquipment
{
	GENERATED_BODY()

public:
	ADSShield();

public:
	virtual void EquipItem() override;
	
public:
	FORCEINLINE FName GetEquipSocketName() const { return EquipSocketName; }
	FORCEINLINE FName GetUnequipSocketName() const { return UnequipSocketName; }

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment | Socket")
	FName EquipSocketName = FName("Shield_Equip_Socket");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment | Socket")
	FName UnequipSocketName = FName("Shield_Unequip_Socket");
};
