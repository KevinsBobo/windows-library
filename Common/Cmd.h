#pragma once

#include "list.h"

class ICmd;
typedef CMyList<ICmd*> CommandList;

/************************************************************************/
/*                                ����                                  */
/************************************************************************/
class ICmd 
{
public:
    ICmd();
    virtual ~ICmd();

public:
    virtual void UnExcute() = 0; //����
    virtual void Excute() = 0; //����
};


/************************************************************************/
/*                              �������                                */
/************************************************************************/
class CCmdManager
{
public:
    CCmdManager();
    virtual ~CCmdManager();

public:
    void UnExcute(); //����
    void Excute(); //����
    void Insert(ICmd *pCmd);

protected:
    void RemoveAll(CommandList& lstCmds);

protected:
    CommandList m_lstUnExcuteCmds; //��������
    CommandList m_lstExcuteCmds; //��������
};



/************************************************************************/
/*             ʵ��(Ϊ�˼���MFC��CList,�����к�����Ϊinline)            */
/************************************************************************/
inline ICmd::ICmd()
{
}


inline ICmd::~ICmd()
{
}


inline CCmdManager::CCmdManager()
{
}


inline CCmdManager::~CCmdManager()
{
    RemoveAll(m_lstUnExcuteCmds);
    RemoveAll(m_lstExcuteCmds);
}

//����
inline void CCmdManager::UnExcute()
{
    if (!m_lstUnExcuteCmds.IsEmpty())
    {
        ICmd *pCmd = m_lstUnExcuteCmds.GetTail();
        pCmd->UnExcute();

        m_lstUnExcuteCmds.RemoveTail();
        m_lstExcuteCmds.AddTail(pCmd);
    }
}

//����
inline void CCmdManager::Excute()
{
    if (!m_lstExcuteCmds.IsEmpty())
    {
        ICmd *pCmd = m_lstExcuteCmds.GetTail();
        pCmd->Excute();

        m_lstExcuteCmds.RemoveTail();
        m_lstUnExcuteCmds.AddTail(pCmd);
    }
}


inline void CCmdManager::Insert(ICmd *pCmd)
{
    m_lstUnExcuteCmds.AddTail(pCmd);
    RemoveAll(m_lstExcuteCmds);
}


inline void CCmdManager::RemoveAll(CommandList& lstCmds)
{
    CommandList::iterator itCmd = lstCmds.begin();
    for (; itCmd != lstCmds.end(); itCmd++)
    {
        delete *itCmd;
    }
    lstCmds.RemoveAll();
}