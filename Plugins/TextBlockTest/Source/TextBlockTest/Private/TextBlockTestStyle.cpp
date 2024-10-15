// Copyright Epic Games, Inc. All Rights Reserved.

#include "TextBlockTestStyle.h"
#include "Styling/SlateStyleRegistry.h"
#include "Framework/Application/SlateApplication.h"
#include "Slate/SlateGameResources.h"
#include "Interfaces/IPluginManager.h"

#include "Styling/SlateStyleMacros.h"

#define RootToContentDir Style->RootToContentDir
#define RootToCoreContentDir Style->RootToCoreContentDir

TSharedPtr<FSlateStyleSet> FTextBlockTestStyle::StyleInstance = nullptr;

void FTextBlockTestStyle::Initialize()
{
	if (!StyleInstance.IsValid())
	{
		StyleInstance = Create();
		FSlateStyleRegistry::RegisterSlateStyle(*StyleInstance);
	}
}

void FTextBlockTestStyle::Shutdown()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*StyleInstance);
	ensure(StyleInstance.IsUnique());
	StyleInstance.Reset();
}

FName FTextBlockTestStyle::GetStyleSetName()
{
	static FName StyleSetName(TEXT("TextBlockTestStyle"));
	return StyleSetName;
}

const FVector2D Icon16x16(16.0f, 16.0f);
const FVector2D Icon20x20(20.0f, 20.0f);

TSharedRef< FSlateStyleSet > FTextBlockTestStyle::Create()
{
	TSharedRef< FSlateStyleSet > Style = MakeShareable(new FSlateStyleSet("TextBlockTestStyle"));
	Style->SetContentRoot(IPluginManager::Get().FindPlugin("TextBlockTest")->GetBaseDir() / TEXT("Resources"));

	Style->Set("TextBlockTest.OpenPluginWindow", new IMAGE_BRUSH_SVG(TEXT("PlaceholderButtonIcon"), Icon20x20));

	const FString EngineSlateContentDir = FPaths::EngineContentDir() / TEXT("Slate");
	const FString EngineEditorSlateContentDir = FPaths::EngineContentDir() / TEXT("Editor/Slate");
	
	Style->SetCoreContentRoot(EngineEditorSlateContentDir);

	const FTextBlockStyle& BaseTextBlockStyle = FCoreStyle::Get().GetWidgetStyle<FTextBlockStyle>("NormalText");
	
	FSlateBorderBrush* BrushUnderline = new CORE_BORDER_BRUSH("Old/HyperlinkUnderline", FMargin(0.f, 0.f, 0.f, 0.4f));	
	//Style->Set( "NodeBulkReplace.BrushUnderline", BrushUnderline);
	Style->Set("TextBlockTest.BrushUnderline", FTextBlockStyle(BaseTextBlockStyle)
		.SetStrikeBrush(*BrushUnderline)		
	);

	FSlateBorderBrush* StrikeAlpha = new CORE_BORDER_BRUSH("Old/Border", FMargin(0.f, 0.f, 0.f, 4.f/16.f));
	//Style->Set( "TextBlockTest.BorderBrush.BrushTestHotel", BrushTestHotel);
	Style->Set("TextBlockTest.StrikeAlpha", FTextBlockStyle(BaseTextBlockStyle)
		.SetStrikeBrush(*StrikeAlpha)		
	);
	
	return Style;
}

void FTextBlockTestStyle::ReloadTextures()
{
	if (FSlateApplication::IsInitialized())
	{
		FSlateApplication::Get().GetRenderer()->ReloadTextureResources();
	}
}

const ISlateStyle& FTextBlockTestStyle::Get()
{
	return *StyleInstance;
}
