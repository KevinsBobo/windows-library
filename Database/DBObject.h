#pragma once

#include "../Common.h"
#include "DBUtil.h"

/*
//�÷���
//.h
class CStudent : public CDBObject
{
    DECLARE_DBOBJECT(CStudent)
public:
    CStudent() { }
    virtual ~CStudent() { }
public:
    _variant_t m_strId;
    _variant_t m_strName;
};

.cpp
BEGIN_FIELD_MAP(CStudent, "tb_student")
    DECLARE_FIELD_STRING_KEY(m_strId, "stu_id", 20)
    DECLARE_FIELD_STRING(m_strName, "stu_name", 20)
END_FIELD_MAP()

//��������һ����¼
CStudent student;
student.m_strId = "1";
student.m_strName = "2";
student.Insert(CDBUtil());
*/

//����һ�����ݿ����
#define DECLARE_DBOBJECT(class_name) \
protected: \
    protected: \
    friend class CDBObject; \
    static class_name* CreateObject(); \
    static CDBTable& _GetTableInfo(); \
    virtual CDBTable& GetTableInfo();

//�ֶ�ӳ���ʼ
#define BEGIN_FIELD_MAP(class_name, table_name) \
    class_name* class_name::CreateObject() { return new class_name; } \
    CDBTable& class_name::GetTableInfo() { return _GetTableInfo(); } \
    CDBTable& class_name::_GetTableInfo() { \
        static class_name *pNull = NULL; \
        static TCHAR *pszTable = TEXT(table_name); \
        static CDBField dbFields[] = {

//�ֶ�ӳ������
#define END_FIELD_MAP() \
        }; \
        static CDBTable dbTable = { pszTable, dbFields, \
            sizeof(dbFields) / sizeof(dbFields[0]), \
            (CDBObject*(*)())CreateObject \
        }; \
        return dbTable; \
    }


//�����ֶ�
#define DECLARE_FIELD(type, member, field, size, key) { type, (size_t)&pNull->member, TEXT(field), size, key },
#define DECLARE_FIELD_INT(member, field) { adInteger, (size_t)&pNull->member, TEXT(field), -1, false },
#define DECLARE_FIELD_INT_KEY(member, field) { adInteger, (size_t)&pNull->member, TEXT(field), -1, true },
#define DECLARE_FIELD_STRING(member, field, size) { adVarChar, (size_t)&pNull->member, TEXT(field), size, false },
#define DECLARE_FIELD_STRING_KEY(member, field, size) { adVarChar, (size_t)&pNull->member, TEXT(field), size, true },

//��ȡָ��ָ����Ա
#define GET_MEMBER(ptr, field) *(_variant_t*)((char*)ptr + field.m_nMember)

class CDBObject;

//�ֶ���Ϣ
class CDBField
{
public:
    DataTypeEnum m_Type;         //�ֶ�����
    size_t       m_nMember;      //��Աƫ��
    TCHAR*       m_pszField;     //�ֶ�����
    long         m_nMaxLen;      //����
    bool         m_isPrimaryKey; //�Ƿ�����
};

//����Ϣ
class CDBTable
{
public:
    TCHAR*    m_pszTable;    //����
    CDBField* m_pAryFields;  //�ֶ�
    int       m_nFieldCount; //�ֶ�����
    CDBObject*(*m_pfnCreateObject)(); //��������ĺ���ָ��
};

typedef CSmartPtr<CDBObject> CDBObjectPtr;
typedef CMyList<CDBObjectPtr> CDBObjectList;

class CDBObject : public CRefCnt
{
public:
    CDBObject();
    virtual ~CDBObject();

public:
    inline bool FindByKey(CDBUtil& dbUtil); //�������������
    inline bool Find(CDBUtil& dbUtil, CDBObjectList& lstObjects); //���ݶ���ģ������

    inline bool Select(CDBUtil& dbUtil, const TCHAR* pszWhere, const TCHAR* pszOrder = NULL); //����where�����Ҷ���
    inline bool Select(CDBUtil& dbUtil, CDBObjectList& lstObjects, const TCHAR* pszWhere, const TCHAR* pszOrder = NULL); //����where����������
    inline bool Select(CDBUtil& dbUtil, bool bMacthAll = false); //���ݶ�����Ҷ���ƥ�������ֶ�/ֻƥ��ǿ��ֶ�
    inline bool Select(CDBUtil& dbUtil, CDBObjectList& lstObjects, bool bMacthAll = false);

