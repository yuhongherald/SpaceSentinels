// Fill out your copyright notice in the Description page of Project Settings.

#include "MyProject.h"
#include "STutorialWindow.h"
#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void STutorialWindow::Construct(const FArguments& InArgs)
{
	OwnerHUD = InArgs._OwnerHUD;
	ChildSlot
	[
		SNew(SOverlay)
		+SOverlay::Slot()
		[
			SNew(SEditableTextBox)
			.BackgroundColor(FLinearColor(.2, .2, .2, .7))
		]
		+SOverlay::Slot()
		[
			SNew(SVerticalBox)
			+SVerticalBox::Slot()
			.AutoHeight()
			[
				SAssignNew(title, STextBlock)
				.ColorAndOpacity(FLinearColor(1, 1, 1, 1))
				.Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Bold.ttf"), 80))
			]
			+SVerticalBox::Slot()
			[
				SAssignNew(instructions, STextBlock)
				.AutoWrapText(true)
				.ColorAndOpacity(FLinearColor(1, 1, 1, 1))
				.Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Bold.ttf"), 50))
			]
			+SVerticalBox::Slot()
				.AutoHeight()
			[
				SNew(SHorizontalBox)
				+SHorizontalBox::Slot()
				[
					SAssignNew(previous, SButton)
					.OnClicked(this, &STutorialWindow::Next)
				]
				+SHorizontalBox::Slot()
				[
					SAssignNew(pageNumber, STextBlock)
					.Justification(ETextJustify::Center)
					.ColorAndOpacity(FLinearColor(1, 1, 1, 1))
					.Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Bold.ttf"), 40))
				]
				+SHorizontalBox::Slot()
				[
					SAssignNew(next, SButton)
					.OnClicked(this, &STutorialWindow::Previous)
				]
			]
		]
	];
	SetRenderTransform(FSlateRenderTransform(0.4, FVector2D(800, 200)));
	listOfLvlHints.Insert(TArray<FText>(), listOfLvlHints.Num());
	lvlUiBlockers.Insert(TArray<TArray<int>>(), lvlUiBlockers.Num());
	listOfLvlHints[0].Insert(FText::FromString("Welcome to the Glass Bead Game. The soldier is our programmable robot. Try clicking on it!"),
		listOfLvlHints[0].Num());
	lvlUiBlockers[0].Insert(TArray<int>(), lvlUiBlockers[0].Num());
	lvlUiBlockers[0][0].Insert(0, lvlUiBlockers[0][0].Num());
	listOfLvlHints[0].Insert(FText::FromString("Currently there is a simple program template loaded in the robot. Press play and observe what it does!"),
		listOfLvlHints[0].Num());
	lvlUiBlockers[0].Insert(TArray<int>(), lvlUiBlockers[0].Num());
	lvlUiBlockers[0][1].Insert(NameToIndex(FText::FromString("Console Run Button")), lvlUiBlockers[0][1].Num());
	NextLevel(FText::FromString("Introduction"));

	for (int i = 0; i < 13; i++){
		allBlockers.Insert(i, i);
	}
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

void STutorialWindow::NextLevel(FText Title) {
	title->SetText(Title);
	page = 0;
	initialTutorial = true;
	level++;
	pageNumber->SetText(FText::FromString(FString::FromInt(page + 1)));
	instructions->SetText(listOfLvlHints[level][page]);
	OwnerHUD->MyUIWidget->Cover();
	OwnerHUD->MyUIWidget->Uncover(lvlUiBlockers[level][page]);
	next->SetVisibility(EVisibility::Hidden);
	previous->SetVisibility(EVisibility::Hidden);
}

void STutorialWindow::ExternalNext() {
	if (initialTutorial) {
		OwnerHUD->MyUIWidget->Cover();
		Next();
	}
}

FReply STutorialWindow::Next() {
	page++;
	if (page >= listOfLvlHints[level].Num()) {
		page = 0;
		SetVisibility(EVisibility::Hidden);
		next->SetVisibility(EVisibility::Visible);
		previous->SetVisibility(EVisibility::Visible);
		OwnerHUD->MyUIWidget->Uncover(allBlockers);
		initialTutorial = false;
	}
	else {
		OwnerHUD->MyUIWidget->Uncover(lvlUiBlockers[level][page]);
	}
	pageNumber->SetText(FText::FromString(FString::FromInt(page + 1)));
	instructions->SetText(listOfLvlHints[level][page]);
	return FReply::Handled();
}

FReply STutorialWindow::Previous() {
	if (page > 0) {
		page--;
		pageNumber->SetText(FText::FromString(FString::FromInt(page)));
		instructions->SetText(listOfLvlHints[level][page]);
	}
	return FReply::Handled();
}

int STutorialWindow::NameToIndex(FText name) {
	if (name.EqualTo(FText::FromString("Console Label"))) {
		return 1;
	}
	else if (name.EqualTo(FText::FromString("Console Run Button"))) {
		return 2;
	}
	else if (name.EqualTo(FText::FromString("Console To Interpreter"))) {
		return 3;
	}
	else if (name.EqualTo(FText::FromString("Console Close Button"))) {
		return 4;
	}
	else if (name.EqualTo(FText::FromString("Console Program Input"))) {
		return 5;
	}
	else if (name.EqualTo(FText::FromString("Interpreter To Console"))) {
		return 8;
	}
	else if (name.EqualTo(FText::FromString("Interpreter Close Button"))) {
		return 9;
	}
	else {
		return 0;
	}
}