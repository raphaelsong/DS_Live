
#include "Characters/DSEnemy.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/DSAttributeComponent.h"
#include "Components/DSStateComponent.h"
#include "Components/DSCombatComponent.h"
#include "Equipments/DSWeapon.h"
#include "DSDefine.h"
#include "GameplayTagContainer.h"
#include "Sound/SoundCue.h"
#include "Engine/DamageEvents.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "UI/DSStatBarWidget.h"
#include "DSGameplayTags.h"

ADSEnemy::ADSEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationYaw = false;
	//GetCharacterMovement()->RotationRate = FRotator(0.0, 360.0f, 0.0f);
	GetCharacterMovement()->bOrientRotationToMovement = true;

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);

	// 능력치 컴포넌트
	AttributeComponent = CreateDefaultSubobject<UDSAttributeComponent>(TEXT("Attribute"));

	// 죽음 Delegate 함수에 구독
	AttributeComponent->OnDeath.AddUObject(this, &ADSEnemy::OnDeath);

	// Health 값 갱신시 호출되도록 구독
	AttributeComponent->OnAttributeChanged.AddUObject(this, &ADSEnemy::OnEnemyAttributeChanged);

	// 상태 컴포넌트
	StateComponent = CreateDefaultSubobject<UDSStateComponent>(TEXT("State"));

	// 전투 컴포넌트
	CombatComponent = CreateDefaultSubobject<UDSCombatComponent>(TEXT("Combat"));

	// 체력 위젯 컴포넌트
	HealthBarWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthBarWidget"));
	HealthBarWidgetComponent->SetupAttachment(GetRootComponent());
	HealthBarWidgetComponent->SetRelativeLocation(FVector(0, 0, 100));
	HealthBarWidgetComponent->SetDrawSize(FVector2D(100.0f, 5.0f));
	HealthBarWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	HealthBarWidgetComponent->SetVisibility(false);
}

void ADSEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	SetupHealthBar();

	// 무기 장착
	if (DefaultWeaponClass)
	{
		if (CombatComponent)
		{
			CombatComponent->SetCombatEnabled(true);
		}

		FActorSpawnParameters SpawnParam;
		SpawnParam.Owner = this;

		ADSWeapon* Weapon = GetWorld()->SpawnActor<ADSWeapon>(DefaultWeaponClass, GetActorTransform(), SpawnParam);

		if (Weapon)
		{
			Weapon->EquipItem();
		}
	}
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

	ToggleHealthBarVisibility(true);

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
	ToggleHealthBarVisibility(false);

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

void ADSEnemy::SetupHealthBar()
{
	if (HealthBarWidgetComponent)
	{
		UDSStatBarWidget* StatBarWidget = Cast<UDSStatBarWidget>(HealthBarWidgetComponent->GetWidget());
		if (StatBarWidget)
		{
			StatBarWidget->SetStatBarColor(FLinearColor::Red);
		}
	}

	if (AttributeComponent)
	{
		AttributeComponent->BroadcastAttributeChanged(EDSAttributeType::Health);
	}
}

void ADSEnemy::ToggleHealthBarVisibility(bool IsVisibility)
{
	if (HealthBarWidgetComponent)
	{
		HealthBarWidgetComponent->SetVisibility(IsVisibility);
	}
}

void ADSEnemy::OnEnemyAttributeChanged(EDSAttributeType Attribute, float InValue)
{
	if (Attribute == EDSAttributeType::Health)
	{
		if (HealthBarWidgetComponent)
		{
			UDSStatBarWidget* StatBarWidget = Cast<UDSStatBarWidget>(HealthBarWidgetComponent->GetWidget());
			if (StatBarWidget)
			{
				StatBarWidget->SetRatio(InValue);
			}
		}
	}
}

void ADSEnemy::PerformAttack(FGameplayTag& AttackTag, FOnMontageEnded& MontageEndedDelegate)
{
	check(StateComponent);
	check(AttributeComponent);
	check(CombatComponent);

	ADSWeapon* Weapon = CombatComponent->GetMainWeapon();
	if (Weapon)
	{
		StateComponent->SetState(DSGameplayTags::Character_State_Attacking);
		
		AttributeComponent->ToggleStaminaRegen(false);

		Weapon->SetLastAttackType(AttackTag);

		UAnimMontage* Montage = Weapon->GetMontageForTag(AttackTag);
		if (Montage)
		{
			UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
			if (AnimInstance)
			{
				AnimInstance->Montage_Play(Montage);
				AnimInstance->Montage_SetEndDelegate(MontageEndedDelegate, Montage);
			}
		}

		const float StaminaCost = Weapon->GetStaminaCost(AttackTag);
		AttributeComponent->DecreaseStamina(StaminaCost);
		AttributeComponent->ToggleStaminaRegen(true, 1.5f);
	}
}

