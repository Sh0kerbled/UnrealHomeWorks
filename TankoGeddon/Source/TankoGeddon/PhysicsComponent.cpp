// Fill out your copyright notice in the Description page of Project Settings.


#include "PhysicsComponent.h"

// Sets default values for this component's properties
UPhysicsComponent::UPhysicsComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

TArray<FVector> UPhysicsComponent::GenerateTrajectory(FVector StartPos, FVector VeloCity, float MaxTime, float TimeStep, float MinZVlaue)
{
	TArray<FVector> trajectory;
	FVector gravityVector(0, 0, Gravity);
	for (float time = 0; time < MaxTime; time = time + TimeStep)
	{
		FVector position = StartPos + VeloCity * time + gravityVector * time * time / 2;
		if (position.Z <= MinZVlaue)
			break;

		trajectory.Add(position);
	}

	return trajectory;
}

