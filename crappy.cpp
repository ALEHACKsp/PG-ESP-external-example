//本地庫
#include "Utils.h"
#include "crappy.hpp"
#include "crappy.h"
#include "decrypt.hpp"
#include "overlay.h"
#include "Utils.h"
#include "tsl.h"
// 調用庫
#include <Dwmapi.h>
#include <iostream>
#include <fstream>
#include <string>


#include <windows.h>
#include <mmsystem.h>
#include <TlHelp32.h>
#include <winsvc.h>
#include <conio.h>
#include <direct.h>
#include <wininet.h>
#include <io.h>
void 讀取配置();
void 保存配置();
void 變態初始();
void 加載驅動();
void 卸載驅動();
void 退出程序();
void 保護輔助();
void 等待遊戲();

驅動* driver = nullptr;
overlay* render;
long 寫入內存最后時間 = 0;
int addItemYaw;

int 當前的時間 = 0;
int 上一秒的時間 = 0;
int 附近敵人數量 = 0;
RECT GameWindowRect;
#pragma comment(lib,"ws2_32.lib") 
using namespace std;
namespace 全局變量
{
	INT 當前視角內目標數量;

	BOOL BE = TRUE;

	BOOL 服务器回调 = TRUE;

	BYTE RigthMove = { NULL };

	ULONG64 鎖定實體指針;
	ULONG64 pGn = 0;
	ULONG64 pUWorld = 0;
	ULONG64 pGameInstance = 0;
	ULONG64 persistentLevel = 0;
	ULONG64 pLocalPlayerArray = 0;
	ULONG64 playerController = 0;
	ULONG64 PlayerCameraManager = 0;
	ULONG64 pPawn = 0;
	ULONG64 pViewportClient = 0;
	ULONG64 pGameBase = 0;

}

namespace 射擊變量
{
	ULONG64 HookAddr;
	ULONG64 JmpAddr;

	
	BYTE 開启子弹追踪[] = { 0x1 };
	BYTE 关闭子弹追踪[] = { 0x0 };

	vector<FRotator> aimAngList;

	vector<float> aimDistanceList;
	vector<Vector3> aimPlayerScreenPosList;
	vector<Vector3> productlocation;
	
	bool 是否倒地;
	bool bFoundTarget;
}

namespace 瞬移變量
{
	int 當前鎖定實體類型;

	Vector3 紀錄實體座標;

	Vector3 自己實體座標;
};

void HookJmp(ULONG64 GameAddress, ULONG64 MyAddress)
{
	
	BYTE Jmp[] = { 0xE9, 0x00, 0x00, 0x00, 0x00 };
	*(ULONG *)(Jmp + 1) = (ULONG)MyAddress - GameAddress - sizeof(Jmp);

   driver->WBT(GameAddress, Jmp, sizeof(Jmp));
	
	
}

void 聲音提示()
{
	Beep(300, 40);
}

void 寫入內存()
{
	VMProtectBeginUltra("寫入內存");


	ULONG64 UPawnMovementComponent = DecryptGeneral(driver->RPM<ULONG64>(全局變量::pPawn + actor::characterMovementComponent));
	float 透過玩家移動速度判斷是否以讀取到玩家 = driver->RPM<float>(UPawnMovementComponent + characterMovementComponent::MaxProneSpeed);
	if (透過玩家移動速度判斷是否以讀取到玩家 >= 50.f && 透過玩家移動速度判斷是否以讀取到玩家 <= 4000.f)
   {
	if (變態功能設置::超級連跳)
	{

	

		if (GetAsyncKeyState(VK_SPACE)) {
		//driver->WPM<int>(全局變量::pPawn + characterMovementComponent::JumpMaxCount, 9999); //JumpMaxCount; 超級連跳
		}

	}
	else {
		//driver->WPM<int>(全局變量::pPawn + characterMovementComponent::JumpMaxCount, 1); //JumpMaxCount; 超級連跳

	}
	
	if (變態功能設置::肢體強化)
	{

		if(GetAsyncKeyState(VK_SHIFT) != 0){
		driver->WPM<float>(UPawnMovementComponent + characterMovementComponent::MaxProneSpeed, 1750.f);//MaxProneSpeed
		//driver->WPM<float>(UPawnMovementComponent + characterMovementComponent::MaxGroggySpeed, 1750.f);//MaxGroggySpeed  2150
		//driver->WPM<float>(UPawnMovementComponent + characterMovementComponent::MaxWalkSpeed, 1750.f);//MaxWalkSpeed
		driver->WPM<float>(UPawnMovementComponent + characterMovementComponent::MaxWalkSpeedCrouched, 1750.f);//MaxWalkSpeedCrouched
		driver->WPM<float>(UPawnMovementComponent + characterMovementComponent::MaxSwimSpeed, 1699.f);//MaxSwimSpeed
		//driver->WPM<float>(UPawnMovementComponent + characterMovementComponent::MaxFlySpeed, 1699.f);//MaxFlySpeed
		driver->WPM<float>(UPawnMovementComponent + characterMovementComponent::MaxCustomMovementSpeed, 5250.f);//MaxCustomMovementSpeed
		driver->WPM<float>(UPawnMovementComponent + characterMovementComponent::MaxAcceleration, 5250.f);//MaxAcceleration
		driver->WPM<float>(UPawnMovementComponent + characterMovementComponent::MaxSwimAcceleration, 5250.f);//MaxSwimAcceleration
	

		}
		else {
			driver->WPM<float>(UPawnMovementComponent + characterMovementComponent::MaxProneSpeed, 50.0f);//MaxProneSpeed
			//driver->WPM<float>(UPawnMovementComponent + characterMovementComponent::MaxGroggySpeed, 100.0f);//MaxGroggySpeed
			//driver->WPM<float>(UPawnMovementComponent + characterMovementComponent::MaxWalkSpeed, 175.0f);//MaxWalkSpeed
			driver->WPM<float>(UPawnMovementComponent + characterMovementComponent::MaxWalkSpeedCrouched, 135.0f);//MaxWalkSpeedCrouched
			driver->WPM<float>(UPawnMovementComponent + characterMovementComponent::MaxSwimSpeed, 300.0f);//MaxSwimSpeed
			 //driver->WPM<float>(UPawnMovementComponent + characterMovementComponent::MaxFlySpeed, 375.0f);//MaxFlySpeed
			driver->WPM<float>(UPawnMovementComponent + characterMovementComponent::MaxCustomMovementSpeed, 500.0f);//MaxCustomMovementSpeed
			driver->WPM<float>(UPawnMovementComponent + characterMovementComponent::MaxAcceleration, 600.0f);//MaxAcceleration
			driver->WPM<float>(UPawnMovementComponent + characterMovementComponent::MaxSwimAcceleration, 950.0f);//MaxSwimAcceleration
		}

	}
	





	if (變態功能設置::無情瞬殺 || 變態功能設置::瞬移載具 || 變態功能設置::瞬移空投)
	{
		//driver->WPM<BYTE>(全局變量:pP + 0xB4, 0);//MovementMode     6 or 5 is swinm       1 or 2 is walk
		//driver->WPM<float>(UPawnMovementComponent + 0x9b0, 999.f);//1 GlobalVaultScale
		//driver->WPM<float>(UPawnMovementComponent + 0x9b4, 999.f);//1 VaultCancelDTScalar
		//driver->WPM<float>(UPawnMovementComponent + 0x9b8, 999.f);//1 MinVelocityForStaticVaultCheck
	}
	else
	{
		//driver->WPM<float>(UPawnMovementComponent + 0x9b0, 1.f);//1 GlobalVaultScale
		//driver->WPM<float>(UPawnMovementComponent + 0x9b4, 1.5f);//1 VaultCancelDTScalar
		//driver->WPM<float>(UPawnMovementComponent + 0x9b8, 0.f);//1 MinVelocityForStaticVaultCheck
	}

	if (變態功能設置::跳躍穿牆)
	{
		

		if (全局變量::RigthMove == NULL) {
			//全局變量::RigthMove = driver->RPM<BYTE>(全局變量::pPawn + bActorEnableCollision_Offset);
			
			
		}
		if (GetAsyncKeyState(VK_SHIFT) && GetAsyncKeyState(VK_SPACE)) {
			//driver->WPM<float>(全局變量::pPawn + 0xAE, 2);
			//driver->WPM<BYTE>(全局變量::pPawn + bActorEnableCollision_Offset, 0);
			
			//printf("穿牆%d", driver->RPM<BYTE>(全局變量::pPawn + bActorEnableCollision_Offset));
		}
		else {
			//driver->WPM<float>(全局變量::pPawn + 0xAE, 0);//bReplicates
			//driver->WPM<BYTE>(全局變量::pPawn + bActorEnableCollision_Offset, 0x3B);
			//printf("back%d", driver->RPM<BYTE>(全局變量::pPawn + bActorEnableCollision_Offset));
		}
		//driver->WPM<BYTE>(全局變量::pPawn + 0xB4, 0x3B);

	}
	//高跳
	if (變態功能設置::跳躍高度 == 0)
	driver->WPM<float>(UPawnMovementComponent + characterMovementComponent::JumpZVelocity, 443.f);
	if (變態功能設置::跳躍高度 == 1)
	driver->WPM<float>(UPawnMovementComponent + characterMovementComponent::JumpZVelocity, 600.f);
	if (變態功能設置::跳躍高度 == 2)
	driver->WPM<float>(UPawnMovementComponent + characterMovementComponent::JumpZVelocity, 750.f);
	if (變態功能設置::跳躍高度 == 3)
	driver->WPM<float>(UPawnMovementComponent + characterMovementComponent::JumpZVelocity, 850.f);
	if (變態功能設置::跳躍高度 == 4)
	driver->WPM<float>(UPawnMovementComponent + characterMovementComponent::JumpZVelocity, 999.f);
   }

   //變態功能 完美無後
   //無後座();
  VMProtectEnd();
}

void 功能實現()
{
	if (GetAsyncKeyState(VK_HOME) & 1)
	{
		聲音提示();
		if (菜單::顯示相關設置開關 || 菜單::射擊相關設置開關 || 菜單::變態功能設置開關 || 菜單::槍械物品篩選開關 || 菜單::配件物品篩選開關 || 菜單::其他物品篩選開關 || 菜單::顯示優化設置開關)
		{
			菜單::顯示相關設置開關 = false;
			菜單::射擊相關設置開關 = false;
			菜單::變態功能設置開關 = false;
			菜單::槍械物品篩選開關 = false;
			菜單::配件物品篩選開關 = false;
			菜單::其他物品篩選開關 = false;
			菜單::顯示優化設置開關 = false;
			菜單::主菜單顯示開關 = false;
		}
		else
		{
			菜單::主菜單顯示開關 = 菜單::主菜單顯示開關 ? false : true;
		}
	}

	if (GetAsyncKeyState(VK_END) & 1)
	{
		聲音提示();
		退出程序();
	}

	if (GetAsyncKeyState(VK_F1) & 1)
	{
		聲音提示();
		顯示相關設置::戰鬥模式開關 = 顯示相關設置::戰鬥模式開關 ? false : true;
	}
	if (GetAsyncKeyState(VK_F2) & 1)
	{
		聲音提示();
		顯示相關設置::顯示槍 = 顯示相關設置::顯示槍 ? false : true;
	}
	if (GetAsyncKeyState(VK_F3) & 1)
	{
		聲音提示();
		顯示相關設置::顯示子彈 = 顯示相關設置::顯示子彈 ? false : true;
	}
	if (GetAsyncKeyState(VK_F4) & 1)
	{
		聲音提示();
		顯示相關設置::顯示配件 = 顯示相關設置::顯示配件 ? false : true;
	}
	if (GetAsyncKeyState(VK_F5) & 1)
	{
		聲音提示();
		顯示相關設置::顯示藥 = 顯示相關設置::顯示藥 ? false : true;
	}
	if (GetAsyncKeyState(VK_F6) & 1)
	{
		聲音提示();
		顯示相關設置::顯示倍鏡 = 顯示相關設置::顯示倍鏡 ? false : true;
	}
	if (GetAsyncKeyState(VK_F7) & 1)
	{
		聲音提示();
		顯示相關設置::顯示自訂 = 顯示相關設置::顯示自訂 ? false : true;
	}
	if (GetAsyncKeyState(0x54) & 1)//t
	{

		全局變量::鎖定實體指針 = NULL;
		//driver->WBT(射擊變量::JmpAddr + 0xa0, 射擊變量::关闭子弹追踪, sizeof(射擊變量::关闭子弹追踪));
		//driver->WBT(射擊變量::JmpAddr + 0xfc, 射擊變量::关闭子弹追踪, sizeof(射擊變量::关闭子弹追踪));
		//driver->WBT(射擊變量::JmpAddr + 0x100 - 0x4, 射擊變量::关闭子弹追踪, sizeof(射擊變量::关闭子弹追踪));

	}
	if (變態功能設置::無情瞬殺 || 變態功能設置::瞬移載具 || 變態功能設置::瞬移空投)
	{
		if (GetAsyncKeyState(0x14) & 1)//caplock
		{

			//重要::::::::::::::::CurrentVaultingTask 判斷是否翻強 float    判斷>=0.0f                      , <2000.0f;


			ULONG64 TargetRootComponent = DecryptGeneral(driver->RPM<ULONG64>(全局變量::鎖定實體指針 + actor::RootComponent));
			瞬移變量::紀錄實體座標 = driver->RPM<Vector3>(TargetRootComponent + actor::_Pos);
			
			ULONG64 LocalRootComponent = DecryptGeneral(driver->RPM<ULONG64>(全局變量::pPawn + actor::RootComponent));
			瞬移變量::自己實體座標 = driver->RPM<Vector3>(LocalRootComponent + actor::_Pos);

		

			if (瞬移變量::當前鎖定實體類型 == 0)
			{
				//driver->WPM<Vector3>(LocalRootComponent + 0x290, Vector3(瞬移變量::紀錄實體座標.x, 瞬移變量::紀錄實體座標.y, 瞬移變量::紀錄實體座標.z));
			}
			else if (瞬移變量::當前鎖定實體類型 == 1)
			{
				//driver->WPM<Vector3>(LocalRootComponent + 0x290, Vector3(瞬移變量::紀錄實體座標.x - 150, 瞬移變量::紀錄實體座標.y - 150, 瞬移變量::紀錄實體座標.z + 100));
			}
			else if (瞬移變量::當前鎖定實體類型 == 2)
			{
				//driver->WPM<Vector3>(LocalRootComponent + 0x290, Vector3(瞬移變量::紀錄實體座標.x, 瞬移變量::紀錄實體座標.y, 瞬移變量::紀錄實體座標.z + 100));
			}
		}
	
	}

	if (變態功能設置::上帝模式)
	{
		if (GetAsyncKeyState(VK_PRIOR))
		{
			auto 判断单组 = driver->RPM<ULONG64>(全局變量::pPawn + actor::team);
			if (判断单组 != 0)
			{
				聲音提示();
				ULONG64 LocalRootComponent = driver->RPM<ULONG64>(全局變量::pPawn + 0x188);
				//driver->WPM<Vector3>(LocalRootComponent + 0x290, Vector3(-9999999, -9999999, 9999999));
			}
		}
	}

	if (變態功能設置::跳躍穿牆) {
		if (全局變量::RigthMove == NULL) {
			全局變量::RigthMove = driver->RPM<BYTE>(全局變量::pPawn + characterMovementComponent::NOWALL);
		}
		if (GetAsyncKeyState(VK_CAPITAL) != 0) {
		//	driver->WPM<BYTE>(全局變量::pPawn + characterMovementComponent::NOWALL, { 0 });


		}
		else {
		//	driver->WPM<BYTE>(全局變量::pPawn + characterMovementComponent::NOWALL, 全局變量::RigthMove);

		}
	}
}

bool 新數據;
vector<DWORD64> EntityAddress;
bool 繪製;
namespace Entityinfo {
	vector<DWORD64> EntityAddress;
}


