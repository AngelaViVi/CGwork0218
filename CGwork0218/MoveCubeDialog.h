#pragma once


// MoveCubeDialog �Ի���

class MoveCubeDialog : public CDialogEx
{
	DECLARE_DYNAMIC(MoveCubeDialog)

public:
	MoveCubeDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~MoveCubeDialog();

// �Ի�������
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	double m_dx;
	double m_dy;
	double m_dz;
};
