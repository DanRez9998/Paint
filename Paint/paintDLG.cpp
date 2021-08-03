#include "stdafx.h"
#include "MyPaint.h"
#include "paintDLG.h"
#include "afxdialogex.h"


IMPLEMENT_DYNAMIC(paintDLG, CDialogEx)

paintDLG::paintDLG(CWnd* pParent)
	: CDialogEx(paintDLG::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	isPressed = false; //bool variable that checks if we pressed left button of the mouse.
	isRefill = false; //bool variable that checks if we pressed the refill button.
	size = 1; // size of shapes.
	lastMode = regular;
	myMode = lastMode;
	rect.SetRect(MY_CANVAS_START_X, MY_CANVAS_START_Y, MY_CANVAS_END_X, MY_CANVAS_END_Y);
	shapeFactory = RectangleFactory::getInstance();
}

paintDLG::~paintDLG()
{
	for (int i = 0; i < myShapes.GetSize(); i++)
	{
		delete myShapes[i];
	}
}

void paintDLG::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON4, clearB);
	DDX_Control(pDX, IDC_BUTTON1, colorChooseB);
	DDX_Control(pDX, IDC_BUTTON6, fillB);
	DDX_Control(pDX, IDC_SLIDER1, lineWidthSlider);
}


BEGIN_MESSAGE_MAP(paintDLG, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_RADIO1, &paintDLG::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &paintDLG::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO3, &paintDLG::OnBnClickedRadio3)
	ON_BN_CLICKED(IDC_RADIO4, &paintDLG::OnBnClickedRadio4)
	ON_BN_CLICKED(IDC_BUTTON1, &paintDLG::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON4, &paintDLG::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON6, &paintDLG::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTONLoad, &paintDLG::OnBnClickedButtonload)
	ON_BN_CLICKED(IDC_BUTTONSave, &paintDLG::OnBnClickedButtonsave)
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_RADIO5, &paintDLG::OnBnClickedRadio5)
	ON_BN_CLICKED(IDC_BUTTON8, &paintDLG::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON7, &paintDLG::OnBnClickedButton7)
	ON_BN_CLICKED(IDCANCEL, &paintDLG::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_RADIO6, &paintDLG::OnBnClickedRadio6)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1, &paintDLG::OnNMCustomdrawSlider1)
	ON_BN_CLICKED(IDC_RADIO7, &paintDLG::OnBnClickedRadio7)
	ON_BN_CLICKED(IDC_RADIO8, &paintDLG::OnBnClickedRadio8)
	ON_BN_CLICKED(IDC_RADIO9, &paintDLG::OnBnClickedRadio9)
END_MESSAGE_MAP()
BOOL paintDLG::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	lineWidthSlider.SetRange(1, 50);
	lineWidthSlider.SetPos(1);

	SetIcon(m_hIcon, TRUE);			
	SetIcon(m_hIcon, FALSE);		
	colorChooseB.ModifyStyle(0, BS_ICON);
	
	m_brush.CreateSolidBrush(RGB(255, 255, 255)); // set the dialog background to be white.
	return TRUE;
}

void paintDLG::OnSysCommand(UINT nID, LPARAM lParam)
{
		CDialogEx::OnSysCommand(nID, lParam);
}

void paintDLG::OnPaint() //"Invalidate"
{
	CPaintDC dc(this);
	dc.Rectangle(MY_CANVAS_START_X, MY_CANVAS_START_Y, MY_CANVAS_END_X, MY_CANVAS_END_Y);
	for (int i = 0; i < myShapes.GetSize(); ++i)
			myShapes[i]->draw(&dc); // draw the shapes
	if(myShapes.IsEmpty())
	{
		clearB.EnableWindow(FALSE);
		GetDlgItem(IDC_RADIO1)->EnableWindow(TRUE);
		GetDlgItem(IDC_RADIO2)->EnableWindow(TRUE);
		GetDlgItem(IDC_RADIO3)->EnableWindow(TRUE);
		GetDlgItem(IDC_RADIO4)->EnableWindow(TRUE);
		GetDlgItem(IDC_RADIO5)->EnableWindow(TRUE);
		myMode = lastMode;
		fillB.EnableWindow(false);
		HCURSOR hcur;
		hcur = AfxGetApp()->LoadCursorW(MAKEINTRESOURCE(IDC_AFXBARRES_DEFAULT_IMAGE));
		SetClassLong(m_hWnd,GCL_HCURSOR,(LONG)hcur);
	}
	else
	{
		clearB.EnableWindow(TRUE);
		for (int i = 0; i < myShapes.GetSize(); ++i)
		{
			if(myShapes[i]->canBeFilled())
			{
				fillB.EnableWindow(true);
			}
		}
	}	
	CDialogEx::OnPaint();
}

