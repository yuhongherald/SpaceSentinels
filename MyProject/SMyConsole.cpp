// Fill out your copyright notice in the Description page of Project Settings.

#include "MyProject.h"
#include "SMyConsole.h"
#include "SlateOptMacros.h"
#include "Information.h"
#include "STutorialWindow.h"
#include <algorithm>

#define LOCTEXT_NAMESPACE "SMyConsole"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SMyConsole::Construct(const FArguments& InArgs)
{
	OwnerHUD = InArgs._OwnerHUD;
	PathToCloseImage = FPaths::GameContentDir() + TEXT("custom/close_button.png");
	PathToPlayImage = FPaths::GameContentDir() + TEXT("custom/play_button.png");
	PathToSaveImage = FPaths::GameContentDir() + TEXT("custom/save.png");
	PathToJSImage = FPaths::GameContentDir() + TEXT("custom/javascript.png");
	PathToInterpreterImage = FPaths::GameContentDir() + TEXT("custom/interpreter.png");
	blocker.SetNum(13);
	blocker2.SetNum(13);
	ChildSlot
	[
		SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		.FillHeight(25)
		[
			SNew(SOverlay)
			+ SOverlay::Slot()
			[
				SNew(STextBlock)
			]
			+ SOverlay::Slot()
			[
				SAssignNew(blocker2[0], SEditableTextBox)
				.Visibility(EVisibility::Collapsed)
			]
			+ SOverlay::Slot()
			[
				SAssignNew(blocker[0], STextBlock)
				.Visibility(EVisibility::Collapsed)
			]
		]
		+ SVerticalBox::Slot()
		.FillHeight(25)
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			.FillWidth(400)
			[
				SNew(SOverlay)
				+ SOverlay::Slot()
				[
					SAssignNew(label1, STextBlock)
					.ColorAndOpacity(FLinearColor::White)
					.Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Bold.ttf"), 32))
				]
				+ SOverlay::Slot()
				[
					SAssignNew(blocker2[1], SEditableTextBox)
					.Visibility(EVisibility::Collapsed)
				]
				+ SOverlay::Slot()
				[
					SAssignNew(blocker[1], STextBlock)
					.Visibility(EVisibility::Collapsed)
				]
			]
			+ SHorizontalBox::Slot()
			.FillWidth(25)
			[
				SNew(SOverlay)
				+ SOverlay::Slot()
				[
					SNew(SBox)
					.HeightOverride(32)
					.WidthOverride(32)
					[
						SNew(SButton)
						.OnClicked(this, &SMyConsole::Advance)
						.ContentPadding(FMargin())
						[
							SNew(SImage)
							.Image(new FSlateDynamicImageBrush(FName(*PathToPlayImage), FVector2D(32, 32)))
						]
					]
				]
				+ SOverlay::Slot()
				[
					SAssignNew(blocker2[12], SEditableTextBox)
					.Visibility(EVisibility::Collapsed)
				]
				+ SOverlay::Slot()
				[
					SAssignNew(blocker[12], STextBlock)
					.Visibility(EVisibility::Collapsed)
				]
			]
			+ SHorizontalBox::Slot()
			.FillWidth(25)
			[
				SNew(SOverlay)
				+ SOverlay::Slot()
				[
					SNew(SBox)
					.HeightOverride(32)
					.WidthOverride(32)
					[
						SNew(SButton)
						.OnClicked(this, &SMyConsole::RunProgram)
						.ContentPadding(FMargin())
						[
							SNew(SImage)
							.Image(new FSlateDynamicImageBrush(FName(*PathToPlayImage), FVector2D(32, 32)))
						]
					]
				]
				+ SOverlay::Slot()
				[
					SAssignNew(blocker2[2], SEditableTextBox)
					.Visibility(EVisibility::Collapsed)
				]
				+ SOverlay::Slot()
				[
					SAssignNew(blocker[2], STextBlock)
					.Visibility(EVisibility::Collapsed)
				]
			]
			+ SHorizontalBox::Slot()
				.FillWidth(25)
			[
				SNew(SOverlay)
				+ SOverlay::Slot()
				[
					SNew(SBox)
					.HeightOverride(32)
					.WidthOverride(32)
					[
						SNew(SButton)
						.OnClicked(this, &SMyConsole::ShowInterpreter)
						.ContentPadding(FMargin())
						[
							SNew(SImage)
							.Image(new FSlateDynamicImageBrush(FName(*PathToInterpreterImage), FVector2D(32, 32)))
						]
					]
				]
				+ SOverlay::Slot()
				[
					SAssignNew(blocker2[3], SEditableTextBox)
					.Visibility(EVisibility::Collapsed)
				]
				+ SOverlay::Slot()
				[
					SAssignNew(blocker[3], STextBlock)
					.Visibility(EVisibility::Collapsed)
				]
			]
			+ SHorizontalBox::Slot()
			.FillWidth(25)
			[
				SNew(SOverlay)
				+ SOverlay::Slot()
				[
					SNew(SBox)
					.HeightOverride(32)
					.WidthOverride(32)
					[
						SNew(SButton)
						.OnClicked(this, &SMyConsole::Close)
						.ContentPadding(FMargin())
						[
							SNew(SImage)
							.Image(new FSlateDynamicImageBrush(FName(*PathToCloseImage), FVector2D(32, 32)))
						]
					]
				]
				+ SOverlay::Slot()
				[
					SAssignNew(blocker2[4], SEditableTextBox)
					.Visibility(EVisibility::Collapsed)
				]
				+ SOverlay::Slot()
				[
					SAssignNew(blocker[4], STextBlock)
					.Visibility(EVisibility::Collapsed)
				]
			]
		]
		+ SVerticalBox::Slot()
		.FillHeight(400)
		[
			SNew(SOverlay)
			+ SOverlay::Slot()
			[
				SAssignNew(TextBox, SMultiLineEditableTextBox)
				.AlwaysShowScrollbars(true)
				.AutoWrapText(true)
				.Font(FSlateFontInfo("Verdana", 16))
				.OnTextChanged(this, &SMyConsole::Save)
				//Causes seek to jump
				//.OnKeyDownHandler(this, &SMyConsole::ConsoleKeys)
			]
			+ SOverlay::Slot()
			[
				SAssignNew(blocker2[5], SEditableTextBox)
				.Visibility(EVisibility::Collapsed)
			]
			+ SOverlay::Slot()
			[
				SAssignNew(blocker[5], STextBlock)
				.Visibility(EVisibility::Collapsed)
			]
		]
		+ SVerticalBox::Slot()
		.Padding(5)
		.FillHeight(400)
		[
			SNew(SOverlay)
			+ SOverlay::Slot()
			[
				SNew(STextBlock)
			]
			+ SOverlay::Slot()
			[
				SAssignNew(blocker2[6], SEditableTextBox)
				.Visibility(EVisibility::Collapsed)
			]
			+ SOverlay::Slot()
			[
				SAssignNew(blocker[6], STextBlock)
				.Visibility(EVisibility::Collapsed)
			]
		]
		+ SVerticalBox::Slot()
		.Padding(5)
		.FillHeight(25)
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			.Padding(5)
			.FillWidth(400)
			[
				SNew(SOverlay)
				+ SOverlay::Slot()
				[
					SNew(STextBlock)
				]
				+ SOverlay::Slot()
				[
					SAssignNew(blocker2[7], SEditableTextBox)
					.Visibility(EVisibility::Collapsed)
				]
				+ SOverlay::Slot()
				[
					SAssignNew(blocker[7], STextBlock)
					.Visibility(EVisibility::Collapsed)
				]
			]
			+ SHorizontalBox::Slot()
			.FillWidth(25)
			[
				SNew(SOverlay)
				+ SOverlay::Slot()
				[
					SNew(SBox)
					.HeightOverride(32)
					.WidthOverride(32)
					[
						SNew(SButton)
						.OnClicked(this, &SMyConsole::ShowConsole)
						.ContentPadding(FMargin())
						[
							SNew(SImage)
							.Image(new FSlateDynamicImageBrush(FName(*PathToJSImage), FVector2D(32, 32)))
						]
					]
				]
			+ SOverlay::Slot()
				[
					SAssignNew(blocker2[8], SEditableTextBox)
					.Visibility(EVisibility::Collapsed)
				]
			+ SOverlay::Slot()
				[
					SAssignNew(blocker[8], STextBlock)
					.Visibility(EVisibility::Collapsed)
				]
			]
			+ SHorizontalBox::Slot()
			.FillWidth(25)
			[
				SNew(SOverlay)
				+ SOverlay::Slot()
				[
					SNew(SBox)
					.HeightOverride(32)
					.WidthOverride(32)
					[
						SNew(SButton)
						.OnClicked(this, &SMyConsole::Close)
						.ContentPadding(FMargin())
						[
							SNew(SImage)
							.Image(new FSlateDynamicImageBrush(FName(*PathToCloseImage), FVector2D(32, 32)))
						]
					]
				]
				+ SOverlay::Slot()
				[
					SAssignNew(blocker2[9], SEditableTextBox)
					.Visibility(EVisibility::Collapsed)
				]
				+ SOverlay::Slot()
				[
					SAssignNew(blocker[9], STextBlock)
					.Visibility(EVisibility::Collapsed)
				]
			]
		]
		+ SVerticalBox::Slot()
		.Padding(5)
		.FillHeight(50)
		[
			SNew(SOverlay)
			+ SOverlay::Slot()
			[
				SAssignNew(MyListWidget, SListView<TSharedPtr<FText>>)
				.ListItemsSource(&blocks)
				.WheelScrollMultiplier(30)
				.OnGenerateRow(this, &SMyConsole::OnGenerateRowForList)
				.OnRowReleased(this, &SMyConsole::OnReleaseRowForList)
			]
			+ SOverlay::Slot()
			[
				SAssignNew(blocker2[10], SEditableTextBox)
				.Visibility(EVisibility::Collapsed)
			]
			+ SOverlay::Slot()
			[
				SAssignNew(blocker[10], STextBlock)
				.Visibility(EVisibility::Collapsed)
			]
		]
		+ SVerticalBox::Slot()
		.Padding(5)
		.FillHeight(20)
		[
			SNew(SOverlay)
			+ SOverlay::Slot()
			[
				SAssignNew(Interpreter, SEditableTextBox)
				.Font(FSlateFontInfo("Verdana", 16))
				.OnKeyDownHandler(this, &SMyConsole::InterpreterKeys)
			]
			+ SOverlay::Slot()
			[
				SAssignNew(blocker2[11], SEditableTextBox)
				.Visibility(EVisibility::Collapsed)
			]
			+ SOverlay::Slot()
			[
				SAssignNew(blocker[11], STextBlock)
				.Visibility(EVisibility::Collapsed)
			]
		]
	];
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

