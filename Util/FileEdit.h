#pragma once

#include "../Common.h"
#include "FileUtil.h"

/************************************************************************/
/*                              CFileEdit                               */
/************************************************************************/

class CFileEdit : public CFileUtil
{
public:
    CFileEdit();
    virtual ~CFileEdit();

public:
    bool Read(int nOffset = 0, size_t nSize = 0); //��ȡ�ļ�
    bool Write(int nOffset = 0, size_t nSize = 0); //�����ļ�

    size_t GetSize(); //���������ô�С
    size_t GetTotalSize(); //�������ܴ�С

    void Swap(CBuffer& Buffer); //�������л�����
    bool IsValid(size_t nOffset); //ƫ���Ƿ���Ч
    bool IsValid(const void *pData); //�������Ƿ���Ч
    void *GetBuffer(size_t nOffset, size_t nLen = 0); //��ȡ�ɶ���������nLenΪ0��ָ������
    void *SetBuffer(size_t nOffset, size_t nLen); //��ȡ��д������

    size_t GetOffset(const void *pData); //��ȡƫ��
    size_t GetMaxLen(const void *pData); //��ȡ��󳤶�

protected:
    CBuffer m_Buffer;
};



/************************************************************************/
/*                             CFileEditPtr                             */
/************************************************************************/

template <typename T>
class CFileEditPtr
{
public:
    CFileEditPtr(CFileEdit *pFile);
    ~CFileEditPtr();

public:
    size_t GetSize() const;
    size_t GetOffset() const;
    size_t GetEndOffset() const;

    void SetOffset(size_t nOffset);
    void SetOffset(const void *pData);
    void SetMemory(int chDest = 0);

    operator T* ();
    T* operator-> ();
    bool operator! ();
    bool operator== (const void *pData);
    bool operator!= (const void *pData);

protected:
    size_t     m_nOffset;
    CFileEdit *m_pFile;

#ifdef _DEBUG
    T*       m_pData;
#endif
};


/************************************************************************/
/*                             CFileEditAry                              */
/************************************************************************/

template <typename T>
class CFileEditAry
{
public:
    CFileEditAry(CFileEdit *pFile);
    ~CFileEditAry();

public:
    int GetCount() const;
    size_t GetSize() const;
    size_t GetOffset() const;
    size_t GetEndOffset() const;

    void SetCount(int nCount);
    void SetOffset(size_t nOffset);
    void SetOffset(const void *pData);
    void SetMemory(int chDest = 0);

    operator T* ();
    T& operator[] (int nIndex);
    bool operator! ();
    bool operator== (const void *pData);
    bool operator!= (const void *pData);

protected:
    int        m_nCount;
    size_t     m_nOffset;
    CFileEdit *m_pFile;

#ifdef _DEBUG
    T*       m_pData;
#endif
};



/************************************************************************/
/*                              CFileEdit                               */
/************************************************************************/

inline CFileEdit::CFileEdit()
{

}

inline CFileEdit::~CFileEdit()
{

}

//��ȡpe�ļ�
inline bool CFileEdit::Read(int nOffset, size_t nSize)
{
    assert(IsOpen());

    m_Buffer.Clear();

    nSize = nSize == 0 ? SeekToEnd() - nOffset : nSize;

    if (CFileUtil::Read(nOffset, m_Buffer.Write(nSize), nSize) == 0)
    {
        m_Buffer.Clear();
        return false;
    }

    return true;
}

//����pe�ļ�
inline bool CFileEdit::Write(int nOffset, size_t nSize)
{
    assert(IsOpen());

    nSize = nSize == 0 ? m_Buffer.GetReadableSize() : nSize;

    return CFileUtil::Write(nOffset, m_Buffer, nSize) == m_Buffer.GetReadableSize();
}

//�������ܴ�С
inline size_t CFileEdit::GetTotalSize()
{
    return m_Buffer.GetTotalSize();
}

