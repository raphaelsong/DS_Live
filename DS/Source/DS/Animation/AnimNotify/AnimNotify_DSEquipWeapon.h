// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_DSEquipWeapon.generated.h"

/**
 * 
 */
UCLASS()
class DS_API UAnimNotify_DSEquipWeapon : public UAnimNotify
{
	GENERATED_BODY()
	
public:
	UAnimNotify_DSEquipWeapon();

public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bToggleEquip;
};