void 繪製實體() {

	VMProtectBeginUltra("繪製實體");




	//if (取时间戳() - 寫入內存最后時間 > 寫入周期)
	{
		//寫入內存最后時間 = 取时间戳();
		寫入內存();
	}





	UpdateAddresses();

	ULONG64  DecryptEntity = DecryptActor(driver->RPM<ULONG64>(全局變量::persistentLevel + actor::actorList));

   ULONG64  entitylist = driver->RPM<ULONG64>(DecryptEntity);//entitylist是双指针 这边要在读一次

	//ULONG64  entitylist = DecryptEntity;//entitylist是双指针 这边要在读一次
	int entitycount = driver->RPM<int>(DecryptEntity + 0x8);
	//	cout << "a" << endl;


	render->繪製文字(0, 50, Color{ 255, 0, 255, 0 }, pFont, u8"實體數量: %d", entitycount);
	render->繪製圓圈(全局.窗口中心點.x, 全局.窗口中心點.y, 顏色::顏色[顏色::準心顏色參數], 射擊相關設置::射擊範圍, 24, 1.5);

		/**/
	if (entitycount < 30 || entitycount > 5000)
		return;
	for (int i = 0; i < entitycount; i++)
	{
		
		auto  實體 = driver->RPM<ULONG64>(entitylist + (i * 0x8));

		if (!實體)
			continue;
		//如果實體指针等于自己指针则跳过（否则自己也会画框）
		//if (GetVehiclePawn(實體) == 全局變量::pPawn)
		//	全局變量::pPawn = GetVehiclePawn(實體);

		if (實體 == 全局變量::pPawn)
			continue;
		//本人在車上

	//	if (GetVehiclePawn(實體) == 全局變量::pPawn)
		//	continue;

		


		

		int ID = DecryptActorID(driver->RPM<int>(實體 + actor::ID));

		Vector3 實體座標數據 = 取實體座標數據(實體);

		Vector3 實體屏幕座標 = WorldToScreen(實體座標數據);

		Vector3 本身位置 = GetLocalPlayerPos();

		int 距離 = (實體座標數據 - 本身位置).Length() / 100.f;

		//int spec = driver->RPM<int>(全局變量::pPawn + actor::SpectedCount);

		//render->繪製文字(全局.窗口中心點.x - 50, 全局.窗口中心點.y / 2.5 + 35, Color{ 255, 255, 0, 0 }, NULL, u8"目前觀戰人數: %d", spec);

		//計算角度方法一
		Vector3 當前視角 = WorldToScreen(driver->RPM<Vector3>(全局變量::PlayerCameraManager + cameraManager::Location));
		int 角度 = 實體屏幕座標.Distance(當前視角);

		if(ID == Actorids[0])
		{
		
			//取實體血量
			int 血量 =取實體血量(實體);

			int 倒地血量 = GetActorGroggyHealth(實體);

			
		
			
		
			//隊友
			int team = DecryptGeneral(driver->RPM<int>(實體 + actor::team));
			int team2 = DecryptGeneral(driver->RPM<int>(全局變量::pPawn + actor::team));
		
		   if (team2 == team)//用TeamNumer
		       continue;
				//雷達
		
			if (顯示相關設置::顯示地圖雷達)
			{
				if (距離 < 220.f)
				{

					int 地圖x = (實體座標數據.x - 本身位置.x) / 200 + (全局.窗口中心點.x * 2 - 165);
					int 地圖y = (實體座標數據.y - 本身位置.y) / 200 + (全局.窗口中心點.y * 2 - 157);

					//int 地圖x = (實體座標數據.x - 本身位置.x) / 200 + GameWindowRect.right - 140;
					//int 地圖y = (實體座標數據.y - 本身位置.y) / 200 + GameWindowRect.bottom - 120;
					if (血量 > 0 || 倒地血量 > 0)
						render->繪製填充圓圈(地圖x, 地圖y, 3, 24, Color{ 255, 255, 0, 0 });

				}
			}
			if (血量 > 0 || 倒地血量 > 0)	//開始判斷render->繪製
			{
				
					ULONGLONG mesh = DecryptGeneral(driver->RPM<ULONGLONG>(實體 + actor::mesh));
			
				//取名稱
				wchar_t 玩家名稱緩存[100] = { NULL };
			
				//或许不需要加密
				ULONG64 PlayerStateAddress = DecryptGeneral(driver->RPM<ULONG64>(實體 + actor::PlayerState));
				
				ULONG64  playerNameAddress = driver->RPM<ULONG64>(PlayerStateAddress + actor::PlayerName);
				//ULONG64  playerNameAddress = driver->RPM<ULONG64>(PlayerStateAddress + actor::PlayerName);
				int  KillNumber = driver->RPM<int>(PlayerStateAddress + actor::KillNum);
			
				if (playerNameAddress)
				{
					driver->ReadStr(playerNameAddress, 玩家名稱緩存, 100);
				
					//cout << "Name: " << 玩家名稱緩存 << endl;
					//printf("Name: %s\n", 玩家名稱緩存);
					//cout << "Name2: " << 玩家名稱緩存2 << endl;
					//printf("Name: %s\n", 玩家名稱緩存2);
					
					//printf("Name: %ws\n",玩家名稱緩存);
				}

				//性别
	


				//判斷玩家可視
				Color 是否可見;
		
				bool 是否能打;
				///float WorldTime = (driver->RPM<float>(全局變量::pUWorld + actor::WorldSecondTime));//后面那个 (世界时间 - 最后骨骼渲染时间) <=0.2f
			
				
				///float isvisible = WorldTime - driver->RPM<float>(mesh + actor::bRecentlyRendered);
				
				///if(isvisible <= 0.2f){
					是否可見 = Color{ 255, 255, 255, 0 };
					
					是否能打 = true;
				//}
				///else {
					///是否可見 = Color{ 255, 138, 43, 226 };

					///是否能打 = false;
					
				///}
				//判斷是否倒地
				bool 是否倒地;
				//Color 倒地顏色;
				if (倒地血量 > 0.0f && 血量 == 0.0f){
					//倒地顏色 = Color{ 255,255,255,255 };
					是否倒地 = true;

				}
				else{
					//倒地顏色 = Color{ 255,255,215,0 };
					是否倒地 = false;
				}
				if (顯示相關設置::附近敵人預警開關)
				{

					if (距離 < 顯示相關設置::附近敵人預警距離)
					{
						附近敵人數量++;
					}
				}
				//if(顯示相關設置::人物透視){
				//自瞄
				if (距離 < 射擊相關設置::射擊距離){
										

							//可視射線
							if (射擊相關設置::可視射線) {
							
								///if (isvisible <= 0.2f)
									render->繪製線條((int)全局.窗口中心點.x, (int)全局.窗口中心點.y, (int)實體屏幕座標.x, (int)實體屏幕座標.y, 顏色::顏色[顏色::射線顏色參數],1);
								
									
							}
							//預警
					
							if (射擊相關設置::內存自瞄) {

						if ((GetAsyncKeyState(射擊相關設置::射擊按鍵[射擊相關設置::按鍵參數]) & 0x8000) != 0) {

							FRotator pRotator = driver->RPM<FRotator>(全局變量::PlayerCameraManager + cameraManager::Rotator);
							Vector3 vecTargetCenterOfMass = GetBoneWithRotation(mesh, 射擊相關設置::射擊位置[射擊相關設置::位置參數]);
							if (射擊相關設置::快速鎖頭)
							{
								if ((GetAsyncKeyState(射擊相關設置::射擊按鍵[射擊相關設置::按鍵參數]) & 0x8000) && GetAsyncKeyState(0x10))
								{
									vecTargetCenterOfMass = GetBoneWithRotation(mesh, 射擊相關設置::射擊位置[0]);
								}
							}
							else
							{
								vecTargetCenterOfMass = GetBoneWithRotation(mesh, 射擊相關設置::射擊位置[射擊相關設置::位置參數]);

							}

							float InitialSpeed;
							float grav;
							//	float Distance;
							Vector3 預判位置; // Plus it to my initial cordinets
					
								//呼吸

							
							ULONG64 mesh_pawn = driver->RPM<ULONG64>(全局變量::pPawn + actor::mesh);
							ULONG64 UAnimScript = driver->RPM<ULONG64>(mesh_pawn + actor::animscriptinstance);
							Vector3 sway = driver->RPM<Vector3>(UAnimScript + actor::ControlRotation_CP);
                            //用法 		預判位置 = WorldToScreen2(瞄準位置,sway);

						
							ULONG64 WeaponProcessor = driver->RPM<ULONG64>(全局變量::pPawn + localPlayerAddr::WeaponProcessor);
							ULONG64 WeaponProperty = driver->RPM<ULONG64>(WeaponProcessor + WeaponProcessor::EquippedWeapons);
							 InitialSpeed = driver->RPM<float>(WeaponProperty + EquippedWeapons::InitialSpeed)/100;
							

							/*
							ULONG64 EquippedWeapons = driver->RPM<ULONG64>(WeaponProcessor + WeaponProcessor::EquippedWeapons);
						//	BYTE CurrentWeaponIndex = driver->RPM<BYTE>(WeaponProcessor + WeaponProcessor::CurrentWeaponIndex +0x1);//+ 0x10
							BYTE CurrentWeaponIndex = driver->RPM<BYTE>(WeaponProcessor + WeaponProcessor::CurrentWeaponIndex );//+ 0x10 0x1
							if (CurrentWeaponIndex >= 0 && CurrentWeaponIndex < 3)
							{
								
								ULONG64 pWeapon = driver->RPM<ULONG64>(EquippedWeapons + CurrentWeaponIndex * 0x8);
								if (pWeapon)
								{

									

									ULONG64 pRecoilInfo = pWeapon + EquippedWeapons::FRecoilInfo;
									ULONG64 pWeaponData = pWeapon + EquippedWeapons::FWeaponData;
									ULONG64 pTrajectoryWeaponData = pWeapon + EquippedWeapons::FTrajectoryWeaponData;//
									ULONG64 pWeaponGunData = pWeapon + EquippedWeapons::FWeaponGunData;
									ULONG64 pWeaponGunAnim = pWeapon + EquippedWeapons::FWeaponGunAnim;
									ULONG64 pWeaponDeviationData = pWeapon + EquippedWeapons::FWeaponDeviationData;

									

									InitialSpeed = driver->RPM<float>(pTrajectoryWeaponData + EquippedWeapons::InitialSpeed);
								
									grav = driver->RPM<float>(pWeapon + EquippedWeapons::TrajectorygravityZ);
									//cout << "aa:" << driver->RPM<float>(pTrajectoryWeaponData + EquippedWeapons::InitialSpeed) << endl;

								}
								if (InitialSpeed == 0)
									InitialSpeed = 900;
							
						}
							else {
							
									InitialSpeed = 902;
							}
							*/
							 //cout << "Test: "<<InitialSpeed << endl;
							 if (InitialSpeed == 0|| InitialSpeed > 2000|| InitialSpeed < 0|| InitialSpeed<250){
								 InitialSpeed = 901;
							 }
							//if (InitialSpeed > 2000)
								//InitialSpeed = 900;
						
							//cout << InitialSpeed << endl;
							//vecTargetCenterOfMass.z += 2;

							Vector3 headppos = WorldToScreen(vecTargetCenterOfMass);
						
							Vector3 Velocity = GetPlayerVelocity(實體);
							
							int lastTime = 0;
							Vector3 newlolc;
							Vector3 玩家判斷數據;
							while (true) {
								int now = clock();
								 玩家判斷數據 = 取實體座標數據(實體);
								if (now - lastTime > 1000)
								{
									 newlolc = 取實體座標數據(實體);

									lastTime = now;
									break;
								}

							}
							
							Vector3 newlo = newlolc - 玩家判斷數據;

							///Vector3 playerpred = predict(vecTargetCenterOfMass, 距離, Velocity, InitialSpeed, 9.8 );
							Vector3 playerpred = predict(vecTargetCenterOfMass, 距離, Velocity, InitialSpeed, newlo);
							
							///預判位置 = WorldToScreen2(playerpred,sway);
							預判位置 = WorldToScreen(playerpred);
							///render->繪製文字(全局.窗口中心點.x, 全局.窗口中心點.y + 45, Color{ 255, 255, 0, 0 }, pFont, u8"子彈速度:%.0f", InitialSpeed);
						
							Vector3 delta = (vecTargetCenterOfMass - 本身位置).ToFRotator();
							FRotator Fdelta = FRotator(delta.x, delta.y, delta.z);
				
							FRotator angDelta = Fdelta - pRotator;
							angDelta.Clamp();
							
							float dotDistance = GetDotDistance(全局.窗口中心點.x, 全局.窗口中心點.y, headppos.x, headppos.y);


							//隨機位置
							/*

							int iTrackPosRandList[] = { Bones::calf_r,Bones::calf_l,Bones::lowerarm_l,
							Bones::lowerarm_r,Bones::spine_03,Bones::spine_02,Bones::upperarm_l,Bones::upperarm_r,Bones::foot_l,Bones::foot_r,
							Bones::hand_r,Bones::hand_l,Bones::spine_01,Bones::thigh_l,Bones::thigh_r,Bones::thigh_l };
							
							int iTrackPos = global::iTrackPosRandList[rand() % 20];//取隨機數
							Vector3	vTrackPlayerPos = GetBonePos(uTrackActor, iTrackPos);//敌人随机位置,對照隨機書的數字 射擊對應的bone代表數字


									if (rand() % 10 < global::iHitPossibleRate)//不命中
						{
							子苗位直 iTrackPosRandList.x += rand() % 500 + 300.f;
							子苗位直  iTrackPosRandList.y += rand() % 500 + 300.f;
							子苗位直   iTrackPosRandList.z += rand() % 500 + 300.f;
						}

							*/
							//if (angDelta.Length() < 射擊相關設置::射擊範圍)
							if (dotDistance < 射擊相關設置::射擊範圍)
							{

								if (是否能打) 
								{

							

									Vector3 Rfoot;

									Vector3 head = WorldToScreen(GetBoneWithRotation(mesh, Bones::Head));
									//if(mela == 1)
									// Rfoot = WorldToScreen(GetBoneWithRotation(mesh, 166));
									//if(mela == 0)
										Rfoot = WorldToScreen(GetBoneWithRotation(mesh, 176));
				
									int 中 = abs((Rfoot.y - head.y) / 4);

									int 長 = 中 * 2;

									int 高 = 中 / 2.8;

									int 寬 = 中 / 1.0;
									//在駕駛時SWAY是錯的
									///if (GetVehiclePawn(全局變量::pPawn) != 全局變量::pPawn) 
									{


										///if (!是否倒地)
										{

											///cout << "InitialSpeed:" << InitialSpeed << endl;
											//  cout << "headx:  " << headppos.x << "heady:  " << headppos.y << "headz:  " << headppos.z << endl;
											///cout << "swayx:  " << sway.x << "swayy:  " << sway.y << "swayz:  " << sway.z << endl;
											///cout << "預判位置x:  " << 預判位置.x << "預判位置y:  " << 預判位置.y << "預判位置z:  " << 預判位置.z << endl;
											///cout << "Velocityx:  " << Velocity.x << "Velocityy:  " << Velocity.y << "Velocityz:  " << Velocity.z << endl;

											//render->繪製文字(全局.窗口中心點.x, 全局.窗口中心點.y + 55, Color{ 255, 255, 0, 0 }, pFont, u8"速度:%.0f  / %.0f / %.0f", Velocity.x, Velocity.y, Velocity.z);

											射擊變量::aimPlayerScreenPosList.push_back(headppos);
											射擊變量::productlocation.push_back(預判位置);
											射擊變量::aimAngList.push_back(angDelta);

											射擊變量::aimDistanceList.push_back(dotDistance);
											射擊變量::bFoundTarget = true;

											//render->繪製文字((int)預判位置.x - 5, (int)預判位置.y - 10, Color{ 255, 255, 0, 0 }, pFont, u8"%.0f   ", Velocity.x);
										render->繪製線條(headppos.x, headppos.y, 預判位置.x, 預判位置.y, Color{ 255, 0, 255, 255 }, 2);

											//render->繪製線條((int)實體屏幕座標.x, (int)實體屏幕座標.y, (int)實體屏幕座標.x + 10, (int)實體屏幕座標.y - 10, Color{ 255, 255, 255, 255 });
											//render->繪製文字((int)實體屏幕座標.x - 5, (int)實體屏幕座標.y - 7, Color{ 255, 240, 240, 240 }, pFont, u8"●");
											//render->繪製線條((int)實體屏幕座標.x + 10, (int)實體屏幕座標.y - 10, (int)實體屏幕座標.x + 50, (int)實體屏幕座標.y - 10, Color{ 255, 255, 255, 255 });
											//render->繪製文字((int)實體屏幕座標.x + 55, (int)實體屏幕座標.y - 15, Color{ 255, 30,144,255 }, pFont, VMProtectDecryptStringA(u8"├名字：%ws\n├血量：%d %%\n├擊殺數：%d 人\n├狀態: 【 目標已鎖定,活著 】"), 玩家名稱緩存, 血量, KillNumber);
											//子弹追踪
											//driver->WBT(射擊變量::JmpAddr + 0x100 - 0x4, 射擊變量::開启子弹追踪, sizeof(射擊變量::開启子弹追踪));
											//HookAim();
											射擊變量::是否倒地 = false;

										}
										///else {
											//	cout << "倒地Velocityx:  " << Velocity.x << "Velocityy:  " << Velocity.y << "Velocityz:  " << Velocity.z << endl;
												//render->繪製線條((int)實體屏幕座標.x, (int)實體屏幕座標.y, (int)實體屏幕座標.x + 10, (int)實體屏幕座標.y - 10, Color{ 255, 255, 255, 255 });
												//render->繪製文字((int)實體屏幕座標.x - 5, (int)實體屏幕座標.y - 7, Color{ 255, 240, 240, 240 }, pFont, u8"●");
												//render->繪製線條((int)實體屏幕座標.x + 10, (int)實體屏幕座標.y - 10, (int)實體屏幕座標.x + 50, (int)實體屏幕座標.y - 10, Color{ 255, 255, 255, 255 });
												//render->繪製文字((int)實體屏幕座標.x + 55, (int)實體屏幕座標.y - 15, Color{ 255,30,144,255 }, pFont, VMProtectDecryptStringA(u8"├名字：%ws\n├血量：%d %%\n├擊殺數：%d 人\n├狀態: 【 目標已鎖定,倒地 】"), 玩家名稱緩存, 倒地血量, KillNumber);

											///射擊變量::是否倒地 = true;
										///}


									}
								}

							
							}


						}
					}
				}

				if (全局變量::鎖定實體指針 == 實體) {

					Color 顏色;
					//DWORD_PTR PlayerStateAddress = driver->RPM<DWORD_PTR>(實體 + actor::PlayerState);
					//DWORD_PTR playerNameAddress = driver->RPM<DWORD_PTR>(PlayerStateAddress + actor::PlayerName);
					//if (playerNameAddress)
					//{
					//driver->ReadStr(playerNameAddress, 玩家名稱緩存, 100);
					//}
					//int 分数 = mem->RPM<float>(PlayerStateAddress + Actor::Score);
					//int 击杀人数 = 分数 / 40;
					
		
		
					//cout << (driver->RPM<bool>(mesh + actor::bRecentlyRendered) & 0x4) << endl;
					//cout << "1: " << driver->RPM<bool>(mesh + actor::bRecentlyRendered) << endl;// 不可見 0

					if (!是否倒地) {

					

						render->繪製線條((int)實體屏幕座標.x, (int)實體屏幕座標.y, (int)實體屏幕座標.x + 10, (int)實體屏幕座標.y - 10, Color{ 255, 255, 255, 255 },1);
						render->繪製文字((int)實體屏幕座標.x - 5, (int)實體屏幕座標.y - 7, 是否可見, pFont, u8"●");
						render->繪製線條((int)實體屏幕座標.x + 10, (int)實體屏幕座標.y - 10, (int)實體屏幕座標.x + 50, (int)實體屏幕座標.y - 10, Color{ 255, 255, 255, 255 },1);
						render->繪製文字((int)實體屏幕座標.x + 55, (int)實體屏幕座標.y - 15, Color{ 255, 30,144,255 }, pFont, VMProtectDecryptStringA(u8"｜名字：%ws\n｜隊伍：%d\n｜血量：%d %%\n｜擊殺數：%d 人\n｜狀態: 良好\n｜鎖定追蹤中... 】"), 玩家名稱緩存, abs(team - team2), 血量, KillNumber);
						
					}
					else {
						render->繪製線條((int)實體屏幕座標.x, (int)實體屏幕座標.y, (int)實體屏幕座標.x + 10, (int)實體屏幕座標.y - 10, Color{ 255, 255, 255, 255 },1);
						render->繪製文字((int)實體屏幕座標.x - 5, (int)實體屏幕座標.y - 7, 是否可見, pFont, u8"●");
						render->繪製線條((int)實體屏幕座標.x + 10, (int)實體屏幕座標.y - 10, (int)實體屏幕座標.x + 50, (int)實體屏幕座標.y - 10, Color{ 255, 255, 255, 255 },1);
						render->繪製文字((int)實體屏幕座標.x + 55, (int)實體屏幕座標.y - 15, Color{ 255, 30,144,255 }, pFont, VMProtectDecryptStringA(u8"｜名字：%ws\n｜隊伍：%d\n｜倒地血量：%d %%\n｜擊殺數：%d 人\n｜狀態: 倒地\n｜鎖定追蹤中... 】"), 玩家名稱緩存, abs(team - team2), 倒地血量, KillNumber);
					

					}
					
					繪製骨骼(mesh, 是否可見, ID);
				
					//driver->WBT(射擊變量::JmpAddr + 0xa0, 射擊變量::開启子弹追踪, sizeof(射擊變量::開启子弹追踪));
					//HookAim();
					continue;
				}
				else {

					if (距離 < 顯示相關設置::人物最大顯示距離) {
						Vector3 head = WorldToScreen(GetBoneWithRotation(mesh, Bones::Head));//Bones::Head
						Vector3 Rfoot;
						//if (mela == 1)
							//Rfoot = WorldToScreen(GetBoneWithRotation(mesh, 166));
						//if (mela == 0)
							Rfoot = WorldToScreen(GetBoneWithRotation(mesh, 176));

						int 中 = abs((Rfoot.y - head.y) / 4);

						int 長 = 中 * 2;

						int 高 = 中 / 2.8;

						int 寬 = 中 / 1.0;

						int 最小框 = 0;
						
						


						//繪製人物
						drawstyle(實體屏幕座標, mesh, head, Rfoot, 長, 中, 高, 寬, 是否可見, ID);

						//  -
						//	-
						//	-
						//	-
						//  --------------*++++++++++++++++++++++
						//	+
						//	+
						//	+
						//	+

						//血条
						if (顯示相關設置::顯示人物血條)
						{
							int r, g, w;

							w = ((中 * 2) / 100) * 血量;

							g = 血量 * 2.55;

							r = 255 - g;

							if (中 < 5)

								最小框 = 5;

							//	render->繪製矩形(實體屏幕座標.x - 中, (head.y - 中) - 5, (中 * 2) + 最小框, 5, Color{ 255, 255, 255, 255 });

							//	render->繪製填充矩形((實體屏幕座標.x - 中) + 1, (head.y - 中) - 4, ((中 * 2) + 最小框) - 2, 3, Color{ 255,r, g, 0 });


							DrawHealthBar(實體屏幕座標.x - 5, head.y, (寬 * 4) - 最小框, 血量, Color{ 255, 255, 255, 255 });
							//填充名稱
							//render->繪製矩形(實體屏幕座標.x - 中 +1, head.y-20+1, 22*10+1, 20, Color{ 255,255,255,255 });
							//render->繪製填充矩形(實體屏幕座標.x - 中, head.y-20, 22*10, 20, Color{ 200,105,105,105 });
							//render->繪製文字(實體屏幕座標.x - 中, head.y-20, Color{ 255,255,0,0 }, NULL, u8"名稱: %ws 隊伍: %d", 玩家名稱緩存, abs(team - team2));
						}

						if (顯示相關設置::顯示人物距離) {

							Color 根據敵人距離換色;
							if (距離 <= 顯示相關設置::敵人近距離)
								根據敵人距離換色 = 顏色::顏色[顏色::敵人近距離顏色參數];
							else if (距離 > 顯示相關設置::敵人近距離 && 距離 <= 顯示相關設置::敵人中距離)
								根據敵人距離換色 = 顏色::顏色[顏色::敵人中距離顏色參數];
							else if (距離 > 顯示相關設置::敵人中距離 && 距離 <= 1000)
								根據敵人距離換色 = 顏色::顏色[顏色::敵人遠距離顏色參數];
							render->繪製描邊文字(實體屏幕座標.x + 寬, 實體屏幕座標.y - 中, Color{ 255,131,52,255 }, 根據敵人距離換色, pFont, VMProtectDecryptStringA(u8"[%d米]"), 距離);



						}
					}
				}
				
				//人物基本訊息  因為怎亂所以先不用 時機到了再說^_^~~~~~~~~~~~~~~~~~~
				
				if (角度 < 顯示相關設置::訊息顯示半徑)
				{
					Color 顏色;
					//DWORD_PTR PlayerStateAddress = driver->RPM<DWORD_PTR>(實體 + actor::PlayerState);
					//DWORD_PTR playerNameAddress = driver->RPM<DWORD_PTR>(PlayerStateAddress + actor::PlayerName);
					//if (playerNameAddress)
					//{
					//driver->ReadStr(playerNameAddress, 玩家名稱緩存, 100);
					//}
					//int 分数 = mem->RPM<float>(PlayerStateAddress + Actor::Score);
					//int 击杀人数 = 分数 / 40;

			
					/* 太亂
					if (!是否倒地) {
						render->繪製線條((int)實體屏幕座標.x, (int)實體屏幕座標.y, (int)實體屏幕座標.x + 10, (int)實體屏幕座標.y - 10, Color{ 255, 255, 255, 255 },1);
						render->繪製文字((int)實體屏幕座標.x - 5, (int)實體屏幕座標.y - 7, 是否可見, pFont, u8"●");
						render->繪製線條((int)實體屏幕座標.x + 10, (int)實體屏幕座標.y - 10, (int)實體屏幕座標.x + 50, (int)實體屏幕座標.y - 10, Color{ 255, 255, 255, 255 },1);
						render->繪製文字((int)實體屏幕座標.x + 55, (int)實體屏幕座標.y - 15, Color{ 255, 30,144,255 }, pFont, VMProtectDecryptStringA(u8"｜名字：%ws\n｜隊伍：%d\n｜血量：%d %%\n｜擊殺數：%d 人\n｜狀態: 良好\n｜鎖定追蹤中... 】"), 玩家名稱緩存, abs(team - team2), 血量, KillNumber);
						
					}
					else {
						render->繪製線條((int)實體屏幕座標.x, (int)實體屏幕座標.y, (int)實體屏幕座標.x + 10, (int)實體屏幕座標.y - 10, Color{ 255, 255, 255, 255 },1);
						render->繪製文字((int)實體屏幕座標.x - 5, (int)實體屏幕座標.y - 7, 是否可見, pFont, u8"●");
						render->繪製線條((int)實體屏幕座標.x + 10, (int)實體屏幕座標.y - 10, (int)實體屏幕座標.x + 50, (int)實體屏幕座標.y - 10, Color{ 255, 255, 255, 255 },1);
						render->繪製文字((int)實體屏幕座標.x + 55, (int)實體屏幕座標.y - 15, Color{ 255, 30,144,255 }, pFont, VMProtectDecryptStringA(u8"｜名字：%ws\n｜隊伍：%d\n｜血量：%d %%\n｜擊殺數：%d 人\n｜狀態: 倒地\n｜鎖定追蹤中... 】"), 玩家名稱緩存, abs(team - team2), 倒地血量, KillNumber);
					}
				*/

					if ((GetAsyncKeyState(射擊相關設置::射擊按鍵[射擊相關設置::按鍵參數]) & 0x8000) != 0)
					{

						全局變量::鎖定實體指針 = 實體;

						continue;
					}

				}
				
		
      }else {

		  if (全局變量::鎖定實體指針 == 實體)
		  {
			  //临时取消当前锁定
			  全局變量::鎖定實體指針 = NULL;
			  //driver->WBT(射擊變量::JmpAddr + 0xa0, 射擊變量::关闭子弹追踪, sizeof(射擊變量::关闭子弹追踪));
		
		  }
          }

	
  }
  /*
     if (是否飛機(ID))
      render->繪製描邊文字(實體屏幕座標.x, 實體屏幕座標.y, Color{ 255,131,52,255 }, 顏色::顏色[顏色::車輛顏色參數], pFont, VMProtectDecryptStringA(u8"飛機 [%d米]"), 距離);
	 if (距離<75) {
		 if (是否手雷(ID)){
			 render->繪製描邊文字(實體屏幕座標.x+5, 實體屏幕座標.y - 5, Color{ 255,131,52,255 }, Color{ 255,255,0,0 }, pFont, VMProtectDecryptStringA(u8"★小心手雷~~~★"));
		     render->繪製填充圓圈(實體屏幕座標.x, 實體屏幕座標.y, 8, 24, Color{ 255,230,0,0 });
		 }
		 if (是否燃燒瓶(ID)){
			 render->繪製描邊文字(實體屏幕座標.x+5, 實體屏幕座標.y - 5, Color{ 255,131,52,255 }, Color{ 255,255,0,0 }, pFont, VMProtectDecryptStringA(u8"★小心燃燒瓶~~~★"));
		     render->繪製填充圓圈(實體屏幕座標.x, 實體屏幕座標.y, 8, 24, Color{ 255,230,0,0 });
		 }
	 }
  	if (!顯示相關設置::戰鬥模式開關){
		//if(顯示相關設置::車輛透視){
			if (距離 < 顯示相關設置::載具最大顯示距離)
			{

				if (是否吉普(ID))
					render->繪製描邊文字(實體屏幕座標.x, 實體屏幕座標.y, Color{ 255,131,52,255 }, 顏色::顏色[顏色::車輛顏色參數], pFont, VMProtectDecryptStringA(u8"吉普 [%d米]"), 距離);
				else if (是否轎車(ID))
					render->繪製描邊文字(實體屏幕座標.x, 實體屏幕座標.y, Color{ 255,131,52,255 }, 顏色::顏色[顏色::車輛顏色參數], pFont, VMProtectDecryptStringA(u8"轎車 [%d米]"), 距離);
				else if (是否摩托(ID))
					render->繪製描邊文字(實體屏幕座標.x, 實體屏幕座標.y, Color{ 255,131,52,255 }, 顏色::顏色[顏色::車輛顏色參數], pFont, VMProtectDecryptStringA(u8"摩托 [%d米]"), 距離);
				else if (是否越野(ID))
					render->繪製描邊文字(實體屏幕座標.x, 實體屏幕座標.y, Color{ 255,131,52,255 }, 顏色::顏色[顏色::車輛顏色參數], pFont, VMProtectDecryptStringA(u8"越野 [%d米]"), 距離);
				else if (是否皮卡(ID))
					render->繪製描邊文字(實體屏幕座標.x, 實體屏幕座標.y, Color{ 255,131,52,255 }, 顏色::顏色[顏色::車輛顏色參數], pFont, VMProtectDecryptStringA(u8"皮卡 [%d米]"), 距離);
				else if (是否巴士(ID))
					render->繪製描邊文字(實體屏幕座標.x, 實體屏幕座標.y, Color{ 255,131,52,255 }, 顏色::顏色[顏色::車輛顏色參數], pFont, VMProtectDecryptStringA(u8"巴士 [%d米]"), 距離);
				else if (是否大船(ID))
					render->繪製描邊文字(實體屏幕座標.x, 實體屏幕座標.y, Color{ 255,131,52,255 }, 顏色::顏色[顏色::車輛顏色參數], pFont, VMProtectDecryptStringA(u8"大船 [%d米]"), 距離);
				else if (是否遊艇(ID))
					render->繪製描邊文字(實體屏幕座標.x, 實體屏幕座標.y, Color{ 255,131,52,255 }, 顏色::顏色[顏色::車輛顏色參數], pFont, VMProtectDecryptStringA(u8"遊艇 [%d米]"), 距離);
				else if (是否跑車(ID))
					render->繪製描邊文字(實體屏幕座標.x, 實體屏幕座標.y, Color{ 255,131,52,255 }, 顏色::顏色[顏色::車輛顏色參數], pFont, VMProtectDecryptStringA(u8"跑車 [%d米]"), 距離);
				else if (是否羅尼(ID))
					render->繪製描邊文字(實體屏幕座標.x, 實體屏幕座標.y, Color{ 255,131,52,255 }, 顏色::顏色[顏色::車輛顏色參數], pFont, VMProtectDecryptStringA(u8"羅尼 [%d米]"), 距離);
				else if (是否嘟嘟車(ID))
					render->繪製描邊文字(實體屏幕座標.x, 實體屏幕座標.y, Color{ 255,131,52,255 }, 顏色::顏色[顏色::車輛顏色參數], pFont, VMProtectDecryptStringA(u8"嘟嘟車 [%d米]"), 距離);
				else if (是否迷你摩托(ID))
					render->繪製描邊文字(實體屏幕座標.x, 實體屏幕座標.y, Color{ 255,131,52,255 }, 顏色::顏色[顏色::車輛顏色參數], pFont, VMProtectDecryptStringA(u8"迷你摩托 [%d米]"), 距離);
				else if (是否防彈車(ID))
					render->繪製描邊文字(實體屏幕座標.x, 實體屏幕座標.y, Color{ 255,131,52,255 }, 顏色::顏色[顏色::車輛顏色參數], pFont, VMProtectDecryptStringA(u8"防彈車 [%d米]"), 距離);
				
			
		}
			*/
	
			/*
		if(顯示相關設置::物品透視){
			if (ID == 物品[0] || ID == 物品[1]){
	
				ULONGLONG DroppedItemGroupArray = driver->RPM<ULONGLONG>(實體 + aDroppedItemGroup::DroppedItemGroupArray);
				int Count = driver->RPM<int>(實體 + aDroppedItemGroup::DroppedItemGroupCount);
				continue;
					if (!Count)
						continue;
				
					for (int j = 0; j < Count; j++)
					{
						
						ULONGLONG pADroppedItemGroup = driver->RPM<ULONGLONG>(DroppedItemGroupArray + j * 0x10);//0x8 0x10

						ULONGLONG pUItem = driver->RPM<ULONGLONG>(pADroppedItemGroup + aDroppedItemGroup::UItem);
						Vector3 relative = driver->RPM<Vector3>(pADroppedItemGroup + aDroppedItemGroup::relative);
						int UItemID = DecryptActorID(driver->RPM<int>(pUItem + actor::ID));

						//	std::string itemName = GetNameFromID(全局變量::pGn, UItemID);

						std::string name = GetNameFromID(全局變量::pGn, UItemID);

						Vector3 物品位置 = 實體座標數據 + relative;
						Vector3 screenloc = WorldToScreen(物品位置);
						int 物品距離 = (物品位置 - 本身位置).Length() / 100.f;

						
						
						if (物品距離 < 顯示相關設置::物品最大顯示距離)
						{
							//std::string itemname = 過濾物品(name, screenloc, 物品距離);
							if(name != " "){
							
							//cout << itemname.c_str() << endl;
							//render->繪製文字(screenloc.x, screenloc.y-12 *  addItemYaw, 顏色::顏色[顏色::普通物品顏色參數], pFont,u8"｜ %s[%d米]", name.c_str(),物品距離);
					     	過濾物品(name, screenloc, 物品距離,16);
							//	delete name;
							//name = nullptr;
						}	
                       }	
						
					}
					addItemYaw = 0;
					
			}
		}
		*/
		/*
		if(true){//顯示相關設置::骨灰盒透視
		if (是否骨灰盒(ID))
		{
		
		
			if (距離 < 200) {

				//render->繪製線條((int)實體屏幕座標.x, (int)實體屏幕座標.y, (int)實體屏幕座標.x + 10, (int)實體屏幕座標.y - 10, Color{ 255, 255, 255, 255 });

				render->繪製描邊文字((int)實體屏幕座標.x - 30, (int)實體屏幕座標.y + 2, Color{ 255,131,52,255 }, 顏色::顏色[顏色::骨灰盒顏色參數], pFont, VMProtectDecryptStringA(u8"｜ 骨灰盒[%d米]"), 距離);

				//render->繪製線條((int)實體屏幕座標.x + 10, (int)實體屏幕座標.y - 10, (int)實體屏幕座標.x + 50, (int)實體屏幕座標.y - 10, Color{ 255, 255, 255, 255 });

				if (aDroppedItemGroup::packageItems == 0x0)
					continue;

				ULONGLONG packageItems = driver->RPM<ULONGLONG>(實體 + aDroppedItemGroup::packageItems);
				int packageItemscount = driver->RPM<int>(實體 + aDroppedItemGroup::packageItemscount);

				if (!packageItemscount)
					continue;
				實體屏幕座標.x -= 30;
				實體屏幕座標.y -= 14;
				for (int i = 0; i < packageItemscount; i++)
				{
					ULONGLONG Item = driver->RPM<ULONGLONG>(packageItems + i * 0x8);
					int UItemID = DecryptActorID(driver->RPM<int>(Item + actor::ID));
					std::string name = GetNameFromID(全局變量::pGn, UItemID);

                    //ULONGLONG ItemFString = driver->RPM<ULONGLONG>(Item + aDroppedItemGroup::UItemFString);
					//ULONGLONG ItemName = driver->RPM<ULONGLONG>(ItemFString + aDroppedItemGroup::ItemName);
					
					if (name != "") {
						//實體屏幕座標.y -= 16;
						//render->繪製描邊文字((int)實體屏幕座標.x + 55, (int)實體屏幕座標.y, Color{ 255,131,52,255 }, 顏色::顏色[顏色::物品列表顏色參數], pFont, u8"%s", name.c_str());
						過濾盒子物品(name, 實體屏幕座標,16);
					}
					//render->繪製描邊文字((int)實體屏幕座標.x + 55, (int)實體屏幕座標.y, Color{ 255,131,52,255 }, 顏色::顏色[顏色::物品列表顏色參數], pFont, u8"%s", name.c_str());
					//wchar_t* lootName;
					//lootName = (wchar_t*)driver->readSize(ItemName, 100);
					//auto packageitemname2 = std::wstring(lootName);
					//auto PackageShowItem = 空投骨灰盒篩選.find(packageitemname2);
					//if (PackageShowItem != 空投骨灰盒篩選.end()) {
						//實體屏幕座標.y -= 16;
						//render->繪製描邊文字((int)實體屏幕座標.x + 55, (int)實體屏幕座標.y, Color{ 255,131,52,255 }, 顏色::顏色[顏色::物品列表顏色參數], pFont, u8"%s", (PackageShowItem->second).c_str());
					//	delete lootName;
					//	lootName = nullptr;
					//}
				}
				addItemYaw = 0;
			}
		}
		}
		}
		*/
		/*
		if(true){//顯示相關設置::空投透視

		if (是否空投(ID) || 是否超級空投(ID))
		{
			

			if (距離 < 2000) {

				//render->繪製線條((int)實體屏幕座標.x, (int)實體屏幕座標.y, (int)實體屏幕座標.x + 10, (int)實體屏幕座標.y - 10, Color{ 255, 255, 255, 255 });
				if (是否空投(ID))
					render->繪製描邊文字((int)實體屏幕座標.x - 30, (int)實體屏幕座標.y + 2, Color{ 255,131,52,255 }, 顏色::顏色[顏色::空投顏色參數], pFont, VMProtectDecryptStringA(u8"｜ 空投[%d米]"), 距離);
				if (是否超級空投(ID)) 
					render->繪製描邊文字((int)實體屏幕座標.x - 30, (int)實體屏幕座標.y + 2, Color{ 255,131,52,255 }, 顏色::顏色[顏色::空投顏色參數], pFont, VMProtectDecryptStringA(u8"｜ 超級空投[%d米]"), 距離);

				
				//render->繪製線條((int)實體屏幕座標.x + 10, (int)實體屏幕座標.y - 10, (int)實體屏幕座標.x + 50, (int)實體屏幕座標.y - 10, Color{ 255, 255, 255, 255 });
         
				if (aDroppedItemGroup::packageItems == 0x0)
					continue;

				ULONGLONG packageItems = driver->RPM<ULONGLONG>(實體 + aDroppedItemGroup::packageItems);
				int packageItemscount = driver->RPM<int>(實體 + aDroppedItemGroup::packageItemscount);

				if (!packageItemscount)
					continue;
				實體屏幕座標.x -= 30;
				實體屏幕座標.y -= 14;
				for (int i = 0; i < packageItemscount; i++)
				{
					ULONGLONG Item = driver->RPM<ULONGLONG>(packageItems + i * 0x8);
					int UItemID = DecryptActorID(driver->RPM<int>(Item + actor::ID));
					std::string name = GetNameFromID(全局變量::pGn, UItemID);
				
					if (name != "") {
						//實體屏幕座標.y -= 16;
						//render->繪製描邊文字((int)實體屏幕座標.x + 55, (int)實體屏幕座標.y, Color{ 255,131,52,255 }, 顏色::顏色[顏色::物品列表顏色參數], pFont, u8"%s", name.c_str());
						過濾盒子物品(name, 實體屏幕座標,16);
					}
					//render->繪製描邊文字((int)實體屏幕座標.x + 55, (int)實體屏幕座標.y, Color{ 255,131,52,255 }, 顏色::顏色[顏色::物品列表顏色參數], pFont, u8"%s", name.c_str());
				//	wchar_t* lootName;
					//lootName = (wchar_t*)driver->readSize(ItemName, 100);
				//	auto packageitemname2 = std::wstring(lootName);
				//	auto PackageShowItem = 空投骨灰盒篩選.find(packageitemname2);
				//	if (PackageShowItem != 空投骨灰盒篩選.end()) {
					//	實體屏幕座標.y -= 16;
					//	render->繪製描邊文字((int)實體屏幕座標.x + 55, (int)實體屏幕座標.y, Color{ 255,131,52,255 }, 顏色::顏色[顏色::物品列表顏色參數], pFont, u8"%s", (PackageShowItem->second).c_str());
					//	delete lootName;
					//	lootName = nullptr;
					//}

				}
				addItemYaw = 0;
			}
		}
	 
	}*/
 }


    if (射擊相關設置::內存自瞄)
  {

	 if (射擊變量::bFoundTarget)
	 {
		 auto length = 射擊變量::aimDistanceList.size();
		 float minTargetDistance;
		 int minIndex = 0;

		 Vector3 hpos;
		// FRotator pdlc;
		 Vector3 center;
		 minTargetDistance = 射擊變量::aimDistanceList[0];
		 for (int X = 1; X < length; X++)
		 {

			 if (射擊變量::aimDistanceList[X] < minTargetDistance)
			 {
				 minTargetDistance = 射擊變量::aimDistanceList[X];
				 minIndex = X;
			 }
		 }
		 //hpos = 射擊變量::aimPlayerScreenPosList[minIndex];
		 hpos = 射擊變量::productlocation[minIndex];
		
		 //pdlc = 射擊變量::aimAngList[minIndex];

		 if ((GetAsyncKeyState(射擊相關設置::射擊按鍵[射擊相關設置::按鍵參數]) & 0x8000) != 0)
		 {

			 if (!射擊變量::是否倒地) {
		
				 float dx = (hpos.x  - 1920/2);
				float dy = (hpos.y - 1080/2);
		
			
				 
				 int smooth = 2;
		
				mouse_event( MOUSEEVENTF_MOVE, dx*0.7, dy*0.7, 0, 0);//dy*(7 * 0.1)  MOUSEEVENTF_MOVE



				//mouse_event(MOUSEEVENTF_LEFTDOWN, dx*0.7, dy*0.7, 0, 0);//dy*(7 * 0.1)  MOUSEEVENTF_MOVE


				//mouse_event(MOUSEEVENTF_LEFTUP, dx*0.7, dy*0.7, 0, 0);//dy*(7 * 0.1)  MOUSEEVENTF_MOVE
			
				// FRotator 當前視角 = driver->RPM<FRotator>(全局變量::playerController + localPlayerAddr::ControlRotation);
				// driver->WPM<FRotator>(全局變量::playerController + localPlayerAddr::ControlRotation, 當前視角 + pdlc);
			 }

		 }
		
		 射擊變量::aimAngList.clear();
		 射擊變量::aimDistanceList.clear();
		 射擊變量::aimPlayerScreenPosList.clear();
		 射擊變量::productlocation.clear();
		 射擊變量::是否倒地 = NULL;
		 射擊變量::bFoundTarget = false;
	 }
 }
	if (全局變量::鎖定實體指針 != NULL) {
		//if (GetAsyncKeyState(VK_SHIFT) != 0) {
		//HookAim();
		//}
	}
	if (!全局變量::服务器回调)
	{
		render->繪製描邊文字(全局.窗口中心點.x - 60, 全局.窗口中心點.y + (全局.窗口中心點.y / 1.85), Color{ 255,131,52,255 }, Color{255, 255, 0, 0 }, pFont, VMProtectDecryptStringA(u8"靈魂出竅 + 超级加速"), NULL);
	}
	if (射擊相關設置::十字準心)
	{
		render->繪製線條(全局.窗口中心點.x - 10, 全局.窗口中心點.y, 全局.窗口中心點.x + 10, 全局.窗口中心點.y, 顏色::顏色[顏色::準心顏色參數],1);
		render->繪製線條(全局.窗口中心點.x, 全局.窗口中心點.y - 10, 全局.窗口中心點.x, 全局.窗口中心點.y + 10, 顏色::顏色[顏色::準心顏色參數],1);
	}
	if (顯示相關設置::戰鬥模式開關)
	{
		render->繪製描邊文字(全局.窗口中心點.x - 25, 全局.窗口中心點.y + (全局.窗口中心點.y / 1.65), Color{ 255,131,52,255 }, Color{255, 255, 0, 0 }, pFont, VMProtectDecryptStringA(u8"戰鬥模式"), NULL);
	}
	if (顯示相關設置::附近敵人預警開關)
	{
		if (附近敵人數量  > 0)
		{
			render->繪製描邊文字(全局.窗口中心點.x - 80, 全局.窗口中心點.y / 2.5, Color{ 255,131,52,255 }, 顏色::顏色[顏色::預警顏色參數], pFont, VMProtectDecryptStringA(u8"警告: %d 米內有 %d 名玩家"), 顯示相關設置::附近敵人預警距離, 附近敵人數量);
		}
		附近敵人數量 = 0;
	}

	VMProtectEnd();
}


