// MyArray.h: interface for the CMyArray class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYARRAY_H__DF37DCF7_C235_4A3D_8CB6_2FEE8945C118__INCLUDED_)
#define AFX_MYARRAY_H__DF37DCF7_C235_4A3D_8CB6_2FEE8945C118__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFX_H__
#define CArray CMyArray
#endif // __AFX_H__

#ifndef NULL 
#define NULL 0
#endif

//typedef int T;
template <typename T>
class CMyArray  
{
public:
    CMyArray(int nSize = 10, float fltGrow = 2);
    CMyArray(const CMyArray<T>& obj);
	virtual ~CMyArray();

public:
    //Ԫ�ظ���
    inline int GetCount() const;
    //��������
    inline const T* GetData() const;
    //��ȡԪ������
    inline const T& GetAt(int nIndex) const;
    //����Ԫ������
    inline const CMyArray<T>& SetAt(int nIndex, const T& Data);
    //�Ƿ�Ϊ������
    inline bool IsEmpty() const;

    //����Ԫ��λ��
    int Find(const T& Data) const;
    //��������Ԫ��λ��
    CMyArray<int> FindAll(const T& Data) const;

    //�ռ��С
    inline int GetSize() const;
    //����������
    inline CMyArray<T>& SetGrow(float fltGrow);
    //���ÿռ��С
    CMyArray<T>& SetSize(int nSize, bool isGrow = true, bool isCopy = true);

    //Ԫ��׷�ӵ�β��
    int Append(const T& Data);
    //����׷�ӵ�β��
    int Append(const CMyArray<T>& obj);
    //��ָ��λ�ò���Ԫ��
    CMyArray<T>& InsertAt(int nIndex, const T& Data);
    //��ָ��λ�ò�������
    CMyArray<T>& InsertAt(int nIndex, const CMyArray<T>& obj);
    //�Ƴ�ָ��λ�õ�Ԫ��
    CMyArray<T>& RemoveAt(int nIndex, int nCount = 0);

    //��������
    CMyArray<T>& Reverse();
    //�Ƴ���������
    CMyArray<T>& FreeExtra();
    //�Ƴ���������
    CMyArray<T>& RemoveAll();

    //��������
    CMyArray<T>& Sort();
    //���ֲ���
    int BinarySearch(const T& Data) const;

    CMyArray<T>& operator= (const CMyArray<T>& obj);
    inline T& operator[] (int nIndex);

private:
    T *m_pData; //����
    int m_nSize; //�ռ��С
    int m_nCount; //Ԫ�ظ���
    float m_fltGrow; //������

private:
    //��������
    void _QuickSort(int nBegin, int nEnd);
    //���鿽��
    CMyArray<T>& Copy(const CMyArray<T>& obj);
};

template <typename T>
CMyArray<T>::CMyArray(int nSize, float fltGrow)
{
    m_fltGrow = fltGrow;
    m_nSize = nSize;
    m_nCount = 0;
    m_pData = new T[m_nSize];
}

template <typename T>
CMyArray<T>::CMyArray(const CMyArray<T>& obj)
{
    Copy(obj);
}

template <typename T>
CMyArray<T>::~CMyArray()
{
    SetSize(0);
}

//Ԫ�ظ���
template <typename T>
inline int CMyArray<T>::GetCount() const
{
    return m_nCount;
}

//��������
template <typename T>
inline const T* CMyArray<T>::GetData() const
{
    return m_pData;
}

//��ȡԪ������
template <typename T>
inline const T& CMyArray<T>::GetAt(int nIndex) const
{
    return m_pData[nIndex];
}

//����Ԫ������
template <typename T>
inline const CMyArray<T>& CMyArray<T>::SetAt(int nIndex, const T& Data)
{
    m_pData[nIndex] = Data;

    return *this;
}

//�Ƿ�Ϊ������
template <typename T>
inline bool CMyArray<T>::IsEmpty() const
{
    return m_nCount == 0;
}

//����Ԫ��λ��
template <typename T>
int CMyArray<T>::Find(const T& Data) const
{
    for (int i = 0; i < m_nCount; i++)
    {
        if (m_pData[i] == Data)
        {
            return i;
        }
    }

    return -1;
}

