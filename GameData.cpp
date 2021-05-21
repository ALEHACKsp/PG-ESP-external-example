
#include "Utils.h"
namespace hook
{

	ULONG64 钩子地址 = 0x73bf2e;
	ULONG64 跳转地址 = 0x61fa400;


	//特征:48 8B CF 44 0F 28 E0 E8--上下後座
	//特征: E8 ?? ?? ?? ?? 44 0F 28 ?? EB 0D--左右後座
	//特徵: 8B 81 ?? ?? ?? ?? 89 02 8B 81 ?? ?? ?? ?? 89 42 04 8B 81 ?? ?? ?? ?? 89 42 08 48 8B C2 C3 CC CC--開鏡無後
	//特征: F3 0F 10 96 ?? ?? ?? ?? 44 0F 28 ?? F3--上下屏息
	//特征: F3 0F 10 96 ?? ?? ?? ?? 0F 28 C2--左右屏息------往上找3個(不包含+960這一行)

	//特征: E8 ?? ?? ?? ?? F3 0F 10 40 1C F3 41--瞬間擊中
	ULONG64 上下無後座 = 0x1200108;//1
	ULONG64 左右無後座 = 0x40D7AB;//1
	ULONG64 開鏡無後座 = 0x78AB62;//1

	ULONG64 開鏡無後座2 = 0x78AB70;//1
	ULONG64 上下屏息 = 0x444792;//1
	ULONG64 左右屏息 = 0x4447DE;//1
	ULONG64 瞬間擊中 = 0x12001B4;//1

};
//Nuanf基指查找.e


namespace offset
{

	ULONGLONG GNames = 0x4370fa0;//10x436D060  437 0FA0‬
	ULONGLONG CHUNKSIZE = 0x4044;//1
	ULONGLONG UWorld = 0x436D978;//1   48 89 5C 24？48 89 74 24？57 48 81 EC？？？？41 0F B6 F9 
	//SeamlessTravel FlushLevelStreaming往上找有 現在改用GWorld  
	//Gworld特徵
	/*
	  qword_7FF606517258 = 4383235833407331596i64;  <<這個
	v183 = *(_QWORD *)(v1 + 152);
	for ( k = 0; ; ++k )
	{
	  v185 = k < 0 || k >= *(_DWORD *)(v183 + 1000) ? 0 : 1;
	  if ( !v185 )
		break;
		 v186 = *(_QWORD *)(*(_QWORD *)(v183 + 992) + 8i64 * k);
	  if ( v186 )
	   {
	   ....
	   }
	 }
	*/

	ULONGLONG persistentLevel = 0x510;//1
	ULONGLONG GameInstance = 0xB68;//1
	ULONGLONG LocalPlayerArray = 0x30;//1
	ULONGLONG playerController = 0x30;//1
	ULONGLONG PlayerCameraManager = 0x460;//1
	ULONGLONG acknowledgedPawn = 0x440;//1
};


namespace cameraManager
{

	ULONGLONG FOV = 0x14d8;//1
	ULONGLONG Rotator = 0x14Ec;//1
	ULONGLONG Location = 0x14fc;//1
}


namespace actor
{
	ULONGLONG actorList = 0xE0;//1
	ULONGLONG ID = 0x1C;//1

	ULONGLONG SpectedCount = 0x0;//用步道
	ULONGLONG PlayerState = 0x3c8;//
	ULONGLONG PlayerName = 0x7E0; //找步道,但uc有提供
	ULONGLONG KillNum = 0x4a4;//找步道

	// F3 0F 10 87 ? ? ? ? 0F 2F F0 76 0F
	ULONGLONG health = 0x1b2c;//找步道,但uc有提供
	ULONGLONG GroggyHealth = 0x0ef8;// 0x0ef8 0x40a//

	ULONGLONG team = 0x818; //找步道 uc//0xfa8 + 0x8;// 判斷team + 0x8 = teamid 以增加  0x5c8

	ULONGLONG characterMovementComponent = 0x410;

	ULONGLONG ComponentToWorld = 0x1C0;//(+0x4E4) E8 ? ? ? ? 48 8B 05 ? ? ? ? 48 8B 7C 24 ? F3 0F 10 00 
	ULONGLONG RootComponent = 0x298;//1
	ULONGLONG _Pos = 0x1D0;//1  0x3f8,0x300 maybe
	ULONGLONG mesh = 0x488;//maybe or 0x488
	ULONGLONG BoneArray = 0x6e8;//0x6f0

	ULONGLONG bRecentlyRendered = 0x764;
	ULONGLONG WorldSecondTime = 0x3b0;


