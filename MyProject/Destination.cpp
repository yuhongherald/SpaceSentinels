// Fill out your copyright notice in the Description page of Project Settings.

#include "MyProject.h"
#include "Destination.h"
#include "Information.h"


// Sets default values
ADestination::ADestination()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	USceneComponent* root = CreateDefaultSubobject<USceneComponent>("root");
}

// Called when the game starts or when spawned
void ADestination::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADestination::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

bool ADestination::Completed()
{
	AInformation* hud = Cast<AInformation>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());
	return hud->GetPObject()->Near(GetActorLocation());
}