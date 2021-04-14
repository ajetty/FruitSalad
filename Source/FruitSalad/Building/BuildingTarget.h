// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "BuildingBase.h"
#include "BuildingTarget.generated.h"

/**
 * 
 */
UCLASS()
class FRUITSALAD_API ABuildingTarget : public ABuildingBase
{
	GENERATED_BODY()
public:
	ABuildingTarget();

	virtual void BeginPlay() override;

	virtual void Destroy(float Damage, FVector HitLocation, FVector ImpulseDir, float Impulse) override;
	
protected:
	
private:
	
};
