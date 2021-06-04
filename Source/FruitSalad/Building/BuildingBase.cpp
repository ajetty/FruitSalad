// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildingBase.h"


#include "FruitSalad/FruitSaladGameModeBase.h"
#include "FruitSalad/Bulldozer/PawnBulldozer.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABuildingBase::ABuildingBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Component"));

	DestructibleComponent = CreateDefaultSubobject<UDestructibleComponent>(TEXT("Destructible Component"));
	DestructibleComponent->SetupAttachment(RootComponent);
	DestructibleComponent->SetNotifyRigidBodyCollision(true);

	TriggerComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger Component"));
	TriggerComponent->SetupAttachment(RootComponent);

	IsDestroyed = false;
	IsTriggeredEnabled = false;

	MaxHealth = 100.0f;

	DefaultDamage = 1.0f;
	DefaultImpulse = 1.0f;

	TimeGain = 60.0f; //seconds
}

// Called when the game starts or when spawned
void ABuildingBase::BeginPlay()
{
	Super::BeginPlay();

	DynamicMaterialInstance = UMaterialInstanceDynamic::Create(DestructibleComponent->GetMaterial(0), this);
	DestructibleComponent->SetMaterial(0, DynamicMaterialInstance);

	DestructibleComponent->OnComponentHit.AddDynamic(this, &ABuildingBase::Damage);
	
	TriggerComponent->OnComponentBeginOverlap.AddDynamic(this, &ABuildingBase::Trigger);

	GameModeBaseRef = Cast<AFruitSaladGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	
	CurrentHealth = MaxHealth;
}

// Called every frame
void ABuildingBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABuildingBase::Damage(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,
	FVector NormalImpulse, const FHitResult& Hit)
{

	if(APawnBulldozer* PlayerPawn = Cast<APawnBulldozer>(OtherActor))
	{
		if(!IsDestroyed)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Orange, "Hit By: " + OtherComponent->GetName());

			CurrentHealth = CurrentHealth - 1.0f;
			//GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Orange, "Current Health: " + FString::SanitizeFloat(CurrentHealth));

			DynamicMaterialInstance->SetScalarParameterValue("Cracks", (1 - CurrentHealth/MaxHealth));
			//UE_LOG(LogTemp, Warning, TEXT("Current Health: %f MESH: %f"), CurrentHealth, (1 - CurrentHealth/MaxHealth));

			if(CurrentHealth <= 0.0f)
			{
				Destroy(DefaultDamage, Hit.Location, NormalImpulse, DefaultImpulse);
			}
		}
	}
}

void ABuildingBase::Trigger(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Sweep)
{
	if(!IsDestroyed && IsTriggeredEnabled && OtherActor->ActorHasTag("Player"))
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Orange, __FUNCTION__);
		Destroy(DefaultDamage, DestructibleComponent->GetComponentLocation(), OtherActor->GetActorForwardVector(), DefaultImpulse);
	}
}

void ABuildingBase::Destroy(float Damage, FVector HitLocation, FVector ImpulseDir, float Impulse)
{
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Orange, __FUNCTION__);

	if(!IsDestroyed)
	{
		IsDestroyed = true;

		DestructibleComponent->ApplyDamage(Damage, HitLocation, ImpulseDir, Impulse);

		GameModeBaseRef->ActorDied(this);
	}
}



