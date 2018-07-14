// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Resettable.h"
#include "GameFramework/Actor.h"
#include "Objective.generated.h"

UCLASS()
class MYPROJECT_API AObjective : public AResettable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AObjective();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	virtual bool Completed();
	
};
