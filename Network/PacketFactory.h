#pragma once

#include "CustomPacket.h"


//��̬�������ݰ���
class CPacketFactory
{
protected:
    CPacketFactory();
    ~CPacketFactory();

public:
    static ICustomPacket *CreatePacket(PacketType type);
};


