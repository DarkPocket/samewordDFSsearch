#include "stdafx.h"
#include "mapSearch.h"

const int bufferLen = 256;
mapSearch::mapSearch()
{
}


void mapSearch::readTxtMap(std::string mapFileName)
{
	std::ifstream mapFile(mapFileName.c_str(), std::ios::in);

	if (!mapFile.is_open())
	{
		std::cout << "error " << mapFileName.c_str() << std::endl;
		mapFile.close();
	}
	char buffer[bufferLen] = { 0 };
	std::string mapContent;

	int i = 0;
	while (!mapFile.eof())
	{
		mapFile >> buffer;
		if (mapFile.eof()) break;

		mapContent = buffer;
		std::vector<wordMapPoint> wordMapRow;
		for (int j = 0; j < mapContent.length(); ++j)
		{
			wordMapPoint wordMap;
			//# o x + -
			if (mapContent[j] == MAP_NONE_SYMBOL)
			{
				wordMap.ptAttrib = WALL_POINT;
				wordMap.ptColour = NONE_COLOUR;
			}
			if (mapContent[j] == MAP_NORMAL_BLACK)
			{
				wordMap.ptAttrib = NORMAL_POINT;
				wordMap.ptColour = BLACK_COLOUR;
			}
			if (mapContent[j] == MAP_NORMAL_WHITE)
			{
				wordMap.ptAttrib = NORMAL_POINT;
				wordMap.ptColour = WHITE_COLOUR;
			}
			if (mapContent[j] == MAP_START_WHITE)
			{
				wordMap.ptAttrib = START_POINT;
				wordMap.ptColour = WHITE_COLOUR;
			}
			if (mapContent[j] == MAP_START_BLACK)
			{
				wordMap.ptAttrib = START_POINT;
				wordMap.ptColour = BLACK_COLOUR;
			}
			wordMap.letter = mapContent[j];
			wordMap.x = i;
			wordMap.y = j;
			wordMapRow.push_back(wordMap);
		}
		i++;
		sameWordMap.push_back(wordMapRow);
	}
	mapFilePath = mapFileName;
	mapFile.close();
}

mapSearch::mapSearch(std::string mapFileName)
{
}



void mapSearch::showMap(std::vector<std::vector<wordMapPoint>> sameWordMapTemp)
{
	// ☉ ⊚  ⦿⊚ ◯● ⓪ ⓿
	for (int i = 0; i < sameWordMapTemp.size(); ++i)
	{
		for (int j = 0; j < sameWordMapTemp[i].size(); ++j)
		{
			if (sameWordMapTemp[i][j].letter == MAP_NONE_SYMBOL)
			{
				std::cout << " ";
			}
			if (sameWordMapTemp[i][j].letter == MAP_NORMAL_BLACK)
			{
				std::cout << "●";
			}
			if (sameWordMapTemp[i][j].letter == MAP_NORMAL_WHITE)
			{
				std::cout << "O ";
			}
			if (sameWordMapTemp[i][j].letter == MAP_START_WHITE)
			{
				std::cout << "- ";
			}
			if (sameWordMapTemp[i][j].letter == MAP_START_BLACK)
			{
				std::cout << "* ";
			}
		}
		std::cout << std::endl;
	}
	//std::cout << " 	☉ ⊚  ⦿⊚ ◯● ⓪ ⓿  " << std::endl;

}


bool mapSearch::checkEdge(int x, int y, std::vector<wordMapPoint> walkWay) // 边界条件和约束条件的判断
{
	// 不是墙壁 不在已有范围内
	if ((sameWordMap.size() <= x) || (sameWordMap[0].size() <= y))
	{
		return 0;
	}
	if (sameWordMap[x][y].ptAttrib != WALL_POINT) // 满足条件
	{
		for (int i = 0; i < walkWay.size(); ++i)
		{
			if ((walkWay[i].x == x) && (walkWay[i].y == y))
			{
				return 0;
			}
		}
		return 1;
	}
	else // 与约束条件冲突
		return 0;
}
bool mapSearch::checkEnd(std::vector<std::vector<wordMapPoint>> sameWordMapTemp)
{
	//判断是否结束  全部同一种颜色
	int tempColour = NONE_COLOUR;
	for (int i = 0; i < sameWordMapTemp.size(); ++i)
	{
		for (int j = 0; j < sameWordMapTemp[i].size(); ++j)
		{
			if (sameWordMapTemp[i][j].ptColour != NONE_COLOUR)
			{
				if (tempColour == NONE_COLOUR)
				{
					tempColour = sameWordMapTemp[i][j].ptColour;
				}
				else
				{
					if (tempColour != sameWordMapTemp[i][j].ptColour)
					{
						return false;
					}
				}
			}
		}
	}

	return true;

}

