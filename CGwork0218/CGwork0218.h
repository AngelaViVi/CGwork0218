
// CGwork0218.h : CGwork0218 Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CCGwork0218App:
// �йش����ʵ�֣������ CGwork0218.cpp
//

class CCGwork0218App : public CWinAppEx
{
public:
	CCGwork0218App();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CCGwork0218App theApp;
