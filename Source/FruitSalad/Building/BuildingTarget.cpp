// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildingTarget.h"

ABuildingTarget::ABuildingTarget()
{
}

void ABuildingTarget::BeginPlay()
{
	Super::BeginPlay();
	DestructibleComponent->SetRenderCustomDepth(true);
	DestructibleComponent->SetCustomDepthStencilValue(2);
}

void ABuildingTarget::Destroy(float Damage, FVector HitLocation, FVector ImpulseDir, float Impulse)
{
	Super::Destroy(Damage, HitLocation, ImpulseDir, Impulse);

	//get rid of outline material
	DestructibleComponent->SetCustomDepthStencilValue(0);
}
