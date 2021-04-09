// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


#include "AITypes.h"
#include "WheeledVehicle.h"
#include "Camera/CameraComponent.h"
#include "Components/TextBlock.h"
#include "GameFramework/SpringArmComponent.h"

#include "PawnBulldozer.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputComponent;
class USkeletalMesh;
class UTextBlock;
UCLASS()
class FRUITSALAD_API APawnBulldozer : public AWheeledVehicle
{
	GENERATED_BODY()

public:
	APawnBulldozer();

	virtual void Tick(float DeltaSeconds) override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	bool bInReverseGear;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* Camera;

	//Throttle and Steer
	void MoveForward(float Value);
	void MoveRight(float Value);

	//Break
	void OnHandbrakePressed();
	void OnHandbrakeReleased();

	//Look Around
	void LookUp(float Value);
	void LookRight(float Value);

	void UpdateInAirControl(float DeltaTime);
};
