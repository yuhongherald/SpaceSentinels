// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Resettable.h"
#include "Cube.generated.h"

UCLASS()
class MYPROJECT_API ACube : public AResettable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACube();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UPROPERTY(EditAnywhere)
		UShapeComponent* Root;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* MyMesh;

	UPROPERTY(EditAnywhere)
		UShapeComponent* HitBox;
	
	UPROPERTY(EditAnywhere)
		USkeletalMeshComponent* MySkel;

	UPROPERTY(EditAnywhere)
		UAnimationAsset* IdleAnim;

	UPROPERTY(EditAnywhere)
		UAnimationAsset* WalkAnim;

	UPROPERTY(EditAnywhere)
		FString Name;

	UPROPERTY(EditAnywhere)
		FText MyProgram;

	UPROPERTY(EditAnywhere)
		FString ProgramFile;

	UPROPERTY(EditAnywhere)
		FText MyLibrary;

	UPROPERTY(EditAnywhere)
		TArray<FString> AsyncOverrides;

	UPROPERTY(EditAnywhere)
		TArray<FString> AwaitOverrides;

	UFUNCTION()
		void OnPlayerClick(AActor* TouchedActor, FKey ButtonPressed);

	UFUNCTION()
		void OnPlayerOver(AActor* TouchedComponent);

	UFUNCTION()
		void OnPlayerOff(AActor* TouchedComponent);

	UFUNCTION()
		void SetProgram(FText program);

	UFUNCTION()
		void AddInteractable(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

	UFUNCTION()
		void RemoveInteractable(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(Blueprintcallable, Category = "Epic Category")
		void MoveCharacter(float x, float y, float z, float speed);

	UFUNCTION(Blueprintcallable, Category = "Epic Category")
		void Walk(float distance, float speed);

	UFUNCTION(Blueprintcallable, Category = "Epic Category")
		int TurnTo(FVector destin);

	UFUNCTION(Blueprintcallable, Category = "Epic Category")
		int WalkTo(FVector destin, float speed);

	UFUNCTION(Blueprintcallable, Category = "Epic Category")
		void Turn(float angle);

	UFUNCTION(Blueprintcallable, Category = "Epic Category")
		bool Near(FVector location);

	virtual void reset() override;
	void nextLevel();

private:
	FVector initialLocation;
	FRotator initialRotate;
	FVector currentLocation;
	FVector destination;
	float desiredAngle = 0;
	TArray<AActor*> InteractableObjects;
	float velocity = 0;
	float TurnRate = PI;
	bool walking = false;
	bool IsReset = false;

};
