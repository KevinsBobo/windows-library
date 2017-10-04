#include "Packet.h"
#include "PacketFactory.h"
#include "CustomPacket.h"
#include "../include/zlib/zlib.h"


CPacket::CPacket()
    : m_pPacket(NULL)
{
    
}


CPacket::CPacket(PacketType type)
{
    m_pPacket = CPacketFactory::CreatePacket(type);
}


CPacket::CPacket(ICustomPacket *pPacket)
    : m_pPacket(pPacket)
{

}


CPacket::CPacket(const CPacket& obj)
{

}


CPacket::~CPacket()
{
    if (m_pPacket != NULL)
    {
        delete m_pPacket;
        m_pPacket = NULL;
    }
}


bool CPacket::OnWrite(CBuffer& Buff, AccessToken *pToken)
{
    if (m_pPacket == NULL)
    {
        return false;
    }

    //��¼һ��ԭ���ж೤
    PacketSize nSize = (PacketSize)Buff.GetReadableSize();

    //Ϊ���ݰ�ͷռ�ÿ�
    PacketHead *pHead = (PacketHead*)Buff.Write(sizeof(PacketHead));

    CBuffer tempBuff;

    //д�����ݰ�����
    if (!m_pPacket->OnWrite(tempBuff))
    {
        return false;
    }

    if (!tempBuff.IsEmpty())
    {
        //ѹ������
        uLong nSrcLen = (uLong)tempBuff.GetReadableSize();
        uLong nDestLen = (uLong)((double)nSrcLen * 1.001) + 12;
        int	nRet = compress(
            (Byte*)Buff.Write(nDestLen), &nDestLen,
            (Byte*)tempBuff.GetBuffer(), nSrcLen);

        if (nRet != Z_OK)
        {
            Buff.SetBufferSize(nSize);
            return false;
        }

        Buff.SetBufferSize(nSize + nDestLen + sizeof(PacketHead));
    }

    //�޸����ݰ�ͷ
    pHead->m_nSize = (PacketSize)Buff.GetReadableSize() - nSize;
    pHead->m_nSrcSize = (PacketSize)tempBuff.GetReadableSize();
    pHead->m_nType = (PacketSize)m_pPacket->GetPacketType();
    pHead->m_Token = pToken != NULL ? *pToken : NULL;

    return true;
}


bool CPacket::OnRead(CBuffer& Buff, AccessToken *pToken)
{
    if (m_pPacket != NULL)
    {
        delete m_pPacket;
        m_pPacket = NULL;
    }

    if (Buff.GetReadableSize() < sizeof(PacketHead))
    {
        return false;
    }

    PacketHead *pHead = (PacketHead*)Buff.GetBuffer();

    //���ݰ�û������
    if (pHead->m_nSize > Buff.GetReadableSize())
    {
        return false;
    }

    //����token
    if (pToken != NULL)
    {
        *pToken = pHead->m_Token;
    }

    Buff.Delete(sizeof(PacketHead));

    CBuffer tempBuff;

    if (pHead->m_nSrcSize != 0)
    {
        //��ѹ����
        uLongf nSrcLen = (uLongf)pHead->GetBuffSize();
        uLongf nDestLen = (uLongf)pHead->m_nSrcSize;
        int	nRet = uncompress(
            (Bytef*)tempBuff.Write(nDestLen), &nDestLen,
            (Bytef*)Buff.Read(nSrcLen), nSrcLen);

        if (nRet != Z_OK)
        {
            return false;
        }
    }

    //��̬�������ݰ�
    m_pPacket = CPacketFactory::CreatePacket(pHead->m_nType);

    if (m_pPacket == NULL)
    {
        return false;
    }

    //�������ݰ�
    if (!m_pPacket->OnRead(tempBuff))
    {
        return false;
    }

    return true;
}


bool CPacket::OnRecv(CMySocket& Socket, AccessToken *pToken)
{
    CBuffer Buff;

    //ռ�����ݰ�ͷ�Ŀ�
    PacketHead *pHead = (PacketHead*)Buff.Write(sizeof(PacketHead));

    if (pHead == NULL)
    {
        return false;
    }

    //�������ݰ�ͷ
    if (!Socket.RecvAll(pHead, sizeof(PacketHead)))
    {
        return false;
    }

    //�������ݳ���
    PacketSize nSize = pHead->GetBuffSize();

    //���հ�����
    void *pBuff = Buff.Write(nSize);

    if (!Socket.RecvAll(pBuff, nSize))
    {
        return false;
    }

    //������
    if (!OnRead(Buff, pToken))
    {
        return false;
    }

    return true;
}


bool CPacket::OnSend(CMySocket& Socket, AccessToken *pToken)
{
    static CLock lock;

    CBuffer Buff;

    //д�����ݰ�
    if (!OnWrite(Buff, pToken))
    {
        return false;
    }

    LOCK_SCOPE(lock);

    //�������ݰ�
    if (!Socket.SendAll(Buff, (PacketSize)Buff.GetReadableSize()))
    {
        return false;
    }

    return true;
}


bool CPacket::OnProcess(void *lpParam)
{
    if (m_pPacket == NULL)
    {
        return false;
    }

    return m_pPacket->OnProcess(lpParam);
}
