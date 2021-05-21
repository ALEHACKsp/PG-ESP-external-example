#pragma once
#include "encrypt.cpp"
#include <map>
#include <algorithm>
#include <tchar.h>
#include <ctime>
#include <iostream>
#include "VMProtectSDK.h"
using std::wstring;
using std::map;

struct Config
{
	bool bPlayerHealthESP = false;
	bool bDistanceESP = false;
	bool bLineESP = false;

	bool bPlayerNameESP = false;
	bool bRadarESP = false;
	bool bSkeletonESP = false;
	float MaxSkeletonDistance = 100.f;
	bool bDrawBones = false;
	bool bShowLoot = false;
	bool bVehicleESP = false;

	bool bDowned = false;
	bool bDownedDistance = false;
	bool bDownedHP = false;
	bool bDownedTimeToDie = false;

	bool bShowLocalMarker = false;
	bool bShowTeamMarker = false;
	bool bAirDrop = false;
	bool bAirdropContents = false;
	bool BoxESP = false;
	float BoxDistance = 100.f;
	int BoxType = -1;

	bool bNoRecoil = false;
	bool bNoSway = false;
	bool bFastFireRate = false;
	bool bFastBullets = false;
	bool bNoMuzzle = false;
	bool bNoSpread = false;

	bool bDebugMode = false;
	bool bLogIds = false;

	bool bAimbot = false;
	float FOV = 10.f;
	bool bDrawFOV = false;
	float Smooth = 100.f;
	float MaxDist = 0.f;
	std::string aimkey = "sidebtn";
	bool bVelocityPrediction = false;
	bool bBulletDropPrediction = false; //TODO
	int aimbotBone = -1;
	bool ShowAimLockBone = false;
	bool ShowLockIndication = false;
	int LockIndicationType = -1;
	bool locktarget = false;

	bool bAutoLogin = false;
	std::string username = "FORUM_USERNAME";
	std::string password = "FORUM_PASSWORD";

	/*
	//Colors 
	ImVec4 SkelColorIMGUI = ImColor(1, 0, 0);
	int SkeletonWidth = 1;
	ImVec4 BoxColorIMGUI = ImColor(1, 0, 0);
	int BoxWidth = 1;

	ImVec4 DrawFOVIMGUI = ImColor(0, 0, 0);

	ImVec4 Distance280IMGUI = ImColor(1, 1, 1);
	ImVec4 Distance560IMGUI = ImColor(1, 0, 0);
	ImVec4 DistanceMorethan560IMGUI = ImColor(0, 0, 1);

	ImVec4 LootDefaultColor = ImColor(0, 0, 1);
	ImVec4 LootL1 = ImColor(0, 0, 1);
	ImVec4 LootL2 = ImColor(0, 0, 1);
	ImVec4 LootL3 = ImColor(0, 0, 1);
	ImVec4 LootGuns = ImColor(0, 0, 1);
	ImVec4 LootAttachements = ImColor(0, 0, 1);
	ImVec4 LootMedical = ImColor(0, 0, 1);
	ImVec4 LootAmmo = ImColor(0, 0, 1);
	ImVec4 LootScopes = ImColor(0, 0, 1);
	ImVec4 LootCustom = ImColor(0, 0, 1);
	*/
	float TextMultiplier = 1;
	int TextFont = 0;
	bool TextOutile = false;

//	ImVec4 AimbotLockColour = ImColor(0, 0, 1);
//	ImVec4 AimbotLockBoneColour = ImColor(0, 0, 1);
	float BoneLockrad = 10.f;

	bool bLootESP = false;
	bool bLootDistanceESP = false;

	//Loot options
	bool
		bLootFilterNone = false,
		bLootFilterL1 = false,
		bLootFilterL2 = false,
		bLootFilterL3 = false,
		bLootFilterGuns = false,
		bLootFilterAttachments = false,
		bAmmoLoot = false,
		bMedicalLoot = false,
		bScopesLoot = false,
		bCustomFilter = false;

	int iSleepRate = 10; // Optimization 

	bool AutoScale = true;
	int ScreenH = 1080;
	int ScreenW = 1920;
	float flOverlayOffset = 0.0f;
};
struct Color {
	float A;
	float R;
	float G;
	float B;
};
int 取时间戳()
{
	return time(NULL);
}

