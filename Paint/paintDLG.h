#pragma once

// Created by Yarin Siton and Daniel Reznik

#define MY_CANVAS_START_X 400
#define MY_CANVAS_END_X 1000
#define MY_CANVAS_START_Y 10
#define MY_CANVAS_END_Y 500

#include "MyShape.h"
#include "MyEllipse.h"
#include "MyRectangle.h"
#include "Square.h"
#include "Parallelogram.h"
#include "MyTriangle.h"
#include "MyTrapezoid.h"
#include "MyLine.h"
#include "MySpray.h"
#include "MyBrush.h"
#include "EllipseFactory.h"
#include "LineFactory.h"
#include "RectangleFactory.h"
#include "SquareFactory.h"
#include "ParallelogramFactory.h"
#include "TriangleFactory.h"
#include "TrapezoidFactory.h"
#include "SprayFactory.h"
#include "BrushFactory.h"
#include <vector>
#include <stack>
#include "afxwin.h"
#include "afxcmn.h"

using namespace std;

// paintDLG dialog

class paintDLG : public CDialogEx
{
	DECLARE_DYNAMIC(paintDLG)

public:
	paintDLG(CWnd* pParent = NULL);   // standard constructor
	virtual ~paintDLG();
	// msg
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio3();
	afx_msg void OnBnClickedRadio4();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButtonload();
	afx_msg void OnBnClickedButtonsave();
	afx_msg void OnBnClickedRadio5();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedRadio6();
	afx_msg bool OnEraseBkGnd();
	enum { IDD = IDD_PAINTDLG };
	enum modeOf{regular, graffity, refill, brush}; // our mode 

	bool isIn(CPoint current, CPoint start, CPoint end){
	if((start.x < end.x) && ((current.x >= start.x && current.x <= end.x && current.y >= start.y && current.y <= end.y) 
		|| (current.x >= start.x && current.x <= end.x && current.y <= start.y && current.y >= end.y)))
		return true;
	if((current.x <= start.x && current.x >= end.x && current.y >= start.y && current.y <= end.y)
		|| (current.x <= start.y && current.x >= end.y && current.y <= start.y && current.y >= end.y))
		return true;
	return false;
}

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

private:
	HICON m_hIcon;
	CBrush m_brush;
	CButton clearB, colorChooseB, fillB; //CButton for each button
	bool spray, isRefill;
	int size;
	CRect rect;
	COLORREF RefillColor, color; //RefillColor = color for fill shape, color = color we choose to paint.
	bool isPressed;
	CTypedPtrArray<CObArray, MyShape*> myShapes;
	ShapeFactory* shapeFactory;
	modeOf myMode, lastMode;

public:
	afx_msg void OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult);
	CSliderCtrl lineWidthSlider;
	afx_msg void OnBnClickedRadio7();
	afx_msg void OnBnClickedRadio8();
	afx_msg void OnBnClickedRadio9();
};
