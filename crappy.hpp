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
int ȡʱ���()
{
	return time(NULL);
}

static map<std::wstring, std::string> ��Ͷ�ǻҺкY�x = {
{ L"Ghillie Suit","����Ͷ: ��������"},
{ L"M24","����Ͷ: M24��" },
{ L"AWM","����Ͷ: AWM��" },
{ L"Mk14","����Ͷ: Mk14��" },
{ L"AUG","����Ͷ: AUG��" },
{ L"Groza","����Ͷ: Groza��" },
{ L"M249","����Ͷ: M249��" },
{ L".300 Magnum","����Ͷ: AWM�ӏ���" },
{ L"Helmet (Lv.3)","�^��Lv.3" },
{ L"Backpack (Lv.3)","����Lv.3" },
{ L"Military Vest (Lv.3)","������Lv.3" },
{ L"Helmet (Lv.2)","�^��Lv.2" },
{ L"Backpack (Lv.2) ","����Lv.2" },
{ L"Police Vest (Lv.2)","������Lv.2" },
{ L"7.62mm","762�ӏ�" },
{ L"5.56mm","556�ӏ�" },
{ L"9mm","9�����ӏ�" },
{ L"Red Dot Sight","�t�c" },
{ L"2x Scope","2���R" },
{ L"4x Scope","4���R" },
{ L"8x Scope","8���R" },
{ L"15x Scope","15���R" },
{ L"Mini14","Mini14" },
{ L"Kar98k","Kar98k" },
{ L"M416","M416" },
{ L"M16A4","M16A4" },
{ L"SCAR-L","SCAR-L" },
{ L"Suppressor (AR, S12K)","��������" },
{ L"Compensator(AR, S12K)","�����a��" },
{ L"Ext.QuickDraw Mag(AR, S12K)","������U" },
{ L"Tactical Stock (M416, Vector)","���g����" },
{ L"Vertical Foregrip (AR, SMG, SR)","��ֱ�հ�" },
{ L"Angled Foregrip (AR, SMG, SR)","ֱ���հ�" },
{ L"SKS","SKS" },
{ L"VSS","VSS" },
{ L"Suppressor (SR)","�ѓ�����" },
{ L"Compensator(SR)","�ѓ��a��" },
{ L"Ext. QuickDraw Mag (SR)", "�ѓ���U" },
{ L"Cheek Pad (SR)","�ѓ�������" },
{ L"Bullet Loops (Kar98k)","Kar98k�ӏ���" },
{ L"AKM","AKM" },
{ L"DP-28","DP-28" },
{ L"Win94","Win94" },
{ L"Sawed-off","Sawed-off" },
{ L"Micro UZI","��Ɲ" },
{ L"Vector","Vector" },
{ L"UMP9","UMP9" },
{ L"Tommy Gun","��ķ�d" },
{ L"S686","S686" },
{ L"S12K","S12K" },
{ L"Pan", "ƽ���" },
{ L"Med Kit","�t����" },
{ L"First Aid Kit","���Ȱ�" },
{ L"Paiikiller","ֹʹˎ" },
{ L"Energy Drink","���" },
{ L"Frag Grenade", "����" }};
//����
bool ���;
bool ����;
bool �t����;
bool ���Ȱ�;
bool ֹʹˎ;
bool ƽ���;
bool ����;
bool ���F��;
bool �W�⏗;
bool ȼ��ƿ;
bool �����^��;
bool �����^��;
bool ��������;
bool ��������;
bool ����������;
bool ����������;
int ������Ʒ�@ʾ�Y�x = -1;
//����
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

int ��е��Ʒ�ˆ��x� = -1;//VVʣ�����淭�g
				  //���
bool x2;
bool x4;
bool x8;
bool ȫϢ;
bool �t�c;
bool ����;
bool ���g����;
bool ��ֱ�հ�;
bool ֱ���հ�;
bool �n�h����;
bool �n�h����;
bool �n�h�a��;
bool �n�h��U;
bool ��������;
bool ��������;
bool �����a��;
bool ������U;
bool �ѓ�����;
bool �ѓ�����;
bool �ѓ��a��;
bool �ѓ���U;
bool ɢ��������;
bool �ѓ�������;
bool ɢ���ӏ���;
bool �ѓ��ӏ���;
int ȡ�r�g��()
{
	return time(NULL);
}

long �r�g = ȡ�r�g��();
char *GetDirectoryFile(char *filename)
{
	static char path[20000];
	char dlldir[20000];
	strcpy(path, dlldir);
	strcat(path, filename);
	return path;
}
namespace �ɫ
{
	Color �ɫ[14] = { Color{ 255, 240, 240, 240 },
		
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
	int ͸����ֵ = 0;


	int �����ɫ����;
	int �����ɫ����;
	int �����ɫ����;
	int �侀�ɫ����;
	int �A���ɫ����;
	int ܇�v�ɫ����;
	int ��Ͷ�ɫ����;
	int �ǻҺ��ɫ����;
	int ��Ʒ�б��ɫ����;
	int ��е�����ɫ����;
	int ��ͨ��Ʒ�ɫ����;
	int �߼���Ʒ�ɫ����;
	int ���˽����x�ɫ����;
	int �����о��x�ɫ����;
	int �����h���x�ɫ����;
		int ���ˏ����ɫ = 0;
	int ��ӆ�ɫ�ˆ��x� = 0;
}

namespace �ˆ�
{

	bool ���ˆ��@ʾ�_�P = true;
	bool �@ʾ���P�O���_�P = false;
	bool ������P�O���_�P= false;
	bool ׃�B�����O���_�P= false;
	bool ��е��Ʒ�Y�x�_�P = false;
	bool �����Ʒ�Y�x�_�P = false;
	bool ������Ʒ�Y�x�_�P = false;
	bool �@ʾ�����O���_�P = false;

	int ���ˆ��x� = -1;
}

namespace �@ʾ���P�O��
{
	bool ��Ʒ͸ҕ;
	bool ��Ͷ͸ҕ;
	bool �ǻҺ�͸ҕ;
	bool �@ʾ��;
	bool �@ʾ�ӏ�;
	bool �@ʾ���;
	bool �@ʾˎ;
	bool �@ʾ���R;
	bool �@ʾ��ӆ;
	//�ˆ���
	int �@ʾ�����L��;
	bool �@ʾ����Ѫ�l;
	bool �@ʾ������x;
	bool �@ʾ�؈D���_;
	bool ���������A���_�P;
	int ���������A�����x;
	int ��������@ʾ���x;
	int ��Ʒ����@ʾ���x;
	int �d������@ʾ���x;
	int ӍϢ�@ʾ�돽;
	//������
	bool ���Yģʽ�_�P;
	//���˾��x
	int ���˽����x;
	int �����о��x;
	int �����h���x = 1000;

