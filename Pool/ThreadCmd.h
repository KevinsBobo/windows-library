#pragma once

#include <windows.h>
#include "../Common/List.h"
#include "../Util/Lock.h"

class IThreadCmd;
typedef CMyList<IThreadCmd*> ThreadCmdList;

/************************************************************************/
/*                                ����                                  */
/************************************************************************/
class IThreadCmd
{
public:
    IThreadCmd();
    virtual ~IThreadCmd();

public:
    virtual bool Excute() = 0;
};

/************************************************************************/
/*                              �������                                */
/************************************************************************/
class CThreadCmdManager
{
public:
    CThreadCmdManager();
    ~CThreadCmdManager();

public:
    bool Insert(IThreadCmd* pCmd); //��������
    IThreadCmd* GetCommand(); //��ȡ��һ������

protected:
    CLock m_lockList;
    ThreadCmdList m_lstCmd;
};



/************************************************************************/
/*                                ʵ��                                  */
/************************************************************************/
inline IThreadCmd::IThreadCmd()
{
}

inline IThreadCmd::~IThreadCmd()
{
}
    

inline CThreadCmdManager::CThreadCmdManager()
{
    
}

inline CThreadCmdManager::~CThreadCmdManager()
{
    LOCK_SCOPE(m_lockList);

    ThreadCmdList::iterator itList = m_lstCmd.begin();

    for (; itList != m_lstCmd.end(); itList++)
    {
        delete *itList;
    }

    m_lstCmd.RemoveAll();
}

inline bool CThreadCmdManager::Insert(IThreadCmd* pCmd)
{
    LOCK_SCOPE(m_lockList);

    if (pCmd != NULL)
    {
        m_lstCmd.AddTail(pCmd);
    }

    return true;
}

inline IThreadCmd* CThreadCmdManager::GetCommand()
{
    LOCK_SCOPE(m_lockList);

    IThreadCmd* pCmd = NULL;

    if (!m_lstCmd.IsEmpty())
    {
        pCmd = m_lstCmd.GetHead();
        m_lstCmd.RemoveHead();
    }

    return pCmd;
}