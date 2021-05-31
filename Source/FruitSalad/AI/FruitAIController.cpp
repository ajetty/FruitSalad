// Fill out your copyright notice in the Description page of Project Settings.


#include "FruitAIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "FruitSalad/Bulldozer/PawnBulldozer.h"
#include "Kismet/GameplayStatics.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

AFruitAIController::AFruitAIController()
{
	PrimaryActorTick.bCanEverTick = true;

	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Component")));
	
	SightConfig->SightRadius = AISightRange;
	SightConfig->LoseSightRadius = AISightRange;
	SightConfig->SetMaxAge(AISightMaxAge);
	
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
	
	GetPerceptionComponent()->SetDominantSense(*SightConfig->GetSenseImplementation());
	GetPerceptionComponent()->ConfigureSense(*SightConfig);
}

void AFruitAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

}

void AFruitAIController::BeginPlay()
{
	Super::BeginPlay();

	if(AIBehavior != nullptr)
	{
		RunBehaviorTree(AIBehavior);

		//APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

		//GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"),PlayerPawn->GetActorLocation());

		//GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"),GetPawn()->GetActorLocation());

		// AIPerception = FindComponentByClass<UFruitAIPerception>();
		//
		// if(ensureMsgf(AIPerception, TEXT("AIPerception in FruitAIController is nullptr.")))
		// {
		// 	AIPerception->OnTargetPerceptionUpdated.AddDynamic(this, &AFruitAIController::SenseActors);	
		// 	TArray<AActor*> ActorsSensed;
		// 	AIPerception->GetCurrentlyPerceivedActors(SightSense, ActorsSensed);
		// }
		//
		// //UNavigationSystemV1::K2_GetRandomReachablePointInRadius();
	}

	GetPerceptionComponent()->OnPerceptionUpdated.AddDynamic(this, &AFruitAIController::OnPawnDetected);
}

void AFruitAIController::OnPawnDetected(const TArray<AActor*>& DetectedPawns)
{
	
	for(AActor* DetectedPawn : DetectedPawns)
	{
		if(Cast<APawnBulldozer>(DetectedPawn))
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Blue, "Perceived " + DetectedPawn->GetName());
			GetBlackboardComponent()->SetValueAsBool(TEXT("HasLineOfSight"), true);
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, "Perceived " + DetectedPawn->GetName());
			GetBlackboardComponent()->SetValueAsBool(TEXT("HasLineOfSight"), false);
		}
	}
}

// void AFruitAIController::SenseActors(AActor* UpdatedActor, FAIStimulus Stimulus)
// {
// 	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, "Perceived " + UpdatedActor->GetName());
// 	if(Stimulus.WasSuccessfullySensed())
// 	{
// 		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Blue, "Perceived " + UpdatedActor->GetName());
// 	}
// }
