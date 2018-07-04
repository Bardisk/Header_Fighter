
#include <stdio.h>
#include <Windows.h>

int main(){
    //获取默认标准显示缓冲区句柄
    HANDLE hOutput;
    COORD coord={0,0};
    hOutput=GetStdHandle(STD_OUTPUT_HANDLE);

    //创建新的缓冲区
    HANDLE hOutBuf = CreateConsoleScreenBuffer(
        GENERIC_READ | GENERIC_WRITE,
        FILE_SHARE_READ | FILE_SHARE_WRITE,
        NULL,
        CONSOLE_TEXTMODE_BUFFER,
        NULL
    );

    //设置新的缓冲区为活动显示缓冲
    SetConsoleActiveScreenBuffer(hOutBuf);

    //隐藏两个缓冲区的光标
    CONSOLE_CURSOR_INFO cci;
    cci.bVisible=0;
    cci.dwSize=1;
    SetConsoleCursorInfo(hOutput, &cci);
    SetConsoleCursorInfo(hOutBuf, &cci);

    //双缓冲处理显示
    DWORD bytes=0;
    char data[800];
    while (1)
    {
        for (char c='a'; c<'z'; c++)
        {
        	SetConsoleActiveScreenBuffer(hOutput);
            system("cls");
            //Sleep(600);
            SetConsoleActiveScreenBuffer(hOutBuf);
            for (int i=0; i<100; i++)
            {
                printf("%c",c);
            }
            ReadConsoleOutputCharacterA(hOutput, data, 800, coord, &bytes);
            WriteConsoleOutputCharacterA(hOutBuf, data, 800, coord, &bytes);
            Sleep(600);
        }
    }
    return 0;
}
