#include "FileUtil.h"

#pragma warning(disable:4996)

//���캯��
CFileUtil::CFileUtil()
    : m_fpFile(NULL)
{

}

//���캯��
CFileUtil::CFileUtil(const char *pszName)
    : m_fpFile(NULL)
    , m_strFileName(pszName)
{
    
}

//���캯��
CFileUtil::CFileUtil(const wchar_t *pszName)
    : m_fpFile(NULL)
    , m_strFileName(pszName)
{
    
}

//��������
CFileUtil::~CFileUtil()
{
    Close();
}

//�����ļ�
bool CFileUtil::Create()
{
    if (IsExist())
    {
        return true;
    }

    FILE *fpCreate = fopen(m_strFileName, "a");

    if (fpCreate == NULL)
    {
        return false;
    }

    fclose(fpCreate);

    return true;
}

//����ļ�
bool CFileUtil::Clear()
{
    Close();

    FILE *fpCreate = fopen(m_strFileName, "w");

    if (fpCreate == NULL)
    {
        return false;
    }

    fclose(fpCreate);

    return true;
}


//���ļ�
bool CFileUtil::Open(int nMode)
{
    assert(!IsOpen());

    int nAccess = (nMode & FILE_WRITE) != 0 ? FILE_WRITE : FILE_READ;
    int nCreate = (nMode & FILE_CREATE_ALWAYS) != 0 ? FILE_CREATE_ALWAYS :
                  (nMode & FILE_CREATE) != 0 ? FILE_CREATE : FILE_EXIST;

    char *pszMode = NULL;

    switch (nAccess)
    {
    case FILE_READ: //��
        switch (nCreate)
        {
        case FILE_EXIST: //�ļ��������
            pszMode = "rb";
            break;
        }
        break;
    case FILE_WRITE: //д
        switch (nCreate)
        {
        case FILE_EXIST: //�ļ��������
            pszMode = "rb+";
            break;
        case FILE_CREATE: //�ļ��������򴴽�
            Create();
            pszMode = "rb+";
            break;
        case FILE_CREATE_ALWAYS: //�ļ����Ǵ���
            pszMode = "wb+";
            break;
        }
        break;
    }

    assert(pszMode != NULL);

    m_fpFile = fopen(m_strFileName, pszMode);

    return IsOpen();
}

//�ر��ļ�
void CFileUtil::Close()
{
    if (IsOpen())
    {
        fclose(m_fpFile);
        m_fpFile = NULL;
    }
}

//д�ļ�
size_t CFileUtil::Write(const void *pBuff, size_t nSize)
{
    assert(IsOpen());

    return fwrite(pBuff, 1, nSize, m_fpFile);
}

//д�ļ�
size_t CFileUtil::Write(int nOffset, const void *pBuff, size_t nSize)
{
    assert(IsOpen());

    if (fseek(m_fpFile, nOffset, SEEK_SET) != 0)
    {
        return false;
    }

    return fwrite(pBuff, 1, nSize, m_fpFile);
}

//���ļ�
size_t CFileUtil::Read(void *pBuff, size_t nSize)
{
    assert(IsOpen());

    return fread(pBuff, 1, nSize, m_fpFile);
}

//���ļ�
size_t CFileUtil::Read(int nOffset, void *pBuff, size_t nSize)
{
    assert(IsOpen());

    if (fseek(m_fpFile, nOffset, SEEK_SET) != 0)
    {
        return 0;
    }

    return fread(pBuff, 1, nSize, m_fpFile);
}