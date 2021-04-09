// Copyright Epic Games, Inc. All Rights Reserved.


#include "FruitSaladGameModeBase.h"



#include "GameFramework/HUD.h"
#include "Kismet/GameplayStatics.h"


AFruitSaladGameModeBase::AFruitSaladGameModeBase()
{
	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.bCanEverTick = true;
}

void AFruitSaladGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	HandleGameStart();
}

void AFruitSaladGameModeBase::Tick(float DeltaSeconds)
{
	if(GetWorld()->GetTimerManager().TimerExists(CountDownTimer))
	{
		CurrentTimeSeconds = GetWorld()->GetTimerManager().GetTimerRemaining(CountDownTimer);
		//UE_LOG(LogTemp, Warning, TEXT("WARNING: FruitSaladGameModeBase: TIME, %f"), CurrentTimeSeconds);

		//convert time remaining to a minute-second format for HUD text boxes 
		int32 Minutes = static_cast<int32>(CurrentTimeSeconds/60.0f);
		UE_LOG(LogTemp, Warning, TEXT("Minutes: %d"), Minutes);
		
		int32 Seconds = static_cast<int32>(CurrentTimeSeconds) % 60;
		UE_LOG(LogTemp, Warning, TEXT("Seconds: %d"), Seconds);
		
		PlayerControllerRef->UpdateHUD(Minutes, Seconds);
	}
}

void AFruitSaladGameModeBase::HandleGameStart()
{
	PlayerBulldozer = Cast<APawnBulldozer>(UGameplayStatics::GetPlayerPawn(this, 0));
	PlayerControllerRef = Cast<ABulldozerPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	
	EndTimeSeconds = CountDownTimerMinutes * 60 + CountDownTimerSeconds;

	if(PlayerControllerRef)
	{
		GetWorld()->GetTimerManager().SetTimer(CountDownTimer, this, &AFruitSaladGameModeBase::EndGame, EndTimeSeconds, false);
	}	
}

void AFruitSaladGameModeBase::HandleGameOver()
{
}

void AFruitSaladGameModeBase::EndGame()
{
	UE_LOG(LogTemp, Warning, TEXT("Game Mode: GAME OVER"));
	PlayerControllerRef->GameHasEnded();
}

// int32 AFruitSaladGameModeBase::GetTargetBuildings()
// {
// }