    inline int Update(CDBUtil& dbUtil, CDBObject& src, bool bUpdateAll = false); //���ݶ���������������
    inline int Update(CDBUtil& dbUtil, const TCHAR* pszWhere, bool bUpdateAll = false); //����where����������

    inline bool Insert(CDBUtil& dbUtil); //��Ӷ���
    inline int Delete(CDBUtil& dbUtil, bool bMacthAll = false); //ɾ������

    template <typename T>
    static bool Select(CDBUtil& dbUtil, CDBObjectList& lstObjects, const TCHAR* pszWhere = NULL, const TCHAR* pszOrder = NULL);
    template <typename T>
    static int Delete(CDBUtil& dbUtil, const TCHAR* pszWhere = NULL);
    template <typename T>
    static bool EqualKey(T& lhs, T& rhs);

protected:
    bool FindByKey(CDBUtil& dbUtil, CDBTable& dbTable); //�������������
    bool Find(CDBUtil& dbUtil, CDBTable& dbTable, CDBObjectList& lstObjects); //���ݶ���ģ������
    bool Select(CDBUtil& dbUtil, CDBTable& dbTable, const TCHAR* pszWhere, const TCHAR* pszOrder = NULL);
    bool Select(CDBUtil& dbUtil, CDBTable& dbTable, CDBObjectList& lstObjects, const TCHAR* pszWhere, const TCHAR* pszOrder = NULL);
    bool Select(CDBUtil& dbUtil, CDBTable& dbTable, bool bMacthAll = false);
    bool Select(CDBUtil& dbUtil, CDBTable& dbTable, CDBObjectList& lstObjects, bool bMacthAll = false);
    int Update(CDBUtil& dbUtil, CDBTable& dbTable, CDBObject& src, bool bUpdateAll = false); //����������������
    int Update(CDBUtil& dbUtil, CDBTable& dbTable, const TCHAR* pszWhere, bool bUpdateAll = false);
    bool Insert(CDBUtil& dbUtil, CDBTable& dbTable);
    int Delete(CDBUtil& dbUtil, CDBTable& dbTable, bool bMacthAll = false);

    static CMyString GetSelectSql(CDBTable& dbTable);
    static CMyString GetDeleteSql(CDBTable& dbTable);
    CMyString GetUpdateSql(CDBUtil& dbUtil, CDBTable& dbTable, bool bUpdateAll);
    CMyString GetInsertSql(CDBUtil& dbUtil, CDBTable& dbTable);
    CMyString GetWhereSql(CDBUtil& dbUtil, CDBTable& dbTable);
    CMyString GetWhereSql(CDBUtil& dbUtil, CDBTable& dbTable, bool bMacthAll, bool bFuzzy);
    void FromFields(FieldsPtr pFields, CDBTable& dbTable);

    //���ú꣨DECLARE_DBOBJECT�����ɣ�����������ʵ��
    virtual CDBTable& GetTableInfo() = 0;
};


inline bool CDBObject::FindByKey(CDBUtil& dbUtil) //�������������
{
    return FindByKey(dbUtil, GetTableInfo());
}


inline bool CDBObject::Find(CDBUtil& dbUtil, CDBObjectList& lstObjects) //���ݶ���ģ������
{
    return Find(dbUtil, GetTableInfo(), lstObjects);
}


inline bool CDBObject::Select(CDBUtil& dbUtil, const TCHAR* pszWhere, const TCHAR* pszOrder)
{
    return Select(dbUtil, GetTableInfo(), pszWhere, pszOrder);
}


inline bool CDBObject::Select(CDBUtil& dbUtil, CDBObjectList& lstObjects, const TCHAR* pszWhere, const TCHAR* pszOrder)
{
    return Select(dbUtil, GetTableInfo(), lstObjects, pszWhere, pszOrder);
}


inline bool CDBObject::Select(CDBUtil& dbUtil, bool bMacthAll)
{
    return Select(dbUtil, GetTableInfo(), bMacthAll);
}


