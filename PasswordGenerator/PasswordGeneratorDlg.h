
// PasswordGeneratorDlg.h: 头文件
//

#pragma once

#include<string>
using namespace std;


// CPasswordGeneratorDlg 对话框
class CPasswordGeneratorDlg : public CDialogEx
{
// 构造
public:
	CPasswordGeneratorDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PASSWORDGENERATOR_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	string CPasswordGeneratorDlg::GenerateStrongPassword(INT length=16,
														BOOL chk_ALPHA=1, BOOL chk_alpha=1, BOOL chk_number=1, BOOL chk_symbol=1);
	void CopyToClipboard();
	void Check_chk(CButton &m_chk1, CButton &m_chk2, CButton &m_chk3, CButton &m_chk4);
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	CEdit m_edit1;
	CEdit m_edit2;
	CSliderCtrl m_sld1;
	CButton m_chk1;
	CButton m_chk2;
	CButton m_chk3;
	CButton m_chk4;
	afx_msg void OnNMCustomdrawSlider1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedCheck2();
	afx_msg void OnBnClickedCheck3();
	afx_msg void OnBnClickedCheck4();
};
