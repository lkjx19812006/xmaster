
// XEngine_RecordMasterDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "XEngine_RecordMaster.h"
#include "XEngine_RecordMasterDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CXEngineRecordMasterDlg 对话框



CXEngineRecordMasterDlg::CXEngineRecordMasterDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_XENGINE_RECORDMASTER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CXEngineRecordMasterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_ComboxAudioList);
	DDX_Control(pDX, IDC_EDIT1, m_EditScreen);
	DDX_Control(pDX, IDC_EDIT2, m_EditPosX);
	DDX_Control(pDX, IDC_EDIT3, m_EditPosY);
	DDX_Control(pDX, IDC_EDIT4, m_EditSaveFile);
	DDX_Control(pDX, IDC_BUTTON1, m_BtnStart);
	DDX_Control(pDX, IDC_BUTTON4, m_BtnSuspend);
	DDX_Control(pDX, IDC_BUTTON5, m_BtnStop);
	DDX_Control(pDX, IDC_STATIC_TIPS, m_StaticTips);
	DDX_Control(pDX, IDC_EDIT5, m_EditWatermark);
	DDX_Control(pDX, IDC_EDIT6, m_EditRate);
	DDX_Control(pDX, IDC_EDIT7, m_EditFrameRate);
	DDX_Control(pDX, IDC_CHECK1, m_BtnCheckPush);
	DDX_Control(pDX, IDC_EDIT8, m_EditPushAddr);
	DDX_Control(pDX, IDC_CHECK2, m_BtnCheckSave);
}

BEGIN_MESSAGE_MAP(CXEngineRecordMasterDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CXEngineRecordMasterDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CXEngineRecordMasterDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON5, &CXEngineRecordMasterDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON4, &CXEngineRecordMasterDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON3, &CXEngineRecordMasterDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_CHECK1, &CXEngineRecordMasterDlg::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_CHECK2, &CXEngineRecordMasterDlg::OnBnClickedCheck2)
END_MESSAGE_MAP()


// CXEngineRecordMasterDlg 消息处理程序

