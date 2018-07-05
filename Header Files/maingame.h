#include "base.h"

#ifndef _MAINGAME_H_
#define _MAINGAME_H_

namespace GAME{
	struct baseinfo{
		bool col[20][20];
		int map[20][20];
		int turns,siz;
	};

	HANDLE GameOut;
	HANDLE BufOut;
	COORD coord={0,0};
	
	class maingame{
		bool color[20][20];
		int need[20][20],map[20][20];
		int turns,nowx,nowy,size;
		char Scdata[1000];
		
		void prepareGame(int sz){
			GameOut=GetStdHandle(STD_OUTPUT_HANDLE);

			BufOut=CreateConsoleScreenBuffer(
				GENERIC_READ | GENERIC_WRITE,
				FILE_SHARE_READ | FILE_SHARE_WRITE,
		        NULL,
		        CONSOLE_TEXTMODE_BUFFER,
		        NULL
			);
			//SetConsoleActiveScreenBuffer(BufOut);
			
			CONSOLE_CURSOR_INFO cci;
    		GetConsoleCursorInfo(GameOut,&cci);
			cci.bVisible=false;
    		SetConsoleCursorInfo(GameOut,&cci);
    		SetConsoleCursorInfo(BufOut,&cci);
			
			turns=1,nowx=1,nowy=1,size=sz;
			memset(map,0x3f,sizeof(map));

			for(int i=1;i<=size;i++){
				for(int j=1;j<=size;j++){
					map[i][j]=true;
					if((i+j)%2==0)
						color[i][j]=false;
					else color[i][j]=true;
					need[i][j]=2;
				}
			}
			for(int i=1;i<=size;i++)
				for(int j=2;j<=size-1;j++)
					need[i][j]++,need[j][i]++;

			for(int i=0;i<=size+1;i++){
				need[i][0]=INF+1000000;
				need[0][i]=INF+1000000;
				need[size+1-i][0]=INF+10000000;
				need[0][size+1-i]=INF+10000000;
			}
			return ;
		}
		
		double calthr(int wid){
			int summ=0,sumn=0,cnt=0;
			for(int i=max(nowx-wid,1);i<=min(nowx+wid,size);i++){
				for(int j=max(nowy-wid,1);j<=min(nowy+wid,size);j++){
					summ+=map[i][j];sumn+=need[i][j];++cnt;
				}
			}
			double ans=(summ);
			return ans/(sumn)-(need[nowx][nowy]-map[nowx][nowy])*0.08;
		}
		
		void setGameMap(){
			defaultMapBuilder();
			//xxMapBuilder();
		}
		void defaultMapBuilder(){
			
			//SetConsoleActiveScreenBuffer(GameOut);
			//system("cls");
            //SetConsoleActiveScreenBuffer(BufOut);
            SetConsoleCursorPosition(GameOut,coord);
			Setcol(GameOut,0xf);

			#ifndef FDEBUG
			puts("DEBUG MODE");
			#endif
			
			double threat=(turns-1.0)/(3.0*(size-2)*(size-2)+2.0*(size-2)*4.0+4.0)*100.0;
			printf("Turns:%d(%s) \nThreat:%.0lf%\n",turns,(turns&1)?"RED/YELLOW":"BLUE/NAVY",threat);

			for(int i=size;i>=1;i--){
				for(int j=1;j<=size;j++){
					int tmp=0;
					if(map[j][i]>need[j][i]-2) tmp|=ForeInt;
					if(map[j][i]==need[j][i]) tmp|=ForeGreen;
					if(i==nowy&&j==nowx) tmp|=(BackInt|BackBlue|BackRed|BackGreen);
					if(!color[j][i]) Setcol(GameOut,ForeBlue|tmp);
					else Setcol(GameOut,ForeRed|tmp);
					
					printf("%d",map[j][i]);
					Setcol(GameOut,0xf); printf(" ");
				}
				printf("\n");
			}

			int ST=(int) (calthr(1)*100.0);
			printf("SelThreat:%3d%\n",ST);
			
			
			#ifndef FDEBUG
			printf("need:%d now:%d\n",need[nowx][nowy],map[nowx][nowy]);
			#endif
			
			//DWORD bytes;
			//ReadConsoleOutputCharacterA(GameOut,Scdata,1000,coord,&bytes);
			//WriteConsoleOutputCharacterA(BufOut,Scdata,1000,coord,&bytes);
			return ;
		}

		bool checkHeadBoom(){
			for(int i=1;i<=size;i++)
				for(int j=1;j<=size;j++)
					if(map[i][j]>need[i][j]) return true;
			return false;
		}
		int checkGameEnd(){
			bool rd=true,bl=true;
			for(int i=1;i<=size;i++){
				for(int j=1;j<=size;j++){
					if(color[i][j]==false) rd=false;
					if(color[i][j]==true) bl=false;
				}
			}
			if(bl==true) return 1;
			if(rd==true) return 2;
			return 0;
		}
		void extendNum(int x,int y,int t){
			if(checkGameEnd()) return ;
			int n=size;
			if(x<=0||y<=0||x>=size+1||y>=size+1) return ;
			if(map[x][y]>need[x][y]){
				map[x][y]-=need[x][y];
				map[x-1][y]++;color[x-1][y]=t;extendNum(x-1,y,t);
				map[x+1][y]++;color[x+1][y]=t;extendNum(x+1,y,t);
				map[x][y-1]++;color[x][y-1]=t;extendNum(x,y-1,t);
				map[x][y+1]++;color[x][y+1]=t;extendNum(x,y+1,t);
			}
			return ;
		}
		void doGameBoom(int t){
			while(true){
				if(!checkHeadBoom()||checkGameEnd()) return ;
				for(int i=1;i<=size;i++)
					for(int j=1;j<=size;j++)
						extendNum(i,j,t);
			}
			return ;
		}
		
		public:
		maingame(){prepareGame(12);}
		maingame(int sz){prepareGame(sz);}
		~maingame(){
			SetConsoleActiveScreenBuffer(GameOut);
			CloseHandle(BufOut);
		}

		start(){setGameMap();}

		baseinfo getmap(){
			baseinfo info;
			memcpy(info.map,map,sizeof(map));
			memcpy(info.col,color,sizeof(color));
			info.siz=size;
			info.turns=turns;
			return info;
		}

		void setcol(int nx,int ny){nowx=nx;nowy=ny;setGameMap();return ;}

		int keydown(){
			if(color[nowx][nowy]!=(turns&1)){
				#ifndef FDEBUG
				printf("turns:%d color:%d",turns,color[nowx][nowy]);
				#endif

				return 1; 
			}
			
			map[nowx][nowy]++;
			doGameBoom((turns&1));
			int k=checkGameEnd();
			if(k){
				setGameMap();
				printf("Player %d wins.\n",k%2+1);
				system("pause");
				return -1;
			}
			++turns;
			setGameMap();
			return 0;
		}
	};
}

#endif //_MAINGAME_H_
