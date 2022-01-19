// pch.h: 这是预编译标头文件。
// 下方列出的文件仅编译一次，提高了将来生成的生成性能。
// 这还将影响 IntelliSense 性能，包括代码完成和许多代码浏览功能。
// 但是，如果此处列出的文件中的任何一个在生成之间有更新，它们全部都将被重新编译。
// 请勿在此处添加要频繁更新的文件，这将使得性能优势无效。

#ifndef PCH_H
#define PCH_H

// 添加要在此处预编译的标头
#include "framework.h"

#endif //PCH_H
#include <list>

using namespace std;
#include <XEngine_Include/XEngine_CommHdr.h>
#include <XEngine_Include/XEngine_ProtocolHdr.h>
#include <XEngine_Include/XEngine_BaseLib/BaseLib_Define.h>
#include <XEngine_Include/XEngine_BaseLib/BaseLib_Error.h>
#include <XEngine_Include/XEngine_AVCoder/AVCollect_Define.h>
#include <XEngine_Include/XEngine_AVCoder/AVCollect_Error.h>
#include <XEngine_Include/XEngine_AVCoder/AudioCoder_Define.h>
#include <XEngine_Include/XEngine_AVCoder/AudioCoder_Error.h>
#include <XEngine_Include/XEngine_AVCoder/VideoCoder_Define.h>
#include <XEngine_Include/XEngine_AVCoder/VideoCoder_Error.h>
#include <XEngine_Include/XEngine_AVCoder/AVHelp_Define.h>
#include <XEngine_Include/XEngine_AVCoder/AVHelp_Error.h>
#include <XEngine_Include/XEngine_AVCoder/AVPacket_Define.h>
#include <XEngine_Include/XEngine_AVCoder/AVPacket_Error.h>
#include <XEngine_Include/XEngine_StreamMedia/XClient_Define.h>
#include <XEngine_Include/XEngine_StreamMedia/XClient_Error.h>

#pragma comment(lib,"XEngine_BaseLib/XEngine_BaseLib.lib")
#pragma comment(lib,"XEngine_AVCoder/XEngine_AudioCoder.lib")
#pragma comment(lib,"XEngine_AVCoder/XEngine_AVCollect.lib")
#pragma comment(lib,"XEngine_AVCoder/XEngine_AVPacket.lib")
#pragma comment(lib,"XEngine_AVCoder/XEngine_VideoCoder.lib")
#pragma comment(lib,"XEngine_AVCoder/XEngine_AVHelp.lib")
#pragma comment(lib,"XEngine_StreamMedia/StreamMedia_XClient.lib")

#if XENGINE_VERSION_BIT < 7280001001
#error Need XEngine V7.28.0.1001
#endif