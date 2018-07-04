#include "Header Files/maingame.h"

//#define FDEBUG
using namespace std;

int size,mode,turns=1,nowx=1,nowy=1,aiturn;
int main()
{
	SetConsoleTitle("Header_Fighter Releaese By Computer Rooms");
	system("mode con cols=40 lines=20");
	HANDLE hOutput=GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cci;
	GetConsoleCursorInfo(hOutput,&cci);
	cci.bVisible=false;
	SetConsoleCursorInfo(hOutput,&cci);
	COORD Siz = {80, 25};
	SetConsoleScreenBufferSize(hOutput,Siz);
    SMALL_RECT rc;
    rc.Left=0;rc.Top=0;
	rc.Right=200;rc.Bottom=200;
    SetConsoleWindowInfo(hOutput,true,&rc);
    printf("大小？\n"); scanf("%d",&size);
    printf("模式？\n"); scanf("%d",&mode);
    printf("ai先后？\n"); scanf("%d",&aiturn);
    GAME::maingame game(size);
    game.start();
    if(mode==0){//default
		while(true)
		{
			hOutput=GetStdHandle(STD_OUTPUT_HANDLE);
			Setcol(hOutput,0xf);
			while(1){
				char ch=getch();
				switch(ch){
					case 'w':{
						if(nowy<size){
							nowy+=1;
							game.setcol(nowx,nowy);
						}
						break;
					}
					case 's':{
						if(nowy>1){
							nowy-=1;
							game.setcol(nowx,nowy);
						}
						break;
					}
					case 'a':{
						if(nowx>1){
							nowx-=1;
							game.setcol(nowx,nowy);
						}	
						break;
					}
					case 'd':{
						if(nowx<size){
							nowx+=1;
							game.setcol(nowx,nowy);
						}
						break;
					}
				}
				if(ch=='\r'){
					int tmp=game.keydown();
					if(tmp==-1) return 0;
				}
			}
		}
		#ifndef FDEBUG
		puts("**************************");
		printf("nowx:%d nowy:%d turns:%d\n",nowx,nowy,turns);
		puts("**************************");
		#endif
		return 0;
	}
	if(mode==1){ //AivsPer
		
	}
	CloseHandle(hOutput);
	return 0;
}
