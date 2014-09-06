
// gitJDMFCDebugDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


#define  RECBUFSIZE 1024
#define PRESIZE	(200)
/*----------------------------------------------------------*/
/*
*	ö�����
*/
enum node
{
	Node_COM = 1,
};

enum eSelect
{
	eDebug = 0,
	eFind,
	eCalc
};

enum Calc
{
	ehex = 0,
	edec
};

// CgitJDMFCDebugDlg �Ի���
class CgitJDMFCDebugDlg : public CDialogEx
{
// ����
public:
	CgitJDMFCDebugDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_GITJDMFCDEBUG_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()


/*----------------------------------------------------------*/
/*
*	�������
*/
private:
	DWORD m_BaudRate;       /* Baudrate at which running       */
	BYTE m_ByteSize;        /* Number of bits/byte, 4-8        */
	BYTE m_Parity;          /* 0-4=None,Odd,Even,Mark,Space    */
	BYTE m_StopBits;        /* 0,1,2 = 1, 1.5, 2               */
	CString m_ComName;

	BOOL m_bHaveCloseComm;
	BOOL m_bKillCommThread;
	HANDLE m_hComm;	
	HANDLE m_hCommThread;
	OVERLAPPED m_ovRead;
	OVERLAPPED m_ovWrite;
	BYTE m_RecBuf[RECBUFSIZE];

	BYTE m_FlyConfigNode;
	CFile m_FlyConfigFile;
	CFile m_DebugFile;
	char  m_DebugMsgBuf[1000];
private:
	afx_msg BOOL ReadConfigFile(void);
	afx_msg BOOL OpenUartCom(void);//��ͨ�Ŵ���
	afx_msg void ReadUartCom(BYTE *p,UINT32 Len);
	afx_msg void WriteUartCom(BYTE *p,UINT32 Len);
	afx_msg void CloseUartCom(void);
	afx_msg BOOL InitDCB(void);
	afx_msg BOOL InitCommTimeouts(void);
	afx_msg HANDLE CreateCommThread(void);
	static DWORD WINAPI ThreadCommProc(LPCVOID pContext);

/*
*	�Ի��������
*/

private:
	// ѡ��ѡ��
	BYTE m_Select;
	BYTE m_calcSelect;

	BYTE m_CmdStatus;
	BYTE m_CmdType;
	BYTE m_CmdLen;
	BYTE m_CmdLenMax;
	BYTE m_CmdBuf[256];
	BYTE m_CmdCrc;

	BYTE m_DebugBuf[256];
	BYTE m_DebufCount;
	

	CButton m_CheckDebug;
	CButton m_CheckSelect;
private:
	afx_msg void OnBnClickedRadio1Debug();
	afx_msg void OnBnClickedRadio2Find();
	afx_msg void OnBnClickedRadio3Calc();

	afx_msg void OnBnClickedRadio4Dec();
	afx_msg void OnBnClickedRadio5Hex();

	afx_msg void DealCommData(BYTE data);
	afx_msg void EditShowDebug(char *p,UINT len);
	afx_msg BOOL StringConvetToHex(CString cs,BYTE *chdata);
	afx_msg BYTE TextConvettToHex(char *p,UINT len);
	afx_msg void HexConvetToString(BYTE *pdat,UINT len);
	CEdit m_DlgShowMsg;
public:
	afx_msg void OnBnClickedButton4OpenFile();
	afx_msg void OnBnClickedButton1Output();
	afx_msg void DealOpenFileData(BYTE edata);\


private:
	CEdit m_FindHead;
	CEdit m_FindType;
	CEdit m_FindLen;

	UINT32 m_OpenFileLength;
	char *m_pOpenFileBuf;
	BYTE *m_HexBuf;
	UINT m_HexBufCount;
	CString m_cFilePatchName;

	BYTE m_OpenFileStatus;
	UINT m_OpenFileLen;
	UINT m_OpenFileMaxLen;
	BYTE m_OpenFileFrameBuf[256];
	UINT m_OpenFileFrameCount;

	BYTE m_head;
	BYTE m_type;
	BYTE m_len;

	char m_Findch[10];
public:
	afx_msg void OnEnChangeEdit1Head();
};
