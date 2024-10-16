// Copyright Epic Games, Inc. All Rights Reserved.

#include "TextBlockTest.h"
#include "TextBlockTestStyle.h"
#include "TextBlockTestCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "ToolMenus.h"

static const FName TextBlockTestTabName("TextBlockTest");

#define LOCTEXT_NAMESPACE "FTextBlockTestModule"

void FTextBlockTestModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FTextBlockTestStyle::Initialize();
	FTextBlockTestStyle::ReloadTextures();

	FTextBlockTestCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FTextBlockTestCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FTextBlockTestModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FTextBlockTestModule::RegisterMenus));
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(TextBlockTestTabName, FOnSpawnTab::CreateRaw(this, &FTextBlockTestModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FTextBlockTestTabTitle", "TextBlockTest"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
}

void FTextBlockTestModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FTextBlockTestStyle::Shutdown();

	FTextBlockTestCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(TextBlockTestTabName);
}

TSharedRef<SDockTab> FTextBlockTestModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	FText WidgetText = FText::Format(
		LOCTEXT("WindowWidgetText", "Add code to {0} in {1} to override this window's contents"),
		FText::FromString(TEXT("FTextBlockTestModule::OnSpawnPluginTab")),
		FText::FromString(TEXT("TextBlockTest.cpp"))
		);

	const ISlateStyle& Style = FTextBlockTestStyle::Get();
	
	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			// Put your tab content here!
			SNew(SBox)
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SNew(SVerticalBox)
				+SVerticalBox::Slot()
				.AutoHeight()
				[
					SNew(STextBlock)
					.Text(WidgetText)
				]
				+SVerticalBox::Slot()
				.AutoHeight()
				[
					SNew(STextBlock)
					.Text(INVTEXT("FSlateBrush Old/White as strike, 1x1. This is ok. It seems that it was used as intended."))
					.TextStyle(&Style.GetWidgetStyle<FTextBlockStyle>("TextBlockTest.BrushWhiteOneByOne"))
				]
				+SVerticalBox::Slot()
				.AutoHeight()
				[
					SNew(STextBlock)
					.Text(INVTEXT("FSlateBrush Old/White as strike, 16x16. This is ok. It seems that it was used as intended."))
					.TextStyle(&Style.GetWidgetStyle<FTextBlockStyle>("TextBlockTest.BrushWhite16"))
				]
				+SVerticalBox::Slot()
				.AutoHeight()
				[
					SNew(STextBlock)
					.Text(INVTEXT("FSlateBrush Old/HyperlinkUnderline as strike. This is ok."))
					.TextStyle(&Style.GetWidgetStyle<FTextBlockStyle>("TextBlockTest.BrushUnderline"))
				]
				+SVerticalBox::Slot()
				.AutoHeight()
				[
					SNew(STextBlock)
					.Text(INVTEXT("FSlateBorderBrush Old/HyperlinkUnderline as strike. This is ok."))
					.TextStyle(&Style.GetWidgetStyle<FTextBlockStyle>("TextBlockTest.BorderBrushUnderline"))
				]
				+SVerticalBox::Slot()
				.AutoHeight()
				[
					SNew(SVerticalBox)
					+SVerticalBox::Slot()
					.AutoHeight()
					[
						SNew(STextBlock)
						.Text(INVTEXT("FSlateBrush Old/Border as strike brush. This is ok."))
						.TextStyle(&Style.GetWidgetStyle<FTextBlockStyle>("TextBlockTest.BrushBorder"))
					]
					+SVerticalBox::Slot()
					[
						SNew(STextBlock)
						.Text(INVTEXT("FSlateBrush Old/Border as strike brush. This is ok."))
						.TextStyle(&Style.GetWidgetStyle<FTextBlockStyle>("TextBlockTest.BrushBorder"))
					]
					+SVerticalBox::Slot()
					[
						SNew(SHorizontalBox)
						+SHorizontalBox::Slot()
						.AutoWidth()
						[
							SNew(STextBlock)
							.Text(INVTEXT("FSlateBrush Old/Border as strike brush. This is ok."))
							.TextStyle(&Style.GetWidgetStyle<FTextBlockStyle>("TextBlockTest.BrushBorder"))
						]
						+SHorizontalBox::Slot()
						.AutoWidth()
						[
							SNew(STextBlock)
							.Text(INVTEXT("FSlateBrush Old/Border as strike brush. This is ok."))
							.TextStyle(&Style.GetWidgetStyle<FTextBlockStyle>("TextBlockTest.BrushBorder"))
						]
					]					
				]
				/*+SVerticalBox::Slot()
				.AutoHeight()
				[
					SNew(SVerticalBox)
					+SVerticalBox::Slot()
					.AutoHeight()
					[
						SNew(STextBlock)
						.Text(INVTEXT("FSlateBorderBrush Old/Border as strike brush. This will make a broken phenomenon."))
						.TextStyle(&Style.GetWidgetStyle<FTextBlockStyle>("TextBlockTest.BorderBrushBorder"))
					]
					+SVerticalBox::Slot()
					[
						SNew(STextBlock)
						.Text(INVTEXT("FSlateBorderBrush Old/Border as strike brush. This will make a broken phenomenon."))
						.TextStyle(&Style.GetWidgetStyle<FTextBlockStyle>("TextBlockTest.BorderBrushBorder"))
					]
					+SVerticalBox::Slot()
					[
						SNew(SHorizontalBox)
						+SHorizontalBox::Slot()
						.AutoWidth()
						[
							SNew(STextBlock)
							.Text(INVTEXT("FSlateBorderBrush Old/Border as strike brush. This will make a broken phenomenon."))
							.TextStyle(&Style.GetWidgetStyle<FTextBlockStyle>("TextBlockTest.BorderBrushBorder"))
						]
						+SHorizontalBox::Slot()
						.AutoWidth()
						[
							SNew(STextBlock)
							.Text(INVTEXT("FSlateBorderBrush Old/Border as strike brush. This will make a broken phenomenon."))
							.TextStyle(&Style.GetWidgetStyle<FTextBlockStyle>("TextBlockTest.BorderBrushBorder"))
						]
					]					
				]*/
			]
		];
}

void FTextBlockTestModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->TryInvokeTab(TextBlockTestTabName);
}

void FTextBlockTestModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FTextBlockTestCommands::Get().OpenPluginWindow, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Settings");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FTextBlockTestCommands::Get().OpenPluginWindow));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FTextBlockTestModule, TextBlockTest)