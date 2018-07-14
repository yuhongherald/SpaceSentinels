// Fill out your copyright notice in the Description page of Project Settings.

#include "MyProject.h"
#include "JavascriptHolder.h"

// Sets default values
AJavascriptHolder::AJavascriptHolder()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AJavascriptHolder::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AJavascriptHolder::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AJavascriptHolder::reset()
{
	TArray<UActorComponent*> temp = GetComponents().Array();
	for (int i = 0; i < temp.Num(); i++) {
		temp[i]->Deactivate();
		temp[i]->Activate();
	}
}