// String.h: interface for the CMyStringW class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STRINGW_H__02F3F393_12C6_4024_8829_7B6D7A1FB1F4__INCLUDED_)
#define AFX_STRINGW_H__02F3F393_12C6_4024_8829_7B6D7A1FB1F4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string.h>
#include "List.h"

#if !defined(__AFX_H__)
class CMyStringW;
typedef CMyStringW CStringW;
#endif // !__AFX_H__

#pragma warning(push)
#pragma warning(disable:4244)
#pragma warning(disable:4267)

/************************************************************************/
/*                               �ַ���                                 */
/************************************************************************/
class CMyStringW
{
public:
    CMyStringW();
    CMyStringW(wchar_t ch, int nRepeat = 1);
    CMyStringW(const wchar_t *pszSrc);
    CMyStringW(const wchar_t *pszSrc, int nLength);
    CMyStringW(const char *pszSrc);
    CMyStringW(const char *pszSrc, int nLength);
    CMyStringW(const CMyStringW& obj);
    virtual ~CMyStringW();

public:
    inline int GetSize() const; //��������С
    inline int GetLength() const; //�ַ�������
    inline bool IsEmpty() const; //�Ƿ�Ϊ��
    inline const wchar_t *GetBuffer() const; //��ȡ�ַ���
    inline wchar_t *GetBufferSetLength(int nLength = 0); //��ȡ��д������
    inline void ReleaseBuffer(); //���ó���
    inline CMyStringW& Empty(); //����ַ���

    CMyStringW& Append(wchar_t ch); //�ַ���ƴ��
    CMyStringW& Append(const wchar_t *pszSrc); //�ַ���ƴ��
    CMyStringW& Append(const char *pszSrc); //�ַ���ƴ��
    CMyStringW& Append(const CMyStringW& obj); //�ַ���ƴ��
    bool IsEqual(wchar_t ch) const; //�ַ����Ƿ���ͬ
    bool IsEqual(const wchar_t *pszSrc) const; //�ַ����Ƿ���ͬ
    bool IsEqual(const CMyStringW& obj) const; //�ַ����Ƿ���ͬ
    int Compare(wchar_t ch) const; //�Ƚ��ַ���
    int Compare(const wchar_t *pszSrc) const; //�Ƚ��ַ���
    int Compare(const CMyStringW& obj) const; //�Ƚ��ַ���
    bool Contain(wchar_t ch) const; //�Ƿ�����Ӵ�
    int CompareNoCase(char ch) const; //�Ƚ��ַ���
    int CompareNoCase(const wchar_t *pszSrc) const; //�Ƚ��ַ���
    int CompareNoCase(const CMyStringW& obj) const; //�Ƚ��ַ���
    bool Contain(const wchar_t *pszSub) const; //�Ƿ�����Ӵ�
    bool Contain(const CMyStringW& obj) const; //�Ƿ�����Ӵ�
    int Find(wchar_t ch) const; //�����ַ�
    int Find(const wchar_t *pszSub) const; //�����Ӵ�
    int Find(wchar_t ch, int nStart) const; //�����ַ�
    int Find(const wchar_t *pszSub, int nStart) const; //�����Ӵ�
    int ReverseFind(wchar_t ch) const; //��������ַ�

    CMyStringW& Upper(); //תΪ��д
    CMyStringW& Lower(); //תΪСд

    CMyStringW& Remove(int nIndex, int nCount = 0); //�Ƴ��ַ���
    CMyStringW& Insert(int nIndex, const wchar_t *pszSrc); //�����ַ���
    CMyStringW& Replace(const wchar_t *pszOld, const wchar_t *pszNew); //�滻�ַ���
    int Split(const wchar_t *pszSplit, CMyList<CMyStringW>& lstStrings); //�ַ����ָ�

    CMyStringW& Format(const wchar_t *pszFmt, ...); //��ʽ���ַ���

public:
    static int ToInt(const wchar_t *pszSrc); //תΪ����
    static int ToInt(const CMyStringW& obj); //תΪ����
    static double ToFloat(const wchar_t *pszSrc); //תΪ������
    static double ToFloat(const CMyStringW& obj); //תΪ������
    static int ToHex(const CMyStringW& obj); //תΪʮ������
    static int ToHex(const wchar_t *pszSrc); //תΪʮ������
    static CMyStringW FromMultiByte(const char *pszSrc, int nBytes = -1); //���ֽ�ת���ֽ�

    inline static int GetLength(const wchar_t *pszSrc); //��ȡ�ַ�������

public:
    inline operator wchar_t* ();
    inline operator const wchar_t* () const;
    inline wchar_t& operator[](int nIndex);

    inline const CMyStringW& operator= (wchar_t ch);
    inline const CMyStringW& operator= (const wchar_t* psz);
    inline const CMyStringW& operator= (const char* psz);
    inline const CMyStringW& operator= (const CMyStringW& obj);
    inline const CMyStringW& operator+= (wchar_t ch);
    inline const CMyStringW& operator+= (const wchar_t* psz);
    inline const CMyStringW& operator+= (const char* psz);
    inline const CMyStringW& operator+= (const CMyStringW& str);
    inline CMyStringW operator+ (wchar_t ch) const;
    inline CMyStringW operator+ (const wchar_t* psz) const;
    inline CMyStringW operator+ (const char* psz) const;
    inline CMyStringW operator+ (const CMyStringW& str) const;

    inline bool operator== (wchar_t ch) const;
    inline bool operator== (const CMyStringW& str) const;
    inline bool operator== (const wchar_t* psz) const;
    inline bool operator!= (wchar_t ch) const;
    inline bool operator!= (const CMyStringW& str) const;
    inline bool operator!= (const wchar_t* psz) const;
    inline bool operator> (wchar_t ch) const;
    inline bool operator> (const CMyStringW& str) const;
    inline bool operator> (const wchar_t* psz) const;
    inline bool operator>= (wchar_t ch) const;
    inline bool operator>= (const CMyStringW& str) const;
    inline bool operator>= (const wchar_t* psz) const;
    inline bool operator< (wchar_t ch) const;
    inline bool operator< (const CMyStringW& str) const;
    inline bool operator< (const wchar_t* psz) const;
    inline bool operator<= (wchar_t ch) const;
    inline bool operator<= (const CMyStringW& str) const;
    inline bool operator<= (const wchar_t* psz) const;

    friend inline CMyStringW operator+ (wchar_t ch, const CMyStringW& str);
    friend inline CMyStringW operator+ (const wchar_t* psz, const CMyStringW& str);
    friend inline CMyStringW operator+ (const char* psz, const CMyStringW& str);

    friend inline bool operator== (wchar_t ch, const CMyStringW& str);
    friend inline bool operator== (const wchar_t* psz, const CMyStringW& str);
    friend inline bool operator!= (wchar_t ch, const CMyStringW& str);
    friend inline bool operator!= (const wchar_t* psz, const CMyStringW& str);
    friend inline bool operator> (wchar_t ch, const CMyStringW& str);
    friend inline bool operator> (const wchar_t* psz, const CMyStringW& str);
    friend inline bool operator>= (wchar_t ch, const CMyStringW& str);
    friend inline bool operator>= (const wchar_t* psz, const CMyStringW& str);
    friend inline bool operator< (wchar_t ch, const CMyStringW& str);
    friend inline bool operator< (const wchar_t* psz, const CMyStringW& str);
    friend inline bool operator<= (wchar_t ch, const CMyStringW& str);
    friend inline bool operator<= (const wchar_t* psz, const CMyStringW& str);

private:
    wchar_t *m_pBuff;  //������
    int m_nSize; //�ռ�
    int m_nLength; //����
    int *m_pnRefCnt; // ���ü���

    static CMyStringW m_strEmpty;

    void Alloc(int nSize);
    void AllocCopy(const wchar_t *pszBuff, int nSize = 0);
    void CopyBeforeWrite(int nSize = 0);

