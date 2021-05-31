// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_PlayerSensed.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

UBTService_PlayerSensed::UBTService_PlayerSensed()
{
	NodeName = TEXT("Update Player Location If Seen");

	Player = Cast<APawnBulldozer>(UGameplayStatics::GetPlayerPawn(this, 0));
}

void UBTService_PlayerSensed::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	if(OwnerComp.GetBlackboardComponent()->GetValueAsBool(TEXT("HasLineOfSight")))
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(TEXT("SensedPlayerLocation"), Player->GetActorLocation());
		//OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("HasLineOfSight"), false);
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Purple, "Perceived " + Player->GetActorLocation().ToString());
	}
	else
	{
			
	}
}



