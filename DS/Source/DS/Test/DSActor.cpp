// Fill out your copyright notice in the Description page of Project Settings.


#include "Test/DSActor.h"

// Sets default values
ADSActor::ADSActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADSActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADSActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

