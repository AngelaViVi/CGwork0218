#pragma once


// BGSMDialog �Ի���

class BGSMDialog : public CDialogEx
{
	DECLARE_DYNAMIC(BGSMDialog)

public:
	BGSMDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~BGSMDialog();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	double m_sx;
	double m_sy;
	double m_sz;
};
