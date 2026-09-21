// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "DSCharacterAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class DS_API UDSCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UDSCharacterAnimInstance();

protected:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "References")
	TObjectPtr<class ACharacter> OwnerCharacter;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "References")
	TObjectPtr<class UCharacterMovementComponent> MovementComponent;

// 애니메이션 조건 변수
protected:
	UPROPERTY(BlueprintReadOnly, Category = "Movement_Data")
	FVector Velocity;

	UPROPERTY(BlueprintReadOnly, Category = "Movement_Data")
	float GroundSpeed = 0.0f;

	UPROPERTY(BlueprintReadOnly, Category = "Movement_Data")
	bool bShouldMove = false;

	UPROPERTY(BlueprintReadOnly, Category = "Movement_Data")
	bool bIsFalling = false;
};
