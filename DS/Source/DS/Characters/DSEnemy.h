// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DSDefine.h"
#include "GameFramework/Character.h"
#include "DSEnemy.generated.h"

class ATargetPoint;

UCLASS()
class DS_API ADSEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADSEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

public:
	virtual void OnDeath();

public:
	void ImpactEffect(const FVector& Location);
	void HitReaction(const AActor* Attacker);
	UAnimMontage* GetHitReactAnimation(const AActor* Attacker) const;

public:
	void SetupHealthBar();

	void ToggleHealthBarVisibility(bool IsVisibility);

	void OnEnemyAttributeChanged(EDSAttributeType Attribute, float InValue);


public:
	FORCEINLINE ATargetPoint* GetPatrolPoint()
	{
		return PatrolPoints.Num() >= (PatrolIndex + 1) ? PatrolPoints[PatrolIndex] : nullptr;
	}

	FORCEINLINE void IncrementPatrolIndex()
	{
		PatrolIndex = (PatrolIndex + 1) % PatrolPoints.Num();
	}

protected:
	UPROPERTY(EditAnywhere, Category = "AI | Patrol")
	TArray<ATargetPoint*> PatrolPoints;

	UPROPERTY(VisibleAnywhere, Category = "AI | Patrol")
	int32 PatrolIndex = 0;

protected:
	UPROPERTY(EditAnywhere, Category = "Effect")
	TObjectPtr<USoundCue> ImpactSound;

	UPROPERTY(EditAnywhere, Category = "Effect")
	TObjectPtr<UParticleSystem> ImpactParticle;

protected:
	UPROPERTY(EditAnywhere, Category = "Montage | HitReact")
	TObjectPtr<UAnimMontage> HitReactFrontAnimation;

	UPROPERTY(EditAnywhere, Category = "Montage | HitReact")
	TObjectPtr<UAnimMontage> HitReactBackAnimation;
	
	UPROPERTY(EditAnywhere, Category = "Montage | HitReact")
	TObjectPtr<UAnimMontage> HitReactLeftAnimation;
	
	UPROPERTY(EditAnywhere, Category = "Montage | HitReact")
	TObjectPtr<UAnimMontage> HitReactRightAnimation;

protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UDSAttributeComponent> AttributeComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UDSStateComponent> StateComponent;

protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UWidgetComponent> HealthBarWidgetComponent;
};
