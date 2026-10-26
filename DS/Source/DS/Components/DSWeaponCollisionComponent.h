// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "DSWeaponCollisionComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnHitActorDelegate, const FHitResult&);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DS_API UDSWeaponCollisionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDSWeaponCollisionComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

/** Collision Section */
public:
	void AddIgnoreActor(AActor* AddActor);
	void RemoveIgnoreActor(AActor* RemoveActor);

	bool CanHitActor(AActor* InActor) const;

	void TurnOnCollision();
	void TurnOffCollision();

	void CollisionTrace();

public:
	FOnHitActorDelegate OnHitActor;

protected:
	// 반지름
	UPROPERTY(EditAnywhere)
	float TraceRadius = 20.0f;

	// Trace 대상 ObjectType
	UPROPERTY(EditAnywhere)
	TArray<TEnumAsByte<EObjectTypeQuery>> TraceObjectTypes;

	// 충돌 예외 처리 Actors
	UPROPERTY(EditAnywhere)
	TArray<AActor*> IgnoreActors;

	// 디버그 드로우 타입
	UPROPERTY(EditAnywhere)
	TEnumAsByte<EDrawDebugTrace::Type> DrawDebugType = EDrawDebugTrace::ForDuration;

	// 충돌 발생 액터 예외 처리
	UPROPERTY()
	TArray<AActor*> AlreadyHitActors;

	// 충돌 체크 활성화
	bool bIsCollisionEnabled = false;

/** Mesh Component */
public:
	FORCEINLINE void SetWeaponMesh(UPrimitiveComponent* MeshComponent)
	{
		WeaponMesh = MeshComponent;
	}

protected:
	UPROPERTY()
	TObjectPtr<UPrimitiveComponent> WeaponMesh;

	// 시작 소켓
	UPROPERTY(EditAnywhere)
	FName TraceStartSocketName;

	// 끝 소켓
	UPROPERTY(EditAnywhere)
	FName TraceEndSocketName;
};
