// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Objective.h"
#include "GameFramework/Actor.h"
#include "RiverSection.generated.h"

UCLASS()
class MYPROJECT_API ARiverSection : public AObjective
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARiverSection();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UFUNCTION(Blueprintcallable, Category = "Epic Category")
		FString getLeft();

	UFUNCTION(Blueprintcallable, Category = "Epic Category")
		FString getRight();

	UFUNCTION(Blueprintcallable, Category = "Epic Category")
		FVector startOfRiver();

	UFUNCTION(Blueprintcallable, Category = "Epic Category")
		FVector endOfRiver();

	UFUNCTION(Blueprintcallable, Category = "Epic Category")
		void VisitStart();

	UFUNCTION(Blueprintcallable, Category = "Epic Category")
		void VisitEnd();

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
		USceneComponent* start;

	UPROPERTY(EditAnywhere)
		USceneComponent* end;

	UPROPERTY(EditAnywhere)
		FString leftName;

	UPROPERTY(EditAnywhere)
		FString rightName;

	virtual bool Completed() override;
	virtual void reset() override;

private:
	FVector riverStart;
	FVector riverEnd;
	bool visitedStart;
	bool visitedEnd;

};
