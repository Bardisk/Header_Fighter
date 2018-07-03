
#include <stdio.h>
#include <windows.h>
int main()
{
    while (1)
    {
        for (char c='a'; c<'z'; c++)
        {
            system("cls");
            for (int i=0; i<800; i++)
            {
                printf("%c",c);
            }
        }
    }
}

