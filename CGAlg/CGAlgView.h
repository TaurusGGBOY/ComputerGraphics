#include <vector>
using namespace std;
// CGAlgView.h: CCGAlgView 类的接口
//

#pragma once


class CCGAlgView : public CScrollView
{
protected: // 仅从序列化创建
	CCGAlgView() noexcept;
	DECLARE_DYNCREATE(CCGAlgView)

// 特性
public:
	CCGAlgDoc* GetDocument() const;
	vector<CPoint> DDALine(float xs, float ys, float xe, float ye);
	vector<CPoint> MLDA(float xs, float ys, float xe, float ye);
	vector<CPoint> BresenhamLine(float xs, float ys, float xe, float ye);
	int alg;
	float xs, ys, xe, ye;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // 构造后第一次调用
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CCGAlgView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDDALine();
	afx_msg void OnMidLine();
	afx_msg void OnBresenhamLine();
	afx_msg void On32774();
	afx_msg void OnSetStartEnd();
	afx_msg void OnBnClickedOk();
	afx_msg void OnClear();
};

#ifndef _DEBUG  // CGAlgView.cpp 中的调试版本
inline CCGAlgDoc* CCGAlgView::GetDocument() const
   { return reinterpret_cast<CCGAlgDoc*>(m_pDocument); }
#endif

