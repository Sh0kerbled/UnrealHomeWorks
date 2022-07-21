// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TankController.h"
#include <Components\ArrowComponent.h>
#include "TankPawn.generated.h"

class ACannon;
class UStaticMeshComponent;
UCLASS()
class TANKOGEDDON_API ATankPawn : public APawn
{
	GENERATED_BODY()

public:
	ATankPawn();

	void MoveForward(float Value);

	void MoveRight(float Value);

	void RotateRight(float Vlaue);

	void Fire();

	void FireSpecial();

	void BST();

	void SetupCannon(TSubclassOf<ACannon> newCannonClass);

	void ChangeGun();

	virtual void Tick(float DeltaSeconds) override;

	virtual void BeginPlay() override;

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* BodyMesh;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* TurretMesh;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		class UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Turret | Component")
	TSubclassOf<ACannon> CannonClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Turret | Component")
	TSubclassOf<ACannon> CannonClassTwo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Turret | Component")
	class UArrowComponent* CannonSetupPoint;

	UPROPERTY()
	ACannon* Cannon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement")
		float RotationSpeed = 30.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement")
		float InterpoLatoinKey = 0.5f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "TurretRotation")
		float TurretRotationInterpolationKey = 0.5f;

	UPROPERTY()
		class ATankController* TankController;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Movement")
	float MoveSpeed = 30.0f;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "dvizh")
	float TargetAxisValue = 0.0f;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "dvizh")
	float TargetRightAxisValue = 0.0f;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "dvizh")
	float RotateRightAxisValue = 0.0f;

	void SetupCannon();
};