	ULONGLONG ComponentVelocity = 0x108;//1,uc ComponentVelocity  0x1E5C 0x108
	ULONGLONG VehicleRiderComponent = 0x1630;// VehicleRiderComponent
	ULONGLONG LastVehiclePawn = 0x230;// LastVehiclePawn
	ULONGLONG VehicleVelocity = 0x88;//123 Velocity  ----2個字通常第3個  0x78  0x88  0x108
	ULONGLONG seatIndex = 0x1F8;// seatIndex 通常倒數第3個  0x1xx   0E4  5CC 0E0 1E8 3B8

	//aim
	ULONGLONG ControlRotation_CP = 0x680;//ControlRotation_CP
	ULONGLONG animscriptinstance = 0x0BB8;//animscriptinstance
}


namespace aDroppedItemGroup
{
	ULONGLONG relative = 0x2a8;//    f3 0f 10 ? ? ? ? ? ? ? ? 8b ? ? 78 ? ? ? ? 0f ? 45

//	ULONGLONG ItemName = 0x40;//1 28  48 40 
	ULONGLONG DroppedItemGroupArray = 0x330;// 
	ULONGLONG DroppedItemGroupCount = DroppedItemGroupArray + 0x8;//
	ULONGLONG UItem = 0x610;//   0F B6 F8 48 85 D2 74 13 4C 8B CE 4C 8B C5 49 8B CE ?? ?? ?? ?? ?? ?? 地址-7
	//ULONGLONG UItemFString = 0x28;//1 40  20 0x28

	ULONGLONG packageItems = 0x518;//   33 DB 66 90 85 DB 78 30 地址+8 完後下面那一個 比較小的
	ULONGLONG packageItemscount = packageItems + 0x8;//
}

namespace localPlayerAddr
{
	ULONGLONG WeaponProcessor = 0xe08;//1,uc WeaponProcessor
	// 取玩家视角 有分2个Rotation  "这个是能改的 PlayerControl+ControlRotaion" 另外一个是PlayerControl+PlayerCameraManger+Roator 不能改的
	ULONGLONG ControlRotation = 0x438;
};

namespace WeaponProcessor
{
	ULONGLONG EquippedWeapons = 0x450;// EquippedWeapons 
	ULONGLONG CurrentWeaponIndex = 0x2c1;// CurrentWeaponIndex   記得判斷怎拿的 
	//0F 84 ? ? ? ? F6 45 60 01 
	//      // (+0x185) E8 ? ? ? ? E9 ? ? ? ? C6 87 ? ? ? ? ? 最有可能
	//這個亙有可能 41 0F B6 8E ? ? ? ? FE C9  超級
	//44 0F B6 8B ? ? ? ? 8B D7 這個比上面夠有可能
} 

namespace EquippedWeapons
{
	ULONGLONG FWeaponData = 0x588;// WeaponConfig;用不到
	ULONGLONG FWeaponGunData = 0x8b8;// WeaponGunConfig;用不到
	ULONGLONG FWeaponGunAnim = 0x0b40;//1 WeaponGunAnim;找不到-用不到
	ULONGLONG FWeaponDeviationData = 0x0f0;//1 WeaponDeviationConfig;找不到-用不到
	ULONGLONG FRecoilInfo = 0x0ef0;//1 RecoilInfo;找不到-用不到
	ULONGLONG WeaponDeviationConfig = 0x0b38;//1 WeaponDeviationConfig;找不到-用不到

	ULONGLONG FTrajectoryWeaponData = 0x0d28;// TrajectoryConfig;----------------0x0b0 0x0c38
	ULONGLONG InitialSpeed = 0x574;// InitialSpeed;---------------
	ULONGLONG TrajectorygravityZ = 0x0d94;// ---------------TrajectorygravityZ 
}


namespace characterMovementComponent
{


	ULONGLONG StanceMode = 0x4f0;//人物模式

	ULONGLONG NOWALL = 0x30;// CollisionMesh   CollisionData 0x98   0x2D0 0x1838

	ULONGLONG MaxProneSpeed = 0x998; // 爬行
	ULONGLONG MaxGroggySpeed = 0x9a0;//  打倒
	ULONGLONG MaxWalkSpeed = 0x2e4; // 慢走第一個通常
	ULONGLONG MaxWalkSpeedCrouched = 0x2e8; // 蹲着
	ULONGLONG MaxSwimSpeed = 0x2ec; // 游泳(测试不能)
	ULONGLONG MaxCustomMovementSpeed = 0x2f4; // 最大自定义移动速度

	ULONGLONG MaxAcceleration = 0x2f8;  // 0x2f8 0x278; //移动加速度
	ULONGLONG MaxSwimAcceleration = 0x0bac;// 自由式
	ULONGLONG JumpMaxCount = 0x490;//  连跳
	ULONGLONG JumpZVelocity = 0x29c;// 跳高
		//DWORD MaxFlySpeed = 0x2f0; //飞行
		//DWORD CurrentTimeDuration = 0x164;
		//int bActorEnableCollision_Offset = 0xB4;
}