HCURSOR paintDLG::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void paintDLG::OnMouseMove(UINT nFlags, CPoint point) //when we move the mouse : check which mode we are and do his thing.
{
	if(isIn(point, rect.TopLeft(), rect.BottomRight()))
	{
		if(isPressed)
		{
			switch (myMode)
			{
			case refill: break;
				case regular:
				{
					myShapes[myShapes.GetSize() - 1]->setEnd(point);
					InvalidateRect(rect); // refresh the rect and redraw the updated shape
					break;
				}
			case brush:
				{
					myShapes[myShapes.GetSize() - 1]->setEnd(point);
					clearB.EnableWindow(TRUE);
					MyShape *s = shapeFactory->createShape();
					myShapes.Add(s);
					s->setBg(color);
					s->setStart(point);
					s->setEnd(point);
					s->setSize(size);
					Invalidate(false);
					break;
				}
				case graffity:
				{
					myShapes[myShapes.GetSize() - 1]->setEnd(point);
					clearB.EnableWindow(TRUE);
					MyShape *s = shapeFactory->createShape();
					myShapes.Add(s);
					s->setBg(color);
					s->setStart(point);
					s->setEnd(point);
					s->setSize(size);
					Invalidate(false);
					break;
				}
			}
		}
	}

	CDialogEx::OnMouseMove(nFlags, point);
}

void paintDLG::OnLButtonDown(UINT nFlags, CPoint point) // on left click the button : check which mode we are and do his thing.
{
	if(isIn(point, rect.TopLeft(), rect.BottomRight()))
	{
		clearB.EnableWindow(TRUE); // Enable button
		isPressed = true;
		switch(myMode)
		{
		case regular:
			{
				MyShape *s = shapeFactory->createShape();
				myShapes.Add(s);
				s->setBg(color);
				s->setStart(point);
				s->setEnd(point);
				s->setSize(size); // width of pen
				InvalidateRect(rect); // refresh the rect and redraw the updated shape
				break;
			}	
		case graffity: //spray
			{
				MyShape *s = shapeFactory->createShape();
				myShapes.Add(s);
				s->setBg(color);
				s->setStart(point);
				s->setEnd(point);
				s->setSize(size);
				Invalidate(false);
				break;
			}
		case brush:
			{
				MyShape *s = shapeFactory->createShape();
				myShapes.Add(s);
				s->setBg(color);
				s->setStart(point);
				s->setEnd(point);
				s->setSize(size);
				Invalidate(false);
				break;
			}
		case refill:
			{
				isPressed = false;
				isRefill = true;
				for (int i=myShapes.GetSize()-1;i>=0;i--)
				{
					if(myShapes[i]->isIn(point))
					{
						if(!myShapes[i]->canBeFilled()) // if brush or line or graffity break (cant fill those shapes)
							break;
						MyShape *s = myShapes[i]; // create pointer s to new shape that its instance is currently on shape factory
						s->setBg(RefillColor); // set the bg color of the shape to the selected refill color
						s->setStart(myShapes[i]->getStart()); 
						s->setEnd(myShapes[i]->getEnd());
						s->setSize(size);
						InvalidateRect(rect); // refresh the rect and redraw the updated shape
						break;
					}
				}
				break;
			}
		}
	}

	CDialogEx::OnLButtonDown(nFlags, point);
}

