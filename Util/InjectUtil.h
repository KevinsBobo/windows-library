#pragma once

#include <windows.h>

/************************************************************************/
/*                             ע�빤����                               */
/************************************************************************/
class CInjectUtil
{
public:
    CInjectUtil(DWORD dwPid = 0);
    ~CInjectUtil();

public:
    //���ý���ID
    inline void SetPid(DWORD dwPid);
    //��ȡ����ID
    inline DWORD GetPid() const;
    //�����Ƿ�����Ч
    inline BOOL IsValidProcess() const;

    //��ȡģ�����ַ
    LPVOID GetBaseAddress(WCHAR *pszModuleName);
    //��ȡ������ģ��ƫ��
    LPVOID GetFuctionOffset(WCHAR *pszDllPath, CHAR *pszProcName);
    //ִ��Զ���߳�
    DWORD ExecRemoteFuction(LPVOID pFucAddr, LPVOID pBuff, SIZE_T nSize, DWORD dwWaitTime = INFINITE);
    
    //��Ŀ����̼���DLL
    DWORD LoadInjectDLL(WCHAR *pszDllPath, SIZE_T nSize, DWORD dwWaitTime = INFINITE);
    //Զ��ִ�к���
    DWORD ExecInjectFuction(WCHAR *pszDllPath, CHAR *pszProcName, LPVOID pBuff, SIZE_T nSize, DWORD dwWaitTime = INFINITE);

protected:
    DWORD  m_dwPid;
    HANDLE m_hProcess;
};


//���ý���ID
inline void CInjectUtil::SetPid(DWORD dwPid)
{
    if (m_hProcess != NULL)
    {
        CloseHandle(m_hProcess);
    }

    m_dwPid = dwPid;
    m_hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, m_dwPid);
}


//��ȡ����ID
inline DWORD CInjectUtil::GetPid() const
{
    return m_dwPid;
}


//�����Ƿ�����Ч
inline BOOL CInjectUtil::IsValidProcess() const
{
    return m_hProcess != NULL;
}