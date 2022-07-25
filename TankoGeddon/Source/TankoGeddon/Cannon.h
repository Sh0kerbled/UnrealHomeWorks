// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameStruct.h"
#include <Components\ArrowComponent.h>
#include "Cannon.generated.h"

UCLASS()
class TANKOGEDDON_API ACannon : public AActor
{
	GENERATED_BODY()
	
public:	
	ACannon();

	void Fire();
	void Reload();
	void FireSpecial();
	void ChangeGun();
	bool IsReadyToFire() { return bCanFire; };
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	class UStaticMeshComponent* CannonMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	class UArrowComponent* ProjectileSpawnPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	ECannonType CannonType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	float ReloadTime = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GunAmmo")
	int32 Nuclei = 99;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GunAmmo")
	int32 BST = 5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GunAmmo")
	float Intervali = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GunAmmo")
	float FireRange = 100.0f;

	FTimerHandle ReloadTimer;
	FTimerHandle BurstTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	TSubclassOf<class AProjectile> ProjectileClass;
public:	
	bool bCanFire = true;
	int32 NoNuclei = 0;
	
	void DStroy();
};
