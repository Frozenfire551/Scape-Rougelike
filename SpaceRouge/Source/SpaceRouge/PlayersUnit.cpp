// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayersUnit.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/DataTable.h"


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
}

// Called when the game starts or when spawned
void APlayersUnit::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayersUnit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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

// Called to bind functionality to input
void APlayersUnit::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveRight", this, &APlayersUnit::MoveRight);
	PlayerInputComponent->BindAxis("MoveForward", this, &APlayersUnit::MoveForward);
}

