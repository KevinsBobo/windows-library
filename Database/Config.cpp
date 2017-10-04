#include "Config.h"
#include <Windows.h>
#include <tchar.h>

CMyString GetCurrentPath()
{
    TCHAR szPath[MAX_PATH] = { 0 };

    //�õ���ǰexe·��
    HMODULE hModule = GetModuleHandle(0);

    GetModuleFileName(hModule, szPath, MAX_PATH);

    //�õ�exe����·��
    TCHAR *pDest = _tcsrchr(szPath, TEXT('\\'));

    if (pDest != NULL)
    {
        pDest[1] = TEXT('\0');
    }

    return szPath;
}


CMyString GetConfigString(const TCHAR *pszPath, const TCHAR *pszAppName, const TCHAR *pszKeyName)
{
    CMyString strPath = GetCurrentPath();
    strPath.Append(pszPath);

    TCHAR szConn[MAXBYTE] = { 0 };
    DWORD dwRet = GetPrivateProfileString(
        pszAppName,             // INI�ļ��е�һ���ֶ���[����]�����кܶ������
        pszKeyName,             // lpAppName �µ�һ��������Ҳ�����������ı�����
        TEXT(""),               // ���lpReturnedStringΪ��,��Ѹ���������lpReturnedString
        szConn,                 // ��ż�ֵ��ָ�����,���ڽ���INI�ļ��м�ֵ(����)�Ľ��ջ�����
        MAXBYTE,                // lpReturnedString�Ļ�������С
        strPath);               // INI�ļ���·��

    return szConn;
}