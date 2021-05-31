// Fill out your copyright notice in the Description page of Project Settings.
//GetCapsuleComponent()->InitCapsuleSize(x, y)

#include "CharacterFruitBase.h"



class APawnBulldozer;
// Sets default values
ACharacterFruitBase::ACharacterFruitBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));

	//SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Skeletal Base Mesh"));
	//SkeletalMesh->SetupAttachment(RootComponent);
	//SkeletalMesh = GetMesh();

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));

}

// Called when the game starts or when spawned
void ACharacterFruitBase::BeginPlay()
{
	Super::BeginPlay();

	GetMesh()->SetSkeletalMesh(FruitDataAsset->SkeletalMesh);
	GetMesh()->OnComponentHit.AddDynamic(this, &ACharacterFruitBase::OnHit);

	HealthComponent->DefaultHealth = FruitDataAsset->MaxHealth;
	HealthComponent->SetHealth();
	
}

// Called every frame
void ACharacterFruitBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACharacterFruitBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ACharacterFruitBase::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	if (APawnBulldozer* PlayerPawn = Cast<APawnBulldozer>(OtherActor))
	{
		HealthComponent->TakeDamage(this, FruitDataAsset->DamageTakenPerHit, DamageType, GetOwner()->GetInstigatorController(), PlayerPawn);
	}
}

