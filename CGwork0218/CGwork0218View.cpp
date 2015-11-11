
// CGwork0218View.cpp : CCGwork0218View ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "CGwork0218.h"
#endif
#include "MainFrm.h"
#include "CGwork0218Doc.h"
#include "CGwork0218View.h"
#include "DlgRotate.h"
#include <math.h>
#include "Sharp.h"
#include "Line.h"
#include"Fill.h"
#include"Circle.h"
#include "MoveDialog.h"
#include"BGSMDialog.h"
#include"MoveCubeDialog.h"
#include"RoateCubeDialog.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCGwork0218View

IMPLEMENT_DYNCREATE(CCGwork0218View, CView)

BEGIN_MESSAGE_MAP(CCGwork0218View, CView)

	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_SETCURSOR()
	ON_COMMAND(ID_Move, &CCGwork0218View::OnMove)
	ON_COMMAND(ID_Rotate, &CCGwork0218View::OnRotate)
	ON_COMMAND(ID_Fill, &CCGwork0218View::OnFill)
	ON_COMMAND(ID_Polygon, &CCGwork0218View::OnPolygon)
	ON_COMMAND(ID_DrawPolygon, &CCGwork0218View::OnDrawpolygon)
	ON_COMMAND(ID_DrawLine, &CCGwork0218View::OnDrawline)
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_DrawLine2, &CCGwork0218View::OnDrawline2)
	ON_COMMAND(ID_FillPolygon, &CCGwork0218View::OnFillpolygon)
	ON_COMMAND(ID_ChooseColor, &CCGwork0218View::OnChoosecolor)
	ON_COMMAND(ID_PenColor, &CCGwork0218View::OnPencolor)
	ON_COMMAND(ID_NumberFill, &CCGwork0218View::OnNumberfill)
	ON_COMMAND(ID_DefaultMouse, &CCGwork0218View::OnDefaultmouse)
	ON_WM_SIZE()
	ON_COMMAND(ID_BGSM, &CCGwork0218View::OnBgsm)
	ON_COMMAND(ID_MoveCube, &CCGwork0218View::OnMovecube)
	ON_COMMAND(ID_RotateCube, &CCGwork0218View::OnRotatecube)
	ON_WM_KEYDOWN()
	ON_WM_CHAR()
	ON_COMMAND(ID_DrawCube, &CCGwork0218View::OnDrawcube)
	ON_COMMAND(ID_CubeT, &CCGwork0218View::OnCubet)
	ON_COMMAND(ID_CubeX, &CCGwork0218View::OnCubex)
	ON_COMMAND(ID_Bezier, &CCGwork0218View::OnBezier)
	ON_COMMAND(ID_BSize, &CCGwork0218View::OnBsize)
	ON_COMMAND(ID_Reset, &CCGwork0218View::OnReset)
END_MESSAGE_MAP()

// CCGwork0218View ����/����

CCGwork0218View::CCGwork0218View()
: bDrawMark(false)
, bMoveMark(false)
, MoveStart((0,0))
, MoveEnd((0,0))
, bRotateMark(false)
, RotateBase((0,0))
, bFillMark(false)
, ptNum(1)
, RotateAngle(0.0)
, m_bDrawMode(false)
, beflag(0)
, xzflag(0)
, beizerItem(NULL)
, cxClient(0)
, cyClient(0)
, m_cMovePoint(0)
, m_bIsChoosed(false)
, m_bStopDraw(false)
, m_bPointChoosed(false)
, m_bMakeSure(false)
, m_iItemOfEditPoint(0)
{
	// TODO:  �ڴ˴���ӹ������
	m_dsDrawSort = DsNull;
	m_startPoint.x = 0;
	m_startPoint.y = 0;
	m_endPoint.x = 0;
	m_endPoint.y = 0;
	m_bIsMouseDown = 0;

	m_lPenColor = RGB(0, 0, 255);
	m_iPenWidth = 1;
	m_lBkColor = RGB(255, 255, 255);
	m_lFillColor = RGB(255, 0, 0);

	m_LineType = BRDL;
	m_CircleType = MDC;
	m_FillType = EXTFLOODFILL;
	m_proFunc = TOUSHI;
	m_bDrawMode = true;
	isCubeInitialized = true;
}

CCGwork0218View::~CCGwork0218View()
{
}

BOOL CCGwork0218View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CCGwork0218View ����

void CCGwork0218View::OnDraw(CDC* pDC)
{
	CCGwork0218Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  �ڴ˴�Ϊ����������ӻ��ƴ���

	if (m_dsDrawSort == DsPolygon){                      //==========����Ǿ��λ���ģʽ
		int size = pDoc->PointArray.GetSize();
		if (size<3)//��������С��3ʱ�������õĵ�
		{
			pDoc->PointArray.RemoveAll();
		}
		else//������������3ʱ�����û�ֱ�߷�ʽ���ƶ����
		{
			pDC->MoveTo(pDoc->PointArray[0]);
			for (int i = 0; i<size; i++)
			{
				pDC->LineTo(pDoc->PointArray[i]);
			}
			pDC->LineTo(pDoc->PointArray[0]);
		}
	}
	
	//if (xzflag == 1)
	//{
		//CRect rect;
		//this->GetClientRect(&rect);
		//pDC->SetMapMode(MM_ANISOTROPIC);
		//pDC->SetViewportOrg(rect.right / 2, rect.bottom / 2);
		//pDC->SetViewportExt(rect.right, rect.bottom);
		//pDC->SetWindowOrg(0, 0);
		//pDC->SetWindowExt((rect.right - rect.left), (rect.top - rect.bottom));
		//pDC->MoveTo(0, 0);
		//pDC->LineTo(0, rect.top - rect.bottom);
		//pDC->MoveTo(0, 0);
		//pDC->LineTo(0, rect.bottom - rect.top);
		//pDC->MoveTo(0, 0);
		//pDC->LineTo(rect.right - rect.left, 0);
		//pDC->LineTo(rect.left - rect.right, 0);
	//}
	POSITION pos = m_sharpList.GetHeadPosition();
	if (m_dsDrawSort == DsLine){
		while (pos != NULL)//====================================�����ֱ�߻���ģʽ
		{
			CSharp* pSharp = m_sharpList.GetNext(pos);
			pSharp->DrawSharp(pDC);
		}
	}
	pos = m_fillList.GetHeadPosition();
	while (pos != NULL)//ֱ��Χ�ɵĶ���ε�����ػ�
	{
		CFill* pFill = m_fillList.GetNext(pos);
		pFill->DrawFill(pDC);

	}
	if (m_dsDrawSort == DsCube){//===============����������廭��ģʽ,Ϊ���������ö������ػ溯��
		if (isCubeInitialized == true)
		{
			InitPoints();
			isCubeInitialized = false;
		}
		ASSERT_VALID(pDoc);
		if (!pDoc)
			return;
		// TODO:  �ڴ˴�Ϊ����������ӻ��ƴ���
		ASSERT_VALID(pDoc);
		HBRUSH hbrush;
		CPen pen;
		HPEN hPen;
		// TODO: add draw code for native data here
		pen.CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
		hPen = (HPEN)pDC->SelectObject(pen);
		pDC->SetViewportOrg(cxClient / 2, cyClient / 2);
		//��������
		pDC->MoveTo(-cxClient / 2, 0);
		pDC->LineTo(cxClient / 2, 0);
		pDC->MoveTo(0, -cyClient / 2);
		pDC->LineTo(0, cyClient / 2);
		pen.DeleteObject();
		pDC->SelectObject(hPen);
		//ѡ��ͶӰ����
		if (m_proFunc==TOUSHI)
		{
			this->PerspectivePROJ();
		}
		else{
			this->ShadowTrans(-45);
		}
		for (int i = 0; i<4; i++)//����������
		{
			pDC->MoveTo(cpoints[i].x, cpoints[i].y);
			pDC->LineTo(cpoints[i + 4].x, cpoints[i + 4].y);
		}
		hbrush = (HBRUSH)pDC->SelectObject(GetStockObject(NULL_BRUSH));
		//Զ��������
		POINT front[5];
		POINT back[5];
		for (int i = 0; i < 4; i++)
		{
			front[i].x = cpoints[i].x;
			front[i].y = cpoints[i].y;
			back[i].x = cpoints[i + 4].x;
			back[i].y = cpoints[i + 4].y;
		}
		pDC->Polygon(front, 4);
		pDC->Polygon(back, 4);
	}
	if (m_dsDrawSort == DsBezier||m_dsDrawSort == DsBsize)//��������߻���ģʽ
	{
		GetClientRect(&rect);

		if (m_eMouseStatus == MouseMove&&m_bStopDraw == false)
		{
			m_vInputPoint.push_back(m_cMovePoint);
		}

		CString str;
		CClientDC d(this);

		int i;

		if (m_bIsChoosed == true)
		{
			//if (m_bStopDraw == false)//������ֵ���������
			//{
			//	str.Format(_T("  X = %d, y = %d "), m_cMovePoint.x, m_cMovePoint.y);
				//d.TextOut(m_cMovePoint.x + 10, m_cMovePoint.y + 10, str);
			//}

			//�ж��û�ѡ���Ӧ������,������Ӧ�Ĵ���
			switch (m_eChooseType) {
			case Bezier:
				str.Format(_T("Bezier����"));
				d.TextOut(200, 10, str);
				for (i = 0; i<m_vInputPoint.size(); i++)
				{
					pDC->Ellipse(m_vInputPoint[i].x - 4, m_vInputPoint[i].y - 4,
						m_vInputPoint[i].x + 4, m_vInputPoint[i].y + 4);
				}
				DrawBezier(pDC);
				break;
			case BYangTiao:
				str.Format(_T("B��������"));
				d.TextOut(200, 10, str);
				if (m_vInputPoint.size() >= 4)
				{
					for (i = 0; i<m_vInputPoint.size(); i++)
					{
						pDC->Ellipse(m_vInputPoint[i].x - 4, m_vInputPoint[i].y - 4,
							m_vInputPoint[i].x + 4, m_vInputPoint[i].y + 4);
					}
					for (i = 0; i<m_vInputPoint.size() - 3; i++)
					{
						DrawB(pDC, m_vInputPoint[i], m_vInputPoint[i + 1],
							m_vInputPoint[i + 2], m_vInputPoint[i + 3]);
					}
				}
				break;
			}
		}
		if (m_eMouseStatus == MouseMove&&m_bStopDraw == false)
		{
			m_vInputPoint.pop_back();
		}
	}
}

// CCGwork0218View ���

#ifdef _DEBUG
void CCGwork0218View::AssertValid() const
{
	CView::AssertValid();
}

void CCGwork0218View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCGwork0218Doc* CCGwork0218View::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCGwork0218Doc)));
	return (CCGwork0218Doc*)m_pDocument;
}
#endif //_DEBUG

///////////////////////////////////////////////////////////////////////////////////////////////////////////
// CCGwork0218View ��Ϣ�������============================================================================
///////////////////////////////////////////////////////////////////////////////////////////////////////////


//�������,������ѡ�Ĺ��ܲ�ͬ,ʵ�ֲ�ͬ�Ĵ���
void CCGwork0218View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ

	m_bIsMouseDown = 1;
	CView::OnLButtonDown(nFlags, point);
	if (m_dsDrawSort == DsNull){             //===============��û��ѡ���κλ���ʱ
		return;
	}
		
	if (m_dsDrawSort == DsLine)                                //================�����߱�־Ϊ��ʱ
	{
		m_endPoint.x = m_startPoint.x = point.x;
		m_endPoint.y = m_startPoint.y = point.y;
	}
	
	if (m_dsDrawSort == DsPolygon)					//================��������α�־Ϊ��ʱ
	{
		CClientDC dc(this);
		CRect rect(point.x - 2, point.y - 2, point.x + 2, point.y + 2);
		CBrush brush(RGB(0, 0, 0));
		CBrush *pOldBrush = dc.SelectObject(&brush);
		dc.Rectangle(rect);			//������ѡ��Ϊ���ĵ�С���α�ʾһ����
		dc.SelectObject(pOldBrush);
		CCGwork0218Doc* pDoc = GetDocument();
		pDoc->PointArray.Add(point);//����ѡ����뼯�϶���
	}
	if (m_dsDrawSort == DsMovePolygon)				   //=================�������ƽ�Ʊ�־Ϊ��ʱ
	{
		if (ptNum == 1)				//��ƽ�Ƶ����Ϊ1ʱ
		{
			CClientDC dc(this);
			CRect rect(point.x - 2, point.y - 2, point.x + 2, point.y + 2);
			CBrush brush(RGB(0, 0, 0));
			CBrush *pOldBrush = dc.SelectObject(&brush);
			dc.Rectangle(rect);		//������ѡ��Ϊ���ĵ�С����
			dc.SelectObject(pOldBrush);
			MoveStart = point;		//����ѡ�㸳ֵ��ƽ�����
			ptNum++;				//ƽ�Ƶ������1
		}
		else						//��ƽ�Ƶ����Ϊ2ʱ
		{
			CClientDC dc(this);
			CRect rect(point.x - 2, point.y - 2, point.x + 2, point.y + 2);
			CBrush brush(RGB(0, 0, 0));
			CBrush *pOldBrush = dc.SelectObject(&brush);
			dc.Rectangle(rect);		//������ѡ��Ϊ���ĵ�С����
			dc.SelectObject(pOldBrush);
			MoveEnd = point;			//����ѡ�㸳ֵ��ƽ���յ�
			ptNum = 1;				//��ƽ�Ƶ������ֵΪ1��ʵ��ƽ��ѭ��
		}
	}
	if (m_dsDrawSort == DsRotatePolygon)				//=================���������ת��־Ϊ��ʱ
	{
		m_dsDrawSort = DsNull;
		CClientDC dc(this);
		CRect rect(point.x - 2, point.y - 2, point.x + 2, point.y + 2);
		CBrush brush(RGB(0, 0, 0));
		CBrush *pOldBrush = dc.SelectObject(&brush);
		dc.Rectangle(rect);		//������ѡ��Ϊ���ĵ�С����
		dc.SelectObject(pOldBrush);
		RotateBase = point;	//����ѡ�㸳ֵ����ת����
	}
	if (m_dsDrawSort == DsFill2)					//==================�����������־Ϊ��ʱ
	{
		m_dsDrawSort = DsNull;//�����������־��Ϊ�٣�ʹ������ִֻ��һ��
		Fill();		//���ö������亯��
	}
	if (m_dsDrawSort == DsBezier||m_dsDrawSort == DsBsize)//================���������߱�־Ϊ��ʱ
	{
		m_eMouseStatus = LButtonDown;
		if (m_bIsChoosed == true)
		{
			if (m_bStopDraw == false)
			{
				m_vInputPoint.push_back(point);
				InvalidateRect(&rect);
			}
			else
			{
				if (m_eChooseType != NHBYangTiao)
				{
					PointOnInputPoint(point);
					if (m_bPointChoosed)
					{
						m_vInputPoint[m_iItemOfEditPoint] = point;
						m_bMakeSure = !m_bMakeSure;
					}
				}
			}
		}

		CView::OnLButtonDown(nFlags, point);
	}
}

