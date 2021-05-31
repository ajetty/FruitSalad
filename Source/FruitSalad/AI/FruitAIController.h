// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "FruitAIController.generated.h"

class UAISenseConfig_Sight;
UCLASS()
class FRUITSALAD_API AFruitAIController : public AAIController
{
	GENERATED_BODY()

public:
	AFruitAIController();
	
	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI")
	UAISenseConfig_Sight* SightConfig;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI")
	float AISightRange = 1000.0f;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
	float AISightMaxAge = 5.0f;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
	bool bAISightStartsEnabled = true;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
	bool bIsPlayerDetected = false;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
	float DistanceToPlayer = 0.0f;
	
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	UBehaviorTree* AIBehavior;

	// Gets called when the perception component updates. This is
	// where check to see if the PlayerCharacter was detected.
	UFUNCTION()
    void OnPawnDetected(const TArray<AActor*>& DetectedPawns);

	// UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackboard", meta = (AllowPrivateAccess = true))
	// UFruitAIPerception* AIPerception;
	//
	// UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackboard", meta = (AllowPrivateAccess = true))
	// TSubclassOf<UAISense> SightSense;
	//
	// void SenseActors(AActor* UpdatedActor, FAIStimulus Stimulus);
	
};
