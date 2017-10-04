#pragma once

#include "../Common.h"
#include "NetworkDef.h"

/*
ʹ���Զ������ݰ�������Ҫ��

1.��.h������������ݣ�ֻ�����һ�Σ�������stdafx.h�ж��壩
*************************************************************
//�������ݰ��ڴ˴�ע��
#define REGISTER_PACKET(register) \
    register(CScreenPacket) \
    register(CCmdProcPacket) \
    register(CLoginPacket)

//�������ݰ�����
enum { REGISTER_PACKET(PACKET_TYPE) };
*************************************************************

2.��.cpp������������ݣ�ֻ�����һ�Σ�������stdafx.cpp�ж��壩
*************************************************************
REGISTER_PACKET(IMPLEMENT_PACKET)                           
*************************************************************
*/

// ��̬���������ݰ�����Ҫ��������
// 1.�̳�ICustomPacket����������������DECLARE_PACKET��
// 2.��REGISTER_PACKET������Ӹ���
class ICustomPacket
{
public:
    virtual bool OnWrite(CBuffer& Buff) = 0; //�ӻ�����д����
    virtual bool OnRead(CBuffer& Buff) = 0; //�ӻ�����������
    virtual bool OnProcess(void *lpParam) = 0; //ִ�ж�Ӧ����

public:
    //����DECLARE_PACKET��֮����Ҫ������ʵ��������麯��
    virtual PacketType GetPacketType() = 0;
};


typedef ICustomPacket* (*PFNCREATEPACKET)();

//���ݰ�ע����
class CPacketRegister
{
public:
    CPacketRegister(PacketType type, PFNCREATEPACKET pfn);
    ~CPacketRegister();

protected:
    friend class CPacketFactory;
    static CHashMap<PacketType, PFNCREATEPACKET> *m_pMap;
};
