// MoveDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CGwork0218.h"
#include "MoveDialog.h"
#include "afxdialogex.h"


// CMoveDialog �Ի���

IMPLEMENT_DYNAMIC(CMoveDialog, CDialogEx)

CMoveDialog::CMoveDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMoveDialog::IDD, pParent)
	, m_dx(0)
	, m_dy(0)
	, m_dz(0)
{

}

CMoveDialog::~CMoveDialog()
{
}

void CMoveDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMoveDialog, CDialogEx)
	ON_BN_CLICKED(IDOK, &CMoveDialog::OnBnClickedOk)
END_MESSAGE_MAP()


// CMoveDialog ��Ϣ�������


void CMoveDialog::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnOK();
	
}