//�����Ҽ�,������ѡ�Ĺ��ܲ�ͬ,ʵ�ֲ�ͬ�Ĵ���
void CCGwork0218View::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (bDrawMark = TRUE)						//��������α�־Ϊ��ʱ
	{
		bDrawMark = FALSE;					//��������α�־��Ϊ�٣�ʹ����һ�ִֻ��һ��
		Invalidate();						//����OnDraw()����
	}
	if (bMoveMark == TRUE)						//�������ƽ�Ʊ�־Ϊ��ʱ
	{
		bMoveMark = FALSE;					//�������ƽ�Ʊ�־��Ϊ�٣�ʹ����һ�ִֻ��һ��
		Move(MoveStart, MoveEnd);			//���ö����ƽ�ƺ���
		Invalidate();						//����OnDraw()����
	}
	if (bRotateMark == TRUE)					//���������ת��־Ϊ��ʱ
	{
		bRotateMark = FALSE;					//���������ת��־��Ϊ�٣�ʹ����һ�ִֻ��һ��
		DlgRotate dlg;
		if (dlg.DoModal() == IDOK)				//������ת�Ի����趨��ת�Ƕȣ����ö������ת����
		{
			RotateAngle = dlg.m_RotateAngle;
			Rotate(RotateBase, RotateAngle);
		}
		Invalidate();						//����OnDraw()����
	}
	if (m_dsDrawSort == DsBezier || m_dsDrawSort == DsBsize){//�������ߺ���Ϊ���ʱ��
		m_eMouseStatus = RButtonDown;
		m_bStopDraw = true;
		InvalidateRect(&rect);
	}
	CView::OnRButtonDown(nFlags, point);
}

//����ƶ�
void CCGwork0218View::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CMainFrame* pMnFrm = (CMainFrame*)AfxGetMainWnd();
	CString str;
	str.Format(_T("X=%d,Y=%d"),point.x,point.y);//��״̬����ʾ���λ��
	CStatusBar* pSttb = &(pMnFrm->m_wndStatusBar);
	CRect rect;
	GetClientRect(rect);
	pSttb->SetPaneInfo(1, ID_SEPARATOR, SBPS_NORMAL, rect.Width() / 7);
	pSttb->SetPaneText(1, str);

	//====================================================================
	CDC *pDC = GetDC();
	if (m_dsDrawSort == DsNull)
		return;
	if (!m_bIsMouseDown&&m_dsDrawSort != DsBezier&&m_dsDrawSort != DsBsize)
		return;
	pDC->SetROP2(R2_NOTXORPEN);
	switch (m_dsDrawSort)
	{
	case DsLine://��ֱ��
		DrawLine(m_startPoint, m_endPoint, pDC);
		DrawLine(m_startPoint, point, pDC);
		break;
	case DsBezier://������
	case DsBsize:
		m_cMovePoint = point;
		m_eMouseStatus = MouseMove;
		if (m_bStopDraw == true)
		{
			if (m_bPointChoosed == true && m_bMakeSure == false)
			{
				m_vInputPoint[m_iItemOfEditPoint].x = point.x;
				m_vInputPoint[m_iItemOfEditPoint].y = point.y;
				InvalidateRect(&rect);
			}
			return;
		}
		InvalidateRect(&rect);
		break;
	}
	m_endPoint = point;
	//===================================================================
	CView::OnMouseMove(nFlags, point);
}

//̧�����
void CCGwork0218View::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	m_bIsMouseDown = 0;
	if (m_dsDrawSort == DsNull)
		return;

	CDC *pDC = GetDC();
	switch (m_dsDrawSort)
	{
		case DsLine:
		{
			DrawLine(m_startPoint, point, GetDC());
			CLine* pLineItem = new CLine();
			pLineItem->startpoint = m_startPoint;
			pLineItem->endpoint = point;
			pLineItem->m_lPenColor = this->m_lPenColor;
			m_sharpList.AddTail(pLineItem);
			break;
		}
		case DsFill:
		{
			 CFill *fillItem = new CFill();
			 fillItem->fillPoint = point;
			 fillItem->m_lFillColor = m_lFillColor;
			 m_listpoint.clear();
			 DrawFill(point, pDC);
			 m_fillList.AddTail(fillItem);
		     break;
		}
	}
	CView::OnLButtonUp(nFlags, point);
}

//������
BOOL CCGwork0218View::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (bDrawMark == TRUE)									//��������α�־Ϊ��ʱ����ʾ���ʹ��
	{
		::SetCursor(DrawCur);
		return TRUE;
	}
	else												//��������α�־Ϊ��ʱ����ʾ��ͼ��Ĭ�Ϲ��
	{
		return CView::OnSetCursor(pWnd, nHitTest, message);
	}

	return CView::OnSetCursor(pWnd, nHitTest, message);
}

/*==========================================================================================================*/
// ������->Ĭ�����ָ��
void CCGwork0218View::OnDefaultmouse()
{
	// TODO:  �ڴ���������������
	m_dsDrawSort = DsNull;
}

// ������->���ƶ����
void CCGwork0218View::OnPolygon()
{
	// TODO:  �ڴ���������������
	m_dsDrawSort = DsPolygon;
	DrawCur = AfxGetApp()->LoadCursor(IDC_DRAWCUR);		//���ػ��ʹ��
	bDrawMark = TRUE;										//������α�־��Ϊ�棬ʵ����Ӧ�������Ӧ����
	bMoveMark = FALSE;
	bRotateMark = FALSE;
	bFillMark = FALSE;
	CCGwork0218Doc* pDoc = GetDocument();
	pDoc->PointArray.RemoveAll();
}

// �˵���->���ƶ����
void CCGwork0218View::OnDrawpolygon()
{
	// TODO:  �ڴ���������������
	DrawCur = AfxGetApp()->LoadCursor(IDC_DRAWCUR);		//���ػ��ʹ��
	bDrawMark = TRUE;										//������α�־��Ϊ�棬ʵ����Ӧ�������Ӧ����
	bMoveMark = FALSE;
	bRotateMark = FALSE;
	bFillMark = FALSE;
	m_dsDrawSort = DsPolygon;
	CCGwork0218Doc* pDoc = GetDocument();
	pDoc->PointArray.RemoveAll();
}

// ������->�ƶ������
void CCGwork0218View::OnMove()
{
	// TODO:  �ڴ���������������
	bMoveMark = TRUE;										//�����ƽ�Ʊ�־��Ϊ�棬ʵ����Ӧ�������Ӧ����
	bDrawMark = FALSE;
	bRotateMark = FALSE;
	bFillMark = FALSE;
	m_dsDrawSort = DsMovePolygon;
}