//��������ǰ��С
inline size_t CFileEdit::GetSize()
{
    return m_Buffer.GetReadableSize();
}

//��ȡ��д������
inline void CFileEdit::Swap(CBuffer& Buffer)
{
    m_Buffer.Swap(Buffer);
}

//ƫ���Ƿ���Ч
inline bool CFileEdit::IsValid(size_t nOffset)
{
    return nOffset < GetTotalSize();
}

//�������Ƿ���Ч
inline bool CFileEdit::IsValid(const void *pData)
{
    return GetOffset(pData) < GetTotalSize();
}

//��ȡ�ɶ�������
inline void *CFileEdit::GetBuffer(size_t nOffset, size_t nLen)
{
    if (nOffset < m_Buffer.GetReadableSize() &&
        (nLen == 0 || nOffset + nLen <= m_Buffer.GetReadableSize()))
    {
        return (char*)m_Buffer + nOffset;
    }

    return NULL;
}

//��ȡ��д������
inline void *CFileEdit::SetBuffer(size_t nOffset, size_t nLen)
{
    assert(nOffset <= nOffset + nLen);

    if (nOffset + nLen > m_Buffer.GetReadableSize())
    {
        m_Buffer.SetBufferSize(nOffset + nLen);
    }

    return (char*)m_Buffer + nOffset;
}

//��ȡָ����ڵ��ļ�ƫ��
inline size_t CFileEdit::GetOffset(const void *pData)
{
    return (char*)pData - (char*)m_Buffer;
}

//��ȡָ��λ�ô���󳤶�
inline size_t CFileEdit::GetMaxLen(const void *pData)
{
    if (pData >= m_Buffer && pData < (char*)m_Buffer + m_Buffer.GetReadableSize())
    {
        return (char*)m_Buffer + m_Buffer.GetReadableSize() - (char*)pData;
    }

    return 0;
}

/************************************************************************/
/*                            CFileEditPtr                              */
/************************************************************************/

template <typename T>
inline CFileEditPtr<T>::CFileEditPtr(CFileEdit *pFile)
    : m_nOffset(-1)
    , m_pFile(pFile)
{

}

template <typename T>
inline CFileEditPtr<T>::~CFileEditPtr()
{
    //assert(m_pFile != NULL);
}

template <typename T>
inline size_t CFileEditPtr<T>::GetSize() const
{
    return sizeof(T);
}

template <typename T>
inline size_t CFileEditPtr<T>::GetOffset() const
{
    assert(m_pFile != NULL);
    assert(GetEndOffset() <= m_pFile->GetTotalSize());

    return m_nOffset;
}

template <typename T>
inline size_t CFileEditPtr<T>::GetEndOffset() const
{
    assert(m_pFile != NULL);

    return m_nOffset + GetSize();
}

template <typename T>
inline void CFileEditPtr<T>::SetOffset(size_t nOffset)
{
    assert(m_pFile != NULL);

    m_nOffset = nOffset;
    m_pFile->SetBuffer(0, GetEndOffset());

#ifdef _DEBUG
    m_pData = *this;
#endif // _DEBUG
}

template <typename T>
inline void CFileEditPtr<T>::SetOffset(const void *pData)
{
    assert(m_pFile != NULL);

    pData != NULL ? SetOffset(m_pFile->GetOffset(pData)) : m_nOffset = -1;

#ifdef _DEBUG
    m_pData = *this;
#endif // _DEBUG
}

template <typename T>
inline void CFileEditPtr<T>::SetMemory(int chDest)
{
    assert(m_pFile != NULL);

    memset(*this, chDest, GetSize());
}

template <typename T>
inline CFileEditPtr<T>::operator T* ()
{
    assert(m_pFile != NULL);
    assert(GetEndOffset() <= m_pFile->GetTotalSize());

    return *this != NULL ? (T*)m_pFile->GetBuffer(m_nOffset) : NULL;
}