FReply SMyConsole::ConsoleKeys(const FGeometry& geom, const FKeyEvent& KeyPressed)
{
	FString EditedText;
	int temp;
	if (KeyPressed.GetKey() == EKeys::Tab) {
		if (!KeyPressed.IsShiftDown()) {
			if (TextBox->AnyTextSelected()) {
				EditedText = TextBox->GetSelectedText().ToString();
				TextBox->InsertTextAtCursor("\t");
				EditedText = EditedText.Replace(FString("\n").operator*(), FString("\n    ").operator*());
				EditedText.InsertAt(0, "    ");
				EditedText = TextBox->GetText().ToString().Replace(FString("\t").operator*(), EditedText.operator*());
				TextBox->SetText(FText::FromString(EditedText));
			}
			else {
				TextBox->InsertTextAtCursor("    ");
			}
		}
		else {
			if (TextBox->AnyTextSelected()) {
				EditedText = TextBox->GetSelectedText().ToString();
				TextBox->InsertTextAtCursor("\t");
				EditedText = EditedText.Replace(FString("\n    ").operator*(), FString("\n").operator*());
				EditedText.RemoveFromStart("    ");
				EditedText = TextBox->GetText().ToString().Replace(FString("\t").operator*(), EditedText.operator*());
				TextBox->SetText(FText::FromString(EditedText));
			}
			else {
			}
		}
	}
	else if (KeyPressed.GetKey() == EKeys::BackSpace) {
		TextBox->InsertTextAtCursor(FText::FromString("\t"));
		EditedText = TextBox->GetText().ToString();
		temp = EditedText.Find("\t", ESearchCase::IgnoreCase, ESearchDir::FromStart);
		if (EditedText.Mid(temp - 3, 3) == "   " && temp >= 3) {
			EditedText.RemoveAt(temp - 3, 4, true);
		}
		else {
			EditedText.RemoveAt(temp, 1, true);
		}
		TextBox->SetText(FText::FromString(EditedText));
	}
	return FReply::Unhandled();
}

