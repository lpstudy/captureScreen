// captureScreenDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "captureScreen.h"
#include "captureScreenDlg.h"
 

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CcaptureScreenDlg 对话框




CcaptureScreenDlg::CcaptureScreenDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CcaptureScreenDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CcaptureScreenDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SAVE_POS, m_savePosEdit);
	DDX_Control(pDX, IDC_CHECK1, m_startCheckButton);
	DDX_Control(pDX, IDC_BUTTON_CAPTURE_SCREEN, m_captureButton);
}

BEGIN_MESSAGE_MAP(CcaptureScreenDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_CAPTURE_SCREEN, &CcaptureScreenDlg::OnBnClickedButtonCaptureScreen)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_CHECK1, &CcaptureScreenDlg::OnBnClickedRadio1)
END_MESSAGE_MAP()


// CcaptureScreenDlg 消息处理程序

BOOL CcaptureScreenDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	m_bOpenMspaint = FALSE;
	
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CcaptureScreenDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CcaptureScreenDlg::OnPaint()
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
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CcaptureScreenDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CcaptureScreenDlg::OnBnClickedButtonCaptureScreen() 
{
	static int count = 1;
	char buf[100];
	sprintf(buf, "%d.bmp",count);
	m_str_save_path = buf;
	count++;

	// TODO: Add your control notification handler code here
	// TODO: Add your control notification handler code here
	
	HWND hWnd = ::GetDesktopWindow();//获得屏幕的HWND.
	HDC hScreenDC = ::GetDC(hWnd);   //获得屏幕的HDC.
	HDC MemDC = ::CreateCompatibleDC(hScreenDC);
	RECT rect; 
	::GetWindowRect(hWnd,&rect);
	SIZE screensize;
	screensize.cx=rect.right-rect.left;
	screensize.cy=rect.bottom-rect.top;
	HBITMAP hBitmap = ::CreateCompatibleBitmap(hScreenDC,screensize.cx,screensize.cy);
	HGDIOBJ hOldBMP = ::SelectObject(MemDC,hBitmap);
	::BitBlt(MemDC,0,0,screensize.cx,screensize.cy,hScreenDC,rect.left,rect.top,SRCCOPY);
	::SelectObject(MemDC,hOldBMP);
	::DeleteObject(MemDC);
	::ReleaseDC(hWnd,hScreenDC);

	this->WriteBmpToFile(hBitmap);
	CString str = "保存文件到当前目录下：" + m_str_save_path;
	m_savePosEdit.SetWindowText(str);

	this->CopyBmpToClipBoard(hBitmap);

	
	if(this->m_bOpenMspaint){
 		::ShellExecute(NULL,"open","mspaint.exe",/*调用画图程序*/
 			this->m_str_save_path,
 			NULL,
 			SW_SHOWMAXIMIZED);
		AfxGetMainWnd()->ShowWindow(SW_NORMAL);     //恢复窗口显示模式 
	}
	
}
void CcaptureScreenDlg::WriteBmpToFile(HBITMAP hBitmap)
{
	HDC hDC =::CreateDC("DISPLAY",NULL,NULL,NULL); 
	int iBits = ::GetDeviceCaps(hDC, BITSPIXEL) * ::GetDeviceCaps(hDC, PLANES);//当前分辨率下每个像素所占字节数  
	::DeleteDC(hDC);

	WORD   wBitCount;   //位图中每个像素所占字节数    
	if (iBits <= 1)
		wBitCount = 1;
	else if (iBits <= 4)
		wBitCount = 4;
	else if (iBits <= 8)
		wBitCount = 8;
	else if (iBits <= 24)
		wBitCount = 24;
	else
		wBitCount = iBits;

	DWORD   dwPaletteSize=0;	//调色板大小， 位图中像素字节大小 
	if (wBitCount <= 8)		
		dwPaletteSize = (1 << wBitCount) *	sizeof(RGBQUAD);	


	BITMAP  bm;        //位图属性结构
	::GetObject(hBitmap, sizeof(bm), (LPSTR)&bm);  


	BITMAPINFOHEADER   bi;       //位图信息头结构     
	bi.biSize            = sizeof(BITMAPINFOHEADER);  
	bi.biWidth           = bm.bmWidth;
	bi.biHeight          = bm.bmHeight;
	bi.biPlanes          = 1;
	bi.biBitCount        = wBitCount;
	bi.biCompression     = BI_RGB; //BI_RGB表示位图没有压缩
	bi.biSizeImage       = 0;
	bi.biXPelsPerMeter   = 0;
	bi.biYPelsPerMeter   = 0;
	bi.biClrUsed         = 0;
	bi.biClrImportant    = 0;

	DWORD dwBmBitsSize = ((bm.bmWidth * wBitCount+31)/32) * 4 * bm.bmHeight;    
	HANDLE hDib  = ::GlobalAlloc(GHND,dwBmBitsSize + dwPaletteSize + sizeof(BITMAPINFOHEADER));  //为位图内容分配内存
	LPBITMAPINFOHEADER lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDib);
	*lpbi = bi;

	HANDLE hPal = ::GetStockObject(DEFAULT_PALETTE);  // 处理调色板 
	HANDLE  hOldPal=NULL; 
	if (hPal)
	{
		hDC = ::GetDC(NULL);
		hOldPal = SelectPalette(hDC,(HPALETTE)hPal, FALSE);
		RealizePalette(hDC);
	}
	::GetDIBits(hDC, hBitmap, 0, (UINT) bm.bmHeight,(LPSTR)lpbi + sizeof(BITMAPINFOHEADER)+dwPaletteSize,(BITMAPINFO*)lpbi,DIB_RGB_COLORS);// 获取该调色板下新的像素值
	if (hOldPal)//恢复调色板
	{
		SelectPalette(hDC, (HPALETTE)hOldPal, TRUE);
		RealizePalette(hDC);
		::ReleaseDC(NULL, hDC);
	}	

	BITMAPFILEHEADER   bmfHdr; //位图文件头结构     
	bmfHdr.bfType = 0x4D42;  // "BM"  	// 设置位图文件头
	DWORD dwDIBSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + dwPaletteSize + dwBmBitsSize;  
	bmfHdr.bfSize = dwDIBSize;
	bmfHdr.bfReserved1 = 0;
	bmfHdr.bfReserved2 = 0;
	bmfHdr.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER) + (DWORD)sizeof(BITMAPINFOHEADER) + dwPaletteSize;

	HANDLE hFile = CreateFile(/*m_strFilePath*/this->m_str_save_path, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, NULL);//创建位图文件   
	DWORD dwWritten;
	WriteFile(hFile, (LPSTR)&bmfHdr, sizeof(BITMAPFILEHEADER), &dwWritten, NULL);	// 写入位图文件头
	WriteFile(hFile, (LPSTR)lpbi, dwDIBSize, &dwWritten, NULL);// 写入位图文件其余内容

	GlobalUnlock(hDib);   //清除   
	GlobalFree(hDib);
	CloseHandle(hFile); 	

}
void CcaptureScreenDlg::CopyBmpToClipBoard(HBITMAP hBitmap)
{
	OpenClipboard() ; 	//打开剪贴板，并将位图拷到剪贴板上 
	EmptyClipboard(); 
	SetClipboardData(CF_BITMAP, hBitmap);
	CloseClipboard(); 	//关闭剪贴板  
}

void CcaptureScreenDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	this->OnBnClickedButtonCaptureScreen();

	CDialog::OnTimer(nIDEvent);
}

void CcaptureScreenDlg::OnBnClickedRadio1()
{
	// TODO: 在此添加控件通知处理程序代码
	
	BOOL result = m_startCheckButton.GetCheck();
	if(result){
		//AfxMessageBox("start timer");
		m_captureButton.EnableWindow(FALSE);
			
		SetTimer(100,5000,0);
		AfxGetMainWnd()->ShowWindow(SW_MINIMIZE );
		this->OnBnClickedButtonCaptureScreen();
	}
	else{
		//AfxMessageBox("stop timer");
		KillTimer(100);
		m_captureButton.EnableWindow(TRUE);
	}
}
