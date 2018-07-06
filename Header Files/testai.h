#include "maingame.h"

#ifndef _LOCALAI_H_
#define _LOCALAI_H_

namespace barAi{
	struct choice{
		int val;
		int dx;
		int dy;
		friend bool operator >(choice a,choice b)
			{return a.val>b.val;}
		friend bool operator <(choice a,choice b)
			{return a.val<b.val;}
	};
	class barMachine{
		int map[20][20];
		int need[20][20];
		bool col[20][20];
		int size,turn;
		priority_queue <choice> q;
		void initalGameStatus(baseinfo status){
			memcpy(map,status.map,sizeof map);
			memcpy(col,status.col,sizeof col);
			turn=status.turns&1;
			size=status.siz;
			return ;
		}
		void initalGameNeed(){
			for(int i=1;i<=size;i++){
				for(int j=1;j<=size;j++){
					need[i][j]=4;
					if(i==1||i==size) need[i][j]--;
					if(j==1||j==size) need[i][j]--;
				}
			}
			return ;
		}
		double areaTemp(int wid,int dx,int dy){
			int summ=0,sumn=0,cnt=0;
			for(int i=max(dx-wid,1);i<=min(dx+wid,size);i++){
				int minl=max(dy-wid+abs(i-dx),1);
				int maxr=min(dy+wid-abs(i-dx),size);
				for(int j=minl;j<=maxr;j++){
					summ+=map[i][j];sumn+=need[i][j];++cnt;
				}
			}
			double ans=(summ)/(sumn)-(need[dx][dy]-map[dx][dy])*0.08;
            if(dx<size)
				ans+=(col[dx+1][dy]^turn)*map[dx+1][dy]*0.03;
			if(dx>1)
				ans+=(col[dx-1][dy]^turn)*map[dx-1][dy]*0.03;
			if(dy<size)
				ans+=(col[dx][dy+1]^turn)*map[dx][dy+1]*0.03;
			if(dy<1)
				ans+=(col[dx][dy-1]^turn)*map[dx][dy-1]*0.03;
			return ans;
		}
		public:
		barMachine(){initalGameNeed();}
		//~barMachine(){}
		aiReturn doChoice(baseinfo nowgame){
			while(!q.empty()) q.pop();
			initalGameStatus(nowgame);
			int tmp;
			for(int i=1;i<=size;i++){
				for(int j=1;j<=size;j++){
					if(!(col[i][j]^turn)){
						tmp=(int) (areaTemp(2,i,j)*100.0);
						q.push((choice){tmp,i,j});
					}
				}
			}
			choice *chi;
			chi=new choice [1];
			for(int i=0;i<1;i++){
				chi[i]=q.top();
				q.pop();
			}
			int res=rand()%(1);
			return make_pair(chi[res].dx,chi[res].dy);
			delete[] chi;
		}
	};
}

#endif //_LOCALAI_H_
