// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindNavigableLocation.h"
#include "AIController.h"
#include "DrawDebugHelpers.h"
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

	//npc and nav system 
	ACharacterFruitBase* FruitCharacter = Cast<ACharacterFruitBase>(OwnerComp.GetAIOwner()->GetPawn());

	UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());

	//reachable point radius, random point vector, location success bool returned from function K2_GetRandomReachablePointInRadius, collision params, vector hit result
	float radius = 1000.0f;
	
	FVector RandomPointInRadius = FVector(0.0f, 0.0f, 0.0f);

	bool bLocationSuccess = false;

	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(FruitCharacter);

	FHitResult OutHit;
	
	//calculate a random point that doesn't hit any other object within radius
	do
	{
		bLocationSuccess = NavSys->K2_GetRandomReachablePointInRadius(GetWorld(), FruitCharacter->GetActorLocation(), RandomPointInRadius, radius);

		FVector ForwardVector = FruitCharacter->GetActorForwardVector();
		FVector EndVector = RandomPointInRadius;

		// if(FruitCharacter->ActorLineTraceSingle(OutHit, FruitCharacter->GetActorLocation(), RandomPointInRadius, ECC_WorldStatic, CollisionParams))
		// {
		// 	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Green, FString::Printf(TEXT("The component being hit %s"), *OutHit.GetComponent()->GetName()));
		// }

		if(GetWorld()->LineTraceSingleByChannel(OutHit, FruitCharacter->GetActorLocation(), RandomPointInRadius, ECollisionChannel::ECC_GameTraceChannel1, CollisionParams))
		{
			//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, FString::Printf(TEXT("The component being hit %s"), *OutHit.GetComponent()->GetName()));
			DrawDebugLine(GetWorld(), FruitCharacter->GetActorLocation(), EndVector, FColor::Red, false, 3, 0, 5);
			bLocationSuccess = false;
		}
		// else
		// {
		// 	//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, FString::Printf(TEXT("The component not being hit.")));
		// 	//DrawDebugLine(GetWorld(), FruitCharacter->GetActorLocation(), EndVector, FColor::Blue, false, 3, 0, 5);
		// }
		
	}while (bLocationSuccess == false);



	
	
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
