#pragma once

#ifndef NULL
#define NULL 0
#endif // !NULL


/************************************************************************/
/*                             ���ü�����                               */
/************************************************************************/
class CRefCnt
{
public:
    CRefCnt(); //���캯��
    ~CRefCnt(); //��������

public:
    void AddRef(); //���ü�����һ
    bool Release(); //���ü�����һ

private:
    int m_nRefCnt; //������
};

//���캯��
inline CRefCnt::CRefCnt()
    : m_nRefCnt(0)
{

}

//��������
inline CRefCnt::~CRefCnt()
{

}

//���ü�����һ
inline void CRefCnt::AddRef()
{
    m_nRefCnt++;
}

//���ü�����һ
inline bool CRefCnt::Release()
{
    return --m_nRefCnt == 0;
}