    inline int  GetRefCnt() const; //��ȡ���ü���
    inline void AddRefCnt(); //�������ü���
    inline void Release(); //�ͷſռ�
};

//��������С
inline int CMyStringW::GetSize() const
{
    return m_nSize;
}

//�ַ�������
inline int CMyStringW::GetLength() const
{
    return m_nLength;
}

//�ַ�������
inline int CMyStringW::GetLength(const wchar_t *pszSrc)
{
    return pszSrc != NULL ? wcslen(pszSrc) : 0;
}

//�Ƿ�Ϊ��
inline bool CMyStringW::IsEmpty() const
{
    return m_nLength == 0;
}

//��ȡ�ַ���
inline const wchar_t *CMyStringW::GetBuffer() const
{
    return m_pBuff;
}

//��ȡ�ַ���
inline wchar_t *CMyStringW::GetBufferSetLength(int nSize)
{
    CopyBeforeWrite(nSize);
    return m_pBuff;
}

//���ó���
inline void CMyStringW::ReleaseBuffer()
{
    m_nLength = GetLength(m_pBuff);
}

//����ַ���
inline CMyStringW& CMyStringW::Empty()
{
    *this = m_strEmpty;

    return *this;
}

//��ȡ���ü���
inline int CMyStringW::GetRefCnt() const
{
    return m_pnRefCnt != NULL ? *m_pnRefCnt : 0;
}

//�������ü���
inline void CMyStringW::AddRefCnt()
{
    if (m_pnRefCnt == NULL)
    {
        m_pnRefCnt = new int(0);
    }

    ++(*m_pnRefCnt);
}

//�ͷſռ�
inline void CMyStringW::Release()
{
    if (m_pnRefCnt != NULL && --(*m_pnRefCnt) == 0)
    {
        delete[] m_pBuff;
        delete m_pnRefCnt;
    }

    m_pBuff = NULL;
    m_pnRefCnt = NULL;
    m_nLength = 0;
    m_nSize = 0;
}

inline CMyStringW::operator wchar_t* ()
{
    return m_pBuff;
}

inline CMyStringW::operator const wchar_t* () const
{
    return m_pBuff;
}

inline wchar_t& CMyStringW::operator[](int nIndex)
{
    return m_pBuff[nIndex];
}

inline const CMyStringW& CMyStringW::operator= (wchar_t ch)
{
    Release();
    AllocCopy(&ch, 2);

    return *this;
}

inline const CMyStringW& CMyStringW::operator= (const wchar_t* psz)
{
    Release();
    AllocCopy(psz);

    return *this;
}

inline const CMyStringW& CMyStringW::operator= (const char* psz)
{
    Release();
    CMyStringW obj = FromMultiByte(psz);
    m_nSize = obj.m_nSize;
    m_nLength = obj.m_nLength;
    m_pBuff = obj.m_pBuff;
    m_pnRefCnt = obj.m_pnRefCnt;
    AddRefCnt();

    return *this;
}

inline const CMyStringW& CMyStringW::operator= (const CMyStringW& obj)
{
    if (this != &obj)
    {
        Release();
        m_nSize = obj.m_nSize;
        m_nLength = obj.m_nLength;
        m_pBuff = obj.m_pBuff;
        m_pnRefCnt = obj.m_pnRefCnt;
        AddRefCnt();
    }

    return *this;
}

inline const CMyStringW& CMyStringW::operator+= (wchar_t ch)
{
    return Append(ch);
}

inline const CMyStringW& CMyStringW::operator+= (const wchar_t* psz)
{
    return Append(psz);
}

inline const CMyStringW& CMyStringW::operator+= (const char* psz)
{
    return Append(psz);
}

inline const CMyStringW& CMyStringW::operator+= (const CMyStringW& str)
{
    return Append(str);
}

inline CMyStringW CMyStringW::operator+ (wchar_t ch) const
{
    return CMyStringW(*this).Append(ch);
}

inline CMyStringW CMyStringW::operator+ (const wchar_t* psz) const
{
    return CMyStringW(*this).Append(psz);
}

