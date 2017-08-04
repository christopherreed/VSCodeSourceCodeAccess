/* Copyright (c) 2017 Christopher Reed

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. */

#include "VSCodeSourceCodeAccessModule.h"
#include "VSCodeSettings.h"

#include "Runtime/Core/Public/Features/IModularFeatures.h"
#include "Modules/ModuleManager.h"

#include "Developer/Settings/Public/ISettingsModule.h"

#define LOCTEXT_NAMESPACE "VSCodeSourceCodeAccessor"

IMPLEMENT_MODULE( FVSCodeSourceCodeAccessModule, VSCodeSourceCodeAccess );

void FVSCodeSourceCodeAccessModule::StartupModule()
{
	// Settings
	if (ISettingsModule *SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->RegisterSettings(
			"Project",
			"Plugins",
			"VSCodeSettings",
			LOCTEXT("RuntimeSettingsName", "VSCode"),
			LOCTEXT("RuntimeSettingsDescription", "Configure the VSCode plugin"),
			GetMutableDefault<UVSCodeSettings>()
		);
	}

	VSCodeSourceCodeAccessor.Startup();

	// Bind our source control provider to the editor
	IModularFeatures::Get().RegisterModularFeature(TEXT("SourceCodeAccessor"), &VSCodeSourceCodeAccessor );
}

void FVSCodeSourceCodeAccessModule::ShutdownModule()
{
	VSCodeSourceCodeAccessor.Shutdown();
	
	// Settings
	if (ISettingsModule *SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->UnregisterSettings("Project", "VSCodeSettings", "General");
	}

	// unbind provider from editor
	IModularFeatures::Get().UnregisterModularFeature(TEXT("SourceCodeAccessor"), &VSCodeSourceCodeAccessor);
}