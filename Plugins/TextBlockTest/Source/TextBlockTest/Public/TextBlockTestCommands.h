// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "TextBlockTestStyle.h"

class FTextBlockTestCommands : public TCommands<FTextBlockTestCommands>
{
public:

	FTextBlockTestCommands()
		: TCommands<FTextBlockTestCommands>(TEXT("TextBlockTest"), NSLOCTEXT("Contexts", "TextBlockTest", "TextBlockTest Plugin"), NAME_None, FTextBlockTestStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};