void 菜單2() {
	
	if (顯示相關設置::顯示槍) {

		render->繪製文字(0, 75, Color{ 255, 0, 255, 0 }, NULL, u8"顯示槍,F2關閉");
	}
	else {
		render->繪製文字(0, 75, Color{ 255, 255, 0, 0 }, NULL, u8"顯示槍,F2開啟");
	}
	if (顯示相關設置::顯示子彈) {

		render->繪製文字(0, 100, Color{ 255, 0, 255, 0 }, NULL, u8"顯示子彈,F3關閉");
	}
	else {
		render->繪製文字(0, 100, Color{ 255, 255, 0, 0 }, NULL, u8"顯示子彈,F3開啟");
	}
	if (顯示相關設置::顯示配件) {

		render->繪製文字(0, 125, Color{ 255, 0, 255, 0 }, NULL, u8"顯示配件,F4關閉");
	}
	else {
		render->繪製文字(0, 125, Color{ 255, 255, 0, 0 }, NULL, u8"顯示配件,F4開啟");
	}
	if (顯示相關設置::顯示藥) {

		render->繪製文字(0, 150, Color{ 255, 0, 255, 0 }, NULL, u8"顯示藥,F5關閉");
	}
	else{
		render->繪製文字(0, 150, Color{ 255, 255, 0, 0 }, NULL, u8"顯示藥,F5開啟");
}
	if (顯示相關設置::顯示倍鏡) {

		render->繪製文字(0, 175, Color{ 255, 0, 255, 0 }, NULL, u8"顯示倍鏡,F6關閉");
	}
	else {
		render->繪製文字(0, 175, Color{ 255, 255, 0, 0 }, NULL, u8"顯示倍鏡,F6開啟");
	}
	if (顯示相關設置::顯示自訂) {

		render->繪製文字(0, 200, Color{ 255, 0, 255, 0 }, NULL, u8"顯示其他,F7關閉");
	}
	else {
		render->繪製文字(0, 200, Color{ 255, 255, 0, 0 }, NULL, u8"顯示其他,F7開啟");
	}
	

  //在資料夾


	//if(菜單::主菜單顯示開關)
	{
		//剩下 自苗類 功能類,過濾物資,顏色介面調整

		ImGuiStyle*Style = &ImGui::GetStyle();
		ImGuiIO&io = ImGui::GetIO(); (void)io;
		POINT mousePosition;
		GetCursorPos(&mousePosition);

		io.MousePos.x = (float)mousePosition.x;
		io.MousePos.y = (float)mousePosition.y;

		if (GetAsyncKeyState(VK_LBUTTON))
			io.MouseDown[0] = true;
		else
			io.MouseDown[0] = false;

		ImGui::Begin(u8"優煌輔助", nullptr, ImVec2(405, 496), -1.0F);
		ImGui::Text("beata");
		ImGui::Text(u8"Home隱藏輔助\nEnd安全退出");

		if (ImGui::CollapsingHeader(u8"顯示相關設置"))
		{
			if (ImGui::TreeNode(u8"玩家類"))
			{
				ImGui::Text(u8"F1開啟戰鬥模式(只透視空投,玩家)");
				ImGui::Checkbox(u8"血量", &顯示相關設置::顯示人物血條);
				ImGui::Checkbox(u8"雷達", &顯示相關設置::顯示地圖雷達);
				ImGui::Spacing();
				ImGui::Checkbox(u8"顯示位置", &顯示相關設置::顯示人物距離);
				ImGui::SliderInt(u8"人物顯示距離", &顯示相關設置::人物最大顯示距離, 1, 1000);
				ImGui::Spacing();
				const char* items[] = { u8"無",u8"角框",u8"方框", u8"骨骼", u8"綜合" };
				ImGui::Combo(u8"透視類型", &顯示相關設置::顯示人物風格, items, IM_ARRAYSIZE(items));
				ImGui::Spacing();
				ImGui::Checkbox(u8"敵人預警", &顯示相關設置::附近敵人預警開關);
				ImGui::SliderInt(u8"預警距離", &顯示相關設置::附近敵人預警距離, 1, 400);
				ImGui::TreePop();
			}

			if (ImGui::TreeNode(u8"物品/空頭/車輛"))
			{
				ImGui::Checkbox(u8"顯示空投資訊", &顯示相關設置::空投透視);
				ImGui::Checkbox(u8"顯示骨灰盒資訊", &顯示相關設置::骨灰盒透視);
				ImGui::SliderInt(u8"車輛顯示距離", &顯示相關設置::載具最大顯示距離, 1, 1000);
				ImGui::Spacing();
				ImGui::Checkbox(u8"顯示物品資訊", &顯示相關設置::物品透視);
				ImGui::SliderInt(u8"物品顯示距離", &顯示相關設置::物品最大顯示距離, 1, 100);
				if (ImGui::TreeNode(u8"物品透視"))
				{

					ImGui::Checkbox(u8"槍類(F2開關)", &顯示相關設置::顯示槍);
					if (顯示相關設置::顯示槍)
					{
						if (ImGui::TreeNode(u8"過濾槍"))
						{
							ImGui::Checkbox(u8"AKM", &顯示篩選::AKM);
							ImGui::Checkbox(u8"Mk47Mutan", &顯示篩選::Mk47Mutan);
							ImGui::Checkbox(u8"BerylM762", &顯示篩選::BerylM762);
							ImGui::Checkbox(u8"DP28", &顯示篩選::DP28);
							ImGui::Checkbox(u8"M416", &顯示篩選::M416);
							ImGui::Checkbox(u8"M16A4", &顯示篩選::M16A4);
							ImGui::Checkbox(u8"SCAR", &顯示篩選::SCAR);
							ImGui::Checkbox(u8"QBZ", &顯示篩選::QBZ);
							ImGui::Checkbox(u8"SKS", &顯示篩選::SKS);
							ImGui::Checkbox(u8"SLR半自動步槍", &顯示篩選::SLR);
							ImGui::Checkbox(u8"QBU", &顯示篩選::QBU);
							ImGui::Checkbox(u8"MINI14", &顯示篩選::MINI14);
							ImGui::Checkbox(u8"VSS", &顯示篩選::VSS);
							ImGui::Checkbox(u8"M24", &顯示篩選::M24);
							ImGui::Checkbox(u8"KAR98K", &顯示篩選::KAR98K);
							ImGui::Checkbox(u8"WIN94", &顯示篩選::WIN94);
							ImGui::Checkbox(u8"UZI", &顯示篩選::UZI);
							ImGui::Checkbox(u8"UMP9", &顯示篩選::UMP9);
							ImGui::Checkbox(u8"VECTOR", &顯示篩選::VECTOR);
							ImGui::Checkbox(u8"湯姆遜", &顯示篩選::TOMMYGUN);
							ImGui::Checkbox(u8"削短型散彈槍", &顯示篩選::SAWED);
							ImGui::Checkbox(u8"S12K", &顯示篩選::S12K);
							ImGui::Checkbox(u8"S686", &顯示篩選::S686);
							ImGui::Checkbox(u8"S1897", &顯示篩選::S1897);
							ImGui::Checkbox(u8"十字弓", &顯示篩選::CROSSBOW);
							ImGui::TreePop();
						}
					}

					ImGui::Checkbox(u8"子彈類(F3開關)", &顯示相關設置::顯示子彈);
					if (顯示相關設置::顯示子彈)
					{
						if (ImGui::TreeNode(u8"過濾子彈"))
						{
							ImGui::Checkbox(u8"7.62", &顯示篩選::子彈762);
							ImGui::Checkbox(u8"5.56", &顯示篩選::子彈556);
							ImGui::TreePop();
						}
					}

					ImGui::Checkbox(u8"配件類(F4開關)", &顯示相關設置::顯示配件);
					if (顯示相關設置::顯示配件)
					{
						if (ImGui::TreeNode(u8"過濾配件/身上裝備/手雷"))
						{
							ImGui::Checkbox(u8"二級防彈衣", &顯示篩選::二級防彈衣);
							ImGui::Checkbox(u8"二級背包", &顯示篩選::二級背包);
							ImGui::Checkbox(u8"二級頭盔", &顯示篩選::二級頭盔);
							ImGui::Checkbox(u8"三級防彈衣", &顯示篩選::三級防彈衣);
							ImGui::Checkbox(u8"三級背包", &顯示篩選::三級背包);
							ImGui::Checkbox(u8"三級頭盔", &顯示篩選::三級頭盔);
							ImGui::Checkbox(u8"手榴彈", &顯示篩選::手榴彈);
							ImGui::Checkbox(u8"閃光彈", &顯示篩選::閃光彈);
							ImGui::Checkbox(u8"煙霧彈", &顯示篩選::煙霧彈);
							ImGui::Checkbox(u8"燃燒瓶", &顯示篩選::燃燒瓶);
							ImGui::Checkbox(u8"步槍快擴", &顯示篩選::步槍快擴);
							ImGui::Checkbox(u8"步槍消音", &顯示篩選::步槍消音);
							ImGui::Checkbox(u8"步槍消焰", &顯示篩選::步槍消焰);
							ImGui::Checkbox(u8"步槍補償", &顯示篩選::步槍補償);
							ImGui::Checkbox(u8"狙擊子彈袋", &顯示篩選::狙擊子彈袋);
							ImGui::Checkbox(u8"狙擊托腮板", &顯示篩選::狙擊托腮板);
							ImGui::Checkbox(u8"狙擊快擴", &顯示篩選::狙擊快擴);
							ImGui::Checkbox(u8"狙擊消音", &顯示篩選::狙擊消音);
							ImGui::Checkbox(u8"狙擊消焰", &顯示篩選::狙擊消焰);
							ImGui::Checkbox(u8"狙擊補償", &顯示篩選::狙擊補償);
							ImGui::Checkbox(u8"衝鋒快擴", &顯示篩選::衝鋒快擴);
							ImGui::Checkbox(u8"衝鋒消音", &顯示篩選::衝鋒消音);
							ImGui::Checkbox(u8"衝鋒消焰", &顯示篩選::衝鋒消焰);
							ImGui::Checkbox(u8"衝鋒補償", &顯示篩選::衝鋒補償);
							ImGui::Checkbox(u8"直角握把", &顯示篩選::直角握把);
							ImGui::Checkbox(u8"垂直握把", &顯示篩選::垂直握把);
							ImGui::Checkbox(u8"半截式握把", &顯示篩選::半截式握把);
							ImGui::Checkbox(u8"輕型握把", &顯示篩選::輕型握把);
							ImGui::Checkbox(u8"拇指握把", &顯示篩選::拇指握把);
							ImGui::Checkbox(u8"全息", &顯示篩選::全息);
							ImGui::Checkbox(u8"紅點", &顯示篩選::紅點);
							ImGui::Checkbox(u8"雷射瞄準器", &顯示篩選::雷射瞄準器);
							ImGui::Checkbox(u8"散彈子彈袋", &顯示篩選::散彈子彈袋);
							ImGui::Checkbox(u8"散彈收束器", &顯示篩選::散彈收束器);
							ImGui::Checkbox(u8"uzi槍托", &顯示篩選::槍托);
							ImGui::Checkbox(u8"戰術槍托", &顯示篩選::戰術槍托);
							ImGui::TreePop();
						}
					}

					ImGui::Checkbox(u8"藥品類(F5開關)", &顯示相關設置::顯示藥);
					if (顯示相關設置::顯示藥)
					{
						if (ImGui::TreeNode(u8"過濾藥品"))
						{
							ImGui::Checkbox(u8"止痛藥", &顯示篩選::止痛藥);
							ImGui::Checkbox(u8"能量飲料", &顯示篩選::飲料);
							ImGui::Checkbox(u8"腎上腺素", &顯示篩選::腎上腺素);
							ImGui::Checkbox(u8"繃帶", &顯示篩選::繃帶);
							ImGui::Checkbox(u8"急救包", &顯示篩選::急救包);
							ImGui::Checkbox(u8"醫療箱", &顯示篩選::醫療箱);
							ImGui::TreePop();
						}
					}

					ImGui::Checkbox(u8"倍鏡(F6開關)", &顯示相關設置::顯示倍鏡);
					if (顯示相關設置::顯示倍鏡)
					{
						if (ImGui::TreeNode(u8"過濾倍鏡"))
						{
							ImGui::Checkbox(u8"2倍", &顯示篩選::x2);
							ImGui::Checkbox(u8"3倍", &顯示篩選::x3);
							ImGui::Checkbox(u8"4倍", &顯示篩選::x4);
							ImGui::Checkbox(u8"6倍", &顯示篩選::x6);
							ImGui::Checkbox(u8"8倍", &顯示篩選::x8);

							ImGui::TreePop();
						}
					}

					ImGui::Checkbox(u8"其他(F7開關)", &顯示相關設置::顯示自訂);
					if (顯示相關設置::顯示自訂)
					{
						if (ImGui::TreeNode(u8"其他物品"))
						{
							ImGui::Checkbox(u8"平底鍋", &顯示篩選::平底鍋);

							ImGui::TreePop();
						}
					}

					ImGui::TreePop();
				}
				ImGui::TreePop();
			}

		}

		if (ImGui::CollapsingHeader(u8"變態功能"))
		{
			ImGui::Checkbox(u8"肢體強化", &變態功能設置::肢體強化);
			ImGui::Checkbox(u8"超級連跳", &變態功能設置::超級連跳);
			ImGui::SliderInt(u8"跳躍級別", &變態功能設置::跳躍高度, 0, 4);
			ImGui::Checkbox(u8"跳躍穿牆", &變態功能設置::跳躍穿牆);
			ImGui::Checkbox(u8"上帝模式", &變態功能設置::上帝模式);
			ImGui::Checkbox(u8"無情瞬殺", &變態功能設置::無情瞬殺);
			ImGui::Checkbox(u8"瞬移空投", &變態功能設置::瞬移空投);
			ImGui::Checkbox(u8"瞬移載具", &變態功能設置::瞬移載具);
		}
		if (ImGui::CollapsingHeader(u8"射擊設置"))
		{
			ImGui::Checkbox(u8"開啟自瞄", &射擊相關設置::內存自瞄);
			ImGui::SliderInt(u8"射擊範圍", &射擊相關設置::射擊範圍, 1, 300);
			if (ImGui::IsItemHovered())
			{
				ImGui::Text(u8"建議範圍1~10,不要超過,超過則會自瞄範圍外敵人");
			}
			ImGui::SliderInt(u8"射擊距離", &射擊相關設置::射擊距離, 1, 1000);
			const char* ShootLoc[] = { u8"頭部",u8"頸部",u8"胸部", u8"腰部" };
			ImGui::Combo(u8"射擊位置", &射擊相關設置::位置參數, ShootLoc, IM_ARRAYSIZE(ShootLoc));
			const char* ShootKey[] = { u8"鼠標右键",u8"鼠標左键",u8"Q鍵", u8"E鍵",u8"Shift鍵" };
			ImGui::Combo(u8"射擊按鍵", &射擊相關設置::按鍵參數, ShootKey, IM_ARRAYSIZE(ShootKey));
			ImGui::Checkbox(u8"繪製準心", &射擊相關設置::十字準心);
			ImGui::Checkbox(u8"可視射線", &射擊相關設置::可視射線);
			ImGui::Checkbox(u8"快速鎖頭", &射擊相關設置::快速鎖頭);
			if (ImGui::IsItemHovered())
			{
				ImGui::Text(u8"快速鎖頭,需要按住Shift鍵");
			}
		}
		if (ImGui::CollapsingHeader(u8"視覺類(顏色繪製就放這9/30在弄)"))
		{
			/*
			ImGui::ColorEdit3("Skelet0n Color", (float*)&config.SkelColorIMGUI);
			ImGui::SliderInt("Skelet0n Width", &config.SkeletonWidth, 1, 10);
			ImGui::ColorEdit3("Box Color", (float*)&config.BoxColorIMGUI);
			ImGui::SliderInt("Box Width", &config.BoxWidth, 1, 10);
			ImGui::ColorEdit3("FOV Ring", (float*)&config.DrawFOVIMGUI);

			if (ImGui::TreeNode("Distance"))
			{
			ImGui::ColorEdit3("Up to 280m", (float*)&config.Distance280IMGUI);
			ImGui::ColorEdit3("Up to 560m", (float*)&config.Distance560IMGUI);
			ImGui::ColorEdit3("More than 560m", (float*)&config.DistanceMorethan560IMGUI);
			ImGui::TreePop();
			}
			*/
			if (ImGui::TreeNode("L00t Options"))
			{
				/*
				ImGui::ColorEdit3("Default Colour", (float*)&config.LootDefaultColor);
				ImGui::ColorEdit3("L1", (float*)&config.LootL1);
				ImGui::ColorEdit3("L2", (float*)&config.LootL2);
				ImGui::ColorEdit3("L3", (float*)&config.LootL3);
				ImGui::ColorEdit3("Guns", (float*)&config.LootGuns);
				ImGui::ColorEdit3("Attachments", (float*)&config.LootAttachements);
				ImGui::ColorEdit3("Medical", (float*)&config.LootMedical);
				ImGui::ColorEdit3("Ammo", (float*)&config.LootAmmo);
				ImGui::ColorEdit3("Scopes", (float*)&config.LootScopes);
				ImGui::ColorEdit3("Custom", (float*)&config.LootCustom);
				*/
				ImGui::TreePop();
			}

			if (ImGui::TreeNode("Text"))
			{
				//ImGui::SliderFloat("Multiplier", &config.TextMultiplier, 0.25, 10, "%.2f");

				//ImGui::Combo("Font", &config.TextFont, Fonts, IM_ARRAYSIZE(Fonts));

				if (ImGui::Button("Update Text"))
				{
					//if (config.TextFont != -1)
					//{
						//int ilength = strlen(Fonts[config.TextFont]);
					//	WCHAR    str3[255];
					//	ZeroMemory(str3, 255);
						//	MultiByteToWideChar(0, 0, Fonts[config.TextFont], ilength, str3, ilength + 1);
						//g_pRender->CreateFonts(config.TextMultiplier, str3);
					//}
					//else {
					//	//g_pRender->CreateFonts(config.TextMultiplier, L"Tahoma");
					//}
				}

				ImGui::TreePop();
			}
		}
		/*
		if (ImGui::CollapsingHeader("PAim"))
		{
			//ImGui::Checkbox("Enabled", &config.bAimbot);
			ImGui::Checkbox("Lock Target", &config.locktarget);
			if (config.locktarget)
			{
				ImGui::Checkbox("Locked Indication", &config.ShowLockIndication);
				if (config.ShowLockIndication)
				{
					if (ImGui::TreeNode("Indication Settings"))
					{
						const char* LockType[] = { "Player", "Static" };
						ImGui::Combo("Lock Type", &config.LockIndicationType, LockType, IM_ARRAYSIZE(LockType));
						//					ImGui::ColorEdit3("Text Colour", (float*)&config.AimbotLockColour);

						ImGui::Spacing();

						ImGui::Checkbox("Show locked Bone", &config.ShowAimLockBone); //config.bonerad
						ImGui::SliderFloat("Bone Radius", &config.BoneLockrad, 0.0f, 10.f);
						//					ImGui::ColorEdit3("Bone Colour", (float*)&config.AimbotLockBoneColour);

						ImGui::Spacing();

						ImGui::TreePop();
					}
				}
			}

			//ImGui::InputText("Aimkey", aimkey, 256); //, ImGuiInputTextFlags_CharsHexadecimal | ImGuiInputTextFlags_CharsDecimal | ImGuiInputTextFlags_CharsNoBlank | ImGuiInputTextFlags_AutoSelectAll
			config.aimkey = std::string("1234key");

			if (ImGui::IsItemHovered())
			{
				ImGui::Text(" List of other keys - \n lshift/shift \n lcontrol/lctr \n lmenu/lalt/alt \n Left mouse - lmouse/mouse1\n Middle Mouse - mmouse/mouse3");
				ImGui::Text(" Right Mouse - rmouse / mouse2 \n Mouse Side Button 1 - sidebtn / mousex1 \n Mouse Side Button 2 - sidebtn2 / mousex2 \n If i missed some send me a DM");
				ImGui::Text(" Capslock - cap/caps \n Tab - tab");
			}

			ImGui::SliderFloat("F0V", &config.FOV, 0.0f, 180.f);
			ImGui::Checkbox("Draw FOV", &config.bDrawFOV);

			ImGui::SliderFloat("Sm00th", &config.Smooth, 0.f, 100.f);
			ImGui::SliderFloat("MaxDist", &config.MaxDist, 0.f, 1024.f);
			if (ImGui::IsItemHovered())
			{
				ImGui::Text("0 = Infinite\n1024m is max dist in game");
			}
			ImGui::Checkbox("VelocityPred", &config.bVelocityPrediction);
			ImGui::Checkbox("BulletDropPred", &config.bBulletDropPrediction);

			const char* items[] = { "Head", "Neck", "Chest", "Waist", "Dick" };
			ImGui::Combo("A1mBone", &config.aimbotBone, items, IM_ARRAYSIZE(items));
		}
		*/
		if (ImGui::CollapsingHeader("Debug"))
		{

			if (ImGui::Button(u8"緩存Gname內名稱"))
			{
				// Dump all GNames
				std::ofstream myfile;
				myfile.open("lelnames.txt");

				for (int i = 0; i < 200000; i++)
				{
					if (GetNameFromID(全局變量::pGn, i) != "FAIL")
					{
						myfile << i << "  |  " << GetNameFromID(全局變量::pGn, i) << "\n";
					}
				}
				myfile.close();
			}

			ImGui::Text(u8"Debug資訊");

			ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
			ImGui::Text(u8"繪製延遲: %.1f", 1000.0f / ImGui::GetIO().Framerate);
	
			
			//if (entitycount >= 0 && entitycount <= 2147483)
			//{
			//ImGui::Text("Act0r Size: %d", (int)entitycount);
			//}
			//else {
			//ImGui::Text("Act0r Size: LOL");
			//}
			ImGui::Text("Base: 0x%X", 全局變量::pGameBase);
			ImGui::Text("UWorld: 0x%X", 全局變量::pUWorld);
			ImGui::Text("GameInstance: 0x%X", 全局變量::pGameInstance);
			//ImGui::Text("Width: %d", config.ScreenW);
			//ImGui::Text("Height: %d", config.ScreenH);

			if (ImGui::Button("Attach Console"))
			{
				AllocConsole();
				freopen("CONIN$", "r", stdin);
				freopen("CONOUT$", "w", stdout);
				freopen("CONOUT$", "w", stderr);
			}

			ImGui::SameLine();

			if (ImGui::Button("Deattach Console"))
			{
				FreeConsole();
			}

			if (ImGui::Button("Refresh"))
			{
				std::cout << "Getting UWorld" << std::endl;

			}

			//	static float values[7] = { 0.0f, 0.60f, 0.35f, 0.9f, 0.70f, 0.20f, 0.0f };
			//	static int values_offset = 0;
			//	ImGui::PlotLines("Lines", values, IM_ARRAYSIZE(values), values_offset, "avg 0.0", -1.0f, 1.0f, ImVec2(0, 80));

		}

		if (ImGui::CollapsingHeader("Config"))
		{
			if (ImGui::Button("Save"))


				ImGui::SameLine();

			if (ImGui::Button("Load"))


				//ImGui::SliderInt("SleepRate", &config.iSleepRate, 1, 1000);
			if (ImGui::IsItemHovered())
			{
				ImGui::Text("Higher values will put less stress on CPU but will draw slower.");
			}
			//ImGui::SliderFloat("OV Offset", &config.flOverlayOffset, 0.01, 1);
		}

		ImGui::End();
	}


}
/*2菜單在桌面*/
void 繪製菜單()
{

	if (顯示相關設置::顯示槍) {

		render->繪製文字(0, 75, Color{ 255, 0, 255, 0 }, NULL, VMProtectDecryptStringA(u8"顯示槍,F2關閉"));
	}
	else {
		render->繪製文字(0, 75, Color{ 255, 255, 0, 0 }, NULL, VMProtectDecryptStringA(u8"顯示槍,F2開啟"));
	}
	if (顯示相關設置::顯示子彈) {

		render->繪製文字(0, 100, Color{ 255, 0, 255, 0 }, NULL, VMProtectDecryptStringA(u8"顯示子彈,F3關閉"));
	}
	else {
		render->繪製文字(0, 100, Color{ 255, 255, 0, 0 }, NULL, VMProtectDecryptStringA(u8"顯示子彈,F3開啟"));
	}
	if (顯示相關設置::顯示配件) {

		render->繪製文字(0, 125, Color{ 255, 0, 255, 0 }, NULL, VMProtectDecryptStringA(u8"顯示配件,F4關閉"));
	}
	else {
		render->繪製文字(0, 125, Color{ 255, 255, 0, 0 }, NULL, VMProtectDecryptStringA(u8"顯示配件,F4開啟"));
	}
	if (顯示相關設置::顯示藥) {

		render->繪製文字(0, 150, Color{ 255, 0, 255, 0 }, NULL, VMProtectDecryptStringA(u8"顯示藥,F5關閉"));
	}
	else {
		render->繪製文字(0, 150, Color{ 255, 255, 0, 0 }, NULL, VMProtectDecryptStringA(u8"顯示藥,F5開啟"));
	}
	if (顯示相關設置::顯示倍鏡) {

		render->繪製文字(0, 175, Color{ 255, 0, 255, 0 }, NULL, VMProtectDecryptStringA(u8"顯示倍鏡,F6關閉"));
	}
	else {
		render->繪製文字(0, 175, Color{ 255, 255, 0, 0 }, NULL, VMProtectDecryptStringA(u8"顯示倍鏡,F6開啟"));
	}
	if (顯示相關設置::顯示自訂) {

		render->繪製文字(0, 200, Color{ 255, 0, 255, 0 }, NULL, VMProtectDecryptStringA(u8"顯示其他,F7關閉"));
	}
	else {
		render->繪製文字(0, 200, Color{ 255, 255, 0, 0 }, NULL, VMProtectDecryptStringA(u8"顯示其他,F7開啟"));
	}
	/*
	char buf3[50] = "瞄准位置[PgUp]";
	char buf1[50] = "瞄准距离[PgDown]";
	char buf5[50] = "人物透视[F2]";
	char buf6[50] = "追踪命中率[~波浪键]";
	int menuRight = 0 + 30;
	int menuTop = 0 + 130;
	render->繪製填充矩形(menuRight - 10, menuTop + 5, 250, 360, Color{ (float)255,112,128,144 });
	
	render->繪製填充矩形(menuRight - 10, menuTop + 5, 250, 30, Color{ 200,255,165,0 });
	render->繪製文字(menuRight, menuTop + 10, Color{ 255,240,240,240 }, NULL, u8"迷嘞否");
	render->繪製文字(menuRight + 100, menuTop + 10, Color{ 255,240,240,240 }, NULL, u8"HOME隐藏显示菜单");
	render->繪製文字(menuRight, menuTop + 35, Color{ 255,240,240,240 }, NULL, u8"自苗測試中");
	render->繪製文字(menuRight, menuTop + 55, Color{ 255,240,240,240 }, NULL, u8"測試中");
	render->繪製填充矩形(menuRight - 10, menuTop + 85, 250, 20, Color{ 200,255,165,0 });
	render->繪製文字(menuRight, menuTop + 85, Color{ 255,240,240,240 }, NULL, u8"透视類");
	render->繪製填充矩形(menuRight - 10, menuTop + 150, 250, 20, Color{ 200,255,165,0 });
	render->繪製文字(menuRight, menuTop + 150, Color{ 255,240,240,240 }, NULL , u8"射擊類");
	render->繪製填充矩形(menuRight - 10, menuTop + 210, 250, 20, Color{ 200,255,165,0 });
	render->繪製文字(menuRight, menuTop + 210, Color{ 255,240,240,240 }, NULL ,u8"其他類");
	Color Orange;
	Color White;
	White = Color{ 200,255,165,0 };
	Orange = Color{ 200,255,165,0 };
	if (GetAsyncKeyState(VK_F7) & 1) {

		射擊相關設置::十字準心 = 射擊相關設置::十字準心 ? false : true;
	}
	if (GetAsyncKeyState(VK_F6) & 1) {

		射擊相關設置::可視射線 = 射擊相關設置::可視射線 ? false : true;
	}
	if (GetAsyncKeyState(VK_F5) & 1) {

		射擊相關設置::內存自瞄 = 射擊相關設置::內存自瞄 ? false : true;
	}
	if (GetAsyncKeyState(VK_F4) & 1) {

		顯示相關設置::物品透視 = 顯示相關設置::物品透視 ? false : true;
	}
	if (GetAsyncKeyState(VK_F3) & 1) {

		顯示相關設置::車輛透視 = 顯示相關設置::車輛透視 ? false : true;
	}
	if (GetAsyncKeyState(VK_F2)& 1) {

		顯示相關設置::附近敵人預警開關 = 顯示相關設置::附近敵人預警開關 ? false : true;
	}
	if ( GetAsyncKeyState(VK_F1) & 1) {

		顯示相關設置::人物透視 = 顯示相關設置::人物透視 ? false : true;
	
	}

	if (顯示相關設置::人物透視)
	{
		if (GetAsyncKeyState(VK_NUMPAD1) & 1) {
			顯示相關設置::顯示人物風格 = (顯示相關設置::顯示人物風格 + 1) > 4 ? 0 : 顯示相關設置::顯示人物風格 + 1;
			{
				
			}
		}
		if (GetAsyncKeyState(VK_NUMPAD8) & 1) {
			顯示相關設置::人物最大顯示距離 = (顯示相關設置::人物最大顯示距離 + 100) > 1000 ? 100 : (顯示相關設置::人物最大顯示距離 + 100);
			{

			}
		}
		render->繪製文字(menuRight, menuTop + 110, Orange, NULL, u8"人物模式[F1][开]");
		render->繪製文字(menuRight, menuTop + 230, Orange, NULL, 顯示相關設置::顯示人物風格 == 0 ? u8"人物風格[數字1]: ✘" : (顯示相關設置::顯示人物風格 == 1 ? VMProtectDecryptStringA(u8"人物風格[數字1]: 角框") :
			(顯示相關設置::顯示人物風格 == 2 ? VMProtectDecryptStringA(u8"人物風格[數字1]: 方框") : (顯示相關設置::顯示人物風格 == 3 ? VMProtectDecryptStringA(u8"人物風格[數字1]: 骨骼") :
			(顯示相關設置::顯示人物風格 == 4 ? VMProtectDecryptStringA(u8"人物風格[數字1]: 綜合") : u8""))))
			);
		render->繪製文字(menuRight, menuTop + 245, Orange, NULL, u8"人物顯示距離[數字8]: %d", 顯示相關設置::人物最大顯示距離);
		顯示相關設置::顯示人物距離 = true;
		顯示相關設置::顯示人物血條 = true;

	}
	else {
		render->繪製文字(menuRight, menuTop + 110, White, NULL, u8"人物模式[F1][关]");	
		render->繪製文字(menuRight, menuTop + 230, Orange, NULL, 顯示相關設置::顯示人物風格 == 0 ? u8"人物風格[數字1]: ✘" : (顯示相關設置::顯示人物風格 == 1 ? VMProtectDecryptStringA(u8"人物風格[數字1]: 角框") :
			(顯示相關設置::顯示人物風格 == 2 ? VMProtectDecryptStringA(u8"人物風格[數字1]: 方框") : (顯示相關設置::顯示人物風格 == 3 ? VMProtectDecryptStringA(u8"人物風格[數字1]: 骨骼") :
			(顯示相關設置::顯示人物風格 == 4 ? VMProtectDecryptStringA(u8"人物風格[數字1]: 綜合") : u8""))))
		);
		render->繪製文字(menuRight, menuTop + 245, Orange, NULL, u8"人物顯示距離[數字8]: %d", 顯示相關設置::人物最大顯示距離);
		顯示相關設置::顯示人物距離 = false;
		顯示相關設置::顯示人物血條 = false;
	}

	if (顯示相關設置::附近敵人預警開關)
	{
		if (GetAsyncKeyState(VK_NUMPAD2) & 1) {
			顯示相關設置::附近敵人預警距離 = (顯示相關設置::附近敵人預警距離 + 50) > 400 ? 0 : (顯示相關設置::附近敵人預警距離 + 50);
			{

			}
		}
		render->繪製文字(menuRight + 120, menuTop + 110, Orange, NULL, u8"敵人預警[F2][开]");
		render->繪製文字(menuRight, menuTop + 260, Orange, NULL, u8"敵人預警距離[數字2]: %d", 顯示相關設置::附近敵人預警距離);
	}
	else {
		render->繪製文字(menuRight + 120, menuTop + 110, Orange, NULL, u8"敵人預警[F2][關]");
		render->繪製文字(menuRight, menuTop + 260, Orange, NULL, u8"敵人預警距離[數字2]: %d", 顯示相關設置::附近敵人預警距離);
	}

	if (顯示相關設置::車輛透視)
	{
		if (GetAsyncKeyState(VK_NUMPAD3) & 1) {
			顯示相關設置::載具最大顯示距離 = (顯示相關設置::載具最大顯示距離 + 100) > 1000 ? 100 : (顯示相關設置::載具最大顯示距離 + 100);
			{

			}
		}
		render->繪製文字(menuRight, menuTop + 125, Orange, NULL, u8"车辆透视[F3][开]");
		render->繪製文字(menuRight, menuTop + 275, Orange, NULL, u8"車輛顯示距離[數字3]: %d", 顯示相關設置::載具最大顯示距離);
	}
	else {
		render->繪製文字(menuRight , menuTop + 125, Orange, NULL, u8"车辆透视[F3][關]");
		render->繪製文字(menuRight, menuTop + 275, Orange, NULL, u8"車輛顯示距離[數字3]: %d", 顯示相關設置::載具最大顯示距離);
	}



	if (顯示相關設置::物品透視)
	{
		if (GetAsyncKeyState(VK_NUMPAD4) & 1) {
			顯示相關設置::物品最大顯示距離 = (顯示相關設置::物品最大顯示距離 + 10) > 100 ? 10 : (顯示相關設置::物品最大顯示距離 + 10);
			{

			}
		}
		render->繪製文字(menuRight + 120, menuTop + 125, Orange, NULL, u8"物品透视[F4][开]");
		render->繪製文字(menuRight, menuTop + 290, Orange, NULL, u8"物品顯示距離[數字4]: %d", 顯示相關設置::物品最大顯示距離);
	}
	else {
		render->繪製文字(menuRight + 120, menuTop + 125, Orange, NULL, u8"物品透视[F4][關]");
		render->繪製文字(menuRight, menuTop + 290, Orange, NULL, u8"物品顯示距離[數字4]: %d", 顯示相關設置::物品最大顯示距離);
	}


	if (射擊相關設置::內存自瞄)
	{
		if (GetAsyncKeyState(VK_NUMPAD5) & 1) {
			射擊相關設置::射擊距離 = (射擊相關設置::射擊距離 + 100) > 1000 ? 0 : (射擊相關設置::射擊距離 + 100);
			{

			}
		}
		if (GetAsyncKeyState(VK_NUMPAD6) & 1) {
			射擊相關設置::射擊範圍 = (射擊相關設置::射擊範圍 + 1) > 100 ? 1 : (射擊相關設置::射擊範圍 + 1);
			{

			}
		}
		if (GetAsyncKeyState(VK_NUMPAD7) & 1) {
			射擊相關設置::位置參數 = (射擊相關設置::位置參數 + 1) > 3 ? 0 : 射擊相關設置::位置參數 + 1;
			{

			}
			
		}
		if (GetAsyncKeyState(VK_NUMPAD9) & 1) {
			
			射擊相關設置::按鍵參數 = (射擊相關設置::按鍵參數 + 1) > 4 ? 0 : 射擊相關設置::按鍵參數 + 1;
		{

			}

		}
		render->繪製文字(menuRight, menuTop + 170, Orange, NULL, u8"自动瞄准[F5][關]");
		render->繪製文字(menuRight + 120, menuTop + 170, Orange, NULL, u8"瞄准距離[數字5]: %d", 射擊相關設置::射擊距離);
		render->繪製文字(menuRight, menuTop + 185, Orange, NULL, u8"射擊範圍[數字6]: %d", 射擊相關設置::射擊範圍);
		render->繪製文字(menuRight + 120, menuTop + 185, Orange, NULL, 射擊相關設置::位置參數 == 0 ? u8"射擊位置[數字7]: 頭" : (射擊相關設置::位置參數 == 1 ? u8"射擊位置[數字7]: 頸" : (射擊相關設置::位置參數 == 2 ? u8"射擊位置[數字7]: 胸" : (射擊相關設置::位置參數 == 3 ? u8"射擊位置[數字7]: 腰" : u8"射擊位置[數字7]: 無"))));
		render->繪製文字(menuRight, menuTop + 305, Orange, NULL, 射擊相關設置::按鍵參數 == 0 ? u8"射擊按鍵[數字9]: 鼠標右键" : (射擊相關設置::按鍵參數 == 1 ? u8"射擊按鍵[數字9]: 鼠標左键" : (射擊相關設置::按鍵參數 == 2 ? u8"射擊按鍵[數字9]: Q" : (射擊相關設置::按鍵參數 == 3 ? u8"射擊按鍵[數字9]: E" : (射擊相關設置::按鍵參數 == 4 ? u8"射擊按鍵[數字9]: Shift" : u8"")))));
	}
	else {
		render->繪製文字(menuRight, menuTop + 170, Orange, NULL, u8"自动瞄准[F5][關]");
		render->繪製文字(menuRight + 120, menuTop + 170, Orange, NULL, u8"瞄准距離[數字5]: %d", 射擊相關設置::射擊距離);
		render->繪製文字(menuRight, menuTop + 185, Orange, NULL, u8"射擊範圍[數字6]: %d", 射擊相關設置::射擊範圍);
		render->繪製文字(menuRight + 120, menuTop + 185, Orange, NULL, 射擊相關設置::位置參數 == 0 ? u8"射擊位置[數字7]: 頭" : (射擊相關設置::位置參數 == 1 ? u8"射擊位置[數字7]: 頸" : (射擊相關設置::位置參數 == 2 ? u8"射擊位置[數字7]: 胸" : (射擊相關設置::位置參數 == 3 ? u8"射擊位置[數字7]: 腰" : u8"射擊位置[數字7]: 無"))));
		render->繪製文字(menuRight, menuTop + 305, Orange, NULL, 射擊相關設置::按鍵參數 == 0 ? u8"射擊按鍵[數字9]: 鼠標右键" : (射擊相關設置::按鍵參數 == 1 ? u8"射擊按鍵[數字9]: 鼠標左键" : (射擊相關設置::按鍵參數 == 2 ? u8"射擊按鍵[數字9]: Q" : (射擊相關設置::按鍵參數 == 3 ? u8"射擊按鍵[數字9]: E" : (射擊相關設置::按鍵參數 == 4 ? u8"射擊按鍵[數字9]: Shift" : u8"")))));
	}
	
	if (射擊相關設置::可視射線)
	{
		
		render->繪製文字(menuRight, menuTop + 320, Orange, NULL, u8"可視射線[F6][開]");
	}
	else {
		render->繪製文字(menuRight, menuTop + 320, Orange, NULL, u8"可視射線[F6][關]");
		
	}
	
	if (射擊相關設置::十字準心)
	{

		render->繪製文字(menuRight, menuTop + 335, Orange, NULL, u8"十字準心[F7][開]");
	}
	else {
		render->繪製文字(menuRight, menuTop + 335, Orange, NULL, u8"十字準心[F7][關]");

	}
	*/
	if (菜單::主菜單顯示開關)
	{
	

		render->繪製文字((全局.窗口中心點.x * 2) - 300, (全局.窗口中心點.y * 2) - 755, Color{ 255, 240, 240, 240 }, pFont, 菜單標題);
		render->繪製文字((全局.窗口中心點.x * 2) - 300, (全局.窗口中心點.y * 2) - 740, Color{ 255, 240, 240, 240 }, pFont, 遊戲版本);

		render->繪製描邊文字((全局.窗口中心點.x * 2) - 300, (全局.窗口中心點.y * 2) - 580, Color{ 255,131,52,255 }, Color{ 255, 255, 0, 0 }, pFont, VMProtectDecryptStringA(u8"Home隱藏輔助\nEnd安全退出"));
		char 菜單文字提示[1024];
		sprintf_s(菜單文字提示,
			VMProtectDecryptStringA(u8"%s顯示相關設置\n%s射擊相關設置\n%s變態功能設置\n%s槍械物品篩選\n%s配件物品篩選\n%s其他物品篩選\n%s界面優化設置"),
			菜單::主菜單選項 == 0 ? u8"➥ " : u8"",
			菜單::主菜單選項 == 1 ? u8"➥ " : u8"",
			菜單::主菜單選項 == 2 ? u8"➥ " : u8"",
			菜單::主菜單選項 == 3 ? u8"➥ " : u8"",
			菜單::主菜單選項 == 4 ? u8"➥ " : u8"",
			菜單::主菜單選項 == 5 ? u8"➥ " : u8"",
			菜單::主菜單選項 == 6 ? u8"➥ " : u8"");
		render->繪製描邊文字((全局.窗口中心點.x * 2) - 300, (全局.窗口中心點.y * 2) - 720, Color{ 255,131,52,255 }, Color{ 255, 30, 144, 255 }, pFont, 菜單文字提示);

		if (GetAsyncKeyState(VK_UP) & 1)
		{
			聲音提示();
			菜單::主菜單選項 = (菜單::主菜單選項 - 1) < 0 ? 6 : 菜單::主菜單選項 - 1;
		}
		if (GetAsyncKeyState(VK_DOWN) & 1)
		{
			聲音提示();
			菜單::主菜單選項 = (菜單::主菜單選項 + 1) > 6 ? 0 : 菜單::主菜單選項 + 1;
		}
		if (GetAsyncKeyState(VK_RIGHT) & 1)
		{
			switch (菜單::主菜單選項)
			{
			case 0:
				菜單::主菜單顯示開關 = 菜單::主菜單顯示開關 ? false : true;
				{
					聲音提示();
					菜單::顯示相關設置開關 = true;
				}
				break;
			case 1:
				菜單::主菜單顯示開關 = 菜單::主菜單顯示開關 ? false : true;
				{
					聲音提示();
					菜單::射擊相關設置開關 = true;
				}
				break;
			case 2:
				菜單::主菜單顯示開關 = 菜單::主菜單顯示開關 ? false : true;
				{
					聲音提示();
					菜單::變態功能設置開關 = true;
				}
				break;
			case 3:
				菜單::主菜單顯示開關 = 菜單::主菜單顯示開關 ? false : true;
				{
					聲音提示();
					菜單::槍械物品篩選開關 = true;
				}
				break;
			case 4:
				菜單::主菜單顯示開關 = 菜單::主菜單顯示開關 ? false : true;
				{
					聲音提示();
					菜單::配件物品篩選開關 = true;
				}
				break;
			case 5:
				菜單::主菜單顯示開關 = 菜單::主菜單顯示開關 ? false : true;
				{
					聲音提示();
					菜單::其他物品篩選開關 = true;
				}
				break;
			case 6:
				菜單::主菜單顯示開關 = 菜單::主菜單顯示開關 ? false : true;
				{
					聲音提示();
					菜單::顯示優化設置開關 = true;
				}
				break;
			default:
				break;
			}
		}
	}

	else if (菜單::顯示相關設置開關)
	{
		render->繪製描邊文字((全局.窗口中心點.x * 2) - 300, (全局.窗口中心點.y * 2) - 750, Color{ 255,131,52,255 }, Color{ 255, 30, 144, 255 }, pFont, VMProtectDecryptStringA(u8"菜單選項 ➥ 顯示相關設置"));
		char 菜單文字提示[1024];
		sprintf_s(菜單文字提示,
			VMProtectDecryptStringA(u8"%s顯示風格設定\n%s顯示人物血量\n%s顯示人物距離\n%s顯示地圖雷達\n\n%s敵人預警\n%s預警距離\n\n%s戰鬥模式切換\n%s訊息顯示半徑\n\n%s物品顯示距離\n%s人物顯示距離\n%s載具顯示距離"),
			顯示相關設置::透視相關選項 == 0 ? u8"➥" : u8"",
			顯示相關設置::透視相關選項 == 1 ? u8"➥" : u8"",
			顯示相關設置::透視相關選項 == 2 ? u8"➥" : u8"",
			顯示相關設置::透視相關選項 == 3 ? u8"➥" : u8"",
			顯示相關設置::透視相關選項 == 4 ? u8"➥" : u8"",
			顯示相關設置::透視相關選項 == 5 ? u8"➥" : u8"",
			顯示相關設置::透視相關選項 == 6 ? u8"➥" : u8"",
			顯示相關設置::透視相關選項 == 7 ? u8"➥" : u8"",
			顯示相關設置::透視相關選項 == 8 ? u8"➥" : u8"",
			顯示相關設置::透視相關選項 == 9 ? u8"➥" : u8"",
			顯示相關設置::透視相關選項 == 10 ? u8"➥" : u8"",
			顯示相關設置::透視相關選項 == 11 ? u8"➥" : u8"");
		render->繪製描邊文字((全局.窗口中心點.x * 2) - 300, (全局.窗口中心點.y * 2) - 720, Color{ 255,131,52,255 }, Color{ 255, 30, 144, 255 }, pFont, 菜單文字提示);
		char 菜單開關狀態[1024];
		sprintf_s(菜單開關狀態, "%s\n%s\n%s\n%s\n\n%s\n%d\n\n%s\n%d\n\n%d\n%d\n%d",
			顯示相關設置::顯示人物風格 == 0 ? u8"✘" : (顯示相關設置::顯示人物風格 == 1 ? VMProtectDecryptStringA(u8"角框") : (顯示相關設置::顯示人物風格 == 2 ? VMProtectDecryptStringA(u8"方框") : (顯示相關設置::顯示人物風格 == 3 ? VMProtectDecryptStringA(u8"骨骼") : (顯示相關設置::顯示人物風格 == 4 ? VMProtectDecryptStringA(u8"骨骼+角框") : u8"")))),
			
			顯示相關設置::顯示人物血條 ? u8"✔" : u8"✘",
			顯示相關設置::顯示人物距離 ? u8"✔" : u8"✘",
			顯示相關設置::顯示地圖雷達 ? u8"✔" : u8"✘",
			顯示相關設置::附近敵人預警開關 ? u8"✔" : u8"✘",
			顯示相關設置::附近敵人預警距離, u8"F1",
			顯示相關設置::訊息顯示半徑,
			顯示相關設置::物品最大顯示距離,
			顯示相關設置::人物最大顯示距離,
			顯示相關設置::載具最大顯示距離);
		render->繪製描邊文字((全局.窗口中心點.x * 2) - 190, (全局.窗口中心點.y * 2) - 720, Color{ 255,131,52,255 }, Color{ 255,0, 255, 0 }, pFont, 菜單開關狀態);

		if (GetAsyncKeyState(VK_UP) & 1)
		{
			聲音提示();
			顯示相關設置::透視相關選項 = (顯示相關設置::透視相關選項 - 1) < 0 ? 10 : 顯示相關設置::透視相關選項 - 1;
		}
		if (GetAsyncKeyState(VK_DOWN) & 1)
		{
			聲音提示();
			顯示相關設置::透視相關選項 = (顯示相關設置::透視相關選項 + 1) > 10 ? 0 : 顯示相關設置::透視相關選項 + 1;
		}
		if (GetAsyncKeyState(VK_LEFT) & 1)
		{
			聲音提示();
			菜單::主菜單顯示開關 = true;
			菜單::顯示相關設置開關 = false;
		}
		if (GetAsyncKeyState(VK_RIGHT) & 1)
		{
			switch (顯示相關設置::透視相關選項)
			{
			case 0:
				顯示相關設置::顯示人物風格 = (顯示相關設置::顯示人物風格 + 1) > 4 ? 0 : 顯示相關設置::顯示人物風格 + 1;
				{
					聲音提示();
				}
				break;
			case 1:
				顯示相關設置::顯示人物血條 = 顯示相關設置::顯示人物血條 ? false : true;
				{
					聲音提示();
				}
				break;
			case 2:
				顯示相關設置::顯示人物距離 = 顯示相關設置::顯示人物距離 ? false : true;
				{
					聲音提示();
				}
				break;
			case 3:
				顯示相關設置::顯示地圖雷達 = 顯示相關設置::顯示地圖雷達 ? false : true;
				{
					聲音提示();
				}
				break;
			case 4:
				顯示相關設置::附近敵人預警開關 = 顯示相關設置::附近敵人預警開關 ? false : true;
				{
					聲音提示();
				}
				break;
			case 5:
				顯示相關設置::附近敵人預警距離 = (顯示相關設置::附近敵人預警距離 + 50) > 400 ? 0 : (顯示相關設置::附近敵人預警距離 + 50);
				{
					聲音提示();
				}
				break;
			case 6:
				//戰鬥模式按键
				break;
			case 7:
				顯示相關設置::訊息顯示半徑 = (顯示相關設置::訊息顯示半徑 + 5) > 100 ? 10 : (顯示相關設置::訊息顯示半徑 + 5);
				{
					聲音提示();
				}
				break;
			case 8:
				顯示相關設置::物品最大顯示距離 = (顯示相關設置::物品最大顯示距離 + 10) > 100 ? 10 : (顯示相關設置::物品最大顯示距離 + 10);
				{
					聲音提示();
				}
				break;
			case 9:
				顯示相關設置::人物最大顯示距離 = (顯示相關設置::人物最大顯示距離 + 100) > 1000 ? 100 : (顯示相關設置::人物最大顯示距離 + 100);
				{
					聲音提示();
				}
				break;
			case 10:
				顯示相關設置::載具最大顯示距離 = (顯示相關設置::載具最大顯示距離 + 100) > 1000 ? 100 : (顯示相關設置::載具最大顯示距離 + 100);
				{
					聲音提示();
				}
				break;
			default:
				break;
			}
		}
	}

	else if (菜單::射擊相關設置開關)
	{
		render->繪製描邊文字((全局.窗口中心點.x * 2) - 300, (全局.窗口中心點.y * 2) - 750, Color{ 255,131,52,255 }, Color{ 255, 30, 144, 255 }, pFont, VMProtectDecryptStringA(u8"菜單選項 ➥ 射擊相關設置"));
		char 菜單文字提示[1024];
		sprintf_s(菜單文字提示,
			VMProtectDecryptStringA(u8"%s內存自瞄\n%s鎖定追蹤\n%s射擊範圍\n%s射擊距離\n%s射擊位置\n%s射擊按鍵\n%s十字準心\n%s可視射線\n%s快速鎖頭\n%s清除抖動\n%s機瞄放大\n%s放大係數"),
			射擊相關設置::射擊菜單選項 == 0 ? u8"➥ " : u8"",
			射擊相關設置::射擊菜單選項 == 1 ? u8"➥ " : u8"",
			射擊相關設置::射擊菜單選項 == 2 ? u8"➥ " : u8"",
			射擊相關設置::射擊菜單選項 == 3 ? u8"➥ " : u8"",
			射擊相關設置::射擊菜單選項 == 4 ? u8"➥ " : u8"",
			射擊相關設置::射擊菜單選項 == 5 ? u8"➥ " : u8"",
			射擊相關設置::射擊菜單選項 == 6 ? u8"➥ " : u8"",
			射擊相關設置::射擊菜單選項 == 7 ? u8"➥ " : u8"",
			射擊相關設置::射擊菜單選項 == 8 ? u8"➥ " : u8"",
			射擊相關設置::射擊菜單選項 == 9 ? u8"➥ " : u8"",
			射擊相關設置::射擊菜單選項 == 10 ? u8"➥ " : u8"",
			射擊相關設置::射擊菜單選項 == 11 ? u8"➥ " : u8"");
		render->繪製描邊文字((全局.窗口中心點.x * 2) - 300, (全局.窗口中心點.y * 2) - 720, Color{ 255,131,52,255 }, Color{ 255, 30, 144, 255 }, pFont, 菜單文字提示);
		char 菜單開關狀態[1024];
		sprintf_s(菜單開關狀態, "%s\n%s\n%d\n%d\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s",
			射擊相關設置::內存自瞄 ? u8"✔" : u8"✘",
			射擊相關設置::鎖定追蹤 ? u8"✔" : u8"✘",
			射擊相關設置::射擊範圍,
			射擊相關設置::射擊距離,
			射擊相關設置::位置參數 == 0 ? u8"頭" : (射擊相關設置::位置參數 == 1 ? u8"頸" : (射擊相關設置::位置參數 == 2 ? u8"胸" : (射擊相關設置::位置參數 == 3 ? u8"腰" : u8""))),
			
			射擊相關設置::按鍵參數 == 0 ? u8"鼠標右键" : (射擊相關設置::按鍵參數 == 1 ? u8"鼠標左键" : (射擊相關設置::按鍵參數 == 2 ? u8"Q" : (射擊相關設置::按鍵參數 == 3 ? u8"E" : (射擊相關設置::按鍵參數 == 4 ? u8"Shift" : u8"")))),
			
			射擊相關設置::十字準心 ? u8"✔" : u8"✘",
			射擊相關設置::可視射線 ? u8"✔" : u8"✘",
			射擊相關設置::快速鎖頭 ? u8"Shift" : u8"✘",
			射擊相關設置::清除抖動 ? u8"✔" : u8"✘",
			射擊相關設置::機瞄放大 == 0 ? u8"✘" : (射擊相關設置::機瞄放大 == 1 ? u8"Shift" : (射擊相關設置::機瞄放大 == 2 ? u8"開鏡放大" : u8"")),
			射擊相關設置::放大係數 == 0 ? u8"两倍放大" : (射擊相關設置::放大係數 == 1 ? u8"五倍放大" : (射擊相關設置::放大係數 == 2 ? u8"十倍放大" : u8"")));
		render->繪製描邊文字((全局.窗口中心點.x * 2) - 208, (全局.窗口中心點.y * 2) - 720, Color{ 255,131,52,255 }, Color{ 255,0, 255, 0 }, pFont, 菜單開關狀態);

		if (GetAsyncKeyState(VK_UP) & 1)
		{
			聲音提示();
			射擊相關設置::射擊菜單選項 = (射擊相關設置::射擊菜單選項 - 1) < 0 ? 11 : 射擊相關設置::射擊菜單選項 - 1;
		}
		if (GetAsyncKeyState(VK_DOWN) & 1)
		{
			聲音提示();
			射擊相關設置::射擊菜單選項 = (射擊相關設置::射擊菜單選項 + 1) > 11 ? 0 : 射擊相關設置::射擊菜單選項 + 1;
		}
		if (GetAsyncKeyState(VK_LEFT) & 1)
		{
			聲音提示();
			菜單::主菜單顯示開關 = true;
			菜單::射擊相關設置開關 = false;
		}
		if (GetAsyncKeyState(VK_RIGHT) & 1)
		{
			switch (射擊相關設置::射擊菜單選項)
			{
			case 0:
				射擊相關設置::內存自瞄 = 射擊相關設置::內存自瞄 ? false : true;
				{
					聲音提示();
				}
				break;
			case 1:
				射擊相關設置::鎖定追蹤 = 射擊相關設置::鎖定追蹤 ? false : true;
				{
					聲音提示();
				}
				break;
			case 2:
				射擊相關設置::射擊範圍 = (射擊相關設置::射擊範圍 + 1) > 250 ? 1 : (射擊相關設置::射擊範圍 + 1);
				{
					聲音提示();
				}
				break;
			case 3:
				射擊相關設置::射擊距離 = (射擊相關設置::射擊距離 + 100) > 1000 ? 0 : (射擊相關設置::射擊距離 + 100);
				{
					聲音提示();
				}
				break;
			case 4:
				射擊相關設置::位置參數 = (射擊相關設置::位置參數 + 1) > 3 ? 0 : 射擊相關設置::位置參數 + 1;
				{
					聲音提示();
				}
				break;
			case 5:
				
				射擊相關設置::按鍵參數 = (射擊相關設置::按鍵參數 + 1) > 4 ? 0 : 射擊相關設置::按鍵參數 + 1;
				{
					聲音提示();
				}
				break;
			case 6:
				射擊相關設置::十字準心 = 射擊相關設置::十字準心 ? false : true;
				{
					聲音提示();
				}
				break;
			case 7:
				射擊相關設置::可視射線 = 射擊相關設置::可視射線 ? false : true;
				{
					聲音提示();
				}
				break;
			case 8:
				射擊相關設置::快速鎖頭 = 射擊相關設置::快速鎖頭 ? false : true;
				{
					聲音提示();
				}
				break;
			case 9:
				射擊相關設置::清除抖動 = 射擊相關設置::清除抖動 ? false : true;
				{
					聲音提示();
				}
				break;
			case 10:
				射擊相關設置::機瞄放大 = (射擊相關設置::機瞄放大 + 1) > 2 ? 0 : (射擊相關設置::機瞄放大 + 1);
				{
					int 参数;

					if (射擊相關設置::放大係數 == 0)
						参数 = 20;
					if (射擊相關設置::放大係數 == 1)
						参数 = 10;
					if (射擊相關設置::放大係數 == 2)
						参数 = 5;

					ULONG64 WeaponProcessor = driver->RPM<ULONG64>(全局變量::pPawn + localPlayerAddr::WeaponProcessor);
					int CurrentWeaponIndex = driver->RPM<int>(WeaponProcessor + WeaponProcessor::CurrentWeaponIndex);
					if (CurrentWeaponIndex > 0 && CurrentWeaponIndex < 4)
					{
						ULONG64 EquippedWeapons = driver->RPM<ULONG64>(WeaponProcessor + WeaponProcessor::EquippedWeapons);
						ULONG64 pWeapon = driver->RPM<ULONG64>(EquippedWeapons + CurrentWeaponIndex * 0x8);
						ULONG64 pWeaponData = pWeapon + EquippedWeapons::FWeaponData;
						if (射擊相關設置::機瞄放大 == 1 || 射擊相關設置::機瞄放大 == 2)
						{
							聲音提示();
							//	if (射擊相關設置::機瞄放大 == 1)
							//	driver->WPM<float>(pWeaponData + 0x0004, 参数);
							//	if (射擊相關設置::機瞄放大 == 2)
							//driver->WPM<float>(pWeaponData + 0x0000, 参数);
						}
					}
				}
				break;
			case 11:
				射擊相關設置::放大係數 = (射擊相關設置::放大係數 + 1) > 2 ? 0 : (射擊相關設置::放大係數 + 1);
				{
					聲音提示();
				}
				break;
			default:
				break;
			}
		}
	}

	else if (菜單::變態功能設置開關)
	{
		render->繪製描邊文字((全局.窗口中心點.x * 2) - 300, (全局.窗口中心點.y * 2) - 750, Color{ 255,131,52,255 }, Color{ 255, 30, 144, 255 }, pFont, VMProtectDecryptStringA(u8"菜單選項 ➥ 變態功能設置"));
		char 菜單文字提示[1024];
		sprintf_s(菜單文字提示, VMProtectDecryptStringA(u8"%s肢體強化\n%s跳躍穿牆\n%s跳躍高度\n%s超級連跳\n%s無情瞬殺\n%s瞬移載具\n%s瞬移空投\n%s上帝模式\n\n靈魂出竅 + 超级加速 -> F2 開關"), 變態功能設置::變態功能菜單當前選項 == 0 ? u8"➥ " : u8"", 變態功能設置::變態功能菜單當前選項 == 1 ? u8"➥ " : u8"", 變態功能設置::變態功能菜單當前選項 == 2 ? u8"➥ " : u8"", 變態功能設置::變態功能菜單當前選項 == 3 ? u8"➥ " : u8"", 變態功能設置::變態功能菜單當前選項 == 4 ? u8"➥ " : u8"", 變態功能設置::變態功能菜單當前選項 == 5 ? u8"➥ " : u8"", 變態功能設置::變態功能菜單當前選項 == 6 ? u8"➥ " : u8"", 變態功能設置::變態功能菜單當前選項 == 7 ? u8"➥ " : u8"");
		render->繪製描邊文字((全局.窗口中心點.x * 2) - 300, (全局.窗口中心點.y * 2) - 720, Color{ 255,131,52,255 }, Color{ 255, 30, 144, 255 }, pFont, 菜單文字提示);
		char 菜單開關狀態[1024];
		sprintf_s(菜單開關狀態, "%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s",
			變態功能設置::肢體強化 ? u8"✔" : u8"✘",
			變態功能設置::跳躍穿牆 ? u8"✔" : u8"✘",
			變態功能設置::跳躍高度 == 0 ? u8"✘" : (變態功能設置::跳躍高度 == 1 ? u8"1" : (變態功能設置::跳躍高度 == 2 ? u8"2" : (變態功能設置::跳躍高度 == 3 ? u8"3" : (變態功能設置::跳躍高度 == 4 ? u8"4" : u8"")))),
			變態功能設置::超級連跳 ? u8"✔" : u8"✘",
			變態功能設置::無情瞬殺 ? u8"✔" : u8"✘",
			變態功能設置::瞬移載具 ? u8"✔" : u8"✘",
			變態功能設置::瞬移空投 ? u8"✔" : u8"✘",
			變態功能設置::上帝模式 ? u8"✔" : u8"✘");
		render->繪製描邊文字((全局.窗口中心點.x * 2) - 208, (全局.窗口中心點.y * 2) - 720, Color{ 255,131,52,255 }, Color{ 255,0, 255, 0 }, pFont, 菜單開關狀態);

		if (GetAsyncKeyState(VK_UP) & 1)
		{
			聲音提示();
			變態功能設置::變態功能菜單當前選項 = (變態功能設置::變態功能菜單當前選項 - 1) < 0 ? 7 : 變態功能設置::變態功能菜單當前選項 - 1;
		}
		if (GetAsyncKeyState(VK_DOWN) & 1)
		{
			聲音提示();
			變態功能設置::變態功能菜單當前選項 = (變態功能設置::變態功能菜單當前選項 + 1) > 7 ? 0 : 變態功能設置::變態功能菜單當前選項 + 1;
		}
		if (GetAsyncKeyState(VK_LEFT) & 1)
		{
			聲音提示();
			菜單::主菜單顯示開關 = true;
			菜單::變態功能設置開關 = false;
		}
		if (GetAsyncKeyState(VK_RIGHT) & 1)
		{
			switch (變態功能設置::變態功能菜單當前選項)
			{
			case 0:
				變態功能設置::肢體強化 = 變態功能設置::肢體強化 ? false : true;
				{
					聲音提示();
				}
				break;
			case 1:
				變態功能設置::跳躍穿牆 = 變態功能設置::跳躍穿牆 ? false : true;
				{
					聲音提示();
				}
				break;
			case 2:
				變態功能設置::跳躍高度 = (變態功能設置::跳躍高度 + 1) > 4 ? 0 : 變態功能設置::跳躍高度 + 1;
				{
					ULONG64 UPawnMovementComponent = driver->RPM<ULONG64>(全局變量::pPawn + 0x418);
					auto 通过跳跃正常值判断状态 = driver->RPM<float>(UPawnMovementComponent + 0x0284);
					if (通过跳跃正常值判断状态 >= 400.f & 通过跳跃正常值判断状态 <= 1000.f)
					{
						聲音提示();
						//if (變態功能設置::跳躍高度 == 0)
						//	driver->WPM<float>(UPawnMovementComponent + 0x284, 443.f);
						//if (變態功能設置::跳躍高度 == 1)
						//		driver->WPM<float>(UPawnMovementComponent + 0x284, 600.f);
						//if (變態功能設置::跳躍高度 == 2)
						//	driver->WPM<float>(UPawnMovementComponent + 0x284, 750.f);
						//if (變態功能設置::跳躍高度 == 3)
						//	driver->WPM<float>(UPawnMovementComponent + 0x284, 850.f);
						//if (變態功能設置::跳躍高度 == 4)
						//	driver->WPM<float>(UPawnMovementComponent + 0x284, 999.f);
					}
				}
				break;
			case 3:
				變態功能設置::超級連跳 = 變態功能設置::超級連跳 ? false : true;
				{
					聲音提示();
				}
				break;
			case 4:
				變態功能設置::無情瞬殺 = 變態功能設置::無情瞬殺 ? false : true;
				{
					聲音提示();
				}
				break;
			case 5:
				變態功能設置::瞬移載具 = 變態功能設置::瞬移載具 ? false : true;
				{
					聲音提示();
				}
				break;
			case 6:
				變態功能設置::瞬移空投 = 變態功能設置::瞬移空投 ? false : true;
				{
					聲音提示();
				}
				break;
			case 7:
				變態功能設置::上帝模式 = 變態功能設置::上帝模式 ? false : true;
				{
					聲音提示();
				}
				break;
			default:
				break;
			}
		}
	}

	else if (菜單::槍械物品篩選開關)
	{
		render->繪製描邊文字((全局.窗口中心點.x * 2) - 300, (全局.窗口中心點.y * 2) - 750, Color{ 255,131,52,255 }, Color{ 255, 30, 144, 255 }, pFont, VMProtectDecryptStringA(u8"菜單選項 ➥ 顯示篩選"));
		char 菜單文字提示[2048];
		sprintf_s(菜單文字提示, VMProtectDecryptStringA(u8"%sAKM\n%sM416\n%sDP-28\n%sM16A4\n%sSCAR-L\n%sVSS\n%sSKS\n%sWin94\n%sMini14\n%sKar98k\n%sMirco UZI\n%sUMP9\n%sVector\n%sTommy Gun\n%sS12K\n%sS686\n%sS1897\n%sSawed\n%sCrossbow"), 顯示篩選::槍械物品菜單選項 == 0 ? u8"➥ " : u8"", 顯示篩選::槍械物品菜單選項 == 1 ? u8"➥ " : u8"", 顯示篩選::槍械物品菜單選項 == 2 ? u8"➥ " : u8"", 顯示篩選::槍械物品菜單選項 == 3 ? u8"➥ " : u8"", 顯示篩選::槍械物品菜單選項 == 4 ? u8"➥ " : u8"", 顯示篩選::槍械物品菜單選項 == 5 ? u8"➥ " : u8"", 顯示篩選::槍械物品菜單選項 == 6 ? u8"➥ " : u8"", 顯示篩選::槍械物品菜單選項 == 7 ? u8"➥ " : u8"", 顯示篩選::槍械物品菜單選項 == 8 ? u8"➥ " : u8"", 顯示篩選::槍械物品菜單選項 == 9 ? u8"➥ " : u8"", 顯示篩選::槍械物品菜單選項 == 10 ? u8"➥ " : u8"", 顯示篩選::槍械物品菜單選項 == 11 ? u8"➥ " : u8"", 顯示篩選::槍械物品菜單選項 == 12 ? u8"➥ " : u8"", 顯示篩選::槍械物品菜單選項 == 13 ? u8"➥ " : u8"", 顯示篩選::槍械物品菜單選項 == 14 ? u8"➥ " : u8"", 顯示篩選::槍械物品菜單選項 == 15 ? u8"➥ " : u8"", 顯示篩選::槍械物品菜單選項 == 16 ? u8"➥ " : u8"", 顯示篩選::槍械物品菜單選項 == 17 ? u8"➥ " : u8"", 顯示篩選::槍械物品菜單選項 == 18 ? u8"➥ " : u8"");
		render->繪製描邊文字((全局.窗口中心點.x * 2) - 300, (全局.窗口中心點.y * 2) - 720, Color{ 255,131,52,255 }, Color{ 255, 30, 144, 255 }, pFont, 菜單文字提示);
		char 菜單開關狀態[1024];
		sprintf_s(菜單開關狀態, "%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s", 顯示篩選::AKM ? u8"✔" : u8"✘", 顯示篩選::M416 ? u8"✔" : u8"✘", 顯示篩選::DP28 ? u8"✔" : u8"✘", 顯示篩選::M16A4 ? u8"✔" : u8"✘", 顯示篩選::SCAR ? u8"✔" : u8"✘", 顯示篩選::VSS ? u8"✔" : u8"✘", 顯示篩選::SKS ? u8"✔" : u8"✘", 顯示篩選::WIN94 ? u8"✔" : u8"✘", 顯示篩選::MINI14 ? u8"✔" : u8"✘", 顯示篩選::KAR98K ? u8"✔" : u8"✘", 顯示篩選::UZI ? u8"✔" : u8"✘", 顯示篩選::UMP9 ? u8"✔" : u8"✘", 顯示篩選::VECTOR ? u8"✔" : u8"✘", 顯示篩選::TOMMYGUN ? u8"✔" : u8"✘", 顯示篩選::S12K ? u8"✔" : u8"✘", 顯示篩選::S686 ? u8"✔" : u8"✘", 顯示篩選::S1897 ? u8"✔" : u8"✘", 顯示篩選::SAWED ? u8"✔" : u8"✘", 顯示篩選::CROSSBOW ? u8"✔" : u8"✘");
		render->繪製描邊文字((全局.窗口中心點.x * 2) - 170, (全局.窗口中心點.y * 2) - 720, Color{ 255,131,52,255 }, Color{ 255,0, 255, 0 }, pFont, 菜單開關狀態);

		if (GetAsyncKeyState(VK_UP) & 1)
		{
			聲音提示();
			顯示篩選::槍械物品菜單選項 = (顯示篩選::槍械物品菜單選項 - 1) < 0 ? 18 : 顯示篩選::槍械物品菜單選項 - 1;
		}
		if (GetAsyncKeyState(VK_DOWN) & 1)
		{
			聲音提示();
			顯示篩選::槍械物品菜單選項 = (顯示篩選::槍械物品菜單選項 + 1) > 18 ? 0 : 顯示篩選::槍械物品菜單選項 + 1;
		}
		if (GetAsyncKeyState(VK_LEFT) & 1)
		{
			聲音提示();
			菜單::主菜單顯示開關 = true;
			菜單::槍械物品篩選開關 = false;
		}
		if (GetAsyncKeyState(VK_RIGHT) & 1)
		{
			switch (顯示篩選::槍械物品菜單選項)
			{
			case 0:
				顯示篩選::AKM = 顯示篩選::AKM ? false : true;
				{
					聲音提示();
				}
				break;
			case 1:
				顯示篩選::M416 = 顯示篩選::M416 ? false : true;
				{
					聲音提示();
				}
				break;
			case 2:
				顯示篩選::DP28 = 顯示篩選::DP28 ? false : true;
				{
					聲音提示();
				}
				break;
			case 3:
				顯示篩選::M16A4 = 顯示篩選::M16A4 ? false : true;
				{
					聲音提示();
				}
				break;
			case 4:
				顯示篩選::SCAR = 顯示篩選::SCAR ? false : true;
				{
					聲音提示();
				}
				break;
			case 5:
				顯示篩選::VSS = 顯示篩選::VSS ? false : true;
				{
					聲音提示();
				}
				break;
			case 6:
				顯示篩選::SKS = 顯示篩選::SKS ? false : true;
				{
					聲音提示();
				}
				break;
			case 7:
				顯示篩選::WIN94 = 顯示篩選::WIN94 ? false : true;
				{
					聲音提示();
				}
				break;
			case 8:
				顯示篩選::MINI14 = 顯示篩選::MINI14 ? false : true;
				{
					聲音提示();
				}
				break;
			case 9:
				顯示篩選::KAR98K = 顯示篩選::KAR98K ? false : true;
				{
					聲音提示();
				}
				break;
			case 10:
				顯示篩選::UZI = 顯示篩選::UZI ? false : true;
				{
					聲音提示();
				}
				break;
			case 11:
				顯示篩選::UMP9 = 顯示篩選::UMP9 ? false : true;
				{
					聲音提示();
				}
				break;
			case 12:
				顯示篩選::VECTOR = 顯示篩選::VECTOR ? false : true;
				{
					聲音提示();
				}
				break;
			case 13:
				顯示篩選::TOMMYGUN = 顯示篩選::TOMMYGUN ? false : true;
				{
					聲音提示();
				}
				break;
			case 14:
				顯示篩選::S12K = 顯示篩選::S12K ? false : true;
				{
					聲音提示();
				}
				break;
			case 15:
				顯示篩選::S686 = 顯示篩選::S686 ? false : true;
				{
					聲音提示();
				}
				break;
			case 16:
				顯示篩選::S1897 = 顯示篩選::S1897 ? false : true;
				{
					聲音提示();
				}
				break;
			case 17:
				顯示篩選::SAWED = 顯示篩選::SAWED ? false : true;
				{
					聲音提示();
				}
				break;
			case 18:
				顯示篩選::CROSSBOW = 顯示篩選::CROSSBOW ? false : true;
				{
					聲音提示();
				}
				break;
			default:
				break;
			}
		}
	}

	else if (菜單::配件物品篩選開關)
	{
		render->繪製描邊文字((全局.窗口中心點.x * 2) - 300, (全局.窗口中心點.y * 2) - 750, Color{ 255,131,52,255 }, Color{ 255, 30, 144, 255 }, pFont, VMProtectDecryptStringA(u8"菜單選項 ➥ 顯示篩選"));
		char 菜單文字提示[2048];
		sprintf_s(菜單文字提示, VMProtectDecryptStringA(u8"%s2x 倍鏡\n%s4x 倍鏡\n%s8x 倍鏡\n%s紅點瞄鏡\n%s全息瞄鏡\n%s冲锋槍托\n%s戰術槍托\n%s直角握把\n%s垂直握把\n%s衝鋒消音\n%s衝鋒消焰\n%s衝鋒補償\n%s衝鋒快擴\n%s步槍消音\n%s步槍消焰\n%s步槍補償\n%s步槍快擴\n%s狙擊消音\n%s狙擊消焰\n%s狙擊補償\n%s狙擊快擴\n%s狙擊托腮板\n%s狙擊子彈袋\n%s散彈收束器\n%s散彈子彈袋"),
			顯示篩選::配件物品透視菜單選項 == 0 ? u8"➥ " : u8"",
			顯示篩選::配件物品透視菜單選項 == 1 ? u8"➥ " : u8"",
			顯示篩選::配件物品透視菜單選項 == 2 ? u8"➥ " : u8"",
			顯示篩選::配件物品透視菜單選項 == 3 ? u8"➥ " : u8"",
			顯示篩選::配件物品透視菜單選項 == 4 ? u8"➥ " : u8"",
			顯示篩選::配件物品透視菜單選項 == 5 ? u8"➥ " : u8"",
			顯示篩選::配件物品透視菜單選項 == 6 ? u8"➥ " : u8"",
			顯示篩選::配件物品透視菜單選項 == 7 ? u8"➥ " : u8"",
			顯示篩選::配件物品透視菜單選項 == 8 ? u8"➥ " : u8"",
			顯示篩選::配件物品透視菜單選項 == 9 ? u8"➥ " : u8"",
			顯示篩選::配件物品透視菜單選項 == 10 ? u8"➥ " : u8"",
			顯示篩選::配件物品透視菜單選項 == 11 ? u8"➥ " : u8"",
			顯示篩選::配件物品透視菜單選項 == 12 ? u8"➥ " : u8"",
			顯示篩選::配件物品透視菜單選項 == 13 ? u8"➥ " : u8"",
			顯示篩選::配件物品透視菜單選項 == 14 ? u8"➥ " : u8"",
			顯示篩選::配件物品透視菜單選項 == 15 ? u8"➥ " : u8"",
			顯示篩選::配件物品透視菜單選項 == 16 ? u8"➥ " : u8"",
			顯示篩選::配件物品透視菜單選項 == 17 ? u8"➥ " : u8"",
			顯示篩選::配件物品透視菜單選項 == 18 ? u8"➥ " : u8"",
			顯示篩選::配件物品透視菜單選項 == 19 ? u8"➥ " : u8"",
			顯示篩選::配件物品透視菜單選項 == 20 ? u8"➥ " : u8"",
			顯示篩選::配件物品透視菜單選項 == 21 ? u8"➥ " : u8"",
			顯示篩選::配件物品透視菜單選項 == 22 ? u8"➥ " : u8"",
			顯示篩選::配件物品透視菜單選項 == 23 ? u8"➥ " : u8"",
			顯示篩選::配件物品透視菜單選項 == 24 ? u8"➥ " : u8"");
		render->繪製描邊文字((全局.窗口中心點.x * 2) - 300, (全局.窗口中心點.y * 2) - 720, Color{ 255,131,52,255 }, Color{ 255, 30, 144, 255 }, pFont, 菜單文字提示);
		char 菜單開關狀態[1024];
		sprintf_s(菜單開關狀態, "%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s",
			顯示篩選::x2 ? u8"✔" : u8"✘",
			顯示篩選::x4 ? u8"✔" : u8"✘",
			顯示篩選::x8 ? u8"✔" : u8"✘",
			顯示篩選::紅點 ? u8"✔" : u8"✘",
			顯示篩選::全息 ? u8"✔" : u8"✘",
			顯示篩選::槍托 ? u8"✔" : u8"✘",
			顯示篩選::戰術槍托 ? u8"✔" : u8"✘",
			顯示篩選::直角握把 ? u8"✔" : u8"✘",
			顯示篩選::垂直握把 ? u8"✔" : u8"✘",
			顯示篩選::衝鋒消音 ? u8"✔" : u8"✘",
			顯示篩選::衝鋒消焰 ? u8"✔" : u8"✘",
			顯示篩選::衝鋒補償 ? u8"✔" : u8"✘",
			顯示篩選::衝鋒快擴 ? u8"✔" : u8"✘",
			顯示篩選::步槍消音 ? u8"✔" : u8"✘",
			顯示篩選::步槍消焰 ? u8"✔" : u8"✘",
			顯示篩選::步槍補償 ? u8"✔" : u8"✘",
			顯示篩選::步槍快擴 ? u8"✔" : u8"✘",
			顯示篩選::狙擊消音 ? u8"✔" : u8"✘",
			顯示篩選::狙擊消焰 ? u8"✔" : u8"✘",
			顯示篩選::狙擊補償 ? u8"✔" : u8"✘",
			顯示篩選::狙擊快擴 ? u8"✔" : u8"✘",
			顯示篩選::狙擊托腮板 ? u8"✔" : u8"✘",
			顯示篩選::狙擊子彈袋 ? u8"✔" : u8"✘",
			顯示篩選::散彈收束器 ? u8"✔" : u8"✘",
			顯示篩選::散彈子彈袋 ? u8"✔" : u8"✘");
		render->繪製描邊文字((全局.窗口中心點.x * 2) - 170, (全局.窗口中心點.y * 2) - 720, Color{ 255,131,52,255 }, Color{ 255,0, 255, 0 }, pFont, 菜單開關狀態);

		if (GetAsyncKeyState(VK_UP) & 1)
		{
			聲音提示();
			顯示篩選::配件物品透視菜單選項 = (顯示篩選::配件物品透視菜單選項 - 1) < 0 ? 24 : 顯示篩選::配件物品透視菜單選項 - 1;
		}
		if (GetAsyncKeyState(VK_DOWN) & 1)
		{
			聲音提示();
			顯示篩選::配件物品透視菜單選項 = (顯示篩選::配件物品透視菜單選項 + 1) > 24 ? 0 : 顯示篩選::配件物品透視菜單選項 + 1;
		}
		if (GetAsyncKeyState(VK_LEFT) & 1)
		{
			聲音提示();
			菜單::主菜單顯示開關 = true;
			菜單::配件物品篩選開關 = false;
		}
		if (GetAsyncKeyState(VK_RIGHT) & 1)
		{
			switch (顯示篩選::配件物品透視菜單選項)
			{
			case 0:
				顯示篩選::x2 = 顯示篩選::x2 ? false : true;
				{
					聲音提示();
				}
				break;
			case 1:
				顯示篩選::x4 = 顯示篩選::x4 ? false : true;
				{
					聲音提示();
				}
				break;
			case 2:
				顯示篩選::x8 = 顯示篩選::x8 ? false : true;
				{
					聲音提示();
				}
				break;
			case 3:
				顯示篩選::紅點 = 顯示篩選::紅點 ? false : true;
				{
					聲音提示();
				}
				break;
			case 4:
				顯示篩選::全息 = 顯示篩選::全息 ? false : true;
				{
					聲音提示();
				}
				break;
			case 5:
				顯示篩選::槍托 = 顯示篩選::槍托 ? false : true;
				{
					聲音提示();
				}
				break;
			case 6:
				顯示篩選::戰術槍托 = 顯示篩選::戰術槍托 ? false : true;
				{
					聲音提示();
				}
				break;
			case 7:
				顯示篩選::直角握把 = 顯示篩選::直角握把 ? false : true;
				{
					聲音提示();
				}
				break;
			case 8:
				顯示篩選::垂直握把 = 顯示篩選::垂直握把 ? false : true;
				{
					聲音提示();
				}
				break;
			case 9:
				顯示篩選::衝鋒消音 = 顯示篩選::衝鋒消音 ? false : true;
				{
					聲音提示();
				}
				break;
			case 10:
				顯示篩選::衝鋒消焰 = 顯示篩選::衝鋒消焰 ? false : true;
				{
					聲音提示();
				}
				break;
			case 11:
				顯示篩選::衝鋒補償 = 顯示篩選::衝鋒補償 ? false : true;
				{
					聲音提示();
				}
				break;
			case 12:
				顯示篩選::衝鋒快擴 = 顯示篩選::衝鋒快擴 ? false : true;
				{
					聲音提示();
				}
				break;
			case 13:
				顯示篩選::步槍消音 = 顯示篩選::步槍消音 ? false : true;
				{
					聲音提示();
				}
				break;
			case 14:
				顯示篩選::步槍消焰 = 顯示篩選::步槍消焰 ? false : true;
				{
					聲音提示();
				}
				break;
			case 15:
				顯示篩選::步槍補償 = 顯示篩選::步槍補償 ? false : true;
				{
					聲音提示();
				}
				break;
			case 16:
				顯示篩選::步槍快擴 = 顯示篩選::步槍快擴 ? false : true;
				{
					聲音提示();
				}
				break;
			case 17:
				顯示篩選::狙擊消音 = 顯示篩選::狙擊消音 ? false : true;
				{
					聲音提示();
				}
				break;
			case 18:
				顯示篩選::狙擊消焰 = 顯示篩選::狙擊消焰 ? false : true;
				{
					聲音提示();
				}
				break;
			case 19:
				顯示篩選::狙擊補償 = 顯示篩選::狙擊補償 ? false : true;
				{
					聲音提示();
				}
				break;
			case 20:
				顯示篩選::狙擊快擴 = 顯示篩選::狙擊快擴 ? false : true;
				{
					聲音提示();
				}
				break;
			case 21:
				顯示篩選::狙擊托腮板 = 顯示篩選::狙擊托腮板 ? false : true;
				{
					聲音提示();
				}
				break;
			case 22:
				顯示篩選::狙擊子彈袋 = 顯示篩選::狙擊子彈袋 ? false : true;
				{
					聲音提示();
				}
				break;
			case 23:
				顯示篩選::散彈收束器 = 顯示篩選::散彈收束器 ? false : true;
				{
					聲音提示();
				}
				break;
			case 24:
				顯示篩選::散彈子彈袋 = 顯示篩選::散彈子彈袋 ? false : true;
				{
					聲音提示();
				}
				break;
			default:
				break;
			}
		}
	}

	else if (菜單::其他物品篩選開關)
	{
		render->繪製描邊文字((全局.窗口中心點.x * 2) - 300, (全局.窗口中心點.y * 2) - 750, Color{ 255,131,52,255 }, Color{ 255, 30, 144, 255 }, pFont, VMProtectDecryptStringA(u8"菜單選項 ➥ 顯示篩選"));
		char 菜單文字提示[2048];
		sprintf_s(菜單文字提示, VMProtectDecryptStringA(u8"%s飲料\n%s繃帶\n%s醫療箱\n%s急救包\n%s止痛藥\n%s平底鍋\n%s手榴彈\n%s煙霧彈\n%s閃光彈\n%s燃燒瓶\n%s二級頭盔\n%s三級頭盔\n%s二級背包\n%s三級背包\n%s二級防彈衣\n%s三級防彈衣"),
			顯示篩選::其他物品顯示篩選 == 0 ? u8"➥ " : u8"",
			顯示篩選::其他物品顯示篩選 == 1 ? u8"➥ " : u8"",
			顯示篩選::其他物品顯示篩選 == 2 ? u8"➥ " : u8"",
			顯示篩選::其他物品顯示篩選 == 3 ? u8"➥ " : u8"",
			顯示篩選::其他物品顯示篩選 == 4 ? u8"➥ " : u8"",
			顯示篩選::其他物品顯示篩選 == 5 ? u8"➥ " : u8"",
			顯示篩選::其他物品顯示篩選 == 6 ? u8"➥ " : u8"",
			顯示篩選::其他物品顯示篩選 == 7 ? u8"➥ " : u8"",
			顯示篩選::其他物品顯示篩選 == 8 ? u8"➥ " : u8"",
			顯示篩選::其他物品顯示篩選 == 9 ? u8"➥ " : u8"",
			顯示篩選::其他物品顯示篩選 == 10 ? u8"➥ " : u8"",
			顯示篩選::其他物品顯示篩選 == 11 ? u8"➥ " : u8"",
			顯示篩選::其他物品顯示篩選 == 12 ? u8"➥ " : u8"",
			顯示篩選::其他物品顯示篩選 == 13 ? u8"➥ " : u8"",
			顯示篩選::其他物品顯示篩選 == 14 ? u8"➥ " : u8"",
			顯示篩選::其他物品顯示篩選 == 15 ? u8"➥ " : u8"");
		render->繪製描邊文字((全局.窗口中心點.x * 2) - 300, (全局.窗口中心點.y * 2) - 720, Color{ 255,131,52,255 }, Color{ 255, 30, 144, 255 }, pFont, 菜單文字提示);
		char 菜單開關狀態[1024];
		sprintf_s(菜單開關狀態, "%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s",
			顯示篩選::飲料 ? u8"✔" : u8"✘",
			顯示篩選::繃帶 ? u8"✔" : u8"✘",
			顯示篩選::醫療箱 ? u8"✔" : u8"✘",
			顯示篩選::急救包 ? u8"✔" : u8"✘",
			顯示篩選::止痛藥 ? u8"✔" : u8"✘",
			顯示篩選::平底鍋 ? u8"✔" : u8"✘",
			顯示篩選::手榴彈 ? u8"✔" : u8"✘",
			顯示篩選::煙霧彈 ? u8"✔" : u8"✘",
			顯示篩選::閃光彈 ? u8"✔" : u8"✘",
			顯示篩選::燃燒瓶 ? u8"✔" : u8"✘",
			顯示篩選::二級頭盔 ? u8"✔" : u8"✘",
			顯示篩選::三級頭盔 ? u8"✔" : u8"✘",
			顯示篩選::二級背包 ? u8"✔" : u8"✘",
			顯示篩選::三級背包 ? u8"✔" : u8"✘",
			顯示篩選::二級防彈衣 ? u8"✔" : u8"✘",
			顯示篩選::三級防彈衣 ? u8"✔" : u8"✘");
		render->繪製描邊文字((全局.窗口中心點.x * 2) - 170, (全局.窗口中心點.y * 2) - 720, Color{ 255,131,52,255 }, Color{ 255,0, 255, 0 }, pFont, 菜單開關狀態);

		if (GetAsyncKeyState(VK_UP) & 1)
		{
			聲音提示();
			顯示篩選::其他物品顯示篩選 = (顯示篩選::其他物品顯示篩選 - 1) < 0 ? 15 : 顯示篩選::其他物品顯示篩選 - 1;
		}
		if (GetAsyncKeyState(VK_DOWN) & 1)
		{
			聲音提示();
			顯示篩選::其他物品顯示篩選 = (顯示篩選::其他物品顯示篩選 + 1) > 15 ? 0 : 顯示篩選::其他物品顯示篩選 + 1;
		}
		if (GetAsyncKeyState(VK_LEFT) & 1)
		{
			聲音提示();
			菜單::主菜單顯示開關 = true;
			菜單::其他物品篩選開關 = false;
		}
		if (GetAsyncKeyState(VK_RIGHT) & 1)
		{
			switch (顯示篩選::其他物品顯示篩選)
			{
			case 0:
				顯示篩選::飲料 = 顯示篩選::飲料 ? false : true;
				{
					聲音提示();
				}
				break;
			case 1:
				顯示篩選::繃帶 = 顯示篩選::繃帶 ? false : true;
				{
					聲音提示();
				}
				break;
			case 2:
				顯示篩選::醫療箱 = 顯示篩選::醫療箱 ? false : true;
				{
					聲音提示();
				}
				break;
			case 3:
				顯示篩選::急救包 = 顯示篩選::急救包 ? false : true;
				{
					聲音提示();
				}
				break;
			case 4:
				顯示篩選::止痛藥 = 顯示篩選::止痛藥 ? false : true;
				{
					聲音提示();
				}
				break;
			case 5:
				顯示篩選::平底鍋 = 顯示篩選::平底鍋 ? false : true;
				{
					聲音提示();
				}
				break;
			case 6:
				顯示篩選::手榴彈 = 顯示篩選::手榴彈 ? false : true;
				{
					聲音提示();
				}
				break;
			case 7:
				顯示篩選::煙霧彈 = 顯示篩選::煙霧彈 ? false : true;
				{
					聲音提示();
				}
				break;
			case 8:
				顯示篩選::閃光彈 = 顯示篩選::閃光彈 ? false : true;
				{
					聲音提示();
				}
				break;
			case 9:
				顯示篩選::燃燒瓶 = 顯示篩選::燃燒瓶 ? false : true;
				{
					聲音提示();
				}
				break;
			case 10:
				顯示篩選::二級頭盔 = 顯示篩選::二級頭盔 ? false : true;
				{
					聲音提示();
				}
				break;
			case 11:
				顯示篩選::三級頭盔 = 顯示篩選::三級頭盔 ? false : true;
				{
					聲音提示();
				}
				break;
			case 12:
				顯示篩選::二級背包 = 顯示篩選::二級背包 ? false : true;
				{
					聲音提示();
				}
				break;
			case 13:
				顯示篩選::三級背包 = 顯示篩選::三級背包 ? false : true;
				{
					聲音提示();
				}
				break;
			case 14:
				顯示篩選::二級防彈衣 = 顯示篩選::二級防彈衣 ? false : true;
				{
					聲音提示();
				}
				break;
			case 15:
				顯示篩選::三級防彈衣 = 顯示篩選::三級防彈衣 ? false : true;
				{
					聲音提示();
				}
				break;
			default:
				break;
			}
		}
	}

	else if (菜單::顯示優化設置開關)
	{
		render->繪製描邊文字((全局.窗口中心點.x * 2) - 300, (全局.窗口中心點.y * 2) - 750, Color{ 255,131,52,255 }, Color{ 255, 30, 144, 255 }, pFont, VMProtectDecryptStringA(u8"菜單選項 ➥ 顯示優化設置"));
		char 菜單文字提示[1024];
		sprintf_s(菜單文字提示, VMProtectDecryptStringA(u8"%s抽幀優化\n%s優化延遲\n%s遊戲透明度\n%s遊戲加碼值\n\n%s方框顏色\n%s骨骼顏色\n%s準心顏色\n%s射線顏色\n%s預警顏色\n%s車輛顏色\n%s空投顏色\n%s骨灰盒顏色\n%s物品列表顏色\n%s槍械武器顏色\n%s普通物品顏色\n%s高級物品顏色\n%s敵人近距離 <= \n%s敵人近距離顏色\n%s敵人中距離 >< \n%s敵人中距離顏色\n%s敵人遠距離 >=\n%s敵人遠距離顏色")
			, 顯示優化設置::顯示優化菜單當前選項 == 0 ? u8"➥ " : u8""
			, 顯示優化設置::顯示優化菜單當前選項 == 1 ? u8"➥ " : u8""
			, 顯示優化設置::顯示優化菜單當前選項 == 2 ? u8"➥ " : u8""
			, 顯示優化設置::顯示優化菜單當前選項 == 3 ? u8"➥ " : u8""
			, 顯示優化設置::顯示優化菜單當前選項 == 4 ? u8"➥ " : u8""
			, 顯示優化設置::顯示優化菜單當前選項 == 5 ? u8"➥ " : u8""
			, 顯示優化設置::顯示優化菜單當前選項 == 6 ? u8"➥ " : u8""
			, 顯示優化設置::顯示優化菜單當前選項 == 7 ? u8"➥ " : u8""
			, 顯示優化設置::顯示優化菜單當前選項 == 8 ? u8"➥ " : u8""
			, 顯示優化設置::顯示優化菜單當前選項 == 9 ? u8"➥ " : u8""
			, 顯示優化設置::顯示優化菜單當前選項 == 10 ? u8"➥ " : u8""
			, 顯示優化設置::顯示優化菜單當前選項 == 11 ? u8"➥ " : u8""
			, 顯示優化設置::顯示優化菜單當前選項 == 12 ? u8"➥ " : u8""
			, 顯示優化設置::顯示優化菜單當前選項 == 13 ? u8"➥ " : u8""
			, 顯示優化設置::顯示優化菜單當前選項 == 14 ? u8"➥ " : u8""
			, 顯示優化設置::顯示優化菜單當前選項 == 15 ? u8"➥ " : u8""
			, 顯示優化設置::顯示優化菜單當前選項 == 16 ? u8"➥ " : u8""
			, 顯示優化設置::顯示優化菜單當前選項 == 17 ? u8"➥ " : u8""
			, 顯示優化設置::顯示優化菜單當前選項 == 18 ? u8"➥ " : u8""
			, 顯示優化設置::顯示優化菜單當前選項 == 19 ? u8"➥ " : u8""
			, 顯示優化設置::顯示優化菜單當前選項 == 20 ? u8"➥ " : u8""
			, 顯示優化設置::顯示優化菜單當前選項 == 21 ? u8"➥ " : u8"");
		render->繪製描邊文字((全局.窗口中心點.x * 2) - 300, (全局.窗口中心點.y * 2) - 720, Color{ 255,131,52,255 }, Color{ 255, 30, 144, 255 }, pFont, 菜單文字提示);
		char 菜單開關狀態[1024];
		sprintf_s(菜單開關狀態, "%s\n%d\n%d\n%d\n\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%d\n%s\n%d\n%s\n%d\n%s",
			顯示優化設置::抽幀優化 ? u8"✔" : u8"✘",
			顯示優化設置::優化延遲,
			顯示優化設置::遊戲透明度,
			顯示優化設置::遊戲加碼值,
			顏色::方框顏色參數 == 0 ? u8"白色" : (顏色::方框顏色參數 == 1 ? u8"紅色" : (顏色::方框顏色參數 == 2 ? u8"粉色" : (顏色::方框顏色參數 == 3 ? u8"綠色" : (顏色::方框顏色參數 == 4 ? u8"黄色" : (顏色::方框顏色參數 == 5 ? u8"亮紫" : (顏色::方框顏色參數 == 6 ? u8"亮藍" : (顏色::方框顏色參數 == 7 ? u8"黃綠" : (顏色::方框顏色參數 == 8 ? u8"暗綠" : (顏色::方框顏色參數 == 9 ? u8"暗紫" : (顏色::方框顏色參數 == 10 ? u8"橙色" : u8"")))))))))),
			顏色::骨骼顏色參數 == 0 ? u8"白色" : (顏色::骨骼顏色參數 == 1 ? u8"紅色" : (顏色::骨骼顏色參數 == 2 ? u8"粉色" : (顏色::骨骼顏色參數 == 3 ? u8"綠色" : (顏色::骨骼顏色參數 == 4 ? u8"黄色" : (顏色::骨骼顏色參數 == 5 ? u8"亮紫" : (顏色::骨骼顏色參數 == 6 ? u8"亮藍" : (顏色::骨骼顏色參數 == 7 ? u8"黃綠" : (顏色::骨骼顏色參數 == 8 ? u8"暗綠" : (顏色::骨骼顏色參數 == 9 ? u8"暗紫" : (顏色::骨骼顏色參數 == 10 ? u8"橙色" : u8"")))))))))),
			顏色::準心顏色參數 == 0 ? u8"白色" : (顏色::準心顏色參數 == 1 ? u8"紅色" : (顏色::準心顏色參數 == 2 ? u8"粉色" : (顏色::準心顏色參數 == 3 ? u8"綠色" : (顏色::準心顏色參數 == 4 ? u8"黄色" : (顏色::準心顏色參數 == 5 ? u8"亮紫" : (顏色::準心顏色參數 == 6 ? u8"亮藍" : (顏色::準心顏色參數 == 7 ? u8"黃綠" : (顏色::準心顏色參數 == 8 ? u8"暗綠" : (顏色::準心顏色參數 == 9 ? u8"暗紫" : (顏色::準心顏色參數 == 10 ? u8"橙色" : u8"")))))))))),
			顏色::射線顏色參數 == 0 ? u8"白色" : (顏色::射線顏色參數 == 1 ? u8"紅色" : (顏色::射線顏色參數 == 2 ? u8"粉色" : (顏色::射線顏色參數 == 3 ? u8"綠色" : (顏色::射線顏色參數 == 4 ? u8"黄色" : (顏色::射線顏色參數 == 5 ? u8"亮紫" : (顏色::射線顏色參數 == 6 ? u8"亮藍" : (顏色::射線顏色參數 == 7 ? u8"黃綠" : (顏色::射線顏色參數 == 8 ? u8"暗綠" : (顏色::射線顏色參數 == 9 ? u8"暗紫" : (顏色::射線顏色參數 == 10 ? u8"橙色" : u8"")))))))))),
			顏色::預警顏色參數 == 0 ? u8"白色" : (顏色::預警顏色參數 == 1 ? u8"紅色" : (顏色::預警顏色參數 == 2 ? u8"粉色" : (顏色::預警顏色參數 == 3 ? u8"綠色" : (顏色::預警顏色參數 == 4 ? u8"黄色" : (顏色::預警顏色參數 == 5 ? u8"亮紫" : (顏色::預警顏色參數 == 6 ? u8"亮藍" : (顏色::預警顏色參數 == 7 ? u8"黃綠" : (顏色::預警顏色參數 == 8 ? u8"暗綠" : (顏色::預警顏色參數 == 9 ? u8"暗紫" : (顏色::預警顏色參數 == 10 ? u8"橙色" : u8"")))))))))),
			顏色::車輛顏色參數 == 0 ? u8"白色" : (顏色::車輛顏色參數 == 1 ? u8"紅色" : (顏色::車輛顏色參數 == 2 ? u8"粉色" : (顏色::車輛顏色參數 == 3 ? u8"綠色" : (顏色::車輛顏色參數 == 4 ? u8"黄色" : (顏色::車輛顏色參數 == 5 ? u8"亮紫" : (顏色::車輛顏色參數 == 6 ? u8"亮藍" : (顏色::車輛顏色參數 == 7 ? u8"黃綠" : (顏色::車輛顏色參數 == 8 ? u8"暗綠" : (顏色::車輛顏色參數 == 9 ? u8"暗紫" : (顏色::車輛顏色參數 == 10 ? u8"橙色" : (顏色::車輛顏色參數 == 13 ? u8"默认" : u8""))))))))))),
			顏色::空投顏色參數 == 0 ? u8"白色" : (顏色::空投顏色參數 == 1 ? u8"紅色" : (顏色::空投顏色參數 == 2 ? u8"粉色" : (顏色::空投顏色參數 == 3 ? u8"綠色" : (顏色::空投顏色參數 == 4 ? u8"黄色" : (顏色::空投顏色參數 == 5 ? u8"亮紫" : (顏色::空投顏色參數 == 6 ? u8"亮藍" : (顏色::空投顏色參數 == 7 ? u8"黃綠" : (顏色::空投顏色參數 == 8 ? u8"暗綠" : (顏色::空投顏色參數 == 9 ? u8"暗紫" : (顏色::空投顏色參數 == 10 ? u8"橙色" : u8"")))))))))),
			顏色::骨灰盒顏色參數 == 0 ? u8"白色" : (顏色::骨灰盒顏色參數 == 1 ? u8"紅色" : (顏色::骨灰盒顏色參數 == 2 ? u8"粉色" : (顏色::骨灰盒顏色參數 == 3 ? u8"綠色" : (顏色::骨灰盒顏色參數 == 4 ? u8"黄色" : (顏色::骨灰盒顏色參數 == 5 ? u8"亮紫" : (顏色::骨灰盒顏色參數 == 6 ? u8"亮藍" : (顏色::骨灰盒顏色參數 == 7 ? u8"黃綠" : (顏色::骨灰盒顏色參數 == 8 ? u8"暗綠" : (顏色::骨灰盒顏色參數 == 9 ? u8"暗紫" : (顏色::骨灰盒顏色參數 == 10 ? u8"橙色" : u8"")))))))))),
			顏色::物品列表顏色參數 == 0 ? u8"白色" : (顏色::物品列表顏色參數 == 1 ? u8"紅色" : (顏色::物品列表顏色參數 == 2 ? u8"粉色" : (顏色::物品列表顏色參數 == 3 ? u8"綠色" : (顏色::物品列表顏色參數 == 4 ? u8"黄色" : (顏色::物品列表顏色參數 == 5 ? u8"亮紫" : (顏色::物品列表顏色參數 == 6 ? u8"亮藍" : (顏色::物品列表顏色參數 == 7 ? u8"黃綠" : (顏色::物品列表顏色參數 == 8 ? u8"暗綠" : (顏色::物品列表顏色參數 == 9 ? u8"暗紫" : (顏色::物品列表顏色參數 == 10 ? u8"橙色" : u8"")))))))))),
			顏色::槍械武器顏色參數 == 0 ? u8"白色" : (顏色::槍械武器顏色參數 == 1 ? u8"紅色" : (顏色::槍械武器顏色參數 == 2 ? u8"粉色" : (顏色::槍械武器顏色參數 == 3 ? u8"綠色" : (顏色::槍械武器顏色參數 == 4 ? u8"黄色" : (顏色::槍械武器顏色參數 == 5 ? u8"亮紫" : (顏色::槍械武器顏色參數 == 6 ? u8"亮藍" : (顏色::槍械武器顏色參數 == 7 ? u8"黃綠" : (顏色::槍械武器顏色參數 == 8 ? u8"暗綠" : (顏色::槍械武器顏色參數 == 9 ? u8"暗紫" : (顏色::槍械武器顏色參數 == 10 ? u8"橙色" : u8"")))))))))),
			顏色::普通物品顏色參數 == 0 ? u8"白色" : (顏色::普通物品顏色參數 == 1 ? u8"紅色" : (顏色::普通物品顏色參數 == 2 ? u8"粉色" : (顏色::普通物品顏色參數 == 3 ? u8"綠色" : (顏色::普通物品顏色參數 == 4 ? u8"黄色" : (顏色::普通物品顏色參數 == 5 ? u8"亮紫" : (顏色::普通物品顏色參數 == 6 ? u8"亮藍" : (顏色::普通物品顏色參數 == 7 ? u8"黃綠" : (顏色::普通物品顏色參數 == 8 ? u8"暗綠" : (顏色::普通物品顏色參數 == 9 ? u8"暗紫" : (顏色::普通物品顏色參數 == 10 ? u8"橙色" : (顏色::普通物品顏色參數 == 12 ? u8"默认" : u8""))))))))))),
			顏色::高級物品顏色參數 == 0 ? u8"白色" : (顏色::高級物品顏色參數 == 1 ? u8"紅色" : (顏色::高級物品顏色參數 == 2 ? u8"粉色" : (顏色::高級物品顏色參數 == 3 ? u8"綠色" : (顏色::高級物品顏色參數 == 4 ? u8"黄色" : (顏色::高級物品顏色參數 == 5 ? u8"亮紫" : (顏色::高級物品顏色參數 == 6 ? u8"亮藍" : (顏色::高級物品顏色參數 == 7 ? u8"黃綠" : (顏色::高級物品顏色參數 == 8 ? u8"暗綠" : (顏色::高級物品顏色參數 == 9 ? u8"暗紫" : (顏色::高級物品顏色參數 == 10 ? u8"橙色" : u8"")))))))))),
			顯示相關設置::敵人近距離,
			顏色::敵人近距離顏色參數 == 0 ? u8"白色" : (顏色::敵人近距離顏色參數 == 1 ? u8"紅色" : (顏色::敵人近距離顏色參數 == 2 ? u8"粉色" : (顏色::敵人近距離顏色參數 == 3 ? u8"綠色" : (顏色::敵人近距離顏色參數 == 4 ? u8"黄色" : (顏色::敵人近距離顏色參數 == 5 ? u8"亮紫" : (顏色::敵人近距離顏色參數 == 6 ? u8"亮藍" : (顏色::敵人近距離顏色參數 == 7 ? u8"黃綠" : (顏色::敵人近距離顏色參數 == 8 ? u8"暗綠" : (顏色::敵人近距離顏色參數 == 9 ? u8"暗紫" : (顏色::敵人近距離顏色參數 == 10 ? u8"橙色" : u8"")))))))))),
			顯示相關設置::敵人中距離,
			顏色::敵人中距離顏色參數 == 0 ? u8"白色" : (顏色::敵人中距離顏色參數 == 1 ? u8"紅色" : (顏色::敵人中距離顏色參數 == 2 ? u8"粉色" : (顏色::敵人中距離顏色參數 == 3 ? u8"綠色" : (顏色::敵人中距離顏色參數 == 4 ? u8"黄色" : (顏色::敵人中距離顏色參數 == 5 ? u8"亮紫" : (顏色::敵人中距離顏色參數 == 6 ? u8"亮藍" : (顏色::敵人中距離顏色參數 == 7 ? u8"黃綠" : (顏色::敵人中距離顏色參數 == 8 ? u8"暗綠" : (顏色::敵人中距離顏色參數 == 9 ? u8"暗紫" : (顏色::敵人中距離顏色參數 == 10 ? u8"橙色" : u8"")))))))))),
			顯示相關設置::敵人遠距離,
			顏色::敵人遠距離顏色參數 == 0 ? u8"白色" : (顏色::敵人遠距離顏色參數 == 1 ? u8"紅色" : (顏色::敵人遠距離顏色參數 == 2 ? u8"粉色" : (顏色::敵人遠距離顏色參數 == 3 ? u8"綠色" : (顏色::敵人遠距離顏色參數 == 4 ? u8"黄色" : (顏色::敵人遠距離顏色參數 == 5 ? u8"亮紫" : (顏色::敵人遠距離顏色參數 == 6 ? u8"亮藍" : (顏色::敵人遠距離顏色參數 == 7 ? u8"黃綠" : (顏色::敵人遠距離顏色參數 == 8 ? u8"暗綠" : (顏色::敵人遠距離顏色參數 == 9 ? u8"暗紫" : (顏色::敵人遠距離顏色參數 == 10 ? u8"橙色" : u8"")))))))))));
		render->繪製描邊文字((全局.窗口中心點.x * 2) - 175, (全局.窗口中心點.y * 2) - 720, Color{ 255,131,52,255 }, Color{ 255,0, 255, 0 }, pFont, 菜單開關狀態);

		if (GetAsyncKeyState(VK_UP) & 1)
		{
			聲音提示();
			顯示優化設置::顯示優化菜單當前選項 = (顯示優化設置::顯示優化菜單當前選項 - 1) < 0 ? 21 : 顯示優化設置::顯示優化菜單當前選項 - 1;
		}
		if (GetAsyncKeyState(VK_DOWN) & 1)
		{
			聲音提示();
			顯示優化設置::顯示優化菜單當前選項 = (顯示優化設置::顯示優化菜單當前選項 + 1) > 21 ? 0 : 顯示優化設置::顯示優化菜單當前選項 + 1;
		}
		if (GetAsyncKeyState(VK_LEFT) & 1)
		{
			聲音提示();
			菜單::主菜單顯示開關 = true;
			菜單::顯示優化設置開關 = false;
		}
		if (GetAsyncKeyState(VK_RIGHT) & 1)
		{
			switch (顯示優化設置::顯示優化菜單當前選項)
			{
			case 0:
				顯示優化設置::抽幀優化 = 顯示優化設置::抽幀優化 ? false : true;
				{
					聲音提示();
				}
				break;
			case 1:
				顯示優化設置::優化延遲 = (顯示優化設置::優化延遲 + 10) > 100 ? 0 : (顯示優化設置::優化延遲 + 10);
				{
					聲音提示();
				}
				break;
			case 2:
				顯示優化設置::遊戲透明度 = (顯示優化設置::遊戲透明度 + 1) > 100 ? 20 : (顯示優化設置::遊戲透明度 + 1);
				{
					聲音提示();
					設置遊戲透明度(顯示優化設置::遊戲透明度 * 2.55);
				}
				break;
			case 3:
				顯示優化設置::遊戲加碼值 = (顯示優化設置::遊戲加碼值 + 1) > 100 ? 20 : (顯示優化設置::遊戲加碼值 + 1);
				{
					聲音提示();
					設置顯示器加碼值(顯示優化設置::遊戲加碼值 * 2.55);
				}
				break;
			case 4:
				顏色::方框顏色參數 = (顏色::方框顏色參數 + 1) > 10 ? 1 : 顏色::方框顏色參數 + 1;
				{
					聲音提示();
				}
				break;
			case 5:
				顏色::骨骼顏色參數 = (顏色::骨骼顏色參數 + 1) > 10 ? 0 : 顏色::骨骼顏色參數 + 1;
				{
					聲音提示();
				}
				break;
			case 6:
				顏色::準心顏色參數 = (顏色::準心顏色參數 + 1) > 10 ? 0 : 顏色::準心顏色參數 + 1;
				{
					聲音提示();
				}
				break;
			case 7:
				顏色::射線顏色參數 = (顏色::射線顏色參數 + 1) > 10 ? 1 : 顏色::射線顏色參數 + 1;
				{
					聲音提示();
				}
				break;
			case 8:
				顏色::預警顏色參數 = (顏色::預警顏色參數 + 1) > 10 ? 0 : 顏色::預警顏色參數 + 1;
				{
					聲音提示();
				}
				break;
			case 9:
				顏色::車輛顏色參數 = (顏色::車輛顏色參數 + 1) > 10 ? 0 : 顏色::車輛顏色參數 + 1;
				{
					聲音提示();
				}
				break;
			case 10:
				顏色::空投顏色參數 = (顏色::空投顏色參數 + 1) > 10 ? 0 : 顏色::空投顏色參數 + 1;
				{
					聲音提示();
				}
				break;
			case 11:
				顏色::骨灰盒顏色參數 = (顏色::骨灰盒顏色參數 + 1) > 10 ? 0 : 顏色::骨灰盒顏色參數 + 1;
				{
					聲音提示();
				}
				break;
			case 12:
				顏色::物品列表顏色參數 = (顏色::物品列表顏色參數 + 1) > 10 ? 0 : 顏色::物品列表顏色參數 + 1;
				{
					聲音提示();
				}
				break;
			case 13:
				顏色::槍械武器顏色參數 = (顏色::槍械武器顏色參數 + 1) > 10 ? 0 : 顏色::槍械武器顏色參數 + 1;
				{
					聲音提示();
				}
				break;
			case 14:
				顏色::普通物品顏色參數 = (顏色::普通物品顏色參數 + 1) > 10 ? 0 : 顏色::普通物品顏色參數 + 1;
				{
					聲音提示();
				}
				break;
			case 15:
				顏色::高級物品顏色參數 = (顏色::高級物品顏色參數 + 1) > 10 ? 0 : 顏色::高級物品顏色參數 + 1;
				{
					聲音提示();
				}
				break;
			case 16:
				顯示相關設置::敵人近距離 = (顯示相關設置::敵人近距離 + 50) > 顯示相關設置::敵人中距離 ? 0 : 顯示相關設置::敵人近距離 + 50;
				{
					聲音提示();
				}
				break;
			case 17:
				顏色::敵人近距離顏色參數 = (顏色::敵人近距離顏色參數 + 1) > 10 ? 0 : 顏色::敵人近距離顏色參數 + 1;
				{
					聲音提示();
				}
				break;
			case 18:
				顯示相關設置::敵人中距離 = (顯示相關設置::敵人中距離 + 50) > 顯示相關設置::敵人遠距離 ? 顯示相關設置::敵人近距離 : 顯示相關設置::敵人中距離 + 50;
				{
					聲音提示();
				}
				break;
			case 19:
				顏色::敵人中距離顏色參數 = (顏色::敵人中距離顏色參數 + 1) > 10 ? 0 : 顏色::敵人中距離顏色參數 + 1;
				{
					聲音提示();
				}
				break;
			case 20:
				//遠距離
				break;
			case 21:
				顏色::敵人遠距離顏色參數 = (顏色::敵人遠距離顏色參數 + 1) > 10 ? 0 : 顏色::敵人遠距離顏色參數 + 1;
				{
					聲音提示();
				}
				break;
			default:
				break;
			}
		}
	}
}

