#include "Header Files/base.h"

#define FDEBUG
using namespace std;

HANDLE hOutput=GetStdHandle(STD_OUTPUT_HANDLE);
COORD coord={0,0};

bool color[20][20];
int need[20][20],map[20][20],size=12;
int turns=1,nowx=size,nowy=1;
void init()
{
	memset(map,0x3f,sizeof map);
	for(int i=1;i<=size;i++)
	{
		for(int j=1;j<=size;j++)
		{
			map[i][j]=1;
			if((i+j)%2==0) color[i][j]=0;
			else color[i][j]=1;
			need[i][j]=2;
		}
	}
	for(int i=1;i<=size;i++)
		for(int j=2;j<=size-1;j++)
			need[i][j]++,need[j][i]++;
	for(int i=0;i<=size+1;i++)
	{
		need[i][0]=INF+1000000;
		need[0][i]=INF+1000000;
		need[size+1-i][0]=INF+10000000;
		need[0][size+1-i]=INF+10000000;
	}
	return;
}
void ptmap()
{
	//system("cls");
	//SetConsoleTextAttribute(hOutput,15);
	SetConsoleCursorPosition(hOutput,coord);
	Setcol(hOutput,0xf);
	#ifndef FDEBUG
	puts("DEBUG MODE");
	#endif
	printf("Turns:%d(%s) \n",turns,(turns&1)?"RED/YELLOW":"BLUE/NAVY");
	for(int i=size;i>=1;i--)
	{
		for(int j=1;j<=size;j++)
		{
			int tmp=0;
			if(map[j][i]>need[j][i]-2) tmp|=ForeInt;
			if(map[j][i]==need[j][i]) tmp|=ForeGreen;
			if(i==nowy&&j==nowx) tmp|=(BackInt|BackBlue|BackRed|BackGreen);
			if(!color[j][i]) Setcol(hOutput,ForeBlue|tmp);
			else Setcol(hOutput,ForeRed|tmp);
			printf("%d",map[j][i]);
			Setcol(hOutput,0xf); printf(" ");
		}
		i!=1?printf("\n"):0;
	}
	#ifndef FDEBUG
	printf("need:%d now:%d\n",need[nowx][nowy],map[nowx][nowy]);
	#endif
	return;
}
bool chb()
{
	for(int i=1;i<=size;i++)
		for(int j=1;j<=size;j++)
			if(map[i][j]>need[i][j]) return true;
	return false;
}
int check()
{
	bool rd=true,bl=true;
	for(int i=1;i<=size;i++)
	{
		for(int j=1;j<=size;j++)
		{
			if(color[i][j]==0) rd=false;
			if(color[i][j]==1) bl=false;
		}
	}
	if(bl==true) return 1;
	if(rd==true) return 2;
	return 0;
}
void b(int x,int y,int t)
{
	if(check()) return ;
	//printf("*%d %d\n",x,y);
	int n=size;
	if(x<=0||y<=0||x>=size+1||y>=size+1) return ;
	if(map[x][y]>need[x][y])
	{
		map[x][y]-=need[x][y];
		map[x-1][y]++;color[x-1][y]=t;b(x-1,y,t);
		map[x+1][y]++;color[x+1][y]=t;b(x+1,y,t);
		map[x][y-1]++;color[x][y-1]=t;b(x,y-1,t);
		map[x][y+1]++;color[x][y+1]=t;b(x,y+1,t);
	}
	return ;
}
void booms(int t)
{
	while(true)
	{
		if(!chb()||check()) return ;
		for(int i=1;i<=size;i++)
			for(int j=1;j<=size;j++)
				b(i,j,t);
	}
	return ;
}

int main()
{
	SetConsoleTitle("Header_Fighter Releaese By Computer Rooms");
	system("mode con cols=80 lines=30");
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
	init();
	ptmap();
	while(true)
	{
		Setcol(hOutput,0xf);
		while(1){
			char ch=getch();
			switch(ch){
				case 'w':{
					if(nowy<size)
						nowy+=1;
					break;
				}
				case 's':{
					if(nowy>1)
						nowy-=1;
					break;
				}
				case 'a':{
					if(nowx>1)
						nowx-=1;
					break;
				}
				case 'd':{
					if(nowx<size)
						nowx+=1;
					break;
				}
			}
			ptmap();
			if(ch=='\r'){
				if(color[nowx][nowy]!=(turns&1)){
					#ifndef FDEBUG
					printf("turns:%d color:%d",turns,color[nowx][nowy]);
					#endif
					printf("!!ÇëÖØÐÂÑ¡Ôñ!!\n");
				}
				else break;
			}
			//printf("It's player %d's turn. (%s)\n",turns,turns==1?"Blue":"Red");
		}
		map[nowx][nowy]++;
		booms((turns&1));
		
		//printf("a\n");
		int k=check();
		if(k!=0)
		{
			ptmap();
			printf("Player %d wins.\n",k%2+1);
			system("pause");
			break;
		}
		++turns;
		ptmap();
		#ifndef FDEBUG
		puts("**************************");
		printf("nowx:%d nowy:%d turns:%d\n",nowx,nowy,turns);
		puts("**************************");
		#endif
	}
	CloseHandle(hOutput);
	return 0;
}
