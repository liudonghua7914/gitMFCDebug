
// gitJDMFCDebug.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CgitJDMFCDebugApp:
// �йش����ʵ�֣������ gitJDMFCDebug.cpp
//

class CgitJDMFCDebugApp : public CWinApp
{
public:
	CgitJDMFCDebugApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CgitJDMFCDebugApp theApp;