
// XEngine_RecordMasterDlg.h: 头文件
//

#pragma once


// CXEngineRecordMasterDlg 对话框
class CXEngineRecordMasterDlg : public CDialogEx
{
// 构造
public:
	CXEngineRecordMasterDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_XENGINE_RECORDMASTER_DIALOG };
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
	XNETHANDLE xhScreen;   //屏幕录制句柄
	XNETHANDLE xhVideo;    //视频编码句柄
	XNETHANDLE xhSound;    //声卡录制句柄
	XNETHANDLE xhAudio;    //音频编解码句柄
	XNETHANDLE xhPacket;   //打包句柄
	XNETHANDLE xhFilter;   //过滤器句柄
	FILE* pSt_VideoFile;   //视频保存地址
	FILE* pSt_AudioFile;   //音频保存地址
	FILE* pSt_File;
	BOOL bRecord;
	BOOL bFilter;

	TCHAR tszAudioFile[MAX_PATH];
	TCHAR tszVideoFile[MAX_PATH];

	int64_t nBitRate;
	int nSmpRate;
	int nChannel;
	static void __stdcall XEngine_AVCollect_CBAudio(uint8_t* punStringAudio, int nVLen, LPVOID lParam);
	static void __stdcall XEngine_AVCollect_CBScreen(uint8_t* punStringY, int nYLen, uint8_t* punStringU, int nULen, uint8_t* punStringV, int nVLen, LPVOID lParam);
	static void __stdcall XEngine_AVPacket_Callback(XNETHANDLE xhNet, int nCvtType, int nCvtFrame, double dlTime, LPVOID lParam);
	static DWORD WINAPI XEngine_AVPacket_Thread(LPVOID lParam);
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	CComboBox m_ComboxAudioList;
	CEdit m_EditScreen;
	CEdit m_EditPosX;
	CEdit m_EditPosY;
	CEdit m_EditSaveFile;
	afx_msg void OnBnClickedButton5();
	CButton m_BtnStart;
	CButton m_BtnSuspend;
	CButton m_BtnStop;
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton3();
	CStatic m_StaticTips;
	CEdit m_EditWatermark;
	CEdit m_EditRate;
	CEdit m_EditFrameRate;
	CButton m_BtnCheckPush;
	CEdit m_EditPushAddr;
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedCheck2();
	CButton m_BtnCheckSave;
	XNETHANDLE xhStream;
};
