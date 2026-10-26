// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/DSWeaponCollisionComponent.h"

// Sets default values for this component's properties
UDSWeaponCollisionComponent::UDSWeaponCollisionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	TraceStartSocketName = FName("WeaponStart");
	TraceEndSocketName = FName("WeaponEnd");

	TraceObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));
}


// Called when the game starts
void UDSWeaponCollisionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UDSWeaponCollisionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bIsCollisionEnabled)
	{
		CollisionTrace();
	}
}

void UDSWeaponCollisionComponent::AddIgnoreActor(AActor* AddActor)
{
	IgnoreActors.Add(AddActor);
}

void UDSWeaponCollisionComponent::RemoveIgnoreActor(AActor* RemoveActor)
{
	IgnoreActors.Remove(RemoveActor);
}

bool UDSWeaponCollisionComponent::CanHitActor(AActor* InActor) const
{
	return AlreadyHitActors.Contains(InActor) == false;
}

void UDSWeaponCollisionComponent::TurnOnCollision()
{
	AlreadyHitActors.Empty();
	bIsCollisionEnabled = true;
}

void UDSWeaponCollisionComponent::TurnOffCollision()
{
	bIsCollisionEnabled = false;
}

void UDSWeaponCollisionComponent::CollisionTrace()
{
	check(WeaponMesh);

	TArray<FHitResult> OutHitResults;

	const FVector Start = WeaponMesh->GetSocketLocation(TraceStartSocketName);
	const FVector End = WeaponMesh->GetSocketLocation(TraceEndSocketName);

	bool bHit = UKismetSystemLibrary::SphereTraceMultiForObjects(
		GetOwner(),
		Start,
		End,
		TraceRadius,
		TraceObjectTypes,
		false,
		IgnoreActors,
		DrawDebugType,
		OutHitResults,
		true);

	if (bHit)
	{
		for (const FHitResult& HitResult : OutHitResults)
		{
			AActor* HitActor = HitResult.GetActor();
			if (HitActor == nullptr)
			{
				continue;
			}

			if (CanHitActor(HitActor))
			{
				AlreadyHitActors.Add(HitActor);

				// Call OnHitActor Broadcast
				if (OnHitActor.IsBound())
				{
					OnHitActor.Broadcast(HitResult);
				}
			}
		}
	}
}

