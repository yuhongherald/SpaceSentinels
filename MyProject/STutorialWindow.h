// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "Widgets/SCompoundWidget.h"
#include "Information.h"

/**
 * 
 */
class MYPROJECT_API STutorialWindow : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(STutorialWindow)
	{}

	SLATE_ARGUMENT(TWeakObjectPtr<class AInformation>, OwnerHUD)

	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);
	void NextLevel(FText Title);
	void ExternalNext();

private:
	TWeakObjectPtr<class AInformation> OwnerHUD;
	TSharedPtr<STextBlock> title;
	TSharedPtr<STextBlock> instructions;
	TSharedPtr<STextBlock> pageNumber;
	TSharedPtr<SButton> previous;
	TSharedPtr<SButton> next;
	TArray<TArray<FText>> listOfLvlHints;
	TArray<TArray<TArray<int>>> lvlUiBlockers;
	TArray<int> allBlockers;
	int NameToIndex(FText name);
	FReply Next();
	FReply Previous();
	int level = -1;
	int page = 0;
	bool initialTutorial = false;
};
