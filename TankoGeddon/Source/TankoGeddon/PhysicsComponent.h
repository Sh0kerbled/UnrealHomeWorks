// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TANKOGEDDON_API UPhysicsComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPhysicsComponent();

	TArray<FVector> GenerateTrajectory(FVector StartPos, FVector VeloCity, float MaxTime, float TimeStep, float MinZVlaue);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Gravity params")
	float Gravity = -9.8f;
};
