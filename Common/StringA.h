// String.h: interface for the CMyStringW class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STRINGA_H__02F3F393_12C6_4024_8829_7B6D7A1FB1F4__INCLUDED_)
#define AFX_STRINGA_H__02F3F393_12C6_4024_8829_7B6D7A1FB1F4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string.h>
#include "List.h"

#if !defined(__AFX_H__)
class CMyStringA;
typedef CMyStringA CStringA;
#endif // !__AFX_H__

#pragma warning(push)
#pragma warning(disable:4244)
#pragma warning(disable:4267)

/************************************************************************/
/*                               �ַ���                                 */
/************************************************************************/
class CMyStringA
{
public:
    CMyStringA();
    CMyStringA(char ch, int nRepeat = 1);
    CMyStringA(const char *pszSrc);
    CMyStringA(const char *pszSrc, int nLength);
    CMyStringA(const wchar_t *pszSrc);
    CMyStringA(const wchar_t *pszSrc, int nLength);
    CMyStringA(const CMyStringA& obj);
    virtual ~CMyStringA();

public:
    inline int GetSize() const; //��������С
    inline int GetLength() const; //�ַ�������
    inline bool IsEmpty() const; //�Ƿ�Ϊ��
    inline const char *GetBuffer() const; //��ȡ�ַ���
    inline char *GetBufferSetLength(int nIndex = 0); //��ȡ��д������
    inline void ReleaseBuffer(); //���ó���
    inline CMyStringA& Empty(); //����ַ���

    CMyStringA& Append(char ch); //�ַ���ƴ��
    CMyStringA& Append(const char *pszSrc); //�ַ���ƴ��
    CMyStringA& Append(const wchar_t *pszSrc); //�ַ���ƴ��
    CMyStringA& Append(const CMyStringA& obj); //�ַ���ƴ��
    bool IsEqual(char ch) const; //�ַ����Ƿ���ͬ
    bool IsEqual(const char *pszSrc) const; //�ַ����Ƿ���ͬ
    bool IsEqual(const CMyStringA& obj) const; //�ַ����Ƿ���ͬ
    int Compare(char ch) const; //�Ƚ��ַ���
    int Compare(const char *pszSrc) const; //�Ƚ��ַ���
    int Compare(const CMyStringA& obj) const; //�Ƚ��ַ���
    int CompareNoCase(char ch) const; //�Ƚ��ַ���
    int CompareNoCase(const char *pszSrc) const; //�Ƚ��ַ���
    int CompareNoCase(const CMyStringA& obj) const; //�Ƚ��ַ���
    bool Contain(char ch) const; //�Ƿ�����Ӵ�
    bool Contain(const char *pszSub) const; //�Ƿ�����Ӵ�
    bool Contain(const CMyStringA& obj) const; //�Ƿ�����Ӵ�
    int Find(char ch) const; //�����ַ�
    int Find(const char *pszSub) const; //�����Ӵ�
    int Find(char ch, int nStart) const; //�����ַ�
    int Find(const char *pszSub, int nStart) const; //�����Ӵ�
    int ReverseFind(char ch) const; //��������ַ�

    CMyStringA& Upper(); //תΪ��д
    CMyStringA& Lower(); //תΪСд
    CMyStringA& Remove(int nIndex, int nCount = 0); //�Ƴ��ַ���
    CMyStringA& Insert(int nIndex, const char *pszSrc); //�����ַ���
    CMyStringA& Replace(const char *pszOld, const char *pszNew); //�滻�ַ���
    int Split(const char *pszSplit, CMyList<CMyStringA>& lstStrings); //�ַ����ָ�

    CMyStringA& Format(const char *pszFmt, ...); //��ʽ���ַ���

public:
    static int ToInt(const char *pszSrc); //תΪ����
    static int ToInt(const CMyStringA& obj); //תΪ����
    static double ToFloat(const char *pszSrc); //תΪ������
    static double ToFloat(const CMyStringA& obj); //תΪ������
    static int ToHex(const CMyStringA& obj); //תΪʮ������
    static int ToHex(const char *pszSrc); //תΪʮ������
    static CMyStringA FromWideChar(const wchar_t *pszSrc, int nBytes = -1); //���ֽ�ת���ֽ�

    inline static int GetLength(const char *pszSrc); //��ȡ�ַ�������

public:
    inline operator char* ();
    inline operator const char* () const;
    inline char& operator[](int nIndex);

    inline const CMyStringA& operator= (char ch);
    inline const CMyStringA& operator= (const char* psz);
    inline const CMyStringA& operator= (const wchar_t* psz);
    inline const CMyStringA& operator= (const CMyStringA& obj);
    inline const CMyStringA& operator+= (char ch);
    inline const CMyStringA& operator+= (const char* psz);
    inline const CMyStringA& operator+= (const wchar_t* psz);
    inline const CMyStringA& operator+= (const CMyStringA& str);
    inline CMyStringA operator+ (char ch) const;
    inline CMyStringA operator+ (const char* psz) const;
    inline CMyStringA operator+ (const wchar_t* psz) const;
    inline CMyStringA operator+ (const CMyStringA& str) const;

