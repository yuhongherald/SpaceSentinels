// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Pickup.h"
#include "PickUpSquare.generated.h"

UCLASS()
class MYPROJECT_API APickUpSquare : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickUpSquare();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* Root;

	UPROPERTY(EditAnywhere)
		UStaticMesh* PickUpMesh;
	
	UPROPERTY(EditAnywhere)
		float distance;

private:
	
	TArray<class APickup*> pickups;
};