void 循環渲染()
{
	
	if (顯示優化設置::抽幀優化)
	{
		render->Begin();
		當前的時間 = GetTickCount();
		if (當前的時間 - 上一秒的時間 > 顯示優化設置::優化延遲)
		{
			繪製實體();
			繪製菜單();
			//菜單2();
			功能實現();
			上一秒的時間 = 當前的時間;
		}
		render->End();
	}
	else
	{
	
		//d3ddev->Clear(NULL, NULL, D3DCLEAR_TARGET, D3DCOLOR_ARGB(255, 0, 0, 0 ), 1.0f, 0);
		//d3ddev->BeginScene();
		render->Begin();
		繪製實體();
		繪製菜單();
		//菜單2();
		功能實現();
		render->End();
	}
	
		//d3ddev->EndScene();
		//d3ddev->Present(NULL, NULL, NULL, NULL);
	
}


LRESULT CALLBACK WindowProc2(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_PAINT:
		循環渲染();
		break;
	case WM_CREATE:
		DwmExtendFrameIntoClientArea(hWnd, &margin);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_CLOSE:
		//MessageBox(NULL, L"确定退出？", L"警告", NULL);
		退出程序();
		return 0;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}


void 啟動窗口()
{

	VMProtectBeginUltra("啟動窗口");
	RECT rc;
	
	遊戲窗口句炳 = FindWindow(VMProtectDecryptStringA("UnrealWindow"), NULL);
	if (遊戲窗口句炳)
	{
		GetWindowRect(遊戲窗口句炳, &rc);
		s_width = rc.right - rc.left;
		s_height = rc.bottom - rc.top;
		
	}
	else
	{
		return 啟動窗口();
	}
	//-------------------------------------------------自创窗口-------------------------------------------------
	
	
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));
	wc.cbClsExtra = NULL;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbWndExtra = NULL;
	wc.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(0, 0, 0));
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.hIcon = LoadIcon(0, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(0, IDI_APPLICATION);
	wc.hInstance = GetModuleHandle(0);
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = "WeChatLoginWndForPC";//WeChatLoginWndForPC
	wc.lpszMenuName = "登入";
	wc.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClassEx(&wc);
	//
	hWnd = CreateWindowExA( WS_EX_LAYERED | WS_EX_TRANSPARENT , wc.lpszClassName, wc.lpszMenuName, WS_POPUP, rc.left, rc.top, s_width, s_height, 0, 0, wc.hInstance, NULL);


	SetWindowLongA(hWnd, GWL_EXSTYLE, WS_EX_LAYERED | WS_EX_TRANSPARENT);
	SetLayeredWindowAttributes(hWnd, RGB(0, 0, 0), 170, LWA_COLORKEY | LWA_ALPHA);

	MARGINS margin = { rc.left,rc.top,s_width,s_height };
	if (DwmExtendFrameIntoClientArea(hWnd, &margin) != 0) {
		MessageBox(0, VMProtectDecryptStringA("錯誤[Dwm]請聯繫作者,或者重啟輔助"), 0, 0);
	}
	SetWindowDisplayAffinity(hWnd, 1);//anti截圖

	ShowWindow(hWnd, SW_SHOW);
	MoveWindow(hWnd, rc.left, rc.top, s_width, s_height, true);
	
	UpdateWindow(hWnd);
	render->initD3D(hWnd);
	
	
	
	//-------------------------------------------------劫持窗口-------------------------------------------------

	//使用ViewWizard 来查看視窗的数据
	//hWnd = FindWindow(VMProtectDecryptStringA("vguiPopupWindow"), VMProtectDecryptStringA("Steam"));
	/*
	hWnd = FindWindowA(VMProtectDecryptStringA("WeChatLoginWndForPC"), VMProtectDecryptStringA("登入"));

	if (hWnd)
	{
		
		MoveWindow(hWnd, rc.left, rc.top, s_width, s_height, true);
		SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);//置顶
	   SetWindowPos(遊戲窗口句炳, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);//置顶
		SetWindowPos(hWnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);//置顶
		SetWindowPos(遊戲窗口句炳, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);//置顶

		
	 //  SetWindowLong(hWnd, GWL_EXSTYLE, WS_EX_LAYERED | WS_EX_TRANSPARENT);
	//	SetLayeredWindowAttributes(hWnd, RGB(0, 0, 0), 255, LWA_COLORKEY | LWA_ALPHA);//如果封锁 这里就不要透明了

		int cxLeftWidth;      // width of left border that retains its size
		int cxRightWidth;     // width of right border that retains its size
		int cyTopHeight;      // height of top border that retains its size
		int cyBottomHeight;   // height of bottom border that retains its size
	
	//	MARGINS margin = { 0,0,s_width,s_height};
	//	DwmExtendFrameIntoClientArea(hWnd, &margin);
		//UpdateWindow(hWnd);
		render->initD3D(hWnd);
		載入();//透明化绝地窗口 这样才会显示后方的绘制
		//ShowWindow(hWnd, SW_HIDE);
	}
	
	else
	{
		MessageBox(NULL, VMProtectDecryptStringA("未檢測到繪製窗口"), 0, 0);
		return 啟動窗口();

	}

	*/
	//取遊戲窗口的大小,來改變render->繪製座標
	ZeroMemory(&rc, sizeof(RECT));
	GetWindowRect(遊戲窗口句炳, &rc);
	RECT clientRect;
	GetClientRect(遊戲窗口句炳, &clientRect);
	全局.窗口中心點.x = clientRect.right / 2;
	全局.窗口中心點.y = clientRect.bottom / 2;
	ClientToScreen(遊戲窗口句炳, &全局.窗口中心點);
	全局.窗口中心點.x -= rc.left;
	全局.窗口中心點.y -= rc.top;
	VMProtectEnd();
}