    inline bool operator== (char ch) const;
    inline bool operator== (const CMyStringA& str) const;
    inline bool operator== (const char* psz) const;
    inline bool operator!= (char ch) const;
    inline bool operator!= (const CMyStringA& str) const;
    inline bool operator!= (const char* psz) const;
    inline bool operator> (char ch) const;
    inline bool operator> (const CMyStringA& str) const;
    inline bool operator> (const char* psz) const;
    inline bool operator>= (char ch) const;
    inline bool operator>= (const CMyStringA& str) const;
    inline bool operator>= (const char* psz) const;
    inline bool operator< (char ch) const;
    inline bool operator< (const CMyStringA& str) const;
    inline bool operator< (const char* psz) const;
    inline bool operator<= (char ch) const;
    inline bool operator<= (const CMyStringA& str) const;
    inline bool operator<= (const char* psz) const;

    friend inline CMyStringA operator+ (char ch, const CMyStringA& str);
    friend inline CMyStringA operator+ (const char* psz, const CMyStringA& str);
    friend inline CMyStringA operator+ (const wchar_t* psz, const CMyStringA& str);

    friend inline bool operator== (char ch, const CMyStringA& str);
    friend inline bool operator== (const char* psz, const CMyStringA& str);
    friend inline bool operator!= (char ch, const CMyStringA& str);
    friend inline bool operator!= (const char* psz, const CMyStringA& str);
    friend inline bool operator> (char ch, const CMyStringA& str);
    friend inline bool operator> (const char* psz, const CMyStringA& str);
    friend inline bool operator>= (char ch, const CMyStringA& str);
    friend inline bool operator>= (const char* psz, const CMyStringA& str);
    friend inline bool operator< (char ch, const CMyStringA& str);
    friend inline bool operator< (const char* psz, const CMyStringA& str);
    friend inline bool operator<= (char ch, const CMyStringA& str);
    friend inline bool operator<= (const char* psz, const CMyStringA& str);

private:
    char *m_pBuff;  //������
    int m_nSize; //�ռ�
    int m_nLength; //����
    int *m_pnRefCnt; // ���ü���

    static CMyStringA m_strEmpty;

    void Alloc(int nSize);
    void AllocCopy(const char *pszBuff, int nSize = 0);
    void CopyBeforeWrite(int nSize = 0);

    inline int  GetRefCnt() const; //��ȡ���ü���
    inline void AddRefCnt(); //�������ü���
    inline void Release(); //�ͷſռ�
};

//��������С
inline int CMyStringA::GetSize() const
{
    return m_nSize;
}

//�ַ�������
inline int CMyStringA::GetLength() const
{
    return m_nLength;
}

//�ַ�������
inline int CMyStringA::GetLength(const char *pszSrc)
{
    return pszSrc != NULL ? strlen(pszSrc) : 0;
}

//�Ƿ�Ϊ��
inline bool CMyStringA::IsEmpty() const
{
    return m_nLength == 0;
}

//��ȡ�ַ���
inline const char *CMyStringA::GetBuffer() const
{
    return m_pBuff;
}

//��ȡ�ַ���
inline char *CMyStringA::GetBufferSetLength(int nSize)
{
    CopyBeforeWrite(nSize);
    return m_pBuff;
}

//���ó���
inline void CMyStringA::ReleaseBuffer()
{
    m_nLength = GetLength(m_pBuff);
}

//����ַ���
inline CMyStringA& CMyStringA::Empty()
{
    *this = CMyStringA();

    return *this;
}

//��ȡ���ü���
inline int CMyStringA::GetRefCnt() const
{
    return m_pnRefCnt != NULL ? *m_pnRefCnt : 0;
}

//�������ü���
inline void CMyStringA::AddRefCnt()
{
    if (m_pnRefCnt == NULL)
    {
        m_pnRefCnt = new int(0);
    }

    ++(*m_pnRefCnt);
}

//�ͷſռ�
inline void CMyStringA::Release()
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

inline CMyStringA::operator char* ()
{
    return m_pBuff;
}

inline CMyStringA::operator const char* () const
{
    return m_pBuff;
}

inline char& CMyStringA::operator[](int nIndex)
{
    return m_pBuff[nIndex];
}

inline const CMyStringA& CMyStringA::operator= (char ch)
{
    Release();
    AllocCopy(&ch, 2);

    return *this;
}

inline const CMyStringA& CMyStringA::operator= (const char* psz)
{
    Release();
    AllocCopy(psz);

    return *this;
}

