
#include <stdio.h>
#include <Windows.h>

int main(){
    //��ȡĬ�ϱ�׼��ʾ���������
    HANDLE hOutput;
    COORD coord={0,0};
    hOutput=GetStdHandle(STD_OUTPUT_HANDLE);

    //�����µĻ�����
    HANDLE hOutBuf = CreateConsoleScreenBuffer(
        GENERIC_READ | GENERIC_WRITE,
        FILE_SHARE_READ | FILE_SHARE_WRITE,
        NULL,
        CONSOLE_TEXTMODE_BUFFER,
        NULL
    );

    //�����µĻ�����Ϊ���ʾ����
    SetConsoleActiveScreenBuffer(hOutBuf);

    //���������������Ĺ��
    CONSOLE_CURSOR_INFO cci;
    cci.bVisible=0;
    cci.dwSize=1;
    SetConsoleCursorInfo(hOutput, &cci);
    SetConsoleCursorInfo(hOutBuf, &cci);

    //˫���崦����ʾ
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
