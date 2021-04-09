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

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	float CountDownTimerMinutes;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	float CountDownTimerSeconds;

	void HandleGameStart();
	void HandleGameOver();
	void EndGame();

	int32 TargetBuildings = 0;
	float EndTimeSeconds;
	float CurrentTimeSeconds;
	FTimerHandle CountDownTimer;
	//int32 GetTargetBuildings();
	
	ABulldozerPlayerController* PlayerControllerRef;
	APawnBulldozer* PlayerBulldozer;
};
