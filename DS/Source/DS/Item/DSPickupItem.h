// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/DSItemInterface.h"
#include "DSPickupItem.generated.h"

UCLASS()
class DS_API ADSPickupItem : public AActor, public IDSItemInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADSPickupItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Transform) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	virtual void Interact(AActor* Interaction) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Item)
	TObjectPtr<class UStaticMeshComponent> Mesh;
};
