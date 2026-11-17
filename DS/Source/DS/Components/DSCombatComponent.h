// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DSCombatComponent.generated.h"

class ADSWeapon;
class ADSShield;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DS_API UDSCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDSCombatComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	FORCEINLINE ADSWeapon* GetMainWeapon() const { return MainWeapon; }
	FORCEINLINE ADSShield* GetShield() const { return Shield; }

public:
	void SetWeapon(ADSWeapon* NewWeapon);
	void SetShield(ADSShield* NewShield);

public:
	FORCEINLINE bool IsCombatEnabled() const				{ return bCombatEnabled;		}
	FORCEINLINE void SetCombatEnabled(const bool bEnabled)	{ bCombatEnabled = bEnabled;	}

protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<ADSWeapon> MainWeapon;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<ADSShield> Shield;

	/* 전투 활성화 상태인지?*/
	UPROPERTY(EditAnywhere)
	bool bCombatEnabled = false;
};