// ������->��ת�����
void CCGwork0218View::OnRotate()
{
	// TODO:  �ڴ���������������
	bRotateMark = TRUE;									//�������ת��־��Ϊ�棬ʵ����Ӧ�������Ӧ����
	bDrawMark = FALSE;
	bMoveMark = FALSE;
	bFillMark = FALSE;
	m_dsDrawSort = DsRotatePolygon;
}

// ������->�������
void CCGwork0218View::OnFill()
{
	// TODO:  �ڴ���������������
	bFillMark = TRUE;									//���������־��Ϊ�棬ʵ����Ӧ�������Ӧ����
	bDrawMark = FALSE;
	bMoveMark = FALSE;
	bRotateMark = FALSE;
	m_dsDrawSort = DsFill2;
}

// �˵�->����ֱ��
void CCGwork0218View::OnDrawline()
{
	// TODO:  �ڴ���������������
	//����:��������˵���֮��,�л�Ϊ����ģʽ,ֻ��Ҫ�϶����,���ܻ�����
	if (m_bDrawMode)
	{
		if (m_dsDrawSort != DsLine)
		{
			m_dsDrawSort = DsLine;
		}
		else
			m_dsDrawSort = DsNull;
		m_bIsMouseDown = 0;
	}
}

// ������->����ֱ��
void CCGwork0218View::OnDrawline2()
{
	// TODO:  �ڴ���������������
	//����:��������˵���֮��,�л�Ϊ����ģʽ,ֻ��Ҫ�϶����,���ܻ�����
	if (m_bDrawMode)
	{
		if (m_dsDrawSort != DsLine)
		{
			m_dsDrawSort = DsLine;
		}
		else
			m_dsDrawSort = DsNull;
		m_bIsMouseDown = 0;
	}
}

// �˵�->�������
void CCGwork0218View::OnFillpolygon()
{
	// TODO:  �ڴ���������������
	if (m_dsDrawSort != DsFill)
	{
		m_dsDrawSort = DsFill;
	}
}

// �˵�->ѡ�������ɫ
void CCGwork0218View::OnChoosecolor()
{
	// TODO:  �ڴ���������������
	CColorDialog dlg;
	if (dlg.DoModal())//���ù�����ɫ�Ի���
	{
		m_lFillColor = dlg.GetColor();//����ѡ��ɫ��ֵ����ǰ�����ɫ

	}
}

// �˵�->ѡ�񻭱���ɫ
void CCGwork0218View::OnPencolor()
{
	// TODO:  �ڴ���������������
	CColorDialog dlg;
	if (dlg.DoModal())//���ù�����ɫ�Ի���
	{
		m_lPenColor = dlg.GetColor();//����ѡ��ɫ��ֵ����ǰ������ɫ

	}
}

// �˵�->ѧ���������
void CCGwork0218View::OnNumberfill()
{
	// TODO:  �ڴ���������������
	CCGwork0218Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (pDoc->PointArray.GetSize() >= 3){
		Polygonfill(this->GetDC(), &(pDoc->PointArray), m_lFillColor);
	}
	
}

// �����ƽ�Ƶ�ʵ�ֺ���
void CCGwork0218View::Move(CPoint start, CPoint end)
{
	int XInc = end.x - start.x;
	int YInc = end.y - start.y;
	CCGwork0218Doc* pDoc = GetDocument();
	int size = pDoc->PointArray.GetSize();
	for (int i = 0; i<size; i++)
	{
		pDoc->PointArray[i].x = pDoc->PointArray[i].x + XInc;
		pDoc->PointArray[i].y = pDoc->PointArray[i].y + YInc;
	}
}

// �������ת��ʵ�ֺ���
void CCGwork0218View::Rotate(CPoint ptBase, double angle)
{
	angle = 3.1415926*angle / 180;
	CCGwork0218Doc* pDoc = GetDocument();
	int size = pDoc->PointArray.GetSize();
	for (int i = 0; i<size; i++)
	{
		int XInc = pDoc->PointArray[i].x - ptBase.x;
		int YInc = pDoc->PointArray[i].y - ptBase.y;
		pDoc->PointArray[i].x = ptBase.x + (int)(XInc*cos(angle) + YInc*sin(angle) + 0.5);
		pDoc->PointArray[i].y = ptBase.y + (int)(YInc*cos(angle) - XInc*sin(angle) + 0.5);
	}
}

// ��ֱ�ߵ�ʵ�ֺ���(Bresenham�㷨)
void CCGwork0218View::DrawLine(POINT p1, POINT p2, CDC* pDC)
{
	int i;

	if (p1.x == p2.x)
	{
		//Ϊ����
		if (p1.y <= p2.y)
		{
			for (i = p1.y; i <= p2.y; i++)
				pDC->SetPixel(p1.x, i, m_lPenColor);
		}
		else
		{
			for (i = p2.y; i <= p1.y; i++)
				pDC->SetPixel(p1.x, i, m_lPenColor);
		}

		return;
	}

	//Ϊ����
	if (p1.y == p2.y)
	{
		if (p1.x <= p2.x)
		{
			for (i = p1.x; i <= p2.x; i++)
				pDC->SetPixel(i, p1.y, m_lPenColor);
		}
		else
		{
			for (i = p2.x; i <= p1.x; i++)
				pDC->SetPixel(i, p1.y, m_lPenColor);
		}

		return;
	}

	//Ϊб��
	float m = (p2.y - p1.y)*1.0 / (p2.x - p1.x);
	float p;

	p = 2 * m - 1;
	if (m>0 && m <= 1)
	{
		if (p1.x<p2.x)
		{
			while (p1.x <= p2.x)
			{
				pDC->SetPixel(p1.x++, p1.y, m_lPenColor);
				if (p >= 0)
				{
					p += 2 * m - 2;
					p1.y++;
				}
				else
					p += 2 * m;
			}
		}
		else
		{
			while (p2.x <= p1.x)
			{
				pDC->SetPixel(p2.x++, p2.y, m_lPenColor);
				if (p >= 0)
				{
					p += 2 * m - 2;
					p2.y++;
				}
				else
					p += 2 * m;
			}
		}

		return;
	}

	p = -2 * m - 1;
	if (m<0 && m >= -1)
	{
		if (p1.x<p2.x)
		{
			while (p1.x <= p2.x)
			{
				pDC->SetPixel(p1.x++, p1.y, m_lPenColor);
				if (p >= 0)
				{
					p += -2 * m - 2;
					p1.y--;
				}
				else
					p += -2 * m;
			}
		}
		else
		{
			while (p2.x <= p1.x)
			{
				pDC->SetPixel(p2.x++, p2.y, m_lPenColor);
				if (p >= 0)
				{
					p += -2 * m - 2;
					p2.y--;
				}
				else
					p += -2 * m;
			}
		}

		return;
	}

	p = 2 / m - 1;
	if (m>1)
	{
		if (p1.y<p2.y)
		{
			while (p1.y <= p2.y)
			{
				pDC->SetPixel(p1.x, p1.y++, m_lPenColor);
				if (p >= 0)
				{
					p += 2 / m - 2;
					p1.x++;
				}
				else
					p += 2 / m;
			}
		}
		else
		{
			while (p2.y <= p1.y)
			{
				pDC->SetPixel(p2.x, p2.y++, m_lPenColor);
				if (p >= 0)
				{
					p += 2 / m - 2;
					p2.x++;
				}
				else
					p += 2 / m;
			}
		}

		return;
	}

	p = -2 / m - 1;
	if (p1.y<p2.y)
	{
		while (p1.y <= p2.y)
		{
			pDC->SetPixel(p1.x, p1.y++, m_lPenColor);
			if (p >= 0)
			{
				p += -2 / m - 2;
				p1.x--;
			}
			else
				p += -2 / m;
		}
	}
	else
	{
		while (p2.y <= p1.y)
		{
			pDC->SetPixel(p2.x, p2.y++, m_lPenColor);
			if (p >= 0)
			{
				p += -2 / m - 2;
				p2.x--;
			}
			else
				p += -2 / m;
		}
	}
}

