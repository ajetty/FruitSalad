// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


void UHealthComponent::SetHealth()
{
	Health = DefaultHealth;
}

// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	//Health = DefaultHealth;
	GameModeBaseRef = Cast<AFruitSaladGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::TakeDamage);
}

void UHealthComponent::TakeDamage(AActor* DamageActor, float Damage, const UDamageType* DamageType,
	AController* InstigatedBy, AActor* DamageCauser)
{
	//GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, "HIT");
	
	if(Damage == 0 || Health <= 0)
	{
		return;
	}

	Health = FMath::Clamp(Health - Damage, 0.0f, DefaultHealth);

	//GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Purple, "Current Health: " + FString::SanitizeFloat(Health));

	if(Health <= 0)
	{
		if(GameModeBaseRef)
		{
			GameModeBaseRef->ActorDied(GetOwner());
		} else
		{
			UE_LOG(LogTemp, Warning, TEXT("WARNING: HealthComponent.cpp: Health component has no reference to the GameMode."));
		}
	}
}