//void mapSearch::dfs(std::vector<std::vector<wordMapPoint>> sameWordMapTemp, wordMapPoint pos, std::vector<wordMapPoint> walkWay, std::vector<wordMapStartPoint> startPosList)
//{
//	walkWay.push_back(pos);
//
//	if (isFind)
//	{
//		return;
//	}
//
//	int i = 0;
//	for (i = 0; i < 4; i++)
//	{
//		int newPosX, newPosY;
//		newPosX = pos.x + dir[i][0];
//		newPosY = pos.y + dir[i][1];
//		if (checkEdge(newPosX, newPosY,walkWay)) // 按照规则生成下一个节点
//		{
//			std::string strDirect = int2Direct(dir[i]);
//			//反转颜色
//			sameWordMapTemp[newPosX][newPosY].ptColour *= (-1);
//
//			if (checkEnd(sameWordMapTemp)) // 出现目标
//			{
//				//...... // 做相应处理
//				//showMapWayDynamic(wayList);
//				isFind = true;
//				return;
//			}
//			showMapWay(walkWay);
//
//			wordMapStartPoint nextStartPos;
//			//是否有下一个起点
//			if (startPosList.size() > 0)
//			{
//				nextStartPos =* startPosList.end();
//				startPosList.pop_back();
//				sameWordMapTemp[nextStartPos.x][nextStartPos.y].ptColour *= (-1);
//				dfs(sameWordMapTemp, nextStartPos, walkWay, startPosList);
//			}
//			else
//			{
//				dfs(sameWordMapTemp, sameWordMapTemp[newPosX][newPosY], walkWay, startPosList);	
//			}
//			//walkWay.pop_back();
//			sameWordMapTemp[newPosX][newPosY].ptColour *= (-1);
//
//		/*	piont pos;
//			pos.x = x;
//			pos.y = y;
//			wayList.push_back(pos);	
//			dfs(x + dir[i][0], y + dir[i][1], wayList);
//			wayList.pop_back();*/
//		}
//
//	}
//	walkWay.pop_back();
//	return; // 没有下层搜索节点，回溯
//
//}

int f = 0;

void mapSearch::dfs(std::vector<std::vector<wordMapPoint>> sameWordMapTemp, wordMapPoint pos, std::vector<wordMapStartPoint> startPosList, int startPtID)
{
	startPosList[startPtID].walkWay.push_back(pos);
	//	walkWay.push_back(pos);
	f++;
	if (isFind)
	{
		return;
	}

	int i = 0;
	for (i = 0; i < 4; i++)
	{
		int newPosX, newPosY;
		newPosX = pos.x + dir[i][0];
		newPosY = pos.y + dir[i][1];
		if (checkEdge(newPosX, newPosY, startPosList[startPtID].walkWay)) // 按照规则生成下一个节点
		{
			std::string strDirect = int2Direct(dir[i]);
			startPosList[startPtID].walkDirect.push_back(strDirect);

			//反转颜色
			sameWordMapTemp[newPosX][newPosY].ptColour *= (-1);

			if (checkEnd(sameWordMapTemp)) // 出现目标
			{
				//...... // 做相应处理
				//showMapWayDynamic(wayList);
				std::cout << "find ！" << std::endl;
				showResult(startPosList);
				saveResult(startPosList);
				isFind = true;
				return;
			}
			wordMapStartPoint nextStartPos;
			//是否有下一个起点
			if (startPosList.size() > startPtID + 1)
			{
				nextStartPos = startPosList[startPtID + 1];
				sameWordMapTemp[nextStartPos.x][nextStartPos.y].ptColour *= (-1);
				dfs(sameWordMapTemp, nextStartPos, startPosList, startPtID + 1);
				//startPtID--;
				sameWordMapTemp[nextStartPos.x][nextStartPos.y].ptColour *= (-1);
			}

			{
				dfs(sameWordMapTemp, sameWordMapTemp[newPosX][newPosY], startPosList, startPtID);
				sameWordMapTemp[newPosX][newPosY].ptColour *= (-1);
			}
			f--;
			if (startPosList[startPtID].walkDirect.size() > 0)
			{
				startPosList[startPtID].walkDirect.pop_back();
			}

		}
		if (isFind)
		{
			return;
		}
	}
	if (startPosList[startPtID].walkWay.size() > 0)
	{
		startPosList[startPtID].walkWay.pop_back();
	}

	return; // 没有下层搜索节点，回溯
}

