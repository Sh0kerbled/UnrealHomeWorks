// Fill out your copyright notice in the Description page of Project Settings.


#include "Cannon.h"
#include "Components\ArrowComponent.h"
#include "Components\StaticMeshComponent.h"
#include "Projectile.h"
#include <GameFramework/ForceFeedbackEffect.h>
#include "Particles\ParticleSystemComponent.h"
#include "GameFramework/ForceFeedbackEffect.h"
#include "Components\AudioComponent.h"
#include "Camera\CameraShakeBase.h"

// Sets default values
ACannon::ACannon()
{
	PrimaryActorTick.bCanEverTick = false;

	CannonMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CannonMesh"));
	RootComponent = CannonMesh;

	USceneComponent* CannonSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("CannonRoot"));
	RootComponent = CannonSceneComponent;

	ProjectileSpawnPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("ProjectileSpawnPoint"));
	ProjectileSpawnPoint->SetupAttachment(CannonSceneComponent);

	ShootEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ShootEffect"));
	ShootEffect->SetupAttachment(ProjectileSpawnPoint);

	AudioEffect = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioEffect"));
}

void ACannon::Fire()
{
	if (!bCanFire || Nuclei <= 0)
	{
		return;
	}

	bCanFire = false;
	Nuclei--;
	ShootEffect->ActivateSystem();
	AudioEffect->Play();

	if (GetOwner() && GetOwner() == GetWorld()->GetFirstPlayerController()->GetPawn())
	{
		if (ShootShake)
		{
			GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(ShootShake);
		}
	}


	if (CannonType == ECannonType::FireProjectile)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("Fire Projectile")));

		AProjectile* projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, ProjectileSpawnPoint->GetComponentLocation(), ProjectileSpawnPoint->GetComponentRotation());
		if (projectile)
		{
			projectile->Start();
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("UKANDA FOREVA AUUAUAUAUUAUAUAUUAUUAUAUAU")));

		FHitResult hitResult;
		FCollisionQueryParams traceParams = FCollisionQueryParams(FName(TEXT("UKANDA FOREVA!")), true, this);
		traceParams.bTraceComplex = true;
		traceParams.bReturnPhysicalMaterial = false;

		FVector StartTrace = ProjectileSpawnPoint->GetComponentLocation();
		FVector EndTrace = StartTrace + ProjectileSpawnPoint->GetForwardVector() * FireRange;

		if (GetWorld()->LineTraceSingleByChannel(hitResult, StartTrace, EndTrace, ECollisionChannel::ECC_Visibility))
		{
			DrawDebugLine(GetWorld(), StartTrace, hitResult.Location, FColor::Purple, false, 0.5f, 0, 10);
			if (hitResult.GetActor())
			{
				hitResult.GetActor()->Destroy();
			}
			else
			{
				DrawDebugLine(GetWorld(), StartTrace, EndTrace, FColor::Green, false, 0.5f, 0, 10);
			}
		}
	}
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("Ammo Left: %d"), Nuclei));

	GetWorld()->GetTimerManager().SetTimer(ReloadTimer, this, &ACannon::Reload, ReloadTime, false);
}

void ACannon::FireSpecial()
{
	if (!bCanFire || Nuclei == 0)
	{
		return;
	}
	Nuclei--;
	 
	bCanFire = false;

	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("UKANDA FOREVA AMMO LEFT: %d"), Nuclei));

	DStroy();
}

void ACannon::Reload()
{
	bCanFire = true;
}

void ACannon::DStroy()
{
	if (NoNuclei == BST)
	{
		GetWorld()->GetTimerManager().ClearTimer(BurstTimer);
		bCanFire = true;
		NoNuclei = 0;
		Nuclei--;
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("Shells is: %d")));
		return;
	}

	NoNuclei++;

	if (CannonType == ECannonType::FireProjectile)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("UKANDA FOREVA AAAAAAAAAAAAAAAAA")));
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("UKANDA FOREVA AAAAAAAAAAAAAAAAA dvazhdi")));
	}

	GetWorld()->GetTimerManager().SetTimer(ReloadTimer, this, &ACannon::Reload, ReloadTime, false);
} 

