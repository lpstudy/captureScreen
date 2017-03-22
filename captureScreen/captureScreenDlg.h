// captureScreenDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CcaptureScreenDlg �Ի���
class CcaptureScreenDlg : public CDialog
{
// ����
public:
	CcaptureScreenDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_CAPTURESCREEN_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
	// ˢ���ļ��ı���λ���Լ��ļ���
	CStatic m_savePosEdit;
	afx_msg void OnBnClickedRadio1();
	// ��Radiobutton����ȷ���Ƿ�������ʱ�������
	CButton m_startCheckButton;
	CButton m_captureButton;
};
