#pragma once


// CMoveDialog �Ի���

class CMoveDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CMoveDialog)

public:
	CMoveDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMoveDialog();

// �Ի�������
	enum { IDD = IDD_MoveDialog };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	// �洢ƽ����
	double m_dx;
	double m_dy;
	double m_dz;
	afx_msg void OnBnClickedOk();
};
