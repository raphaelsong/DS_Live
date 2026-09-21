// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DSCharacter.generated.h"

struct FInputActionValue;
class UInputMappingContext;
class UInputAction;

UCLASS()
class DS_API ADSCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADSCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

/** 캐릭터의 관련 기능 */
public:
	bool IsMoving();
	bool IsSpringing();

protected:
	/** 질주 속도*/
	UPROPERTY(EditAnywhere, Category = Sprinting)
	float SprintingSpeed = 700.0f;

	/** 일반 속도*/
	UPROPERTY(EditAnywhere, Category = Sprinting)
	float NormalSpeed = 350.0f;

	/** 기본적인 스테미나 사용량*/
	UPROPERTY(EditAnywhere, Category = Sprinting)
	float BaseStaminaCost = 0.1f;

	UPROPERTY(VisibleAnywhere, Category = Sprinting)
	bool bSprinting = false;

/** 캐릭터의 컴포넌트들*/
protected:
	// 각종 스탯 관리
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class UDSAttributeComponent> AttributeComponent;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class USpringArmComponent> SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class UCameraComponent> Camera;

#pragma region InputSystem
public:
	void Input_Move(const FInputActionValue& InputValue);
	void Input_Look(const FInputActionValue& InputValue);

	void Sprinting();
	void StopSprint();
	void Rolling();

protected:
	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputMappingContext> DefaultMappingContext;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> SprintRollingAction;
#pragma endregion
};
