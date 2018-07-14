// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Interactable.h"
#include "GameFramework/Actor.h"
#include "Resettable.generated.h"

UCLASS()
class MYPROJECT_API AResettable : public AInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AResettable();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;
	virtual void reset();
	
};