inline bool CDBObject::Select(CDBUtil& dbUtil, CDBObjectList& lstObjects, bool bMacthAll)
{
    return Select(dbUtil, GetTableInfo(), lstObjects, bMacthAll);
}


inline int CDBObject::Update(CDBUtil& dbUtil, CDBObject& src, bool bUpdateAll) //����������������
{
    return Update(dbUtil, GetTableInfo(), src, bUpdateAll);
}


inline int CDBObject::Update(CDBUtil& dbUtil, const TCHAR* pszWhere, bool bUpdateAll)
{
    return Update(dbUtil, GetTableInfo(), pszWhere, bUpdateAll);
}


inline bool CDBObject::Insert(CDBUtil& dbUtil)
{
    return Insert(dbUtil, GetTableInfo());
}


inline int CDBObject::Delete(CDBUtil& dbUtil, bool bMacthAll)
{
    return Delete(dbUtil, GetTableInfo(), bMacthAll);
}


template <typename T>
bool CDBObject::Select(CDBUtil& dbUtil, CDBObjectList& lstObjects, const TCHAR* pszWhere, const TCHAR* pszOrder)
{
    if (!dbUtil.IsOpen() && !dbUtil.Open())
    {
        return false;
    }

    CDBTable& dbTable = T::_GetTableInfo();

    CMyString strSql = GetSelectSql(dbTable);

    if (pszWhere != NULL && pszWhere[0] != TEXT('\0'))
    {
        strSql.Append(TEXT(" WHERE "));
        strSql.Append(pszWhere);
    }

    if (pszOrder != NULL && pszOrder[0] != TEXT('\0'))
    {
        strSql.Append(TEXT(" ORDER BY "));
        strSql.Append(pszOrder);
    }

    _RecordsetPtr pRecordSet = dbUtil.ExecuteRecord(strSql.GetBuffer());

    while (!pRecordSet->ADOEOF)
    {
        CDBObject *pObject = new T();
        pObject->FromFields(pRecordSet->Fields, dbTable);
        lstObjects.AddTail(pObject);
        pRecordSet->MoveNext();
    }

    return true;
}


template <typename T>
int CDBObject::Delete(CDBUtil& dbUtil, const TCHAR* pszWhere)
{
    if (!dbUtil.IsOpen() && !dbUtil.Open())
    {
        return false;
    }

    CDBTable dbTable = T::_GetTableInfo();

    CMyString strSql = GetDeleteSql(dbTable);

    if (pszWhere != NULL && pszWhere[0] != TEXT('\0'))
    {
        strSql.Append(TEXT(" WHERE "));
        strSql.Append(pszWhere);
    }

    return dbUtil.ExecuteNonQuery(strSql.GetBuffer());
}


template <typename T>
static bool CDBObject::EqualKey(T& lhs, T& rhs)
{
    CDBTable& dbTable = T::_GetTableInfo();

    for (int i = 0; i < dbTable.m_nFieldCount; i++)
    {
        if (dbTable.m_pAryFields[i].m_isPrimaryKey)
        {
            if (GET_MEMBER(&lhs, dbTable.m_pAryFields[i]) !=
                GET_MEMBER(&rhs, dbTable.m_pAryFields[i]))
            {
                return false;
            }
        }
    }

    return true;
}






// class CStudent : public CDBObject
// {
// protected: \
//     static CStudent* CreateObject() { return new CStudent; } \
//     virtual CDBTable* GetTableInfo(CDBTable& dbTable);
// public:
//     CStudent() { }
//     virtual ~CStudent() { }
// public:
//     _variant_t m_strId;
//     _variant_t m_strName;
// };
// 
// 
// CDBTable* CStudent::GetTableInfo() {
// 
//     static TCHAR *pszTable = TEXT("tb_student");
// 
//     static CDBField dbFields[] = {
//             { adInteger, (size_t)&this->m_strId - (size_t)this, TEXT("stu_id"), 20, false },
//     };
// 
//     static CDBTable dbTable = {
//         pszTable,
//         dbFields,
//         sizeof(dbFields) / sizeof(dbFields[0]),
//         (CDBObject*(*)())CreateObject
//     };
// 
//     return &dbTable;
// }
// 
// 
