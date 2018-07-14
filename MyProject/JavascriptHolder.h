// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Resettable.h"
#include "JavascriptHolder.generated.h"

UCLASS()
class MYPROJECT_API AJavascriptHolder : public AResettable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AJavascriptHolder();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	virtual void reset() override;
	
};
