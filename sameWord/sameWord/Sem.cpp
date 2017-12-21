#include "stdafx.h"
#include "Sem.h"

CSem::CSem(void)
{
	m_handle = CreateSemaphore(NULL, 0, 1, NULL);
	m_hMutex = CreateMutex(NULL, FALSE, NULL);
	Release();
}


CSem::~CSem(void)
{
	CloseHandle(m_hMutex);
	CloseHandle(m_handle);
}

void CSem::Wait()
{
	WaitForSingleObject(m_hMutex, INFINITE);
	WaitForSingleObject(m_handle, INFINITE);
}

void CSem::Release()
{
	ReleaseSemaphore( m_handle, 1, NULL );
	ReleaseMutex(m_hMutex);
}
