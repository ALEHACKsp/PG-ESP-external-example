#pragma once
#include "crappy.h"


#include "Utils.h"
namespace hook
{
	extern ULONG64 ���ӵ�ַ;
	extern ULONG64 ��ת��ַ;

	extern ULONG64 ���o����;
	extern ULONG64 ���ҟo����;
	extern ULONG64 �_�R�o����;
	extern ULONG64 �_�R�o����2;
	extern ULONG64 ������Ϣ;
	extern ULONG64 ������Ϣ;
	extern ULONG64 ˲�g����;
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
	extern ULONGLONG MaxProneSpeed; //����
	extern ULONGLONG MaxGroggySpeed;// ��
	extern ULONGLONG MaxWalkSpeed; //����
	extern ULONGLONG MaxWalkSpeedCrouched; //����
	extern ULONGLONG MaxSwimSpeed; //��Ӿ(���Բ���)
	extern ULONGLONG MaxCustomMovementSpeed; //����Զ����ƶ��ٶ�

	extern ULONGLONG MaxAcceleration;  // 0x270 0x2f8; //�ƶ����ٶ�
	extern ULONGLONG MaxSwimAcceleration;// ����ʽ
	extern ULONGLONG JumpMaxCount;// ����
	extern ULONGLONG JumpZVelocity;//����
									//DWORD MaxFlySpeed = 0x2f0; //����
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

namespace ȫ��׃��
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