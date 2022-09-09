// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayersUnit.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/DataTable.h"
#include "Engine/GameEngine.h"


// Sets default values
APlayersUnit::APlayersUnit()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PlayerMeshCom = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("PlayerMeshCom"));
	PlayerMeshCom->SetupAttachment(RootComponent);

	SpringArmCom = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmCom"));
	SpringArmCom->SetupAttachment(PlayerMeshCom);

	CameraCom = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraCom"));
	CameraCom->SetupAttachment(SpringArmCom);

	static ConstructorHelpers::FObjectFinder<UDataTable> DT_ActiveAbility(TEXT("DataTable'/Game/DT_ActiveAbility.DT_ActiveAbility'"));
	if (DT_ActiveAbility.Succeeded())
	{
		PlayerActSkills_DT = DT_ActiveAbility.Object;
	}
	SKillcooldown.SetNum(6);
}

// Called when the game starts or when spawned
void APlayersUnit::BeginPlay()
{
	Super::BeginPlay();

	PlayerrActSkills_Structs.SetNum(5);
	
	addSkill(0,"Attack");
	//addSkill(1, "Ice");
	//addSkill(2, "Mult");
	//addSkill(3, "Spirt");
	//addSkill(4, "Lighting");
}

// Called every frame
void APlayersUnit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (SkillsOnCooldown.Num() != 0)
	{
		
		for (auto Elem = SkillsOnCooldown.CreateConstIterator(); Elem;)
		{
			if (Elem.Value() - DeltaTime <= 0)
			{
				UISkillOffCooldown(Elem.Key());
				SkillsOnCooldown.Remove(Elem.Key());
				if (GEngine) {

					GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Remove %f"), Elem.Key()));
				}
				//skill off cooldown (good to use)
			
		//		//
			}
			else
			{
				//still on cooldown
				SkillsOnCooldown[Elem.Key()] = Elem.Value()- DeltaTime;
				UIUpdateCooldownOnSkill(Elem.Key(), Elem.Value() - DeltaTime);
				GEngine->AddOnScreenDebugMessage(-1, 0.3f, FColor::Yellow, FString::Printf(TEXT("%f"), Elem.Value() - DeltaTime));
			}
			++Elem;
		}

		/*for (auto Elem : SkillsOnCooldown)
		{
			SkillsOnCooldown[Elem.Key] = Elem.Value - DeltaTime;
			UIUpdateCooldownOnSkill(Elem.Key, Elem.Value - DeltaTime);
			if (GEngine) {

				//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("%f"), Elem.Value - DeltaTime));
			}
		}*/
	}

}
void APlayersUnit::addSkill(int _skillLoctation, FName _skillName)
{
	if (PlayerActSkills_DT)
	{
		
		static const FString ContextString(TEXT("Act_Ability Context"));
		PlayerrActSkills_Structs[_skillLoctation] = 
			PlayerActSkills_DT->FindRow<FAct_Ability>(_skillName, ContextString, true);
		
		if (PlayerrActSkills_Structs[_skillLoctation])
		{
			UTexture2D* Image = PlayerrActSkills_Structs[_skillLoctation]->Image;
			UIAddSkill(Image, _skillLoctation);
			
			UseSkill(_skillLoctation);
			if (GEngine) {

				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, FString::Printf(TEXT("%f"), PlayerrActSkills_Structs[_skillLoctation]->Cooldown));

				//float g = PlayerrActSkills_Structs->Damage;
				//FString Message = FString::Printf(TEXT("%s"),
				//	(PlayerrActSkills_Structs->Image));
				//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, FString::Printf(TEXT("%f"), SKillcooldown.Num()));
				//UE_LOG(LogTemp, Warning, TEXT("The Actor's name is %s"), *YourActor->GetName());
			}
		}
	}
}
void APlayersUnit::MoveRight(float Value)
{
	if ((Controller) && (Value != 0.0f))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}
void APlayersUnit::MoveForward(float Value)
{
	if ((Controller) && (Value != 0.0f))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);

	}
}

void APlayersUnit::UseSkill(int Value)
{
	//if skill is empty : return;
	//SKillcooldown[Value] = PlayerrActSkills_Structs->Cooldown;

	if (SkillsOnCooldown.Num() > 0)
	{
		if (!SkillsOnCooldown.FindKey(Value))
		{
			//can't used skill
			if (GEngine) {

				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, 
					FString::Printf(TEXT("skill %f is on cooldown"), Value));
			}
			return;
		}
	}

	UIUseSkill(Value, PlayerrActSkills_Structs[Value]->Cooldown);
	SkillsOnCooldown.Add(Value, PlayerrActSkills_Structs[Value]->Cooldown);

	//do skill

}

// Called to bind functionality to input
void APlayersUnit::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveRight", this, &APlayersUnit::MoveRight);
	PlayerInputComponent->BindAxis("MoveForward", this, &APlayersUnit::MoveForward);
	
	PlayerInputComponent->BindAction<Skill>("skill1", IE_Pressed, this, &APlayersUnit::UseSkill,0);
	PlayerInputComponent->BindAction<Skill>("skill2", IE_Pressed, this, &APlayersUnit::UseSkill, 1);
	PlayerInputComponent->BindAction<Skill>("skill3", IE_Pressed, this, &APlayersUnit::UseSkill, 2);
	PlayerInputComponent->BindAction<Skill>("skill4", IE_Pressed, this, &APlayersUnit::UseSkill, 3);
	PlayerInputComponent->BindAction<Skill>("skill5", IE_Pressed, this, &APlayersUnit::UseSkill, 4);
}

