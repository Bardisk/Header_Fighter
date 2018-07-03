#include<windows.h>
#include<iostream>
//HANDLE hOutput=GetStdHandle(STD_OUTPUT_HANDLE);
int main()
{
	system("pause");
	while(1){
		HANDLE hOutput=GetStdHandle(STD_OUTPUT_HANDLE);
		COORD size = {80, 25};
		SetConsoleScreenBufferSize(hOutput,size);
		SMALL_RECT rc;
    	rc.Left=0;rc.Top=0;
		rc.Right=160;rc.Bottom=150;
   	 	SetConsoleWindowInfo(hOutput,true,&rc);
   	 	CloseHandle(hOutput);
	}
	return 0;
}
