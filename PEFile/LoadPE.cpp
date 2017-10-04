#include "PEFile.h"
#include "LoadPE.h"

HMODULE LoadDLL(CPEFile *pFile);

/************************************************************************/
/*                      ����PE�ļ���ͬLoadLibrary                       */
/************************************************************************/

HMODULE LoadDLL(LPCTSTR lpFileName)
{
    CPEFile file(lpFileName);

    //�򿪲���ȡpe�ļ�����
    if (file.ParseFile())
    {
        return file.Load();
    }

    return NULL;
}


/************************************************************************/
/*             ��ȡ������ַ��û�о��Ե�ַ����ͬGetProcAddress           */
/************************************************************************/
extern "C" FARPROC GetProcAddr(
    HMODULE hModule,    // handle to DLL module
    LPCSTR lpProcName   // function name
    )
{
    IMAGE_DOS_HEADER *pDosHeader = (IMAGE_DOS_HEADER*)hModule;
    IMAGE_NT_HEADERS *pNtHeader = (IMAGE_NT_HEADERS*)((PBYTE)hModule + pDosHeader->e_lfanew);
    IMAGE_DATA_DIRECTORY *pDataDir = &pNtHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT];
    IMAGE_EXPORT_DIRECTORY *pExport = (IMAGE_EXPORT_DIRECTORY*)((PBYTE)hModule + pDataDir->VirtualAddress);
    
    DWORD* pFuctions = (DWORD*)((PBYTE)hModule + pExport->AddressOfFunctions);
    DWORD* pNames = (DWORD*)((PBYTE)hModule + pExport->AddressOfNames);
    WORD* pOrdinals = (WORD*)((PBYTE)hModule + pExport->AddressOfNameOrdinals);

    DWORD dwOrdinal = -1;

    //����Ǻ�����
    if (lpProcName > (LPCSTR)0xFFFF)
    {
        DWORD i = 0, j = 0;

        for (; i < pExport->NumberOfNames; i++)
        {
            LPSTR pszName = (LPSTR)hModule + pNames[i];

            //strcmp
            for (j = 0; lpProcName[j] != '\0' && pszName[j] != '\0'; j++)
            {
                if (lpProcName[j] != pszName[j])
                {
                    break;
                }
            }

            //����ƥ����
            if (lpProcName[j] == '\0' && pszName[j] == '\0')
            {
                dwOrdinal = pOrdinals[i];
                break;
            }
        }
    }
    else
    {
        dwOrdinal = (DWORD)lpProcName - pExport->Base;
    }

    //�����Ŵ�������
    if (dwOrdinal >= pExport->NumberOfFunctions)
    {
        return NULL;
    }

    DWORD dwFuction = pFuctions[dwOrdinal];

    //Ϊ0�Ǿ�˵��������
    if (dwFuction == 0)
    {
        return NULL;
    }

    PBYTE pFuction = (PBYTE)hModule + dwFuction;

    //�������ת�������ڣ�ֱ�ӷ��غ�����ַ���������ת����
    if (pFuction < (PBYTE)pExport || pFuction >= (PBYTE)pExport + pDataDir->Size)
    {
        return (FARPROC)pFuction;
    }

    PLDR_DATA_TABLE_ENTRY pLdtEntryHead = NULL;

#ifndef _WIN64
    //��ȡģ������
    __asm mov eax, fs:[0x18]; //��ȡ_TEB
    __asm mov eax, [eax + 0x30]; //��ȡ_PEB
    __asm mov eax, [eax + 0xC]; //��ȡ_PEB_LDR_DATA
    __asm mov eax, [eax + 0xC]; //��ȡInLoadOrderModuleList������ģ������
    __asm mov pLdtEntryHead, eax;
#else
    // mov rax, qword ptr gs : [30] //��ȡ_TEB
    // mov rax, qword ptr ds : [rax + 60] //��ȡ_PEB
    // mov rax, qword ptr ds : [rax + 18] //��ȡ_PEB_LDR_DATA
    // mov rax, qword ptr ds : [rax + 10] //InLoadOrderModuleList
    PBYTE pTeb = (PBYTE)__readgsqword(0x30);
    PBYTE pPeb = *(PBYTE*)(pTeb + 0x60);
    PBYTE pLdr = *(PBYTE*)(pPeb + 0x18);
    pLdtEntryHead = *(PLDR_DATA_TABLE_ENTRY*)(pLdr + 0x10);
#endif

    PLDR_DATA_TABLE_ENTRY pLdtEntry = pLdtEntryHead;

    do
    {
        if (pLdtEntry->BaseDllName.Length >= 24) //wcslen(L"kernel32.dll");
        {
            LPWSTR pszFileName = pLdtEntry->BaseDllName.Buffer;

            //�ҵ�kernel32.dll
            if ((pszFileName[0] == L'K' || pszFileName[0] == L'k') &&
                //(pszFileName[1] == L'E' || pszFileName[1] == L'e') &&
                (pszFileName[2] == L'R' || pszFileName[2] == L'r') &&
                //(pszFileName[3] == L'N' || pszFileName[3] == L'n') &&
                (pszFileName[4] == L'E' || pszFileName[4] == L'e') &&
                //(pszFileName[5] == L'L' || pszFileName[5] == L'l') &&
                (pszFileName[6] == L'3' || pszFileName[6] == L'3') &&
                //(pszFileName[7] == L'2' || pszFileName[7] == L'2') &&
                (pszFileName[8] == L'.' || pszFileName[8] == L'.') &&
                //(pszFileName[9] == L'D' || pszFileName[9] == L'd') &&
                //(pszFileName[10] == L'L' || pszFileName[10] == L'l') &&
                (pszFileName[11] == L'L' || pszFileName[11] == L'l'))
            {
                CHAR szLoadLibrary[] = {
                    'L', 'o', 'a', 'd', 'L', 'i', 'b', 'r', 'a', 'r', 'y', 'A', '\0'
                };

                //�õ�LoadLibraryA
                PFNLoadLibraryA pfnLoadLibrary = (PFNLoadLibraryA)
                    GetProcAddr((HMODULE)pLdtEntry->DllBase, szLoadLibrary);

                if (pfnLoadLibrary == NULL)
                {
                    return NULL;
                }

                CHAR szDllName[MAX_PATH];

                int i = 0;

                //�õ�dll��
                while (((LPCSTR)pFuction)[i] != '.')
                {
                    szDllName[i] = ((LPCSTR)pFuction)[i];
                    i++;
                }

                szDllName[i] = '\0';

                HMODULE hModule = pfnLoadLibrary(szDllName);

                //�ݹ���Һ�����ַ
                return GetProcAddr(hModule, (LPCSTR)(pFuction + i + 1));
            }
        }

        //������һ��
        pLdtEntry = (PLDR_DATA_TABLE_ENTRY)pLdtEntry->InLoadOrderLinks.Flink;

    } while (pLdtEntry != NULL && pLdtEntry != pLdtEntryHead);

    return NULL;
}