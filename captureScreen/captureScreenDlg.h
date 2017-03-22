// captureScreenDlg.h : 头文件
//

#pragma once
#include "afxwin.h"


// CcaptureScreenDlg 对话框
class CcaptureScreenDlg : public CDialog
{
// 构造
public:
	CcaptureScreenDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_CAPTURESCREEN_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonCaptureScreen();
public:
	CString m_str_save_path;
	boolean m_bOpenMspaint;
	void CcaptureScreenDlg::OnBtnPrintScreen() ;
	void CcaptureScreenDlg::WriteBmpToFile(HBITMAP hBitmap);
	void CcaptureScreenDlg::CopyBmpToClipBoard(HBITMAP hBitmap);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	// 刷新文件的保存位置以及文件名
	CStatic m_savePosEdit;
	afx_msg void OnBnClickedRadio1();
	// 此Radiobutton用以确认是否启动定时保存机制
	CButton m_startCheckButton;
	CButton m_captureButton;
};