BOOL CXEngineRecordMasterDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	m_EditPosX.SetWindowText(_T("0"));
	m_EditPosY.SetWindowText(_T("0"));
	m_EditFrameRate.SetWindowText(_T("24"));
	m_EditScreen.SetWindowText(_T("1920x1080"));

	memset(tszVideoFile, '\0', MAX_PATH);
	memset(tszAudioFile, '\0', MAX_PATH);

	pSt_File = NULL;
	pSt_AudioFile = NULL;
	pSt_VideoFile = NULL;
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CXEngineRecordMasterDlg::OnPaint()
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
HCURSOR CXEngineRecordMasterDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void _stdcall CXEngineRecordMasterDlg::XEngine_AVCollect_CBAudio(uint8_t* punStringAudio, int nVLen, LPVOID lParam)
{
	CXEngineRecordMasterDlg* pClass_This = (CXEngineRecordMasterDlg*)lParam;

	if (pClass_This->bRecord)
	{
		int nListCount = 0;
		AVCODEC_AUDIO_MSGBUFFER** ppSt_ListMsgBuffer;
		AudioCodec_Stream_EnCodec(pClass_This->xhAudio, punStringAudio, nVLen, &ppSt_ListMsgBuffer, &nListCount);
		for (int i = 0; i < nListCount; i++)
		{
			BYTE byAACHdr[8];
			AVHelp_Packet_AACHdr(byAACHdr, pClass_This->nSmpRate, pClass_This->nChannel, ppSt_ListMsgBuffer[i]->nMsgLen);

			fwrite(byAACHdr, 1, 7, pClass_This->pSt_AudioFile);
			fwrite(ppSt_ListMsgBuffer[i]->pbyMsgBuffer, 1, ppSt_ListMsgBuffer[i]->nMsgLen, pClass_This->pSt_AudioFile);
		}
		BaseLib_OperatorMemory_Free((void***)&ppSt_ListMsgBuffer, nListCount);
	}
}
void __stdcall CXEngineRecordMasterDlg::XEngine_AVCollect_CBScreen(uint8_t* punStringY, int nYLen, uint8_t* punStringU, int nULen, uint8_t* punStringV, int nVLen, LPVOID lParam)
{
	CXEngineRecordMasterDlg* pClass_This = (CXEngineRecordMasterDlg*)lParam;

	if (pClass_This->bRecord)
	{
		int nFLen = 1024 * 1024 * 10;
		int nELen = 1024 * 1024 * 10;
		TCHAR* ptszFilterBuffer = (TCHAR*)malloc(nFLen);
		TCHAR* ptszEncodeBuffer = (TCHAR*)malloc(nELen);
		if ((NULL == ptszFilterBuffer) || (NULL == ptszEncodeBuffer))
		{
			return;
		}
		memset(ptszFilterBuffer, '\0', nFLen);
		memset(ptszEncodeBuffer, '\0', nELen);

		if (pClass_This->bFilter)
		{
			if (VideoCodec_Help_FilterCvt(pClass_This->xhFilter, punStringY, punStringU, punStringV, nYLen, nULen, nVLen, (uint8_t*)ptszFilterBuffer, &nFLen))
			{
				VideoCodec_Stream_EnCodec(pClass_This->xhVideo, (uint8_t*)ptszFilterBuffer, NULL, NULL, nFLen, 0, 0, (uint8_t*)ptszEncodeBuffer, &nELen);
				if (nELen > 0)
				{
					fwrite(ptszEncodeBuffer, 1, nELen, pClass_This->pSt_VideoFile);
				}
			}
		}
		else
		{
			VideoCodec_Stream_EnCodec(pClass_This->xhVideo, punStringY, punStringU, punStringV, nYLen, nULen, nVLen, (uint8_t*)ptszEncodeBuffer, &nELen);
			if (nELen > 0)
			{
				fwrite(ptszEncodeBuffer, 1, nELen, pClass_This->pSt_VideoFile);
			}
		}
		free(ptszFilterBuffer);
		free(ptszEncodeBuffer);

		ptszFilterBuffer = NULL;
		ptszEncodeBuffer = NULL;
	}
	else
	{
		XClient_StreamPush_PushVideo(pClass_This->xhStream, punStringY, nYLen, punStringU, nULen, punStringV, nVLen);
	}
}
void __stdcall CXEngineRecordMasterDlg::XEngine_AVPacket_Callback(XNETHANDLE xhNet, int nCvtType, int nCvtFrame, double dlTime, LPVOID lParam)
{
	CXEngineRecordMasterDlg* pClass_This = (CXEngineRecordMasterDlg*)lParam;
	CString m_StrTipsType;
	
	m_StrTipsType.Format(_T("提示:正在打包...第 %d 个%s,当前时间:%lf"), nCvtFrame, nCvtType == 1 ? _T("视频帧") : _T("音频帧"), dlTime);
	pClass_This->m_StaticTips.SetWindowText(m_StrTipsType);
}
DWORD WINAPI CXEngineRecordMasterDlg::XEngine_AVPacket_Thread(LPVOID lParam)
{
	CXEngineRecordMasterDlg* pClass_This = (CXEngineRecordMasterDlg*)lParam;

	while (1)
	{
		BOOL bIsRun = FALSE;
		if (AVPacket_FilePacket_GetStatus(pClass_This->xhPacket, &bIsRun))
		{
			if (!bIsRun)
			{
				break;
			}
		}
		Sleep(1000);
	}
	AVPacket_FilePacket_Stop(pClass_This->xhPacket);

	DeleteFile(pClass_This->tszAudioFile);
	DeleteFile(pClass_This->tszVideoFile);
	pClass_This->m_StaticTips.SetWindowText(_T("提示:停止录制..."));

	pClass_This->m_BtnStart.EnableWindow(TRUE);
	pClass_This->m_BtnSuspend.EnableWindow(FALSE);
	pClass_This->m_BtnStop.EnableWindow(FALSE);
	pClass_This->m_BtnStart.SetWindowText(_T("开始录制"));
	return 0;
}

void CXEngineRecordMasterDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CString m_StrEditFile;
	CString m_StrEditScreen;
	CString m_StrEditPosX;
	CString m_StrEditPosY;
	CString m_StrEditRate;
	CString m_StrEditFrame;
	CString m_StrEditWaterMark;
	CString m_StrComboAudio;
	CString m_StrSMSUrl;
	
	TCHAR tszFileDir[MAX_PATH];
	XENGINE_PROTOCOL_AVINFO st_AVProtocol;

	memset(&st_AVProtocol, '\0', sizeof(XENGINE_PROTOCOL_AVINFO));

	m_EditSaveFile.GetWindowText(m_StrEditFile);
	m_EditScreen.GetWindowText(m_StrEditScreen);
	m_EditPosX.GetWindowText(m_StrEditPosX);
	m_EditPosY.GetWindowText(m_StrEditPosY);
	m_EditRate.GetWindowText(m_StrEditRate);
	m_EditFrameRate.GetWindowText(m_StrEditFrame);
	m_EditWatermark.GetWindowText(m_StrEditWaterMark);
	m_ComboxAudioList.GetWindowText(m_StrComboAudio);
	m_EditPushAddr.GetWindowText(m_StrSMSUrl);

	if (m_StrEditFile.IsEmpty() && m_StrSMSUrl.IsEmpty())
	{
		AfxMessageBox(_T("必须输入保存地址"));
		return;
	}
	
	//音频配置
	if (m_ComboxAudioList.GetCurSel() >= 0)
	{
		bRecord = TRUE;
		memset(tszFileDir, '\0', MAX_PATH);
		//获得路径名
		BaseLib_OperatorString_GetFileAndPath(m_StrEditFile.GetBuffer(), tszFileDir);

		_stprintf(tszAudioFile, _T("%s\\Audio.aac"), tszFileDir);
		pSt_AudioFile = _tfopen(tszAudioFile, _T("wb"));
		//选择后才启用
		if (!AVCollect_Audio_Init(&xhSound, m_StrComboAudio.GetBuffer(), XEngine_AVCollect_CBAudio, this))
		{
			AfxMessageBox(_T("初始化音频采集器失败"));
			return;
		}
		ENUM_AVCOLLECT_AUDIOSAMPLEFORMAT enAudioFmt;
		AVCollect_Audio_GetInfo(xhSound, &enAudioFmt, &nBitRate, &nSmpRate, &nChannel);

		if (BST_CHECKED == m_BtnCheckSave.GetCheck())
		{
			//文件保存需要的属性
			if (!AudioCodec_Stream_EnInit(&xhAudio, ENUM_AVCODEC_AUDIO_TYPE_AAC, nSmpRate, nChannel, nBitRate, 0, ENUM_AVCOLLECT_AUDIO_SAMPLE_FMT_FLTP))
			{
				AfxMessageBox(_T("初始化编码器失败"));
				return;
			}
			int nLen = 0;
			if (!AudioCodec_Stream_SetResample(xhAudio, &nLen, nSmpRate, nSmpRate, ENUM_AVCOLLECT_AUDIO_SAMPLE_FMT_S16, ENUM_AVCOLLECT_AUDIO_SAMPLE_FMT_FLTP, nChannel, nChannel))
			{
				AfxMessageBox(_T("初始化重采样工具失败"));
				return;
			}
		}
		if (BST_CHECKED == m_BtnCheckPush.GetCheck())
		{
			//推流需要的属性
			st_AVProtocol.st_PushAudio.bEnable = TRUE;
			st_AVProtocol.st_PushAudio.enAvCodec = ENUM_AVCODEC_AUDIO_TYPE_AAC;
			st_AVProtocol.st_PushAudio.nBitRate = nBitRate;
			st_AVProtocol.st_PushAudio.nChannel = nChannel;
			st_AVProtocol.st_PushAudio.nSampleFmt = ENUM_AVCOLLECT_AUDIO_SAMPLE_FMT_FLTP;
			st_AVProtocol.st_PushAudio.nSampleRate = nSmpRate;
		}
	}
	//屏幕配置
	if (!AVCollect_Screen_Init(&xhScreen, XEngine_AVCollect_CBScreen, this, m_StrEditScreen.GetBuffer(), _ttoi(m_StrEditPosX.GetBuffer()), _ttoi(m_StrEditPosY.GetBuffer()), _ttoi(m_StrEditFrame.GetBuffer())))
	{
		AfxMessageBox(_T("初始化屏幕采集失败"));
		return;
	}
	int nWidth = 0;
	int nHeight = 0;
	int64_t nBitRate = 0;
	
	AVCollect_Screen_GetInfo(xhScreen, &nWidth, &nHeight, &nBitRate);
	if (m_StrEditRate.IsEmpty())
	{
		m_StrEditRate.Format(_T("%lld"), nBitRate);
		m_EditRate.SetWindowText(m_StrEditRate);
	}
	else
	{
		nBitRate = _ttoi(m_StrEditRate.GetBuffer());
	}
	//是否需要保存
	if (BST_CHECKED == m_BtnCheckSave.GetCheck())
	{
		if (!VideoCodec_Stream_EnInit(&xhVideo, nWidth, nHeight, ENUM_ENTENGINE_AVCODEC_VEDIO_TYPE_H264, nBitRate))
		{
			AfxMessageBox(_T("初始化失败"));
			return;
		}
		if (m_StrEditWaterMark.IsEmpty())
		{
			bFilter = FALSE;
		}
		else
		{
			TCHAR tszFilterStr[MAX_PATH];
			memset(tszFilterStr, '\0', MAX_PATH);

			_stprintf(tszFilterStr, _T("drawtext=fontfile=Arial.ttf:fontcolor=green:fontsize=30:x=100:y=10:text='%s'"), m_StrEditWaterMark.GetBuffer());
			if (!VideoCodec_Help_FilterInit(&xhFilter, tszFilterStr, nWidth, nHeight, ENUM_AVCOLLECT_VIDEO_FMT_YUV420P, 24))
			{
				AfxMessageBox(_T("初始化过滤器失败"));
				return;
			}
			bFilter = TRUE;
		}
		_stprintf(tszVideoFile, _T("%s\\Video.h264"), tszFileDir);
		pSt_VideoFile = _tfopen(tszVideoFile, _T("wb"));
	}
	//是否需要推流
	if (BST_CHECKED == m_BtnCheckPush.GetCheck())
	{
		st_AVProtocol.st_PushVideo.bEnable = TRUE;
		st_AVProtocol.st_PushVideo.enAvCodec = ENUM_ENTENGINE_AVCODEC_VEDIO_TYPE_H264;
		st_AVProtocol.st_PushVideo.nBitRate = nBitRate;
		st_AVProtocol.st_PushVideo.nFrameRate = 24;
		st_AVProtocol.st_PushVideo.nHeight = nHeight;
		st_AVProtocol.st_PushVideo.nWidth = nWidth;
		
		if (!XClient_StreamPush_Init(&xhStream, m_StrSMSUrl.GetBuffer(), &st_AVProtocol, "flv"))
		{
			AfxMessageBox(_T("推送初始化失败,无法继续"));
			return;
		}
	}
	AVCollect_Screen_Start(xhScreen);
	AVCollect_Audio_Start(xhSound);

	m_BtnStart.EnableWindow(FALSE);
	m_BtnSuspend.EnableWindow(TRUE);
	m_BtnStop.EnableWindow(TRUE);

	m_StaticTips.SetWindowText(_T("提示:正在录制..."));
}


void CXEngineRecordMasterDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	int nACount = 0;
	int nVCount = 0;
	AVHELP_DEVICEINFO** ppSt_AudioList;
	AVHELP_DEVICEINFO** ppSt_VideoList;

	AVHelp_Device_EnumDevice(&ppSt_AudioList, &ppSt_VideoList, &nACount, &nVCount);
	for (int i = 0; i < nACount; i++)
	{
		m_ComboxAudioList.AddString(ppSt_AudioList[i]->tszName);
	}
	BaseLib_OperatorMemory_Free((void***)&ppSt_AudioList, nACount);
	BaseLib_OperatorMemory_Free((void***)&ppSt_VideoList, nVCount);
}


void CXEngineRecordMasterDlg::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	AVCollect_Screen_Destory(xhScreen);
	AVCollect_Audio_Destory(xhSound);
	VideoCodec_Stream_Destroy(xhVideo);
	AudioCodec_Stream_Destroy(xhAudio);
	VideoCodec_Help_FilterDestroy(xhFilter);
	XClient_StreamPush_Close(xhStream);

	if (NULL != pSt_VideoFile)
	{
		fclose(pSt_VideoFile);
	}
	if (NULL != pSt_AudioFile)
	{
		fclose(pSt_AudioFile);
	}

	//是否需要打包
	if (_tcslen(tszVideoFile) > 0)
	{
		double dlVideoTime = 0;
		double dlAudioTime = 0;
		m_StaticTips.SetWindowText(_T("提示:正在打包..."));
		if (!AVPacket_FilePacket_Init(&xhPacket, XEngine_AVPacket_Callback, this))
		{
			AfxMessageBox(_T("初始化打包工具失败"));
			return;
		}
		AVPacket_FilePacket_Input(xhPacket, tszVideoFile, &dlVideoTime);
		if (_tcslen(tszAudioFile) > 0)
		{
			AVPacket_FilePacket_Input(xhPacket, tszAudioFile, &dlAudioTime);
		}
		CString m_StrFile;
		m_EditSaveFile.GetWindowText(m_StrFile);
		if (!AVPacket_FilePacket_Output(xhPacket, m_StrFile))
		{
			AfxMessageBox(_T("设置输出失败"));
			return;
		}
		if (!AVPacket_FilePacket_Start(xhPacket))
		{
			AfxMessageBox(_T("开始打包失败"));
			return;
		}
		HANDLE hThread = CreateThread(NULL, 0, XEngine_AVPacket_Thread, this, 0, NULL);
		CloseHandle(hThread);
	}
}


void CXEngineRecordMasterDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	bRecord = FALSE;

	m_BtnStart.EnableWindow(TRUE);
	m_BtnSuspend.EnableWindow(FALSE);
	m_BtnStop.EnableWindow(TRUE);

	m_BtnStart.SetWindowText(_T("继续录制"));
	m_StaticTips.SetWindowText(_T("提示:暂停录制..."));
}


void CXEngineRecordMasterDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	TCHAR tszDir[MAX_PATH];
	memset(tszDir, '\0', MAX_PATH);

	OPENFILENAME st_FileDir;  
	memset(&st_FileDir, '\0', sizeof(OPENFILENAME));

	st_FileDir.lStructSize = sizeof(OPENFILENAME);
	st_FileDir.hwndOwner = this->m_hWnd;                 
	st_FileDir.lpstrFile = tszDir;                      //返回的文件路径
	st_FileDir.nMaxFile = MAX_PATH;
	st_FileDir.lpstrFilter = _T("mp4 视频文件(*.mp4)\0*.mp4\0所有文件(*.*)\0*.*\0"); 
	st_FileDir.nFilterIndex = 1;                        //指定当前过滤器索引,2即是所有文件
	st_FileDir.Flags = OFN_FILEMUSTEXIST   //指定用户仅可以在文件名登录字段中输入已存在的文件的名字。
		| OFN_EXPLORER                     //指出任何打开或另存为对话框使用新的Explorer风格的用户化模块。
		| OFN_HIDEREADONLY                 //隐藏只读复选框
		| OFN_OVERWRITEPROMPT;             //提醒用户否复盖这个文件。
	
	if (GetSaveFileName(&st_FileDir))
	{
		_tcscat(tszDir, _T(".mp4"));
		m_EditSaveFile.SetWindowText(tszDir);
	}
}


void CXEngineRecordMasterDlg::OnBnClickedCheck1()
{
	// TODO: 在此添加控件通知处理程序代码
	if (BST_CHECKED == m_BtnCheckPush.GetCheck())
	{
		m_EditPushAddr.EnableWindow(TRUE);
	}
	else
	{
		m_EditPushAddr.EnableWindow(FALSE);
	}
}


void CXEngineRecordMasterDlg::OnBnClickedCheck2()
{
	// TODO: 在此添加控件通知处理程序代码
	if (BST_CHECKED == m_BtnCheckSave.GetCheck())
	{
		m_EditSaveFile.EnableWindow(TRUE);
	}
	else
	{
		m_EditSaveFile.EnableWindow(FALSE);
	}
}
