#pragma once

#pragma warning ( push )
//#pragma warning ( disable : 4146 )
#pragma warning ( disable : 4290 )
#import "msado15.dll" rename("EOF", "ADOEOF") no_namespace 
#include <windows.h>

const LPTSTR CONFIG_FILE = TEXT("config.ini"); //ini�ļ���
const LPTSTR CONFIG_APP = TEXT("ADO"); //����
const LPTSTR CONFIG_KEY_CONNECTION = TEXT("Connection"); //�����ַ���
const LPTSTR CONFIG_KEY_USERID = TEXT("UserID"); //�û���
const LPTSTR CONFIG_KEY_PASSWORD = TEXT("Password"); //����

/************************************************************************/
/*                            ���ݿ⹤����                              */
/************************************************************************/
class CDBUtil
{
    //ʹ��ǰ��Ҫ��ʼ��CoInitialize(NULL);
    //ʹ�������CoUninitialize();
public:
    CDBUtil(); //Ĭ�ϴ�Ӧ�ó�������Ŀ¼��ȡ�����ļ��������ַ���
    CDBUtil(_bstr_t strConnection, _bstr_t strUserID = "", _bstr_t strPassword = "");
    ~CDBUtil();

public:
    //������
    bool Open(long lOptions = adConnectUnspecified) throw(_com_error);
    //�ر�����
    void Close();

    //�Ƿ��
    inline bool IsOpen() throw(_com_error);

    //���һ������
    inline void AddParamter(const _variant_t& vtValue = vtMissing, DataTypeEnum Type = adInteger,
        long lSize = -1, ParameterDirectionEnum Direction = adParamInput, _bstr_t strName = "") throw(_com_error);
    //�Ƴ������б�
    inline void RefreshParamter() throw(_com_error);

    //ִ��sql����Ӱ������
    inline int ExecuteNonQuery(_bstr_t strSql, _variant_t *pParams = NULL, long lOptions = adCmdText) throw(_com_error);
    //ִ��sql���ص�һ�е�һ��
    inline _variant_t ExecuteScalar(_bstr_t strSql, _variant_t *pParams = NULL, long lOptions = adCmdText) throw(_com_error);
    //ִ��sql���ؼ�¼��
    inline _RecordsetPtr ExecuteRecord(_bstr_t strSql, _variant_t *pParams = NULL, long lOptions = adCmdText) throw(_com_error);

protected:
    _bstr_t m_strConnection;
    _bstr_t m_strUserID;
    _bstr_t m_strPassword;
    _CommandPtr m_pCommand;
    _ConnectionPtr m_pConnection;
};


inline bool CDBUtil::IsOpen() throw(_com_error)
{
    return m_pConnection != NULL && m_pConnection->GetState() != adStateClosed;
}


inline void CDBUtil::AddParamter(const _variant_t& vtValue, DataTypeEnum Type, long lSize, ParameterDirectionEnum Direction, _bstr_t strName) throw(_com_error)
{
    m_pCommand->Parameters->Append(m_pCommand->CreateParameter(strName, Type, Direction, lSize, vtValue));
}


inline void CDBUtil::RefreshParamter() throw(_com_error)
{
    while (m_pCommand->Parameters->GetCount() > 0)
        m_pCommand->Parameters->Delete(m_pCommand->Parameters->GetCount() - 1);
}


inline int CDBUtil::ExecuteNonQuery(_bstr_t strSql, _variant_t *pParams, long lOptions) throw(_com_error)
{
    _variant_t t;
    m_pCommand->CommandText = strSql;
    m_pCommand->Execute(&t, pParams, lOptions);
    RefreshParamter();
    return t;
}


inline _variant_t CDBUtil::ExecuteScalar(_bstr_t strSql, _variant_t *pParams, long lOptions) throw(_com_error)
{
    m_pCommand->CommandText = strSql;
    _RecordsetPtr rs = m_pCommand->Execute(NULL, pParams, lOptions);
    RefreshParamter();
    return !rs->ADOEOF ? rs->Fields->Item[(long)0]->Value : _variant_t();
}


inline _RecordsetPtr CDBUtil::ExecuteRecord(_bstr_t strSql, _variant_t *pParams, long lOptions) throw(_com_error)
{
    m_pCommand->CommandText = strSql;
    _RecordsetPtr rs = m_pCommand->Execute(NULL, pParams, lOptions);
    RefreshParamter();
    return rs;
}

#pragma warning ( pop )