static map<std::wstring, std::string> 空投骨灰盒篩選 = {
{ L"Ghillie Suit","【空投: 吉利服】"},
{ L"M24","【空投: M24】" },
{ L"AWM","【空投: AWM】" },
{ L"Mk14","【空投: Mk14】" },
{ L"AUG","【空投: AUG】" },
{ L"Groza","【空投: Groza】" },
{ L"M249","【空投: M249】" },
{ L".300 Magnum","【空投: AWM子彈】" },
{ L"Helmet (Lv.3)","頭盔Lv.3" },
{ L"Backpack (Lv.3)","背包Lv.3" },
{ L"Military Vest (Lv.3)","防彈衣Lv.3" },
{ L"Helmet (Lv.2)","頭盔Lv.2" },
{ L"Backpack (Lv.2) ","背包Lv.2" },
{ L"Police Vest (Lv.2)","防彈衣Lv.2" },
{ L"7.62mm","762子彈" },
{ L"5.56mm","556子彈" },
{ L"9mm","9毫米子彈" },
{ L"Red Dot Sight","紅點" },
{ L"2x Scope","2倍鏡" },
{ L"4x Scope","4倍鏡" },
{ L"8x Scope","8倍鏡" },
{ L"15x Scope","15倍鏡" },
{ L"Mini14","Mini14" },
{ L"Kar98k","Kar98k" },
{ L"M416","M416" },
{ L"M16A4","M16A4" },
{ L"SCAR-L","SCAR-L" },
{ L"Suppressor (AR, S12K)","步槍消音" },
{ L"Compensator(AR, S12K)","步槍補償" },
{ L"Ext.QuickDraw Mag(AR, S12K)","步槍快擴" },
{ L"Tactical Stock (M416, Vector)","戰術槍托" },
{ L"Vertical Foregrip (AR, SMG, SR)","垂直握把" },
{ L"Angled Foregrip (AR, SMG, SR)","直角握把" },
{ L"SKS","SKS" },
{ L"VSS","VSS" },
{ L"Suppressor (SR)","狙擊消音" },
{ L"Compensator(SR)","狙擊補償" },
{ L"Ext. QuickDraw Mag (SR)", "狙擊快擴" },
{ L"Cheek Pad (SR)","狙擊托腮板" },
{ L"Bullet Loops (Kar98k)","Kar98k子彈袋" },
{ L"AKM","AKM" },
{ L"DP-28","DP-28" },
{ L"Win94","Win94" },
{ L"Sawed-off","Sawed-off" },
{ L"Micro UZI","烏茲" },
{ L"Vector","Vector" },
{ L"UMP9","UMP9" },
{ L"Tommy Gun","湯姆遜" },
{ L"S686","S686" },
{ L"S12K","S12K" },
{ L"Pan", "平底鍋" },
{ L"Med Kit","醫療箱" },
{ L"First Aid Kit","急救包" },
{ L"Paiikiller","止痛藥" },
{ L"Energy Drink","飲料" },
{ L"Frag Grenade", "手榴彈" }};
//其他
bool 飲料;
bool 繃帶;
bool 醫療箱;
bool 急救包;
bool 止痛藥;
bool 平底鍋;
bool 手榴彈;
bool 煙霧彈;
bool 閃光彈;
bool 燃燒瓶;
bool 二級頭盔;
bool 三級頭盔;
bool 二級背包;
bool 三級背包;
bool 二級防彈衣;
bool 三級防彈衣;
int 其他物品顯示篩選 = -1;
//武器
bool AKM;
bool M416;
bool M16A4;
bool SCAR;
bool VSS;
bool SKS;
bool MINI14;
bool KAR98K;
bool DP28;
bool WIN94;
bool SAWED;
bool UZI;
bool UMP9;
bool VECTOR;
bool TOMMYGUN;
bool S12K;
bool S686;
bool S1897;
bool CROSSBOW;

int 槍械物品菜單選項 = -1;//VV剩下下面翻譯
				  //配件
