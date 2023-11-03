
// PasswordGeneratorDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "PasswordGenerator.h"
#include "PasswordGeneratorDlg.h"
#include "afxdialogex.h"
#include <algorithm>



#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPasswordGeneratorDlg 对话框



CPasswordGeneratorDlg::CPasswordGeneratorDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PASSWORDGENERATOR_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPasswordGeneratorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_edit1);
	DDX_Control(pDX, IDC_EDIT2, m_edit2);
	DDX_Control(pDX, IDC_SLIDER1, m_sld1);
	DDX_Control(pDX, IDC_CHECK1, m_chk1);
	DDX_Control(pDX, IDC_CHECK2, m_chk2);
	DDX_Control(pDX, IDC_CHECK3, m_chk3);
	DDX_Control(pDX, IDC_CHECK4, m_chk4);
}

BEGIN_MESSAGE_MAP(CPasswordGeneratorDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CPasswordGeneratorDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CPasswordGeneratorDlg::OnBnClickedButton2)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1, &CPasswordGeneratorDlg::OnNMCustomdrawSlider1)
	ON_BN_CLICKED(IDC_CHECK1, &CPasswordGeneratorDlg::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_CHECK2, &CPasswordGeneratorDlg::OnBnClickedCheck2)
	ON_BN_CLICKED(IDC_CHECK3, &CPasswordGeneratorDlg::OnBnClickedCheck3)
	ON_BN_CLICKED(IDC_CHECK4, &CPasswordGeneratorDlg::OnBnClickedCheck4)
END_MESSAGE_MAP()


// CPasswordGeneratorDlg 消息处理程序

BOOL CPasswordGeneratorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	SetWindowText(_T("密码生成器 v0.2-02"));
	GetDlgItem(IDC_BUTTON1)->SetWindowText(_T("生成密码"));
	GetDlgItem(IDC_BUTTON2)->SetWindowText(_T("复制"));
	m_chk1.SetWindowText(_T("A-Z"));
	m_chk2.SetWindowText(_T("a-z"));
	m_chk3.SetWindowText(_T("0-9"));
	m_chk4.SetWindowText(_T("][!\"#$%&&'()*+,./:;<=>?@\\^_`{|}~-"));  // &&显示&
	m_chk1.SetCheck(TRUE);
	m_chk2.SetCheck(TRUE);
	m_chk3.SetCheck(TRUE);
	m_chk4.SetCheck(TRUE);
	m_edit1.SetReadOnly(TRUE);
	m_edit2.SetReadOnly(TRUE);
	m_sld1.SetFocus();
	m_sld1.SetRange(6, 40);
	m_sld1.SetPos(16);
	m_edit1.SetWindowText((CString)(GenerateStrongPassword().c_str()));
	CDialog::SetDefID(IDC_EDIT1);  //设置默认ID，避免Enter退出，ESC还是会退出

	//return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
	return FALSE;
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CPasswordGeneratorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CPasswordGeneratorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


string CPasswordGeneratorDlg::GenerateStrongPassword(INT length, BOOL chk_ALPHA, BOOL chk_alpha, BOOL chk_number, BOOL chk_symbol)
{
	string ALPHA = chk_ALPHA?"ABCDEFGHIJKLMNOPQRSTUVWXYZ":"";
	string alpha = chk_alpha?"abcdefghijklmnopqrstuvwxyz":"";
	string number = chk_number?"0123456789":"";
	string symbol = chk_symbol?"][!\"#$%&'()*+,./:;<=>?@\\^_`{|}~-":"";
	string total = ALPHA+alpha+number+symbol;
	string password = "";

	random_shuffle(total.begin(), total.end());  //随机洗牌total字符串

	/* 随机函数生成密码 */
	srand(time(0));
	while(length--)
		password += total[rand() % total.length()];

	return password;
}