// ����㷨����
void CCGwork0218View::DrawFill(CPoint point, CDC* pDC)
{
	switch (m_FillType)
	{
	case FEEDFILL:
		this->Seedfill(point.x, point.y, this->m_lPenColor, this->m_lFillColor, pDC);
		break;
	case EXTFLOODFILL:
		Fill(point, pDC);
		break;
	default:
		break;
	}
}

// ʵ�ֹ������ϵ���䰴������
void CCGwork0218View::Fill()
{
	CCGwork0218Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	int size = pDoc->PointArray.GetSize();
	CPoint *pt = new CPoint[size];
	for (int i = 0; i<size; i++)
	{
		pt[i] = pDoc->PointArray.GetAt(i);
	}
	CClientDC dc(this);
	CBrush brush(m_lFillColor);
	CBrush *pOldBrush = dc.SelectObject(&brush);
	dc.Polygon(pt, size);
	dc.SelectObject(pOldBrush);
	delete pt;
}

// �������
void CCGwork0218View::Seedfill(int x, int y, int oldcolor, int newcolor, CDC* pDC)
{
	//if (pDC->GetPixel(x, y) == oldcolor)
	if (pDC->GetPixel(x, y) != oldcolor&&pDC->GetPixel(x, y) != newcolor)
	{
		pDC->SetPixelV(x, y, newcolor);
		Seedfill(x, y + 1, oldcolor, newcolor, pDC);
		Seedfill(x, y - 1, oldcolor, newcolor, pDC);
		Seedfill(x - 1, y, oldcolor, newcolor, pDC);
		Seedfill(x + 1, y, oldcolor, newcolor, pDC);
	}
}

// �������
void CCGwork0218View::Fill(CPoint point, CDC* pDC)
{
	CBrush   brush(m_lFillColor), *pOldBrush;
	pOldBrush = (CBrush   *)pDC->SelectObject(&brush);
	long bkcolor = GetSysColor(COLOR_WINDOW);
	HDC h = ::GetDC(m_hWnd);//��ǰ���ڵľ��
	COLORREF clr = COLORREF(GetPixel(h, point.x, point.y));//��ȡ��ǰ�����ɫ
	pDC->ExtFloodFill(point.x, point.y, clr, FLOODFILLSURFACE);
	pDC->SelectObject(pOldBrush);
}

//==============================================ʹ�ñ߱�Ķ����ɨ��ת���㷨==============================================
// ִ�ж����ɨ��ת���㷨
void CCGwork0218View::Polygonfill(CDC* pDC, CArray<CPoint, CPoint>* points, COLORREF color)
{
	EDGE * pET = GetET(points);
	EDGE * pAET = NULL;
	int i = 0;//i �� �޶�ѭ���Ļ���10
	int xetrl;
	int y = pET->ymin;
	int ymax = pET->ymax;
	while (y<ymax)
	{
		while (pET != NULL&&pET->ymin == y)
		{
			EDGE * p = pET;
			pET = pET->next;
			p->next = NULL;
			if (pAET == NULL)
			{
				pAET = p;
			}
			else
			{
				pAET->next = p;
				p->pre = pAET;
				pAET = p;
			}
			if (ymax<pAET->ymax)
			{
				ymax = pAET->ymax;

			}
		}
		while (pAET->pre != NULL)
			pAET = pAET->pre;
		SortAET(pAET);
		EDGE* pFill = pAET;
		/*
		while (pFill!=NULL)
		{

		for(int i = (int) pFill->xmin  ;i<=(int)pFill->next->xmin;i++)
		{
		setPixel(pDC,i,y,color);         ///////////////////////////////////////////////
		}
		pFill=pFill->next->next;
		}
		*/
		while (pFill != NULL)
		{
			if (i == 10) i = 0;
			if (i == 0)xetrl = (int)pFill->xmin;
			setnumberlinepixel(pDC, i, xetrl, (int)pFill->xmin, (int)pFill->next->xmin, y, color);
			pFill = pFill->next->next;
			i++;
		}

		pFill = pAET;
		while (pFill != NULL)
		{
			if (pFill->ymax == y)
			{
				if (pFill->pre != NULL)
				{
					pFill->pre->next = pFill->next;
				}
				else
					pAET = pFill->next;
				if (pFill->next != NULL)
				{
					pFill->next->pre = pFill->pre;
				}
				EDGE* pdelet = pFill;
				pFill = pFill->next;
				delete pdelet;

			}
			else pFill = pFill->next;
		}
		if (pAET != NULL)
		{
			pFill = pAET;
			while (pFill != NULL)
			{
				pFill->xmin += pFill->fm;
				pFill = pFill->next;

			}
			SortAET(pAET);
			while
				(pAET->next != NULL)
			{
				pAET = pAET->next;
			}

		}
		y++;

	}
}

// �߱�ET������
void CCGwork0218View::SortET(EDGE* pEDGE)
{
	EDGE * p1 = pEDGE;
	EDGE* p2 = NULL;
	while (p1 != NULL)
	{
		p2 = p1->next;
		while (p2 != NULL)
		{
			if ((p2->ymin < p1->ymin) || ((p2->xmin <  p1->xmin) && (p2->ymin < p1->ymin)))
			{
				int cid;
				double cdd;
				cid = p1->ymax; p1->ymax = p2->ymax; p2->ymax = cid;
				cid = p1->ymin; p1->ymin = p2->ymin; p2->ymin = cid;
				cdd = p1->xmin; p1->xmin = p2->xmin; p2->xmin = cdd;
				cdd = p1->fm; p1->fm = p2->fm; p2->fm = cdd;
			}
			p2 = p2->next;
		}
		p1 = p1->next;
	}
}

// ��Ծ�߱�AET��������
void CCGwork0218View::SortAET(EDGE* pEDGE)
{
	EDGE * p1 = pEDGE;
	EDGE * p2 = NULL;
	while (p1 != NULL)
	{
		p2 = p1->next;
		while (p2 != NULL)
		{
			if (p1->xmin>p2->xmin)
			{
				int cid; double cdd;
				cid = p1->ymax; p1->ymax = p2->ymax; p2->ymax = cid;
				cid = p1->ymin; p1->ymin = p2->ymin; p2->ymin = cid;
				cdd = p1->xmin; p1->xmin = p2->xmin; p2->xmin = cdd;
				cdd = p1->fm; p1->fm = p2->fm; p2->fm = cdd;
			}
			p2 = p2->next;
		}
		p1 = p1->next;
	}
}