//��������Ԫ��λ��
template <typename T>
CMyArray<int> CMyArray<T>::FindAll(const T& Data) const
{
    CMyArray<int> aryIndex;

    for (int i = 0; i < m_nCount; i++)
    {
        if (m_pData[i] == Data)
        {
            aryIndex.Append(i);
        }
    }

    return aryIndex;
}

//�ռ��С
template <typename T>
inline int CMyArray<T>::GetSize() const
{
    return m_nSize;
}

//����������
template <typename T>
inline CMyArray<T>& CMyArray<T>::SetGrow(float fltGrow)
{
    m_fltGrow = fltGrow;

    return *this;
}

//���ÿռ��С
template <typename T>
CMyArray<T>& CMyArray<T>::SetSize(int nSize, bool isGrow, bool isCopy)
{
    if (nSize == 0)
    {
        m_nSize = m_nCount = 0;

        if (m_pData != NULL)
        {
            delete[] m_pData;
            m_pData = NULL;
        }
    }
    else
    {
        T *pData = m_pData;

        if (isGrow)
        {
            m_nSize = (int)(nSize * m_fltGrow);
            m_nSize = m_nSize > nSize ? m_nSize : nSize + 1;
        }
        else
        {
            m_nSize = nSize;
        }
        
        m_nCount = m_nCount > nSize ? nSize : m_nCount;
        m_pData = new T[m_nSize];
        
        if (isCopy && pData != NULL)
        {
            for (int i = 0; i < m_nCount; i++)
            {
                m_pData[i] = pData[i];
            }

            delete[] pData;
            pData = NULL;
        }
    }

    return *this;
}

//Ԫ��׷�ӵ�β��
template <typename T>
int CMyArray<T>::Append(const T& Data)
{
    if (m_nCount >= m_nSize)
    {
        SetSize(m_nCount + 1);
    }

    int nIndex = m_nCount;

    m_pData[m_nCount++] = Data;

    return nIndex;
}

//����׷�ӵ�β��
template <typename T>
int CMyArray<T>::Append(const CMyArray<T>& obj)
{
    if (obj.m_pData == NULL)
    {
        return -1;
    }

    if (m_nCount + obj.m_nCount > m_nSize)
    {
        SetSize(m_nCount + obj.m_nCount);
    }

    for (int i = 0; i < obj.m_nCount; i++)
    {
        m_pData[m_nCount + i] = obj.m_pData[i];
    }

    int nIndex = m_nCount;

    m_nCount += obj.m_nCount;

    return nIndex;
}

//��ָ��λ�ò���Ԫ��
template <typename T>
CMyArray<T>& CMyArray<T>::InsertAt(int nIndex, const T& Data)
{
    const int nCount = 1;
    int nNewCount = m_nCount + nCount;
    int i = 0;
    
    nIndex = nIndex >= nNewCount ? m_nCount : nIndex;
    
    if (nNewCount > m_nSize)
    {
        T *pData = m_pData;

        SetSize(nNewCount, true, false);

        if (pData != NULL)
        {
            for (i = 0; i < m_nCount && i < nIndex; i++)
            {
                m_pData[i] = pData[i];
            }

            for (i = m_nCount - 1; i >= nIndex; i--)
            {
                m_pData[i + nCount] = pData[i];
            }

            delete[] pData;
            pData = NULL;
        }
    }
    else
    {
        for (i = m_nCount - 1; i >= nIndex; i--)
        {
            m_pData[i + nCount] = m_pData[i];
        }
    }

    m_pData[nIndex] = Data;
    m_nCount = nNewCount;

    return *this;
}

//��ָ��λ�ò�������
template <typename T>
CMyArray<T>& CMyArray<T>::InsertAt(int nIndex, const CMyArray<T>& obj)
{
    int nCount = obj.m_nCount;
    int nNewCount = m_nCount + nCount;
    int i = 0;

    T *pData = NULL;
    T *pDataSrc = obj.m_pData;

    nIndex = nIndex >= nNewCount ? m_nCount : nIndex;
    
    if (nNewCount > m_nSize)
    {
        pData = m_pData;
        
        SetSize(nNewCount, true, false);
        
        if (pData != NULL)
        {
            for (i = 0; i < m_nCount && i < nIndex; i++)
            {
                m_pData[i] = pData[i];
            }
            
            for (i = m_nCount - 1; i >= nIndex; i--)
            {
                m_pData[i + nCount] = pData[i];
            }
        }
    }
    else
    {
        for (i = m_nCount - 1; i >= nIndex; i--)
        {
            m_pData[i + nCount] = m_pData[i];
        }
    }

    for (i = nCount - 1; i >= 0; i--)
    {
        m_pData[i + nIndex] = pDataSrc[i];
    }

    m_nCount = nNewCount;

    if (pData != NULL)
    {
        delete[] pData;
        pData = NULL;
    }
    
    return *this;
}