void mapSearch::showResult(std::vector<wordMapStartPoint> startPosList)
{
	for (int i = 0; i < startPosList.size(); ++i)
	{
		for (int j = 0; j < startPosList[i].walkDirect.size(); ++j)
		{
			std::cout << " " << startPosList[i].walkDirect[j].c_str();
		}
		std::cout << std::endl;
	}
}


void mapSearch::saveResult(std::vector<wordMapStartPoint> startPosList)
{
	std::ofstream fileWrite;
	std::string resultPath;
	resultPath = mapFilePath;
	resultPath.insert(mapFilePath.rfind("."), "_answer");
	fileWrite.open(resultPath, std::ios::out);

	if (!fileWrite.is_open())
	{
		std::cout<< "  saveResult error !!! " << endl;
		return;
	}
	for (int i = 0; i < startPosList.size(); ++i)
	{
		for (int j = 0; j < startPosList[i].walkDirect.size(); ++j)
		{
			fileWrite << " " << startPosList[i].walkDirect[j].c_str();
		}
		fileWrite << std::endl;
	}
	fileWrite.close();
}

void mapSearch::showMapWay(std::vector<wordMapPoint> wayList)
{
	std::vector<std::vector<wordMapPoint>> sameWordMapTemp;
	sameWordMapTemp = sameWordMap;
	for (int k = 0; k < wayList.size(); ++k)
	{
		sameWordMapTemp[wayList[k].x][wayList[k].y].letter = '*';
	}
	for (int i = 0; i < sameWordMapTemp.size(); ++i)
	{
		for (int j = 0; j < sameWordMapTemp[i].size(); ++j)
		{
			std::cout << sameWordMapTemp[i][j].letter;
		}
		std::cout << std::endl;
	}

	for (int i = 0; i < 6; ++i)
	{
		std::cout << "===";
	}
	std::cout << std::endl;
	std::cout << std::endl;
}

void mapSearch::search()
{
	std::vector<wordMapStartPoint> startPosList;
	//提取起点
	for (int i = 0; i < sameWordMap.size(); ++i)
	{
		for (int j = 0; j < sameWordMap[i].size(); ++j)
		{
			if (sameWordMap[i][j].ptAttrib == START_POINT)
			{
				wordMapStartPoint startPos;
				startPos.ptAttrib = sameWordMap[i][j].ptAttrib;
				startPos.ptColour = sameWordMap[i][j].ptColour;
				startPos.x = sameWordMap[i][j].x;
				startPos.y = sameWordMap[i][j].y;
				startPos.letter = sameWordMap[i][j].letter;

				startPosList.push_back(startPos);
			}
		}
	}
	int startPtID = 0;
	wordMapStartPoint firstStartPt = startPosList[startPtID];

	//startPosList.erase(startPosList.begin());

	sameWordMap[firstStartPt.x][firstStartPt.y].ptColour *= (-1);

	dfs(sameWordMap, firstStartPt, startPosList, startPtID);



}

std::string mapSearch::int2Direct(const int d[2])
{   //{ 1,0 },{ 0,1 },{ 0,-1 },{ -1,0 } }; // 方向向量，(x,y)周围的四个方向  上 右  下 左
	std::string strDirect;

	if (d[0] == 1)
	{
		strDirect = "下";
	}
	if (d[1] == 1)
	{
		strDirect = "右";
	}

	if (d[0] == -1)
	{
		strDirect = "上";
	}
	if (d[1] == -1)
	{
		strDirect = "左";
	}
	return strDirect;

}

mapSearch::~mapSearch()
{
}
