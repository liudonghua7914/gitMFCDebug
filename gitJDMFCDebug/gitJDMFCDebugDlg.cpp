
// gitJDMFCDebugDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "gitJDMFCDebug.h"
#include "gitJDMFCDebugDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CgitJDMFCDebugDlg �Ի���




CgitJDMFCDebugDlg::CgitJDMFCDebugDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CgitJDMFCDebugDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CgitJDMFCDebugDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_RADIO1, m_CheckDebug);
	DDX_Control(pDX, IDC_RADIO4, m_CheckSelect);
	DDX_Control(pDX, IDC_EDIT4, m_DlgShowMsg);
	DDX_Control(pDX, IDC_EDIT1, m_FindHead);
	DDX_Control(pDX, IDC_EDIT2, m_FindType);
	DDX_Control(pDX, IDC_EDIT3, m_FindLen);
}

BEGIN_MESSAGE_MAP(CgitJDMFCDebugDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_RADIO1, &CgitJDMFCDebugDlg::OnBnClickedRadio1Debug)
	ON_BN_CLICKED(IDC_RADIO2, &CgitJDMFCDebugDlg::OnBnClickedRadio2Find)
	ON_BN_CLICKED(IDC_RADIO3, &CgitJDMFCDebugDlg::OnBnClickedRadio3Calc)
	ON_BN_CLICKED(IDC_RADIO4, &CgitJDMFCDebugDlg::OnBnClickedRadio4Dec)
	ON_BN_CLICKED(IDC_RADIO5, &CgitJDMFCDebugDlg::OnBnClickedRadio5Hex)
	ON_BN_CLICKED(IDC_BUTTON4, &CgitJDMFCDebugDlg::OnBnClickedButton4OpenFile)
	ON_BN_CLICKED(IDC_BUTTON1, &CgitJDMFCDebugDlg::OnBnClickedButton1Output)
	ON_EN_CHANGE(IDC_EDIT1, &CgitJDMFCDebugDlg::OnEnChangeEdit1Head)
	ON_BN_CLICKED(IDC_BUTTON2, &CgitJDMFCDebugDlg::OnBnClickedButton2Clear)
	ON_BN_CLICKED(IDC_BUTTON3, &CgitJDMFCDebugDlg::OnBnClickedButton3SaveFile)
END_MESSAGE_MAP()


// CgitJDMFCDebugDlg ��Ϣ�������

BOOL CgitJDMFCDebugDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	m_CmdStatus = 0;


	SetDlgItemText(IDC_EDIT1,__T("2e"));
	SetDlgItemText(IDC_EDIT2,__T("60"));
	SetDlgItemText(IDC_EDIT3,__T("5"));


	GetDlgItem(IDC_EDIT1)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT2)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT3)->EnableWindow(FALSE);

	GetDlgItem(IDC_RADIO4)->EnableWindow(FALSE);
	GetDlgItem(IDC_RADIO5)->EnableWindow(FALSE);

	GetDlgItem(IDC_BUTTON1)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON4)->EnableWindow(FALSE);


	m_DlgShowMsg.SetLimitText(100000);

	m_calcSelect = e8bit;

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CgitJDMFCDebugDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CgitJDMFCDebugDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CgitJDMFCDebugDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CgitJDMFCDebugDlg::OnBnClickedRadio1Debug()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_Select = eDebug;
	m_CheckDebug.SetCheck(TRUE);
	m_CheckSelect.SetCheck(TRUE);

	GetDlgItem(IDC_EDIT1)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT2)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT3)->EnableWindow(FALSE);

	GetDlgItem(IDC_RADIO4)->EnableWindow(FALSE);
	GetDlgItem(IDC_RADIO5)->EnableWindow(FALSE);

	GetDlgItem(IDC_BUTTON1)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON4)->EnableWindow(FALSE);
}


