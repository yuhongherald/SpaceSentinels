// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "StaticProgrammedObject.h"
#include "GameFramework/Actor.h"
#include "ProgrammedPlatform.generated.h"

UCLASS()
class MYPROJECT_API AProgrammedPlatform : public AStaticProgrammedObject
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProgrammedPlatform();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UFUNCTION(Blueprintcallable, Category = "Epic Category")
		void SetState(int newState);

	UFUNCTION(Blueprintcallable, Category = "Epic Category")
		int GetState();

	UFUNCTION(Blueprintcallable, Category = "Epic Category")
		void RootPlayer(AActor* player);

	UFUNCTION(Blueprintcallable, Category = "Epic Category")
		void UnrootPlayer(AActor* player);

private:

	int state;
	
};
