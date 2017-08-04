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

#include "VSCodeSettings.h"

#include "Misc/Paths.h"
#include "Runtime/CoreUObject/Public/UObject/UnrealType.h"


#if WITH_EDITOR

void UVSCodeSettings::PostEditChangeProperty(struct FPropertyChangedEvent &PropertyChangedEvent)
{
	CheckSettings();
}

void UVSCodeSettings::PreEditChange(UProperty *Property)
{
    Super::PreEditChange(Property);
}

bool UVSCodeSettings::CheckSettings()
{
	if (VSCodePath.IsEmpty() || !FPaths::FileExists(VSCodePath))
	{
#if PLATFORM_WINDOWS
		VSCodePath = TEXT("C:\\Program Files (x86)\\Microsoft VS Code\\Code.exe");
#elif PLATFORM_MAC
		VSCodePath = TEXT("/usr/bin/code"); // Untested
#elif PLATFORM_LINUX
		VSCodePath = TEXT("/usr/bin/code");
#endif
	}

    return true;
}

#endif // WITH_EDITOR