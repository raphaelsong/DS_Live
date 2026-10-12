// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "DSStateComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DS_API UDSStateComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDSStateComponent();
		
public:
	FORCEINLINE void SetState(const FGameplayTag NewState) { CurrentState = NewState; }
	FORCEINLINE FGameplayTag GetState() const { return CurrentState; }

	/*현재 상태 초기화*/
	void ClearState();
	
	/*현재 State가 TagsToCheck의 어떤것과 같은지 체크(OR)*/
	bool IsCurrentStateEqualToAny(const FGameplayTagContainer& TagsToCheck) const;

public:
	FORCEINLINE bool MovementInputEnabled() const { return bMovementInputEnabled; }

	/* 이동 입력 토글 */
	void ToggleMovementInput(bool bEnabled, float Duration = 0.0f);

	/* 이동 입력 활성화(C++/Blueprint모두 사용하는 함수) */
	UFUNCTION()
	void MovementInputEnableAction();

protected:
	// 캐릭터의 현재 상태
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = State)
	FGameplayTag CurrentState;

	// 이동키 입력 상태 관리
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = State)
	bool bMovementInputEnabled = true;
};
