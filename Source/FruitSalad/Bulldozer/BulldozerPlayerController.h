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
	
	virtual void GameHasEnded(AActor* EndGameFocus = nullptr, bool bIsWinner = true) override;
	
	void UpdateHUD(int32 MinutesUpdate, int32 SecondsUpdate);

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UUserWidget* HUD;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UUserWidget* PauseMenu;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UUserWidget* MainMenu;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UUserWidget* WinScreen;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UUserWidget* LoseScreen;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> HUDClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> LoseScreenClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> WinScreenClass;

	UTextBlock* TextBlock_Minutes;
	UTextBlock* TextBlock_Seconds;
};
