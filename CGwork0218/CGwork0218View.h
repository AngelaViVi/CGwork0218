
// CGwork0218View.h : CCGwork0218View ��Ľӿ�
//

//#pragma once
#include "atltypes.h"
#include "stdlib.h"
#include "math.h"
#include <list>
#include <vector>
#include"CGwork0218Doc.h"
#include "Beizer.h"
#include "afxtempl.h"
#include"Fill.h"
#include "vssym32.h"
struct MYPOINT//Բ
{
	int x;
	int y;     //�뾶
};

struct EDGE {//�߱�Ľڵ�
	int ymin;
	int ymax;
	double xmin;
	double fm;

	EDGE * next;
	EDGE * pre;
};

struct ThPoint{/*���ﶨ��һ���洢��ά��Ľṹ*/
	double x;
	double y;
	double z;
};
// ��������
enum DRAWSORT{ DsNull, DsLine,DsPolygon, DsMovePolygon,DsRotatePolygon,DsCircle,DsFill,DsFill2,DsFill3,DsBezier,DsBsize,DsCube};
// �����㷨
enum LINETYPE{ DDA, MDA, BRDL };
// ��Բ�㷨
enum CIRCLETYPE{ MDC, BRDC };
// ͶӰ�㷨
enum ProFunction{TOUSHI,XIEJIAO};
// ���߲�������
enum ChooseType{ Bezier, BYangTiao, NHSanCiYangTiao, NHBezier, NHBYangTiao };
// ������ʱ����״̬
enum MouseStatus{ LButtonDown, LButtonUp, RButtonDown, RButtonUp, MouseMove };

using namespace std;

class CCGwork0218View : public CView
{
protected: // �������л�����
	CCGwork0218View();
	DECLARE_DYNCREATE(CCGwork0218View)

// ����
public:
	CCGwork0218Doc* GetDocument() const;
	enum FILLTYPE{ FEEDFILL, EXTFLOODFILL };//��䷽ʽ
// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// ʵ��
public:
	virtual ~CCGwork0218View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	// ���ڱ���Ƿ��ڶ���λ���ģʽ
	bool bDrawMark;
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnMove();
	// �����ƽ�Ƶ�ʵ�ֺ���
	void Move(CPoint start, CPoint end);
	afx_msg void OnRotate();
	// �������ת��ʵ�ֺ���
	void Rotate(CPoint ptBase, double angle);
	afx_msg void OnFill();
	// ���������ʵ�ֺ���
	void Fill();
	// �ƶ����
	bool bMoveMark;
	// �ƶ������
	CPoint MoveStart;
	// �ƶ�����ֹ��
	CPoint MoveEnd;
	// ��ת�������
	bool bRotateMark;
	// ��ת����
	CPoint RotateBase;
	// �����
	bool bFillMark;
	// ƽ�ƵĲ���
	int ptNum;
	// ����������ɫ
	COLORREF clr;
	// ��ת�Ƕ�
	double RotateAngle;
	// ���ʹ��
	HCURSOR DrawCur;

	DRAWSORT m_dsDrawSort;		//��ͼ����
	LINETYPE m_LineType;		//�����㷨
	CIRCLETYPE m_CircleType;	//��Բ�㷨
	ProFunction m_proFunc;      //ͶӰ�㷨
	bool m_bDrawMode;
	bool isCubeInitialized;     //�Ƿ���Ҫ��������Ľǵ���������ʼ������
	POINT m_startPoint;//ǰ��
	POINT m_endPoint;  //���

	bool m_bIsMouseDown;//����Ƿ����ƶ�

	list<MYPOINT> m_listpoint;

	int m_iPenWidth;  //���ʿ��
	long m_lPenColor; //������ɫ
	long m_lBkColor;  //������ɫ
	long m_lFillColor;//�����ɫ

