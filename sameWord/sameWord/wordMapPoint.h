#pragma once

#include<vector>

#define	NONE_COLOUR (0)
#define	WHITE_COLOUR (4)
#define	BLACK_COLOUR -(WHITE_COLOUR)

#define	WALL_POINT (0)
#define	NORMAL_POINT (1)
#define	START_POINT (2)

#define	MAP_NONE_SYMBOL		 '#'
#define	MAP_NORMAL_BLACK	'x'
#define	MAP_NORMAL_WHITE	'o'
#define	MAP_START_BLACK		'-'
#define	MAP_START_WHITE		'+'
 

class wordMapPoint
{
public:
	wordMapPoint();
	~wordMapPoint();
	int ptColour;
	int ptAttrib;
	int x;
	int y;
	char letter;
};


class wordMapStartPoint :public wordMapPoint
{
public:
	std::vector<wordMapPoint> vst;  //拜访过的位置点
	std::vector<wordMapPoint> walkWay; //行走路线

	std::vector<std::string> walkDirect; //行走方向
	std::vector<int > walkDirectNum;
	//wordMapPoint & operator=(const wordMapStartPoint &t1) {
	//	ptColour = t1.ptColour;
	//	ptAttrib = t1.ptAttrib;
	//	x = t1.x;
	//	y = t1.y;
	//	letter = t1.letter;
	//	vst = t1.vst;
	//	walkWay = t1.walkWay;
	//	return *this;
	//}
};