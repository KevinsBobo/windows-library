#pragma once

#include <io.h>
#include <stdio.h>
#include <assert.h>
#include "../StringT.h"

#if defined(WIN32)
#define access _access
#endif

/************************************************************************/
/*                             �ļ�������                               */
/************************************************************************/
class CFileUtil
{
public:
    enum
    {
        FILE_READ = 1, //����Ĭ�ϣ�
        FILE_WRITE = 2, //д
        FILE_EXIST = 4, //�ļ��������
        FILE_CREATE = 8, //�ļ��������򴴽�
        FILE_CREATE_ALWAYS = 16, //���Ǵ����ļ�
    };

public:
    CFileUtil(); //���캯��
    CFileUtil(const char *pszFileName); //���캯��
    CFileUtil(const wchar_t *pszFileName); //���캯��
    virtual ~CFileUtil(); //��������

public:
    void SetFileName(CMyStringA strFileName); //�����ļ���
    CMyStringA GetFileName() const; //��ȡ�ļ���

    bool IsExist() const;
    bool IsOpen() const; //�Ƿ��

    bool Create(); //�����ļ�
    bool Clear(); //����ļ�

    bool Open(int nMode = FILE_READ | FILE_EXIST); //���ļ�
    void Close(); //�ر��ļ�

    size_t Write(const void *pBuff, size_t nSize); //д�ļ�
    size_t Write(int nOffset, const void *pBuff, size_t nSize); //д�ļ�
    size_t Read(void *pBuff, size_t nSize); //���ļ�
    size_t Read(int nOffset, void *pBuff, size_t nSize); //���ļ�

    bool Seek(int nOffset); //�ƶ��ļ�ָ�뵽ָ����
    void SeekToBegin(); //�ƶ��ļ�ָ�����ļ���ͷ
    size_t SeekToEnd(); //�ƶ��ļ�ָ�����ļ�ĩ�������ļ�����

    void Flush(); //ˢ���ļ�������

private:
    CMyStringA m_strFileName; //�ļ���
    FILE*      m_fpFile; //�ļ�ָ��
};

//�����ļ���
inline void CFileUtil::SetFileName(CMyStringA strFileName)
{
    Close();
    m_strFileName = strFileName;
}

//��ȡ�ļ���
inline CMyStringA CFileUtil::GetFileName() const
{
    return m_strFileName;
}

inline bool CFileUtil::IsExist() const
{
    return access(m_strFileName, 00) == 0;
}

//�Ƿ��
inline bool CFileUtil::IsOpen() const
{
    return m_fpFile != NULL;
}

//�ƶ��ļ�ָ�뵽ָ����
inline bool CFileUtil::Seek(int nOffset)
{
    assert(IsOpen());

    return fseek(m_fpFile, nOffset, SEEK_SET) == 0;
}

//�ƶ��ļ�ָ�����ļ���ͷ
inline void CFileUtil::SeekToBegin()
{
    assert(IsOpen());

    fseek(m_fpFile, 0, SEEK_SET);
}

//�ƶ��ļ�ָ�����ļ�ĩ�������ļ�����
inline size_t CFileUtil::SeekToEnd()
{
    assert(IsOpen());

    fseek(m_fpFile, 0, SEEK_END);

    return ftell(m_fpFile);
}

//ˢ���ļ�������
inline void CFileUtil::Flush()
{
    assert(IsOpen());

    fflush(m_fpFile);
}
