#pragma once


// DlgRotate �Ի���

class DlgRotate : public CDialogEx
{
	DECLARE_DYNAMIC(DlgRotate)

public:
	DlgRotate(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~DlgRotate();

// �Ի�������
	enum { IDD = IDD_DLGROTATE };
	double	m_RotateAngle;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