// ��ȡ�߱�
EDGE* CCGwork0218View::GetET(CArray <CPoint, CPoint>* points)
{
	EDGE * pHead = NULL;
	EDGE * p = NULL;
	for (int i = 0; i<points->GetSize(); i++)
	{
		CPoint point1 = (CPoint)points->GetAt(i);
		CPoint point2;//=(CPoint)points->GetAt(i+1);

		if (i == points->GetSize() - 1)
		{
			point2 = (CPoint)points->GetAt(0);

		}
		else{ point2 = (CPoint)points->GetAt(i + 1); }
		if (point1.y == point2.y)
			continue;
		EDGE* edge = new EDGE();
		edge->fm = (double)(point2.x - point1.x) / (point2.y - point1.y);
		if (point1.y>point2.y)
		{
			edge->ymax = point1.y;
			edge->ymin = point2.y;
			edge->xmin = point2.x;
		}
		else
		{
			edge->ymax = point2.y;
			edge->ymin = point1.y;
			edge->xmin = point1.x;
		}
		edge->next = NULL;
		edge->pre = NULL;
		if (p == NULL)
		{
			pHead = edge;
			p = edge;

		}
		else
		{
			p->next = edge;
			edge->pre = p;
			p = edge;
		}
	}

	p = pHead;
	EDGE * pNext = NULL;
	while (p != NULL)
	{
		if (p->next == NULL)
		{
			pNext = pHead;
		}
		else
			pNext = p->next;
		if (p->ymin != pNext->ymin && p->ymax != pNext->ymax)
		{
			if (p->ymax>pNext->ymax)
			{
				p->ymin++;
				p->xmin += p->fm;
			}
			else{
				pNext->ymin++;
				pNext->xmin += pNext->fm;
			}

		}
		p = p->next;
	}
	SortET(pHead);
	return pHead;
}

// �����ص㲢���˵�����ƽ��������ĵ�
void CCGwork0218View::setPixel(CDC* pDC, int x, int y, COLORREF color)
{
	if (x % 10 == y % 10)
	{
		pDC->SetPixel(x, y, color);
	}
}

// �������ص�ķ������γ�ָ��������ַ�
void CCGwork0218View::setnumberlinepixel(CDC* pDC, int i, int xetrl, int xl, int xr, int y, COLORREF color)
{
	int j = 0;// ѭ������30 ���У�20/30 �������ֵı�ʾ
	int x = xetrl;
	while (x<xr)
	{
		if (j == 30){
			j = 0;
		}
		if (x>xl)
			switch (i)

		{
			case 0:
				if (j != 3 && j != 4 && j != 8 && j != 9 && j != 10 && j != 12 && j != 13 && j != 14 && j != 18 && j != 19 && j<20)
					pDC->SetPixel(x, y, color);
				break;
			case 1:
				if (j == 0 || j == 2 || j == 7 || j == 10 || j == 11 || j == 15 || j == 17)
					pDC->SetPixel(x, y, color);
				break;
			case 2:
				if (j != 1 && j != 3 && j != 4 && j != 8 && j != 9 && j != 10 && j != 12 && j != 13 && j != 14 && j != 18 && j != 19 && j<20)
					pDC->SetPixel(x, y, color);
				break;
			case 3:
				if (j == 0 || j == 2 || j == 5 || j == 11 || j == 15 || j == 17)
					pDC->SetPixel(x, y, color);
				break;
			case 4:
				if (j != 3 && j != 4 && j != 8 && j != 9 && j != 13 && j != 14 && j != 18 && j != 19 && j<20)
					pDC->SetPixel(x, y, color);
				break;
		}

		j++;
		x++;
	}
}
//====================================��������ƹ���========================================================================================

// ����ĳ˷�
void CCGwork0218View::MutiTransMarix(double a[1][4], double b[4][4], double MutiResult[1][4])
{
	for (int i = 0; i<4; i++) MutiResult[0][i] = 0;
	for (int i = 0; i<1; i++)
	for (int j = 0; j<4; j++)
	for (int k = 0; k<4; k++)
		MutiResult[i][j] += a[i][k] * b[k][j];
}

// ������ת��Ϊ������ʽ(����)
void CCGwork0218View::TransPointToMarix(ThPoint & tp, double a[1][4])
{
	a[0][0] = tp.x;
	a[0][1] = tp.y;
	a[0][2] = tp.z;
	a[0][3] = 1;
}

// ������(����)ת��Ϊ��ά������ʽ
void CCGwork0218View::TransMarixToPoint(double  a[1][4], ThPoint & tp)
{
	tp.x = a[0][0];
	tp.y = a[0][1];
	tp.z = a[0][2];
}

// �������ƽ���㷨
void CCGwork0218View::MoveTrans(double x, double y, double z)
{
	double a[8][4], result[1][4];
	double moveMarix[4][4] =
	{
		{ 1, 0, 0, 0 }, { 0, 1, 0, 0 },
		{ 0, 0, 1, 0 }, { x, y, z, 1 }
	};

	for (int i = 0; i<8; i++)
	{
		TransPointToMarix(points[i], a + i);
		MutiTransMarix(a + i, moveMarix, result);
		TransMarixToPoint(result, points[i]);
	}
	ShadowTrans(-45);
}

// �������б��ͶӰ�㷨(����ά����ת��Ϊ��ά����Ļ��ʾ)
void CCGwork0218View::ShadowTrans(int degree)
{
	double a[8][4], result[1][4];
	ThPoint pts[8];
	for (int i = 0; i<8; i++)
	{
		pts[i].x = points[i].x;
		pts[i].y = points[i].y;
		pts[i].z = points[i].z;
	}
	double shadowMarix[4][4] =
	{
		{ 1, 0, 0, 0 }, { 0, 1, 0, 0 },
		{ cos(degree), sin(degree), 0, 0 }, { 0, 0, 0, 1 }
	};

	for (int i = 0; i<8; i++)
	{
		TransPointToMarix(pts[i], a + i);
		MutiTransMarix(a + i, shadowMarix, result);
		TransMarixToPoint(result, pts[i]);
	}
	for (int i = 0; i<8; i++)
	{
		cpoints[i].x = (int)pts[i].x;
		cpoints[i].y = (int)pts[i].y;
	}
}

// ͸��ͶӰ(Perspective projection)
void CCGwork0218View::PerspectivePROJ()
{
	//��z=0ΪͶӰƽ��,����ʱ���õ���ͨ�������ϵ���������ϵ
	//�ڼ������ֵ��,���������任
	//����ͶӰ����
	double x0 = 140;
	double y0 = 140;
	double z0 = -140;
	double d = -z0;
	for (int i = 0; i < 8; i++)
	{
		cpoints[i].x = x0 + (d*(points[i].x - x0) / (points[i].z + d));
		cpoints[i].y = y0 + (d*(points[i].y - x0) / (points[i].z + d));
	}
}