void CgitJDMFCDebugDlg::OnBnClickedRadio2Find()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_Select = eFind;
	GetDlgItem(IDC_EDIT1)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT2)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT3)->EnableWindow(TRUE);

	GetDlgItem(IDC_RADIO4)->EnableWindow(FALSE);
	GetDlgItem(IDC_RADIO5)->EnableWindow(FALSE);

	
	GetDlgItem(IDC_BUTTON4)->EnableWindow(TRUE);
}


void CgitJDMFCDebugDlg::OnBnClickedRadio3Calc()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_Select = eCalc;

	GetDlgItem(IDC_EDIT1)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT2)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT3)->EnableWindow(FALSE);

	GetDlgItem(IDC_RADIO4)->EnableWindow(TRUE);
	GetDlgItem(IDC_RADIO5)->EnableWindow(TRUE);

	GetDlgItem(IDC_BUTTON1)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON4)->EnableWindow(TRUE);
}


void CgitJDMFCDebugDlg::OnBnClickedRadio4Dec()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_calcSelect = e8bit;
}


void CgitJDMFCDebugDlg::OnBnClickedRadio5Hex()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_calcSelect = e16bit;
}

void CgitJDMFCDebugDlg::DealCommData(BYTE data)
{
	switch(m_CmdStatus)
	{
		case 0x00:	if (0X2E == data)
					{
						m_CmdStatus = 0x01;
						m_DebufCount = 0;
						m_DebugBuf[m_DebufCount++] = data;
					}
					break;

		case 0x01:	m_CmdType = data;
					m_CmdStatus = 0x02;
					m_DebugBuf[m_DebufCount++] = data;
					break;

		case 0x02:	m_CmdLenMax = data;
					m_CmdLen = 0;
					m_CmdCrc = 0;
					m_CmdStatus = 0x03;	
					m_DebugBuf[m_DebufCount++] = data;
					break;

		case 0x03:	if (m_CmdLen <= m_CmdLenMax)
					{
						m_CmdStatus = 0X03;
						m_CmdBuf[m_CmdLen++] = data;
						m_DebugBuf[m_DebufCount++] = data;
						m_CmdCrc += data;					
					}
					else
					{
						m_CmdStatus = 0X04;
					}
					break;

		case 0x04:	m_DebugBuf[m_DebufCount++] = data;
					if(data == (0XFF - (BYTE)m_CmdCrc))
					{
						m_DebugBuf[m_DebufCount++] = '\r';
						m_DebugBuf[m_DebufCount++] = '\n';
						m_DebugBuf[m_DebufCount] = '\0';
					}
					else
					{
						int copylen = strlen("CRC ERROR\r\n");
						memcpy(&m_DebugBuf[m_DebufCount],"CRC ERROR\r\n",copylen);
						m_DebufCount += copylen;
						m_DebugBuf[m_DebufCount] = '\0';
					}

					EditShowDebug((char *)m_DebugBuf,m_DebufCount);
					break;

		default:
					break;

	}
}

void CgitJDMFCDebugDlg::EditShowDebug(char *p,UINT len)
{
	WCHAR *pwDebug = NULL;
	int copyLen = 0;
	copyLen = MultiByteToWideChar(CP_ACP,0,(char *)p,-1,NULL,0);
	pwDebug = new WCHAR[copyLen];

	MultiByteToWideChar(CP_ACP,0,(char *)p,-1,pwDebug,copyLen);

	m_DlgShowMsg.SetSel(-1,-1);
	m_DlgShowMsg.ReplaceSel(pwDebug);

	delete pwDebug;
}

void CgitJDMFCDebugDlg::OnBnClickedButton4OpenFile()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CFileDialog UpdateFileDlg(TRUE);
	UpdateFileDlg.m_ofn.lpstrFilter = __T("All File (*.*)\0*.*\0*.bin\0*.bin\0Text(*.txt)\0*.txt\0\0");
	
	if (IDOK  == UpdateFileDlg.DoModal())
	{
		m_cFilePatchName = UpdateFileDlg.GetPathName();
		GetDlgItem(IDC_BUTTON1)->EnableWindow(TRUE);
		m_OpenFileStatus = 0;
	}
}

const char StingHex[] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};


