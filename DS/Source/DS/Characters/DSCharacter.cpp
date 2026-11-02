// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/DSCharacter.h"
#include "DSDefine.h"
#include "DSGameplayTags.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/DSAttributeComponent.h"
#include "Components/DSStateComponent.h"
#include "Components/DSCombatComponent.h"
#include "UI/DSPlayerHUDWidget.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Interface/DSItemInterface.h"
#include "Equipments/DSWeapon.h"
#include "Components/CapsuleComponent.h"
#include "Engine/DamageEvents.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Sound/SoundCue.h"

// Sets default values
ADSCharacter::ADSCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCharacterMovement()->MaxWalkSpeed = NormalSpeed;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.0f;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->TargetArmLength = 500.0f;
	SpringArm->SetRelativeRotation(FRotator(-30, 0, 0));

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	// 캐릭터 컴포넌트
	AttributeComponent = CreateDefaultSubobject<UDSAttributeComponent>(TEXT("Attribute"));
	AttributeComponent->OnDeath.AddUObject(this, &ADSCharacter::OnDeath);

	StateComponent = CreateDefaultSubobject<UDSStateComponent>(TEXT("State"));
	CombatComponet = CreateDefaultSubobject<UDSCombatComponent>(TEXT("Combat"));
}

// Called when the game starts or when spawned
void ADSCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController)
	{
		auto* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());

		if (Subsystem)
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	if (WBP_PlayerHUDWidget)
	{
		PlayerHUDWidget = CreateWidget<UDSPlayerHUDWidget>(GetWorld(), WBP_PlayerHUDWidget);

		if (PlayerHUDWidget)
		{
			PlayerHUDWidget->AddToViewport();
		}
	}
}

// Called every frame
void ADSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ADSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	auto* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (EnhancedInputComponent)
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ADSCharacter::Input_Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ADSCharacter::Input_Look);

		EnhancedInputComponent->BindAction(SprintRollingAction, ETriggerEvent::Triggered, this, &ADSCharacter::Sprinting);
		EnhancedInputComponent->BindAction(SprintRollingAction, ETriggerEvent::Completed, this, &ADSCharacter::StopSprint);
		EnhancedInputComponent->BindAction(SprintRollingAction, ETriggerEvent::Canceled, this, &ADSCharacter::Rolling);
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &ADSCharacter::Interact);
		EnhancedInputComponent->BindAction(ToggleCombatAction, ETriggerEvent::Triggered, this, &ADSCharacter::ToggleCombat);

		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Canceled, this, &ADSCharacter::ComboAttack);
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Triggered, this, &ADSCharacter::SpecialAttack);
	}
}

float ADSCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (AttributeComponent)
	{
		AttributeComponent->TakeDamageAmount(ActualDamage);
	}

	StateComponent->SetState(DSGameplayTags::Character_State_Hit);
	StateComponent->ToggleMovementInput(false);

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

void ADSCharacter::OnDeath()
{
	// 충돌 예외 처리
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// Ragdoll
	GetMesh()->SetCollisionProfileName("Ragdoll");
	GetMesh()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetMesh()->SetSimulatePhysics(true);
}

void ADSCharacter::ImpactEffect(const FVector& Location)
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

void ADSCharacter::HitReaction(const AActor* Attacker)
{
	UAnimMontage* HitReactAnimMontage = GetHitReactAnimation(Attacker);
	if (HitReactAnimMontage)
	{
		float DelaySeconds = PlayAnimMontage(HitReactAnimMontage);
	}
}

UAnimMontage* ADSCharacter::GetHitReactAnimation(const AActor* Attacker) const
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


bool ADSCharacter::IsMoving()
{
	UCharacterMovementComponent* MovementComp = GetCharacterMovement();
	if (MovementComp)
	{
		return MovementComp->Velocity.Size2D() > 3.0f && MovementComp->GetCurrentAcceleration() != FVector::ZeroVector;
	}

	return false;
}

