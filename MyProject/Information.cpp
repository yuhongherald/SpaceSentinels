// Fill out your copyright notice in the Description page of Project Settings.

#include "MyProject.h"
#include "Information.h"
#include "Engine/Canvas.h"
#include "Engine/Font.h"
#include "SlateBasics.h"
#include "Cube.h"
#include "SMyConsole.h"
#include "STutorialWindow.h"
#include "JavascriptHolder.h"
#include "StaticProgrammedObject.h"
#include "Interactable.h"
#include "Objective.h"
#include "Resettable.h"


AInformation::AInformation()
{
	// Use the RobotoDistanceField font from the Engine.
	static ConstructorHelpers::FObjectFinder<UFont>HUDFontOb(TEXT("/Engine/EngineFonts/RobotoDistanceField"));
	
	HUDFont = HUDFontOb.Object;
	display = "";
}

void AInformation::BeginPlay()
{
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/////So far only TSharedPtr<SMyUIWidget> has been created, now create the actual object.
	/////Create a SMyUIWidget on heap, our MyUIWidget shared pointer provides handle to object
	/////Widget will not self-destruct unless the HUD's SharedPtr (and all other SharedPtrs) destruct first.
	MyUIWidget = SNew(SMyConsole).OwnerHUD(this);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/////Pass our viewport a weak ptr to our widget
	/////Viewport's weak ptr will not give Viewport ownership of Widget
	GEngine->GameViewport->AddViewportWidgetContent(SNew(SWeakWidget).PossiblyNullContent(MyUIWidget.ToSharedRef()), 0);
	MyUIWidget->SetVisibility(EVisibility::Hidden);

	tutorialWindow = SNew(STutorialWindow).OwnerHUD(this);
	GEngine->GameViewport->AddViewportWidgetContent(SNew(SWeakWidget).PossiblyNullContent(tutorialWindow.ToSharedRef()), 1);
	tutorialWindow->SetVisibility(EVisibility::Visible);

	//Get all interactable objects
	for (TActorIterator<AInteractable> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		// Same as with the Object Iterator, access the subclass instance with the * or -> operators.
		interactable.Insert(*ActorItr, interactable.Num());
	}

	//Get all objectives
	for (TActorIterator<AObjective> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		objectives.Insert(*ActorItr, objectives.Num());
	}

	//Get all resets
	for (TActorIterator<AResettable> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		resets.Insert(*ActorItr, resets.Num());
	}

	//Get all static objects
	for (TActorIterator<AStaticProgrammedObject> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		StaticObjects.Insert(*ActorItr, StaticObjects.Num());
	}

	//Create identity Actor for marking resets
	javascript = GetWorld()->SpawnActor<AJavascriptHolder>(AJavascriptHolder::StaticClass(), GetActorLocation(), FRotator::ZeroRotator);
}

void AInformation::DrawHUD()
{
	// Get the screen dimensions
	FVector2D ScreenDimensions = FVector2D(Canvas->SizeX, Canvas->SizeY);
	// Call to the parent versions of DrawHUD
	Super::DrawHUD();

	DrawText(display, FColor::White, 50, 50, HUDFont);
}

void AInformation::SetString(FString name)
{
	display = name;
}

void AInformation::SetProgram(FText program, ACube* CurObject)
{
	CurrentProgram = program;
	CurrentObject = CurObject;
	MyUIWidget->ToggleConsole(display);
	MyUIWidget->SetVisibility(EVisibility::Visible);
	MyUIWidget->Load(program);
}

void AInformation::Save(FText program)
{
	CurrentProgram = program;
	CurrentObject->SetProgram(program);
}

void AInformation::ClearProgram()
{
	CurrentProgram = FText();
	MyUIWidget->SetVisibility(EVisibility::Hidden);
}

TArray<AStaticProgrammedObject*> AInformation::GetStatics()
{
	return StaticObjects;
}

FText AInformation::GetCmd()
{
	return Cmd;
}

FText AInformation::GetEnv()
{
	return Env;
}

FText AInformation::GetLib()
{
	return CurrentObject->MyLibrary;
}

void AInformation::SetCmd(FText cmdstring, FText environment)
{
	Cmd = cmdstring;
	Env = environment;
}

void AInformation::Output(FText reply)
{
	MyUIWidget->Output(reply);
}

ACube* AInformation::GetPObject() {
	return CurrentObject;
}

void AInformation::Reset() {
	javascript->Destroy();
	javascript = GetWorld()->SpawnActor<AJavascriptHolder>(AJavascriptHolder::StaticClass(), GetActorLocation(), FRotator::ZeroRotator);
	for (int i = 0; i < resets.Num(); i++) {
		resets[i]->reset();
	}
}

AInteractable* AInformation::GetInteractable(FString name) {
	for (int i = 0; i < interactable.Num(); i++) {
		if (interactable[i]->itemName.Equals(name)) {
			return interactable[i];
		}
	}
	return NULL;
}

void AInformation::nextLevel() {
	for (int i = 0; i < objectives.Num(); i++) {
		//exit if objective incomplete
		if (!objectives[i]->Completed()) {
			return;
		}
	}
	GetPObject()->nextLevel();
}

AJavascriptHolder* AInformation::getSignal() {
	return javascript;
}