bool x2;
bool x4;
bool x8;
bool 全息;
bool 紅點;
bool 槍托;
bool 戰術槍托;
bool 垂直握把;
bool 直角握把;
bool 衝鋒消音;
bool 衝鋒消焰;
bool 衝鋒補償;
bool 衝鋒快擴;
bool 步槍消音;
bool 步槍消焰;
bool 步槍補償;
bool 步槍快擴;
bool 狙擊消音;
bool 狙擊消焰;
bool 狙擊補償;
bool 狙擊快擴;
bool 散彈收束器;
bool 狙擊托腮板;
bool 散彈子彈袋;
bool 狙擊子彈袋;
int 取時間戳()
{
	return time(NULL);
}

long 時間 = 取時間戳();
char *GetDirectoryFile(char *filename)
{
	static char path[20000];
	char dlldir[20000];
	strcpy(path, dlldir);
	strcat(path, filename);
	return path;
}
namespace 顏色
{
	Color 顏色[14] = { Color{ 255, 240, 240, 240 },
		
		(Color{ 255, 255, 0, 0 }),
		(Color{ 255, 255, 0, 128 }),
		(Color{ 255, 0, 255, 0 }),
		(Color{ 255, 255, 215, 0 }),
		(Color{ 255, 255, 0, 255 }),
		(Color{ 255, 0, 255, 255 }),
		(Color{ 255, 124, 252, 0 }),
		(Color{ 255, 128, 255, 128 }),
		(Color{ 255, 128, 128, 255 }),
		(Color{ 255, 255, 128, 64 }),
		(Color{ 255, 0, 0, 0 }),
		(Color{ 200, 100, 200, 255 }),
		(Color{ 200, 255, 155, 0 })
		
};
	int 透明數值 = 0;


	int 方框顏色參數;
	int 骨骼顏色參數;
	int 準心顏色參數;
	int 射線顏色參數;
	int 預警顏色參數;
	int 車輛顏色參數;
	int 空投顏色參數;
	int 骨灰盒顏色參數;
	int 物品列表顏色參數;
	int 槍械武器顏色參數;
	int 普通物品顏色參數;
	int 高級物品顏色參數;
	int 敵人近距離顏色參數;
	int 敵人中距離顏色參數;
	int 敵人遠距離顏色參數;
		int 敵人強弱顏色 = 0;
	int 自訂顏色菜單選項 = 0;
}

namespace 菜單
{

	bool 主菜單顯示開關 = true;
	bool 顯示相關設置開關 = false;
	bool 射擊相關設置開關= false;
	bool 變態功能設置開關= false;
	bool 槍械物品篩選開關 = false;
	bool 配件物品篩選開關 = false;
	bool 其他物品篩選開關 = false;
	bool 顯示優化設置開關 = false;

	int 主菜單選項 = -1;
}

namespace 顯示相關設置
{
	bool 物品透視;
	bool 空投透視;
	bool 骨灰盒透視;
	bool 顯示槍;
	bool 顯示子彈;
	bool 顯示配件;
	bool 顯示藥;
	bool 顯示倍鏡;
	bool 顯示自訂;
	//菜單类
	int 顯示人物風格;
	bool 顯示人物血條;
	bool 顯示人物距離;
	bool 顯示地圖雷達;
	bool 附近敵人預警開關;
	int 附近敵人預警距離;
	int 人物最大顯示距離;
	int 物品最大顯示距離;
	int 載具最大顯示距離;
	int 訊息顯示半徑;
	//其他类
	bool 戰鬥模式開關;
	//敌人距離
	int 敵人近距離;
	int 敵人中距離;
	int 敵人遠距離 = 1000;

	int 透視相關選項 = -1;
}

namespace 射擊相關設置
{
	int 射擊位置[4] = { 12, 5, 4, 2 };
	int 射擊按鍵[5] = { 2, 1, 81, 69, 16 };
	bool 內存自瞄;
	bool 是否鎖定;
	bool 鎖定追蹤;
	int 射擊範圍;
	int 射擊距離;
	int 位置參數;
	int 按鍵參數;
	bool 十字準心;
	bool 可視射線;
	bool 快速鎖頭;
	int 機瞄放大;
	int 放大係數;
	bool 清除抖動;
	int 射擊菜單選項 = -1;
}