bool ADSCharacter::IsSpringing()
{
	return bSprinting;
}

bool ADSCharacter::CanToggleCombat() const
{
	check(StateComponent);

	FGameplayTagContainer CheckTags;
	CheckTags.AddTag(DSGameplayTags::Character_State_Attacking);
	CheckTags.AddTag(DSGameplayTags::Character_State_Rolling);
	CheckTags.AddTag(DSGameplayTags::Character_State_GeneralAction);

	return (StateComponent->IsCurrentStateEqualToAny(CheckTags) == false);
}

bool ADSCharacter::CanPerformAttack(const FGameplayTag& AttackTypeTag) const
{
	check(StateComponent);
	check(AttributeComponent);
	check(CombatComponet);

	if (IsValid(CombatComponet->GetMainWeapon()) == false)
	{
		return false;
	}

	FGameplayTagContainer CheckTags;
	CheckTags.AddTag(DSGameplayTags::Character_State_Rolling);
	CheckTags.AddTag(DSGameplayTags::Character_State_GeneralAction);
	CheckTags.AddTag(DSGameplayTags::Character_State_Hit);

	const float StaminaCost = CombatComponet->GetMainWeapon()->GetStaminaCost(AttackTypeTag);

	return StateComponent->IsCurrentStateEqualToAny(CheckTags) == false
		&& CombatComponet->IsCombatEnabled()
		&& AttributeComponent->CheckHasEnoughStamina(StaminaCost);
}

void ADSCharacter::ExecuteComboAttack(const FGameplayTag& AttackTypeTag)
{
	check(StateComponent);

	if (StateComponent->GetState() != DSGameplayTags::Character_State_Attacking)
	{
		ResetCombo();

		DoAttack(AttackTypeTag);
	}
	else if (bCanComboInput)
	{
		bSavedComboInput = true;
	}
}

void ADSCharacter::DoAttack(const FGameplayTag& AttackTypeTag)
{
	check(StateComponent);
	check(CombatComponet);
	check(AttributeComponent);

	ADSWeapon* Weapon = CombatComponet->GetMainWeapon();
	if (Weapon)
	{
		StateComponent->SetState(DSGameplayTags::Character_State_Attacking);
		StateComponent->ToggleMovementInput(false);

		UAnimMontage* Montage = Weapon->GetMontageForTag(AttackTypeTag, ComboCounter);
		if (Montage == nullptr)
		{
			ComboCounter = 0;
			Montage = Weapon->GetMontageForTag(AttackTypeTag, ComboCounter);
		}

		PlayAnimMontage(Montage);

		Weapon->SetLastAttackType(AttackTypeTag);

		const float StaminaCost = Weapon->GetStaminaCost(AttackTypeTag);

		AttributeComponent->DecreaseStamina(StaminaCost);
		AttributeComponent->ToggleStaminaRegen(false);
		AttributeComponent->ToggleStaminaRegen(true, 1.5f);
	}
}

void ADSCharacter::ResetCombo()
{
	bCanComboInput = false;
	bSavedComboInput = false;
	ComboCounter = 0;
}

void ADSCharacter::EnableComboWindow()
{
	bCanComboInput = true;
}

void ADSCharacter::DisableComboWindow()
{
	bCanComboInput = false;

	if (bSavedComboInput)
	{
		bSavedComboInput = false;
		ComboCounter++;
		DoAttack(DSGameplayTags::Character_Attack_Light);
	}
}

void ADSCharacter::Input_Move(const FInputActionValue& InputValue)
{
	check(StateComponent);

	if (StateComponent->MovementInputEnabled() == false)
	{
		return;
	}

	FVector2D MovementVector = InputValue.Get<FVector2D>();

	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation = FRotator(0, Rotation.Yaw, 0);

	const FVector ForwardVector = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightVector = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(ForwardVector, MovementVector.X);
	AddMovementInput(RightVector, MovementVector.Y);
}

