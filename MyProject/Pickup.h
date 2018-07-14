// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Objective.h"
#include "Pickup.generated.h"

UCLASS()
class MYPROJECT_API APickup : public AObjective
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickup();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UPROPERTY(EditAnywhere)
		UBoxComponent* HitBox;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* MyMesh;

	void SetMesh(UStaticMesh* Model);
	virtual bool Completed() override;
	virtual void reset() override;

	UFUNCTION()
		void Collide(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);


};