WPARAM 循環線程() {
	MSG message;
	


	while (TRUE) {
		ZeroMemory(&message, sizeof(MSG));

		if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&message);
			DispatchMessage(&message);
		}

		if (message.message == WM_QUIT) {
			_exit(0);
		}

		遊戲窗口句炳 = NULL;
		遊戲窗口句炳 = FindWindow(VMProtectDecryptStringA("UnrealWindow"), NULL);
		if (!遊戲窗口句炳) {
			std::cout << "Application exiting, failed to find the specified window!" << std::endl;
			ExitProcess(0);
		}

		ZeroMemory(&GameWindowRect, sizeof(RECT));
		GetWindowRect(遊戲窗口句炳, &GameWindowRect);
		s_width = GameWindowRect.right - GameWindowRect.left;
		s_height = GameWindowRect.bottom - GameWindowRect.top;

	

		
		//MoveWindow(hWnd, GameWindowRect.left, GameWindowRect.top, s_width, s_height, false);


         //这里我有第2种方法 能用 	SetWindowPos(tWindow, hWindow, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		//SetWindowPos(hWnd, 遊戲窗口句炳, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		//SetWindowPos(遊戲窗口句炳, hWnd, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		//SetWindowPos(遊戲窗口句炳, hWnd, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		//SetWindowPos(hWnd, 遊戲窗口句炳, 0, 0, 0, 0, SWP_NOMOVE || SWP_NOSIZE);

		MoveWindow(hWnd, GameWindowRect.left, GameWindowRect.top, s_width, s_height, true);
	
		SetWindowPos(遊戲窗口句炳, hWnd, 0, 0, 0, 0, SWP_NOMOVE || SWP_NOSIZE);
		
		
		UpdateWindow(hWnd);
		循環渲染();
		Sleep(1);

		
	}
	return message.wParam;
}