void ADSCharacter::Input_Look(const FInputActionValue& InputValue)
{
	FVector2D LookVector = InputValue.Get<FVector2D>();

	AddControllerYawInput(LookVector.X);
	AddControllerPitchInput(LookVector.Y);
}

void ADSCharacter::Sprinting()
{
	check(AttributeComponent);
	if (AttributeComponent->CheckHasEnoughStamina(BaseStaminaCost) && IsMoving())
	{
		GetCharacterMovement()->MaxWalkSpeed = SprintingSpeed;

		AttributeComponent->DecreaseStamina(BaseStaminaCost);

		AttributeComponent->ToggleStaminaRegen(false);
	}
	else
	{
		StopSprint();
	}
}

void ADSCharacter::StopSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = NormalSpeed;

	check(AttributeComponent);

	AttributeComponent->ToggleStaminaRegen(true);
}

void ADSCharacter::Rolling()
{
	check(AttributeComponent);
	check(StateComponent);

	// 롤링 중 롤링 금지
	FGameplayTagContainer RollingTag;
	RollingTag.AddTag(DSGameplayTags::Character_State_Rolling);
	if (StateComponent->IsCurrentStateEqualToAny(RollingTag))
	{
		return;
	}

	if (AttributeComponent->CheckHasEnoughStamina(RollingStaminaCost))
	{
		// 이동 입력 처리 무시
		StateComponent->ToggleMovementInput(false);

		// 롤링 상태 설정
		StateComponent->SetState(DSGameplayTags::Character_State_Rolling);

		// 스태미나 충전 멈춤
		AttributeComponent->ToggleStaminaRegen(false);

		// 스태미나 차감
		AttributeComponent->DecreaseStamina(RollingStaminaCost);

		// 롤링 애니메이션 재생(AM_Rolling_Forward)
		PlayAnimMontage(RollingMontage);

		// 스태미나 충전 시작
		AttributeComponent->ToggleStaminaRegen(true);
	}
}

void ADSCharacter::Interact()
{
	FHitResult OutHit;
	const FVector Start = GetActorLocation();
	const FVector End = Start;
	const float Radius = 100.0f;

	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(COLLISION_OBJECT_INTERACTION));

	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(this);

	bool bHit = UKismetSystemLibrary::SphereTraceSingleForObjects(
		this,
		Start,
		End,
		Radius,
		ObjectTypes,
		false,
		ActorsToIgnore,
		EDrawDebugTrace::ForDuration,
		OutHit,
		true
	);

	if (bHit)
	{
		AActor* HitActor = OutHit.GetActor();
		if (HitActor)
		{
			IDSItemInterface* Interaction = Cast<IDSItemInterface>(HitActor);
			if (Interaction)
			{
				Interaction->Interact(this);
			}
		}
	}
}

void ADSCharacter::ToggleCombat()
{
	check(CombatComponet);
	check(StateComponent);

	const ADSWeapon* Weapon = CombatComponet->GetMainWeapon();
	if (Weapon)
	{
		if (CanToggleCombat())
		{
			StateComponent->SetState(DSGameplayTags::Character_State_GeneralAction);

			if (CombatComponet->IsCombatEnabled())
			{
				PlayAnimMontage(Weapon->GetUnequipMontage());
			}
			else
			{
				PlayAnimMontage(Weapon->GetEquipMontage());
			}
		}
	}
}

void ADSCharacter::ComboAttack()
{
	const FGameplayTag AttackTypeTag = DSGameplayTags::Character_Attack_Light;
	if (CanPerformAttack(AttackTypeTag))
	{
		ExecuteComboAttack(AttackTypeTag);
	}
}

void ADSCharacter::SpecialAttack()
{
	const FGameplayTag AttackTypeTag = DSGameplayTags::Character_Attack_Special;
	if (CanPerformAttack(AttackTypeTag))
	{
		ExecuteComboAttack(AttackTypeTag);
	}
}