namespace 變態功能設置
{
	bool 肢體強化 = false;
	bool 跳躍穿牆 = false;
	int 跳躍高度 = 0;
	bool 超級連跳 = false;
	bool 無情瞬殺 = false;
	bool 瞬移載具 = false;
	bool 瞬移空投 = false;
	bool 上帝模式 = false;
	int 變態功能菜單當前選項;
}

namespace 顯示優化設置
{
	bool 抽幀優化;	
	int 優化延遲 = 50;
	int 遊戲透明度 = 50;
	int 遊戲加碼值= 80;
	int 顯示優化菜單當前選項;
}

namespace 顯示篩選
{
	//子彈
	bool 子彈762;
	bool 子彈556;
	//其他
	bool 飲料;
	bool 繃帶;
	bool 醫療箱;
	bool 急救包;
	bool 止痛藥;
	bool 腎上腺素;
	bool 平底鍋;
	bool 手榴彈;
	bool 煙霧彈;
	bool 閃光彈;
	bool 燃燒瓶;
	bool 二級頭盔;
	bool 三級頭盔;
	bool 二級背包;
	bool 三級背包;
	bool 二級防彈衣;
	bool 三級防彈衣;
	int 其他物品顯示篩選 = -1;
	//武器
	bool AKM;
	bool M416;
	bool M16A4;
	bool SCAR;
	bool VSS;
	bool SKS;
	bool MINI14;
	bool KAR98K;
	bool DP28;
	bool WIN94;
	bool SAWED;
	bool UZI;
	bool UMP9;
	bool VECTOR;
	bool TOMMYGUN;
	bool S12K;
	bool S686;
	bool S1897;
	bool CROSSBOW;

	bool M24;
	bool QBU;
	bool SLR;
	bool Mk47Mutan;
	bool BerylM762;
	bool QBZ;
	int 槍械物品菜單選項 = -1;//VV剩下下面翻譯
	//配件
	bool x2;
	bool x3;
	bool x4;
	bool x6;
	bool x8;
	bool 全息;
	bool 紅點;
	bool 雷射瞄準器;
	bool 槍托;
	bool 戰術槍托;
	bool 垂直握把;
	bool 直角握把;
	bool 衝鋒消音;
	bool 衝鋒消焰;
	bool 衝鋒補償;
	bool 衝鋒快擴;
	bool 步槍消音;
	bool 步槍消焰;
	bool 步槍補償;
	bool 步槍快擴;
	bool 狙擊消音;
	bool 狙擊消焰;
	bool 狙擊補償;
	bool 狙擊快擴;
	bool 散彈收束器;
	bool 狙擊托腮板;
	bool 散彈子彈袋;
	bool 狙擊子彈袋;
	bool 半截式握把;
	bool 輕型握把;
	bool 拇指握把;
	int 配件物品透視菜單選項= -1;
}



void 設置遊戲透明度(int tm) 
{
	HWND 遊戲窗口句炳= FindWindow(VMProtectDecryptStringA("UnrealWindow"), NULL);
	LONG nRet = ::GetWindowLong(遊戲窗口句炳, GWL_EXSTYLE);
	nRet = nRet | WS_EX_LAYERED;
	::SetWindowLong(遊戲窗口句炳, GWL_EXSTYLE, nRet);
	::SetLayeredWindowAttributes(遊戲窗口句炳, 0, tm, LWA_ALPHA);
}
void 恢复遊戲透明度()
{
	HWND 遊戲窗口句炳 = FindWindow(VMProtectDecryptStringA("UnrealWindow"), NULL);
	LONG nRet = ::GetWindowLong(遊戲窗口句炳, GWL_EXSTYLE);
	nRet = nRet | WS_EX_LAYERED;
	SetWindowLong(遊戲窗口句炳, GWL_EXSTYLE, nRet);
	::SetLayeredWindowAttributes(遊戲窗口句炳, 0, 255, LWA_ALPHA);
}
void 設置顯示器加碼值(int gm)
{
	BOOL bReturn = FALSE;
	HDC hGammaDC = NULL;

	if (hGammaDC == NULL)
		hGammaDC = GetDC(NULL);

	if (hGammaDC != NULL)
	{

		WORD GammaArray[3][256];

		for (int iIndex = 0; iIndex < 256; iIndex++)
		{
			int iArrayValue = iIndex * (gm + 128);

			if (iArrayValue > 65535)
				iArrayValue = 65535;

			GammaArray[0][iIndex] =
				GammaArray[1][iIndex] =
				GammaArray[2][iIndex] = (WORD)iArrayValue;

		}

		SetDeviceGammaRamp(hGammaDC, GammaArray);
	}
}

