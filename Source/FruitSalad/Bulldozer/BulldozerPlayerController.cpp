// Fill out your copyright notice in the Description page of Project Settings.


#include "BulldozerPlayerController.h"

#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetTree.h"
#include "FruitSalad/HUD/FruitSaladHUD.h"
#include "GameFramework/HUD.h"
#include "Kismet/GameplayStatics.h"

ABulldozerPlayerController::ABulldozerPlayerController()
{
	
}

void ABulldozerPlayerController::BeginPlay()
{
	HUD = CreateWidget(this, HUDClass);
	
	if(HUD == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("ERROR: BulldozerPlayerController.cpp: HUD IS NULLPTR"))
		return;
	}
	
	HUD->AddToViewport();
	//HUD->SetVisibility(ESlateVisibility::Hidden);
	
	UTextBlock* TEST = Cast<UTextBlock>(HUD->WidgetTree->FindWidget("TextBlock_TEST"));
	
	if(TEST)
	{
		//UE_LOG(LogTemp, Error, TEXT("TEST IS GOOOOOD"));
		TEST->SetText(FText::FromString("Banananas!"));
	}
	
	//widgets from HUD parent class FruitSaladHUD
	TextBlock_Minutes = Cast<UTextBlock>(HUD->WidgetTree->FindWidget("TextBlock_Minutes"));
	TextBlock_Seconds = Cast<UTextBlock>(HUD->WidgetTree->FindWidget("TextBlock_Seconds"));

	//UpdateHUD(27.0f, 27.0f);

	if(!TextBlock_Minutes && !TextBlock_Seconds)
	{
		UE_LOG(LogTemp, Error, TEXT("ERROR: BulldozerPlayerController: BULLDOZER PLAYER CONTROLLER NOT BEING READ IN BEGIN GAME"))
		return;
	}

	Super::BeginPlay();
}

void ABulldozerPlayerController::GameHasEnded(AActor* EndGameFocus, bool bIsWinner)
{
	Super::GameHasEnded(EndGameFocus, bIsWinner);
	UE_LOG(LogTemp, Warning, TEXT("Player Controller: The Game has Ended!"));
}

void ABulldozerPlayerController::UpdateHUD(int32 MinutesUpdate, int32 SecondsUpdate)
{
	if(TextBlock_Minutes && TextBlock_Seconds)
	{
		UFruitSaladHUD::UpdateTimeTextBlock(TextBlock_Minutes, TextBlock_Seconds, MinutesUpdate, SecondsUpdate);
	}else
	{
		UE_LOG(LogTemp, Error, TEXT("ERROR: BulldozerPlayerController: BULLDOZER PLAYER CONTROLLER TEXTBLOCK_MINUTES AND TEXTBLOCK_SECONDS ARE NULL"))
	}
}


