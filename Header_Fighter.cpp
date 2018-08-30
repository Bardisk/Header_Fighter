#define FDEBUG
#define ESCUI

#include "Header Files/maingame.h"
#include "Header Files/testai.h"

int size,mode,turns=1,nowx=1,nowy=1,aiturn;

int main(){
	srand(time(0));
	SetConsoleTitle("Header_Fighter Releaese By Computer Rooms");
	system("mode con cols=45 lines=25");

	HANDLE hOutput=GetStdHandle(STD_OUTPUT_HANDLE);
	//CONSOLE_CURSOR_INFO cci;
	//GetConsoleCursorInfo(hOutput,&cci);
	//cci.bVisible=false;
	//SetConsoleCursorInfo(hOutput,&cci);

	//COORD Siz = {80, 25};
	//SetConsoleScreenBufferSize(hOutput,Siz);

	//SMALL_RECT rc=(SMALL_RECT){0,0,200,200};
    //SetConsoleWindowInfo(hOutput,true,&rc);
    #ifndef ESCUI
    Setcol(hOutput,ForeBlue|ForeGreen|ForeInt);
    printf("\nHeader_Fighter!\n");
    Sleep(2000);
    printf("\nReleased by ASFNUCR\n");
    Sleep(2000);
    Setcol(hOutput,0xf);
    printf("\noriginal designer&director:");
    Setcol(hOutput,ForeGreen|ForeInt);
	printf("lzier\n");
    Sleep(2000);
    Setcol(hOutput,0xf);
    printf("\nadapters:");
	Setcol(hOutput,ForeBlue|ForeInt);
	printf("Smokey_Days,Bardisk\n");
    Sleep(2000);
    Setcol(hOutput,0xf);
    printf("\njavascript:");
    Setcol(hOutput,ForeRed|ForeGreen|ForeInt);
	printf("Hotwords123\n");
    Sleep(2000);
    Setcol(hOutput,0xf);
    printf("\nGameStart!\n");
    Setcol(hOutput,0xf);
    Sleep(1000);
    system("cls");
	#endif

	printf("SIZE?\n"); scanf("%d",&size);
    printf("MODE?\n"); scanf("%d",&mode);
    printf("aiturn?\n"); scanf("%d",&aiturn);

	baseinfo unuse;
	GAME::maingame game(size);
    game.start(0,unuse);
    
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
	//Person vs LocalAi
	if(mode==1){
		barAi::barMachine ai(size);
		baseinfo numap;
		while(1){
			numap=game.getmap();
			if((numap.turns&1)==aiturn){
				aiReturn now=ai.doChoice(numap);
				nowx=now.first;
				nowy=now.second;
				game.setcol(now.first,now.second);
				int tmp=game.keydown();
				if(tmp==-1) return 0;
				continue;
			}
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
	//LocalAi vs LocalAi
	if(mode==2){
		barAi::barMachine ai1(size);
		barAi::barMachine ai2(size);
		baseinfo numap;
		while(1){
			numap=game.getmap();
			if((numap.turns&1)==aiturn){
				aiReturn now=ai1.doChoice(numap);
				nowx=now.first;
				nowy=now.second;
				game.setcol(now.first,now.second);
				int tmp=game.keydown();
				if(tmp==-1) return 0;
				if(tmp==0) Sleep(100);
				continue;
			}
			else{
				aiReturn now=ai2.doChoice(numap);
				nowx=now.first;
				nowy=now.second;
				game.setcol(now.first,now.second);
				int tmp=game.keydown();
				if(tmp==-1) return 0;
				if(tmp==0) Sleep(100);
				continue;
			}
		}
	}
	CloseHandle(hOutput);
	return 0;
}