FReply SMyConsole::InterpreterKeys(const FGeometry& geom, const FKeyEvent& KeyPressed)
{
	if (KeyPressed.GetKey() == EKeys::Enter) {
		if (KeyPressed.IsShiftDown()) {
			ExecuteInterpreter();
		}
		return FReply::Handled();
	}
	else {
		return FReply::Unhandled();
	}
}


void SMyConsole::Save(const FText& InText)
{
	OwnerHUD->Save(InText);
}

void SMyConsole::Load(FText program)
{
	TextBox->SetText(program);
}

void SMyConsole::Output(FText reply)
{
	blocks.Add(MakeShareable(new FText(reply)));
	MyListWidget->RequestListRefresh();
	MyListWidget->ScrollToBottom();
}

FReply SMyConsole::ShowInterpreter()
{
	ToggleInterpreter();
	OwnerHUD->tutorialWindow->ExternalNext();
	return FReply::Handled();
}

FReply SMyConsole::ShowConsole()
{
	ToggleConsole(label1->GetText().ToString());
	OwnerHUD->tutorialWindow->ExternalNext();
	
	return FReply::Handled();
}

FReply SMyConsole::Advance()
{
	OwnerHUD->Reset();
	FString newString = TextBox->GetText().ToString();
	newString.InsertAt(newString.Len(), "\n_advance();");
	OwnerHUD->SetCmd(FText::FromString(newString), label1->GetText());
	OwnerHUD->ClearProgram();
	return FReply::Handled();
}