inline CMyStringW CMyStringW::operator+ (const char* psz) const
{
    return CMyStringW(*this).Append(psz);
}

inline CMyStringW CMyStringW::operator+ (const CMyStringW& str) const
{
    return CMyStringW(*this).Append(str);
}

inline bool CMyStringW::operator== (wchar_t ch) const
{
    return Compare(ch) == 0;
}

inline bool CMyStringW::operator== (const wchar_t* psz) const
{
    return Compare(psz) == 0;
}

inline bool CMyStringW::operator== (const CMyStringW& str) const
{
    return Compare(str) == 0;
}

inline bool CMyStringW::operator!= (wchar_t ch) const
{
    return Compare(ch) != 0;
}

inline bool CMyStringW::operator!= (const wchar_t* psz) const
{
    return Compare(psz) != 0;
}

inline bool CMyStringW::operator!= (const CMyStringW& str) const
{
    return Compare(str) != 0;
}

inline bool CMyStringW::operator> (wchar_t ch) const
{
    return Compare(ch) > 0;
}

inline bool CMyStringW::operator> (const wchar_t* psz) const
{
    return Compare(psz) > 0;
}

inline bool CMyStringW::operator> (const CMyStringW& str) const
{
    return Compare(str) > 0;
}

inline bool CMyStringW::operator>= (wchar_t ch) const
{
    return Compare(ch) >= 0;
}

inline bool CMyStringW::operator>= (const CMyStringW& str) const
{
    return Compare(str) >= 0;
}

inline bool CMyStringW::operator>= (const wchar_t* psz) const
{
    return Compare(psz) >= 0;
}

inline bool CMyStringW::operator< (wchar_t ch) const
{
    return Compare(ch) < 0;
}

inline bool CMyStringW::operator< (const CMyStringW& str) const
{
    return Compare(str) < 0;
}

inline bool CMyStringW::operator< (const wchar_t* psz) const
{
    return Compare(psz) < 0;
}

inline bool CMyStringW::operator<= (wchar_t ch) const
{
    return Compare(ch) <= 0;
}

inline bool CMyStringW::operator<= (const CMyStringW& str) const
{
    return Compare(str) <= 0;
}

inline bool CMyStringW::operator<= (const wchar_t* psz) const
{
    return Compare(psz) <= 0;
}

inline CMyStringW operator+ (wchar_t ch, const CMyStringW& str)
{
    return CMyStringW(ch) + str;
}

inline CMyStringW operator+ (const wchar_t* psz, const CMyStringW& str)
{
    return CMyStringW(psz) + str;
}

inline CMyStringW operator+ (const char* psz, const CMyStringW& str)
{
    return CMyStringW(psz) + str;
}

inline bool operator== (wchar_t ch, const CMyStringW& str)
{
    return str == ch;
}

inline bool operator== (const wchar_t* psz, const CMyStringW& str)
{
    return str == psz;
}

inline bool operator!= (wchar_t ch, const CMyStringW& str)
{
    return str != ch;
}

inline bool operator!= (const wchar_t* psz, const CMyStringW& str)
{
    return str != psz;
}

inline bool operator> (wchar_t ch, const CMyStringW& str)
{
    return str < ch;
}

inline bool operator>(const wchar_t* psz, const CMyStringW& str)
{
    return str < psz;
}

inline bool operator>= (wchar_t ch, const CMyStringW& str)
{
    return str <= ch;
}

inline bool operator>= (const wchar_t* psz, const CMyStringW& str)
{
    return str <= psz;
}

inline bool operator< (wchar_t ch, const CMyStringW& str)
{
    return str > ch;
}

inline bool operator< (const wchar_t* psz, const CMyStringW& str)
{
    return str > psz;
}

inline bool operator<= (wchar_t ch, const CMyStringW& str)
{
    return str >= ch;
}

inline bool operator<= (const wchar_t* psz, const CMyStringW& str)
{
    return str >= psz;
}

#pragma warning(pop)

#endif // !defined(AFX_STRINGW_H__02F3F393_12C6_4024_8829_7B6D7A1FB1F4__INCLUDED_)
