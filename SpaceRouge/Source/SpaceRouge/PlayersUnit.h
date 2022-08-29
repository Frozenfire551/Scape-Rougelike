// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PossablePlayerStatsStruct.h"
#include "PlayersUnit.generated.h"

class USkeletalMeshComponent;
class UCameraComponent;
class USpringArmComponent;
UCLASS()
class SPACEROUGE_API APlayersUnit : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayersUnit();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerMesh")
		USkeletalMeshComponent* PlayerMeshCom;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
		USpringArmComponent* SpringArmCom;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
		UCameraComponent* CameraCom;

	TArray<FAct_Ability> PossableAttacks;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void MoveRight(float Value);
	void MoveForward(float Value);
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