	int ͸ҕ���P�x� = -1;
}

namespace ������P�O��
{
	int ���λ��[4] = { 12, 5, 4, 2 };
	int ������I[5] = { 2, 1, 81, 69, 16 };
	bool �ȴ�����;
	bool �Ƿ��i��;
	bool �i��׷ۙ;
	int �������;
	int ������x;
	int λ�Å���;
	int ���I����;
	bool ʮ�֜���;
	bool ��ҕ�侀;
	bool �����i�^;
	int �C��Ŵ�;
	int �Ŵ�S��;
	bool �������;
	int ����ˆ��x� = -1;
}

namespace ׃�B�����O��
{
	bool ֫�w���� = false;
	bool ���S���� = false;
	int ���S�߶� = 0;
	bool �����B�� = false;
	bool �o��˲�� = false;
	bool ˲���d�� = false;
	bool ˲�ƿ�Ͷ = false;
	bool �ϵ�ģʽ = false;
	int ׃�B���ܲˆή�ǰ�x�;
}

namespace �@ʾ�����O��
{
	bool �鎬����;	
	int �������t = 50;
	int �[��͸���� = 50;
	int �[��Ӵaֵ= 80;
	int �@ʾ�����ˆή�ǰ�x�;
}

namespace �@ʾ�Y�x
{
	//�ӏ�
	bool �ӏ�762;
	bool �ӏ�556;
	//����
	bool ���;
	bool ����;
	bool �t����;
	bool ���Ȱ�;
	bool ֹʹˎ;
	bool �I������;
	bool ƽ���;
	bool ����;
	bool ���F��;
	bool �W�⏗;
	bool ȼ��ƿ;
	bool �����^��;
	bool �����^��;
	bool ��������;
	bool ��������;
	bool ����������;
	bool ����������;
	int ������Ʒ�@ʾ�Y�x = -1;
	//����
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
	int ��е��Ʒ�ˆ��x� = -1;//VVʣ�����淭�g
	//���
	bool x2;
	bool x3;
	bool x4;
	bool x6;
	bool x8;
	bool ȫϢ;
	bool �t�c;
	bool ���������;
	bool ����;
	bool ���g����;
	bool ��ֱ�հ�;
	bool ֱ���հ�;
	bool �n�h����;
	bool �n�h����;
	bool �n�h�a��;
	bool �n�h��U;
	bool ��������;
	bool ��������;
	bool �����a��;
	bool ������U;
	bool �ѓ�����;
	bool �ѓ�����;
	bool �ѓ��a��;
	bool �ѓ���U;
	bool ɢ��������;
	bool �ѓ�������;
	bool ɢ���ӏ���;
	bool �ѓ��ӏ���;
	bool ���ʽ�հ�;
	bool �p���հ�;
	bool Ĵָ�հ�;
	int �����Ʒ͸ҕ�ˆ��x�= -1;
}



void �O���[��͸����(int tm) 
{
	HWND �[�򴰿ھ��= FindWindow(VMProtectDecryptStringA("UnrealWindow"), NULL);
	LONG nRet = ::GetWindowLong(�[�򴰿ھ��, GWL_EXSTYLE);
	nRet = nRet | WS_EX_LAYERED;
	::SetWindowLong(�[�򴰿ھ��, GWL_EXSTYLE, nRet);
	::SetLayeredWindowAttributes(�[�򴰿ھ��, 0, tm, LWA_ALPHA);
}
void �ָ��[��͸����()
{
	HWND �[�򴰿ھ�� = FindWindow(VMProtectDecryptStringA("UnrealWindow"), NULL);
	LONG nRet = ::GetWindowLong(�[�򴰿ھ��, GWL_EXSTYLE);
	nRet = nRet | WS_EX_LAYERED;
	SetWindowLong(�[�򴰿ھ��, GWL_EXSTYLE, nRet);
	::SetLayeredWindowAttributes(�[�򴰿ھ��, 0, 255, LWA_ALPHA);
}
void �O���@ʾ���Ӵaֵ(int gm)
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

void �d��()
{
	�O���[��͸����(�@ʾ�����O��::�[��͸���� * 2.55);
	�O���@ʾ���Ӵaֵ(�@ʾ�����O��::�[��Ӵaֵ * 2.55);

}

void �ָ�()
{
	�ָ��[��͸����();
	�O���@ʾ���Ӵaֵ(120);
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
//��ɫ

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
		MessageBox(NULL, "[IMGUI�汾]Dx11ע��ɹ�!!", "ϵ�y��ʾ", NULL);
		return true;
	}
	else {
		Sleep(50);
		MessageBox(NULL, "[IMGUI�汾]ע��ʧ��,Ոʹ��ϵ�y����T�_��!!", "ϵ�y��ʾ", NULL);
		return false;
	}
}
*/
