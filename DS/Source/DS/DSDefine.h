// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

// 디파인 관련
#define COLLISION_OBJECT_INTERACTION ECC_GameTraceChannel3

// 열거자 관련
UENUM(BlueprintType)
enum class EDSAttributeType : uint8
{
	Stamina,
	Health,
};