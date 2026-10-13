// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipments/DSEquipment.h"
#include <GameFramework/Character.h>

// Sets default values
ADSEquipment::ADSEquipment()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);

	if (Mesh)
	{
		Mesh->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);
	}
}

void ADSEquipment::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	if (Mesh && MeshAsset)
	{
		Mesh->SetStaticMesh(MeshAsset);
	}
}

// Called when the game starts or when spawned
void ADSEquipment::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADSEquipment::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADSEquipment::EquipItem()
{
}

void ADSEquipment::UnequipItem()
{
}

void ADSEquipment::AttachToOwner(FName SocketName)
{
	ACharacter* OwnerCharacter = Cast<ACharacter>(GetOwner());
	if (OwnerCharacter)
	{
		USkeletalMeshComponent* CharacterMesh = OwnerCharacter->GetMesh();
		if (CharacterMesh)
		{
			AttachToComponent(CharacterMesh, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), SocketName);
		}
	}
}