void 載入()
{
	設置遊戲透明度(顯示優化設置::遊戲透明度 * 2.55);
	設置顯示器加碼值(顯示優化設置::遊戲加碼值 * 2.55);

}

void 恢复()
{
	恢复遊戲透明度();
	設置顯示器加碼值(120);
}
void SetColor(unsigned short ForeColor = 0, unsigned short BackGroundColor = 0)
{
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hCon, ForeColor | BackGroundColor);
}


/*
typedef int(WINAPI *InitDX11)(HWND Hwnd, const char* ttf, int size);
typedef int(WINAPI *DestoryDX11)(HWND hwnd);
typedef int(WINAPI *DrawBegin)();
typedef int(WINAPI * DrawEnd)();
//DLL_DEMO void __stdcall ImGuiWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
typedef int(WINAPI * DrawNewText)(int x, int y, float R, float G, float B, float A, const char* str);
typedef int(WINAPI *DrawCircleFilled)(int x, int y, int radius, float R, float G, float B, float A, int segments);
typedef int(WINAPI *DrawCircle)(int x, int y, int radius, float R, float G, float B, float A, int segments, int thickness);
typedef int(WINAPI *DrawRect)(int x, int y, int w, int h, float R, float G, float B, float A, int thickness);
typedef int(WINAPI *DrawFilledRect)(int x, int y, int w, int h, float R, float G, float B , float A );
typedef int(WINAPI *DrawLine)(int x1, int y1, int x2, int y2, float R, float G, float B, float A, int thickness);
typedef int(WINAPI * DrawImage)(int x, int y, int w, int h, LPCSTR MyImage);


InitDX11 initd3d11 = NULL;
DestoryDX11 uninstallDraw = NULL;
DrawBegin drawbegin = NULL;
DrawEnd drawend = NULL;
DrawNewText drawString = NULL;
DrawCircleFilled drawcirclefilled = NULL;
DrawCircle drawcircle = NULL;
DrawRect drawrect = NULL;
DrawFilledRect drawfilledrect = NULL;
DrawLine drawline = NULL;
DrawImage drawimage = NULL;
//颜色

bool LoadDll() {

	HMODULE hModuleDll = LoadLibrary(_T("dx11.dll"));

	if (NULL != hModuleDll)
	{

		Sleep(10);
		initd3d11 = (InitDX11)GetProcAddress(hModuleDll, "InitDX11");
		Sleep(10);
		uninstallDraw = (DestoryDX11)GetProcAddress(hModuleDll, "DestoryDX11");
		Sleep(10);
		drawbegin = (DrawBegin)GetProcAddress(hModuleDll, "DrawBegin");
		Sleep(10);
		drawend = (DrawEnd)GetProcAddress(hModuleDll, "DrawEnd");
		Sleep(10);
		drawString = (DrawNewText)GetProcAddress(hModuleDll, "DrawNewText");
		Sleep(10);
		drawcirclefilled = (DrawCircleFilled)GetProcAddress(hModuleDll, "DrawCircleFilled");
		Sleep(10);
		drawcircle = (DrawCircle)GetProcAddress(hModuleDll, "DrawCircle");
		Sleep(10);
		drawrect = (DrawRect)GetProcAddress(hModuleDll, "DrawRect");
		Sleep(10);
		drawfilledrect = (DrawFilledRect)GetProcAddress(hModuleDll, "DrawFilledRect");
		Sleep(10);
		drawline = (DrawLine)GetProcAddress(hModuleDll, "DrawLine");
		Sleep(10);
		drawimage = (DrawImage)GetProcAddress(hModuleDll, "DrawImage");
		Sleep(10);
		MessageBox(NULL, "[IMGUI版本]Dx11注入成功!!", "系統提示", NULL);
		return true;
	}
	else {
		Sleep(50);
		MessageBox(NULL, "[IMGUI版本]注入失敗,請使用系統管理員開啟!!", "系統提示", NULL);
		return false;
	}
}
*/
