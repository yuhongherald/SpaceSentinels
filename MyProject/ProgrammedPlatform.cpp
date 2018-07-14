// Fill out your copyright notice in the Description page of Project Settings.

#include "MyProject.h"
#include "ProgrammedPlatform.h"


// Sets default values
AProgrammedPlatform::AProgrammedPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AProgrammedPlatform::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProgrammedPlatform::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AProgrammedPlatform::SetState(int newState)
{
	state = newState;
}

int AProgrammedPlatform::GetState()
{
	return state;
}

void AProgrammedPlatform::RootPlayer(AActor* player)
{
	player->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
}

void AProgrammedPlatform::UnrootPlayer(AActor* player)
{
	player->DetachRootComponentFromParent();
}