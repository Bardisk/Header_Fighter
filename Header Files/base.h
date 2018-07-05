#include<conio.h>
#include<cstdio>
#include<windows.h>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<queue>
#include<vector>
#include<cmath>
#include<cstdlib>
#include<ctime>

#pragma once

#ifndef _BASE_H_
#define _BASE_H_

const int INF=0x3f3f3f3f;

using std::max;
using std::min;
using std::abs;
using std::pair;
using std::make_pair;
using std::priority_queue;

#define Setcol(hOP,a) SetConsoleTextAttribute(hOP,a)
#define ForeBlue FOREGROUND_BLUE
#define ForeGreen FOREGROUND_GREEN
#define ForeRed FOREGROUND_RED
#define ForeInt FOREGROUND_INTENSITY
#define BackBlue BACKGROUND_BLUE
#define BackGreen BACKGROUND_GREEN
#define BackRed BACKGROUND_RED
#define BackInt BACKGROUND_INTENSITY

typedef \
struct mapBaseInfo{
	bool col[20][20];
	int map[20][20];
	int turns,siz;
}baseinfo;
typedef pair<int,int> aiReturn;

#endif //_BASE_H_