void  CPasswordGeneratorDlg::CopyToClipboard()
{
	if (!OpenClipboard())
	{
		AfxMessageBox(_T("Cannot open the Clipboard"));
		return;
	}
	if (!EmptyClipboard())
	{
		AfxMessageBox(_T("Cannot empty the Clipboard"));
		return;
	}

	CString cstr;
	m_edit1.GetWindowText(cstr);

	CStringA str(cstr);

	HGLOBAL h = GlobalAlloc(GMEM_FIXED, cstr.GetLength() + 1);
	strcpy_s((char*)h, cstr.GetLength() + 1, str);

	if (::SetClipboardData(CF_TEXT, h) == NULL)
	{
		CString msg;
		msg.Format(_T("Unable to set Clipboard data, error: %d"), GetLastError());
		AfxMessageBox(msg);
		CloseClipboard();
		GlobalFree(h);
		return;
	}
	CloseClipboard();
}


void  CPasswordGeneratorDlg::Check_chk(CButton &m_chk1, CButton &m_chk2, CButton &m_chk3, CButton &m_chk4)
{
	if (!m_chk1.GetCheck() && !m_chk2.GetCheck() && !m_chk3.GetCheck() && m_chk4.GetCheck())
		m_chk4.EnableWindow(FALSE);
	else if (m_chk1.GetCheck() && !m_chk2.GetCheck() && !m_chk3.GetCheck() && m_chk4.GetCheck())
		m_chk4.EnableWindow(TRUE);
	else if (!m_chk1.GetCheck() && !m_chk2.GetCheck() && m_chk3.GetCheck() && !m_chk4.GetCheck())
		m_chk3.EnableWindow(FALSE);
	else if (m_chk1.GetCheck() && !m_chk2.GetCheck() && m_chk3.GetCheck() && !m_chk4.GetCheck())
		m_chk3.EnableWindow(TRUE);
	else if (!m_chk1.GetCheck() && m_chk2.GetCheck() && !m_chk3.GetCheck() && !m_chk4.GetCheck())
		m_chk2.EnableWindow(FALSE);
	else if (m_chk1.GetCheck() && m_chk2.GetCheck() && !m_chk3.GetCheck() && !m_chk4.GetCheck())
		m_chk2.EnableWindow(TRUE);
}


void CPasswordGeneratorDlg::OnBnClickedButton1()
{
	GetDlgItem(IDC_BUTTON1)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON2)->EnableWindow(false);
	INT length = m_sld1.GetPos();
	INT chk_ALPHA = m_chk1.GetCheck();
	INT chk_alpha = m_chk2.GetCheck();
	INT chk_number = m_chk3.GetCheck();
	INT chk_symbol = m_chk4.GetCheck();
	string str = GenerateStrongPassword(length,chk_ALPHA,chk_alpha,chk_number,chk_symbol);
	CString cstr(str.c_str());
	m_edit1.SetWindowText(cstr);
	GetDlgItem(IDC_BUTTON1)->EnableWindow(true);
	GetDlgItem(IDC_BUTTON2)->EnableWindow(true);
}


void CPasswordGeneratorDlg::OnBnClickedButton2()
{
	CopyToClipboard();
}


void CPasswordGeneratorDlg::OnNMCustomdrawSlider1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);

	*pResult = 0;

	CString cstr;
	cstr.Format(_T("%d"), m_sld1.GetPos());
	m_edit2.SetWindowText(cstr);
}


void CPasswordGeneratorDlg::OnBnClickedCheck1()
{
	Check_chk(m_chk1,m_chk2,m_chk3,m_chk4);
}


void CPasswordGeneratorDlg::OnBnClickedCheck2()
{
	Check_chk(m_chk2, m_chk1, m_chk3, m_chk4);
}


void CPasswordGeneratorDlg::OnBnClickedCheck3()
{
	Check_chk(m_chk3, m_chk1, m_chk2, m_chk4);
}


void CPasswordGeneratorDlg::OnBnClickedCheck4()
{
	Check_chk(m_chk4, m_chk1, m_chk2, m_chk3);
}
