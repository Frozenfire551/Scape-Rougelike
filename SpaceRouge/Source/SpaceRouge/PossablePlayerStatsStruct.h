// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "PossablePlayerStatsStruct.generated.h"
/**
 * 
 */

USTRUCT(BlueprintType)
struct FPlayerStatsStruct : public FTableRowBase
{
public:
	GENERATED_BODY()

		/** phylics Health Condition*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Playerstat")
		float MaxPHC;//phylics Health Coddions

	/** Mental Health Condition*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Playerstat")
		float MaxMHC;
	
	/** Soul Health Condition*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Playerstat")
		float MaxSHC;
};

USTRUCT(BlueprintType)
struct FAffintysStruct : public FTableRowBase
{
public:
	GENERATED_BODY()

		/** phylics Health Condition*/
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Playerstat")
		float Human = 100.0f;
};

UENUM(BlueprintType)
enum class ERaratiy : uint8 {
	Common       UMETA(DisplayName = "Common"),
	Uncommon       UMETA(DisplayName = "Uncommon"),
	Mutation        UMETA(DisplayName = "Mutation"),
	Rare       UMETA(DisplayName = "Rare"),
	Epic       UMETA(DisplayName = "Epic"),
	Legendary        UMETA(DisplayName = "Legendary"),
	Mythical        UMETA(DisplayName = "Mythical"),
	
};
USTRUCT(BlueprintType)
struct FAct_Ability : public FTableRowBase
{
public:
	GENERATED_BODY()

		/** phylics Health Condition*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Act_Ability")
		UTexture2D* Image;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Act_Ability")
		ERaratiy Raratiy;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Act_Ability")
		float Damage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Act_Ability")
		int MaxProjectile;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Act_Ability")
		float AttackSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Act_Ability")
		int NumberFireAttacks;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Act_Ability")
		bool projectile;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Act_Ability")
		float MovementSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Act_Ability")
		float Cooldown;

};