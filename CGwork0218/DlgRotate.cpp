// DlgRotate.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CGwork0218.h"
#include "DlgRotate.h"
#include "afxdialogex.h"


// DlgRotate �Ի���

IMPLEMENT_DYNAMIC(DlgRotate, CDialogEx)

DlgRotate::DlgRotate(CWnd* pParent /*=NULL*/)
	: CDialogEx(DlgRotate::IDD, pParent)
{
	m_RotateAngle = 0.0;
}

DlgRotate::~DlgRotate()
{
}

void DlgRotate::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_ANGLE, m_RotateAngle);
}


BEGIN_MESSAGE_MAP(DlgRotate, CDialogEx)
END_MESSAGE_MAP()


// DlgRotate ��Ϣ�������
