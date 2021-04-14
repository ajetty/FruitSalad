// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "DestructibleComponent.h"

#include "BuildingBase.generated.h"


class UBoxComponent;
class UDestructibleComponent;
class UMaterialInstanceDynamic;
class UMaterial;
class AWheeledVehicle;
class AFruitSaladGameModeBase;
UCLASS()
class FRUITSALAD_API ABuildingBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABuildingBase();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION()
    void Damage(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
    void Trigger(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Sweep);

	UFUNCTION()
    virtual void Destroy(float Damage, FVector HitLocation, FVector ImpulseDir, float Impulse);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Destructable", meta = (AllowPrivateAccess = "true"))
	UBoxComponent* TriggerComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Destructable", meta = (AllowPrivateAccess = "true"))
	UDestructibleComponent* DestructibleComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Destructable", meta = (AllowPrivateAccess = "true"))
	UMaterial* DestructibleMaterialComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Destructable", meta = (AllowPrivateAccess = "true"))
	UMaterialInstanceDynamic* DynamicMaterialInstance;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Destructable", meta = (AllowPrivateAccess = "true"))
	bool IsTriggeredEnabled;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Destructable", meta = (AllowPrivateAccess = "true"))
	bool IsDestroyed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Destructable", meta = (AllowPrivateAccess = "true"))
	float MaxHealth;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Destructable", meta = (AllowPrivateAccess = "true"))
	float CurrentHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Destructable", meta = (AllowPrivateAccess = "true"))
	float DefaultDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Destructable", meta = (AllowPrivateAccess = "true"))
	float DefaultImpulse;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Destructable", meta = (AllowPrivateAccess = "true"))
	float TimeGain;

	
private:
	AFruitSaladGameModeBase* GameModeBaseRef;
};
