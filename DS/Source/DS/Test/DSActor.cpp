// Fill out your copyright notice in the Description page of Project Settings.


#include "Test/DSActor.h"
#include "Test/DSObject.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ADSActor::ADSActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Box = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Box"));
	SetRootComponent(Box);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> BoxMeshRef(TEXT("/Script/Engine.StaticMesh'/Game/LevelPrototyping/Meshes/SM_ChamferCube.SM_ChamferCube'"));

	if (BoxMeshRef.Succeeded())
	{
		Box->SetStaticMesh(BoxMeshRef.Object);
	}
}

// Called when the game starts or when spawned
void ADSActor::BeginPlay()
{
	Super::BeginPlay();
	
	Obj = NewObject<UDSObject>();
}

// Called every frame
void ADSActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//FVector Location = GetActorLocation();
	//FVector NewLocation = Location + FVector::ForwardVector * DeltaTime * MoveSpeed;
	//SetActorLocation(NewLocation);

	AddActorWorldOffset(FVector::ForwardVector * DeltaTime * MoveSpeed);

	//FRotator Rotate = GetActorRotation();
	//FRotator NewRotate = FRotator(Rotate.Pitch, Rotate.Yaw + RotationRate * DeltaTime, Rotate.Roll);
	//SetActorRotation(NewRotate);

	AddActorWorldRotation(FRotator(0, RotationRate * DeltaTime, 0));
}

