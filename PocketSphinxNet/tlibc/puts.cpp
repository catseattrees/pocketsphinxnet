// puts.cpp

// based on:
// LIBCTINY - Matt Pietrek 2001
// MSDN Magazine, January 2001

// 08/12/06 (mv)

#ifndef POCKETSPHINX_NET
#include <windows.h>
#include <stdio.h>
//EXTERN_C 
int puts(const char *s)
{
    DWORD cbWritten;
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

	int bw = fwrite(s, lstrlenA(s), 1, stdout)
		;
	bw += fwrite("\n", 1, 1, stdout)
		;
	return bw;

    WriteFile(hStdOut, s, lstrlenA(s)*sizeof(char), &cbWritten, 0);
    WriteFile(hStdOut, "\r\n", 2, &cbWritten, 0);

    return (int)(cbWritten ? cbWritten : EOF);
}

//EXTERN_C 
int _putws(const wchar_t *s)
{
	DWORD bw;
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

	// _putws converts unicode to ascii before writing to stdout!
	char bfr[1024] = {0};
	 WideCharToMultiByte(CP_ACP, 0, s, -1, bfr, sizeof(bfr), 0, 0);
	//return puts(bfr);

	WriteFile(hStdOut, s, lstrlenW(s)*sizeof(wchar_t), &bw, 0);
	WriteFile(hStdOut, L"\r\n", 2*sizeof(wchar_t), &bw, 0);

	return (int)(bw ? bw : EOF);
}


#else
#include "libct.h"
using namespace System;

int puts(const char *s)
{
	int len = -1;
	if(s!=0)
	{
		String^ str = gcnew String(s);
		str+=L"\r\n";
		System::Console::Write(str);

		len = str->Length;
	}
	return len;

}

//EXTERN_C 
int _putws(const wchar_t *s)
{
	int len = -1;
	if(s!=0)
	{
		String^ str = gcnew String(s);
		str+=L"\r\n";
		System::Console::Write(str);

		len = str->Length;
	}
	return len;

}
#endif

