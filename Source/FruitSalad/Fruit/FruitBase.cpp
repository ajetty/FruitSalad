// Fill out your copyright notice in the Description page of Project Settings.


#include "FruitBase.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
AFruitBase::AFruitBase()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Base Mesh"));
	BaseMesh->SetupAttachment(RootComponent);

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));
	//HealthComponent = NewObject<UHealthComponent>();
	
}

// Called when the game starts or when spawned
void AFruitBase::BeginPlay()
{
	Super::BeginPlay();

	BaseMesh->SetStaticMesh(FruitDataAsset->StaticMesh);
	BaseMesh->OnComponentHit.AddDynamic(this, &AFruitBase::OnHit);

	HealthComponent->DefaultHealth = FruitDataAsset->MaxHealth;
	HealthComponent->SetHealth();
}

// Called every frame
void AFruitBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AFruitBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AFruitBase::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                       FVector NormalImpulse, const FHitResult& Hit)
{
	if (APawnBulldozer* PlayerPawn = Cast<APawnBulldozer>(OtherActor))
	{
		HealthComponent->TakeDamage(this, FruitDataAsset->DamageTakenPerHit, DamageType, GetOwner()->GetInstigatorController(), PlayerPawn);
	}
}