void paintDLG::OnLButtonUp(UINT nFlags, CPoint point) //when left click, move the mouse and left click again
{
	if(isIn(point, rect.TopLeft(), rect.BottomRight()))
	{
		if((myMode == regular) && (isRefill == false))
			myShapes[myShapes.GetSize() - 1]->setEnd(point); // sets the end point of the shape
		isRefill = false;
		isPressed = false;
		InvalidateRect(rect); // refresh the rect and redraw the updated shape
	}
	CDialogEx::OnLButtonUp(nFlags, point);
}

HBRUSH paintDLG::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = m_brush;
	return hbr;
}


void paintDLG::OnBnClickedRadio2() //line option
{
	HCURSOR hcur;
	hcur = AfxGetApp()->LoadCursorW(MAKEINTRESOURCE(IDC_AFXBARRES_LINE));
	SetClassLong(m_hWnd,GCL_HCURSOR,(LONG)hcur);
	lastMode = myMode;
	myMode = regular;
	shapeFactory = LineFactory::getInstance();
}


void paintDLG::OnBnClickedRadio3() //rectangle option
{
	HCURSOR hcur;
	hcur = AfxGetApp()->LoadCursorW(MAKEINTRESOURCE(IDC_AFXBARRES_RECT));
	SetClassLong(m_hWnd,GCL_HCURSOR,(LONG)hcur);
	lastMode = myMode;
	myMode = regular;
	shapeFactory = RectangleFactory::getInstance();
}


void paintDLG::OnBnClickedRadio4() ////ellipse option
{
	HCURSOR hcur;
	hcur = AfxGetApp()->LoadCursorW(MAKEINTRESOURCE(IDC_AFXBARRES_ELLIPSE));
	SetClassLong(m_hWnd,GCL_HCURSOR,(LONG)hcur);
	lastMode = myMode;
	myMode = regular;
	shapeFactory = EllipseFactory::getInstance();
}


void paintDLG::OnBnClickedButton1()//choose color to paint with from color palette
{
	CColorDialog dlg;
	if(dlg.DoModal()==IDOK) //Displays a color dialog box 
	{
		color=dlg.GetColor();
	}
}



void paintDLG::OnBnClickedButton4() // clear button
{
	for (int i = 0; i < myShapes.GetSize(); i++)
	{
		delete myShapes[i];
	}
	myShapes.RemoveAll();
	Invalidate();
}

void paintDLG::OnBnClickedButton6()//choose color to fill the shape with
{
	// changes the cursor icon (fill icon)
	HCURSOR hcur;
	hcur = AfxGetApp()->LoadCursorW(MAKEINTRESOURCE(IDC_AFXBARRES_FILL));
	SetClassLong(m_hWnd,GCL_HCURSOR,(LONG)hcur);

	myMode=refill;
	// Displays a color dialog box 
	CColorDialog dlg;
	if(dlg.DoModal()==IDOK)
	{
		RefillColor=dlg.GetColor();
	}
}

void paintDLG::OnBnClickedRadio1() //spray option
{
	// change cursor icon to spray
	HCURSOR hcur;
	hcur = AfxGetApp()->LoadCursorW(MAKEINTRESOURCE(IDC_AFXBARRES_PEN));
	SetClassLong(m_hWnd,GCL_HCURSOR,(LONG)hcur);

	lastMode = myMode;
	myMode = graffity;
	shapeFactory = SprayFactory::getInstance(); // create graffity shape instance in shapeFactory
}

bool paintDLG::OnEraseBkGnd()
{
	return true;
}

void paintDLG::OnBnClickedButtonload() // load button
{
	CFile file;
	CFileDialog FileDlg(TRUE);
	FileDlg.m_ofn.lpstrFilter=_T("DATA Files (*.dat)\0*.dat\0"); // supporting file formats
	FileDlg.m_ofn.lpstrTitle=_T("Load DATA File"); // name of the load dialog
	CString filename;
	if(FileDlg.DoModal()==IDOK)
	{
		filename=FileDlg.GetPathName(); // insert path name into filename
	}
	else
	{
		return;
	}
	if(file.Open(filename,CFile::modeRead))
	{
		CArchive ar(&file,CArchive::load);
		myShapes.Serialize(ar); // insert all shapes in the loaded file into myShapes array
		ar.Close();
	}
	else
		return;
	file.Close();
	Invalidate();
}