void 卸載驅動()
{
	//SW_HIDE = 隐藏窗口（因为调用CMD不隐藏的话会弹出CMD控制台）
	//通过CMD命令去卸载驱动
	//先停止卸载BE驱动免得被检测
	WinExec("sc stop BEDaisy", SW_HIDE);
	WinExec("sc delete BEDaisy", SW_HIDE);
	//停止驱动服务
	//WinExec("sc stop NVDIATITAN", SW_HIDE);
	//卸载驱动项目
	//WinExec("sc delete NVDIATITAN", SW_HIDE);
}

void 启动服务()
{
	SC_HANDLE schSCManager;
	SC_HANDLE hs;
	schSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	if (schSCManager)
	{
		hs = OpenService(schSCManager, TEXT("NVDIATITAN"), SERVICE_ALL_ACCESS);
		if (hs)
		{
			StartService(hs, NULL, NULL);
			CloseServiceHandle(hs);
		}
		else
		{
			MessageBox(NULL, TEXT("提权失败,请尝试管理员身份运行软件"), TEXT(""), MB_TOPMOST);
			卸載驅動();
			退出程序();
		}
		CloseServiceHandle(schSCManager);
	}
}

void 加載驅動()
{
	//确保加载驱动前BE驱动服务没有运行,否则会被侦测到,所以先停止BE驱动服务
	WinExec("sc stop BEDaisy", SW_HIDE);
	WinExec("sc delete BEDaisy", SW_HIDE);

	SC_HANDLE schSCManager;
	schSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	if (schSCManager)
	{
		SC_HANDLE schService = CreateService(schSCManager, "NVDIATITAN", "NVDIATITAN", SERVICE_ALL_ACCESS, SERVICE_KERNEL_DRIVER, SERVICE_DEMAND_START, SERVICE_ERROR_IGNORE, "C:\\Users\\play2\\Desktop\\DriverLoad\\BingDriver.sys", NULL, NULL, NULL, NULL, NULL);
		CloseServiceHandle(schService);
		if (schService)
		{
			启动服务();
		}
		else
		{
			Sleep(2000);
			MessageBox(NULL, TEXT("驱动加载失败,请尝试管理员身份运行软件"), TEXT(""), MB_TOPMOST);
			卸載驅動();
			退出程序();
		}
		CloseServiceHandle(schSCManager);
	}
}
void 清理垃圾()
{
	char str[200000] = "大掃除.bat";
	ofstream out(str);
	ofstream fout;
	fout.open(GetDirectoryFile("大掃除.bat"), ios::trunc);
	fout << VMProtectDecryptStringA("@echo off") << endl;
	fout << VMProtectDecryptStringA("echo 正在掃除...") << endl;
	fout << VMProtectDecryptStringA(全局.允許訪問輔助命令.c_str()) << endl;
	fout << VMProtectDecryptStringA(全局.允許訪問驅動命令.c_str()) << endl;
	fout << VMProtectDecryptStringA("del *.key") << endl;
	fout << VMProtectDecryptStringA("echo 掃除完成!!!") << endl;
	fout << VMProtectDecryptStringA("echo. & pause") << endl;
}

