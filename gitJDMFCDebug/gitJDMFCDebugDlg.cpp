
// gitJDMFCDebugDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "gitJDMFCDebug.h"
#include "gitJDMFCDebugDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CgitJDMFCDebugDlg 对话框




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


// CgitJDMFCDebugDlg 消息处理程序

BOOL CgitJDMFCDebugDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
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

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CgitJDMFCDebugDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CgitJDMFCDebugDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CgitJDMFCDebugDlg::OnBnClickedRadio1Debug()
{
	// TODO: 在此添加控件通知处理程序代码
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
	// TODO: 在此添加控件通知处理程序代码
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
	// TODO: 在此添加控件通知处理程序代码
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
	// TODO: 在此添加控件通知处理程序代码
	m_calcSelect = e8bit;
}


void CgitJDMFCDebugDlg::OnBnClickedRadio5Hex()
{
	// TODO: 在此添加控件通知处理程序代码
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
	// TODO: 在此添加控件通知处理程序代码
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
	char *ch = NULL;
	ch = new char[64];
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

	delete ch;
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
						m_OpenFileFrameBuf[2] = m_len;

						m_OpenFileLen = 0;
					}
					else
					{
						m_OpenFileStatus = 0x00;
					}
					break;

		case 0x02:	if (m_OpenFileLen < m_OpenFileMaxLen)
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
		MessageBox(__T("输入为空"));
	}
	else
	{
		bConvet = FALSE; 
		MessageBox(__T("输入长度度不对,请输入2位十六进制数"));
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
			MessageBox(__T("不是十六进制数"));
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
	// TODO: 在此添加控件通知处理程序代码

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
			//解析文本信息
			for (i = 0;i < m_HexBufCount;i++)
			{
				DealOpenFileData(m_HexBuf[i]);
			}
			delete m_HexBuf;
		}
		MessageBox(__T("文件查找完毕"));
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
		 


	//关闭文件
	OpenFile.Close();
}


void CgitJDMFCDebugDlg::OnEnChangeEdit1Head()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代

}


void CgitJDMFCDebugDlg::OnBnClickedButton2Clear()
{
	// TODO: 在此添加控件通知处理程序代码
	m_DlgShowMsg.SetSel(0,-1);
	m_DlgShowMsg.ReplaceSel(__T(""));
}


void CgitJDMFCDebugDlg::OnBnClickedButton3SaveFile()
{
	// TODO: 在此添加控件通知处理程序代码
	CString m_strDate,m_strTime;
	CTime m_time;  

	m_time=CTime::GetCurrentTime();             //获取当前时间日期  
	m_strDate=m_time.Format(_T("%x"));          //格式化日期  
	m_strTime=m_time.Format(_T("%X"));          //格式化时间  
	m_cSaveFile=m_time.Format(_T("%Y-%m-%d %H:%M:%S %A end"));   //格式化日期时间

	int len = m_cSaveFile.GetLength();

	

	///CFile saveFile(m_cSaveFile,CFile::modeCreate | CFile::modeReadWrite);

	//saveFile.Write((char *)("addfdfdff"),5);

	MessageBox(m_cSaveFile);
}
