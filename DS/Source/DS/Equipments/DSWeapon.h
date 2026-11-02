// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Equipments/DSEquipment.h"
#include "GameplayTagContainer.h"
#include "DSWeapon.generated.h"

UCLASS()
class DS_API ADSWeapon : public ADSEquipment
{
	GENERATED_BODY()
	
public:
	ADSWeapon();

public:
	virtual void EquipItem() override;

public:
	UAnimMontage* GetMontageForTag(const FGameplayTag& GroupTag, const int32 Index = 0);
	float GetStaminaCost(const FGameplayTag& InTag) const;
	float GetAttackDamage() const;

public:
	void TurnOnWeaponCollision();
	void TurnOffWeaponCollision();

	// 무기 충돌 액터에 데미지 전달 함수 구독용
	void OnHitActor(const FHitResult& Hit);

public:
	FORCEINLINE FGameplayTag GetLastAttackType() const { return LastAttackType; }
	FORCEINLINE void SetLastAttackType(const FGameplayTag& NewLastAttackType) { LastAttackType = NewLastAttackType; }

public:
	FORCEINLINE FName GetEquipSocketName() const { return EquipSocketName; }
	FORCEINLINE FName GetUnEquipSocketName() const { return UnequipSocketName; }

	FORCEINLINE UAnimMontage* GetEquipMontage() const { return EquipMontageAnimation; }
	FORCEINLINE UAnimMontage* GetUnequipMontage() const { return UnequipMontageAnimation; }

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment | Socket")
	FName EquipSocketName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment | Socket")
	FName UnequipSocketName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment | Animation")
	TObjectPtr<UAnimMontage> EquipMontageAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment | Animation")
	TObjectPtr<UAnimMontage> UnequipMontageAnimation;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment | Animation")
	TObjectPtr<class UDSMontageActionData> MontageActionData;

protected:
	// 기본 데미지
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BaseDamage = 15.0f;

	// 데미지 승수 맵
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FGameplayTag, float> DamageMultiplierMap;

	// 마지막 공격 타입(AttackType)
	UPROPERTY(VisibleAnywhere)
	FGameplayTag LastAttackType;

protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UDSWeaponCollisionComponent> WeaponCollisionComponent;
};
