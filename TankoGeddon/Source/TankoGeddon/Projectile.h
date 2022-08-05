// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class TANKOGEDDON_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	AProjectile();

	virtual void Start();

	void Addforce();

	void Reload();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite,Category= "Components")
	class UStaticMeshComponent* ProjectileMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	float MoveSpeed = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	float MoveRate = 0.01f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	float Damage = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	float PushForce = 1000.0f;

	UPROPERTY(EditAnywhere, Category = "Damage")
	float Force = 500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	float MortarNucleis = 5.0f;

	FTimerHandle MoveTimer;

	UFUNCTION()
	virtual void Move();

public:
	bool CanItFire = true;

	int32 NoMortar = 0;

	UFUNCTION()
	void OnMeshOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
