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

#include "VSCodeSourceCodeAccessor.h"
#include "CoreMinimal.h"
#include "DesktopPlatformModule.h"
#include "Modules/ModuleManager.h"
#include "VSCodeSourceCodeAccessModule.h"
#include "ISourceCodeAccessModule.h"
#include "Misc/Paths.h"

#define LOCTEXT_NAMESPACE "VSCodeSourceCodeAccessor"

DEFINE_LOG_CATEGORY_STATIC(LogVSCodeAccessor, Log, All);

void FVSCodeSourceCodeAccessor::Startup()
{
	Settings = GetMutableDefault<UVSCodeSettings> ();
	Settings->CheckSettings();
	
	ProjectFile = *FPaths::ConvertRelativePathToFull(*FPaths::GetProjectFilePath());
	FPaths::NormalizeFilename(ProjectFile);

	ProjectName = *FPaths::GetBaseFilename(ProjectFile);

	ProjectDir = *FPaths::ConvertRelativePathToFull(*FPaths::GetPath(ProjectFile));
	FPaths::NormalizeFilename(ProjectDir);

	VSCodeWorkspaceDir = *FPaths::Combine(ProjectDir, TEXT(".vscode"));
	FPaths::NormalizeDirectoryName(VSCodeWorkspaceDir);
}

void FVSCodeSourceCodeAccessor::Shutdown()
{
	Settings = nullptr;
}

bool FVSCodeSourceCodeAccessor::CanAccessSourceCode() const
{
	return Settings->CheckSettings();
}

FName FVSCodeSourceCodeAccessor::GetFName() const
{
	return FName("VSCodeSourceCodeAccessor");
}

FText FVSCodeSourceCodeAccessor::GetNameText() const
{
	return LOCTEXT("VSCodeDisplayName", "VSCode");
}

FText FVSCodeSourceCodeAccessor::GetDescriptionText() const
{
	return LOCTEXT("VSCodeDisplayDesc", "Open source code files in Visual Studio Code");
}

bool FVSCodeSourceCodeAccessor::OpenSolution()
{
	// A project in VSCode is simply a directory, optionally with a .vscode sub directory to configure extensions
	if (!FPaths::DirectoryExists(ProjectDir))
	{
		UE_LOG(LogVSCodeAccessor, Error, TEXT("Could Not Open Solution - Project Directory Not Found"));
		return false;
	}

	// Open Project Directory in VSCode
	// Add this to handle spaces in path names.
	const FString FixedProjectDir = FString::Printf(TEXT("\"%s\""), *ProjectDir);

	FProcHandle Proc = FPlatformProcess::CreateProc(*Settings->VSCodePath, *FixedProjectDir, true, true, false, nullptr, 0, nullptr, nullptr);

	if (!Proc.IsValid())
	{
		FPlatformProcess::CloseProc(Proc);
		return false;
	}

	return true;

}

bool FVSCodeSourceCodeAccessor::OpenFileAtLine(const FString& FullPath, int32 LineNumber, int32 ColumnNumber)
{
	// column & line numbers are 1-based, so dont allow zero
	LineNumber = LineNumber > 0 ? LineNumber : 1;
	ColumnNumber = ColumnNumber > 0 ? ColumnNumber : 1;

	// Add this to handle spaces in path names.
	const FString FixedFilePath = FString::Printf(TEXT("\"%s:%d:%d\""), *FullPath, LineNumber, ColumnNumber);

	FProcHandle Proc = FPlatformProcess::CreateProc(*Settings->VSCodePath, *FixedFilePath, true, false, false, nullptr, 0, nullptr, nullptr);
	if (!Proc.IsValid())
	{
		FPlatformProcess::CloseProc(Proc);
		return false;
	}

	return true;	
}

bool FVSCodeSourceCodeAccessor::OpenSourceFiles(const TArray<FString>& AbsoluteSourcePaths)
{
	for (const FString& SourcePath : AbsoluteSourcePaths)
	{
		// Add this to handle spaces in path names.
		const FString FixedFilePath = FString::Printf(TEXT("\"%s\""), *SourcePath);

		FProcHandle Proc = FPlatformProcess::CreateProc(*Settings->VSCodePath, *FixedFilePath, true, false, false, nullptr, 0, nullptr, nullptr);
		if (!Proc.IsValid())
		{
			FPlatformProcess::CloseProc(Proc);
			return false;
		}
	}

	return true;
}

bool FVSCodeSourceCodeAccessor::AddSourceFiles(const TArray<FString>& AbsoluteSourcePaths, const TArray<FString>& AvailableModules)
{
	return true; // I don't think we need to do anything when files are added
}

bool FVSCodeSourceCodeAccessor::SaveAllOpenDocuments() const
{
	return false;
}

void FVSCodeSourceCodeAccessor::Tick(const float DeltaTime)
{
}

#undef LOCTEXT_NAMESPACE