	afx_msg void OnPolygon();
	afx_msg void OnDrawpolygon();
	afx_msg void OnDrawline();
	// //��ֱ�ߵ�ִ�к���(Bresenham�㷨)
	void DrawLine(POINT p1, POINT p2, CDC* pDC);
	// ��Բ��ʵ���㷨(Bres�㷨)
	void DrawCircle(POINT pc, int r, CDC* pDC);
	// ��Բ�㷨�ĸ����Ӻ���
	void CirPort(int x0, int y0, int x, int y, CDC* pDC);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	int beflag;
	int xzflag;
	CTypedPtrList<CObList, CSharp*> m_sharpList;
	CTypedPtrList<CObList,CFill*> m_fillList;
	CBeizer *beizerItem;
	int GetDist(POINT p1, POINT p2);
	void DrawFill(CPoint point, CDC* pDC);
	void Seedfill(int x, int y, int oldcolor, int newcolor, CDC* pDC);
	void Fill(CPoint point, CDC* pDC);
	// ��䷽ʽ
	FILLTYPE m_FillType;
	afx_msg void OnDrawline2();
	afx_msg void OnFillpolygon();
	afx_msg void OnChoosecolor();
	afx_msg void OnPencolor();
	afx_msg void OnNumberfill();
	// ʹ�ñ߱�Ķ����ɨ��ת���㷨
	void Polygonfill(CDC* pDC, CArray<CPoint, CPoint>* points, COLORREF color);
	// �߱�ET������
	void SortET(EDGE* pEDGE);
	// ��Ծ�߱�AET��������
	void SortAET(EDGE* pEDGE);
	// ��ȡ�߱�
	EDGE* GetET(CArray <CPoint, CPoint>* points);
	// �����ص㲢���˵�����ƽ��������ĵ�
	void setPixel(CDC* pDC, int x, int y, COLORREF color);
	// �������ص�ķ������γ�ָ��������ַ�
	void setnumberlinepixel(CDC* pDC, int i, int xetrl, int xl, int xr, int y, COLORREF color);
	afx_msg void OnDefaultmouse();
	// �ͻ��˽���Ĵ��ڳߴ�
	int cxClient;
	int cyClient;
	ThPoint points[8];
	ThPoint cpoints[8];
		
	void TransPointToMarix(ThPoint & tp, double a[1][4]);

	void TransMarixToPoint(double  a[1][4], ThPoint & tp);
	// �������ƽ���㷨
	void MoveTrans(double x, double y, double z);

	void MutiTransMarix(double a[1][4], double b[4][4], double MutiResult[1][4]);
	// �������б��ͶӰ�㷨(����ά����ת��Ϊ��ά����Ļ��ʾ)
	void ShadowTrans(int degree);
	// ��������ת�㷨,��ת���Ŀ�����x,y��z��,degree��ת�Ķ���,rc��ת����	
	void RotateTrans(double degree, CString rc);

	// ������ı����任�㷨
	void BigerOrSmallerTrans(double timeX, double timeY, double timeZ);

	// ͸��ͶӰ(Perspective projection)
	void PerspectivePROJ();

	afx_msg void OnSize(UINT nType, int cx, int cy);

	afx_msg void OnBgsm();

	afx_msg void OnMovecube();

	afx_msg void OnRotatecube();
	// �����������ʼ��
	void InitPoints();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnDrawcube();
	afx_msg void OnCubet();
	afx_msg void OnCubex();
	// ����û���������߿��Ƶ�
	vector<CPoint> m_vInputPoint;
	// ��ſ��ƶ��㣨���ʱ�ã�
	vector<CPoint> m_vControlPoint;
	// ����ø�˹��Ԫ��������ʱ��ϵ�������ʱ�ã�
	vector<double> m_vXiShu;
	// �ƶ����ĵĵ�,�����û�Ԥ��������״
	CPoint m_cMovePoint;
	// �û��Ƿ�ѡ��Ӧ��
	bool m_bIsChoosed;
	// �û��Ƿ�ֹͣ��ͼ�������Ҽ���
	bool m_bStopDraw;
	// �û��Ƿ�ѡ�п��ƶ���
	bool m_bPointChoosed;
	// ��ֹͣ��ͼ���ƶ�ѡ�п��ƵĶ���ʱ
	bool m_bMakeSure;
	// ��ѡ��Ҫ�ƶ��Ŀ��ƶ�����ջ�е�λ��
	int m_iItemOfEditPoint;
	// �û�ѡ���Ӧ������
	ChooseType m_eChooseType;
	// ��¼��ǰ���״̬
	MouseStatus m_eMouseStatus;
	// ��ǰ���ڵ�������Ϣ
	RECT rect;
	afx_msg void OnBezier();
	afx_msg void OnBsize();
	// �������ξ���B��������
	void DrawB(CDC* pDC, CPoint point1, CPoint point2, CPoint point3, CPoint point4);
	// ����Bezier����
	void DrawBezier(CDC* pDC);
	// ��׳�
	int JieCheng(int n);
	// �������
	double C(int n, int i);
	// ��һ����u��n�η�
	double N(double u, int n);
	// �жϵ��Ƿ��ڿ��ƶ���
	void PointOnInputPoint(CPoint CheckedPoint);
	afx_msg void OnReset();
};

#ifndef _DEBUG  // CGwork0218View.cpp �еĵ��԰汾
inline CCGwork0218Doc* CCGwork0218View::GetDocument() const
   { return reinterpret_cast<CCGwork0218Doc*>(m_pDocument); }
#endif

