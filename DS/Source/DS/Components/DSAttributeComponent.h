// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DSAttributeComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DS_API UDSAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDSAttributeComponent();

public:
	/** 스테미나 Getter */
	FORCEINLINE float GetBaseStamina() const { return BaseStamina; }
	FORCEINLINE float GetMaxStamina() const { return MaxStamina; }

	/** 스테미나 비율 계산*/
	FORCEINLINE float GetStaminaRatio() const { return BaseStamina / MaxStamina; }

public:
	/**스테미나가 충분한지 체크*/
	bool CheckHasEnoughStamina(float StaminaCost) const;

	/** 스테미나 차감*/
	void DecreaseStamina(float StaminaCost);

	/** 스태미나 재충전/중지 토글*/
	void ToggleStaminaRegen(bool bEnabled, float StartDelay = 2.0f);

	/** 스태미나 재충전 처리 핸드링 함수*/
	void RegenerateStaminaHandler();

protected:
	UPROPERTY(EditAnywhere, Category = Stamina)
	float BaseStamina = 100.0f;

	UPROPERTY(EditAnywhere, Category = Stamina)
	float MaxStamina = 100.0f;

	UPROPERTY(EditAnywhere, Category = Stamina)
	float StaminaRegenRate = 0.2f;

	/** 스태미나 재충전 타이머 핸들*/
	FTimerHandle StaminaRegenTimerHandle;
};
