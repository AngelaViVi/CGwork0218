#pragma once


// RoateCubeDialog �Ի���

class RoateCubeDialog : public CDialogEx
{
	DECLARE_DYNAMIC(RoateCubeDialog)

public:
	RoateCubeDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~RoateCubeDialog();

// �Ի�������
	enum { IDD = IDD_DIALOG3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	double m_degree;
	CString m_rc;
};
