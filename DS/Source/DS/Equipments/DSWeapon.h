// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Equipments/DSEquipment.h"
#include "DSWeapon.generated.h"

/**
 * 
 */
UCLASS()
class DS_API ADSWeapon : public ADSEquipment
{
	GENERATED_BODY()
	
public:
	ADSWeapon();

public:
	virtual void EquipItem() override;

public:
	FORCEINLINE FName GetEquipSocketName() const { return EquipSocketName; }
	FORCEINLINE FName GetUnEquipSocketName() const { return UnequipSocketName; }

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment | Socket")
	FName EquipSocketName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment | Socket")
	FName UnequipSocketName;
};
