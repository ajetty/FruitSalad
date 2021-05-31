// Copyright Epic Games, Inc. All Rights Reserved.


#include "FruitSaladGameModeBase.h"



#include "Building/BuildingTarget.h"
#include "Fruit/CharacterFruitBase.h"
#include "Fruit/FruitBase.h"
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
	if(GetWorld()->GetTimerManager().TimerExists(CountDownTimerHandle))
	{
		CurrentTimeSeconds = GetWorld()->GetTimerManager().GetTimerRemaining(CountDownTimerHandle);
		//UE_LOG(LogTemp, Warning, TEXT("WARNING: FruitSaladGameModeBase: TIME, %f"), CurrentTimeSeconds);

		//convert time remaining to a minute-second format for HUD text boxes 
		int32 Minutes = static_cast<int32>(CurrentTimeSeconds/60.0f);
		//UE_LOG(LogTemp, Warning, TEXT("Minutes: %d"), Minutes);
		
		int32 Seconds = static_cast<int32>(CurrentTimeSeconds) % 60;
		//UE_LOG(LogTemp, Warning, TEXT("Seconds: %d"), Seconds);
		
		PlayerControllerRef->UpdateHUD(Minutes, Seconds);
	}
}

void AFruitSaladGameModeBase::AddCountDownTime(float AddSeconds)
{
	EndTimeSeconds = CurrentTimeSeconds + AddSeconds;
	GetWorld()->GetTimerManager().SetTimer(CountDownTimerHandle, HandleGameOverDelegate, EndTimeSeconds, false);
}

void AFruitSaladGameModeBase::HandleGameStart()
{
	PlayerBulldozer = Cast<APawnBulldozer>(UGameplayStatics::GetPlayerPawn(this, 0));
	PlayerControllerRef = Cast<ABulldozerPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	
	EndTimeSeconds = CountDownTimerMinutes * 60 + CountDownTimerSeconds;

	if(PlayerControllerRef)
	{
		//if timer counts down to zero without variable TargetBuilding == 0 then player loses
		HandleGameOverDelegate = FTimerDelegate::CreateUObject(this, &AFruitSaladGameModeBase::HandleGameOver, false);
		GetWorld()->GetTimerManager().SetTimer(CountDownTimerHandle, HandleGameOverDelegate, EndTimeSeconds, false);
	}

	TargetBuildings = GetTargetBuildings();

	UE_LOG(LogTemp, Warning, TEXT("Buildings: %d"), TargetBuildings);
}

void AFruitSaladGameModeBase::HandleGameOver(bool bIsWinner)
{
	EndGame(bIsWinner);
	GetWorld()->GetTimerManager().ClearTimer(CountDownTimerHandle);
}

void AFruitSaladGameModeBase::EndGame(bool bIsPlayerWinner)
{
	UE_LOG(LogTemp, Warning, TEXT("Game Mode: GAME OVER"));
	bool bIsWinner = PlayerControllerRef->IsPlayerController() == bIsPlayerWinner;
	PlayerControllerRef->GameHasEnded(PlayerControllerRef->GetPawn(), bIsWinner);
}

int32 AFruitSaladGameModeBase::GetTargetBuildings()
{
	TArray<AActor*> BuildingTargetPawns;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABuildingTarget::StaticClass(), BuildingTargetPawns);
	return BuildingTargetPawns.Num();
}

void AFruitSaladGameModeBase::ActorDied(AActor* DeadActor)
{
	if(ABuildingTarget* DeadTargetBuilding = Cast<ABuildingTarget>(DeadActor))
	{
		--TargetBuildings;
		
		if(TargetBuildings == 0)
		{
			HandleGameOver(true);
		}
		
		AddCountDownTime(DeadTargetBuilding->TimeGain);
	}
	else if(ABuildingBase* DeadBaseBuilding = Cast<ABuildingBase>(DeadActor))
	{
		AddCountDownTime(DeadBaseBuilding->TimeGain);
	}
	else if(ACharacterFruitBase* DeadFruit = Cast<ACharacterFruitBase>(DeadActor))
	{
		AddCountDownTime(DeadFruit->FruitDataAsset->TimeGain);
		DeadFruit->Destroy();
	}	
}
