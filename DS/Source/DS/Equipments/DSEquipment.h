// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DSEquipment.generated.h"

UCLASS()
class DS_API ADSEquipment : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADSEquipment();

protected:
	virtual void OnConstruction(const FTransform& Transform) override;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	virtual void EquipItem();
	virtual void UnequipItem();

	virtual void AttachToOwner(FName SocketName);

public:
	FORCEINLINE UStaticMesh* GetMeshAsset() { return MeshAsset; }

protected:
	UPROPERTY(VisibleAnywhere, Category = "Equipment | Mesh")
	TObjectPtr<UStaticMeshComponent> Mesh;

	UPROPERTY(EditAnywhere, Category = "Equipment | Mesh")
	TObjectPtr<UStaticMesh> MeshAsset;
};
