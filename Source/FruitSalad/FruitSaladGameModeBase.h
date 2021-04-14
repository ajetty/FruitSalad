// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "Bulldozer/BulldozerPlayerController.h"
#include "Bulldozer/PawnBulldozer.h"
#include "GameFramework/GameModeBase.h"
#include "FruitSaladGameModeBase.generated.h"

class ABulldozerPlayerController;
class APawnBulldozer;
class UUserWidget;
UCLASS()
class FRUITSALAD_API AFruitSaladGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AFruitSaladGameModeBase();
	void ActorDied(AActor* DeadActor, float TimeGain);

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	float CountDownTimerMinutes;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	float CountDownTimerSeconds;

	void HandleGameStart();
	void HandleGameOver(bool bIsWinner);
	void EndGame(bool bIsPlayerWinner);

	int32 TargetBuildings = 0;
	int32 GetTargetBuildings();
	
	float EndTimeSeconds;
	float CurrentTimeSeconds;
	FTimerHandle CountDownTimerHandle;
	FTimerDelegate HandleGameOverDelegate;
	void AddCountDownTime(float AddSeconds);
	
	ABulldozerPlayerController* PlayerControllerRef;
	APawnBulldozer* PlayerBulldozer;
};
