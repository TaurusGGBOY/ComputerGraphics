
// CGAlgView.cpp: CCGAlgView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "CGAlg.h"
#endif

#include "CGAlgDoc.h"
#include "CGAlgView.h"
#include "StartEnd.h"
#include <iostream>
#include <sstream>
#include <cstring>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCGAlgView

IMPLEMENT_DYNCREATE(CCGAlgView, CScrollView)

BEGIN_MESSAGE_MAP(CCGAlgView, CScrollView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CScrollView::OnFilePrintPreview)
	ON_COMMAND(ID_32771, &CCGAlgView::OnDDALine)
	ON_COMMAND(ID_32772, &CCGAlgView::OnMidLine)
	ON_COMMAND(ID_32773, &CCGAlgView::OnBresenhamLine)
	//ON_COMMAND(ID_32774, &CCGAlgView::On32774)
	ON_COMMAND(ID_32775, &CCGAlgView::OnSetStartEnd)
	ON_BN_CLICKED(IDOK, &CCGAlgView::OnBnClickedOk)
	ON_COMMAND(ID_32774, &CCGAlgView::OnClear)
END_MESSAGE_MAP()

// CCGAlgView 构造/析构

CCGAlgView::CCGAlgView() noexcept
{
	// TODO: 在此处添加构造代码
	alg = 0;
	xs = 0;
	ys = 0;
	xe = 4;
	ye = 1;
}

CCGAlgView::~CCGAlgView()
{
}

BOOL CCGAlgView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CScrollView::PreCreateWindow(cs);
}


void CCGAlgView::OnDraw(CDC* pDC)
{
	CCGAlgDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	

	// TODO: 在此处为本机数据添加绘制代码


	vector<CPoint> points;
	switch (alg)
	{
	case 1:
		points = DDALine(xs, ys, xe, ye);
		break;
	case 2:
		points = MLDA(xs, ys, xe, ye);
		break;
	case 3:
		points = BresenhamLine(xs, ys, xe, ye);
		break;
	default:
		break;
	}

	if (points.size() > 0)
	{
		pDC->MoveTo(points[0]);

		for (CPoint point : points)
		{
			pDC->LineTo(point);

			TRACE("%d %d\n", point.x,point.y);
		}
	}
}

void CCGAlgView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: 计算此视图的合计大小
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);
}


// CCGAlgView 打印

BOOL CCGAlgView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CCGAlgView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CCGAlgView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CCGAlgView 诊断

#ifdef _DEBUG
void CCGAlgView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CCGAlgView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CCGAlgDoc* CCGAlgView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCGAlgDoc)));
	return (CCGAlgDoc*)m_pDocument;
}
#endif //_DEBUG


// CCGAlgView 消息处理程序
vector<CPoint> CCGAlgView::DDALine(float xs, float ys, float xe, float ye)
{
	float x1 = xs, y1 = ys, x2 = xe, y2 = ye,dx,dy,m;
	int length;
	vector<CPoint> points;
	CPoint point;

	point.x = (int)x1;
	point.y = (int)y1;
	points.push_back(point);
	m = (y2 - y1) / (x2 - x1); // |m|=|dy|/|dx|
	x1 += 0.5f;
	y1 += 0.5f;
	dx = abs(x2 - x1);
	dy = abs(y2 - y1);
	length = (int)max(dx, dy);

	for (int i = 0; i < length; i++)
	{
		if (dx > dy && x1 < x2) // 0<m<1 保证x,y的增量带m的>0,<1，不带m的=-1或1
		{
			x1 += 1;
			y1 += m;
		}
		else if (dx > dy && x1 >= x2) // -1<m<0
		{
			x1 += -1;
			y1 += -m;
		}
		else if (dx <= dy && x1 < x2) // m>1
		{
			x1 += 1 / m;
			y1 += 1;
		}
		else if (dx <= dy && x1 >= x2) // m<-1
		{
			x1 += -1 / m;
			y1 += -1;
		}
		point.x = (int)x1;
		point.y = (int)y1;
		points.push_back(point);
	}
	point.x = (int)x2;
	point.y = (int)y2;
	points.push_back(point);
	return points;
}

