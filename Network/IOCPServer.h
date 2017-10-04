#pragma once

#include "../Common/Singleton.h"
#include "NetworkDef.h"
#include "Socket.h"
#include "ClientManager.h"
#include "IOCPSpeed.h"
#include "Packet.h"

typedef void(*PFNIOCPNotify)(UINT, ClientContext*);

class CIOCPServer
{
    DECLARE_SINGLETON(CIOCPServer)
protected:
    CIOCPServer();
    virtual ~CIOCPServer();

public:
    inline bool IsRunning();
    inline int GetPort();
    inline int GetConnections();

    bool Initialize(PFNIOCPNotify pfnNotify, int nMaxConnect, int nPort); //��ʼ��
    void ShutDown(); //����

    bool CreateCompletionPort(); //������ɶ˿�
    void CloseCompletionPort(); //�ر���ɶ˿�

    static unsigned __stdcall ListenThreadProc(LPVOID lpParam); //�����߳�
    static unsigned __stdcall ThreadPoolFunc(LPVOID lpParam); //�̳߳��߳�

    void Send(AccessToken& Token, CBuffer& Buff, PacketSize nSize = 0); //Ĭ�����ݰ���СΪbuff��С
    void Send(ClientContext* pContext, CBuffer& Buff, PacketSize nSize = 0); //Ĭ�����ݰ���СΪbuff��С
    void Send(AccessToken& Token, CPacket Packet); //�������ݰ�
    void Send(ClientContext* pContext, CPacket Packet); //�������ݰ�
    bool PostSend(ClientContext* pContext); //Ͷ�ݷ�������
    void PostRecv(ClientContext* pContext); //Ͷ�ݽ�������
    void PostRemove(ClientContext* pContext); //Ͷ���Ƴ��ͻ�������
    void RemoveClient(ClientContext* pContext); //�Ƴ��ͻ���

    CMyStringA GetHostName();
    CMyStringA GetHostName(SOCKET socket);
    CMyStringA GetHostAddr();
    CMyStringA GetHostAddr(const char *pszHostName);

protected:
    BEGIN_IOMESSAGE_MAP()
        DECLARE_IOMESSAGE(IO_INITIALIZE, OnInitialize)
        DECLARE_IOMESSAGE(IO_FINALIZE, OnFinalize)
        DECLARE_IOMESSAGE(IO_READ, OnRead)
        DECLARE_IOMESSAGE(IO_WRITE, OnWrite)
    END_IOMESSAGE_MAP()

    void OnAccept(); //��������
    void OnInitialize(ClientContext* pContext, DWORD dwIoSize);
    void OnFinalize(ClientContext* pContext, DWORD dwIoSize);
    void OnRead(ClientContext* pContext, DWORD dwIoSize);
    void OnWrite(ClientContext* pContext, DWORD dwIoSize);

public:
    inline DWORD GetSendSpeed();
    inline DWORD GetRecvSpeed();

protected:
    LONG      m_nPort;
    LONG      m_nWorkerCnt; //�����߳���
    LONG      m_nCurrentCnt; //��ǰ�̳߳���
    LONG      m_nBusyCnt; //æµ�߳���
    UINT      m_nMaxConnect; //���������
    HANDLE    m_hExitEvent; //�˳��¼�
    HANDLE    m_hCompletionPort; //��ɶ˿ھ��
    CMySocket m_ListenSocket; //����Socket
    WSAEVENT  m_hAcceptEvent; //Socket�����¼�
    HANDLE    m_hListenThread; //�����߳�
    PFNIOCPNotify m_pfnNotify; //�ص�����
    CClientManager m_ClientMgr;

protected:
    CIOCPSpeed m_SendSpeed;
    CIOCPSpeed m_RecvSpeed;
};


inline bool CIOCPServer::IsRunning()
{
    return m_hExitEvent != NULL && WaitForSingleObject(m_hExitEvent, 0) == WAIT_OBJECT_0;
}


inline int CIOCPServer::GetPort()
{
    return IsRunning() ? m_nPort : 0;
}


inline int CIOCPServer::GetConnections()
{
    return m_ClientMgr.GetCount();
}


inline DWORD CIOCPServer::GetSendSpeed()
{
    return m_SendSpeed.GetSpeed();
}


inline DWORD CIOCPServer::GetRecvSpeed()
{
    return m_RecvSpeed.GetSpeed();
}