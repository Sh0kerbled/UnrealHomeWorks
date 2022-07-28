// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameStruct.h"
#include <Components\ArrowComponent.h>
#include "Camera/CameraShake.h"
#include "Components/AudioComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ForceFeedbackEffect.h"
#include "Particles/ParticleSystemComponent.h"
#include <../Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/MatineeCameraShake.h>
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

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UParticleSystemComponent* ShootEffect;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UParticleSystemComponent* HitEffect;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UParticleSystemComponent* DestroyEffect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
	UForceFeedbackEffect* ShootForceEffect;
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Effects")
	TSubclassOf<UMatineeCameraShake> ShootShake;


	FTimerHandle ReloadTimer;
	FTimerHandle BurstTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	TSubclassOf<class AProjectile> ProjectileClass;
public:	
	bool bCanFire = true;
	int32 NoNuclei = 0;
	
	void DStroy();
};
