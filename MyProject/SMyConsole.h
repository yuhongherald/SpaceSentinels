// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "Widgets/SCompoundWidget.h"
#include "Information.h"

/**
 * 
 */
class MYPROJECT_API SMyConsole : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SMyConsole)
	{}

	SLATE_ARGUMENT(TWeakObjectPtr<class AInformation>, OwnerHUD)

	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);
	void Load(FText program);
	void Output(FText reply);
	void ToggleConsole(FString display);
	void Uncover(TArray<int> indices);
	void Cover();

private:
	void Save(const FText& InText);
	void OnReleaseRowForList(const TSharedRef<ITableRow>& OnWidgetToBeRemoved);
	void ToggleInterpreter();
	TSharedRef<ITableRow> OnGenerateRowForList(TSharedPtr<FText> Item, const TSharedRef<STableViewBase>& OwnerTable);
	FReply ConsoleKeys(const FGeometry& geom, const FKeyEvent& KeyPressed);
	FReply InterpreterKeys(const FGeometry& geom, const FKeyEvent& KeyPressed);
	FReply ShowInterpreter();
	FReply ShowConsole();
	FReply Advance();
	FReply RunProgram();
	FReply ExecuteInterpreter();
	FReply Close();
	FReply DeleteAllRows();

	TWeakObjectPtr<class AInformation> OwnerHUD;
	TSharedPtr<class SMultiLineEditableTextBox> TextBox;
	TSharedPtr<class SEditableTextBox> Interpreter;
	TSharedPtr<class STextBlock> label1;
	TArray<TSharedPtr<class STextBlock>> blocker;
	TArray<TSharedPtr<class SEditableTextBox>> blocker2;
	TArray<TSharedPtr<class FText>> blocks;
	TSharedPtr<class SListView<TSharedPtr<FText>>> MyListWidget;
	FString PathToCloseImage;
	FString PathToPlayImage;
	FString PathToSaveImage;
	FString PathToJSImage;
	FString PathToInterpreterImage;
};
