#pragma once
#include "crappy.h"


#include "Utils.h"
namespace hook
{
	extern ULONG64 钩子地址;
	extern ULONG64 跳转地址;

	extern ULONG64 上下無後座;
	extern ULONG64 左右無後座;
	extern ULONG64 開鏡無後座;
	extern ULONG64 開鏡無後座2;
	extern ULONG64 上下屏息;
	extern ULONG64 左右屏息;
	extern ULONG64 瞬間擊中;
};

namespace offset
{
	extern ULONGLONG GNames;
	extern ULONGLONG CHUNKSIZE;
	extern ULONGLONG UWorld;
	extern ULONGLONG persistentLevel;
	extern ULONGLONG GameInstance;
	extern ULONGLONG LocalPlayerArray;
	extern ULONGLONG playerController;
	extern ULONGLONG PlayerCameraManager;
	extern ULONGLONG acknowledgedPawn;
};

namespace localPlayerAddr
{
	extern ULONGLONG WeaponProcessor;
	extern ULONGLONG ControlRotation;
};
namespace cameraManager
{

	extern ULONGLONG FOV;
	extern ULONGLONG Rotator;
	extern ULONGLONG Location;
};

namespace actor
{
	extern ULONGLONG SpectedCount;
	extern ULONGLONG actorList;
	extern ULONGLONG health;
	extern ULONGLONG GroggyHealth;
	extern ULONGLONG characterMovementComponent;
	extern ULONGLONG team;
	extern ULONGLONG ID;
	extern ULONGLONG bRecentlyRendered;
	extern ULONGLONG WorldSecondTime;
	extern ULONGLONG mesh;
	extern ULONGLONG BoneArray;
	extern ULONGLONG ComponentToWorld;
	extern ULONGLONG PlayerState;
	extern ULONGLONG PlayerName;
	extern ULONGLONG RootComponent;
	extern ULONGLONG _Pos;
	extern ULONGLONG KillNum;
	extern ULONGLONG ComponentVelocity;
	extern ULONGLONG VehicleRiderComponent;
	extern ULONGLONG LastVehiclePawn;
	extern ULONGLONG VehicleVelocity;
	extern ULONGLONG seatIndex;

	extern ULONGLONG ControlRotation_CP;
	extern ULONGLONG animscriptinstance;
	
}

namespace characterMovementComponent
{
	extern ULONGLONG StanceMode;
	extern ULONGLONG NOWALL;
	extern ULONGLONG MaxProneSpeed; //爬行
	extern ULONGLONG MaxGroggySpeed;// 打倒
	extern ULONGLONG MaxWalkSpeed; //慢走
	extern ULONGLONG MaxWalkSpeedCrouched; //蹲着
	extern ULONGLONG MaxSwimSpeed; //游泳(测试不能)
	extern ULONGLONG MaxCustomMovementSpeed; //最大自定义移动速度

	extern ULONGLONG MaxAcceleration;  // 0x270 0x2f8; //移动加速度
	extern ULONGLONG MaxSwimAcceleration;// 自由式
	extern ULONGLONG JumpMaxCount;// 连跳
	extern ULONGLONG JumpZVelocity;//跳高
									//DWORD MaxFlySpeed = 0x2f0; //飞行
									//DWORD CurrentTimeDuration = 0x164;
									//int bActorEnableCollision_Offset = 0xB4;
}

namespace aDroppedItemGroup
{
	extern ULONGLONG relative;
	//extern ULONGLONG ItemName;
	extern ULONGLONG DroppedItemGroupArray;
	extern ULONGLONG DroppedItemGroupCount;
	extern ULONGLONG UItem;
	//extern ULONGLONG UItemFString;
	extern ULONGLONG packageItems;
	extern ULONGLONG packageItemscount;
}

namespace WeaponProcessor
{
	extern ULONGLONG EquippedWeapons;
	extern ULONGLONG CurrentWeaponIndex;
}

namespace EquippedWeapons
{
	extern ULONGLONG FWeaponData;
	extern ULONGLONG FWeaponGunData;
	extern ULONGLONG FWeaponGunAnim;
	extern ULONGLONG FWeaponDeviationData;
	extern ULONGLONG FTrajectoryWeaponData;
	extern ULONGLONG FRecoilInfo;
	extern ULONGLONG WeaponDeviationConfig;
	extern ULONGLONG InitialSpeed;
	extern ULONGLONG TrajectorygravityZ;
	
}

namespace 全局變量
{
	extern ULONG64 pGn;
	extern ULONG64 pUWorld;
	extern ULONG64 pGameInstance;
	extern ULONG64 persistentLevel;
	extern ULONG64 pLocalPlayerArray;
	extern ULONG64 playerController;
	extern ULONG64 PlayerCameraManager;
	extern ULONG64 pPawn;
	extern ULONG64 pViewportClient;
	extern ULONG64 pGameBase;

}