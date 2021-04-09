// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnBulldozer.h"
#include "Components/InputComponent.h"
#include "WheeledVehicleMovementComponent4W.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

APawnBulldozer::APawnBulldozer()
{
	
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}

void APawnBulldozer::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	bInReverseGear = GetVehicleMovement()->GetCurrentGear() < 0;

	UpdateInAirControl(DeltaSeconds);
}

void APawnBulldozer::BeginPlay()
{
	Super::BeginPlay();

	bInReverseGear = false;
}

void APawnBulldozer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	checkf(PlayerInputComponent, TEXT("PlayerInputComponent is not referenced."));

	PlayerInputComponent->BindAxis("MoveForward", this, &APawnBulldozer::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APawnBulldozer::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &APawnBulldozer::LookUp);
	PlayerInputComponent->BindAxis("LookRight", this, &APawnBulldozer::LookRight);

	PlayerInputComponent->BindAction("Handbrake", IE_Pressed, this, &APawnBulldozer::OnHandbrakePressed);
	PlayerInputComponent->BindAction("Handbrake", IE_Released, this, &APawnBulldozer::OnHandbrakeReleased);
	
}

void APawnBulldozer::MoveForward(float Value)
{
	GetVehicleMovementComponent()->SetThrottleInput(Value);
}

void APawnBulldozer::MoveRight(float Value)
{
	GetVehicleMovementComponent()->SetSteeringInput(Value);
}

void APawnBulldozer::OnHandbrakePressed()
{
	GetVehicleMovementComponent()->SetHandbrakeInput(true);
}

void APawnBulldozer::OnHandbrakeReleased()
{
	GetVehicleMovementComponent()->SetHandbrakeInput(false);
}

void APawnBulldozer::LookUp(float Value)
{
	if(Value != 0.0f)
	{
		AddControllerPitchInput(-Value);
	}
}

void APawnBulldozer::LookRight(float Value)
{
	if(Value != 0.0f)
	{
		AddControllerYawInput(Value);
	}
}

void APawnBulldozer::UpdateInAirControl(float DeltaTime)
{
	if(UWheeledVehicleMovementComponent4W* Vehicle4W = CastChecked<UWheeledVehicleMovementComponent4W>(GetVehicleMovement()))
	{
		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(this);

		const FVector TraceStart = GetActorLocation() + FVector(0.0f, 0.0f, 50.0f);
		const FVector TraceEnd = GetActorLocation() - FVector(0.0f, 0.0f, 200.0f);

		FHitResult Hit;

		//our we in the air
		const bool bInAir = !GetWorld()->LineTraceSingleByChannel(Hit, TraceStart, TraceEnd, ECC_Visibility, QueryParams);

		//dot product of up vector of bulldozer with up vector of world - check to see if we're flipped over
		const bool bNotGrounded = FVector::DotProduct(GetActorUpVector(), FVector::UpVector) < 0.1f;

		if(bInAir || bNotGrounded)
		{
			const float ForwardInput = InputComponent->GetAxisValue("MoveForward");
			const float RightInput = InputComponent->GetAxisValue("MoveRight");

			const float AirMovementForcePitch = 3.0f;
			const float AirMovementForceRoll = !bInAir && bNotGrounded ? 20.0f : 3.0f;

			if(UPrimitiveComponent* VehicleMesh = Vehicle4W->UpdatedPrimitive)
			{
				const FVector MovementVector = FVector(RightInput * -AirMovementForceRoll, ForwardInput * AirMovementForcePitch, 0.0f) * DeltaTime * 200.0f;
				const FVector NewAngularMovement = GetActorRotation().RotateVector(MovementVector);

				VehicleMesh->SetPhysicsAngularVelocityInDegrees(NewAngularMovement, true);
			}
		}
	}
}