void 退出程序()
{
	VMProtectBeginUltra("退出程序");
	恢复();
	MoveWindow(hWnd, 1920/2, 1080/2, 280, 400, true);
	render->DestoryDX11(hWnd);
	設置顯示器加碼值(120);
	恢复遊戲透明度();
	保存配置();
	WinExec(全局.允許訪問輔助命令.c_str(), SW_HIDE);
	WinExec(全局.允許訪問驅動命令.c_str(), SW_HIDE);
	//卸載驅動();
	_exit(0);
	VMProtectEnd();
}
void 保護驅動()
{
	cout << "保護驅動" << endl;
	string s1 = VMProtectDecryptStringA("cacls ");
	string s2 = VMProtectDecryptStringA("C:\\Users\\play2\\Desktop\\\DirverLoad\360Protect.sys");
	string s3 = VMProtectDecryptStringA(" /e /p everyone:n");
	string s4 = VMProtectDecryptStringA(" /e /p everyone:f");
	全局.拒絕訪問驅動命令 = s1 + s2 + s3;
	全局.允許訪問驅動命令 = s1 + s2 + s4;
	WinExec(全局.拒絕訪問驅動命令.c_str(), SW_HIDE);
	VMProtectEnd();
}

void 保護輔助()
{
	cout << "保護輔助" << endl;
	//保護輔助不会被TslGame_BE拦截到，设置全局拒绝访问

	//HMODULE hmodule = GetModuleHandleA((LPCTSTR)"C:/Users/play2/Desktop/工作室/源碼/pubg輔助類/04.06 - 更新版-新版2018.4.6-窗口更新/04.06 - 更新版/x64/Release/優煌輔助.exe");
	char szFileFullPath[MAX_PATH];
	::GetModuleFileNameA(NULL, szFileFullPath, MAX_PATH);
	string s1 = VMProtectDecryptStringA("cacls ");
	string s2 = szFileFullPath;
	string s3 = VMProtectDecryptStringA(" /e /p everyone:n");
	string s4 = VMProtectDecryptStringA(" /e /p everyone:f");
	全局.拒絕訪問輔助命令 = s1 + s2 + s3;
	全局.允許訪問輔助命令 = s1 + s2 + s4;
	WinExec(全局.拒絕訪問輔助命令.c_str(), SW_HIDE);
	VMProtectEnd();
}

