#pragma once
#include "wordMapPoint.h"
#include "Timing_function.h"
#include<iostream>
#include<fstream>



class mapSearch
{
public:
	mapSearch();
	mapSearch(std::string mapFile);

	~mapSearch();

	void showMap(std::vector<std::vector<wordMapPoint>> sameWordMap);
	void readTxtMap(std::string mapFileName);
	bool checkEdge(int x, int y, std::vector<wordMapPoint> walkWay);
	void search();
	void dfs2(std::vector<std::vector<wordMapPoint>> sameWordMapTemp, wordMapPoint pos, std::vector<wordMapPoint> walkWay, std::vector<wordMapStartPoint> startPosList);
	void dfs(std::vector<std::vector<wordMapPoint>> sameWordMapTemp, wordMapPoint pos,  std::vector<wordMapStartPoint> startPosList, int startPtID);

	void showResult(std::vector<wordMapStartPoint> startPosList);
	void saveResult(std::vector<wordMapStartPoint> startPosList);
	bool checkEnd(std::vector<std::vector<wordMapPoint>> sameWordMapTemp);

	void showMapWay(std::vector<wordMapPoint> wayList);
	std::string int2Direct(const int d[2]);

	std::string mapFilePath;
	std::vector<std::vector<wordMapPoint>> sameWordMap;
	const int dir[4][2] = { { -1,0 } ,{ 0,1 }, {1,0 },{ 0,-1 } }; // 方向向量，(x,y)周围的四个方向  上 右  下 左
	bool isFind = false;
};

