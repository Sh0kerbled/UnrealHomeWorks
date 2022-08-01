// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameStruct.h"
#include "DamageTaker.h"
#include "MachinePawn.h"
#include <Engine/TargetPoint.h>
#include "TankPawn.generated.h"

class ACannon;
class UStaticMeshComponent;
class ATargetPoint;
UCLASS()
class TANKOGEDDON_API ATankPawn : public AMachinePawn
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

	UFUNCTION()
	TArray<FVector> GetPatrollingPoints();

	void SetPatrollingPoints(TArray<ATargetPoint*> NewPatrollingPoints);

	UFUNCTION()
		float GetAccurency() { return MovementAccurency; }

	UFUNCTION()
	FVector GetTurretForwardVector();

	UFUNCTION()
	void RotateTurretTo(FVector TargetPoition);

	UFUNCTION()
	FVector GetEyesPosition();

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		class UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Turret | Component")
		TSubclassOf<ACannon> CannonClassTwo;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement")
		float RotationSpeed = 100.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement")
		float InterpoLatoinKey = 0.5f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "TurretRotation")
		float TurretRotationInterpolationKey = 0.5f;

	UPROPERTY()
		class ATankController* TankController;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Movement")
	float MoveSpeed = 30.0f;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Movement")
	float MoveSpeed2 = 30.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI | Components", Meta = (MakeEditWidget = true))
	TArray<ATargetPoint*> PatrollingPoints;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI | Components")
	float MovementAccurency = 30.0f;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "dvizh")
	float TargetAxisValue = 0.0f;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "dvizh")
	float TargetRightAxisValue = 0.0f;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "dvizh")
	float RotateRightAxisValue = 0.0f;

	void SetupCannon();
};
