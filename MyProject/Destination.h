// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Objective.h"
#include "GameFramework/Actor.h"
#include "Destination.generated.h"

UCLASS()
class MYPROJECT_API ADestination : public AObjective
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADestination();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	virtual bool Completed() override;
	
};