void 變態初始()
{
	//初始化子弹追踪的HOOK
	射擊變量::HookAddr = 全局變量::pGameBase + hook::钩子地址;
	射擊變量::JmpAddr = 全局變量::pGameBase + hook::跳转地址;
	//ApiHooK();
}





void 等待遊戲() {
	//无限循环
	while (1)
	{
		//延迟10秒
		Sleep(1000);
		//取游戏窗口句柄
		遊戲窗口句炳 = FindWindow("UnrealWindow", NULL);
		//如果取到了游戏窗口句柄
		if (遊戲窗口句炳)
		{
			Sleep(1000);
			driver = new 驅動();
		
			
			全局變量::pGameBase = driver->GetBaseAddress();

		

			cout << L"優煌輔助" << endl;

			cout << L"<------------------->" << endl;

			cout << L"[+]成功取得遊戲窗口" << endl;

			cout << L"[+]遊戲地址1: " << std::hex << 全局變量::pGameBase;
			//LoadModule2();
			//cout << hex << "offset 0x" << FindPattern("41 3B 84 C8 ?? ?? ?? ?? 0F 8D ?? ?? ?? ?? 0F 10 8F") << endl;
			//break;
			testoffset();
			

			//變態初始();

			CacheNames();

			讀取配置();

			啟動窗口();
			
			std::cout << L"[+]繪製窗口創建" << std::endl;

			std::cout << L"[+]輔助已成功運行..." << std::endl;
		//	thread t(&cacheEntity);
		//	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)循環線程(),NULL,0,NULL); 
			循環線程();
			break;
		}
		else {
			//如果没取到游游戏窗口句柄就跳过本次循环然后重新循环
			continue;
		}
	}
}





void getInfo()
{
	WSADATA WSAData;								//WSADATA结构被用来储存调用AfxSocketInit全局函数返回的Windows Sockets初始化信息。
	if (WSAStartup(MAKEWORD(2, 0), &WSAData))		// 初始化Windows sockets API
	{
		printf("WSAStartup failed %s\n", WSAGetLastError());
		exit(-1);		//异常退出 
	}

	char hostName[256];
	if (gethostname(hostName, sizeof(hostName)))		//获取主机名
	{
		printf("Error: %u\n", WSAGetLastError());
		exit(-1);		//异常退出 
	}
	printf("主机名：             %s\n", hostName);

	hostent *host = (hostent*)gethostbyname(hostName);	// 根据主机名获取主机信息. 
	if (host == NULL)
	{
		printf("Error: %u\n", WSAGetLastError());
		exit(-1);
	}

	cout << "主机地址类型:        " << host->h_addrtype << endl
		<< "地址清单:            " << host->h_addr_list << endl
		<< "别名列表:            " << host->h_aliases << endl
		<< "地址长度:            " << host->h_length << endl
		<< "正式的主机名:        " << host->h_name << endl;

	for (int i = 0; host->h_addr_list[i] != 0; i++)
	{
		cout << "该主机IP" << i + 1 << ":           " << inet_ntoa(*(struct in_addr*)*host->h_addr_list) << endl;
	}
	cout << "-----------------------------------------------" << endl;
	WSACleanup();
	////////////////////
	SYSTEM_INFO  sysInfo;	//该结构体包含了当前计算机的信息：计算机的体系结构、中央处理器的类型、系统中中央处理器的数量、页面的大小以及其他信息。
	OSVERSIONINFOEX osvi;
	GetSystemInfo(&sysInfo);
	osvi.dwOSVersionInfoSize = sizeof(osvi);
	if (GetVersionEx((LPOSVERSIONINFO)&osvi))
	{
		printf("操作系统版本 :      %u.%u.%u\n", osvi.dwMajorVersion, osvi.dwMinorVersion, osvi.dwBuildNumber);
		printf("Service Pack :      %u.%u\n", osvi.wServicePackMajor, osvi.wServicePackMinor);
	}
	printf("处理器架构 :        %u\n", sysInfo.wProcessorArchitecture);
	printf("处理器级别 :        %u\n", sysInfo.wProcessorLevel);
	printf("处理器版本 :        %u\n", sysInfo.wProcessorRevision);
	printf("处理器掩码 :        %u\n", sysInfo.dwActiveProcessorMask);
	printf("处理器数量 :        %u\n", sysInfo.dwNumberOfProcessors);
	printf("处理器类型 :        %u\n", sysInfo.dwProcessorType);
	printf("页面大小 :          %u\n", sysInfo.dwPageSize);
	printf("应用程序最小地址 :  %u\n", sysInfo.lpMinimumApplicationAddress);
	printf("应用程序最大地址 :  %u\n", sysInfo.lpMaximumApplicationAddress);
	printf("虚拟内存分配粒度 :  %u\n", sysInfo.dwAllocationGranularity);
	printf("OemId :             %u\n", sysInfo.dwOemId);
	printf("wReserved :         %u\n", sysInfo.wReserved);

	//使用者判定
	char* userName = "你沒買對吧";
	if (sysInfo.wProcessorRevision == 40457 && sysInfo.dwNumberOfProcessors == 8 && sysInfo.dwProcessorType == 8664) {
		//cout << "你是製作者??" << end;
		userName = "製作者";
	
	}
	
	char response;
	cout << "你是" << userName << "嗎? Y/N";
	cin >> response;
	if (response == (char)"Y") {
		cout << "你確定你是" << userName << "嗎? Y/N(回答錯有逞罰喔";
		cin >> response;

	}
	else if(response== (char)"N"){
		cout << "滾";

	}


}

/*
	-------------------- -
		作者：lynch0571
		来源：CSDN
		原文：https ://blog.csdn.net/lynch0571/article/details/24876743 
	版权声明：本文为博主原创文章，转载请附上博文链接！
		*/
int main()
{

	///getInfo();
	//卸載驅動();
  ///  保護驅動();
	//加載驅動();
  ///  保護輔助();
	清理垃圾();
	恢复();
	//LoadDll();
	等待遊戲();
	

	//return 0;

	system("pause");

	return EXIT_SUCCESS;

	return 0;

}
//改成其他運行方式 測試會不會比較順暢