void CgitJDMFCDebugDlg::HexConvetToString(BYTE *pdat,UINT len)
{
	char ch[256];
	
	int cnt = 0;
	int i;
	BYTE tmp;
	char chtmp;


	for (i = 0;i < len;i++)
	{
		tmp = pdat[i];
		ch[i * 3] = StingHex[tmp / 16];
		ch[i * 3 + 1] = StingHex[tmp % 16];
		ch[i * 3 + 2] = ' ';
	
	}
	ch[i * 3 + 0] = '\r';
	ch[i * 3 + 1] = '\n';
	ch[i * 3 + 2] = '\0';

	EditShowDebug(ch,cnt+2);
}

void CgitJDMFCDebugDlg::DealOpenFileData(BYTE edata)
{
	switch(m_OpenFileStatus)
	{
		case 0x00:	if (m_head == edata)
					{
						m_OpenFileStatus = 0x01;
						m_OpenFileFrameCount = 0;
					}
					break;

		case 0X01:	if (m_type == edata)
					{
						m_OpenFileStatus = 0x02;
						m_OpenFileMaxLen = m_len;

						m_OpenFileFrameBuf[0] = m_head;
						m_OpenFileFrameBuf[1] = m_type;
						//m_OpenFileFrameBuf[2] = m_len;

						m_OpenFileLen = 0;
					}
					else
					{
						m_OpenFileStatus = 0x00;
					}
					break;

		case 0x02:	if(m_len > edata)
					{
						m_OpenFileStatus = 0;
						MessageBox(__T("len > MAX Len"));
						m_OpenFileStatus = 0x03;
						m_OpenFileFrameBuf[2] = edata;
						m_OpenFileMaxLen = edata;
					}
					else
					{
						m_OpenFileStatus = 0x03;
						m_OpenFileFrameBuf[2] = edata;
						m_OpenFileStatus = 0x03;
					}				
					break;
					
		case 0x03:	if (m_OpenFileLen < m_OpenFileMaxLen)
					{
						m_OpenFileFrameBuf[m_OpenFileLen + 3] = edata;
						m_OpenFileLen++;
					}
					else
					{
						m_OpenFileStatus = 0;
						HexConvetToString(m_OpenFileFrameBuf,m_OpenFileLen + 3);
					}
					break;
	}
}

BOOL CgitJDMFCDebugDlg::StringConvetToHex(CString cs,BYTE *chdata)
{
	BOOL bConvet = TRUE;
	int   iTextLen;
	char *pszMultiByte;
	BYTE convertData = 0;
	BYTE charData = 0;

	int length = cs.GetLength();

	if (2 >= length)
	{
		bConvet = TRUE;
	}
	else if (!length)
	{
		bConvet = FALSE; 
		MessageBox(__T("����Ϊ��"));
	}
	else
	{
		bConvet = FALSE; 
		MessageBox(__T("���볤�ȶȲ���,������2λʮ��������"));
	}



	iTextLen = WideCharToMultiByte(CP_ACP, 0, cs, -1, NULL, 0, NULL, NULL);
	pszMultiByte = new char[iTextLen + 1];
	pszMultiByte[iTextLen] = '\0';
	WideCharToMultiByte(CP_ACP, 0, cs, -1, pszMultiByte, iTextLen, NULL, NULL);
	for (int i = 0;i < length;i ++)
	{
		if (('0' <= pszMultiByte[i]) && (pszMultiByte[i] <='9'))
		{
			charData = pszMultiByte[i] - '0';
		}
		else if (('a' <= pszMultiByte[i]) && (pszMultiByte[i] <='f'))
		{
			charData =  pszMultiByte[i] - 'a' + 10;
		}
		else if (('A' <= pszMultiByte[i]) && (pszMultiByte[i] <='F'))
		{
			charData =  pszMultiByte[i] - 'A' + 10;
		}
		else
		{
			bConvet = FALSE;
			MessageBox(__T("����ʮ��������"));
		}

		convertData = (convertData << (i * 4)) + charData;
	}
	*chdata = convertData;
	delete pszMultiByte;

	return bConvet;
}