template <typename T>
inline T* CFileEditPtr<T>::operator-> ()
{
    assert(m_pFile != NULL);
    assert(GetEndOffset() <= m_pFile->GetTotalSize());

    return (T*)m_pFile->GetBuffer(m_nOffset);
}

template <typename T>
inline bool CFileEditPtr<T>::operator! ()
{
    return m_nOffset == -1;
}

template <typename T>
inline bool CFileEditPtr<T>::operator== (const void *pData)
{
    return pData != NULL ? m_nOffset == m_pFile->GetOffset(pData) : m_nOffset == -1;
}

template <typename T>
inline bool CFileEditPtr<T>::operator!= (const void *pData)
{
    return pData != NULL ? m_nOffset != m_pFile->GetOffset(pData) : m_nOffset != -1;
}

/************************************************************************/
/*                            CFileEditAry                              */
/************************************************************************/

template <typename T>
inline CFileEditAry<T>::CFileEditAry(CFileEdit *pFile)
    : m_nOffset(-1)
    , m_nCount(0)
    , m_pFile(pFile)
{

}

template <typename T>
inline CFileEditAry<T>::~CFileEditAry()
{
    //assert(m_pFile != NULL);
}

template <typename T>
inline size_t CFileEditAry<T>::GetSize() const
{
    return m_nCount * sizeof(T);
}

template <typename T>
inline size_t CFileEditAry<T>::GetOffset() const
{
    assert(m_pFile != NULL);
    assert(GetEndOffset() <= m_pFile->GetTotalSize());

    return m_nOffset;
}

template <typename T>
inline size_t CFileEditAry<T>::GetEndOffset() const
{
    assert(m_pFile != NULL);

    return m_nOffset + GetSize();
}

template <typename T>
inline void CFileEditAry<T>::SetOffset(size_t nOffset)
{
    assert(m_pFile != NULL);

    m_nOffset = nOffset;
    m_pFile->SetBuffer(0, GetEndOffset());

#ifdef _DEBUG
    m_pData = *this;
#endif // _DEBUG
}

template <typename T>
inline void CFileEditAry<T>::SetOffset(const void *pData)
{
    assert(m_pFile != NULL);

    pData != NULL ? SetOffset(m_pFile->GetOffset(pData)) : m_nOffset = -1;

#ifdef _DEBUG
    m_pData = *this;
#endif // _DEBUG
}

template <typename T>
inline int CFileEditAry<T>::GetCount() const
{
    return m_nCount;
}

template <typename T>
inline void CFileEditAry<T>::SetCount(int nCount)
{
    assert(m_pFile != NULL);

    m_nCount = nCount;
    m_pFile->SetBuffer(0, GetEndOffset());
}

template <typename T>
inline void CFileEditAry<T>::SetMemory(int chDest)
{
    assert(m_pFile != NULL);

    memset(*this, chDest, GetSize());
}

template <typename T>
inline CFileEditAry<T>::operator T* ()
{
    assert(m_pFile != NULL);
    assert(GetEndOffset() <= m_pFile->GetTotalSize());

    return *this != NULL ? (T*)m_pFile->GetBuffer(m_nOffset) : NULL;
}

template <typename T>
inline T& CFileEditAry<T>::operator[] (int nIndex)
{
    assert(m_pFile != NULL);
    assert(*this != NULL);

    if (nIndex >= m_nCount)
    {
        SetCount(nIndex + 1);
    }

    return ((T*)m_pFile->GetBuffer(m_nOffset))[nIndex];
}

template <typename T>
inline bool CFileEditAry<T>::operator! ()
{
    return m_nOffset == -1;
}

template <typename T>
inline bool CFileEditAry<T>::operator== (const void *pData)
{
    return pData != NULL ? m_nOffset == m_pFile->GetOffset(pData) : m_nOffset == -1;
}

template <typename T>
inline bool CFileEditAry<T>::operator!= (const void *pData)
{
    return pData != NULL ? m_nOffset != m_pFile->GetOffset(pData) : m_nOffset != -1;
}