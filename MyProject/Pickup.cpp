// Fill out your copyright notice in the Description page of Project Settings.

#include "MyProject.h"
#include "Pickup.h"


// Sets default values
APickup::APickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MyMesh"));
	MyMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	HitBox = CreateDefaultSubobject <UBoxComponent>(TEXT("HitBox"));
	HitBox->SetWorldScale3D(FVector(2, 2, 2));
	HitBox->SetupAttachment(MyMesh);
	HitBox->OnComponentBeginOverlap.AddDynamic(this, &APickup::Collide);
}

// Called when the game starts or when spawned
void APickup::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APickup::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void APickup::SetMesh(UStaticMesh* Model)
{
	MyMesh->SetStaticMesh(Model);
	MyMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

bool APickup::Completed()
{
	return bHidden;
}

void APickup::Collide(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	SetActorHiddenInGame(true);
}

void APickup::reset()
{
	SetActorHiddenInGame(false);
}