BYTE CgitJDMFCDebugDlg::TextConvettToHex(char *p,UINT len)
{
	BYTE charData = 0;
	BYTE convertData = 0;
	UINT cnt = 0;
	BOOL bCov = TRUE;
	m_HexBufCount = 0;
	
	for (UINT i = 0;i < len;i++)
	{
		bCov = TRUE;
		if (' ' == p[i] || ',' == p[i] || '\0' == p[i])
		{
			if (cnt)
			{
				m_HexBuf[m_HexBufCount++] = convertData;
			}
			cnt = 0;
			charData = 0;
			convertData = 0;
			bCov = FALSE;
		} 
		else if (('0' <= p[i]) && (p[i] <='9'))
		{
			charData = p[i] - '0';
		}
		else if (('a' <= p[i]) && (p[i] <='f'))
		{
			charData =  p[i] - 'a' + 10;
		}
		else if (('A' <= p[i]) && (p[i] <='F'))
		{
			charData =  p[i] - 'A' + 10;
		}
		else
		{
			MessageBox(__T("�ļ����зǷ�����"));
			bCov = FALSE;
		}
		if (bCov)
		{
			convertData = (convertData << (cnt * 4)) + charData;
			cnt = (cnt + 1) % 10;
		}	
	}

	
	return 0;
}

WCHAR wHex[] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};

void CgitJDMFCDebugDlg::OnBnClickedButton1Output()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	UINT i = 0;
	BOOL bDeal = FALSE;
	CString csFind;
	CFile OpenFile(m_cFilePatchName,CFile::modeRead);
	m_OpenFileLength = OpenFile.GetLength();
	m_pOpenFileBuf = NULL;

	if(m_OpenFileLength)
	{
		if (NULL == m_pOpenFileBuf)
		{
			m_pOpenFileBuf = new char[m_OpenFileLength + 1];
			m_pOpenFileBuf[m_OpenFileLength] = '\0';
			OpenFile.Read(m_pOpenFileBuf,m_OpenFileLength);
		}	
	}
	else
	{
		MessageBox(__T("OpenFile Fail"));
	}

	m_HexBuf = new BYTE[m_OpenFileLength + 1];	
	m_HexBuf[m_OpenFileLength] = '\0';
	TextConvettToHex(m_pOpenFileBuf,m_OpenFileLength + 1);

	if(eFind == m_Select)
	{
		m_FindHead.GetWindowText(csFind);
		bDeal = StringConvetToHex(csFind,&m_head);


		m_FindType.GetWindowText(csFind);
		bDeal = StringConvetToHex(csFind,&m_type);

		m_FindLen.GetWindowText(csFind);
		bDeal = StringConvetToHex(csFind,&m_len);


		if (bDeal)
		{
			//�����ı���Ϣ
			for (i = 0;i < m_HexBufCount;i++)
			{			
				DealOpenFileData(m_HexBuf[i]);
			}
			delete m_HexBuf;
		}
		MessageBox(__T("�ļ��������"));
	}
	else if (eCalc == m_Select)
	{

			BYTE check8bitSum = 0;
			WCHAR w8bit[6];
			for (UINT i = 0;i < m_HexBufCount;i++)
			{
				check8bitSum += m_HexBuf[i];
			}
			w8bit[0] = wHex[check8bitSum / 16];
			w8bit[1] = wHex[check8bitSum % 16];
			w8bit[2] = '\r';
			w8bit[3] = '\n';
			w8bit[4] = '\0';

			m_DlgShowMsg.SetSel(0,-1);
			m_DlgShowMsg.ReplaceSel(__T("8bit checksum: "));

			m_DlgShowMsg.SetSel(-1,-1);
			m_DlgShowMsg.ReplaceSel(w8bit);

			m_DlgShowMsg.SetSel(-1,-1);
			m_DlgShowMsg.ReplaceSel(__T("8bit checksum~: "));

			
			w8bit[0] = wHex[(0XFF - check8bitSum) / 16];
			w8bit[1] = wHex[(0XFF - check8bitSum) % 16];
			w8bit[2] = '\r';
			w8bit[3] = '\n';
			w8bit[4] = '\0';
			m_DlgShowMsg.SetSel(-1,-1);
			m_DlgShowMsg.ReplaceSel(w8bit);
			


			m_DlgShowMsg.SetSel(-1,-1);
			m_DlgShowMsg.ReplaceSel(__T("16bit checksum: "));


			WCHAR w16bit[10];
			UINT16 check16bitSum = 0;
			for (UINT i = 0;i < m_HexBufCount;i++)
			{
				check16bitSum += m_HexBuf[i];
			}
			w16bit[0] = wHex[((check16bitSum >> 8) & 0XFF) / 16 ];
			w16bit[1] = wHex[((check16bitSum >> 8) & 0XFF) % 16 ];
			w16bit[2] = wHex[((check16bitSum >> 0) & 0XFF) / 16 ];
			w16bit[3] = wHex[((check16bitSum >> 0) & 0XFF) % 16 ];
			w16bit[4] = '\r';
			w16bit[5] = '\n';
			w16bit[6] = '\0';
			m_DlgShowMsg.SetSel(-1,-1);
			m_DlgShowMsg.ReplaceSel(w16bit);


			m_DlgShowMsg.SetSel(-1,-1);
			m_DlgShowMsg.ReplaceSel(__T("16bit checksum~: "));
			w16bit[0] = wHex[(((0XFFFF - check16bitSum) >> 8) & 0XFF) / 16 ];
			w16bit[1] = wHex[(((0XFFFF - check16bitSum) >> 8) & 0XFF) % 16 ];
			w16bit[2] = wHex[(((0XFFFF - check16bitSum) >> 0) & 0XFF) / 16 ];
			w16bit[3] = wHex[(((0XFFFF - check16bitSum) >> 0) & 0XFF) % 16 ];
			w16bit[4] = '\r';
			w16bit[5] = '\n';
			w16bit[6] = '\0';
			m_DlgShowMsg.SetSel(-1,-1);
			m_DlgShowMsg.ReplaceSel(w16bit);



	}
		 


	//�ر��ļ�
	OpenFile.Close();
}


