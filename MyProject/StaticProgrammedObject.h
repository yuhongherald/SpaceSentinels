// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Resettable.h"
#include "GameFramework/Actor.h"
#include "StaticProgrammedObject.generated.h"

UCLASS()
class MYPROJECT_API AStaticProgrammedObject : public AResettable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStaticProgrammedObject();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	virtual void reset() override;

	UPROPERTY(EditAnywhere)
		UShapeComponent* Root;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* MyMesh;

	UPROPERTY(EditAnywhere)
		FString ProgramFile;
	
	UPROPERTY(EditAnywhere)
		FText lib;

	UPROPERTY(EditAnywhere)
		TArray<FString> AsyncOverrides;

	UPROPERTY(EditAnywhere)
		TArray<FString> AwaitOverrides;

	UFUNCTION(Blueprintcallable, Category = "Epic Category")
		FText GetCmd();

	UFUNCTION(Blueprintcallable, Category = "Epic Category")
		FText GetLib();

	UFUNCTION(Blueprintcallable, Category = "Epic Category")
		int TurnTo(FVector destin);

	UFUNCTION(Blueprintcallable, Category = "Epic Category")
		int WalkTo(FVector destin, float speed);

	UFUNCTION(Blueprintcallable, Category = "Epic Category")
		bool Near(FVector location);


private:

	FString ProgramFromFile;
	FVector initialLocation;
	FRotator initialRotate;
	FVector currentLocation;
	FVector destination;

	float velocity;
	float desiredAngle;

	float TurnRate = PI;

};