FReply SMyConsole::RunProgram()
{
	OwnerHUD->Reset();
	FString FinalizedCmd = TextBox->GetText().ToString();
	for (FString Async : OwnerHUD->CurrentObject->AsyncOverrides)
	{
		FinalizedCmd = FinalizedCmd.Replace(Async.operator*(), FString("async ").Append(Async).operator*());
	}
	for (FString Await : OwnerHUD->CurrentObject->AwaitOverrides)
	{
		FinalizedCmd = FinalizedCmd.Replace(Await.operator*(), FString("await ").Append(Await).operator*());
	}
	OwnerHUD->SetCmd(FText::FromString(FinalizedCmd), label1->GetText());
	OwnerHUD->tutorialWindow->ExternalNext();
	ToggleInterpreter();
	return FReply::Handled();
}

FReply SMyConsole::ExecuteInterpreter()
{
	if (!Interpreter->GetText().IsEmpty()) {
		OwnerHUD->SetCmd(Interpreter->GetText(), FText::FromString(""));
		OwnerHUD->tutorialWindow->ExternalNext();
		Interpreter->SetText(FText::FromString(""));
	}
	return FReply::Handled();
}

FReply SMyConsole::Close()
{
	Interpreter->SetText(FText::FromString(""));
	TextBox->SetText(FText::FromString(""));
	OwnerHUD->ClearProgram();
	return FReply::Handled();
}

FReply SMyConsole::DeleteAllRows()
{
	blocks.SetNum(0);
	MyListWidget->RequestListRefresh();
	MyListWidget->ScrollToBottom();
	return FReply::Handled();
}

TSharedRef<ITableRow> SMyConsole::OnGenerateRowForList(TSharedPtr< FText > Item, const TSharedRef<STableViewBase>& OwnerTable)
{
	return
	SNew(STableRow< TSharedPtr< FText > >, OwnerTable)
	[
		SNew(STextBlock)
		.AutoWrapText(true)
		.Text(*Item.Get())
		.Font(FSlateFontInfo("Verdana", 16))
	];
}

void SMyConsole::OnReleaseRowForList(const TSharedRef<ITableRow>& OnWidgetToBeRemoved)
{
}

void SMyConsole::ToggleInterpreter()
{
	for (int i = 0; i <= 2; i++) {
		GetChildren()->GetChildAt(0)->GetChildren()->GetChildAt(i)->SetVisibility(EVisibility::Collapsed);
	}
	for (int i = 3; i <= 6; i++) {
		GetChildren()->GetChildAt(0)->GetChildren()->GetChildAt(i)->SetVisibility(EVisibility::Visible);
	}
}

void SMyConsole::ToggleConsole(FString display)
{
	label1->SetText(display);
	for (int i = 0; i <= 2; i++) {
		GetChildren()->GetChildAt(0)->GetChildren()->GetChildAt(i)->SetVisibility(EVisibility::Visible);
	}
	for (int i = 3; i <= 6; i++) {
		GetChildren()->GetChildAt(0)->GetChildren()->GetChildAt(i)->SetVisibility(EVisibility::Collapsed);
	}
}


void SMyConsole::Cover() {
	for (int i = 0; i < blocker.Num(); i++) {
		blocker[i]->SetVisibility(EVisibility::Visible);
		blocker2[i]->SetVisibility(EVisibility::Visible);
		blocker2[i]->SetTextBoxBackgroundColor(FLinearColor(0.1, 0.1, 0.15, 0.9));
	}
}

void SMyConsole::Uncover(TArray<int> indices) {
	for (int i = 0; i < indices.Num(); i++) {
		blocker[indices[i]]->SetVisibility(EVisibility::Collapsed);
		blocker2[indices[i]]->SetVisibility(EVisibility::Collapsed);
	}
}

#undef LOCTEXT_NAMESPACE