// sameWord.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "mapSearch.h"

#include <windows.h>
#include <process.h>

CSem semNum;
std::string txtFilePath;

unsigned int __stdcall ThreadRunDfs(PVOID pM)
{
	int roateNum = (int)pM;
	mapSearch myMap;

	semNum.Wait();
	std::cout << roateNum << std::endl;

	std::string  path = txtFilePath;
	std::string  filePath = path.substr(0, path.rfind(".")) + "_" + std::to_string(roateNum) + ".txt";

	myMap.roateNum = roateNum;
	myMap.readTxtMap(filePath);
	myMap.showMap(myMap.txtSameWordMap);

	std::cout << "========================" << std::endl;
	semNum.Release();

	myMap.search();

	std::cout << roateNum <<" over "<< std::endl;
	return 0;
}

void testRunDfs(int pM)
{
	int roateNum = (int)pM;
	mapSearch myMap;

	semNum.Wait();
	std::cout << roateNum << std::endl;

	std::string  path = txtFilePath;
	std::string  filePath = path.substr(0, path.rfind(".")) + "_" + std::to_string(roateNum) + ".txt";

	myMap.readTxtMap(filePath);
	myMap.showMap(myMap.txtSameWordMap);

	std::cout << "========================" << std::endl;
	semNum.Release();

	myMap.search();


}
int threadTest(std::string filePath)
{
	semNum.Wait();
	txtFilePath = filePath;
	semNum.Release();

	getOhterTxtMap(txtFilePath);

	const int THREAD_NUM = 4;
	HANDLE handle[THREAD_NUM];

	int i = 0;

	for (i = 0; i < THREAD_NUM; i++)
	{
		handle[i] = (HANDLE)_beginthreadex(NULL, 0, ThreadRunDfs, (PVOID)i, 0, NULL);
	}

	WaitForMultipleObjects(THREAD_NUM, handle, TRUE, INFINITE);
	return 0;
}

void dfsRun(std::string filePath)
{
	mapSearch myMap;
	myMap.readTxtMap(filePath);
 	myMap.showMap(myMap.sameWordMap);
	myMap.search();
	 
}


void test()
{

	std::string filePath = "mapdataTest510.txt"; //mapdataTest42

	 
	std::string buf;
	std::cout << "输入地图地址" << std::endl;
	std::cout << "默认为 " << filePath .c_str()<< std::endl;
		std::cin>>buf;
	if (buf.size() < strlen(".txt"))
	{
	}
	else
	{
		filePath = buf;
	}
	Timing_function mytiming;

	mytiming.Timing_start();

	
	//dfsRun(filePath);

	//多线程不同地图 dfs
	threadTest(filePath);


	mytiming.Timing_finish();


 
}

int main()
{

	test();
 

	system("pause");
	return 0;
}

