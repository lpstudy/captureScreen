// captureScreen.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CcaptureScreenApp:
// �йش����ʵ�֣������ captureScreen.cpp
//

class CcaptureScreenApp : public CWinApp
{
public:
	CcaptureScreenApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CcaptureScreenApp theApp;