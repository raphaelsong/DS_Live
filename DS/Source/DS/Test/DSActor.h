// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DSActor.generated.h"

UCLASS()
class DS_API ADSActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADSActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY()
	TObjectPtr<class UDSObject> Obj;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 Hp = 100;

	UPROPERTY(BlueprintReadWrite)
	int32 Mp = 50;

	UPROPERTY(EditAnywhere)
	float Speed = 3.5f;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class UStaticMeshComponent> Box;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MoveSpeed = 50.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RotationRate = 45.0f;
};
