// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindNavigableLocation.h"

#include "AIController.h"
#include "NavigationSystem.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "FruitSalad/Fruit/CharacterFruitBase.h"

UBTTask_FindNavigableLocation::UBTTask_FindNavigableLocation()
{

}

EBTNodeResult::Type UBTTask_FindNavigableLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	float radius = 1000.0f;

	ACharacterFruitBase* FruitCharacter = Cast<ACharacterFruitBase>(OwnerComp.GetAIOwner()->GetPawn());

	UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());

	FVector RandomPointInRadius;

	bool bLocationSuccess = NavSys->K2_GetRandomReachablePointInRadius(GetWorld(), FruitCharacter->GetActorLocation(), RandomPointInRadius, radius);

	if(bLocationSuccess)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(TEXT("TargetMoveLocation"), RandomPointInRadius);
	}
	else
	{
		OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
		return EBTNodeResult::Failed;
	}

	return EBTNodeResult::Succeeded;
}