vector<CPoint> CCGAlgView::MLDA(float xs, float ys, float xe, float ye)
{
	int x1 = (int)xs, y1 = (int)ys, x2 = (int)xe, y2 = (int)ye;
	vector<CPoint> points;
	int a, b, d, deta1, deta2, x, y;
	CPoint point;

	// 仅考虑0<=m<=1
	a = y1 - y2;
	b = x2 - x1;
	d = 2 * a + b; // x1 y1的d的二倍 为了避免小数运算
	deta1 = 2 * a; // 计算下一个d用 为了避免小数运算 用了2倍
	deta2 = 2 * (a + b); // 计算下一个d用 为了避免小数运算 用了2倍
	x = x1;
	y = y1;
	point.x = x;
	point.y = y;
	points.push_back(point);

	TRACE("x1=%d y1=%d a=%d b=%d d=%d deta1=%d deta2=%d \n", x1,y1,a,b,d,deta1,deta2);

	while (x < x2)
	{
		if (d < 0) // 如果交点在直线的上方 则下个点在中点上方 都加1 即加a也加b
		{
			x++;
			y++;
			d += deta2;
		}
		else // 否则下个点在中点下方 y不变 只有x加1 d也只加a
		{
			x++;
			d += deta1;
		}
		point.x = x;
		point.y = y;
		points.push_back(point);
	}

	return points;
}

vector<CPoint> CCGAlgView::BresenhamLine(float xs, float ys, float xe, float ye)
{
	float x1 = xs, y1 = ys, x2 = xe, y2 = ye;
	vector<CPoint> points;
	float dx, dy, m,e,x,y;
	CPoint point;
	int s1, s2;

	dx = x2 - x1;
	dy = y2 - y1;
	m = dy / dx;
	x = x1;
	y = y1;
	if (dx >= 0)
	{
		s1 = 1;
	}
	else
	{
		s1 = -1;
	}
	if (dy >= 0)
	{
		s2 = 1;
	}
	else
	{
		s2 = -1;
	}

	if (abs(m) > 1) // |dy|>|dx| 保证e是负数
	{
		e = 2 * abs(dx) - abs(dy); // 两个小的减一个大的 苏小红版本P51页初值有错
	}
	else
	{
		e = 2 * abs(dy) - abs(dx);
	}

	point.x = (int)x;
	point.y = (int)y;
	points.push_back(point);
	while (x < x2)
	{
		if (e < 0)
		{
			if (abs(m) > 1) // y方向上增长更快
			{
				y += s2;
				e += 2 * abs(dx);
			}
			else
			{
				x += s1;
				e += 2 * abs(dy);
			}
		}
		else
		{
			if (abs(m) > 1) // y方向上增长更快 同时e需要变为负数
			{
				x += s1;
				y += s2;
				e += 2 * (abs(dx)-abs(dy));
			}
			else
			{
				x += s1;
				y += s2;
				e += 2 * (abs(dy) - abs(dx));
			}
		}
		point.x = (int)x;
		point.y = (int)y;
		points.push_back(point);
	}

	return points;
}

void CCGAlgView::OnDDALine()
{
	// TODO: 在此添加命令处理程序代码
	alg = 1;
	Invalidate();
}


void CCGAlgView::OnMidLine()
{
	// TODO: 在此添加命令处理程序代码
	alg = 2;
	Invalidate();
}


void CCGAlgView::OnBresenhamLine()
{
	// TODO: 在此添加命令处理程序代码
	alg = 3;
	Invalidate();
}




void CCGAlgView::OnSetStartEnd()
{
	// TODO: 在此添加命令处理程序代码
}


void CCGAlgView::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	
}


void CCGAlgView::OnClear()
{
	// TODO: 在此添加命令处理程序代码
	alg = 0;
	Invalidate();
}