void CgitJDMFCDebugDlg::OnEnChangeEdit1Head()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ��������

}


void CgitJDMFCDebugDlg::OnBnClickedButton2Clear()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_DlgShowMsg.SetSel(0,-1);
	m_DlgShowMsg.ReplaceSel(__T(""));
}


void CgitJDMFCDebugDlg::OnBnClickedButton3SaveFile()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString m_strDate,m_strTime;
	
	CTime m_time;  
	m_time=CTime::GetCurrentTime();             //��ȡ��ǰʱ������  
	m_strDate=m_time.Format(_T("%x"));          //��ʽ������  
	m_strTime=m_time.Format(_T("%X"));          //��ʽ��ʱ��  
	m_cSaveFile=m_time.Format(_T("%Y-%m-%d_%H-%M-%S"));   //��ʽ������ʱ��

	m_cSaveFile = m_cSaveFile + __T(".txt");

	

	CFile saveFile(m_cSaveFile,CFile::modeCreate | CFile::modeReadWrite);

	int len = m_DlgShowMsg.GetWindowTextLength();
	WCHAR *pText = new WCHAR[len];
	//pText[len] = '\0';
	m_DlgShowMsg.GetWindowText(pText,len);

	char *pszMultiByte;

	int iTextLen = WideCharToMultiByte(CP_ACP, 0, pText, -1, NULL, 0, NULL, NULL);

	pszMultiByte = new char[iTextLen + 1];
	pszMultiByte[iTextLen] = '\0';
	WideCharToMultiByte(CP_ACP, 0, pText, -1, pszMultiByte, iTextLen, NULL, NULL);
	delete pText;

	saveFile.Write((char *)pszMultiByte,iTextLen - 1);
	MessageBox(m_cSaveFile);
	saveFile.Close();
	delete pszMultiByte;
	
}
