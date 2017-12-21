#pragma once
#include <windows.h>

class CSem
{
public:
	CSem(void);
	~CSem(void);

	void Wait();
	void Release();
private:	
	HANDLE m_handle;
	HANDLE m_hMutex;
};

