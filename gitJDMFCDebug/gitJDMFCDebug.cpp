
// gitJDMFCDebug.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "gitJDMFCDebug.h"
#include "gitJDMFCDebugDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CgitJDMFCDebugApp

BEGIN_MESSAGE_MAP(CgitJDMFCDebugApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CgitJDMFCDebugApp ����

CgitJDMFCDebugApp::CgitJDMFCDebugApp()
{
	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CgitJDMFCDebugApp ����

CgitJDMFCDebugApp theApp;


// CgitJDMFCDebugApp ��ʼ��

BOOL CgitJDMFCDebugApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// ���� shell ���������Է��Ի������
	// �κ� shell ����ͼ�ؼ��� shell �б���ͼ�ؼ���
	CShellManager *pShellManager = new CShellManager;

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

	CgitJDMFCDebugDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȡ�������رնԻ���Ĵ���
	}

	// ɾ�����洴���� shell ��������
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}

/*********************************************************************************************************************************************
**��������:		ReadConfigFile
**��������:
**��ڲ���:
**���ز���:
**********************************************************************************************************************************************/
BOOL CgitJDMFCDebugDlg::ReadConfigFile(void)
{
	BOOL bRes = FALSE;
	char *pBuf = NULL;
	UINT FileLength = 0;

	UINT32 i = 0;
	BOOL bNode = FALSE;
	BOOL bNeedProc = FALSE;
	BOOL bID = TRUE;

	char ID[256];
	char Value[256];

	BYTE IDlength = 0;
	BYTE ValueLength = 0;


	BOOL bRunFunc = FALSE;
	/*
	 * ��ȡ�����ļ�
	 */
	bRes = m_FlyConfigFile.Open(__T("Config.ini"),CFile::modeRead);
	if (bRes)
	{
		FileLength  = m_FlyConfigFile.GetLength();
		pBuf = new char[FileLength + 1];
		pBuf[FileLength] = '\0';
		m_FlyConfigFile.Read(pBuf,FileLength);
	}
	else
	{
		return FALSE;
	}

	/*
	 *	���������ļ�
	*/
	if (bRes)
	{
		for (i = 0;i <= FileLength;i++)
		{
			if ('[' == pBuf[i])
			{
				bNode = TRUE;
			}
			else if (']' == pBuf[i])
			{
				bNode = TRUE;
				bNeedProc = TRUE;
			}
			else if (('\r'== pBuf[i]) || ('\n' == pBuf[i]))
			{
				bNeedProc = TRUE;
				bID = TRUE;
			}
			else if ('=' == pBuf[i])
			{
				bID = FALSE;
			}
			else if( pBuf[i] > ' ')
			{
				if (bID)
				{
					ID[IDlength++] = pBuf[i];
					ID[IDlength] = '\0';
				}
				else
				{
					Value[ValueLength++] = pBuf[i];
					Value[ValueLength] = '\0';
				}

			}

			if (bNeedProc)
			{
				if (bNode)
				{
					if (IDlength)
					{
						//FlyConfigProcInIData(TRUE,ID,NULL);
						bRunFunc = TRUE;
					}

				}
				else
				{
					if (IDlength && ValueLength)
					{
						//FlyConfigProcInIData(FALSE,ID,Value);
						bRunFunc = TRUE;
					}	
				}

				if(bRunFunc)
				{
					bRunFunc = FALSE;

					if (bNode)
					{
						if(!memcmp("COM",ID,sizeof("COM")))
						{
							m_FlyConfigNode = Node_COM;
						}
					}
					else
					{
						if (Node_COM == m_FlyConfigNode)
						{
							if (!memcmp(("ComName"),ID,sizeof("ComName")))
							{
								m_ComName = Value;
							}
							else if (!memcmp(("BaudRate"),ID,sizeof("BaudRate")))
							{
								m_BaudRate = atoi(Value);
							}
							else if (!memcmp(("Parity"),ID,sizeof("Parity")))
							{
								if (!memcmp(("NOPARITY"),Value,sizeof("NOPARITY")))
								{
									m_Parity = NOPARITY;
								}
							}
							else if (!memcmp(("StopBits"),ID,sizeof("StopBits")))
							{
								if (!memcmp(("ONESTOPBIT"),Value,sizeof("ONESTOPBIT")))
								{
									m_StopBits = ONESTOPBIT;
								}
							}
							else if (!memcmp(("ByteSize"),ID,sizeof("ByteSize")))
							{
								m_ByteSize = atoi(Value);
							}
						}
					}	
				}


				bNeedProc = FALSE;
				bNode = FALSE;
				IDlength = 0;
				ValueLength = 0;
			}
		}
	}

	

	delete pBuf;

	return bRes;
}

