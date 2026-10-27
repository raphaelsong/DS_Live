
#include "Characters/DSEnemy.h"
#include "Components/CapsuleComponent.h"
#include "Components/DSAttributeComponent.h"
#include "Components/DSStateComponent.h"
#include "DSDefine.h"
#include "GameplayTagContainer.h"
#include "Sound/SoundCue.h"
#include "Engine/DamageEvents.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

ADSEnemy::ADSEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);

	// 능력치 컴포넌트
	AttributeComponent = CreateDefaultSubobject<UDSAttributeComponent>(TEXT("Attribute"));

	// 죽음 Delegate 함수에 구독
	AttributeComponent->OnDeath.AddUObject(this, &ADSEnemy::OnDeath);

	// 상태 컴포넌트
	StateComponent = CreateDefaultSubobject<UDSStateComponent>(TEXT("State"));
}

void ADSEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADSEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ADSEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float ADSEnemy::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (AttributeComponent)
	{
		AttributeComponent->TakeDamageAmount(ActualDamage);
	}

	if (DamageEvent.IsOfType(FPointDamageEvent::ClassID))
	{
		const FPointDamageEvent* PointDamageEvent = static_cast<const FPointDamageEvent*>(&DamageEvent);

		// 데미지 방향
		FVector ShotDirection = PointDamageEvent->ShotDirection;

		// 히트 위치
		FVector ImpactPoint = PointDamageEvent->HitInfo.ImpactPoint;

		// 히트 방향
		FVector ImpactDirection = PointDamageEvent->HitInfo.ImpactNormal;

		// 히트한 객체의 위치
		FVector HitLocation = PointDamageEvent->HitInfo.Location;

		ImpactEffect(ImpactPoint);
		HitReaction(EventInstigator->GetPawn());
	}

	return ActualDamage;
}

void ADSEnemy::OnDeath()
{
	// 충돌 예외 처리
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// Ragdoll
	GetMesh()->SetCollisionProfileName("Ragdoll");
	GetMesh()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetMesh()->SetSimulatePhysics(true);
}

void ADSEnemy::ImpactEffect(const FVector& Location)
{
	if (ImpactSound)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), ImpactSound, Location);
	}

	if (ImpactParticle)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactParticle, Location);
	}
}

void ADSEnemy::HitReaction(const AActor* Attacker)
{
	UAnimMontage* HitReactAnimMontage = GetHitReactAnimation(Attacker);
	if (HitReactAnimMontage)
	{
		float DelaySeconds = PlayAnimMontage(HitReactAnimMontage);
	}
}

UAnimMontage* ADSEnemy::GetHitReactAnimation(const AActor* Attacker) const
{
	// 현재 액터가 공격자를 바라보는 회전값
	const FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), Attacker->GetActorLocation());

	// 현재 액터의 회전값과 LookAt 회전값의 차이
	const FRotator DeltaRotation = UKismetMathLibrary::NormalizedDeltaRotator(GetActorRotation(), LookAtRotation);

	// Yaw 회전
	const float DeltaYaw = DeltaRotation.Yaw;

	EHitDirection HitDirection = EHitDirection::Front;
	if (UKismetMathLibrary::InRange_FloatFloat(DeltaYaw, -45.0f, 45.0f))
	{
		HitDirection = EHitDirection::Front;
	}
	else if (UKismetMathLibrary::InRange_FloatFloat(DeltaYaw, 45.0f, 135.0f))
	{
		HitDirection = EHitDirection::Left;
	}
	else if (UKismetMathLibrary::InRange_FloatFloat(DeltaYaw, 135.0f, 180.0f) ||
			 UKismetMathLibrary::InRange_FloatFloat(DeltaYaw, -180.0f, -135.0f))
	{
		HitDirection = EHitDirection::Back;
	}
	else
	{
		HitDirection = EHitDirection::Right;
	}

	UAnimMontage* SelectedMontage = nullptr;
	switch (HitDirection)
	{
	case EHitDirection::Front:
		SelectedMontage = HitReactFrontAnimation;
		break;
	case EHitDirection::Back:
		SelectedMontage = HitReactBackAnimation;
		break;
	case EHitDirection::Left:
		SelectedMontage = HitReactLeftAnimation;
		break;
	case EHitDirection::Right:
		SelectedMontage = HitReactRightAnimation;
		break;
	default:
		break;
	}

	return SelectedMontage;

}

