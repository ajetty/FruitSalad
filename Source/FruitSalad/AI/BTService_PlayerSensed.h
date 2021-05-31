// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "FruitSalad/Bulldozer/PawnBulldozer.h"
#include "Perception/AISenseConfig_Sight.h"

#include "BTService_PlayerSensed.generated.h"

/**
 * 
 */
UCLASS()
class FRUITSALAD_API UBTService_PlayerSensed : public UBTService_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UBTService_PlayerSensed();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	APawnBulldozer *Player;
};