void paintDLG::OnBnClickedButtonsave() //save button
{
	CFile file;
	CFileDialog FileDlg(TRUE);
	FileDlg.m_ofn.lpstrFilter=_T("DATA Files (*.dat)\0*.dat\0"); // supporting file formats
	FileDlg.m_ofn.lpstrTitle=_T("Save DATA File As"); // name of the load dialog
	CString filename;
	if (FileDlg.DoModal()==IDOK)
	{
		filename=FileDlg.GetPathName(); // insert path name into filename
		if (filename.Find(_T(".dat"), 0) < 0) // add .dat if the filename is not ended with it
			filename.Append(_T(".dat")); // add file extention to filename
	}
	else
	{
		return;
	}
	if(file.Open(filename,CFile::modeCreate|CFile::modeWrite))
	{
		CArchive ar(&file, CArchive::store);
		myShapes.Serialize(ar); // save all shapes int myShapes array into ar object
		ar.Close();
	}
	else
		return;
	file.Close();
}

void paintDLG::OnBnClickedRadio5() //brush option
{
	HCURSOR hcur;
	hcur = AfxGetApp()->LoadCursorW(MAKEINTRESOURCE(IDC_AFXBARRES_PEN));
	SetClassLong(m_hWnd,GCL_HCURSOR,(LONG)hcur);
	lastMode = myMode;
	myMode = brush;
	shapeFactory = BrushFactory::getInstance();
}


void paintDLG::OnBnClickedButton8()  //size of shape get bigger
{
	if (size < 50)
	{
		size++;
		lineWidthSlider.SetPos(lineWidthSlider.GetPos() + 1);
	}
}


void paintDLG::OnBnClickedButton7() //size of shape get lower
{
	if (size > 1)
	{
		size--;
		lineWidthSlider.SetPos(lineWidthSlider.GetPos() - 1);
	}
}


void paintDLG::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}

void paintDLG::OnBnClickedRadio6() //triangle option
{
	HCURSOR hcur;
	hcur = AfxGetApp()->LoadCursorW(MAKEINTRESOURCE(IDC_AFXBARRES_HAND));
	SetClassLong(m_hWnd, GCL_HCURSOR, (LONG)hcur);
	lastMode = myMode;
	myMode = regular;
	shapeFactory = TriangleFactory::getInstance();
}



void paintDLG::OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	*pResult = 0;
	size = lineWidthSlider.GetPos();
}


void paintDLG::OnBnClickedRadio7() // Trapezoid option
{
	HCURSOR hcur;
	hcur = AfxGetApp()->LoadCursorW(MAKEINTRESOURCE(IDC_AFXBARRES_HAND));
	SetClassLong(m_hWnd, GCL_HCURSOR, (LONG)hcur);
	lastMode = myMode;
	myMode = regular;
	shapeFactory = TrapezoidFactory::getInstance();
}


void paintDLG::OnBnClickedRadio8() // Square option
{
	HCURSOR hcur;
	hcur = AfxGetApp()->LoadCursorW(MAKEINTRESOURCE(IDC_AFXBARRES_HAND));
	SetClassLong(m_hWnd, GCL_HCURSOR, (LONG)hcur);
	lastMode = myMode;
	myMode = regular;
	shapeFactory = SquareFactory::getInstance();
}


void paintDLG::OnBnClickedRadio9() // Parallelogram option
{
	HCURSOR hcur;
	hcur = AfxGetApp()->LoadCursorW(MAKEINTRESOURCE(IDC_AFXBARRES_HAND));
	SetClassLong(m_hWnd, GCL_HCURSOR, (LONG)hcur);
	lastMode = myMode;
	myMode = regular;
	shapeFactory = ParallelogramFactory::getInstance();
}
