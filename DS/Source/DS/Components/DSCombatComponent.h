// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DSCombatComponent.generated.h"

class ADSWeapon;

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

public:
	void SetWeapon(ADSWeapon* NewWeapon);

protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<ADSWeapon> MainWeapon;
};
