// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PossablePlayerStatsStruct.h"
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

	//TArray<FAct_Ability> PossableAttacks;
	//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DataTable")
	//	FAct_Ability PlayerrActSkills_Structs;
	TArray <FAct_Ability*> PlayerrActSkills_Structs;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DataTable")
	UDataTable* PlayerActSkills_DT;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "skills")
	TArray<float> SKillcooldown;
	TMap<int, float> SkillsOnCooldown;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	DECLARE_DELEGATE_OneParam(Skill, int32);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//
	void addSkill(int _skillLoctation,FName _skillName);

	//inputs functions
	void MoveRight(float Value);
	void MoveForward(float Value);
	void UseSkill(int Value);
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//
	UFUNCTION(BlueprintImplementableEvent)
		void UISetup(UTexture2D* SkillChangeImage);
	//
	UFUNCTION(BlueprintImplementableEvent)
		void UIChange(int SkillChange, UTexture2D* SkillChangeImage);
	
	
	//skill changed or got added
	UFUNCTION(BlueprintImplementableEvent)
		void UIAddSkill( UTexture2D* SkillChangeImage, int _skill);
	//skill was used and its cooldown
	UFUNCTION(BlueprintImplementableEvent)
		void UIUseSkill(int _skill, float _Skillcooldown);
	//skill new cooldown
	UFUNCTION(BlueprintImplementableEvent)
		void UIUpdateCooldownOnSkill(int _skill, float _Skillcooldown);
	//skill off cooldown
	UFUNCTION(BlueprintImplementableEvent)
		void UISkillOffCooldown(int _skill);
	
};
