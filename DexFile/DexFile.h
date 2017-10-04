#pragma once

#include "../Common.h"
#include "../Util/FileEdit.h"
#include "../include/DexFile/DexFile.h"

typedef CFileEditPtr<DexHeader>    CDexHeaderPtr;
typedef CFileEditAry<DexLink>      CDexLinkAry;
typedef CFileEditPtr<DexMapList>   CDexMapListPtr;
typedef CFileEditAry<DexStringId>  CDexStringIdAry;
typedef CFileEditAry<DexTypeId>    CDexTypeIdAry;
typedef CFileEditAry<DexProtoId>   CDexProtoIdAry;
typedef CFileEditAry<DexFieldId>   CDexFieldIdAry;
typedef CFileEditAry<DexMethodId>  CDexMethodIdAry;
typedef CFileEditAry<DexClassDef>  CDexClassDefAry;
typedef CFileEditAry<char>         CDexDataAry;

class CDexFile : public CFileEdit
{
public:
    CDexFile();
    virtual ~CDexFile();
    
public:
    bool ParseFile(); //��ȡ�ļ����ݲ������ļ�
    bool ParseHeader(); //����Dexͷ
    bool RepairFile(); //�޸��ļ�
    bool ConfuseFile(CDexFile& file); //����Dex�ļ�

    CMyStringA GetStringData(DexStringId* pStringId);
    int SetSrtingData(size_t nStringDataOff, CMyStringA& strData);

    DexTypeId *GetDexTypeIds();

private:
    size_t InitOffset(CDexFile& file);

public:
    CDexHeaderPtr   m_pHeader;
    CDexLinkAry     m_aryLink;
    CDexMapListPtr  m_pMapList;
    CDexStringIdAry m_aryStringId;
    CDexTypeIdAry   m_aryTypeId;
    CDexProtoIdAry  m_aryProtoId;
    CDexFieldIdAry  m_aryFieldId;
    CDexMethodIdAry m_aryMethodId;
    CDexClassDefAry m_aryClassDef;
    CDexDataAry     m_aryData;
};