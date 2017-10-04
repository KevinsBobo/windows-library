#pragma once

typedef void* AccessToken;
typedef unsigned char PacketType;
typedef unsigned long PacketSize;

const PacketType PACKET_TYPE_UNUSED = 0xFF;
const PacketSize PACKET_SIZE_RECEIVE = 0x1000;

//iocpģ��io����
typedef enum emIO_TYPE
{
    IO_INITIALIZE,
    IO_FINALIZE,
    IO_READ,
    IO_WRITE,
}IO_TYPE;

//iocpģ�ͻص�����֪ͨ����
typedef enum _NOTIFY_TYPE
{
    /*
        �ͻ�������(������Token)
    */
    NC_CONNECT,

    /*
        �ͻ��˶Ͽ�
    */
    NC_DISCONNECT,

    /*
        ��������
    */
    NC_SEND,
    
    /*
        Ͷ�ݽ�������
        �����޸�Ͷ�ݽ�������Ĵ�СpContext->m_wsaRecvBuff.len
    */
    NC_POSTRECEIVE,

    /*
        �յ�����
        ���Զ�pContext->m_RecvBuff�е����ݽ��н�������
    */
    NC_RECEIVE,

}NOTIFY_TYPE;

//�����Զ������ݰ�
#define DECLARE_PACKET(class_name) \
    friend class CPacket; \
    static CPacketRegister m_Register; \
    static class_name* CreatePacket(); \
    virtual PacketType GetPacketType();

//�Զ������ݰ�ʵ��
#define IMPLEMENT_PACKET(class_name) \
    CPacketRegister class_name::m_Register(PT_##class_name, (PFNCREATEPACKET)CreatePacket); \
    PacketType class_name::GetPacketType() { return (PacketType)PT_##class_name; } \
    class_name* class_name::CreatePacket() { return new class_name; }

//��ȡ���ݰ�����
#define GET_PACKET_TYPE(class_name) ((PacketType)PT_##class_name)
#define PACKET_TYPE(class_name) PT_##class_name,

//����IO�������¼�
#define BEGIN_IOMESSAGE_MAP() static void OnMsgHandle(IO_TYPE ioType, CIOCPServer* pIocp, ClientContext* pContext, DWORD dwIoSize) { switch (ioType) {
#define DECLARE_IOMESSAGE(ioType, pfnHandle) case ioType: pIocp->pfnHandle(pContext, dwIoSize); break;
#define END_IOMESSAGE_MAP() } }
