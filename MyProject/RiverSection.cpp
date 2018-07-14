// Fill out your copyright notice in the Description page of Project Settings.

#include "MyProject.h"
#include "RiverSection.h"


// Sets default values
ARiverSection::ARiverSection()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	start = CreateDefaultSubobject<USceneComponent>(TEXT("start"));
	start->SetupAttachment(Mesh);
	end = CreateDefaultSubobject<USceneComponent>(TEXT("end"));
	end->SetupAttachment(Mesh);
}

// Called when the game starts or when spawned
void ARiverSection::BeginPlay()
{
	Super::BeginPlay();
	visitedStart = false;
	visitedEnd = false;
	riverStart = start->GetComponentLocation();
	riverEnd = end->GetComponentLocation();
}

// Called every frame
void ARiverSection::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

FString ARiverSection::getLeft()
{
	return leftName;
}

FString ARiverSection::getRight()
{
	return rightName;
}

FVector ARiverSection::startOfRiver()
{
	return riverStart;
}

FVector ARiverSection::endOfRiver()
{
	return riverEnd;
}

void ARiverSection::VisitStart()
{
	visitedStart = true;
}

void ARiverSection::VisitEnd()
{
	visitedEnd = true;
}

bool ARiverSection::Completed()
{
	return itemName.Equals("") || visitedStart && visitedEnd;
}

void ARiverSection::reset()
{
	visitedStart = false;
	visitedEnd = false;
}