// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/DSPickupItem.h"
#include "DSDefine.h"

// Sets default values
ADSPickupItem::ADSPickupItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);

	if (Mesh)
	{
		Mesh->SetCollisionObjectType(COLLISION_OBJECT_INTERACTION);
		Mesh->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
		Mesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	}
}

// Called when the game starts or when spawned
void ADSPickupItem::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADSPickupItem::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}

// Called every frame
void ADSPickupItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADSPickupItem::Interact(AActor* Interaction)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, TEXT("Pickup Item"));
}

