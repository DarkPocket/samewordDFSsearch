// sameWord.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include "mapSearch.h"


void test()
{
	std::string filePath = "mapdataTest.txt";
	//filePath = "map.txt";
	mapSearch myMap;

	std::string buf;
	std::cout << "" <<std::endl;
	std::cin>>buf;
	if (buf.size() < strlen(".txt"))
	{

	}else
	{
		filePath = buf;
	}

	myMap.readTxtMap(filePath);
	myMap.showMap(myMap.sameWordMap);

	if (myMap.checkEnd(myMap.sameWordMap))
	{
		std::cout << "same" << std::endl;
	}
	else
	{
		std::cout << "no same" << std::endl;
	}
	myMap.search();

}

int main()
{
	Timing_function mytiming;

	mytiming.Timing_start();
	test();

	mytiming.Timing_finish();

	system("pause");
    return 0;
}