inline const CMyStringA& CMyStringA::operator= (const wchar_t* psz)
{
    Release();
    CMyStringA obj = FromWideChar(psz);
    m_nSize = obj.m_nSize;
    m_nLength = obj.m_nLength;
    m_pBuff = obj.m_pBuff;
    m_pnRefCnt = obj.m_pnRefCnt;
    AddRefCnt();

    return *this;
}

inline const CMyStringA& CMyStringA::operator= (const CMyStringA& obj)
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

inline const CMyStringA& CMyStringA::operator+= (char ch)
{
    return Append(ch);
}

inline const CMyStringA& CMyStringA::operator+= (const char* psz)
{
    return Append(psz);
}

inline const CMyStringA& CMyStringA::operator+= (const wchar_t* psz)
{
    return Append(psz);
}

inline const CMyStringA& CMyStringA::operator+= (const CMyStringA& str)
{
    return Append(str);
}

inline CMyStringA CMyStringA::operator+ (char ch) const
{
    return CMyStringA(*this).Append(ch);
}

inline CMyStringA CMyStringA::operator+ (const char* psz) const
{
    return CMyStringA(*this).Append(psz);
}

inline CMyStringA CMyStringA::operator+ (const wchar_t* psz) const
{
    return CMyStringA(*this).Append(psz);
}

inline CMyStringA CMyStringA::operator+ (const CMyStringA& str) const
{
    return CMyStringA(*this).Append(str);
}

inline bool CMyStringA::operator== (char ch) const
{
    return Compare(ch) == 0;
}

inline bool CMyStringA::operator== (const char* psz) const
{
    return Compare(psz) == 0;
}

inline bool CMyStringA::operator== (const CMyStringA& str) const
{
    return Compare(str) == 0;
}

inline bool CMyStringA::operator!= (char ch) const
{
    return Compare(ch) != 0;
}

inline bool CMyStringA::operator!= (const char* psz) const
{
    return Compare(psz) != 0;
}

inline bool CMyStringA::operator!= (const CMyStringA& str) const
{
    return Compare(str) != 0;
}

inline bool CMyStringA::operator> (char ch) const
{
    return Compare(ch) > 0;
}

inline bool CMyStringA::operator> (const char* psz) const
{
    return Compare(psz) > 0;
}

inline bool CMyStringA::operator> (const CMyStringA& str) const
{
    return Compare(str) > 0;
}

inline bool CMyStringA::operator>= (char ch) const
{
    return Compare(ch) >= 0;
}

inline bool CMyStringA::operator>= (const CMyStringA& str) const
{
    return Compare(str) >= 0;
}

inline bool CMyStringA::operator>= (const char* psz) const
{
    return Compare(psz) >= 0;
}

inline bool CMyStringA::operator< (char ch) const
{
    return Compare(ch) < 0;
}

inline bool CMyStringA::operator< (const CMyStringA& str) const
{
    return Compare(str) < 0;
}

inline bool CMyStringA::operator< (const char* psz) const
{
    return Compare(psz) < 0;
}

inline bool CMyStringA::operator<= (char ch) const
{
    return Compare(ch) <= 0;
}

inline bool CMyStringA::operator<= (const CMyStringA& str) const
{
    return Compare(str) <= 0;
}

inline bool CMyStringA::operator<= (const char* psz) const
{
    return Compare(psz) <= 0;
}

inline CMyStringA operator+ (char ch, const CMyStringA& str)
{
    return CMyStringA(ch) + str;
}

inline CMyStringA operator+ (const char* psz, const CMyStringA& str)
{
    return CMyStringA(psz) + str;
}

inline CMyStringA operator+ (const wchar_t* psz, const CMyStringA& str)
{
    return CMyStringA(psz) + str;
}

inline bool operator== (char ch, const CMyStringA& str)
{
    return str == ch;
}

inline bool operator== (const char* psz, const CMyStringA& str)
{
    return str == psz;
}

inline bool operator!= (char ch, const CMyStringA& str)
{
    return str != ch;
}

inline bool operator!= (const char* psz, const CMyStringA& str)
{
    return str != psz;
}

inline bool operator> (char ch, const CMyStringA& str)
{
    return str < ch;
}

inline bool operator>(const char* psz, const CMyStringA& str)
{
    return str < psz;
}

inline bool operator>= (char ch, const CMyStringA& str)
{
    return str <= ch;
}

inline bool operator>= (const char* psz, const CMyStringA& str)
{
    return str <= psz;
}

inline bool operator< (char ch, const CMyStringA& str)
{
    return str > ch;
}

inline bool operator< (const char* psz, const CMyStringA& str)
{
    return str > psz;
}

inline bool operator<= (char ch, const CMyStringA& str)
{
    return str >= ch;
}

inline bool operator<= (const char* psz, const CMyStringA& str)
{
    return str >= psz;
}

#pragma warning(pop)

#endif // !defined(AFX_STRINGA_H__02F3F393_12C6_4024_8829_7B6D7A1FB1F4__INCLUDED_)