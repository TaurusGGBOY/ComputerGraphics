
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
END_MESSAGE_MAP()

// CCGAlgView 构造/析构

CCGAlgView::CCGAlgView() noexcept
{
	// TODO: 在此处添加构造代码

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

// CCGAlgView 绘图

void CCGAlgView::OnDraw(CDC* /*pDC*/)
{
	CCGAlgDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
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
