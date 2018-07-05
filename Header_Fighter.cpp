#define FDEBUG

#include "Header Files/maingame.h"

int size,mode,turns=1,nowx=1,nowy=1,aiturn;

int main(){
	SetConsoleTitle("Header_Fighter Releaese By Computer Rooms");
	system("mode con cols=40 lines=20");

	HANDLE hOutput=GetStdHandle(STD_OUTPUT_HANDLE);
	//CONSOLE_CURSOR_INFO cci;
	//GetConsoleCursorInfo(hOutput,&cci);
	//cci.bVisible=false;
	//SetConsoleCursorInfo(hOutput,&cci);

	//COORD Siz = {80, 25};
	//SetConsoleScreenBufferSize(hOutput,Siz);

	//SMALL_RECT rc=(SMALL_RECT){0,0,200,200};
    //SetConsoleWindowInfo(hOutput,true,&rc);

	printf("SIZE?\n"); scanf("%d",&size);
    printf("MODE?\n"); scanf("%d",&mode);
    printf("aiturn?\n"); scanf("%d",&aiturn);

	GAME::maingame game(size);
    game.start();
    
    if(mode==0){
		while(true){
			while(1){
				char ch=getch();
				if(ch=='W'||ch=='w'){
					if(nowy<size){
						nowy+=1;
						game.setcol(nowx,nowy);
					}
						continue;
				}
				if(ch=='S'||ch=='s'){
					if(nowy>1){
						nowy-=1;
						game.setcol(nowx,nowy);
					}
						continue;
				}
				if(ch=='A'||ch=='a'){
					if(nowx>1){
						nowx-=1;
						game.setcol(nowx,nowy);
					}
						continue;
				}
				if(ch=='D'||ch=='d'){
					if(nowx<size){
						nowx+=1;
						game.setcol(nowx,nowy);
					}
						continue;
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
		CloseHandle(hOutput);
		return 0;
	}
	if(mode==1){
		
	}
	CloseHandle(hOutput);
	return 0;
}