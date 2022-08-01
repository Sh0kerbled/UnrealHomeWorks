// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DamageTaker.h"
#include <Particles/ParticleSystemComponent.h>
#include <Components/AudioComponent.h>
#include "TankFactory.generated.h"

UCLASS()
class TANKOGEDDON_API ATankFactory : public AActor, public IDamageTaker
{
	GENERATED_BODY()
	
public:	
	ATankFactory();

protected:
	virtual void BeginPlay() override;

	void SpawnTank();

	void SpawnFactory();

	UFUNCTION()
	virtual void TakeDamage(FDamageData DamageData);

	UFUNCTION()
	void Die();

	UFUNCTION()
	void DamageTaked(float DamageValue);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	class UStaticMeshComponent* BuildingMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	class UBoxComponent* BoxCollider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	class UHealthComponent* HealthComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	class UArrowComponent* TankSpawnPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	class UArrowComponent* TankFactorySpawnPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnParametres")
	TSubclassOf<class ATankPawn> SpawnTankClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnParametres")
	TSubclassOf<class ATankFactory> SpawnTankFactoryClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	float SpawnTankRate = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TArray<class ATargetPoint*> TankWayPoints;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MapLoader")
	class AMapLoader* MapLoader;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components | Effects")
	UParticleSystemComponent* TankSpawnEffect;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components | Effects")
	UParticleSystemComponent* FactoryDestroyEffect;
};
