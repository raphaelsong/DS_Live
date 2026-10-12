// Fill out your copyright notice in the Description page of Project Settings.


#include "Test/DSBox.h"
#include <Components/BoxComponent.h>

// Sets default values
ADSBox::ADSBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	SetRootComponent(Box);
	
	if (Box)
	{
		Box->SetBoxExtent(FVector(100.0f, 100.0f, 100.0f));
		Box->SetHiddenInGame(false);
		Box->SetCollisionProfileName(UCollisionProfile::BlockAllDynamic_ProfileName);
	}
}

void ADSBox::BeginPlay()
{
	Super::BeginPlay();
	
	if (Box)
	{
		Box->OnComponentHit.AddDynamic(this, &ADSBox::OnBoxHit);
	}
}

void ADSBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADSBox::OnBoxHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	Destroy();
}

