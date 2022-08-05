// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include <Components/SceneComponent.h>
#include <Components/StaticMeshComponent.h>
#include "DamageTaker.h"
#include <Components/PrimitiveComponent.h>
#include "PhysicsProjectile.h"
#include <Kismet/KismetMathLibrary.h>
#include "TankPawn.h"
#include "MachinePawn.h"
#include "TankFactory.h"

ATankPawn TankPawn;
AMachinePawn MachinePawn;
ATankFactory TankFactory;

AProjectile::AProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	RootComponent = SceneComponent;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
	ProjectileMesh->SetupAttachment(SceneComponent);
	ProjectileMesh->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::OnMeshOverlapBegin);
	ProjectileMesh->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel1);
}

void AProjectile::Start()
{
	GetWorld()->GetTimerManager().SetTimer(MoveTimer, this, &AProjectile::Move, MoveRate, true, MoveRate);
}

void AProjectile::Reload()
{
	CanItFire = true
}

void AProjectile::Move()
{
	FVector nextPosition = GetActorLocation() + GetActorForwardVector() * MoveSpeed * MoveRate;
	SetActorLocation(nextPosition);
}

void APhysicsProjectile::Move()
{
	FVector currentMoveVector = CurrentTrajectory[TragectoryPointIndex] - GetActorLocation();
	currentMoveVector.Normalize();
	FVector newLocation = GetActorLocation() + currentMoveVector * MoveSpeed * MoveRate;
	SetActorLocation(newLocation);
	if (FVector::Distance(newLocation, CurrentTrajectory[TragectoryPointIndex]) <= MoveAccurency)
	{
		TragectoryPointIndex++;
		if (TragectoryPointIndex >= CurrentTrajectory.Num())
		{
			Destroy();
		}
		else
		{
			FRotator newRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), CurrentTrajectory[TragectoryPointIndex]);
			SetActorRotation(newRotation);
		}
	}
}
void AProjectile::OnMeshOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	FVector startPos = GetActorLocation();
	FVector endPos = startPos + FVector(0.1f);
	FCollisionShape Shape = FCollisionShape::MakeSphere(ExplodeRadius);
	FCollisionQueryParams params = FCollisionQueryParams::DefaultQueryParam;
	params.AddIgnoredActor(this);
	params.bTraceComplex = true;
	params.TraceTag = "Explode Trace";
	TArray<FHitResult> AttackHit;
	FQuat Rotation = FQuat::Identity;
	bool sweepResult = GetWorld()->SweepMultiByChannel
	(
		AttackHit, startPos, endPos, Rotation, ECollisionChannel::ECC_Visibility, Shape, params
	)
	GetWorld()->DebugDrawTraceTag = "Explode Trace";
	if (!CanItFire || MortarNucleis == 0)
	{
		return;
	}
	MortarNucleis--;

	CanItFire = false;

	if (MortarNucleis == NoMortar)
	{
		return;
	}
	CanItFire = false;

	if (sweepResult)
	{
		for (FHitResult hitResult : AttackHit)
		{
			AActor* otherActor = hitResult.GetActor();
			if (!otherActor)
				continue;
			IDamageTaker* damageTakerActor = Cast<IDamageTaker>(otherActor);
			if (damageTakerActor)
			{
				FDamageData damageData;
				damageData.DamageValue = Damage;
				damageData.Instigator = GetOwner();
				damageData.DamageMaker = this;
				damageTakerActor->TakeDamage(damageData);
			}
			else
			{
				UPrimitiveComponent* mesh = Cast<UPrimitiveComponent>(otherActor->GetRootComponent());
				if (mesh)
				{
					if (mesh->IsSimulatingPhysics())
					{
						FVector forceVector = OtherActor->GetActorLocation() - GetActorLocation();
						forceVector.Normalize();
						/*mesh->AddImpulse(forceVector * PushForce, NAME_None, true);*/
						mesh->AddForce(forceVector * Force, NAME_None, true);
					}
				}
			}
			if (TankPawn || TankFactory || MachinePawn)
			{
				FVector forceVector = OtherActor->GetActorLocation() - GetActorLocation();
				forceVector.Normalize();
				mesh->AddForce(forceVector * Force, NAME_None, true);
			}
			Destroy();
		}
	}
}


				