// Fill out your copyright notice in the Description page of Project Settings.

#include "MyProject.h"
#include "PickUpSquare.h"
#include "Pickup.h"


// Sets default values
APickUpSquare::APickUpSquare()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Root"));
}

// Called when the game starts or when spawned
void APickUpSquare::BeginPlay()
{
	Super::BeginPlay();

	APickup* temp;

	// creates a 3 x 3 square of pickups excluding center
	for (int i = -1; i < 2; i++) {
		for (int j = -1; j < 2; j++) {
			if (i != 0 || j != 0) {
				FVector Location(i * distance, j * distance, 0.0f);
				temp = GetWorld()->SpawnActor<APickup>(APickup::StaticClass(), GetActorLocation() + Location, FRotator::ZeroRotator);
				temp->SetMesh(PickUpMesh);
			}
		}
	}

	/*
	pickups.SetNum(8);

	pickups.Insert(GetWorld()->SpawnActor<APickup>(GetActorLocation() + FVector(distance, 0, 0), FRotator::ZeroRotator), pickups.Num());
	pickups.Insert(GetWorld()->SpawnActor<APickup>(GetActorLocation() + FVector(distance, distance, 0), FRotator::ZeroRotator), pickups.Num());
	pickups.Insert(GetWorld()->SpawnActor<APickup>(GetActorLocation() + FVector(0, distance, 0), FRotator::ZeroRotator), pickups.Num());
	pickups.Insert(GetWorld()->SpawnActor<APickup>(GetActorLocation() + FVector(-distance, 0, 0), FRotator::ZeroRotator), pickups.Num());
	pickups.Insert(GetWorld()->SpawnActor<APickup>(GetActorLocation() + FVector(0, -distance, 0), FRotator::ZeroRotator), pickups.Num());
	pickups.Insert(GetWorld()->SpawnActor<APickup>(GetActorLocation() + FVector(-distance, -distance, 0), FRotator::ZeroRotator), pickups.Num());
	pickups.Insert(GetWorld()->SpawnActor<APickup>(GetActorLocation() + FVector(distance, -distance, 0), FRotator::ZeroRotator), pickups.Num());
	pickups.Insert(GetWorld()->SpawnActor<APickup>(GetActorLocation() + FVector(-distance, distance, 0), FRotator::ZeroRotator), pickups.Num());
	for (int i = 0; i < 8; i++) {
		pickups[i]->SetMesh(PickUpMesh);
	}
	*/
}

// Called every frame
void APickUpSquare::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}
