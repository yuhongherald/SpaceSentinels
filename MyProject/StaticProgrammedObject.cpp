// Fill out your copyright notice in the Description page of Project Settings.

#include "MyProject.h"
#include "StaticProgrammedObject.h"


// Sets default values
AStaticProgrammedObject::AStaticProgrammedObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<UBoxComponent>(TEXT("Root"));
	MyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MyMesh"));
	MyMesh->SetupAttachment(Root);

}

// Called when the game starts or when spawned
void AStaticProgrammedObject::BeginPlay()
{
	Super::BeginPlay();
	initialLocation = GetActorLocation();
	initialRotate = GetActorRotation();
	currentLocation = initialLocation;
	destination = initialLocation;


}

// Called every frame
void AStaticProgrammedObject::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	if (currentLocation.Equals(destination)) {
	}
	else {
		currentLocation = FMath::VInterpConstantTo(currentLocation, destination, DeltaTime, velocity);
		SetActorLocation(currentLocation);
	}
	if (desiredAngle != 0) {
		float diff = DeltaTime * TurnRate * FMath::Sign(desiredAngle);
		if (FMath::Abs(diff) >= FMath::Abs(desiredAngle)) {
			SetActorRotation(GetActorQuat() * FQuat(FVector(0, 0, 1), desiredAngle));
			desiredAngle = 0;
		}
		else {
			SetActorRotation(GetActorQuat() * FQuat(FVector(0, 0, 1), diff));
			desiredAngle -= diff;
		}
	}
}

FText AStaticProgrammedObject::GetCmd()
{
	FString InFilename = FPaths::GameContentDir() + ProgramFile;
	TArray<FString> OutStrings;
	FFileHelper::LoadFileToString(ProgramFromFile, InFilename.operator*());
	for (FString Async : AsyncOverrides)
	{
		ProgramFromFile = ProgramFromFile.Replace(Async.operator*(), FString("async ").Append(Async).operator*());
	}
	for (FString Await : AwaitOverrides)
	{
		ProgramFromFile = ProgramFromFile.Replace(Await.operator*(), FString("await ").Append(Await).operator*());
	}
	return FText::FromString(ProgramFromFile);
}

FText AStaticProgrammedObject::GetLib()
{
	return lib;
}

int AStaticProgrammedObject::TurnTo(FVector destin) {
	FVector difference = destin - currentLocation;
	difference.Normalize();
	FVector forward = GetActorRightVector();
	float product = FVector::DotProduct(difference, forward);
	float diff = 0;
	if (product == 0) {
		diff = PI / 2 * FMath::Sign(FVector::CrossProduct(forward, difference).Z);
	}
	else {
		//Strangely Acos only returns 0 to PI/2...
		diff = FMath::Acos(product) * FMath::Sign(FVector::CrossProduct(forward, difference).Z);
	}
	desiredAngle += diff;
	return FMath::Abs(diff * 1000 / TurnRate);
}

int AStaticProgrammedObject::WalkTo(FVector destin, float speed) {
	destination = destin;
	velocity = speed;
	return FVector::Dist(currentLocation, destination) * 1000 / speed;
}

bool AStaticProgrammedObject::Near(FVector location)
{
	return FVector::Dist(currentLocation, location) < 50;
}

void AStaticProgrammedObject::reset() {
	currentLocation = initialLocation;
	destination = initialLocation;
	desiredAngle = 0;
	SetActorLocation(initialLocation);
	SetActorRotation(initialRotate);
}