// ��������ת�㷨,��ת���Ŀ�����x,y��z��,degree��ת�Ķ���,rc��ת����
void CCGwork0218View::RotateTrans(double degree, CString rc)
{
	double a[8][4], result[1][4];
	int i = 0;

	if (rc == "z")
	{
		double xRotateMarix[4][4] =
		{
			{ cos(degree*3.14 / 180), sin(degree*3.14 / 180), 0, 0 },
			{ -sin(degree*3.14 / 180), cos(degree*3.14 / 180), 0, 0 },
			{ 0, 0, 1, 0 }, { 0, 0, 0, 1 },
		};
		for (i = 0; i<8; i++)
		{
			TransPointToMarix(points[i], a + i);
			MutiTransMarix(a + i, xRotateMarix, result);
			TransMarixToPoint(result, points[i]);
		}
	}
	else if (rc == "x")
	{
		double yRotateMarix[4][4] =
		{
			{ 1, 0, 0, 0 },
			{ 0, cos(degree*3.14 / 180), sin(degree*3.14 / 180), 0 },
			{ 0, -sin(degree*3.14 / 180), cos(degree*3.14 / 180), 0 },
			{ 0, 0, 0, 1 }
		};
		for (int i = 0; i<8; i++)
		{
			TransPointToMarix(points[i], a + i);
			MutiTransMarix(a + i, yRotateMarix, result);
			TransMarixToPoint(result, points[i]);
		}

	}
	else if (rc == "y")
	{
		double zRotateMarix[4][4] =
		{
			{ cos(degree*3.14 / 180), 0, -sin(degree*3.14 / 180), 0 },
			{ 0, 1, 0, 0 },
			{ sin(degree*3.14 / 180), 0, cos(degree*3.14 / 180), 0 },
			{ 0, 0, 0, 1 }
		};
		for (i = 0; i<8; i++)
		{
			TransPointToMarix(points[i], a + i);
			MutiTransMarix(a + i, zRotateMarix, result);
			TransMarixToPoint(result, points[i]);
		}

	}
	ShadowTrans(-45);
}

// ������ı����任�㷨
void CCGwork0218View::BigerOrSmallerTrans(double timeX, double timeY, double timeZ)
{
	double a[8][4], result[1][4];
	double bsMarix[4][4] =
	{
		{ timeX, 0, 0, 0 }, { 0, timeY, 0, 0 },
		{ 0, 0, timeZ, 0 }, { 0, 0, 0, 1 }
	};
	for (int i = 0; i<8; i++)
	{
		TransPointToMarix(points[i], a + i);
		MutiTransMarix(a + i, bsMarix, result);
		TransMarixToPoint(result, points[i]);
	}
	ShadowTrans(-45);
}

// ��ȡ��ͼ����Ĵ�С
void CCGwork0218View::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO:  �ڴ˴������Ϣ����������
	cxClient = cx;
	cyClient = cy;
}

// ������->���Ź���
void CCGwork0218View::OnBgsm()
{
	// TODO:  �ڴ���������������
	BGSMDialog B_dlg;
	if (IDOK == B_dlg.DoModal())
	{
		BigerOrSmallerTrans(B_dlg.m_sx, B_dlg.m_sy, B_dlg.m_sz);
	}
	Invalidate();
	UpdateWindow();
}

// ������->ƽ�ƹ���
void CCGwork0218View::OnMovecube()
{
	// TODO:  �ڴ���������������
	MoveCubeDialog M_dlg;
	if (IDOK == M_dlg.DoModal())
	{
		MoveTrans(M_dlg.m_dx, M_dlg.m_dy, M_dlg.m_dz);
	}
	Invalidate();
	UpdateWindow();
}

// ������->��ת����
void CCGwork0218View::OnRotatecube()
{
	// TODO:  �ڴ���������������
	RoateCubeDialog BT_dlg;
	if (IDOK == BT_dlg.DoModal())
	{
		RotateTrans(BT_dlg.m_degree, BT_dlg.m_rc);
	}
	Invalidate();
	UpdateWindow();
}

// �����������ʼ��
void CCGwork0218View::InitPoints()
{
	int a = 100;//��ʼ�߳�
	//������Ļ����ϵ,z����������Ļ����
	points[0].x = 0; points[0].y = a; points[0].z = a;//0 a a
	points[1].x = a; points[1].y = a; points[1].z = a;//a a a 
	points[2].x = a; points[2].y = 0; points[2].z = a;//a 0 a
	points[3].x = 0; points[3].y = 0; points[3].z = a;//0 0 a
	points[4].x = 0; points[4].y = a; points[4].z = 0;//0 a 0
	points[5].x = a; points[5].y = a; points[5].z = 0;//a a 0
	points[6].x = a; points[6].y = 0; points[6].z = 0;//a 0 0
	points[7].x = 0; points[7].y = 0; points[7].z = 0;//0 0 0 
	
	cpoints[0].x = 0; cpoints[0].y = a; cpoints[0].z = a;//0 a a
	cpoints[1].x = a; cpoints[1].y = a; cpoints[1].z = a;//a a a 
	cpoints[2].x = 0; cpoints[2].y = 0; cpoints[2].z = a;//0 0 a
	cpoints[3].x = a; cpoints[3].y = 0; cpoints[3].z = a;//a 0 a
	cpoints[4].x = 0; cpoints[4].y = a; cpoints[4].z = 0;//0 a 0
	cpoints[5].x = a; cpoints[5].y = a; cpoints[5].z = 0;//a a 0
	cpoints[6].x = 0; cpoints[6].y = 0; cpoints[6].z = 0;//0 0 0 
	cpoints[7].x = a; cpoints[7].y = 0; cpoints[7].z = 0;//a 0 0
}

// ����ƽ��������
// ����down����ƽ��һ����λ��up����ƽ��һ����λ��
// left����ƽ��һ����λ��right����ƽ��һ����λ
void CCGwork0218View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
	switch (nChar)
	{
	case VK_DOWN:
		MoveTrans(0, 1, 0);
		break;
	case VK_UP:
		MoveTrans(0, -1, 0);
		break;
	case VK_LEFT:
		MoveTrans(-1, 0, 0);
		break;
	case VK_RIGHT:
		MoveTrans(1, 0, 0);
		break;
	}
	Invalidate();
	UpdateWindow();
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


// �������ź���ת(��Ҫ�ر����뷨)
// ����x��x��Ϊ��ת������תһ�ȣ�y��y��Ϊ��ת������תһ�ȣ�
// z��z��Ϊ��ת������תһ�ȣ�b���,s��С
void CCGwork0218View::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CView::OnChar(nChar, nRepCnt, nFlags);
	switch (nChar)
	{
	case 'x':
		RotateTrans(1, CString("x"));
		break;
	case 'y':
		RotateTrans(1, CString("y"));
		break;
	case 'z':
		RotateTrans(1, CString("z"));
		break;
	case 'b':
		BigerOrSmallerTrans(1.1, 1.1, 1.1);
		break;
	case 's':
		BigerOrSmallerTrans(0.9, 0.9, 0.9);
		break;
	}
	Invalidate();
	UpdateWindow();
	CView::OnChar(nChar, nRepCnt, nFlags);
}

// ������->�����廭�ʹ���
void CCGwork0218View::OnDrawcube()
{
	// TODO:  �ڴ���������������
	m_dsDrawSort = DsCube;
	Invalidate();
	UpdateWindow();
}

// ������->͸��ͶӰ�㷨
void CCGwork0218View::OnCubet()
{
	// TODO:  �ڴ���������������
	m_proFunc = TOUSHI;
	Invalidate();
	UpdateWindow();
	isCubeInitialized = true;
}

// ������->б��ͶӰ�㷨
void CCGwork0218View::OnCubex()
{
	// TODO:  �ڴ���������������
	m_proFunc = XIEJIAO;
	Invalidate();
	UpdateWindow();
	isCubeInitialized = true;
}
/*==============================���ߵĻ���==============================================*/

// ������->����Bezier����
void CCGwork0218View::OnBezier()
{
	m_dsDrawSort =DsBezier;//�л�ΪBezier���߻���
	// TODO:  �ڴ���������������
	m_eChooseType = Bezier;
	m_bIsChoosed = true;
	m_bStopDraw = false;
	while (m_vInputPoint.size() != 0)
	{
		m_vInputPoint.pop_back();
	}
	while (m_vControlPoint.size() != 0)
	{
		m_vControlPoint.pop_back();
	}
	while (m_vXiShu.size() != 0)
	{
		m_vXiShu.pop_back();
	}
}

