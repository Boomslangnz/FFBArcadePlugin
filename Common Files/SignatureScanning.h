/*This file is part of FFB Arcade Plugin.
FFB Arcade Plugin is free software : you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.
FFB Arcade Plugin is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with FFB Arcade Plugin.If not, see < https://www.gnu.org/licenses/>.
*/

#include <Windows.h>

static char* aAddy;
static char* aAddy2;

static char* InScan(char* pattern, char* mask, char* begin, unsigned int size)
{
	unsigned int patternLength = strlen(mask);

	for (unsigned int i = 0; i < size - patternLength; i++)
	{
		bool found = true;
		for (unsigned int j = 0; j < patternLength; j++)
		{
			if (mask[j] != '?' && pattern[j] != *(begin + i + j))
			{
				found = false;
				break;
			}
		}
		if (found)
		{
			return (begin + i);
		}
	}

	return 0;
}

static char* PatternScan(char* pattern, char* mask)
{
	SYSTEM_INFO sysInfo;

	GetSystemInfo(&sysInfo);

	__int64 end = (__int64)sysInfo.lpMaximumApplicationAddress;

	char* currentChunk = 0;
	char* match = nullptr;
	SIZE_T bytesRead;

	while (currentChunk < (char*)end)
	{
		MEMORY_BASIC_INFORMATION mbi;

		HANDLE process = GetCurrentProcess();

		if (!VirtualQueryEx(process, currentChunk, &mbi, sizeof(mbi)))
		{
			return 0;
		}

		char* buffer = 0;
		if (mbi.State == MEM_COMMIT && mbi.Protect != PAGE_NOACCESS)
		{
			buffer = new char[mbi.RegionSize];
			DWORD oldprotect;
			if (VirtualProtectEx(process, mbi.BaseAddress, mbi.RegionSize, PAGE_EXECUTE_READWRITE, &oldprotect))
			{
				ReadProcessMemory(process, mbi.BaseAddress, buffer, mbi.RegionSize, &bytesRead);
				VirtualProtectEx(process, mbi.BaseAddress, mbi.RegionSize, oldprotect, &oldprotect);

				char* internalAddress = InScan(pattern, mask, buffer, bytesRead);

				if (internalAddress != 0)
				{
					__int64 offsetFromBuffer = internalAddress - buffer;
					match = currentChunk + offsetFromBuffer;

					if (match != aAddy2)
					{
						break;
					}
				}
			}
		}

		currentChunk = currentChunk + mbi.RegionSize;

		if (buffer)
		{
			delete[] buffer;
			buffer = 0;
		}
	}
	return match;
}