// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TextBlock.h"
#include "GameFramework/PlayerController.h"
//#include "FruitSalad/HUD/FruitSaladHUD.h"
#include "BulldozerPlayerController.generated.h"


class AActor;
class UUserWidget;
class UFruitSaladHUD;
UCLASS()
class FRUITSALAD_API ABulldozerPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ABulldozerPlayerController();
	virtual void GameHasEnded(AActor* EndGameFocus = nullptr, bool bIsWinner = false) override;
	void UpdateHUD(int32 MinutesUpdate, int32 SecondsUpdate);

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> HUDClass;
	
	UPROPERTY(EditAnywhere)
	UUserWidget* HUD;

	UTextBlock* TextBlock_Minutes;
	UTextBlock* TextBlock_Seconds;

	// UFruitSaladHUD* PlayerHUD;
	//
	// UPROPERTY(EditAnywhere)
	// TSubclassOf<UUserWidget> PlayerHUDClass;
};