// ������->����B��������
void CCGwork0218View::OnBsize()
{
	m_dsDrawSort = DsBsize;//�л�ΪB��������
	// TODO:  �ڴ���������������
	m_eChooseType = BYangTiao;
	m_bIsChoosed = true;
	m_bStopDraw = false;
	while (m_vInputPoint.size() != 0)
	{
		m_vInputPoint.pop_back();
	}
	while (m_vControlPoint.size() != 0)
	{
		m_vControlPoint.pop_back();
	}
	while (m_vXiShu.size() != 0)
	{
		m_vXiShu.pop_back();
	}
}

// �������ξ���B��������
void CCGwork0218View::DrawB(CDC* pDC, CPoint point1, CPoint point2, CPoint point3, CPoint point4)
{
	int x1, y1, x2, y2, x3, y3, x4, y4;//����4��������ֵ
	x1 = point1.x;
	y1 = point1.y;
	x2 = point2.x;
	y2 = point2.y;
	x3 = point3.x;
	y3 = point3.y;
	x4 = point4.x;
	y4 = point4.y;

	pDC->SetPixel(x1, y1, (COLORREF)0x000000FF);		//�ú���ɫ����4�������
	pDC->SetPixel(x2, y2, (COLORREF)0x000000FF);
	pDC->SetPixel(x3, y3, (COLORREF)0x000000FF);
	pDC->SetPixel(x4, y4, (COLORREF)0x000000FF);
	pDC->MoveTo(x1, y1);		//����4������������
	pDC->LineTo(x2, y2);
	pDC->LineTo(x3, y3);
	pDC->LineTo(x4, y4);

	double x = 0, y = 0, ax, ay, s1, s2, s3, u;
	pDC->SetPixel(x1, y1, RGB(255, 0, 0));
	ax = (x1 + 4 * x2 + x3) / 6.0;
	ay = (y1 + 4 * y2 + y3) / 6.0;
	for (u = 0; u <= 1; u = u + 0.001)
	{
		s1 = u;
		s2 = s1*s1;
		s3 = s1*s1*s1;
		x = ax + ((x3 - x1) / 2.0)*s1 + ((x1 - 2 * x2 + x3) / 2.0)*s2 + ((x4 - 3 * x3 + 3 * x2 - x1) / 6.0)*s3;
		y = ay + ((y3 - y1) / 2.0)*s1 + ((y1 - 2 * y2 + y3) / 2.0)*s2 + ((y4 - 3 * y3 + 3 * y2 - y1) / 6.0)*s3;
		if (u == 0)
		{
			pDC->MoveTo((int)ax, (int)ay);
		}
		pDC->LineTo((int)x, (int)y);
		if (u == 0 || u == 1)
		{
			pDC->Ellipse(x - 3, y - 3, x + 3, y + 3);
		}
	}

	return;
}

// ����Bezier����
void CCGwork0218View::DrawBezier(CDC* pDC)
{
	int iNumber = m_vInputPoint.size();
	pDC->MoveTo(m_vInputPoint[0]);
	if (iNumber == 1)
	{
		pDC->SetPixel(m_vInputPoint[0], (COLORREF)0x000000FF);
		return;
	}
	for (int i = 0; i<iNumber - 1; i++)
	{
		pDC->SetPixel(m_vInputPoint[i], (COLORREF)0x000000FF);
		pDC->SetPixel(m_vInputPoint[i + 1], (COLORREF)0x000000FF);
		pDC->LineTo(m_vInputPoint[i + 1]);
	}
	double u, x, y;
	pDC->SetPixel(m_vInputPoint[0], RGB(255, 0, 0));
	pDC->MoveTo(m_vInputPoint[0]);
	for (u = 0; u <= 1; u = u + 0.001)
	{
		x = 0; y = 0;
		for (int i = 0; i<iNumber; i++)
		{
			x += C(iNumber - 1, i)*N(u, i)*N((1 - u), (iNumber - 1 - i))*m_vInputPoint[i].x;
			y += C(iNumber - 1, i)*N(u, i)*N((1 - u), (iNumber - 1 - i))*m_vInputPoint[i].y;
		}
		pDC->LineTo((int)x, (int)y);
	}

	return;
}

// ��׳�
int CCGwork0218View::JieCheng(int n)
{
	if (n == 1 || n == 0)
	{
		return 1;
	}
	else
	{
		return n*JieCheng(n - 1);
	}
}

// �������
double CCGwork0218View::C(int n, int i)
{
	return ((double)JieCheng(n)) / ((double)(JieCheng(i)*JieCheng(n - i)));
}

// ��һ����u��n�η�
double CCGwork0218View::N(double u, int n)
{
	double sum = 1.0;
	if (n == 0)
	{
		return 1;
	}
	for (int i = 0; i<n; i++)
	{
		sum *= u;
	}
	return sum;
}

// �жϵ��Ƿ��ڿ��ƶ���
void CCGwork0218View::PointOnInputPoint(CPoint CheckedPoint)
{
	double dDistence;

	int i;
	for (i = 0; i<m_vInputPoint.size(); i++)
	{
		dDistence = (CheckedPoint.x - m_vInputPoint[i].x)*(CheckedPoint.x - m_vInputPoint[i].x) +
			(CheckedPoint.y - m_vInputPoint[i].y)*(CheckedPoint.y - m_vInputPoint[i].y) - 4 * 4;
		if (dDistence <= 0)
		{
			m_iItemOfEditPoint = i;
			m_bPointChoosed = true;
			return;
		}
	}
	m_bPointChoosed = false;
	return;
}

//������->����
void CCGwork0218View::OnReset()
{
	// �����еĲ�����ʼ��
	m_dsDrawSort = DsNull;
	m_sharpList.RemoveAll();
	m_fillList.RemoveAll();
	//bDrawMark = false;
	//bMoveMark = false;
	//MoveStart=(0, 0);
	//MoveEnd=(0, 0);
	//bRotateMark = false;
	//RotateBase=(0, 0);
	//bFillMark = false;
	//ptNum=1;
	//RotateAngle = 0.0;
	//m_bDrawMode = false;
	//beflag = 0;
	//xzflag = 0;
	//beizerItem = NULL;
	//cxClient = 0;
	//cyClient = 0;
	//m_cMovePoint = 0;
	//m_bIsChoosed = false;
	//m_bStopDraw = false;
	//m_bPointChoosed = false;
	//m_bMakeSure = false;
	//m_iItemOfEditPoint = 0;
	//m_dsDrawSort = DsNull;
	//m_startPoint.x = 0;
	//m_startPoint.y = 0;
	//m_endPoint.x = 0;
	//m_endPoint.y = 0;
	//m_bIsMouseDown = 0;
	//m_lPenColor = RGB(0, 0, 255);
	//m_iPenWidth = 1;
	//m_lBkColor = RGB(255, 255, 255);
	//m_lFillColor = RGB(255, 0, 0);
	//m_LineType = BRDL;
	//m_CircleType = MDC;
	//m_FillType = EXTFLOODFILL;
	//m_proFunc = TOUSHI;
	//m_bDrawMode = true;
	//isCubeInitialized = true;
	Invalidate();
	UpdateWindow();
}
