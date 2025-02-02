#pragma once
#define WIN32_LEAN_AND_MEAN             // 从 Windows 头中排除极少使用的资料
#include <shlobj.h>
#include <shellapi.h>
#include <commdlg.h>
#include <time.h>
#pragma comment(lib,"shell32.lib")

// DM
#include "DmMainOutput.h"

// 依赖的dui
#include "DUIButton.h"
#include "DUIComboBox.h"
#include "DUICheckBox.h"
#include "DUIEdit.h"
#include "DUIMenu.h"
#include "DUIStatic.h"
#include "DUITabCtrl.h"
#include "DUIFlowLayout.h"
#include "DUIListBoxEx.h"
#include "DUIListCtrlEx.h"

// lib
#ifdef _DEBUG
#pragma comment(lib,"DmMain_d.lib")
#else
#pragma comment(lib,"DmMain.lib")
#endif

using namespace DM;

// DS
#include "Define.h"
#include "Helper.h"
#include "Events.h"
#include "Layout.h"
#include "DUIDragFrame.h"
#include "DUIPos.h"
#include "DUITreeEx.h"
#include "DUIRect.h"
#include "DUISize.h"
#include "DUIPropCtrl.h"
#include "DUILimitEdit.h"
#include "DUImgEditor.h"
#include "DUIObjEditor.h"
#include "DUIList.h"
#include "ObjTree.h"
#include "ProjTree.h"

#include "AttrExpandWnd.h"
#include "TipWnd.h"
#include "MsgBox.h"
#include "ScanDlg.h"
#include "SkinDlg.h"
#include "PoolDlg.h"
#include "ImgTypeDlg.h"
#include "ThemeDlg.h"
#include "ImgDlg.h"
#include "StyleDlg.h"
#include "LayoutDlg.h"
#include "PreHWnd.h"



#include "Data.h"

#include "ResMultFolder.h"

#include "AttrBase.h"
#include "NameAttr.h"
#include "HostAttr.h"
#include "WidgetAttr.h"
#include "PosAttr.h"
#include "AddXml.h"
#include "RightXml.h"
#include "ProjXml.h"
#include "ObjXml.h"
#include "DMDesignerWnd.h"


#if _MSC_VER==1500
#include "vld.h"
#pragma comment(lib, "vld.lib")// VLD仅在mDd模式下才能有效，其他v s版本请使用其他版本vld
#endif

extern DMDesignerWnd* g_pMainWnd;
extern DMLazyT<DMCtrlXml> g_pAttr;
extern DMSmartPtrT<ResMultFolder> g_pRes;