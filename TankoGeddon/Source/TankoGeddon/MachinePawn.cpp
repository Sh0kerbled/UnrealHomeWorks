// Fill out your copyright notice in the Description page of Project Settings.


#include "MachinePawn.h"
#include "TankPawn.h"
#include "Components\StaticMeshComponent.h"
#include "Components\ArrowComponent.h"
#include "Components\BoxComponent.h"
#include "HealthComponent.h"
#include "Cannon.h"

AMachinePawn::AMachinePawn()
{
	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyMesh"));
	RootComponent = BodyMesh;

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TurretMesh"));
	TurretMesh->SetupAttachment(BodyMesh);

	CannonSetupPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("CannonSetupPoint"));
	CannonSetupPoint->SetupAttachment(TurretMesh);

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	BoxComponent->SetupAttachment(BodyMesh);

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
	HealthComponent->OnDie.AddUObject(this, &AMachinePawn::Die);
	HealthComponent->OnHealthChanged.AddUObject(this, &AMachinePawn::DamageTaked);
}

void AMachinePawn::TakeDamage(FDamageData DamageData)
{
	HealthComponent->TakeDamage(DamageData);
}

void AMachinePawn::Fire()
{
	if (Cannon)
		Cannon->Fire();
}

void AMachinePawn::SetupCannon(TSubclassOf<ACannon> newCannonClass)
{
	if (!newCannonClass)
	{
		return;
	}

	if (Cannon)
	{
		Cannon->Destroy();
	}

	CannonClass = newCannonClass;

	FActorSpawnParameters params;
	params.Instigator = this;
	params.Owner = this;

	Cannon = GetWorld()->SpawnActor<ACannon>(CannonClass, params);
	Cannon->SetOwner(this);

	Cannon->AttachToComponent(CannonSetupPoint, FAttachmentTransformRules::SnapToTargetIncludingScale);

}

void AMachinePawn::BeginPlay()
{
	Super::BeginPlay();

	SetupCannon(CannonClass);
}

void AMachinePawn::Die()
{
	if (Cannon)
	{
		Cannon->Destroy();
	}
	Destroy();
}

void AMachinePawn::DamageTaked(float DamageValue)
{
	UE_LOG(LogTemp, Warning, TEXT("Turret %s take Damage: %f,  Health: %f"), *GetName(), DamageValue, HealthComponent->GetHealth());
}

