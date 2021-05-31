// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FruitSalad/FruitSaladGameModeBase.h"

#include "HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FRUITSALAD_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

	UFUNCTION()
	void TakeDamage(AActor* DamageActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);

	UPROPERTY(EditAnywhere)
	float DefaultHealth;

	void SetHealth();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:	
	float Health = 0.0f;
	AFruitSaladGameModeBase* GameModeBaseRef;
		
};