/*********************************************************************************************************************************************
**��������:		InitDCB
**��������:
**��ڲ���:
**���ز���:
**********************************************************************************************************************************************/
BOOL CgitJDMFCDebugDlg::InitDCB(void)
{
	DCB PortDCB;

	GetCommState(m_hComm,&PortDCB);
	PortDCB.DCBlength = sizeof(DCB);
	PortDCB.BaudRate = m_BaudRate;
	PortDCB.ByteSize = m_ByteSize;
	PortDCB.fBinary = TRUE;		//Win32��֧�ַǶ����ƴ��д���ģʽ������ΪTRUE 
	PortDCB.fParity = FALSE;	//��żУ�� 
	PortDCB.fOutxCtsFlow = FALSE;
	PortDCB.fOutxDsrFlow = FALSE;
	PortDCB.fTXContinueOnXoff = FALSE;
	PortDCB.fOutX = FALSE;
	PortDCB.fInX = FALSE;
	PortDCB.fErrorChar = FALSE;
	PortDCB.fNull = FALSE;
	PortDCB.fRtsControl = RTS_CONTROL_DISABLE;
	PortDCB.fAbortOnError = FALSE;
	PortDCB.Parity = m_Parity;
	PortDCB.StopBits =m_StopBits;
	if(!SetCommState(m_hComm,&PortDCB))
	{	
		return FALSE;
	}
	return TRUE;
}
/*********************************************************************************************************************************************
**��������:		InitCommTimeouts
**��������:
**��ڲ���:
**���ز���:
**********************************************************************************************************************************************/
BOOL CgitJDMFCDebugDlg::InitCommTimeouts(void)
{
	COMMTIMEOUTS CommTimeOuts;
	GetCommTimeouts(m_hComm,&CommTimeOuts);
	CommTimeOuts.ReadIntervalTimeout = MAXDWORD;
	CommTimeOuts.ReadTotalTimeoutMultiplier = 0;
	CommTimeOuts.ReadTotalTimeoutConstant = 0;
	CommTimeOuts.WriteTotalTimeoutConstant = 0;
	CommTimeOuts.WriteTotalTimeoutMultiplier = 0;
	if (!SetCommTimeouts(m_hComm,&CommTimeOuts))
	{
		return FALSE;
	}
	return TRUE;
}
/*********************************************************************************************************************************************
**��������:		ReadUartCom
**��������:
**��ڲ���:
**���ز���:
**********************************************************************************************************************************************/
void CgitJDMFCDebugDlg::ReadUartCom(BYTE *p,UINT32 Len)
{
	UINT32 i;
	if(Len && (eDebug == m_Select))
	{
		for (i = 0;i < Len;i++)
		{
			DealCommData(p[i]);
		}
	}
}
/*********************************************************************************************************************************************
**��������:		WriteUartCom
**��������:
**��ڲ���:
**���ز���:
**********************************************************************************************************************************************/
void CgitJDMFCDebugDlg::WriteUartCom(BYTE *p,UINT32 Len)
{
	DWORD dwLength;
	BOOL fWriteStatus;
	DWORD dwRes;
	memset(&m_ovWrite,0,sizeof(m_ovWrite));
	m_ovWrite.hEvent = CreateEvent(NULL,TRUE,FALSE,NULL);
	fWriteStatus = WriteFile(m_hComm,p,Len,&dwLength,&m_ovWrite);
	if (!fWriteStatus)
	{
		if(ERROR_IO_PENDING == GetLastError())
		{
			dwRes = WaitForSingleObject(m_ovWrite.hEvent,INFINITE);
			switch(dwRes)
			{
				case WAIT_OBJECT_0:		if(GetOverlappedResult(m_hComm,&m_ovWrite,&dwLength,FALSE))
										{

										}
										break;

				case WAIT_TIMEOUT:		
					break;

				default:				
					break; 
			}	
		}
	}	
}
/*********************************************************************************************************************************************
**��������:		ThreadCommProc
**��������:
**��ڲ���:
**���ز���:
**********************************************************************************************************************************************/
DWORD WINAPI CgitJDMFCDebugDlg::ThreadCommProc(LPCVOID pContext)
{
	DWORD dwLength;
	BOOL fReadStatus;
	BOOL bWaitingOnRead = FALSE;	
	DWORD dwRes;
	CgitJDMFCDebugDlg *pUpdateT123Dlg = (CgitJDMFCDebugDlg *)pContext;

	memset(&pUpdateT123Dlg->m_ovRead,0,sizeof(pUpdateT123Dlg->m_ovRead));

	pUpdateT123Dlg->m_ovRead.hEvent = CreateEvent(NULL,TRUE,FALSE,NULL);

	while (!pUpdateT123Dlg->m_bKillCommThread)
	{
		fReadStatus = ReadFile(pUpdateT123Dlg->m_hComm,pUpdateT123Dlg->m_RecBuf,RECBUFSIZE,&dwLength,&pUpdateT123Dlg->m_ovRead);//
		if (!fReadStatus)
		{
			if(ERROR_IO_PENDING == GetLastError())
			{
				dwRes = WaitForSingleObject(pUpdateT123Dlg->m_ovRead.hEvent,500);
				switch(dwRes)
				{
					case WAIT_OBJECT_0:		if(GetOverlappedResult(pUpdateT123Dlg->m_hComm,&pUpdateT123Dlg->m_ovRead,&dwLength,FALSE))
											{
												//���ö�����
												pUpdateT123Dlg->ReadUartCom(pUpdateT123Dlg->m_RecBuf,dwLength);
											}
											break;

					case WAIT_TIMEOUT:		
						break;

					default:				
						break; 
				}

			}
		}
		else
		{
			//���ö�����
			pUpdateT123Dlg->ReadUartCom(pUpdateT123Dlg->m_RecBuf,dwLength);
		}
	}

	return TRUE;
}
/*********************************************************************************************************************************************
**��������:		OpenUartCom
**��������:
**��ڲ���:
**���ز���:
**********************************************************************************************************************************************/
BOOL CgitJDMFCDebugDlg::OpenUartCom(void)
{
	DWORD dwThreadID;
/*
 *	���ڳ�ʼ��
*/
	CString msg;
#if 1
	if (!ReadConfigFile())
	{
		msg = "Open ReadConfigFile Fail";
		MessageBox(msg);
		return FALSE;
	}
#else
	m_ComName = "COM5:";
	m_BaudRate = 115200;
	m_Parity = NOPARITY;
	m_StopBits = ONESTOPBIT;
	m_ByteSize = 8;
#endif
	
	m_hComm = CreateFile(m_ComName,GENERIC_READ | GENERIC_WRITE,0,NULL,OPEN_EXISTING,FILE_FLAG_OVERLAPPED,NULL);
	if(INVALID_HANDLE_VALUE == m_hComm)
	{
		msg = "Open Fail ";
		msg += m_ComName;
		MessageBox(msg);
		return FALSE;
	}

	SetCommMask(m_hComm,EV_RXCHAR);
	SetupComm(m_hComm,1024,512);
	PurgeComm(m_hComm,PURGE_TXCLEAR|PURGE_RXCLEAR);

	if(!InitDCB())
	{
		msg = "InitDCB Fail ";	
		MessageBox(msg);
		return FALSE;
	}
	if (!InitCommTimeouts())
	{
		msg = "InitCommTimeouts Fail ";	
		MessageBox(msg);	
		return FALSE;
	}

	EscapeCommFunction(m_hComm,SETDTR);
	EscapeCommFunction(m_hComm,SETRTS);
	m_bKillCommThread = FALSE;
	m_hCommThread = CreateThread((LPSECURITY_ATTRIBUTES)NULL,
								0,
								(LPTHREAD_START_ROUTINE)ThreadCommProc,
								this,
								0,
								&dwThreadID
								);
	if(NULL == m_hCommThread)
	{
		msg = "CreateThread ThreadCommProc Fail ";	
		MessageBox(msg);	
		return FALSE;
	}

	return TRUE;
}


/*********************************************************************************************************************************************
**��������:		CloseUartCom
**��������:
**��ڲ���:
**���ز���:
**********************************************************************************************************************************************/
void CgitJDMFCDebugDlg::CloseUartCom(void)
{
	m_bKillCommThread = TRUE;

	if (INVALID_HANDLE_VALUE != m_hComm)
	{
		CloseHandle(m_hComm);
	}

	if (NULL != m_hCommThread)
	{
		CloseHandle(m_hCommThread);
	}

	if (NULL != m_ovRead.hEvent)
	{
		ResetEvent(m_ovRead.hEvent);
	}

	if (NULL != m_ovWrite.hEvent)
	{
		ResetEvent(m_ovWrite.hEvent);
	}
}