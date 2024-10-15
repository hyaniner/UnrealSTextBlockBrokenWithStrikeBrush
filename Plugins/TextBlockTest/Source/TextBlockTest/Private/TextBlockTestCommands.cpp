// Copyright Epic Games, Inc. All Rights Reserved.

#include "TextBlockTestCommands.h"

#define LOCTEXT_NAMESPACE "FTextBlockTestModule"

void FTextBlockTestCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "TextBlockTest", "Bring up TextBlockTest window", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