//�Ƴ�ָ��λ�õ�Ԫ��
template <typename T>
CMyArray<T>& CMyArray<T>::RemoveAt(int nIndex, int nCount)
{
    if (nCount <= 0 || nIndex + nCount >= m_nCount)
    {
        m_nCount = nIndex;
    }
    else
    {
        m_nCount -= nCount;

        for (int i = nIndex; i < m_nCount; i++)
        {
            m_pData[i] = m_pData[i + nCount];
        }
    }

    return *this;
}

//���鿽��
template <typename T>
CMyArray<T>& CMyArray<T>::Copy(const CMyArray<T>& obj)
{
    if (obj.m_pData == NULL)
    {
        return *this;
    }

    m_fltGrow = obj.m_fltGrow;
    m_nSize = obj.m_nSize;
    m_nCount = obj.m_nCount;
    m_pData = new T[m_nSize];

    for (int i = 0; i < m_nCount; i++)
    {
        m_pData[i] = obj.m_pData[i];
    }

    return *this;
}

//��������
template <typename T>
CMyArray<T>& CMyArray<T>::Reverse()
{
    int nLeft = 0;
    int nRight = m_nCount - 1;

    while (nLeft < nRight)
    {
        T Data = m_pData[nLeft];
        m_pData[nLeft] = m_pData[nRight];
        m_pData[nRight] = Data;

        nLeft++;
        nRight--;
    }

    return *this;
}

//�Ƴ���������
template <typename T>
CMyArray<T>& CMyArray<T>::FreeExtra()
{
    SetSize(m_nCount, false);

    return *this;
}

//�Ƴ���������
template <typename T>
CMyArray<T>& CMyArray<T>::RemoveAll()
{
    SetSize(0);

    return *this;
}

//��������
template <typename T>
CMyArray<T>& CMyArray<T>::Sort()
{
    _QuickSort(0, m_nCount - 1);

    return *this;
}

//��������
template <typename T>
void CMyArray<T>::_QuickSort(int nBegin, int nEnd)
{
    int nLeft = nBegin;
    int nRight = nEnd;
    T Key = m_pData[nBegin];
    
    while (nLeft < nRight)
    {
        while (nLeft < nRight)
        {
            if (Key > m_pData[nRight])
            {
                m_pData[nLeft++] = m_pData[nRight];
                break;
            }

            nRight--;
        }
        
        while (nLeft < nRight)
        {
            if (m_pData[nLeft] > Key)
            {
                m_pData[nRight--] = m_pData[nLeft];
                break;
            }
            
            nLeft++;
        }
    }
    
    m_pData[nLeft] = Key;
    
    if (nBegin < nLeft - 1)
    {
        _QuickSort(nBegin, nLeft - 1);
    }

    if (nLeft + 1 < nEnd)
    {
        _QuickSort(nLeft + 1, nEnd);
    }
}

//���ֲ���
template <typename T>
int CMyArray<T>::BinarySearch(const T& Data) const
{
    int nLeft = 0;
    int nRight = m_nCount - 1;

    while (nLeft <= nRight)
    {
        int nMid = (nLeft + nRight) / 2;

        if (Data > m_pData[nMid])
        {
            nLeft = nMid + 1;
        }
        else if (m_pData[nMid] > Data)
        {
            nRight = nMid - 1;
        }
        else
        {
            return nMid;
        }
    }

    return -1;
}

template <typename T>
CMyArray<T>& CMyArray<T>::operator= (const CMyArray<T>& obj)
{
    if (this == &obj)
    {
        return *this;
    }

    SetSize(0);
    Copy(obj);

    return *this;
}

template <typename T>
inline T& CMyArray<T>::operator[] (int nIndex)
{
    return m_pData[nIndex];
}

#endif // !defined(AFX_MYARRAY_H__DF37DCF7_C235_4A3D_8CB6_2FEE8945C118__INCLUDED_)
