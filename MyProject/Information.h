// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/HUD.h"
#include "Cube.h"
#include "SMyConsole.h"
#include "STutorialWindow.h"
#include "JavascriptHolder.h"
#include "Interactable.h"
#include "Objective.h"
#include "StaticProgrammedObject.h"
#include "Resettable.h"
#include "Information.generated.h"

/**
 * 
 */

class SMyConsole;
class STutorialWindow;



UCLASS()
class MYPROJECT_API AInformation : public AHUD
{
	GENERATED_BODY()

	AInformation();

	virtual void DrawHUD() override;

public:

	TSharedPtr<SMyConsole> MyUIWidget;
	TSharedPtr<STutorialWindow> tutorialWindow;
	ACube* CurrentObject;
	TArray<AStaticProgrammedObject*> StaticObjects;

	void BeginPlay();
	void SetString(FString name);
	void SetProgram(FText program, ACube* CurObject);
	void Save(FText program);
	void ClearProgram();

	UFUNCTION(Blueprintcallable, Category = "Epic Category")
		TArray<AStaticProgrammedObject*> GetStatics();

	UFUNCTION(Blueprintcallable, Category = "Epic Category")
		FText GetCmd();

	UFUNCTION(Blueprintcallable, Category = "Epic Category")
		FText GetEnv();

	UFUNCTION(Blueprintcallable, Category = "Epic Category")
		FText GetLib();

	UFUNCTION(Blueprintcallable, Category = "Epic Category")
		void SetCmd(FText cmdstring, FText environment);

	UFUNCTION(Blueprintcallable, Category = "Epic Category")
		void Output(FText reply);

	UFUNCTION(Blueprintcallable, Category = "Epic Category")
		ACube* GetPObject();

	UFUNCTION(Blueprintcallable, Category = "Epic Category")
		void Reset();

	UFUNCTION(Blueprintcallable, Category = "Epic Category")
		AInteractable* GetInteractable(FString name);

	UFUNCTION(Blueprintcallable, Category = "Epic Category")
		AJavascriptHolder* getSignal();

	UFUNCTION(Blueprintcallable, Category = "Epic Category")
		void nextLevel();

private:

	UFont* HUDFont;
	FString display;
	FText CurrentProgram;
	FText Cmd;
	FText Env;
	AJavascriptHolder* javascript;
	TArray<AInteractable*> interactable;
	TArray<AObjective*> objectives;
	TArray<AResettable*> resets;

};
