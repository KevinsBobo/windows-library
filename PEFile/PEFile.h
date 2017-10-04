#pragma once

#include "PEDef.h"

/************************************************************************/
/*                               PE�ļ�                                 */
/************************************************************************/

class CPEFile : public CFileEdit
{
public:
    CPEFile();
    CPEFile(LPCSTR pszFileName);
    CPEFile(LPCWSTR pszFileName);
    virtual ~CPEFile();

public:
    HMODULE Load(HMODULE hModule = NULL, bool bCallEntry = true); //ָ����ַ����pe�ļ�

    bool ParseFile(); //��ȡ�ļ����ݲ�����peͷ
    bool ParseHeader(); //����peͷ

    bool AppendSection(); //��ӽ�
    bool DeleteSection(int nIndex); //ɾ����

    CImageExportDirectoryPtr ParseExportTable(); //����������
    CDwordAry GetExportFunctions(PIMAGE_EXPORT_DIRECTORY pExport); //����������ַ��RVA��
    CDwordAry GetExportNames(PIMAGE_EXPORT_DIRECTORY pExport); //���������±��뵼�������ͬ��
    CWordAry GetExportNameOrdinals(PIMAGE_EXPORT_DIRECTORY pExport); //�������

    CImageImportDescriptorAry ParseImportTable(); //���������
    CImageThunkDataAry GetThunkAry(size_t nFirstThunk); //��ȡ�����Thunk����

    CImageBaseRelocationPtr ParseBaseRelocation(); //�����ض�λ��
    CRelocTypeOffsetAry GetTypeOffsetAry(PIMAGE_BASE_RELOCATION pReloc); //��ȡ�ض�λ��ƫ������

    CImageTlsDirectoryPtr ParseTlsDirectory(); //����Tls��

    CImageResourceDirectoryPtr ParseResourceDirectory(); //������ԴĿ¼
    size_t GetResourceOffset(size_t nOffset); //��ȡ��Դ�ļ�ƫ��(����Ϊƫ��)
    void *GetResourceData(PIMAGE_RESOURCE_DATA_ENTRY pEntry); //��ȡ��Դ����

    size_t OffsetToRva(size_t nOffset); //��ȡ��������ַ
    size_t RvaToOffset(size_t nRva); //��ȡ�ļ�ƫ��

    void *GetBufferByRva(size_t nRva, size_t nLen = 0); //��ȡ�ɶ���������nLenΪ0��ָ������
    void *SetBufferByRva(size_t nRva, size_t nLen); //��ȡ��д������

public:
    CImageDosHeaderPtr m_pDosHeader;
    CImageNtHeadersPtr m_pNtHeaders;
    CImageDataDirectoryAry m_aryDataDirectory;
    CImageSectionHeaderAry m_arySectionHeader;
};

#include "PEImp.h"
