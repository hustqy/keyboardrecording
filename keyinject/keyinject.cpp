// keyinject.cpp : Defines the entry point for the console application.
//
#include <Windows.h>
#include <tchar.h>
#include <stdio.h>
#include <stdlib.h>

int _tmain(int argc, char* argv[])
{

	HWND wndhd;
	DWORD threadId ;
	BOOL bret;
	MSG msg;
	//system("notepad.exe");
	wndhd = FindWindow(NULL,TEXT("1.txt - ¼ÇÊÂ±¾"));

	if(!wndhd)
	{
		printf("failed to find notepad\n");
		getchar();
		return -1;
	}

	/*while(bret = GetMessage(&msg,wndhd,0,0)!=0){
		if(bret == -1)
		{
			printf("sleep\n");
			Sleep(3000);
			wndhd = FindWindow(NULL,TEXT("Untitled - notepad.exe"));


		}
		else{
			printf("get message\n");
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	*/
	threadId = GetWindowThreadProcessId(wndhd,NULL); 
		if(!threadId)
	{
		printf("failed to get window of notpad\n");
		getchar();
		return 0;
	}

	HMODULE dll  = LoadLibrary(TEXT("C:\\Users\\qy\\Desktop\\dllinject.dll"));
	if(!dll)
	{
		printf("no such dll");
		getchar();
		return 0;
	}

	HOOKPROC hpc = (HOOKPROC)GetProcAddress(dll,"?KeyboardProc@@YGJHIJ@Z");
	if(!hpc)
	{
		printf("failed to get KeyboardProc address");
		getchar();
		return 0;
	}
	
	HHOOK hk = SetWindowsHookEx(WH_KEYBOARD,hpc,dll,threadId);
	if(!hk )
	{
		printf("failed to hook\n");
		getchar();
		return 0;
	}

	printf("hook success\n");
	while(GetMessage(&msg,NULL,0,0)>0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	UnhookWindowsHookEx(hk);

	return 0;
}

