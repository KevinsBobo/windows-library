#pragma once

#include <Windows.h>
#include <Tlhelp32.h>

typedef enum emENUM_RET_TYPE
{
    ENUM_CONTINUE,
    ENUM_RET_TRUE,
    ENUM_RET_FALSE
}ENUM_RET_TYPE;

//�������̻ص�����������ENUM_CONTINUE���������
typedef ENUM_RET_TYPE (*PFNEnumProcess)(PROCESSENTRY32 *pProcessEntry, LPVOID pParam);

//�����̻߳ص�����������ENUM_CONTINUE���������
typedef ENUM_RET_TYPE (*PFNEnumThread)(THREADENTRY32 *pThreadEntry, LPVOID pParam);

//����ģ��ص�����������ENUM_CONTINUE���������
typedef ENUM_RET_TYPE (*PFNEnumModule)(MODULEENTRY32 *pModuleEntry, LPVOID pParam);

class CSnapshoot
{
public:
    //�������̣�Ĭ�Ϸ���TRUE
    static BOOL EnumProcess(PFNEnumProcess pfnEnum, DWORD dwPid = 0, LPVOID pParam = NULL);
    
    //�����̣߳�Ĭ�Ϸ���TRUE
    static BOOL EnumThread(PFNEnumThread pfnEnum, DWORD dwPid = 0, LPVOID pParam = NULL);

    //����ģ�飬Ĭ�Ϸ���TRUE
    static BOOL EnumModule(PFNEnumModule pfnEnum, DWORD dwPid = 0, LPVOID pParam = NULL);
};

