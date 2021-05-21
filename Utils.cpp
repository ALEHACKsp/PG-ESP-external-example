#include <iostream>
#include "Utils.h"
#include "crappy.cpp"
#include "decrypt.hpp"
//defining data
int s_width = 1920;
int s_height = 1080;
LPDIRECT3D9 d3d;
LPDIRECT3DDEVICE9 d3ddev;
HWND hWnd;
HWND 遊戲窗口句炳;
MARGINS  margin = { 0, 0, s_width, s_height };
LPD3DXFONT pFont;
ID3DXLine* d3dLine;

list<int> upper_part = { Bones::neck_01, Bones::Head, Bones::forehead };
list<int> right_arm = { Bones::neck_01, Bones::upperarm_r, Bones::lowerarm_r, Bones::hand_r };
list<int> left_arm = { Bones::neck_01, Bones::upperarm_l, Bones::lowerarm_l, Bones::hand_l };
list<int> spine = { Bones::neck_01, Bones::spine_02, Bones::spine_01, Bones::pelvis };

list<int> lower_right = { Bones::pelvis, Bones::thigh_r, Bones::calf_r, Bones::foot_r };
list<int> lower_left = { Bones::pelvis, Bones::thigh_l, Bones::calf_l, Bones::foot_l };

list<list<int>> skeleton = { upper_part, right_arm, left_arm, spine, lower_right, lower_left };
#define Pi 3.1415926535
int Actorids[1];
int boy[2];
int girl[2];
int 物品[2];
int 吉普[3];
int 轎車[4];
int 摩托[8];
int 越野[10];
int 巴士[5];
int 皮卡[12];
int 大船[2];
int 遊艇[4];
int 跑車[12];
int 羅尼[5];
int 嘟嘟車[5];
int 迷你摩托[6];
int 飛機[7];
int 空投[1];
int 超級空投[1];
int 防彈車[3];
int Grenade[1];
int Molotov[1];
int 骨灰盒;



D3DXMATRIX Matrix(Vector3 rot, Vector3 origin = Vector3(0, 0, 0))
{
	float radPitch = (rot.x * float(浮點精度) / 180.f);
	float radYaw = (rot.y * float(浮點精度) / 180.f);
	float radRoll = (rot.z * float(浮點精度) / 180.f);

	float SP = sinf(radPitch);
	float CP = cosf(radPitch);
	float SY = sinf(radYaw);
	float CY = cosf(radYaw);
	float SR = sinf(radRoll);
	float CR = cosf(radRoll);

	D3DMATRIX matrix;
	matrix.m[0][0] = CP * CY;
	matrix.m[0][1] = CP * SY;
	matrix.m[0][2] = SP;
	matrix.m[0][3] = 0.f;

	matrix.m[1][0] = SR * SP * CY - CR * SY;
	matrix.m[1][1] = SR * SP * SY + CR * CY;
	matrix.m[1][2] = -SR * CP;
	matrix.m[1][3] = 0.f;

	matrix.m[2][0] = -(CR * SP * CY + SR * SY);
	matrix.m[2][1] = CY * SR - CR * SP * SY;
	matrix.m[2][2] = CR * CP;
	matrix.m[2][3] = 0.f;

	matrix.m[3][0] = origin.x;
	matrix.m[3][1] = origin.y;
	matrix.m[3][2] = origin.z;
	matrix.m[3][3] = 1.f;

	return matrix;
}
Vector3 SubD3DXVECTOR3(Vector3 VecA, Vector3 VecB)
{
	Vector3 M;
	M.x = VecA.x - VecB.x;
	M.y = VecA.y - VecB.y;
	M.z = VecA.z - VecB.z;
	return M;
}
VOID GetAxes(Vector3 Rotation, Vector3* X, Vector3* Y, Vector3* Z)
{
	float SP = 0, CP = 0, SY = 0, CY = 0, SR = 0, CR = 0;

	SP = sin(Rotation.x * Pi / 180);
	CP = cos(Rotation.x * Pi / 180);
	SY = sin(Rotation.y * Pi / 180);
	CY = cos(Rotation.y * Pi / 180);
	SR = sin(Rotation.z * Pi / 180);
	CR = cos(Rotation.z * Pi / 180);

	X->x = CP * CY;
	X->y = CP * SY;
	X->z = SP;

	Y->x = SR * SP * CY - CR * SY;
	Y->y = SR * SP * SY + CR * CY;
	Y->z = -SR * CP;

	Z->x = -(CR * SP * CY + SR * SY);
	Z->y = CY * SR - CR * SP * SY;
	Z->z = CR * CP;

}
float DotProduct(Vector3 VecA, Vector3 VecB)
{
	return VecA.x * VecB.x + VecA.y * VecB.y + VecA.z * VecB.z;
}
Vector3 WorldToScreen2(Vector3 WorldLocation,Vector3 Rotators) {
	RECT rc;

	Vector3 Screenlocation = Vector3(0, 0, 0);
	ULONG64 Camera_Cache = 全局變量::PlayerCameraManager;

	Vector3 AxisX, AxisY, AxisZ, Delta, Transformed, Location, Rotator;
	float FovAngle = 0;

	Location = driver->RPM<Vector3>(Camera_Cache + cameraManager::Location);
	Rotator = Rotators;
	FovAngle = driver->RPM<float>(Camera_Cache + cameraManager::FOV);

	Delta = SubD3DXVECTOR3(WorldLocation, Location);
	GetAxes(Rotator, &AxisX, &AxisY, &AxisZ);
	Transformed.x = DotProduct(Delta, AxisY);
	Transformed.y = DotProduct(Delta, AxisZ);
	Transformed.z = DotProduct(Delta, AxisX);

	if (Transformed.z < 1.00f)
	{
		Transformed.z = 1.0f;

	}
	//float ScreenCenterX = (1920 / 2);
	//	float ScreenCenterY = (1080 / 2);
	//Screenlocation.x = ScreenCenterX + Transformed.x * ScreenCenterX / tanf(FovAngle * Pi / 360.0f) / Transformed.z;
	//Screenlocation.y = ScreenCenterY - Transformed.y * ScreenCenterX / tanf(FovAngle * Pi / 360.0f) / Transformed.z;

	if (Transformed.z / 100 > 0)
	{

		float ScreenCenterX = 1920 / 2;//(1920 / 2);
		float ScreenCenterY = 1080 / 2;//(1080/ 2);

		Screenlocation.x = ScreenCenterX + Transformed.x * ScreenCenterX / tanf(FovAngle * Pi / 360.0f) / Transformed.z;
		Screenlocation.y = ScreenCenterY - Transformed.y * ScreenCenterX / tanf(FovAngle * Pi / 360.0f) / Transformed.z;
		//if (Screenlocation.x < 1920 && Screenlocation.x > 0)
		//	{
		//	if (Screenlocation.y < 1080 && Screenlocation.y > 0)
		//	{
		//	cout << "绘制成功" << endl;
		//}
		//}


	}



	return Screenlocation;
}
Vector3 WorldToScreen(Vector3 WorldLocation) {
	RECT rc;

	Vector3 Screenlocation = Vector3(0, 0, 0);
	ULONG64 Camera_Cache = 全局變量::PlayerCameraManager;
	Vector3 AxisX, AxisY, AxisZ, Delta, Transformed, Location, Rotator;
	float FovAngle = 0;

	Location = driver->RPM<Vector3>(Camera_Cache + cameraManager::Location);
	Rotator = driver->RPM<Vector3>(Camera_Cache + cameraManager::Rotator);
	FovAngle = driver->RPM<float>(Camera_Cache + cameraManager::FOV);

	Delta = SubD3DXVECTOR3(WorldLocation, Location);
	GetAxes(Rotator, &AxisX, &AxisY, &AxisZ);
	Transformed.x = DotProduct(Delta, AxisY);
	Transformed.y = DotProduct(Delta, AxisZ);
	Transformed.z = DotProduct(Delta, AxisX);

	if (Transformed.z < 1.00f)
	{
		Transformed.z = 1.0f;

	}
	//float ScreenCenterX = (1920 / 2);
	//	float ScreenCenterY = (1080 / 2);
	//Screenlocation.x = ScreenCenterX + Transformed.x * ScreenCenterX / tanf(FovAngle * Pi / 360.0f) / Transformed.z;
	//Screenlocation.y = ScreenCenterY - Transformed.y * ScreenCenterX / tanf(FovAngle * Pi / 360.0f) / Transformed.z;

	if (Transformed.z / 100 > 0)
	{

		float ScreenCenterX = 1920 / 2;//(1920 / 2);
		float ScreenCenterY = 1080 / 2;//(1080/ 2);

		Screenlocation.x = ScreenCenterX + Transformed.x * ScreenCenterX / tanf(FovAngle * Pi / 360.0f) / Transformed.z;
		Screenlocation.y = ScreenCenterY - Transformed.y * ScreenCenterX / tanf(FovAngle * Pi / 360.0f) / Transformed.z;
		//if (Screenlocation.x < 1920 && Screenlocation.x > 0)
		//	{
		//	if (Screenlocation.y < 1080 && Screenlocation.y > 0)
		//	{
		//	cout << "绘制成功" << endl;
		//}
		//}


	}



	return Screenlocation;
}


Vector3 GetLocalPlayerPos()
{
	Vector3 實體座標數據;
	if (!driver)
		return 實體座標數據;
	auto rootcomp = DecryptGeneral(driver->RPM<ULONG64>(全局變量::pPawn + actor::RootComponent));

	實體座標數據 = driver->RPM<Vector3>(rootcomp + actor::_Pos);

	return 實體座標數據;
}

Vector3 取實體座標數據(ULONG64 實體)
{
	Vector3 實體座標數據;
	if (!driver)
		return 實體座標數據;

	auto rootcomp = DecryptGeneral(driver->RPM<ULONG64>(實體 + actor::RootComponent));

	實體座標數據 = driver->RPM<Vector3>(rootcomp + actor::_Pos);


	return 實體座標數據;
}

float GetLocalPlayerHealth()
{
	if (!driver)
		return 0.f;
	auto pawn = 全局變量::pPawn;
	return driver->RPM<float>(pawn + actor::health);
}

float 取實體血量(ULONG64 pAActor)
{
	if (!driver)
		return 1.f;

	return driver->RPM<float>(pAActor + actor::health);

}

float GetActorGroggyHealth(ULONG64 pAActor)
{
	if (!driver)
		return 0.f;
	return driver->RPM<float>(pAActor + actor::GroggyHealth);
}
std::string GetNameFromID(ULONG64 GN1, int ID)
{
	ULONG64 GN = GN1;

	ULONG64  fNamePtr = driver->RPM<ULONG64>(GN + int(ID / offset::CHUNKSIZE) * 8);
	ULONG64  fName = driver->RPM<ULONG64>(fNamePtr + 8 * int(ID % offset::CHUNKSIZE));
	char* name;
	if ((name = (char*)driver->readSize(fName + 0x10, 100)) != NULL)
	{
	  
		std::string string = std::string(name);

		//cout << string << endl;

		
		delete name;
		return string;
	}
}


ULONG64 FindGnames() {

	
	ULONG64 tmp = driver->RPM<ULONG64>(全局變量::pGameBase + offset::GNames);
	ULONG64 gnames = 0;
	for (int i = 0; i < 0xFFFFF; i++)
	{
		gnames = tmp - i * 0x10;
		if (GetNameFromID(gnames, 1) == "ByteProperty" && GetNameFromID(gnames, 2) == "IntProperty" && GetNameFromID(gnames, 3) == "BoolProperty")
		{
			cout << "ByteProperty"<<"||"<< i << endl;
			
			return gnames;
			break;
		}
		
	}
	


	//return  driver->RPM<ULONG64>(全局變量::pGameBase + offset::GNames);
}



BOOL CacheNames()
{
	string name = { NULL };
	全局變量::pGn = FindGnames();
	std::ofstream mycout("C:\\names.txt");//driver->RPM<ULONG64>


	for (int i = 0, c1 = 0, c2 = 0, c3 = 0, c4 = 0, c5 = 0, c6 = 0, c7 = 0, c8 = 0, c9 = 0, c10 = 0, c11 = 0, c12 = 0, c13 = 0, c14 = 0, c15 = 0, c17 = 0,c18 = 0,c19 = 0,c20 = 0,c21 = 0; i < 200000; i++)
	{
		mycout << i << "||" << GetNameFromID(全局變量::pGn,i) << std::endl;
		if (c1 == 1 && c2 == 3 && c3 == 4 && c4 == 8 && c5 == 10 && c6 == 2 && c7 == 12 && c8 == 5 && c9 == 2 && c10 == 4 && c11 == 12 && c12 == 5 && c13 == 5 && c14 == 6 && c15 == 7 && c17 == 1 && c18==1 &&c19==3 && c20 == 1 && c21 == 1 && 骨灰盒 != 0)
		{
			//	mycout.close();
			cout << "成功緩存所有實體名稱" << endl;
			return true;
		}
	
		name = GetNameFromID(全局變量::pGn, i);

		

		//玩家
		if (name == VMProtectDecryptStringA("BP_PlayerPawnPC_C"))
		{
			
			Actorids[c1++] = i;
		}
		//吉普
		if (name == VMProtectDecryptStringA("Uaz_A_01_C") || name == VMProtectDecryptStringA("Uaz_B_01_C") || name == VMProtectDecryptStringA("Uaz_C_01_C"))
		{
			//	cout << name << " " << i << endl;
			吉普[c2++] = i;
		}
		//轎車
		if (name == VMProtectDecryptStringA("Dacia_A_01_v2_C") || name == VMProtectDecryptStringA("Dacia_A_02_v2_C") || name == VMProtectDecryptStringA("Dacia_A_03_v2_C") || name == VMProtectDecryptStringA("Dacia_A_04_v2_C"))
		{
			//	cout << name << " " << i << endl;
			轎車[c3++] = i;
		}
		//摩托車
		if (name == VMProtectDecryptStringA("ABP_Motorbike_03_C") || name == VMProtectDecryptStringA("ABP_Motorbike_04_C") || name == VMProtectDecryptStringA("ABP_Motorbike_04_Sidecar_C")		|| name == VMProtectDecryptStringA("BP_Motorbike_03_C") || name == VMProtectDecryptStringA("BP_Motorbike_04_C") || name == VMProtectDecryptStringA("BP_Motorbike_04_Desert_C")	|| name == VMProtectDecryptStringA("BP_Motorbike_04_SideCar_C") || name == VMProtectDecryptStringA("BP_Motorbike_04_SideCar_Desert_C"))
		{
			//	cout << name << " " << i << endl;
			摩托[c4++] = i;
		}
		//越野
		if (name == VMProtectDecryptStringA("Buggy_A_01_C") || name == VMProtectDecryptStringA("Buggy_A_02_C") || name == VMProtectDecryptStringA("Buggy_A_03_C")|| name == VMProtectDecryptStringA("Buggy_A_04_C") || name == VMProtectDecryptStringA("Buggy_A_05_C") || name == VMProtectDecryptStringA("Buggy_A_06_C")|| name == VMProtectDecryptStringA("Buggy_A_Burned_C") || name == VMProtectDecryptStringA("Buggy_C") || name == VMProtectDecryptStringA("ABP_Buggy_02") || name == VMProtectDecryptStringA("ABP_Buggy_02_C"))
		{
			//cout << name << " " << i << endl;
			越野[c5++] = i;
		}
		//物品
		if (name == VMProtectDecryptStringA("DroppedItemInteractionComponent") || name == VMProtectDecryptStringA("DroppedItemGroup"))
		{
			//cout << name << " " << i << endl;
			物品[c6++] = i;
		}
		//皮卡
		if (name == VMProtectDecryptStringA("BP_PickupTruck_A_C") || name == VMProtectDecryptStringA("BP_PickupTruck_A_01_C") || name == VMProtectDecryptStringA("BP_PickupTruck_A_02_C")|| name == VMProtectDecryptStringA("BP_PickupTruck_A_03_C") || name == VMProtectDecryptStringA("BP_PickupTruck_A_04_C") || name == VMProtectDecryptStringA("BP_PickupTruck_A_05_C")|| name == VMProtectDecryptStringA("BP_PickupTruck_B_C") || name == VMProtectDecryptStringA("BP_PickupTruck_B_01_C") || name == VMProtectDecryptStringA("BP_PickupTruck_B_02_C")|| name == VMProtectDecryptStringA("BP_PickupTruck_B_03_C") || name == VMProtectDecryptStringA("BP_PickupTruck_B_04_C") || name == VMProtectDecryptStringA("BP_PickupTruck_B_05_C"))
		{
			//cout << name << " " << i << endl;
			皮卡[c7++] = i;
		}
		//巴士
		if (name == VMProtectDecryptStringA("ABP_Minibus_02_C") || name == VMProtectDecryptStringA("BP_MiniBus_C") || name == VMProtectDecryptStringA("BP_Van_A_01_C")	|| name == VMProtectDecryptStringA("BP_Van_A_02_C") || name == VMProtectDecryptStringA("BP_Van_A_03_C"))
		{
			//cout << name << " " << i << endl;
			巴士[c8++] = i;
		}
		//大船
		if (name == VMProtectDecryptStringA("Boat_PG117_C") || name == VMProtectDecryptStringA("Boat_PG117_Animation_C"))
		{
			//cout << "找到大船(更新)"<< name << " " << i << endl;
			大船[c9++] = i;
		}
		//遊艇
		if (name == VMProtectDecryptStringA("AquaRail_C") || name == VMProtectDecryptStringA("AquaRail_A_01_C") || name == VMProtectDecryptStringA("AquaRail_A_02_C") || name == VMProtectDecryptStringA("AquaRail_A_03_C"))
		{
			//cout << "找到遊艇(更新)" << name << " " << i << endl;
			遊艇[c10++] = i;
		}
		//跑車
		if (name == VMProtectDecryptStringA("ABP_Mirado_C") || name == VMProtectDecryptStringA("BP_Mirado_C") || name == VMProtectDecryptStringA("BP_Mirado_A_01_C")|| name == VMProtectDecryptStringA("BP_Mirado_A_02_C") || name == VMProtectDecryptStringA("BP_Mirado_A_03_C") || name == VMProtectDecryptStringA("BP_Mirado_A_03_Esports_C")|| name == VMProtectDecryptStringA("BP_Mirado_Open_C") || name == VMProtectDecryptStringA("BP_Mirado_Open_01_C") || name == VMProtectDecryptStringA("BP_Mirado_Open_02_C")|| name == VMProtectDecryptStringA("BP_Mirado_Open_03_C") || name == VMProtectDecryptStringA("BP_Mirado_Open_04_C") || name == VMProtectDecryptStringA("BP_Mirado_A_04_C"))
		{
			//cout << name << " " << i << endl;
			跑車[c11++] = i;
		}
		//羅尼
		if (name == VMProtectDecryptStringA("ABP_Rony_C") || name == VMProtectDecryptStringA("BP_M_Rony_A_01_C") || name == VMProtectDecryptStringA("BP_Rony_C")|| name == VMProtectDecryptStringA("BP_M_Rony_A_02_C") || name == VMProtectDecryptStringA("BP_M_Rony_A_03_C"))
		{
			//cout << "羅尼 " << name << " " << i << endl;
			羅尼[c12++] = i;
		}
		//嘟嘟車
		if (name == VMProtectDecryptStringA("ABP_TukTuk_C") || name == VMProtectDecryptStringA("BP_TukTukTuk_C") || name == VMProtectDecryptStringA("BP_TukTukTuk_A_01_C")		|| name == VMProtectDecryptStringA("BP_TukTukTuk_A_02_C") || name == VMProtectDecryptStringA("BP_TukTukTuk_A_03_C"))
		{
			//cout<<"嘟嘟車 " << name << " " << i << endl;
			嘟嘟車[c13++] = i;
		}
		//迷你摩托
		if (name == VMProtectDecryptStringA("ABP_Scooter_C") || name == VMProtectDecryptStringA("BP_Scooter_C") || name == VMProtectDecryptStringA("BP_Scooter_01_A_C")|| name == VMProtectDecryptStringA("BP_Scooter_02_A_C") || name == VMProtectDecryptStringA("BP_Scooter_03_A_C") || name == VMProtectDecryptStringA("BP_Scooter_04_A_C"))
        {
			//cout << "迷你摩托 " << name << " " << i << endl;
			迷你摩托[c14++] = i;
		}
		//飛機
		//121414：AircraftCarePackage_Test_ChildLowSound_C  TransportAircraft_Seat_C
		if (name == VMProtectDecryptStringA("AircraftCarePackage_Test_C") || name == VMProtectDecryptStringA("TransportAircraft_Seat_C") || name == VMProtectDecryptStringA("DummyTransportAircraft_C")
			|| name == VMProtectDecryptStringA("AircraftCarePackage_Desert_C") | name == VMProtectDecryptStringA("AircraftCarePackage_Test_ChildLowSound_C")
			|| name == VMProtectDecryptStringA("AircraftCarePackage_FlareGun_C") || name == VMProtectDecryptStringA("AircraftCarePackage_Vehicle_C")) {

			//cout << "飛機 " << name << " " << i << endl;
			飛機[c15++] = i;
		}
		//空投
		if (name == VMProtectDecryptStringA("Carapackage_RedBox_C")) {
			空投[c17++] = i;
		}
		//超級空投
		if (name == VMProtectDecryptStringA("Carapackage_FlareGun_C")) {

			超級空投[c18++] = i;
		}
		//防彈車
		if (name == VMProtectDecryptStringA("BP_VehicleDrop_C") || name == VMProtectDecryptStringA("BP_VehicleDrop_UAZ_C") || name == VMProtectDecryptStringA("Uaz_Armored_C") ) {

			防彈車[c19++] = i;
		}
		//手雷
		if (name == VMProtectDecryptStringA("ProjGrenade_C")) {//Weapon_Grenade_C 是所有的  ProjGrenade_C是丟出去的
			//cout << name << " " << i << endl;
			Grenade[c20++] = i;
		}
		//燃燒瓶
		if (name == VMProtectDecryptStringA("ProjMolotov_C")) { //Weapon_Molotov_C 是在所有的 ProjMolotov_C是丟出去的
			//cout << name << " " << i << endl;
			Molotov[c21++] = i;
		}
		//骨灰盒
		if (name == VMProtectDecryptStringA("DeathDropItemPackage_C")) {
			//cout << name << " " << i << endl;
			骨灰盒 = i;
		}

	}
	mycout.close();
	return false;
}

int 是否吉普(int ID)
{
	for (int i = 0; i < 3; i++)
		if (ID == 吉普[i])
			return 1;
	return 0;
}

int 是否轎車(int ID)
{
	for (int i = 0; i < 4; i++)
		if (ID == 轎車[i])
			return 1;
	return 0;
}

int 是否越野(int ID)
{
	for (int i = 0; i < 10; i++)
		if (ID == 越野[i])
			return 1;
	return 0;
}

int 是否摩托(int ID)
{
	for (int i = 0; i < 8; i++)
		if (ID == 摩托[i])
			return 1;
	return 0;
}
int 是否皮卡(int ID)
{
	for (int i = 0; i < 12; i++)
		if (ID == 皮卡[i])
			return 1;
	return 0;
}

int 是否巴士(int ID)
{
	for (int i = 0; i < 5; i++)
		if (ID == 巴士[i])
			return 1;
	return 0;
}

int 是否空投(int ID)
{
	for (int i = 0; i < 1; i++)
		if (ID == 空投[i])
			return 1;
	return 0;
}
int 是否超級空投(int ID)
{
	for (int i = 0; i < 1; i++)
		if (ID == 超級空投[i])
			return 1;
	return 0;
}

int 是否骨灰盒(int ID)
{
	return ID == 骨灰盒;
}

int 是否大船(int ID)
{
	for (int i = 0; i < 2; i++)
		if (ID == 大船[i])
			return 1;
	return 0;
}

int 是否遊艇(int ID)
{
	for (int i = 0; i < 4; i++)
		if (ID == 遊艇[i])
			return 1;
	return 0;
}
int 是否跑車(int ID)
{
	for (int i = 0; i < 12; i++)
		if (ID == 跑車[i])
			return 1;
	return 0;
}
int 是否羅尼(int ID)
{
	for (int i = 0; i < 5; i++)
		if (ID == 羅尼[i])
			return 1;
	return 0;
}
int 是否嘟嘟車(int ID)
{
	for (int i = 0; i < 5; i++)
		if (ID == 嘟嘟車[i])
			return 1;
	return 0;
}
int 是否迷你摩托(int ID)
{
	for (int i = 0; i < 6; i++)
		if (ID == 迷你摩托[i])
			return 1;
	return 0;
}
int 是否防彈車(int ID)
{
	for (int i = 0; i < 3; i++)
		if (ID == 防彈車[i])
			return 1;
	return 0;
}
int 是否手雷(int ID)
{
	for (int i = 0; i < 1; i++)
		if (ID == Grenade[i])
			return 1;
	return 0;
}
int 是否燃燒瓶(int ID)
{
	for (int i = 0; i < 1; i++)
		if (ID == Molotov[i])
			return 1;
	return 0;
}
int 是否飛機(int ID)
{
	for (int i = 0; i < 7; i++)
		if (ID == 飛機[i])
			return 1;
	return 0;
}
D3DMATRIX MatrixMultiplication(D3DMATRIX pM1, D3DMATRIX pM2)
{
	D3DMATRIX pOut;
	pOut._11 = pM1._11 * pM2._11 + pM1._12 * pM2._21 + pM1._13 * pM2._31 + pM1._14 * pM2._41;
	pOut._12 = pM1._11 * pM2._12 + pM1._12 * pM2._22 + pM1._13 * pM2._32 + pM1._14 * pM2._42;
	pOut._13 = pM1._11 * pM2._13 + pM1._12 * pM2._23 + pM1._13 * pM2._33 + pM1._14 * pM2._43;
	pOut._14 = pM1._11 * pM2._14 + pM1._12 * pM2._24 + pM1._13 * pM2._34 + pM1._14 * pM2._44;
	pOut._21 = pM1._21 * pM2._11 + pM1._22 * pM2._21 + pM1._23 * pM2._31 + pM1._24 * pM2._41;
	pOut._22 = pM1._21 * pM2._12 + pM1._22 * pM2._22 + pM1._23 * pM2._32 + pM1._24 * pM2._42;
	pOut._23 = pM1._21 * pM2._13 + pM1._22 * pM2._23 + pM1._23 * pM2._33 + pM1._24 * pM2._43;
	pOut._24 = pM1._21 * pM2._14 + pM1._22 * pM2._24 + pM1._23 * pM2._34 + pM1._24 * pM2._44;
	pOut._31 = pM1._31 * pM2._11 + pM1._32 * pM2._21 + pM1._33 * pM2._31 + pM1._34 * pM2._41;
	pOut._32 = pM1._31 * pM2._12 + pM1._32 * pM2._22 + pM1._33 * pM2._32 + pM1._34 * pM2._42;
	pOut._33 = pM1._31 * pM2._13 + pM1._32 * pM2._23 + pM1._33 * pM2._33 + pM1._34 * pM2._43;
	pOut._34 = pM1._31 * pM2._14 + pM1._32 * pM2._24 + pM1._33 * pM2._34 + pM1._34 * pM2._44;
	pOut._41 = pM1._41 * pM2._11 + pM1._42 * pM2._21 + pM1._43 * pM2._31 + pM1._44 * pM2._41;
	pOut._42 = pM1._41 * pM2._12 + pM1._42 * pM2._22 + pM1._43 * pM2._32 + pM1._44 * pM2._42;
	pOut._43 = pM1._41 * pM2._13 + pM1._42 * pM2._23 + pM1._43 * pM2._33 + pM1._44 * pM2._43;
	pOut._44 = pM1._41 * pM2._14 + pM1._42 * pM2._24 + pM1._43 * pM2._34 + pM1._44 * pM2._44;

	return pOut;
}

FTransform GetBoneIndex(ULONG64 mesh, int index)
{
	ULONG64 bonearray = driver->RPM<ULONG64>(mesh + actor::BoneArray);

	return driver->RPM<FTransform>(bonearray + (index * 0x30));

}
Vector3 GetBonePos(ULONG64 mesh, int BonePos) {

	return GetBoneWithRotation(mesh, BonePos);
}


Vector3 GetBoneWithRotation(ULONG64 mesh, int ID)
{
	
	FTransform bone = GetBoneIndex(mesh, ID);
	
	FTransform ComponentToWorld = (driver->RPM<FTransform>(mesh + actor::ComponentToWorld));

	D3DMATRIX Matrix;
	Matrix = MatrixMultiplication(bone.ToMatrixWithScale(), ComponentToWorld.ToMatrixWithScale());
	return Vector3(Matrix._41, Matrix._42, Matrix._43);
}/*
enum Bones4 : int
{
	Root = 0,
	Head = 6,
	Neck = 5,

	Spine_2 = 4,
	Spine_1 = 3,
	Spine_0 = 2,
	Pelvis = 1,

	Clavicle_R_0 = 11,
	Clavicle_R_1 = 12,
	Cubit_R = 13,
	Wrist_R = 14,

	Clavicle_L_0 = 32,
	Clavicle_L_1 = 33,
	Cubit_L = 34,
	Wrist_L = 35,

	Leg_R_0 = 53,
	Leg_R_1 = 54,
	Leg_R_2 = 55,

	Leg_L_0 = 57,
	Leg_L_1 = 58,
	Leg_L_2 = 59,
};
*/
/*
void 繪製骨骼(ULONG64 mesh, Color color, int ID) {
	Vector3 neckpos = GetBoneWithRotation(mesh, 6);
	Vector3 neckpos2 = GetBoneWithRotation(mesh, 5);
	render->繪製線條(neckpos.x, neckpos.y, neckpos2.x, neckpos2.y, color, 1);

}
*/
void 繪製骨骼4(ULONG64 mesh, Color color, int ID)
{

	for (int i = 0; i < 250; i++) {
		Vector3 neckpos = WorldToScreen(GetBoneWithRotation(mesh, i));
		//Vector3 pelvispos = GetBoneWithRotation(mesh, Bones::pelvis);
		//render->繪製線條(p1.x, p1.y, c1.x, c1.y, color, 1);
		render->繪製文字(neckpos.x, neckpos.y, color, NULL, "%d", i);
	}
	/*
	Vector3 neckpos = GetBoneWithRotation(mesh, Bones::neck_01);
	Vector3 pelvispos = GetBoneWithRotation(mesh, Bones::pelvis);
	Vector3 previous(0, 0, 0);
	Vector3 current, p1, c1;
	for (auto a : skeleton)
	{
		previous = Vector3(0, 0, 0);
		for (int bone : a)
		{
			current = bone == Bones::neck_01 ? neckpos : (bone == Bones::pelvis ? pelvispos : GetBoneWithRotation(mesh, bone));
			if (previous.x == 0.f)
			{
				previous = current;
				continue;
			}
			p1 = WorldToScreen(previous);
			c1 = WorldToScreen(current);
			render->繪製線條(p1.x, p1.y, c1.x, c1.y, color, 1);

			previous = current;
		}
	}
	*/
	/*
	Vector3 neckpos = GetBoneWithRotation(mesh, Bones::neck_01);
	Vector3 pelvispos = GetBoneWithRotation(mesh, Bones::pelvis);
	Vector3 previous(0, 0, 0);
	Vector3 current, p1, c1;
	for (auto a : skeleton)
	{
		previous = Vector3(0, 0, 0);
		for (int bone : a)
		{
			//bool bMale;
			///if (ID == boy[0] || ID == boy[1])
				//bMale = true;
			//if (ID == girl[0] || ID == girl[1])
				//Male = false;
			 bone > Bones::forehead ? bone += 10 : bone;
			current = bone == Bones::Head ? neckpos : (bone == Bones::pelvis ? pelvispos : GetBoneWithRotation(mesh, bone));

			if (previous.x == 0.f)
			{
				previous = current;
				continue;
			}

			p1 = WorldToScreen(previous);
			c1 = WorldToScreen(current);
			render->繪製線條(p1.x, p1.y, c1.x, c1.y, color,1);


			previous = current;
		}
	}
	*/
}

int GetSeatIndex(ULONG64 addr) {
	ULONG64 pVehicleRiderComponent = (driver->RPM<ULONG64>(addr + actor::VehicleRiderComponent));//VehicleRiderComponent+

	int seatIndex = driver->RPM<int>(pVehicleRiderComponent + actor::seatIndex);//SeatIndex;    
	return seatIndex;
}
//get this
ULONG64 GetVehiclePawn(ULONG64 pActor) {
	ULONG64 pVehicleRiderComponent = (driver->RPM<ULONG64>(pActor + actor::VehicleRiderComponent));//VehicleRiderComponent
	int seatIndex = driver->RPM<int>(pVehicleRiderComponent + actor::seatIndex);//seatIndex 
	if (seatIndex > -1) {
		ULONG64 pVehiclePawn = (driver->RPM<ULONG64>(pVehicleRiderComponent + actor::LastVehiclePawn)); //LastVehiclePawn 
		return pActor;
	}
	return NULL;
}

Vector3 GetPlayerVelocity(ULONG64 pAActor) {

	auto rootcom = DecryptGeneral(driver->RPM<ULONG64>(pAActor + actor::RootComponent)); //RootComponent
	return driver->RPM<Vector3>(rootcom + actor::ComponentVelocity);// ComponentVelocity
	/*
	ULONG64 UVehicleRiderComponent = (driver->RPM <ULONG64>(pAActor + actor::VehicleRiderComponent)); // 0x1280    
	ULONG64 UVehicleRiderComponent_Pawn = (driver->RPM <ULONG64>(UVehicleRiderComponent + actor::LastVehiclePawn)); // 0x0220    
	////*
	bool isLocalPlayerInVehicle = GetSeatIndex(pAActor) > -1; //check if local player in vehicle
	if (isLocalPlayerInVehicle) {
	
		//cout << "isLocalPlayerInVehicle" << endl;
		render->繪製文字(全局.窗口中心點.x, 全局.窗口中心點.y+25, Color{ 255, 0, 255, 0 }, pFont, u8"isLocalPlayerInVehicle");
		auto rootcom = DecryptGeneral(driver->RPM<ULONG64>(GetVehiclePawn(pAActor) + actor::RootComponent)); //m_rootComponent
		return driver->RPM<Vector3>(rootcom + actor::ComponentVelocity);// ComponentVelocity
	} 
	////*
	if (UVehicleRiderComponent_Pawn) {

		render->繪製文字(全局.窗口中心點.x, 全局.窗口中心點.y+35, Color{ 255, 0, 255, 0 }, pFont, u8"Rideing");
		auto rootcom = DecryptGeneral(driver->RPM<ULONG64>(pAActor + actor::RootComponent)); //m_rootComponent
		Vector3 velotity = driver->RPM<Vector3>(UVehicleRiderComponent_Pawn + actor::VehicleVelocity);
		//cout << "ride" << endl;
		return velotity;// Velocity    
	}
	else {
		//cout << "ent" << endl;
		//cout << "No----------UVehicleRiderComponent_Pawn" << endl;
		auto rootcom = DecryptGeneral(driver->RPM<ULONG64>(pAActor + actor::RootComponent)); //RootComponent

		return driver->RPM<Vector3>(rootcom + actor::ComponentVelocity);// ComponentVelocity

	}


	*/


}


void 繪製骨骼(ULONG64 mesh, Color color, int ID)
{


if (mesh <= 0)
{
return;
}

Vector3 Head, Hip, Neck, Leftshoulder, LeftArm, LeftArm2, Rightshoulder, RightArm, RightArm2, Chest, Chest2, Chest3, Chest4, Leftthigh, Leftthigh2, LeftCalf, LeftCalf2, Leftfoot, Rightthigh, Rightthigh2, RightCalf, RightCalf2, Rightfoot;
/*



眼睛11, 12
頭部9
警6
井下13
左肩 14
誘姦35
左必15
又避36

2井下4
3井下3
4井下2

左闢故55
又屁股59
左2屁股56
又2屁股60
左小腿57
右小腿61
左腳58
右腳62
*/
//Head
Head = WorldToScreen(GetBoneWithRotation(mesh, 6));//

//Hip
Hip = WorldToScreen(GetBoneWithRotation(mesh, 13));//

//Neck
Neck = WorldToScreen(GetBoneWithRotation(mesh, 5));//

//Left UpperArm
Leftshoulder = WorldToScreen(GetBoneWithRotation(mesh, 14));
LeftArm = WorldToScreen(GetBoneWithRotation(mesh, 15));
LeftArm2 = WorldToScreen(GetBoneWithRotation(mesh, 20));

//	Rightshoulder = WorldToScreen(GetBoneWithRotation(mesh, 104));
Rightshoulder = WorldToScreen(GetBoneWithRotation(mesh, 35));
RightArm = WorldToScreen(GetBoneWithRotation(mesh, 36));
RightArm2 = WorldToScreen(GetBoneWithRotation(mesh, 40));

Chest = WorldToScreen(GetBoneWithRotation(mesh, 4));//
Chest2 = WorldToScreen(GetBoneWithRotation(mesh, 3));//
Chest3 = WorldToScreen(GetBoneWithRotation(mesh, 2));//
Chest4 = WorldToScreen(GetBoneWithRotation(mesh, 1));//

Leftthigh = WorldToScreen(GetBoneWithRotation(mesh, 55));
Leftthigh2 = WorldToScreen(GetBoneWithRotation(mesh, 56));
LeftCalf = WorldToScreen(GetBoneWithRotation(mesh, 57));


Rightthigh = WorldToScreen(GetBoneWithRotation(mesh, 59));
Rightthigh2 = WorldToScreen(GetBoneWithRotation(mesh, 60));
RightCalf = WorldToScreen(GetBoneWithRotation(mesh, 61));





render->繪製線條(Head.x, Head.y, Neck.x, Neck.y, color,1);
//render->繪製線條(Neck.x, Neck.y, Hip.x, Hip.y, color, 1);

//render->繪製線條(Neck.x, Neck.y, Leftshoulder.x, Leftshoulder.y, color);
//render->繪製線條(Leftshoulder.x, Leftshoulder.y, Leftshoulder2.x, Leftshoulder2.y, color);
render->繪製線條(Neck.x, Neck.y, Leftshoulder.x, Leftshoulder.y, color, 1);

render->繪製線條(Leftshoulder.x, Leftshoulder.y, LeftArm.x, LeftArm.y, color, 1);
render->繪製線條(LeftArm.x, LeftArm.y, LeftArm2.x, LeftArm2.y, color, 1);



render->繪製線條(Neck.x, Neck.y, Rightshoulder.x, Rightshoulder.y, color, 1);


render->繪製線條(Rightshoulder.x, Rightshoulder.y, RightArm.x, RightArm.y, color, 1);
render->繪製線條(RightArm.x, RightArm.y, RightArm2.x, RightArm2.y, color, 1);

render->繪製線條(Neck.x, Neck.y, Chest.x, Chest.y, color, 1);
render->繪製線條(Chest.x, Chest.y, Chest2.x, Chest2.y, color, 1);
render->繪製線條(Chest2.x, Chest2.y, Chest3.x, Chest3.y, color, 1);
render->繪製線條(Chest3.x, Chest3.y, Chest4.x, Chest4.y, color, 1);
render->繪製線條(Chest4.x, Chest4.y, Leftthigh.x, Leftthigh.y, color, 1);
render->繪製線條(Leftthigh.x, Leftthigh.y, Leftthigh2.x, Leftthigh2.y, color, 1);
render->繪製線條(Leftthigh2.x, Leftthigh2.y, LeftCalf.x, LeftCalf.y, color, 1);
//render->繪製線條(LeftCalf.x, LeftCalf.y, LeftCalf2.x, LeftCalf2.y, color, 1);
//render->繪製線條(LeftCalf2.x, LeftCalf2.y, Leftfoot.x, Leftfoot.y, color, 1);

render->繪製線條(Chest4.x, Chest4.y, Rightthigh.x, Rightthigh.y, color, 1);
render->繪製線條(Rightthigh.x, Rightthigh.y, Rightthigh2.x, Rightthigh2.y, color, 1);
render->繪製線條(Rightthigh2.x, Rightthigh2.y, RightCalf.x, RightCalf.y, color, 1);
//render->繪製線條(RightCalf.x, RightCalf.y, RightCalf2.x, RightCalf2.y, color, 1);
//render->繪製線條(RightCalf2.x, RightCalf2.y, Rightfoot.x, Rightfoot.y, color, 1);

}



void UpdateAddresses()
{
	if (!driver)
		return;







	全局變量::pUWorld = DecryptWorld(driver->RPM<ULONG64>(全局變量::pGameBase + offset::UWorld));



	全局變量::persistentLevel = DecryptLevel(driver->RPM<ULONG64>(全局變量::pUWorld + offset::persistentLevel));

	全局變量::pGameInstance = DecryptGameInstance(driver->RPM<ULONG64>(全局變量::pUWorld + offset::GameInstance));

	全局變量::pLocalPlayerArray = DecryptLocalPlayer(driver->RPM<ULONG64>(driver->RPM<ULONG64>(全局變量::pGameInstance + offset::LocalPlayerArray)));//+0x0或不用

	全局變量::playerController = DecryptPlayerController(driver->RPM<ULONG64>(全局變量::pLocalPlayerArray + offset::playerController));

	全局變量::PlayerCameraManager = driver->RPM<ULONG64>(全局變量::playerController + offset::PlayerCameraManager);

	//全局變量::pViewportClient = tsl_decrypt_prop(&tsl, 全局變量::pLocalPlayer + offset::ViewportClient);

	//全局變量::pPawn = DecryptGeneral(driver->RPM<ULONG64>(DecryptPlayerController(driver->RPM<ULONG64>(全局變量::pLocalPlayerArray + localPlayerAddr::playerController))) + playerController::acknowledgedPawn);
	全局變量::pPawn = DecryptGeneral(driver->RPM<ULONG64>(全局變量::playerController + offset::acknowledgedPawn));
	//全局變量::cameracache = GetCameraCache();

	/*
	全局變量::pUWorld = driver->RPM<ULONG64>(driver->RPM<ULONG64>(全局變量::pGameBase + offset::UWorld));

	全局變量::persistentLevel = DecryptLevel(driver->RPM<ULONG64>(全局變量::pUWorld + offset::persistentLevel));
	全局變量::pGameInstance = DecryptGameInstance(driver->RPM<ULONG64>(全局變量::pUWorld + offset::GameInstance));

	全局變量::pLocalPlayerArray = DecryptLocalPlayer(driver->RPM<ULONG64>(driver->RPM<ULONG64>(全局變量::pGameInstance + offset::LocalPlayerArray)));//+0x0或不用

	全局變量::playerController = DecryptPlayerController(driver->RPM<ULONG64>(全局變量::pLocalPlayerArray + offset::playerController));

	全局變量::PlayerCameraManager = driver->RPM<ULONG64>(全局變量::playerController + offset::PlayerCameraManager);

	//全局變量::pViewportClient = tsl_decrypt_prop(&tsl, 全局變量::pLocalPlayer + offset::ViewportClient);

	//全局變量::pPawn = DecryptGeneral(driver->RPM<ULONG64>(DecryptPlayerController(driver->RPM<ULONG64>(全局變量::pLocalPlayerArray + localPlayerAddr::playerController))) + playerController::acknowledgedPawn);
	全局變量::pPawn = DecryptGeneral(driver->RPM<ULONG64>(全局變量::playerController + offset::acknowledgedPawn));

	//全局變量::cameracache = GetCameraCache();

	*/
}


void testoffset() {







	

	全局變量::pUWorld = driver->RPM<ULONG64>(driver->RPM<ULONG64>(全局變量::pGameBase + offset::UWorld));
	cout << hex << VMProtectDecryptStringA("\n2次:             0x") << 全局變量::pUWorld << endl;


	全局變量::pUWorld = DecryptWorld(driver->RPM<ULONG64>(driver->RPM<ULONG64>(全局變量::pGameBase + offset::UWorld)));
	cout << hex << VMProtectDecryptStringA("\n2次解密:             0x") << 全局變量::pUWorld << endl;


	全局變量::pUWorld = (driver->RPM<ULONG64>(全局變量::pGameBase + offset::UWorld));
	cout << hex << VMProtectDecryptStringA("\n一次b:             0x") << 全局變量::pUWorld << endl;
	

	全局變量::pUWorld = DecryptWorld(driver->RPM<ULONG64>(全局變量::pGameBase + offset::UWorld));
	cout << hex << VMProtectDecryptStringA("\na一次解密:             0x") << 全局變量::pUWorld << endl;

	全局變量::persistentLevel = DecryptLevel(driver->RPM<ULONG64>(全局變量::pUWorld + offset::persistentLevel));

	全局變量::pGameInstance = DecryptGameInstance(driver->RPM<ULONG64>(全局變量::pUWorld + offset::GameInstance));

	全局變量::pLocalPlayerArray = DecryptLocalPlayer(driver->RPM<ULONG64>(driver->RPM<ULONG64>(全局變量::pGameInstance + offset::LocalPlayerArray)));//+0x0或不用

	全局變量::playerController = DecryptPlayerController(driver->RPM<ULONG64>(全局變量::pLocalPlayerArray + offset::playerController));

	全局變量::PlayerCameraManager = driver->RPM<ULONG64>(全局變量::playerController + offset::PlayerCameraManager);

	//全局變量::pViewportClient = tsl_decrypt_prop(&tsl, 全局變量::pLocalPlayer + offset::ViewportClient);

	//全局變量::pPawn = DecryptGeneral(driver->RPM<ULONG64>(DecryptPlayerController(driver->RPM<ULONG64>(全局變量::pLocalPlayerArray + localPlayerAddr::playerController))) + playerController::acknowledgedPawn);
	全局變量::pPawn = DecryptGeneral(driver->RPM<ULONG64>(全局變量::playerController + offset::acknowledgedPawn));
	//全局變量::cameracache = GetCameraCache();
	ULONG64 GN = DecryptGname(driver->RPM<ULONG64>(全局變量::pGameBase + offset::GNames));

	ULONG64  EncryptEntity = driver->RPM<ULONG64>(DecryptActor(driver->RPM<ULONG64>(全局變量::persistentLevel + actor::actorList)));
	cout << hex << VMProtectDecryptStringA("\nGN:                  0x") << GN << endl;
	cout << hex << VMProtectDecryptStringA("pUWorld:             0x") << 全局變量::pUWorld << endl;
	cout << hex << VMProtectDecryptStringA("persistentLevel:     0x") << 全局變量::persistentLevel << endl;
	cout << hex << VMProtectDecryptStringA("pGameInstance:       0x") << 全局變量::pGameInstance << endl;
	cout << hex << VMProtectDecryptStringA("pLocalPlayer:        0x") << 全局變量::pLocalPlayerArray << endl;
	cout << hex << VMProtectDecryptStringA("playerController:    0x") << 全局變量::playerController << endl;
	cout << hex << VMProtectDecryptStringA("PlayerCameraManager: 0x") << 全局變量::PlayerCameraManager << endl;
	cout << hex << VMProtectDecryptStringA("pViewportClient:     0x") << 全局變量::pViewportClient << endl;
	cout << hex << VMProtectDecryptStringA("pPawn:               0x") << 全局變量::pPawn << endl;
	cout << hex << VMProtectDecryptStringA("EncryptEntity:       0x") << EncryptEntity << endl;
}


Vector3 predict(Vector3 TargetPos, float Distance, Vector3 TargetVelocity, float InitialSpeed, Vector3 grav) {



	int temp;
	Vector3 pred;
	float flytime;
	int drop;
	if (Distance > 10 && Distance < 35) {
		Distance = 35;
		temp = 1.05;
	}

	if (Distance > 35 && Distance < 50) {
		Distance = 50;
		temp = 1.05;
	}
	if (Distance > 50 &&  Distance < 100){
		Distance = 100;//31 ,36 no  34,35 ok   調成1.34   200米內超穩 
		temp = 1.1;
	}
	if (Distance < 200)
		temp = 1.15;
	if (Distance < 300)
		temp = 1.25;
	if (Distance < 400)
		temp = 1.35;
	if (Distance < 500)
		temp = 1.5;
	if (Distance < 600)
		temp = 1.6;
	if (Distance < 700)
		temp = 1.7;
	if (Distance < 800)
		temp = 1.8;
	if (Distance < 900)
		temp = 1.9;
	if (Distance < 1000)
		temp = 2.0;

	
	//flytime = (Distance / InitialSpeed);//*temp;//or just * 1.5 
	flytime = (Distance / InitialSpeed);//*temp;//or just * 1.5   
	//flytime = flytime * temp;

	
	//方法一
	/*
     float speed = sqrt((TargetVelocity.x*TargetVelocity.x) + (TargetVelocity.y * TargetVelocity.y) + (TargetVelocity.z * TargetVelocity.z));//計算朝向速度

      float lead = (speed /10) * flytime;  //計算速度 *flytime = 需要提槍的量     越近越小  越遠越大   5*0.11  6
	  */
	//方法二
	  //pred.x = TargetPos.x + TargetVelocity.x *flytime;

	  //方法二比較準

	  
	
	//pred.x = TargetPos.x + TargetVelocity.x *flytime;//TargetVelocity.x *flytime*temp;//10*5 = 50  10*2=20
	//10   400*5     210               10 10

	pred.x = (TargetPos.x + grav.x)+ TargetVelocity.x *flytime;

	//pred.x = TargetPos.x + grav.x*flytime;
	pred.y = TargetPos.y + TargetVelocity.y *flytime;//(flytime * temp);

   //pred.z = TargetPos.z + 0.5* abs(grav)*flytime*flytime;    //pow(flytime, 2)  *45太高 * 5.0f有時候沒用,暫時先不乘,   https://www.unknowncheats.me/forum/playerunknown-s-battlegrounds/264334-calculating-bullet-drop-1-0-using-vdragcoefficient-gravity-bulletspeed.html
	///pred.z = TargetPos.z + (9.92665f * 100 / 2 * flytime * flytime + flytime * TargetVelocity.z);//這個算出來的值 比上面還高 優先選擇 

	//pred.z = TargetPos.z + 0.5 * 9.92665f * pow(flytime, 2) + (TargetVelocity.z * flytime) + flytime * 200.f;//這個算出來的值 比上面還高 優先選擇 
	pred.z = TargetPos.z + (0.5 * abs(8.8) *flytime*flytime + (TargetVelocity.z * flytime));
   //因為y太高先選擇 pred.z小的試試看

	
	return pred;
}

void drawstyle(Vector3 實體屏幕座標, ULONG64 mesh, Vector3 head, Vector3 Rfoot, int 長, int 中, int 高, int 寬, Color 顏色, int ID) {
	//角框
	if (顯示相關設置::顯示人物風格 == 1)
	{
		render->繪製圓圈(head.x - 中 * 0.2, head.y, Color{ 255, 255, 0, 0 }, 0.5*寬, 24, 1);
		render->繪製方框(head.x - 中 * 0.2, head.y, 0.5*中, 0.5*寬, Color{ 255, 255, 0, 0 });
		
		render->繪製線條(實體屏幕座標.x - 中, head.y, 實體屏幕座標.x - 中 + 高, head.y, 顏色::顏色[顏色::方框顏色參數],1);
		render->繪製線條(實體屏幕座標.x - 中, head.y, 實體屏幕座標.x - 中, head.y + 寬, 顏色::顏色[顏色::方框顏色參數], 1);

		render->繪製線條(實體屏幕座標.x + 中 - 高, head.y, 實體屏幕座標.x + 中, head.y, 顏色::顏色[顏色::方框顏色參數], 1);
		render->繪製線條(實體屏幕座標.x + 中, head.y, 實體屏幕座標.x + 中, head.y + 寬, 顏色::顏色[顏色::方框顏色參數], 1);

		render->繪製線條(實體屏幕座標.x - 中, Rfoot.y, 實體屏幕座標.x - 中 + 高, Rfoot.y, 顏色::顏色[顏色::方框顏色參數], 1);
		render->繪製線條(實體屏幕座標.x - 中, Rfoot.y, 實體屏幕座標.x - 中, Rfoot.y - 寬, 顏色::顏色[顏色::方框顏色參數], 1);

		render->繪製線條(實體屏幕座標.x + 中 - 高, Rfoot.y, 實體屏幕座標.x + 中, Rfoot.y, 顏色::顏色[顏色::方框顏色參數], 1);
		render->繪製線條(實體屏幕座標.x + 中, Rfoot.y, 實體屏幕座標.x + 中, Rfoot.y - 寬, 顏色::顏色[顏色::方框顏色參數], 1);
	}
	//方块
	if (顯示相關設置::顯示人物風格 == 2)
	{


		render->繪製圓圈(head.x - 中 * 0.2, head.y, Color{ 255, 255, 0, 0 }, 0.5*寬, 24, 1);
		render->繪製方框(head.x - 中 * 0.2, head.y, 0.5*中, 0.5*寬, Color{ 255, 255, 0, 0 });


		render->繪製填充矩形(實體屏幕座標.x - 中, head.y, (中 * 2), (寬 * 4), Color{ 100, 105, 105, 105 });
		render->繪製方框(實體屏幕座標.x - 中 + 1, head.y + 1, (中 * 2) + 1, (寬 * 4) + 1, 顏色::顏色[顏色::方框顏色參數]);

	}
	//骨頭
	if (顯示相關設置::顯示人物風格 == 3)
	{
		render->繪製圓圈(head.x - 中 * 0.2, head.y, Color{ 255, 255, 0, 0 }, 0.4*寬, 24, 1);
		//render->繪製方框(head.x - 中 * 0.2, head.y, 0.5*中, 0.5*寬, Color{ 255, 255, 0, 0 });

		//	render->繪製骨骼(mesh, 顏色::顏色[顏色::骨骼顏色參數]);
		繪製骨骼(mesh, 顏色, ID);
	}
	//綜合
	if (顯示相關設置::顯示人物風格 == 4)
	{
		render->繪製圓圈(head.x - 中 * 0.2, head.y, Color{ 255, 255, 0, 0 }, 0.5*寬, 24, 1);
		render->繪製方框(head.x - 中 * 0.2, head.y, 0.5*中, 0.5*寬, Color{ 255, 255, 0, 0 });

		render->繪製填充矩形(實體屏幕座標.x - 中, head.y, (中 * 2), (寬 * 4), Color{ 100, 105 ,105 ,105 });
		render->繪製方框(實體屏幕座標.x - 中 + 1, head.y + 1, (中 * 2) + 1, (寬 * 4) + 1, 顏色::顏色[顏色::方框顏色參數]);

		繪製骨骼(mesh, 顏色, ID);

	}
}

void  過濾盒子物品(std::string name, Vector3 screenloc, int onece) {

	if (name == VMProtectDecryptStringA("Item_Ghillie_01_C") || name == VMProtectDecryptStringA("Item_Ghillie_02_C")) {
		render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::高級物品顏色參數], pFont, VMProtectDecryptStringA(u8"｜ 吉利服"));
		addItemYaw += onece;
		//return u8"｜ 吉利服";
	}
	if (name == VMProtectDecryptStringA("Item_Ammo_762mm_C")) {
		render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::普通物品顏色參數], pFont, VMProtectDecryptStringA(u8"｜ 762子彈"));
		addItemYaw += onece;
		//return u8"｜ 762子彈";
	}
	if (name == VMProtectDecryptStringA("Item_Ammo_556mm_C")) {
		render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::普通物品顏色參數], pFont, VMProtectDecryptStringA(u8"｜ 556子彈"));
		addItemYaw += onece;
		//return u8"｜ 556子彈";
	}
	if (name == VMProtectDecryptStringA("Item_Ammo_Flare_C")) {
		render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::高級物品顏色參數], pFont, VMProtectDecryptStringA(u8"｜ 信號槍子彈"));
		addItemYaw += onece;
		//return u8"｜ 信號槍子彈";
	}
	if (name == VMProtectDecryptStringA("Item_Ammo_300Magnum_C")) {
		render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::高級物品顏色參數], pFont, VMProtectDecryptStringA(u8"｜ AWM子彈"));
		addItemYaw += onece;
		//return u8"｜ AWM子彈";
	}

	if (name == VMProtectDecryptStringA("Item_Boost_EnergyDrink_C")) {

		render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::普通物品顏色參數], pFont, VMProtectDecryptStringA(u8"｜ 能量飲料"));
		addItemYaw += onece;
		//return u8"｜ 能量飲料";
	}
	if (name == VMProtectDecryptStringA("Item_Boost_PainKiller_C")) {
		render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::普通物品顏色參數], pFont, VMProtectDecryptStringA(u8"｜ 止痛藥"));
		addItemYaw += onece;
		//return u8"｜ 止痛藥";
	}
	if (name == VMProtectDecryptStringA("Item_Boost_AdrenalineSyringe_C")) {
		render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::高級物品顏色參數], pFont, VMProtectDecryptStringA(u8"｜ 腎上腺素"));
		addItemYaw += onece;
		//return u8"｜ 腎上腺素";
	}
	if (name == VMProtectDecryptStringA("Item_Heal_Bandage_C")) {
		render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::普通物品顏色參數], pFont, VMProtectDecryptStringA(u8"｜ 繃帶"));
		addItemYaw += onece;
		//return u8"｜ 繃帶";
	}
	if (name == VMProtectDecryptStringA("Item_Heal_FirstAid_C")) {
		render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::普通物品顏色參數], pFont, VMProtectDecryptStringA(u8"｜ 急救包"));
		addItemYaw += onece;
		//return u8"｜ 急救包";
	}
	if (name == VMProtectDecryptStringA("Item_Heal_MedKit_C")) {
		render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::高級物品顏色參數], pFont, VMProtectDecryptStringA(u8"｜ 醫療箱"));
		addItemYaw += onece;
		//return u8"｜ 醫療箱";
	}


	if (name == VMProtectDecryptStringA("Item_Attach_Weapon_Upper_Aimpoint_C")) {
		render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::普通物品顏色參數], pFont, VMProtectDecryptStringA(u8"｜ 2x倍镜"));
		addItemYaw += onece;
		//return u8"｜ 2x倍镜";
	}
	if (name == VMProtectDecryptStringA("Item_Attach_Weapon_Upper_Scope3x_C")) {
		render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::普通物品顏色參數], pFont, VMProtectDecryptStringA(u8"｜ 3x倍镜"));
		addItemYaw += onece;
		//return u8"｜ 3x倍镜";
	}
	if (name == VMProtectDecryptStringA("Item_Attach_Weapon_Upper_ACOG_01_C")) {
		render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::高級物品顏色參數], pFont, VMProtectDecryptStringA(u8"｜ 4x倍镜"));
		addItemYaw += onece;
		//return u8"｜ 4x倍镜";
	}
	if (name == VMProtectDecryptStringA("Item_Attach_Weapon_Upper_Scope6x_C")) {
		render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::高級物品顏色參數], pFont, VMProtectDecryptStringA(u8"｜ 6x倍镜"));
		addItemYaw += onece;
		//return u8"｜ 6x倍镜";
	}
	if (name == VMProtectDecryptStringA("Item_Attach_Weapon_Upper_CQBSS_C")) {
		render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::高級物品顏色參數], pFont, VMProtectDecryptStringA(u8"｜ 8x倍镜"));
		addItemYaw += onece;
		//return u8"｜ 8x倍镜";
	}


	if (name == VMProtectDecryptStringA("Item_Weapon_Grenade_C")) {
		render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::普通物品顏色參數], pFont, VMProtectDecryptStringA(u8"｜ 手榴彈"));
		addItemYaw += onece;
		//return u8"｜ 手榴彈";
	}
	if (name == VMProtectDecryptStringA("Item_Weapon_Molotov_C")) {
		render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::普通物品顏色參數], pFont, VMProtectDecryptStringA(u8"｜ 燃燒瓶"));
		addItemYaw += onece;
		//return u8"｜ 燃燒瓶";
	}
	if (name == VMProtectDecryptStringA("Item_Weapon_FlashBang_C")) {
		render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::普通物品顏色參數], pFont, VMProtectDecryptStringA(u8"｜ 閃光彈"));
		addItemYaw += onece;
		//return u8"｜ 閃光彈";
	}
	if (name == VMProtectDecryptStringA("Item_Weapon_SmokeBomb_C")) {
		render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::普通物品顏色參數], pFont, VMProtectDecryptStringA(u8"｜ 煙霧彈"));
		addItemYaw += onece;
		//return u8"｜ 煙霧彈";
	}
	if (name == VMProtectDecryptStringA("Item_Attach_Weapon_Upper_PM2_01_C")) {
		render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::高級物品顏色參數], pFont, VMProtectDecryptStringA(u8"｜ 15x倍镜"));
		addItemYaw += onece;
		//return u8"｜ 15x倍镜";
	}
	if (name == VMProtectDecryptStringA("Item_Attach_Weapon_Stock_SniperRifle_BulletLoops_C")) {
		render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::普通物品顏色參數], pFont, VMProtectDecryptStringA(u8"｜ 狙擊子彈袋"));
		addItemYaw += onece;
		//return u8"｜ 狙擊子彈袋";
	}
	if (name == VMProtectDecryptStringA("Item_Attach_Weapon_Stock_SniperRifle_CheekPad_C")) {
		render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::普通物品顏色參數], pFont, VMProtectDecryptStringA(u8"｜ 托腮版"));
		addItemYaw += onece;
		//return u8"｜ 托腮版";
	}
	if (name == VMProtectDecryptStringA("Item_Attach_Weapon_Stock_UZI_C")) {
		render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::普通物品顏色參數], pFont, VMProtectDecryptStringA(u8"｜ 烏茲槍托"));
		addItemYaw += onece;
		//return u8"｜ 烏茲槍托";
	}
	if (name == VMProtectDecryptStringA("Item_Attach_Weapon_Stock_AR_Composite_C")) {
		render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::普通物品顏色參數], pFont, VMProtectDecryptStringA(u8"｜ 戰術槍托"));
		addItemYaw += onece;
		//return u8"｜ 戰術槍托";
	}
	if (name == VMProtectDecryptStringA("Item_Attach_Weapon_Lower_AngledForeGrip_C")) {
		render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::普通物品顏色參數], pFont, VMProtectDecryptStringA(u8"｜ 直角握把"));
		addItemYaw += onece;
		//return u8"｜ 直角握把";
	}
	if (name == VMProtectDecryptStringA("Item_Attach_Weapon_Lower_Foregrip_C")) {
		render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::普通物品顏色參數], pFont, VMProtectDecryptStringA(u8"｜ 垂直握把"));
		addItemYaw += onece;
		//return u8"｜ 垂直握把";
	}

	if (name == VMProtectDecryptStringA("Item_Attach_Weapon_Lower_HalfGrip_C")) {
		render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::普通物品顏色參數], pFont, VMProtectDecryptStringA(u8"｜ 半截式握把"));
		addItemYaw += onece;
		//return u8"｜ 半截式握把";
	}
	if (name == VMProtectDecryptStringA("Item_Attach_Weapon_Lower_LightweightForeGrip_C")) {
		render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::普通物品顏色參數], pFont, VMProtectDecryptStringA(u8"｜ 輕型握把"));
		addItemYaw += onece;
		//return u8"｜ 輕型握把";
	}
	if (name == VMProtectDecryptStringA("Item_Attach_Weapon_Lower_ThumbGrip_C")) {
		render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::普通物品顏色參數], pFont, VMProtectDecryptStringA(u8"｜ 拇指握把"));
		addItemYaw += onece;
		//return u8"｜ 拇指握把";
	}
	if (name == VMProtectDecryptStringA("Item_Attach_Weapon_Lower_LaserPointer_C")) {
		render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::普通物品顏色參數], pFont, VMProtectDecryptStringA(u8"｜ 雷射瞄準器"));
		addItemYaw += onece;
		//return u8"｜ 雷射瞄準器";
	}
	if (name == VMProtectDecryptStringA("Item_Attach_Weapon_Upper_Holosight_C")) {
		render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::普通物品顏色參數], pFont, VMProtectDecryptStringA(u8"｜ 全息"));
		addItemYaw += onece;
		//return u8"｜ 全息";
	}
	if (name == VMProtectDecryptStringA("Item_Attach_Weapon_Upper_DotSight_01_C")) {
		render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::普通物品顏色參數], pFont, VMProtectDecryptStringA(u8"｜ 紅點"));
		addItemYaw += onece;
		//return u8"｜ 紅點";
	}
	if (name == VMProtectDecryptStringA("Item_Attach_Weapon_Magazine_ExtendedQuickDraw_Large_C")) {
		render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::高級物品顏色參數], pFont, VMProtectDecryptStringA(u8"｜ 步槍快擴"));
		addItemYaw += onece;
		//return u8"｜ 步槍快擴";
	}
	if (name == VMProtectDecryptStringA("Item_Attach_Weapon_Magazine_ExtendedQuickDraw_SniperRifle_C")) {
		render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::高級物品顏色參數], pFont, VMProtectDecryptStringA(u8"｜ 狙擊快擴"));
		addItemYaw += onece;
		//return u8"｜ 狙擊快擴";
	}

	if (name == VMProtectDecryptStringA("Item_Attach_Weapon_Muzzle_Compensator_Large_C")) {
		render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::高級物品顏色參數], pFont, VMProtectDecryptStringA(u8"｜ 步槍補償"));
		addItemYaw += onece;
		//return u8"｜ 步槍補償";
	}
	if (name == VMProtectDecryptStringA("Item_Attach_Weapon_Muzzle_Compensator_SniperRifle_C")) {
		render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::高級物品顏色參數], pFont, VMProtectDecryptStringA(u8"｜ 狙擊補償"));
		addItemYaw += onece;
		//return u8"｜ 狙擊補償";
	}
	if (name == VMProtectDecryptStringA("Item_Attach_Weapon_Muzzle_Suppressor_Large_C")) {
		render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::高級物品顏色參數], pFont, VMProtectDecryptStringA(u8"｜ 步槍消音"));
		addItemYaw += onece;
		//return u8"｜ 步槍消音";
	}
	if (name == VMProtectDecryptStringA("Item_Attach_Weapon_Muzzle_Suppressor_SniperRifle_C")) {
		render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::高級物品顏色參數], pFont, VMProtectDecryptStringA(u8"｜ 狙擊消音"));
		addItemYaw += onece;
		//return u8"｜ 狙擊消音";
	}

	if (name == VMProtectDecryptStringA("Item_Armor_D_01_Lv2_C") || name == VMProtectDecryptStringA("Item_Armor_D_02_Lv2_C")) {
		render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::普通物品顏色參數], pFont, VMProtectDecryptStringA(u8"｜ 護甲Lv.2"));
		addItemYaw += onece;
		//return u8"｜ 護甲Lv.2";
	}
	if (name == VMProtectDecryptStringA("Item_Armor_C_01_Lv3_C") || name == VMProtectDecryptStringA("Item_Armor_C_02_Lv3_C")) {
		render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::高級物品顏色參數], pFont, VMProtectDecryptStringA(u8"｜ 護甲Lv.3"));
		addItemYaw += onece;
		//return u8"｜ 護甲Lv.3";
	}
	if (name == VMProtectDecryptStringA("Item_Back_F_02_Lv2_C") || name == VMProtectDecryptStringA("Item_Back_F_01_Lv2_C")) {
		render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::普通物品顏色參數], pFont, VMProtectDecryptStringA(u8"｜ 背包Lv.2"));
		addItemYaw += onece;
		//return u8"｜ 背包Lv.2";
	}//
	if (name == VMProtectDecryptStringA("Item_Back_C_02_Lv3_C") || name == VMProtectDecryptStringA("Item_Back_C_01_Lv3_C")) {
		render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::高級物品顏色參數], pFont, VMProtectDecryptStringA(u8"｜ 背包Lv.3"));
		addItemYaw += onece;
		//return u8"｜ 背包Lv.3";
	}
	if (name == VMProtectDecryptStringA("Item_Head_F_02_Lv2_C") || name == VMProtectDecryptStringA("Item_Head_F_01_Lv2_C")) {
		render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::普通物品顏色參數], pFont, VMProtectDecryptStringA(u8"｜ 頭盔Lv.2"));
		addItemYaw += onece;
		//return u8"｜ 頭盔Lv.2";
	}
	if (name == VMProtectDecryptStringA("Item_Head_G_02_Lv3_C") || name == VMProtectDecryptStringA("Item_Head_G_01_Lv3_C")) {
		render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::高級物品顏色參數], pFont, VMProtectDecryptStringA(u8"｜ 頭盔Lv.3"));
		addItemYaw += onece;
		//return u8"｜ 頭盔Lv.3";
	}


	if (name == VMProtectDecryptStringA("Item_Weapon_Winchester_C")) {
		render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::槍械武器顏色參數], pFont, VMProtectDecryptStringA(u8"｜ S1897"));
		addItemYaw += onece;
		//return u8"｜ S1897";
	}
	if (name == VMProtectDecryptStringA("Item_Weapon_Saiga12_C")) {
		render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::槍械武器顏色參數], pFont, VMProtectDecryptStringA(u8"｜ S12K"));
		addItemYaw += onece;
		//return u8"｜ S12K";
	}
	if (name == VMProtectDecryptStringA("Item_Weapon_Berreta686_C")) {
		render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::槍械武器顏色參數], pFont, VMProtectDecryptStringA(u8"｜ S686散彈"));
		addItemYaw += onece;
		//return u8"｜ S686散彈";
	}

	//衝鋒
	if (name == VMProtectDecryptStringA("Item_Weapon_UZI_C")) {
		render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::槍械武器顏色參數], pFont, VMProtectDecryptStringA(u8"｜ UZI"));
		addItemYaw += onece;
		//return u8"｜ UZI";
	}
	if (name == VMProtectDecryptStringA("Item_Weapon_Thompson_C")) {
		render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::槍械武器顏色參數], pFont, VMProtectDecryptStringA(u8"｜ 湯姆遜衝鋒槍"));
		addItemYaw += onece;
		//return u8"｜ 湯姆遜衝鋒槍";
	}
	if (name == VMProtectDecryptStringA("Item_Weapon_UMP_C")) {
		render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::槍械武器顏色參數], pFont, VMProtectDecryptStringA(u8"｜ UMP"));
		addItemYaw += onece;
		//return u8"｜ UMP";
	}
	if (name == VMProtectDecryptStringA("Item_Weapon_Vector_C")) {
		render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::槍械武器顏色參數], pFont, VMProtectDecryptStringA(u8"｜ Vector衝鋒槍"));
		addItemYaw += onece;
		//return u8"｜ Vector衝鋒槍";
	}


	if (name == VMProtectDecryptStringA("Item_Weapon_Win1894_C")) {
		render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::槍械武器顏色參數], pFont, VMProtectDecryptStringA(u8"｜ Win94"));
		addItemYaw += onece;

		//return u8"｜ Win94";
	}
	if (name == VMProtectDecryptStringA("Item_Weapon_Kar98k_C")) {
		render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::槍械武器顏色參數], pFont, VMProtectDecryptStringA(u8"｜ Kar98k"));
		addItemYaw += onece;
		//return u8"｜ Kar98k";
	}
	if (顯示篩選::M24&&name == VMProtectDecryptStringA("Item_Weapon_M24_C")) {
		render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::槍械武器顏色參數], pFont, VMProtectDecryptStringA(u8"｜ M24"));
		addItemYaw += onece;
		//return u8"｜ M24";
	}
	if (name == VMProtectDecryptStringA("Item_Weapon_AWM_C")) {
		render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::槍械武器顏色參數], pFont, VMProtectDecryptStringA(u8"｜ AWM"));
		addItemYaw += onece;
		//return u8"｜ AWM";
	}

	//步槍
	if (name == VMProtectDecryptStringA("Item_Weapon_VSS_C")) {
		render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::槍械武器顏色參數], pFont, VMProtectDecryptStringA(u8"｜ VSS"));
		addItemYaw += onece;
		//return u8"｜ VSS";
	}
	if (name == VMProtectDecryptStringA("Item_Weapon_Mini14_C")) {
		render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::槍械武器顏色參數], pFont, VMProtectDecryptStringA(u8"｜ Mini14"));
		addItemYaw += onece;
		//return u8"｜ 762子彈";
	}
	if (name == VMProtectDecryptStringA("Item_Weapon_QBU88_C")) {
		render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::槍械武器顏色參數], pFont, VMProtectDecryptStringA(u8"｜ QBU"));
		addItemYaw += onece;
		//return u8"｜ QBU";
	}
	if (name == VMProtectDecryptStringA("Item_Weapon_SKS_C")) {
		render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::槍械武器顏色參數], pFont, VMProtectDecryptStringA(u8"｜ SKS"));
		addItemYaw += onece;
		//return u8"｜ SKS";
	}

	if (name == VMProtectDecryptStringA("Item_Weapon_FNFal_C")) {
		render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::槍械武器顏色參數], pFont, VMProtectDecryptStringA(u8"｜ SLR(狙擊步槍)"));
		addItemYaw += onece;
		//return u8"｜ SLR(狙擊步槍)";
	}
	if (name == VMProtectDecryptStringA("Item_Weapon_Mk47Mutant_C")) {
		render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::槍械武器顏色參數], pFont, VMProtectDecryptStringA(u8"｜ Mk47Mutant"));
		addItemYaw += onece;
		//return u8"｜ Mk47Mutant";
	}
	if (name == VMProtectDecryptStringA("Item_Weapon_DP28_C")) {
		render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::槍械武器顏色參數], pFont, VMProtectDecryptStringA(u8"｜ DP28"));
		addItemYaw += onece;
		//return u8"｜ DP28";
	}
	if (name == VMProtectDecryptStringA("Item_Weapon_BerylM762_C")) {
		render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::槍械武器顏色參數], pFont, VMProtectDecryptStringA(u8"｜ BerylM762"));
		addItemYaw += onece;
		//return u8"｜ BerylM762";
	}
	if (name == VMProtectDecryptStringA("Item_Weapon_AK47_C")) {
		render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::槍械武器顏色參數], pFont, VMProtectDecryptStringA(u8"｜ AKM"));
		addItemYaw += onece;
		//return u8"｜ AKM";
	}
	if (name == VMProtectDecryptStringA("Item_Weapon_M16A4_C")) {
		render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::槍械武器顏色參數], pFont, VMProtectDecryptStringA(u8"｜ M16A4"));
		addItemYaw += onece;
		//return u8"｜ M16A4";
	}
	if (name == VMProtectDecryptStringA("Item_Weapon_SCAR-L_C")) {
		render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::槍械武器顏色參數], pFont, VMProtectDecryptStringA(u8"｜ SCAR-L"));
		addItemYaw += onece;
		//return u8"｜ SCAR-L";
	}
	if (name == VMProtectDecryptStringA("Item_Weapon_QBZ95_C")) {
		render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::槍械武器顏色參數], pFont, VMProtectDecryptStringA(u8"｜ QBZ"));
		addItemYaw += onece;
		//return u8"｜ QBZ";
	}
	if (name == VMProtectDecryptStringA("Item_Weapon_HK416_C")) {


		render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::槍械武器顏色參數], pFont, VMProtectDecryptStringA(u8"｜ M416"));
		addItemYaw += onece;
		//return u8"｜ M416";
	}
	if (name == VMProtectDecryptStringA("Item_Weapon_M249_C")) {
		render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::槍械武器顏色參數], pFont, VMProtectDecryptStringA(u8"｜ M249"));
		addItemYaw += onece;
		//return u8"｜ M249";
	}
	if (name == VMProtectDecryptStringA("Item_Weapon_Mk14_C")) {
		render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::槍械武器顏色參數], pFont, VMProtectDecryptStringA(u8"｜ MK14"));
		addItemYaw += onece;
		//return u8"｜ MK14";
	}
	if (name == VMProtectDecryptStringA("Item_Weapon_AUG_C")) {
		render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::槍械武器顏色參數], pFont, VMProtectDecryptStringA(u8"｜ AUG"));
		addItemYaw += onece;
		//return u8"｜ AUG";
	}
	if (name == VMProtectDecryptStringA("Item_Weapon_Groza_C")) {
		render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::槍械武器顏色參數], pFont, VMProtectDecryptStringA(u8"｜ Groza"));
		addItemYaw += onece;
		//return u8"｜ Groza";
	}


	if (name == VMProtectDecryptStringA("Item_Weapon_Pan_C")) {
		render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::高級物品顏色參數], pFont, VMProtectDecryptStringA(u8"｜ 平底鍋"));
		addItemYaw += onece;
		//return u8"｜ 平底鍋";
	}
	if (name == VMProtectDecryptStringA("Item_Weapon_FlareGun_C")) {
		render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::槍械武器顏色參數], pFont, VMProtectDecryptStringA(u8"｜ 模式重要武器:信號槍"));
		addItemYaw += onece;
		//return u8"｜ 模式重要武器:信號槍";
	}




}
void  過濾物品(std::string name, Vector3 screenloc, int 距離, int onece) {
	//	char name[100] = { NULL };

	//sprintf_s(name, "%s", cache.c_str());
	//cout << "" << name << endl;
	//render->繪製文字(screenloc.x, screenloc.y, Color{ 255, 255, 0, 255 }, pFont, name);


	//子彈
	if (顯示相關設置::顯示子彈) {
		if (顯示篩選::子彈762&&name == VMProtectDecryptStringA("Item_Ammo_762mm_C")) {
			render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::普通物品顏色參數], pFont, VMProtectDecryptStringA(u8"762子彈[%dm]"), 距離);
			addItemYaw += onece;
			//return u8"762子彈";
		}
		if (顯示篩選::子彈556&&name == VMProtectDecryptStringA("Item_Ammo_556mm_C")) {
			render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::普通物品顏色參數], pFont, VMProtectDecryptStringA(u8"556子彈[%dm]"), 距離);
			addItemYaw += onece;
			//return u8"556子彈";
		}
		if (name == VMProtectDecryptStringA("Item_Ammo_Flare_C")) {
			render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::高級物品顏色參數], pFont, VMProtectDecryptStringA(u8"信號槍子彈[%dm]"), 距離);
			addItemYaw += onece;
			//return u8"信號槍子彈";
		}
		if (name == VMProtectDecryptStringA("Item_Ammo_300Magnum_C")) {
			render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::高級物品顏色參數], pFont, VMProtectDecryptStringA(u8"AWM子彈[%dm]"), 距離);
			addItemYaw += onece;
			//return u8"AWM子彈";
		}
	}
	//補品
	if (顯示相關設置::顯示藥) {
		if (顯示篩選::飲料&&name == VMProtectDecryptStringA("Item_Boost_EnergyDrink_C")) {

			render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::普通物品顏色參數], pFont, VMProtectDecryptStringA(u8"能量飲料[%dm]"), 距離);
			addItemYaw += onece;
			//return u8"能量飲料";
		}
		if (顯示篩選::止痛藥&&name == VMProtectDecryptStringA("Item_Boost_PainKiller_C")) {
			render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::普通物品顏色參數], pFont, VMProtectDecryptStringA(u8"止痛藥[%dm]"), 距離);
			addItemYaw += onece;
			//return u8"止痛藥";
		}
		if (顯示篩選::腎上腺素&&name == VMProtectDecryptStringA("Item_Boost_AdrenalineSyringe_C")) {
			render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::高級物品顏色參數], pFont, VMProtectDecryptStringA(u8"腎上腺素[%dm]"), 距離);
			addItemYaw += onece;
			//return u8"腎上腺素";
		}
		if (顯示篩選::繃帶&&name == VMProtectDecryptStringA("Item_Heal_Bandage_C")) {
			render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::普通物品顏色參數], pFont, VMProtectDecryptStringA(u8"繃帶[%dm]"), 距離);
			addItemYaw += onece;
			//return u8"繃帶";
		}
		if (顯示篩選::急救包&&name == VMProtectDecryptStringA("Item_Heal_FirstAid_C")) {
			render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::普通物品顏色參數], pFont, VMProtectDecryptStringA(u8"急救包[%dm]"), 距離);
			addItemYaw += onece;
			//return u8"急救包";
		}
		if (顯示篩選::醫療箱&&name == VMProtectDecryptStringA("Item_Heal_MedKit_C")) {
			render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::高級物品顏色參數], pFont, VMProtectDecryptStringA(u8"醫療箱[%dm]"), 距離);
			addItemYaw += onece;
			//return u8"醫療箱";
		}
	}
	if (顯示相關設置::顯示倍鏡) {

		if (顯示篩選::x2&&name == VMProtectDecryptStringA("Item_Attach_Weapon_Upper_Aimpoint_C")) {
			render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::普通物品顏色參數], pFont, VMProtectDecryptStringA(u8"2x倍镜[%dm]"), 距離);
			addItemYaw += onece;
			//return u8"2x倍镜";
		}
		if (顯示篩選::x3&&name == VMProtectDecryptStringA("Item_Attach_Weapon_Upper_Scope3x_C")) {
			render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::普通物品顏色參數], pFont, VMProtectDecryptStringA(u8"3x倍镜[%dm]"), 距離);
			addItemYaw += onece;
			//return u8"3x倍镜";
		}
		if (顯示篩選::x4&&name == VMProtectDecryptStringA("Item_Attach_Weapon_Upper_ACOG_01_C")) {
			render->繪製圖片(screenloc.x, screenloc.y - addItemYaw, 70, 70, "C:\\Users\\play2\\Desktop\\p\\bj.png");
			render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::高級物品顏色參數], pFont, VMProtectDecryptStringA(u8"4x倍镜[%dm]"), 距離);
			addItemYaw += onece;
			//return u8"4x倍镜";
		}
		if (顯示篩選::x6&&name == VMProtectDecryptStringA("Item_Attach_Weapon_Upper_Scope6x_C")) {
			render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::高級物品顏色參數], pFont, VMProtectDecryptStringA(u8"6x倍镜[%dm]"), 距離);
			addItemYaw += onece;
			//return u8"6x倍镜";
		}
		if (顯示篩選::x8&&name == VMProtectDecryptStringA("Item_Attach_Weapon_Upper_CQBSS_C")) {
			render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::高級物品顏色參數], pFont, VMProtectDecryptStringA(u8"8x倍镜[%dm]"), 距離);
			addItemYaw += onece;
			//return u8"8x倍镜";
		}
	}
	//配件/身上裝備/手雷
	if (顯示相關設置::顯示配件) {
		//手雷
		if (顯示篩選::手榴彈&&name == VMProtectDecryptStringA("Item_Weapon_Grenade_C")) {
			render->繪製圖片(screenloc.x, screenloc.y - addItemYaw, 70, 70, "C:\\Users\\play2\\Desktop\\p\\sl.png");
			render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::普通物品顏色參數], pFont, VMProtectDecryptStringA(u8"手榴彈[%dm]"), 距離);
			addItemYaw += onece;
			//return u8"手榴彈";
		}
		if (顯示篩選::燃燒瓶 &&name == VMProtectDecryptStringA("Item_Weapon_Molotov_C")) {
			render->繪製圖片(screenloc.x, screenloc.y - addItemYaw, 70, 70, "C:\\Users\\play2\\Desktop\\p\\rsp.png");
			render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::普通物品顏色參數], pFont, VMProtectDecryptStringA(u8"燃燒瓶[%dm]"), 距離);
			addItemYaw += onece;
			//return u8"燃燒瓶";
		}
		if (顯示篩選::閃光彈&&name == VMProtectDecryptStringA("Item_Weapon_FlashBang_C")) {
			render->繪製圖片(screenloc.x, screenloc.y - addItemYaw, 70, 70, "C:\\Users\\play2\\Desktop\\p\\zbd.png");
			render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::普通物品顏色參數], pFont, VMProtectDecryptStringA(u8"閃光彈[%dm]"), 距離);
			addItemYaw += onece;
			//return u8"閃光彈";
		}
		if (顯示篩選::煙霧彈&&name == VMProtectDecryptStringA("Item_Weapon_SmokeBomb_C")) {
			render->繪製圖片(screenloc.x, screenloc.y - addItemYaw, 70, 70, "C:\\Users\\play2\\Desktop\\p\\ywd.png");
			render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::普通物品顏色參數], pFont, VMProtectDecryptStringA(u8"煙霧彈[%dm]"), 距離);
			addItemYaw += onece;
			//return u8"煙霧彈";
		}
		//if (顯示篩選::手榴彈&&name == VMProtectDecryptStringA("Item_Weapon_Grenade_Warmode_C")) {
		//	render->繪製圖片(screenloc.x, screenloc.y - addItemYaw, 70, 70, "C:\\Users\\play2\\Desktop\\p\\sl.png");
		//	render->繪製文字(screenloc.x, screenloc.y  - addItemYaw, 顏色::顏色[顏色::普通物品顏色參數], pFont,VMProtectDecryptStringA(u8"手榴彈(戰爭模式)[%dm]"), 距離);
		//addItemYaw += onece;
		////return u8"手榴彈(戰爭模式";}
		//配件
		if (name == VMProtectDecryptStringA("Item_Attach_Weapon_Upper_PM2_01_C")) {
			render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::高級物品顏色參數], pFont, VMProtectDecryptStringA(u8"15x倍镜[%dm]"), 距離);
			addItemYaw += onece;
			//return u8"15x倍镜";
		}

		if (顯示篩選::散彈收束器&&name == VMProtectDecryptStringA("Item_Attach_Weapon_Muzzle_Duckbill_C")) {
			render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::普通物品顏色參數], pFont, VMProtectDecryptStringA(u8"收束器(S12K)[%dm]"), 距離);
			addItemYaw += onece;
			//return u8"收束器(S12K)";
		}
		if (顯示篩選::散彈收束器&&name == VMProtectDecryptStringA("Item_Attach_Weapon_Muzzle_Choke_C")) {
			render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::普通物品顏色參數], pFont, VMProtectDecryptStringA(u8"收束器[%dm]"), 距離);
			addItemYaw += onece;
			//return u8"收束器";
		}
		if (顯示篩選::散彈子彈袋&&name == VMProtectDecryptStringA("Item_Attach_Weapon_Stock_Shotgun_BulletLoops_C")) {
			render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::普通物品顏色參數], pFont, VMProtectDecryptStringA(u8"散彈子彈袋[%dm]"), 距離);
			addItemYaw += onece;
			//return u8"散彈子彈袋";
		}
		if (顯示篩選::狙擊子彈袋&&name == VMProtectDecryptStringA("Item_Attach_Weapon_Stock_SniperRifle_BulletLoops_C")) {
			render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::普通物品顏色參數], pFont, VMProtectDecryptStringA(u8"狙擊子彈袋[%dm]"), 距離);
			addItemYaw += onece;
			//return u8"狙擊子彈袋";
		}
		if (顯示篩選::狙擊托腮板&&name == VMProtectDecryptStringA("Item_Attach_Weapon_Stock_SniperRifle_CheekPad_C")) {
			render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::普通物品顏色參數], pFont, VMProtectDecryptStringA(u8"托腮版[%dm]"), 距離);
			addItemYaw += onece;
			//return u8"托腮版";
		}
		if (顯示篩選::槍托&&name == VMProtectDecryptStringA("Item_Attach_Weapon_Stock_UZI_C")) {
			render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::普通物品顏色參數], pFont, VMProtectDecryptStringA(u8"烏茲槍托[%dm]"), 距離);
			addItemYaw += onece;
			//return u8"烏茲槍托";
		}
		if (顯示篩選::戰術槍托&&name == VMProtectDecryptStringA("Item_Attach_Weapon_Stock_AR_Composite_C")) {
			render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::普通物品顏色參數], pFont, VMProtectDecryptStringA(u8"戰術槍托[%dm]"), 距離);
			addItemYaw += onece;
			//return u8"戰術槍托";
		}
		if (顯示篩選::直角握把&&name == VMProtectDecryptStringA("Item_Attach_Weapon_Lower_AngledForeGrip_C")) {
			render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::普通物品顏色參數], pFont, VMProtectDecryptStringA(u8"直角握把[%dm]"), 距離);
			addItemYaw += onece;
			//return u8"直角握把";
		}
		if (顯示篩選::垂直握把&&name == VMProtectDecryptStringA("Item_Attach_Weapon_Lower_Foregrip_C")) {
			render->繪製圖片(screenloc.x, screenloc.y - addItemYaw, 70, 70, "C:\\Users\\play2\\Desktop\\p\\czwb.png");
			render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::普通物品顏色參數], pFont, VMProtectDecryptStringA(u8"垂直握把[%dm]"), 距離);
			addItemYaw += onece;
			//return u8"垂直握把";
		}

		if (顯示篩選::半截式握把&&name == VMProtectDecryptStringA("Item_Attach_Weapon_Lower_HalfGrip_C")) {
			render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::普通物品顏色參數], pFont, VMProtectDecryptStringA(u8"半截式握把[%dm]"), 距離);
			addItemYaw += onece;
			//return u8"半截式握把";
		}
		if (顯示篩選::輕型握把&&name == VMProtectDecryptStringA("Item_Attach_Weapon_Lower_LightweightForeGrip_C")) {
			render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::普通物品顏色參數], pFont, VMProtectDecryptStringA(u8"輕型握把[%dm]"), 距離);
			addItemYaw += onece;
			//return u8"輕型握把";
		}
		if (顯示篩選::拇指握把&&name == VMProtectDecryptStringA("Item_Attach_Weapon_Lower_ThumbGrip_C")) {
			render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::普通物品顏色參數], pFont, VMProtectDecryptStringA(u8"拇指握把[%dm]"), 距離);
			addItemYaw += onece;
			//return u8"拇指握把";
		}
		if (顯示篩選::雷射瞄準器&&name == VMProtectDecryptStringA("Item_Attach_Weapon_Lower_LaserPointer_C")) {
			render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::普通物品顏色參數], pFont, VMProtectDecryptStringA(u8"雷射瞄準器[%dm]"), 距離);
			addItemYaw += onece;
			//return u8"雷射瞄準器";
		}
		if (顯示篩選::全息&&name == VMProtectDecryptStringA("Item_Attach_Weapon_Upper_Holosight_C")) {
			render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::普通物品顏色參數], pFont, VMProtectDecryptStringA(u8"全息[%dm]"), 距離);
			addItemYaw += onece;
			//return u8"全息";
		}
		if (顯示篩選::紅點&&name == VMProtectDecryptStringA("Item_Attach_Weapon_Upper_DotSight_01_C")) {
			render->繪製圖片(screenloc.x, screenloc.y - addItemYaw, 70, 70, "C:\\Users\\play2\\Desktop\\p\\hd.png");
			render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::普通物品顏色參數], pFont, VMProtectDecryptStringA(u8"紅點[%dm]"), 距離);
			addItemYaw += onece;
			//return u8"紅點";
		}
		if (顯示篩選::衝鋒快擴&&name == VMProtectDecryptStringA("Item_Attach_Weapon_Magazine_ExtendedQuickDraw_Medium_C")) {
			render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::普通物品顏色參數], pFont, VMProtectDecryptStringA(u8"衝鋒快擴[%dm]"), 距離);
			addItemYaw += onece;
			//return u8"衝鋒快擴";
		}
		if (顯示篩選::步槍快擴&&name == VMProtectDecryptStringA("Item_Attach_Weapon_Magazine_ExtendedQuickDraw_Large_C")) {
			render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::高級物品顏色參數], pFont, VMProtectDecryptStringA(u8"步槍快擴[%dm]"), 距離);
			addItemYaw += onece;
			//return u8"步槍快擴";
		}
		if (顯示篩選::狙擊快擴&&name == VMProtectDecryptStringA("Item_Attach_Weapon_Magazine_ExtendedQuickDraw_SniperRifle_C")) {
			render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::高級物品顏色參數], pFont, VMProtectDecryptStringA(u8"狙擊快擴[%dm]"), 距離);
			addItemYaw += onece;
			//return u8"狙擊快擴";
		}
		if (顯示篩選::衝鋒消焰&&name == VMProtectDecryptStringA("Item_Attach_Weapon_Muzzle_FlashHider_Medium_C")) {
			render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::普通物品顏色參數], pFont, VMProtectDecryptStringA(u8"衝鋒消焰器[%dm]"), 距離);
			addItemYaw += onece;
			//return u8"衝鋒消焰器";
		}
		if (顯示篩選::步槍消焰&&name == VMProtectDecryptStringA("Item_Attach_Weapon_Muzzle_FlashHider_Large_C")) {
			render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::普通物品顏色參數], pFont, VMProtectDecryptStringA(u8"步槍消焰器[%dm]"), 距離);
			addItemYaw += onece;
			//return u8"步槍消焰器";
		}
		if (顯示篩選::狙擊消焰&&name == VMProtectDecryptStringA("Item_Attach_Weapon_Muzzle_FlashHider_SniperRifle_C")) {
			render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::普通物品顏色參數], pFont, VMProtectDecryptStringA(u8"狙擊消焰器[%dm]"), 距離);
			addItemYaw += onece;
			//return u8"狙擊消焰器";
		}
		if (顯示篩選::衝鋒補償&&name == VMProtectDecryptStringA("Item_Attach_Weapon_Muzzle_Compensator_Medium_C")) {
			render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::普通物品顏色參數], pFont, VMProtectDecryptStringA(u8"衝鋒補償[%dm]"), 距離);
			addItemYaw += onece;
			//return u8"衝鋒補償";
		}
		if (顯示篩選::步槍補償&&name == VMProtectDecryptStringA("Item_Attach_Weapon_Muzzle_Compensator_Large_C")) {
			render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::高級物品顏色參數], pFont, VMProtectDecryptStringA(u8"步槍補償[%dm]"), 距離);
			addItemYaw += onece;
			//return u8"步槍補償";
		}
		if (顯示篩選::狙擊補償&&name == VMProtectDecryptStringA("Item_Attach_Weapon_Muzzle_Compensator_SniperRifle_C")) {
			render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::高級物品顏色參數], pFont, VMProtectDecryptStringA(u8"狙擊補償[%dm]"), 距離);
			addItemYaw += onece;
			//return u8"狙擊補償";
		}
		if (顯示篩選::衝鋒消音&&name == VMProtectDecryptStringA("Item_Attach_Weapon_Muzzle_Suppressor_Medium_C")) {
			render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::普通物品顏色參數], pFont, VMProtectDecryptStringA(u8"衝鋒消音[%dm]"), 距離);
			addItemYaw += onece;
			//return u8"衝鋒消音";
		}
		if (顯示篩選::步槍消音&&name == VMProtectDecryptStringA("Item_Attach_Weapon_Muzzle_Suppressor_Large_C")) {
			render->繪製圖片(screenloc.x, screenloc.y - addItemYaw, 70, 70, "C:\\Users\\play2\\Desktop\\p\\xsq.png");
			render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::高級物品顏色參數], pFont, VMProtectDecryptStringA(u8"步槍消音[%dm]"), 距離);
			addItemYaw += onece;
			//return u8"步槍消音";
		}
		if (顯示篩選::狙擊消音&&name == VMProtectDecryptStringA("Item_Attach_Weapon_Muzzle_Suppressor_SniperRifle_C")) {
			render->繪製圖片(screenloc.x, screenloc.y - addItemYaw, 70, 70, "C:\\Users\\play2\\Desktop\\p\\xsq.png");
			render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::高級物品顏色參數], pFont, VMProtectDecryptStringA(u8"狙擊消音[%dm]"), 距離);
			addItemYaw += onece;
			//return u8"狙擊消音";
		}
		//身上的裝備
		//if (name == VMProtectDecryptStringA("Item_Armor_E_01_Lv1_C")) {
		//	render->繪製文字(screenloc.x, screenloc.y  - addItemYaw, 顏色::顏色[顏色::普通物品顏色參數], pFont,VMProtectDecryptStringA(u8"護甲Lv.1[%dm]"), 距離);
		//	addItemYaw += onece;
		////return u8"護甲Lv.1";}
		if (顯示篩選::二級防彈衣&&name == VMProtectDecryptStringA("Item_Armor_D_01_Lv2_C") || 顯示篩選::二級防彈衣&&name == VMProtectDecryptStringA("Item_Armor_D_02_Lv2_C")) {
			render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::普通物品顏色參數], pFont, VMProtectDecryptStringA(u8"護甲Lv.2[%dm]"), 距離);
			addItemYaw += onece;
			//return u8"護甲Lv.2";
		}
		if (顯示篩選::三級防彈衣&&name == VMProtectDecryptStringA("Item_Armor_C_01_Lv3_C") || 顯示篩選::三級防彈衣&&name == VMProtectDecryptStringA("Item_Armor_C_02_Lv3_C")) {
			render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::高級物品顏色參數], pFont, VMProtectDecryptStringA(u8"護甲Lv.3[%dm]"), 距離);
			addItemYaw += onece;
			//return u8"護甲Lv.3";
		}
		//if (name == VMProtectDecryptStringA("Item_Back_E_01_Lv1_C" || name == VMProtectDecryptStringA("Item_Back_E_02_Lv1_C")) {
		//	render->繪製文字(screenloc.x, screenloc.y  - addItemYaw, 顏色::顏色[顏色::普通物品顏色參數], pFont,VMProtectDecryptStringA(u8"背包Lv.1[%dm]"), 距離);
		//	addItemYaw += onece;
		////return u8"背包Lv.1";}
		if (顯示篩選::二級背包&&name == VMProtectDecryptStringA("Item_Back_F_02_Lv2_C") || 顯示篩選::二級背包&& name == VMProtectDecryptStringA("Item_Back_F_01_Lv2_C")) {
			render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::普通物品顏色參數], pFont, VMProtectDecryptStringA(u8"背包Lv.2[%dm]"), 距離);
			addItemYaw += onece;
			//return u8"背包Lv.2";
		}//
		if (顯示篩選::三級背包&&name == VMProtectDecryptStringA("Item_Back_C_02_Lv3_C") || 顯示篩選::三級背包&&name == VMProtectDecryptStringA("Item_Back_C_01_Lv3_C")) {
			render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::高級物品顏色參數], pFont, VMProtectDecryptStringA(u8"背包Lv.3[%dm]"), 距離);
			addItemYaw += onece;
			//return u8"背包Lv.3";
		}
		//if (name == VMProtectDecryptStringA("Item_Head_E_02_Lv1_C" || name == VMProtectDecryptStringA("Item_Head_E_01_Lv1_C")) {
		//	render->繪製文字(screenloc.x, screenloc.y  - addItemYaw, 顏色::顏色[顏色::普通物品顏色參數], pFont,VMProtectDecryptStringA(u8"頭盔Lv.1[%dm]"), 距離);
		//	addItemYaw += onece;
		////return u8"頭盔Lv.1";}
		if (顯示篩選::二級頭盔&&name == VMProtectDecryptStringA("Item_Head_F_02_Lv2_C") || 顯示篩選::二級頭盔&& name == VMProtectDecryptStringA("Item_Head_F_01_Lv2_C")) {
			render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::普通物品顏色參數], pFont, VMProtectDecryptStringA(u8"頭盔Lv.2[%dm]"), 距離);
			addItemYaw += onece;
			//return u8"頭盔Lv.2";
		}
		if (顯示篩選::三級頭盔&&name == VMProtectDecryptStringA("Item_Head_G_02_Lv3_C") || 顯示篩選::三級頭盔&&name == VMProtectDecryptStringA("Item_Head_G_01_Lv3_C")) {
			render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::高級物品顏色參數], pFont, VMProtectDecryptStringA(u8"頭盔Lv.3[%dm]"), 距離);
			addItemYaw += onece;
			//return u8"頭盔Lv.3";
		}
	}
	//槍
	if (顯示相關設置::顯示槍) {
		//小槍

		//if (name == VMProtectDecryptStringA("Item_Weapon_NagantM1895_C")) {
		//	render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::槍械武器顏色參數], pFont,VMProtectDecryptStringA(u8"左輪手槍[%dm]"), 距離);
		//	addItemYaw += onece;
		////return u8"左輪手槍";}
		//if (name == VMProtectDecryptStringA("Item_Weapon_Rhino_C")) {
		//	render->繪製文字(screenloc.x, screenloc.y  - addItemYaw, 顏色::顏色[顏色::槍械武器顏色參數], pFont,VMProtectDecryptStringA(u8"R45[%dm]"), 距離);
		//	addItemYaw += onece;
		////return u8"R45";}
		//if (name == VMProtectDecryptStringA("Item_Weapon_M9_C")) {
		//render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::槍械武器顏色參數], pFont,VMProtectDecryptStringA(u8"P92[%dm]"), 距離);
		//addItemYaw += onece;
		////return u8"P92";}
		//if (name == VMProtectDecryptStringA("Item_Weapon_G18_C")) {
		//	render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::槍械武器顏色參數], pFont,VMProtectDecryptStringA(u8"P18C[%dm]"), 距離);
		////return u8"P18C";}
		//if (name == VMProtectDecryptStringA("Item_Weapon_M1911_C")) {
		//	render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::槍械武器顏色參數], pFont,VMProtectDecryptStringA(u8"P1911[%dm]"), 距離);
		//	addItemYaw += onece;
		////return u8"P1911";}
		if (顯示篩選::SAWED&&name == VMProtectDecryptStringA("Item_Weapon_Sawnoff_C")) {
			render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::槍械武器顏色參數], pFont, VMProtectDecryptStringA(u8"削短型散彈槍[%dm]"), 距離);
			addItemYaw += onece;
			//return u8"削短型散彈槍";
		}
		//散彈
		if (顯示篩選::S1897&&name == VMProtectDecryptStringA("Item_Weapon_Winchester_C")) {
			render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::槍械武器顏色參數], pFont, VMProtectDecryptStringA(u8"S1897[%dm]"), 距離);
			addItemYaw += onece;
			//return u8"S1897";
		}
		if (顯示篩選::S12K&&name == VMProtectDecryptStringA("Item_Weapon_Saiga12_C")) {
			render->繪製圖片(screenloc.x, screenloc.y - addItemYaw, 70, 70, "C:\\Users\\play2\\Desktop\\p\\s12k.png");
			render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::槍械武器顏色參數], pFont, VMProtectDecryptStringA(u8"S12K[%dm]"), 距離);
			addItemYaw += onece;
			//return u8"S12K";
		}
		if (顯示篩選::S686&&name == VMProtectDecryptStringA("Item_Weapon_Berreta686_C")) {
			render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::槍械武器顏色參數], pFont, VMProtectDecryptStringA(u8"S686散彈[%dm]"), 距離);
			addItemYaw += onece;
			//return u8"S686散彈";
		}

		//衝鋒
		if (顯示篩選::UZI&&name == VMProtectDecryptStringA("Item_Weapon_UZI_C")) {
			render->繪製圖片(screenloc.x, screenloc.y - addItemYaw, 70, 70, "C:\\Users\\play2\\Desktop\\p\\uzi.png");
			render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::槍械武器顏色參數], pFont, VMProtectDecryptStringA(u8"UZI[%dm]"), 距離);
			addItemYaw += onece;
			//return u8"UZI";
		}
		if (顯示篩選::TOMMYGUN&&name == VMProtectDecryptStringA("Item_Weapon_Thompson_C")) {
			render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::槍械武器顏色參數], pFont, VMProtectDecryptStringA(u8"湯姆遜衝鋒槍[%dm]"), 距離);
			addItemYaw += onece;
			//return u8"湯姆遜衝鋒槍";
		}
		if (顯示篩選::UMP9&&name == VMProtectDecryptStringA("Item_Weapon_UMP_C")) {
			render->繪製圖片(screenloc.x, screenloc.y - addItemYaw, 70, 70, "C:\\Users\\play2\\Desktop\\p\\ump9.png");
			render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::槍械武器顏色參數], pFont, VMProtectDecryptStringA(u8"UMP[%dm]"), 距離);
			addItemYaw += onece;
			//return u8"UMP";
		}
		if (顯示篩選::VECTOR&&name == VMProtectDecryptStringA("Item_Weapon_Vector_C")) {
			render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::槍械武器顏色參數], pFont, VMProtectDecryptStringA(u8"Vector衝鋒槍[%dm]"), 距離);
			addItemYaw += onece;
			//return u8"Vector衝鋒槍";
		}

		//狙擊
		if (顯示篩選::CROSSBOW&&name == VMProtectDecryptStringA("Item_Weapon_Crossbow_C")) {
			render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::槍械武器顏色參數], pFont, VMProtectDecryptStringA(u8"十字弓[%dm]"), 距離);
			addItemYaw += onece;
			//return u8"十字弓";
		}
		if (顯示篩選::WIN94&&name == VMProtectDecryptStringA("Item_Weapon_Win1894_C")) {
			render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::槍械武器顏色參數], pFont, VMProtectDecryptStringA(u8"Win94[%dm]"), 距離);
			addItemYaw += onece;

			//return u8"Win94";
		}
		if (顯示篩選::KAR98K&&name == VMProtectDecryptStringA("Item_Weapon_Kar98k_C")) {
			render->繪製圖片(screenloc.x, screenloc.y - addItemYaw, 70, 70, "C:\\Users\\play2\\Desktop\\p\\98k.png");
			render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::槍械武器顏色參數], pFont, VMProtectDecryptStringA(u8"Kar98k[%dm]"), 距離);
			addItemYaw += onece;
			//return u8"Kar98k";
		}
		if (顯示篩選::M24&&name == VMProtectDecryptStringA("Item_Weapon_M24_C")) {
			render->繪製圖片(screenloc.x, screenloc.y - addItemYaw, 70, 70, "C:\\Users\\play2\\Desktop\\p\\m24.png");
			render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::槍械武器顏色參數], pFont, VMProtectDecryptStringA(u8"M24[%dm]"), 距離);
			addItemYaw += onece;
			//return u8"M24";
		}
		if (name == VMProtectDecryptStringA("Item_Weapon_AWM_C")) {
			render->繪製圖片(screenloc.x, screenloc.y - addItemYaw, 70, 70, "C:\\Users\\play2\\Desktop\\p\\awm.png");
			render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::槍械武器顏色參數], pFont, VMProtectDecryptStringA(u8"AWM[%dm]"), 距離);
			addItemYaw += onece;
			//return u8"AWM";
		}

		//步槍
		if (顯示篩選::VSS&&name == VMProtectDecryptStringA("Item_Weapon_VSS_C")) {
			render->繪製圖片(screenloc.x, screenloc.y - addItemYaw, 70, 70, "C:\\Users\\play2\\Desktop\\p\\vss.png");
			render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::槍械武器顏色參數], pFont, VMProtectDecryptStringA(u8"VSS[%dm]"), 距離);
			addItemYaw += onece;
			//return u8"VSS";
		}
		if (顯示篩選::MINI14&&name == VMProtectDecryptStringA("Item_Weapon_Mini14_C")) {
			render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::槍械武器顏色參數], pFont, VMProtectDecryptStringA(u8"Mini14[%dm]"), 距離);
			addItemYaw += onece;
			//return u8"762子彈";
		}
		if (顯示篩選::QBU&&name == VMProtectDecryptStringA("Item_Weapon_QBU88_C")) {
			render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::槍械武器顏色參數], pFont, VMProtectDecryptStringA(u8"QBU[%dm]"), 距離);
			addItemYaw += onece;
			//return u8"QBU";
		}
		if (顯示篩選::SKS&&name == VMProtectDecryptStringA("Item_Weapon_SKS_C")) {
			render->繪製圖片(screenloc.x, screenloc.y - addItemYaw, 70, 70, "C:\\Users\\play2\\Desktop\\p\\sks.png");
			render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::槍械武器顏色參數], pFont, VMProtectDecryptStringA(u8"SKS[%dm]"), 距離);
			addItemYaw += onece;
			//return u8"SKS";
		}

		if (顯示篩選::SLR&&name == VMProtectDecryptStringA("Item_Weapon_FNFal_C")) {
			render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::槍械武器顏色參數], pFont, VMProtectDecryptStringA(u8"SLR(狙擊步槍)[%dm]"), 距離);
			addItemYaw += onece;
			//return u8"SLR(狙擊步槍)";
		}
		if (顯示篩選::Mk47Mutan&&name == VMProtectDecryptStringA("Item_Weapon_Mk47Mutant_C")) {
			render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::槍械武器顏色參數], pFont, VMProtectDecryptStringA(u8"Mk47Mutant[%dm]"), 距離);
			addItemYaw += onece;
			//return u8"Mk47Mutant";
		}
		if (顯示篩選::DP28&&name == VMProtectDecryptStringA("Item_Weapon_DP28_C")) {
			render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::槍械武器顏色參數], pFont, VMProtectDecryptStringA(u8"DP28[%dm]"), 距離);
			addItemYaw += onece;
			//return u8"DP28";
		}
		if (顯示篩選::BerylM762&&name == VMProtectDecryptStringA("Item_Weapon_BerylM762_C")) {
			render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::槍械武器顏色參數], pFont, VMProtectDecryptStringA(u8"BerylM762[%dm]"), 距離);
			addItemYaw += onece;
			//return u8"BerylM762";
		}
		if (顯示篩選::AKM&&name == VMProtectDecryptStringA("Item_Weapon_AK47_C")) {
			render->繪製圖片(screenloc.x, screenloc.y - addItemYaw, 70, 70, "C:\\Users\\play2\\Desktop\\p\\akm.png");
			render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::槍械武器顏色參數], pFont, VMProtectDecryptStringA(u8"AKM[%dm]"), 距離);
			addItemYaw += onece;
			//return u8"AKM";
		}
		if (顯示篩選::M16A4&&name == VMProtectDecryptStringA("Item_Weapon_M16A4_C")) {
			render->繪製圖片(screenloc.x, screenloc.y - addItemYaw, 70, 70, "C:\\Users\\play2\\Desktop\\p\\m16.png");
			render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::槍械武器顏色參數], pFont, VMProtectDecryptStringA(u8"M16A4[%dm]"), 距離);
			addItemYaw += onece;
			//return u8"M16A4";
		}
		if (顯示篩選::SCAR&&name == VMProtectDecryptStringA("Item_Weapon_SCAR-L_C")) {
			render->繪製圖片(screenloc.x, screenloc.y - addItemYaw, 70, 70, "C:\\Users\\play2\\Desktop\\p\\scar.png");
			render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::槍械武器顏色參數], pFont, VMProtectDecryptStringA(u8"SCAR-L[%dm]"), 距離);
			addItemYaw += onece;
			//return u8"SCAR-L";
		}
		if (顯示篩選::QBZ&&name == VMProtectDecryptStringA("Item_Weapon_QBZ95_C")) {
			render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::槍械武器顏色參數], pFont, VMProtectDecryptStringA(u8"QBZ[%dm]"), 距離);
			addItemYaw += onece;
			//return u8"QBZ";
		}
		if (顯示篩選::M416&&name == VMProtectDecryptStringA("Item_Weapon_HK416_C")) {

			render->繪製圖片(screenloc.x, screenloc.y - addItemYaw, 70, 70, "C:\\Users\\play2\\Desktop\\p\\m416.png");
			render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::槍械武器顏色參數], pFont, VMProtectDecryptStringA(u8"M416[%dm]"), 距離);
			addItemYaw += onece;
			//return u8"M416";
		}
		if (name == VMProtectDecryptStringA("Item_Weapon_M249_C")) {
			render->繪製圖片(screenloc.x, screenloc.y - addItemYaw, 70, 70, "C:\\Users\\play2\\Desktop\\p\\m249.png");
			render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::槍械武器顏色參數], pFont, VMProtectDecryptStringA(u8"M249[%dm]"), 距離);
			addItemYaw += onece;
			//return u8"M249";
		}
		if (name == VMProtectDecryptStringA("Item_Weapon_Mk14_C")) {
			render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::槍械武器顏色參數], pFont, VMProtectDecryptStringA(u8"MK14[%dm]"), 距離);
			addItemYaw += onece;
			//return u8"MK14";
		}
		if (name == VMProtectDecryptStringA("Item_Weapon_AUG_C")) {
			render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::槍械武器顏色參數], pFont, VMProtectDecryptStringA(u8"AUG[%dm]"), 距離);
			addItemYaw += onece;
			//return u8"AUG";
		}
		if (name == VMProtectDecryptStringA("Item_Weapon_Groza_C")) {
			render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::槍械武器顏色參數], pFont, VMProtectDecryptStringA(u8"Groza[%dm]"), 距離);
			addItemYaw += onece;
			//return u8"Groza";
		}
	}
	//其他
	if (顯示相關設置::顯示自訂) {
		//if (name == "tem_JerryCan_C")) {
		//render->繪製文字(screenloc.x, screenloc.y  - addItemYaw, 顏色::顏色[顏色::普通物品顏色參數], pFont,VMProtectDecryptStringA(u8"油桶[%dm]"), 距離);
		//	//return u8"油桶";}}
		if (顯示篩選::平底鍋&&name == VMProtectDecryptStringA("Item_Weapon_Pan_C")) {
			render->繪製圖片(screenloc.x, screenloc.y - addItemYaw, 70, 70, "C:\\Users\\play2\\Desktop\\p\\pdg.png");
			render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::高級物品顏色參數], pFont, VMProtectDecryptStringA(u8"平底鍋[%dm]"), 距離);
			addItemYaw += onece;
			//return u8"平底鍋";
		}
		if (name == VMProtectDecryptStringA("Item_Weapon_FlareGun_C")) {
			render->繪製文字(screenloc.x, screenloc.y - addItemYaw, 顏色::顏色[顏色::槍械武器顏色參數], pFont, VMProtectDecryptStringA(u8"模式重要武器:信號槍[%dm]"), 距離);
			addItemYaw += onece;
			//return u8"模式重要武器:信號槍";
		}
	}


	/*
	if (顯示篩選::醫療箱 && !strcmp(缓存物品, "Med Kit"))
	{
	render->繪製描邊文字(screenloc.x, screenloc.y,Color{255,131,52,255}, 顏色::顏色[顏色::普通物品顏色參數], pFont, VMProtectDecryptStringA(u8"醫療箱[%d米]"), 距離);
	}
	else if (顯示篩選::急救包 && !strcmp(缓存物品, "First Aid Kit"))
	{
	render->繪製描邊文字(screenloc.x, screenloc.y,Color{255,131,52,255}, 顏色::顏色[顏色::普通物品顏色參數], pFont, VMProtectDecryptStringA(u8"急救包[%d米]"), 距離);
	}
	else if (顯示篩選::止痛藥 && !strcmp(缓存物品, "Painkiller"))
	{
	render->繪製描邊文字(screenloc.x, screenloc.y,Color{255,131,52,255}, 顏色::顏色[顏色::普通物品顏色參數], pFont, VMProtectDecryptStringA(u8"止痛藥[%d米]"), 距離);
	}
	else if (顯示篩選::飲料 && !strcmp(缓存物品, "Energy Drink"))
	{
	render->繪製描邊文字(screenloc.x, screenloc.y,Color{255,131,52,255}, 顏色::顏色[顏色::普通物品顏色參數], pFont, VMProtectDecryptStringA(u8"飲料[%d米]"), 距離);
	}
	else if (顯示篩選::繃帶 && !strcmp(缓存物品, "Bandage"))
	{
	render->繪製描邊文字(screenloc.x, screenloc.y,Color{255,131,52,255}, 顏色::顏色[顏色::普通物品顏色參數], pFont, VMProtectDecryptStringA(u8"繃帶[%d米]"), 距離);
	}
	else if (顯示篩選::AKM && !strcmp(缓存物品, "AKM"))
	{
	render->繪製描邊文字(screenloc.x, screenloc.y,Color{255,131,52,255}, 顏色::顏色[顏色::槍械武器顏色參數], pFont, VMProtectDecryptStringA(u8"AKM[%d米]"), 距離);
	}
	else if (顯示篩選::M416 && !strcmp(缓存物品, "M416"))
	{
	render->繪製描邊文字(screenloc.x, screenloc.y,Color{255,131,52,255}, 顏色::顏色[顏色::槍械武器顏色參數], pFont, VMProtectDecryptStringA(u8"M416[%d米]"), 距離);
	}
	else if (顯示篩選::M16A4 && !strcmp(缓存物品, "M16A4"))
	{
	render->繪製描邊文字(screenloc.x, screenloc.y,Color{255,131,52,255}, 顏色::顏色[顏色::槍械武器顏色參數], pFont, VMProtectDecryptStringA(u8"M16A4[%d米]"), 距離);
	}
	else if (顯示篩選::SCAR && !strcmp(缓存物品, "SCAR-L"))
	{
	render->繪製描邊文字(screenloc.x, screenloc.y,Color{255,131,52,255}, 顏色::顏色[顏色::槍械武器顏色參數], pFont, VMProtectDecryptStringA(u8"SCAR-L[%d米]"), 距離);
	}
	else if (顯示篩選::VSS && !strcmp(缓存物品, "VSS"))
	{
	render->繪製描邊文字(screenloc.x, screenloc.y,Color{255,131,52,255}, 顏色::顏色[顏色::槍械武器顏色參數], pFont, VMProtectDecryptStringA(u8"VSS[%d米]"), 距離);
	}
	else if (顯示篩選::SKS && !strcmp(缓存物品, "SKS"))
	{
	render->繪製描邊文字(screenloc.x, screenloc.y,Color{255,131,52,255}, 顏色::顏色[顏色::槍械武器顏色參數], pFont, VMProtectDecryptStringA(u8"SKS[%d米]"), 距離);
	}
	else if (顯示篩選::MINI14 && !strcmp(缓存物品, "Mini14"))
	{
	render->繪製描邊文字(screenloc.x, screenloc.y,Color{255,131,52,255}, 顏色::顏色[顏色::槍械武器顏色參數], pFont, VMProtectDecryptStringA(u8"Mini14[%d米]"), 距離);
	}
	else if (顯示篩選::KAR98K && !strcmp(缓存物品, "Kar98k"))
	{
	render->繪製描邊文字(screenloc.x, screenloc.y,Color{255,131,52,255}, 顏色::顏色[顏色::槍械武器顏色參數], pFont, VMProtectDecryptStringA(u8"Kar98k[%d米]"), 距離);
	}
	else if (顯示篩選::WIN94 && !strcmp(缓存物品, "Win94"))
	{
	render->繪製描邊文字(screenloc.x, screenloc.y,Color{255,131,52,255}, 顏色::顏色[顏色::槍械武器顏色參數], pFont, VMProtectDecryptStringA(u8"Win94[%d米]"), 距離);
	}
	else if (顯示篩選::SAWED && !strcmp(缓存物品, "Sawed-off"))
	{
	render->繪製描邊文字(screenloc.x, screenloc.y,Color{255,131,52,255}, 顏色::顏色[顏色::槍械武器顏色參數], pFont, VMProtectDecryptStringA(u8"Sawed-off[%d米]"), 距離);
	}
	else if (顯示篩選::DP28 && !strcmp(缓存物品, "DP-28"))
	{
	render->繪製描邊文字(screenloc.x, screenloc.y,Color{255,131,52,255}, 顏色::顏色[顏色::槍械武器顏色參數], pFont, VMProtectDecryptStringA(u8"DP-28[%d米]"), 距離);
	}
	else if (顯示篩選::UZI && !strcmp(缓存物品, "Micro UZI"))
	{
	render->繪製描邊文字(screenloc.x, screenloc.y,Color{255,131,52,255}, 顏色::顏色[顏色::槍械武器顏色參數], pFont, VMProtectDecryptStringA(u8"Micro UZI[%d米]"), 距離);
	}
	else if (顯示篩選::UMP9 && !strcmp(缓存物品, "UMP9"))
	{
	render->繪製描邊文字(screenloc.x, screenloc.y,Color{255,131,52,255}, 顏色::顏色[顏色::槍械武器顏色參數], pFont, VMProtectDecryptStringA(u8"UMP9[%d米]"), 距離);
	}
	else if (顯示篩選::VECTOR && !strcmp(缓存物品, "Vector"))
	{
	render->繪製描邊文字(screenloc.x, screenloc.y,Color{255,131,52,255}, 顏色::顏色[顏色::槍械武器顏色參數], pFont, VMProtectDecryptStringA(u8"Vector[%d米]"), 距離);
	}
	else if (顯示篩選::S12K && !strcmp(缓存物品, "S12K"))
	{
	render->繪製描邊文字(screenloc.x, screenloc.y,Color{255,131,52,255}, 顏色::顏色[顏色::槍械武器顏色參數], pFont, VMProtectDecryptStringA(u8"S12K[%d米]"), 距離);
	}
	else if (顯示篩選::S686 && !strcmp(缓存物品, "S686"))
	{
	render->繪製描邊文字(screenloc.x, screenloc.y,Color{255,131,52,255}, 顏色::顏色[顏色::槍械武器顏色參數], pFont, VMProtectDecryptStringA(u8"S686[%d米]"), 距離);
	}
	else if (顯示篩選::S1897 && !strcmp(缓存物品, "S1897"))
	{
	render->繪製描邊文字(screenloc.x, screenloc.y,Color{255,131,52,255}, 顏色::顏色[顏色::槍械武器顏色參數], pFont, VMProtectDecryptStringA(u8"S1897[%d米]"), 距離);
	}
	else if (顯示篩選::CROSSBOW && !strcmp(缓存物品, "Crossbow"))
	{
	render->繪製描邊文字(screenloc.x, screenloc.y,Color{255,131,52,255}, 顏色::顏色[顏色::槍械武器顏色參數], pFont, VMProtectDecryptStringA(u8"十字弓[%d米]"), 距離);
	}
	else if (顯示篩選::TOMMYGUN && !strcmp(缓存物品, "Tommy Gun"))
	{
	render->繪製描邊文字(screenloc.x, screenloc.y,Color{255,131,52,255}, 顏色::顏色[顏色::槍械武器顏色參數], pFont, VMProtectDecryptStringA(u8"湯姆遜[%d米]"), 距離);
	}
	else if (顯示篩選::平底鍋 && !strcmp(缓存物品, "Pan"))
	{
	render->繪製描邊文字(screenloc.x, screenloc.y,Color{255,131,52,255}, 顏色::顏色[顏色::普通物品顏色參數], pFont, VMProtectDecryptStringA(u8"平底鍋[%d米]"), 距離);
	}
	else if (顯示篩選::手榴彈 && !strcmp(缓存物品, "Frag Grenade"))
	{
	render->繪製描邊文字(screenloc.x, screenloc.y,Color{255,131,52,255}, 顏色::顏色[顏色::普通物品顏色參數], pFont, VMProtectDecryptStringA(u8"手榴彈[%d米]"), 距離);
	}
	else if (顯示篩選::煙霧彈 && !strcmp(缓存物品, "Smoke Grenade"))
	{
	render->繪製描邊文字(screenloc.x, screenloc.y,Color{255,131,52,255}, 顏色::顏色[顏色::普通物品顏色參數], pFont, VMProtectDecryptStringA(u8"煙霧彈[%d米]"), 距離);
	}
	else if (顯示篩選::閃光彈 && !strcmp(缓存物品, "Stun Grenade"))
	{
	render->繪製描邊文字(screenloc.x, screenloc.y,Color{255,131,52,255}, 顏色::顏色[顏色::普通物品顏色參數], pFont, VMProtectDecryptStringA(u8"閃光彈[%d米]"), 距離);
	}
	else if (顯示篩選::燃燒瓶 && !strcmp(缓存物品, "Molotov Cocktail"))
	{
	render->繪製描邊文字(screenloc.x, screenloc.y,Color{255,131,52,255}, 顏色::顏色[顏色::普通物品顏色參數], pFont, VMProtectDecryptStringA(u8"燃燒瓶[%d米]"), 距離);
	}
	else if (顯示篩選::二級頭盔 && !strcmp(缓存物品, "Helmet (Lv.2)"))
	{
	render->繪製描邊文字(screenloc.x, screenloc.y,Color{255,131,52,255}, 顏色::顏色[顏色::普通物品顏色參數], pFont, VMProtectDecryptStringA(u8"頭盔Lv.2[%d米]"), 距離);
	}
	else if (顯示篩選::三級頭盔 && !strcmp(缓存物品, "Helmet (Lv.3)"))
	{
	render->繪製描邊文字(screenloc.x, screenloc.y,Color{255,131,52,255}, 顏色::顏色[顏色::高級物品顏色參數], pFont, VMProtectDecryptStringA(u8"頭盔Lv.3[%d米]"), 距離);
	}
	else if (顯示篩選::二級背包 && !strcmp(缓存物品, "Backpack (Lv.2)"))
	{
	render->繪製描邊文字(screenloc.x, screenloc.y,Color{255,131,52,255}, 顏色::顏色[顏色::普通物品顏色參數], pFont, VMProtectDecryptStringA(u8"背包Lv.2[%d米]"), 距離);
	}
	else if (顯示篩選::三級背包 && !strcmp(缓存物品, "Backpack (Lv.3)"))
	{
	render->繪製描邊文字(screenloc.x, screenloc.y,Color{255,131,52,255}, 顏色::顏色[顏色::高級物品顏色參數], pFont, VMProtectDecryptStringA(u8"背包Lv.3[%d米]"), 距離);
	}
	else if (顯示篩選::二級防彈衣 && !strcmp(缓存物品, "Police Vest (Lv.2)"))
	{
	render->繪製描邊文字(screenloc.x, screenloc.y,Color{255,131,52,255}, 顏色::顏色[顏色::普通物品顏色參數], pFont, VMProtectDecryptStringA(u8"防彈衣Lv.2[%d米]"), 距離);
	}
	else if (顯示篩選::三級防彈衣 && !strcmp(缓存物品, "Military Vest (Lv.3)"))
	{
	render->繪製描邊文字(screenloc.x, screenloc.y,Color{255,131,52,255}, 顏色::顏色[顏色::高級物品顏色參數], pFont, VMProtectDecryptStringA(u8"防彈衣Lv.3[%d米]"), 距離);
	}
	else if (顯示篩選::x2 && !strcmp(缓存物品, "2x Scope"))
	{
	render->繪製描邊文字(screenloc.x, screenloc.y,Color{255,131,52,255}, 顏色::顏色[顏色::普通物品顏色參數], pFont, VMProtectDecryptStringA(u8"2x 倍鏡[%d米]"), 距離);
	}
	else if (顯示篩選::x4 && !strcmp(缓存物品, "4x Scope"))
	{
	render->繪製描邊文字(screenloc.x, screenloc.y,Color{255,131,52,255}, 顏色::顏色[顏色::高級物品顏色參數], pFont, VMProtectDecryptStringA(u8"4x 倍鏡[%d米]"), 距離);
	}
	else if (顯示篩選::x8 && !strcmp(缓存物品, "8x Scope"))
	{
	render->繪製描邊文字(screenloc.x, screenloc.y,Color{255,131,52,255}, 顏色::顏色[顏色::高級物品顏色參數], pFont, VMProtectDecryptStringA(u8"8x 倍鏡[%d米]"), 距離);
	}
	else if (顯示篩選::全息 && !strcmp(缓存物品, "Holographic Sight"))
	{
	render->繪製描邊文字(screenloc.x, screenloc.y,Color{255,131,52,255}, 顏色::顏色[顏色::普通物品顏色參數], pFont, VMProtectDecryptStringA(u8"全息[%d米]"), 距離);
	}
	else if (顯示篩選::紅點 && !strcmp(缓存物品, "Red Dot Sight"))
	{
	render->繪製描邊文字(screenloc.x, screenloc.y,Color{255,131,52,255}, 顏色::顏色[顏色::普通物品顏色參數], pFont, VMProtectDecryptStringA(u8"紅點[%d米]"), 距離);
	}
	else if (顯示篩選::槍托 && !strcmp(缓存物品, "Stock (Micro UZI)"))
	{
	render->繪製描邊文字(screenloc.x, screenloc.y,Color{255,131,52,255}, 顏色::顏色[顏色::普通物品顏色參數], pFont, VMProtectDecryptStringA(u8"烏茲槍托[%d米]"), 距離);
	}
	else if (顯示篩選::戰術槍托 && !strcmp(缓存物品, "Tactical Stock (M416, Vector)"))
	{
	render->繪製描邊文字(screenloc.x, screenloc.y,Color{255,131,52,255}, 顏色::顏色[顏色::普通物品顏色參數], pFont, VMProtectDecryptStringA(u8"戰術槍托[%d米]"), 距離);
	}
	else if (顯示篩選::垂直握把 && !strcmp(缓存物品, "Vertical Foregrip (AR, SMG, SR)"))
	{
	render->繪製描邊文字(screenloc.x, screenloc.y,Color{255,131,52,255}, 顏色::顏色[顏色::普通物品顏色參數], pFont, VMProtectDecryptStringA(u8"垂直握把[%d米]"), 距離);
	}
	else if (顯示篩選::直角握把 && !strcmp(缓存物品, "Angled Foregrip (AR, SMG, SR)"))
	{
	render->繪製描邊文字(screenloc.x, screenloc.y,Color{255,131,52,255}, 顏色::顏色[顏色::普通物品顏色參數], pFont, VMProtectDecryptStringA(u8"直角握把[%d米]"), 距離);
	}
	else if (顯示篩選::衝鋒消音 && !strcmp(缓存物品, "Suppressor (SMG)"))
	{
	render->繪製描邊文字(screenloc.x, screenloc.y,Color{255,131,52,255}, 顏色::顏色[顏色::普通物品顏色參數], pFont, VMProtectDecryptStringA(u8"衝鋒消音[%d米]"), 距離);
	}
	else if (顯示篩選::步槍消音 && !strcmp(缓存物品, "Suppressor (AR, S12K)"))
	{
	render->繪製描邊文字(screenloc.x, screenloc.y,Color{255,131,52,255}, 顏色::顏色[顏色::高級物品顏色參數], pFont, VMProtectDecryptStringA(u8"步槍消音[%d米]"), 距離);
	}
	else if (顯示篩選::狙擊消音 && !strcmp(缓存物品, "Suppressor (SR)"))
	{
	render->繪製描邊文字(screenloc.x, screenloc.y,Color{255,131,52,255}, 顏色::顏色[顏色::高級物品顏色參數], pFont, VMProtectDecryptStringA(u8"狙擊消音[%d米]"), 距離);
	}
	else if (顯示篩選::衝鋒消焰 && !strcmp(缓存物品, "Flash Hider (SMG)"))
	{
	render->繪製描邊文字(screenloc.x, screenloc.y,Color{255,131,52,255}, 顏色::顏色[顏色::普通物品顏色參數], pFont, VMProtectDecryptStringA(u8"衝鋒消焰[%d米]"), 距離);
	}
	else if (顯示篩選::步槍消焰 && !strcmp(缓存物品, "Flash Hider (AR, S12K)"))
	{
	render->繪製描邊文字(screenloc.x, screenloc.y,Color{255,131,52,255}, 顏色::顏色[顏色::普通物品顏色參數], pFont, VMProtectDecryptStringA(u8"步槍消焰[%d米]"), 距離);
	}
	else if (顯示篩選::狙擊消焰 && !strcmp(缓存物品, "Flash Hider (SR)"))
	{
	render->繪製描邊文字(screenloc.x, screenloc.y,Color{255,131,52,255}, 顏色::顏色[顏色::普通物品顏色參數], pFont, VMProtectDecryptStringA(u8"狙擊消焰[%d米]"), 距離);
	}
	else if (顯示篩選::衝鋒快擴 && !strcmp(缓存物品, "Ext. QuickDraw Mag (SMG)"))
	{
	render->繪製描邊文字(screenloc.x, screenloc.y,Color{255,131,52,255}, 顏色::顏色[顏色::普通物品顏色參數], pFont, VMProtectDecryptStringA(u8"衝鋒快擴[%d米]"), 距離);
	}
	else if (顯示篩選::狙擊快擴 && !strcmp(缓存物品, "Ext. QuickDraw Mag (SR)"))
	{
	render->繪製描邊文字(screenloc.x, screenloc.y,Color{255,131,52,255}, 顏色::顏色[顏色::普通物品顏色參數], pFont, VMProtectDecryptStringA(u8"狙擊快擴[%d米]"), 距離);
	}
	else if (顯示篩選::步槍快擴 && !strcmp(缓存物品, "Ext. QuickDraw Mag (AR, S12K)"))
	{
	render->繪製描邊文字(screenloc.x, screenloc.y,Color{255,131,52,255}, 顏色::顏色[顏色::普通物品顏色參數], pFont, VMProtectDecryptStringA(u8"步槍快擴[%d米]"), 距離);
	}
	else if (顯示篩選::衝鋒補償 && !strcmp(缓存物品, "Compensator (SMG)"))
	{
	render->繪製描邊文字(screenloc.x, screenloc.y,Color{255,131,52,255}, 顏色::顏色[顏色::普通物品顏色參數], pFont, VMProtectDecryptStringA(u8"衝鋒補償[%d米]"), 距離);
	}
	else if (顯示篩選::步槍補償 && !strcmp(缓存物品, "Compensator (AR, S12K)"))
	{
	render->繪製描邊文字(screenloc.x, screenloc.y,Color{255,131,52,255}, 顏色::顏色[顏色::高級物品顏色參數], pFont, VMProtectDecryptStringA(u8"步槍補償[%d米]"), 距離);
	}
	else if (顯示篩選::狙擊補償 && !strcmp(缓存物品, "Compensator (SR)"))
	{
	render->繪製描邊文字(screenloc.x, screenloc.y,Color{255,131,52,255}, 顏色::顏色[顏色::高級物品顏色參數], pFont, VMProtectDecryptStringA(u8"狙擊補償[%d米]"), 距離);
	}
	else if (顯示篩選::散彈收束器 && !strcmp(缓存物品, "Shotgun Choke"))
	{
	render->繪製描邊文字(screenloc.x, screenloc.y,Color{255,131,52,255}, 顏色::顏色[顏色::普通物品顏色參數], pFont, VMProtectDecryptStringA(u8"散彈收束器[%d米]"), 距離);
	}
	else if (顯示篩選::狙擊托腮板 && !strcmp(缓存物品, "Cheek Pad (SR)"))
	{
	render->繪製描邊文字(screenloc.x, screenloc.y,Color{255,131,52,255}, 顏色::顏色[顏色::普通物品顏色參數], pFont, VMProtectDecryptStringA(u8"狙擊托腮板[%d米]"), 距離);
	}
	else if (顯示篩選::散彈子彈袋 && !strcmp(缓存物品, "Bullet Loops (SG)"))
	{
	render->繪製描邊文字(screenloc.x, screenloc.y,Color{255,131,52,255}, 顏色::顏色[顏色::普通物品顏色參數], pFont, VMProtectDecryptStringA(u8"散彈子彈袋[%d米]"), 距離);
	}
	else if (顯示篩選::狙擊子彈袋 && !strcmp(缓存物品, "Bullet Loops (Kar98k)"))
	{
	render->繪製描邊文字(screenloc.x, screenloc.y,Color{255,131,52,255}, 顏色::顏色[顏色::高級物品顏色參數], pFont, VMProtectDecryptStringA(u8"Kar98K子彈袋[%d米]"), 距離);
	}
	*/
}
void 保存配置()
{
	//創建
	char str[20000] = "C:\\輔助設置.ini";
	ifstream out(str);
	//保存
	ofstream fout;
	fout.open("C:\\輔助設置.ini", ios::trunc);

	//顯示相關設置
	
	fout << VMProtectDecryptStringA("[顯示相關設置]") << endl;
	fout << VMProtectDecryptStringA("顯示人物風格=") << 顯示相關設置::顯示人物風格 << endl;
	fout << VMProtectDecryptStringA("顯示人物血條=") << 顯示相關設置::顯示人物血條 << endl;
	fout << VMProtectDecryptStringA("顯示人物距離=") << 顯示相關設置::顯示人物距離 << endl;
	fout << VMProtectDecryptStringA("顯示地圖雷達=") << 顯示相關設置::顯示地圖雷達 << endl;
	fout << VMProtectDecryptStringA("附近敵人預警開關=") << 顯示相關設置::附近敵人預警開關 << endl;
	fout << VMProtectDecryptStringA("附近敵人預警距離=") << 顯示相關設置::附近敵人預警距離 << endl;
	fout << VMProtectDecryptStringA("人物最大顯示距離=") << 顯示相關設置::人物最大顯示距離 << endl;
	fout << VMProtectDecryptStringA("物品最大顯示距離=") << 顯示相關設置::物品最大顯示距離 << endl;
	fout << VMProtectDecryptStringA("載具最大顯示距離=") << 顯示相關設置::載具最大顯示距離 << endl;
	fout << VMProtectDecryptStringA("訊息顯示半徑=") << 顯示相關設置::訊息顯示半徑 << endl;
	fout << VMProtectDecryptStringA("物品透視=") << 顯示相關設置::物品透視 << endl;
	fout << VMProtectDecryptStringA("空投透視=") << 顯示相關設置::空投透視 << endl;
	fout << VMProtectDecryptStringA("骨灰盒透視=") << 顯示相關設置::骨灰盒透視 << endl;
	fout << VMProtectDecryptStringA("顯示槍=") << 顯示相關設置::顯示槍 << endl;
	fout << VMProtectDecryptStringA("顯示子彈=") << 顯示相關設置::顯示子彈 << endl;
	fout << VMProtectDecryptStringA("顯示配件=") << 顯示相關設置::顯示配件 << endl;
	fout << VMProtectDecryptStringA("顯示藥=") << 顯示相關設置::顯示藥 << endl;
	fout << VMProtectDecryptStringA("顯示倍鏡=") << 顯示相關設置::顯示倍鏡 << endl;
	fout << VMProtectDecryptStringA("顯示自訂=") << 顯示相關設置::顯示自訂 << endl;
	//射擊相關設置
	fout << VMProtectDecryptStringA("　") << endl;
	fout << VMProtectDecryptStringA("[射擊相關設置]") << endl;
	fout << VMProtectDecryptStringA("內存自瞄=") << 射擊相關設置::內存自瞄 << endl;
	fout << VMProtectDecryptStringA("射擊範圍=") << 射擊相關設置::射擊範圍 << endl;
	fout << VMProtectDecryptStringA("射擊距離=") << 射擊相關設置::射擊距離 << endl;
	fout << VMProtectDecryptStringA("位置參數=") << 射擊相關設置::位置參數 << endl;
	fout << VMProtectDecryptStringA("十字準心=") << 射擊相關設置::十字準心 << endl;
	fout << VMProtectDecryptStringA("可視射線=") << 射擊相關設置::可視射線 << endl;
	fout << VMProtectDecryptStringA("快速鎖頭=") << 射擊相關設置::快速鎖頭 << endl;
	fout << VMProtectDecryptStringA("機瞄放大=") << 射擊相關設置::機瞄放大 << endl;
	fout << VMProtectDecryptStringA("放大係數=") << 射擊相關設置::放大係數 << endl;
	fout << VMProtectDecryptStringA("清除抖動=") << 射擊相關設置::清除抖動 << endl;
	fout << VMProtectDecryptStringA("鎖定追蹤=") << 射擊相關設置::鎖定追蹤 << endl;
	fout << VMProtectDecryptStringA("是否鎖定=") << 射擊相關設置::是否鎖定 << endl;
	fout << VMProtectDecryptStringA("按鍵參數=") << 射擊相關設置::按鍵參數 << endl;
	//變態功能設置
	fout << VMProtectDecryptStringA("　") << endl;
	fout << VMProtectDecryptStringA("[變態功能設置]") << endl;
	fout << VMProtectDecryptStringA("上帝模式=") << 變態功能設置::上帝模式 << endl;
	fout << VMProtectDecryptStringA("肢體強化=") << 變態功能設置::肢體強化 << endl;
	fout << VMProtectDecryptStringA("無情瞬殺=") << 變態功能設置::無情瞬殺 << endl;
	fout << VMProtectDecryptStringA("超級連跳=") << 變態功能設置::超級連跳 << endl;
	fout << VMProtectDecryptStringA("跳躍穿牆=") << 變態功能設置::跳躍穿牆 << endl;
	fout << VMProtectDecryptStringA("跳躍高度=") << 變態功能設置::跳躍高度 << endl;
	fout << VMProtectDecryptStringA("瞬移空投=") << 變態功能設置::瞬移空投 << endl;
	fout << VMProtectDecryptStringA("瞬移載具=") << 變態功能設置::瞬移載具 << endl;
	//武器顯示篩選
	fout << VMProtectDecryptStringA("　") << endl;
	fout << VMProtectDecryptStringA("[武器顯示篩選]") << endl;
	fout << VMProtectDecryptStringA("AKM=") << 顯示篩選::AKM << endl;
	fout << VMProtectDecryptStringA("M416=") << 顯示篩選::M416 << endl;
	fout << VMProtectDecryptStringA("M16A4=") << 顯示篩選::M16A4 << endl;
	fout << VMProtectDecryptStringA("SCAR=") << 顯示篩選::SCAR << endl;
	fout << VMProtectDecryptStringA("VSS=") << 顯示篩選::VSS << endl;
	fout << VMProtectDecryptStringA("SKS=") << 顯示篩選::SKS << endl;
	fout << VMProtectDecryptStringA("MINI14=") << 顯示篩選::MINI14 << endl;
	fout << VMProtectDecryptStringA("KAR98K=") << 顯示篩選::KAR98K << endl;
	fout << VMProtectDecryptStringA("DP28=") << 顯示篩選::DP28 << endl;
	fout << VMProtectDecryptStringA("WIN94=") << 顯示篩選::WIN94 << endl;
	fout << VMProtectDecryptStringA("SAWED=") << 顯示篩選::SAWED << endl;
	fout << VMProtectDecryptStringA("UZI=") << 顯示篩選::UZI << endl;
	fout << VMProtectDecryptStringA("UMP9=") << 顯示篩選::UMP9 << endl;
	fout << VMProtectDecryptStringA("VECTOR=") << 顯示篩選::VECTOR << endl;
	fout << VMProtectDecryptStringA("TOMMYGUN=") << 顯示篩選::TOMMYGUN << endl;
	fout << VMProtectDecryptStringA("S12K=") << 顯示篩選::S12K << endl;
	fout << VMProtectDecryptStringA("S686=") << 顯示篩選::S686 << endl;
	fout << VMProtectDecryptStringA("S1897=") << 顯示篩選::S1897 << endl;
	fout << VMProtectDecryptStringA("CROSSBOW=") << 顯示篩選::CROSSBOW << endl;
	fout << VMProtectDecryptStringA("BerylM762=") << 顯示篩選::BerylM762 << endl;
	fout << VMProtectDecryptStringA("M24=") << 顯示篩選::M24 << endl;
	fout << VMProtectDecryptStringA("Mk47Mutan=") << 顯示篩選::Mk47Mutan << endl;
	fout << VMProtectDecryptStringA("QBU=") << 顯示篩選::QBU << endl;
	fout << VMProtectDecryptStringA("QBZ=") << 顯示篩選::QBZ << endl;
	fout << VMProtectDecryptStringA("SLR=") << 顯示篩選::SLR << endl;
	//配件顯示篩選
	fout << VMProtectDecryptStringA("　") << endl;
	fout << VMProtectDecryptStringA("[配件顯示篩選]") << endl;
	fout << VMProtectDecryptStringA("半截式握把=") << 顯示篩選::半截式握把 << endl;
	fout << VMProtectDecryptStringA("輕型握把=") << 顯示篩選::輕型握把 << endl;
	fout << VMProtectDecryptStringA("拇指握把=") << 顯示篩選::拇指握把 << endl;
	fout << VMProtectDecryptStringA("子彈556=") << 顯示篩選::子彈556 << endl;
	fout << VMProtectDecryptStringA("子彈762=") << 顯示篩選::子彈762 << endl;
	fout << VMProtectDecryptStringA("雷射瞄準器=") << 顯示篩選::雷射瞄準器 << endl;
	fout << VMProtectDecryptStringA("x3=") << 顯示篩選::x3 << endl;
	fout << VMProtectDecryptStringA("x6=") << 顯示篩選::x6 << endl;
	fout << VMProtectDecryptStringA("x2=") << 顯示篩選::x2 << endl;
	fout << VMProtectDecryptStringA("x4=") << 顯示篩選::x4 << endl;
	fout << VMProtectDecryptStringA("x8=") << 顯示篩選::x8 << endl;
	fout << VMProtectDecryptStringA("全息=") << 顯示篩選::全息 << endl;
	fout << VMProtectDecryptStringA("紅點=") << 顯示篩選::紅點 << endl;
	fout << VMProtectDecryptStringA("槍托=") << 顯示篩選::槍托 << endl;
	fout << VMProtectDecryptStringA("戰術槍托=") << 顯示篩選::戰術槍托 << endl;
	fout << VMProtectDecryptStringA("垂直握把=") << 顯示篩選::垂直握把 << endl;
	fout << VMProtectDecryptStringA("直角握把=") << 顯示篩選::直角握把 << endl;
	fout << VMProtectDecryptStringA("衝鋒消音=") << 顯示篩選::衝鋒消音 << endl;
	fout << VMProtectDecryptStringA("衝鋒消焰=") << 顯示篩選::衝鋒消焰 << endl;
	fout << VMProtectDecryptStringA("衝鋒補償=") << 顯示篩選::衝鋒補償 << endl;
	fout << VMProtectDecryptStringA("衝鋒快擴=") << 顯示篩選::衝鋒快擴 << endl;
	fout << VMProtectDecryptStringA("步槍消音=") << 顯示篩選::步槍消音 << endl;
	fout << VMProtectDecryptStringA("步槍消焰=") << 顯示篩選::步槍消焰 << endl;
	fout << VMProtectDecryptStringA("步槍補償=") << 顯示篩選::步槍補償 << endl;
	fout << VMProtectDecryptStringA("步槍快擴=") << 顯示篩選::步槍快擴 << endl;
	fout << VMProtectDecryptStringA("狙擊消音=") << 顯示篩選::狙擊消音 << endl;
	fout << VMProtectDecryptStringA("狙擊消焰=") << 顯示篩選::狙擊消焰 << endl;
	fout << VMProtectDecryptStringA("狙擊補償=") << 顯示篩選::狙擊補償 << endl;
	fout << VMProtectDecryptStringA("狙擊快擴=") << 顯示篩選::狙擊快擴 << endl;
	fout << VMProtectDecryptStringA("狙擊托腮板=") << 顯示篩選::狙擊托腮板 << endl;
	fout << VMProtectDecryptStringA("狙擊子彈袋=") << 顯示篩選::狙擊子彈袋 << endl;
	fout << VMProtectDecryptStringA("散彈收束器=") << 顯示篩選::散彈收束器 << endl;
	fout << VMProtectDecryptStringA("散彈子彈袋=") << 顯示篩選::散彈子彈袋 << endl;

	//其他顯示篩選
	fout << VMProtectDecryptStringA("　") << endl;
	fout << VMProtectDecryptStringA("[其他顯示篩選]") << endl;
	fout << VMProtectDecryptStringA("腎上腺素=") << 顯示篩選::腎上腺素 << endl;
	fout << VMProtectDecryptStringA("飲料=") << 顯示篩選::飲料 << endl;
	fout << VMProtectDecryptStringA("繃帶=") << 顯示篩選::繃帶 << endl;
	fout << VMProtectDecryptStringA("醫療箱=") << 顯示篩選::醫療箱 << endl;
	fout << VMProtectDecryptStringA("急救包=") << 顯示篩選::急救包 << endl;
	fout << VMProtectDecryptStringA("止痛藥=") << 顯示篩選::止痛藥 << endl;
	fout << VMProtectDecryptStringA("平底鍋=") << 顯示篩選::平底鍋 << endl;
	fout << VMProtectDecryptStringA("手榴彈=") << 顯示篩選::手榴彈 << endl;
	fout << VMProtectDecryptStringA("煙霧彈=") << 顯示篩選::煙霧彈 << endl;
	fout << VMProtectDecryptStringA("閃光彈=") << 顯示篩選::閃光彈 << endl;
	fout << VMProtectDecryptStringA("燃燒瓶=") << 顯示篩選::燃燒瓶 << endl;
	fout << VMProtectDecryptStringA("頭盔Lv.2=") << 顯示篩選::二級頭盔 << endl;
	fout << VMProtectDecryptStringA("頭盔Lv.3=") << 顯示篩選::三級頭盔 << endl;
	fout << VMProtectDecryptStringA("背包Lv.2=") << 顯示篩選::二級背包 << endl;
	fout << VMProtectDecryptStringA("背包Lv.3=") << 顯示篩選::三級背包 << endl;
	fout << VMProtectDecryptStringA("防彈衣Lv.2=") << 顯示篩選::二級防彈衣 << endl;
	fout << VMProtectDecryptStringA("防彈衣Lv.3=") << 顯示篩選::三級防彈衣 << endl;
	//顯示優化設置
	fout << VMProtectDecryptStringA("　") << endl;
	fout << VMProtectDecryptStringA("[顯示優化設置]") << endl;
	fout << VMProtectDecryptStringA("抽幀優化=") << 顯示優化設置::抽幀優化 << endl;
	fout << VMProtectDecryptStringA("優化延遲=") << 顯示優化設置::優化延遲 << endl;
	fout << VMProtectDecryptStringA("遊戲透明度=") << 顯示優化設置::遊戲透明度 << endl;
	fout << VMProtectDecryptStringA("遊戲加碼值=") << 顯示優化設置::遊戲加碼值 << endl;
	fout << VMProtectDecryptStringA("方框顏色參數=") << 顏色::方框顏色參數 << endl;
	fout << VMProtectDecryptStringA("骨骼顏色參數=") << 顏色::骨骼顏色參數 << endl;
	fout << VMProtectDecryptStringA("準心顏色參數=") << 顏色::準心顏色參數 << endl;
	fout << VMProtectDecryptStringA("射線顏色參數=") << 顏色::射線顏色參數 << endl;
	fout << VMProtectDecryptStringA("預警顏色參數=") << 顏色::預警顏色參數 << endl;
	fout << VMProtectDecryptStringA("車輛顏色參數=") << 顏色::車輛顏色參數 << endl;
	fout << VMProtectDecryptStringA("空投顏色參數=") << 顏色::空投顏色參數 << endl;
	fout << VMProtectDecryptStringA("骨灰盒顏色參數=") << 顏色::骨灰盒顏色參數 << endl;
	fout << VMProtectDecryptStringA("物品列表顏色參數=") << 顏色::物品列表顏色參數 << endl;
	fout << VMProtectDecryptStringA("槍械武器顏色參數=") << 顏色::槍械武器顏色參數 << endl;
	fout << VMProtectDecryptStringA("普通物品顏色參數=") << 顏色::普通物品顏色參數 << endl;
	fout << VMProtectDecryptStringA("高級物品顏色參數=") << 顏色::高級物品顏色參數 << endl;
	fout << VMProtectDecryptStringA("敵人近距離=") << 顯示相關設置::敵人近距離 << endl;
	fout << VMProtectDecryptStringA("敵人近距離顏色參數=") << 顏色::敵人近距離顏色參數 << endl;
	fout << VMProtectDecryptStringA("敵人中距離=") << 顯示相關設置::敵人中距離 << endl;
	fout << VMProtectDecryptStringA("敵人中距離顏色參數=") << 顏色::敵人中距離顏色參數 << endl;
	fout << VMProtectDecryptStringA("敵人遠距離=") << 顯示相關設置::敵人遠距離 << endl;
	fout << VMProtectDecryptStringA("敵人遠距離顏色參數=") << 顏色::敵人遠距離顏色參數 << endl;


	fout.close();

}
void 讀取配置()
{
	LPTSTR lpPath = new char[MAX_PATH];
	strcpy(lpPath, "C:\\輔助設置.ini");

	//顯示相關設置
	顯示相關設置::顯示人物風格 = GetPrivateProfileInt(VMProtectDecryptStringA("顯示相關設置"), VMProtectDecryptStringA("顯示人物風格"), 0, lpPath);
	顯示相關設置::顯示人物血條 = GetPrivateProfileInt(VMProtectDecryptStringA("顯示相關設置"), VMProtectDecryptStringA("顯示人物血條"), 0, lpPath);
	顯示相關設置::顯示人物距離 = GetPrivateProfileInt(VMProtectDecryptStringA("顯示相關設置"), VMProtectDecryptStringA("顯示人物距離"), 0, lpPath);
	顯示相關設置::顯示地圖雷達 = GetPrivateProfileInt(VMProtectDecryptStringA("顯示相關設置"), VMProtectDecryptStringA("顯示地圖雷達"), 0, lpPath);
	顯示相關設置::附近敵人預警開關 = GetPrivateProfileInt(VMProtectDecryptStringA("顯示相關設置"), VMProtectDecryptStringA("附近敵人預警開關"), 0, lpPath);
	顯示相關設置::附近敵人預警距離 = GetPrivateProfileInt(VMProtectDecryptStringA("顯示相關設置"), VMProtectDecryptStringA("附近敵人預警距離"), 0, lpPath);
	顯示相關設置::人物最大顯示距離 = GetPrivateProfileInt(VMProtectDecryptStringA("顯示相關設置"), VMProtectDecryptStringA("人物最大顯示距離"), 0, lpPath);
	顯示相關設置::物品最大顯示距離 = GetPrivateProfileInt(VMProtectDecryptStringA("顯示相關設置"), VMProtectDecryptStringA("物品最大顯示距離"), 0, lpPath);
	顯示相關設置::載具最大顯示距離 = GetPrivateProfileInt(VMProtectDecryptStringA("顯示相關設置"), VMProtectDecryptStringA("載具最大顯示距離"), 0, lpPath);
	顯示相關設置::訊息顯示半徑 = GetPrivateProfileInt(VMProtectDecryptStringA("顯示相關設置"), VMProtectDecryptStringA("訊息顯示半徑"), 0, lpPath);

	顯示相關設置::物品透視 = GetPrivateProfileInt(VMProtectDecryptStringA("顯示相關設置"), VMProtectDecryptStringA("物品透視"), 0, lpPath);
	顯示相關設置::空投透視 = GetPrivateProfileInt(VMProtectDecryptStringA("顯示相關設置"), VMProtectDecryptStringA("空投透視"), 0, lpPath);
	顯示相關設置::骨灰盒透視 = GetPrivateProfileInt(VMProtectDecryptStringA("顯示相關設置"), VMProtectDecryptStringA("骨灰盒透視"), 0, lpPath);
	顯示相關設置::顯示槍 = GetPrivateProfileInt(VMProtectDecryptStringA("顯示相關設置"), VMProtectDecryptStringA("顯示槍"), 0, lpPath);
	顯示相關設置::顯示子彈 = GetPrivateProfileInt(VMProtectDecryptStringA("顯示相關設置"), VMProtectDecryptStringA("顯示子彈"), 0, lpPath);
	顯示相關設置::顯示配件 = GetPrivateProfileInt(VMProtectDecryptStringA("顯示相關設置"), VMProtectDecryptStringA("顯示配件"), 0, lpPath);
	顯示相關設置::顯示藥 = GetPrivateProfileInt(VMProtectDecryptStringA("顯示相關設置"), VMProtectDecryptStringA("顯示藥"), 0, lpPath);
	顯示相關設置::顯示倍鏡 = GetPrivateProfileInt(VMProtectDecryptStringA("顯示相關設置"), VMProtectDecryptStringA("顯示倍鏡"), 0, lpPath);
	顯示相關設置::顯示自訂 = GetPrivateProfileInt(VMProtectDecryptStringA("顯示相關設置"), VMProtectDecryptStringA("顯示自訂"), 0, lpPath);
	//射擊相關設置
	射擊相關設置::內存自瞄 = GetPrivateProfileInt(VMProtectDecryptStringA("射擊相關設置"), VMProtectDecryptStringA("內存自瞄"), 0, lpPath);
	射擊相關設置::射擊範圍 = GetPrivateProfileInt(VMProtectDecryptStringA("射擊相關設置"), VMProtectDecryptStringA("射擊範圍"), 0, lpPath);
	射擊相關設置::射擊距離 = GetPrivateProfileInt(VMProtectDecryptStringA("射擊相關設置"), VMProtectDecryptStringA("射擊距離"), 0, lpPath);
	射擊相關設置::位置參數 = GetPrivateProfileInt(VMProtectDecryptStringA("射擊相關設置"), VMProtectDecryptStringA("位置參數"), 0, lpPath);
	射擊相關設置::十字準心 = GetPrivateProfileInt(VMProtectDecryptStringA("射擊相關設置"), VMProtectDecryptStringA("十字準心"), 0, lpPath);
	射擊相關設置::可視射線 = GetPrivateProfileInt(VMProtectDecryptStringA("射擊相關設置"), VMProtectDecryptStringA("可視射線"), 0, lpPath);
	射擊相關設置::快速鎖頭 = GetPrivateProfileInt(VMProtectDecryptStringA("射擊相關設置"), VMProtectDecryptStringA("快速鎖頭"), 0, lpPath);
	射擊相關設置::機瞄放大 = GetPrivateProfileInt(VMProtectDecryptStringA("射擊相關設置"), VMProtectDecryptStringA("機瞄放大"), 0, lpPath);
	射擊相關設置::放大係數 = GetPrivateProfileInt(VMProtectDecryptStringA("射擊相關設置"), VMProtectDecryptStringA("放大係數"), 0, lpPath);
	射擊相關設置::清除抖動 = GetPrivateProfileInt(VMProtectDecryptStringA("射擊相關設置"), VMProtectDecryptStringA("清除抖動"), 0, lpPath);
	射擊相關設置::鎖定追蹤 = GetPrivateProfileInt(VMProtectDecryptStringA("射擊相關設置"), VMProtectDecryptStringA("鎖定追蹤"), 0, lpPath);
	射擊相關設置::是否鎖定 = GetPrivateProfileInt(VMProtectDecryptStringA("射擊相關設置"), VMProtectDecryptStringA("是否鎖定"), 0, lpPath);
	射擊相關設置::按鍵參數 = GetPrivateProfileInt(VMProtectDecryptStringA("射擊相關設置"), VMProtectDecryptStringA("按鍵參數"), 0, lpPath);

	//變態功能設置
	變態功能設置::上帝模式 = GetPrivateProfileInt(VMProtectDecryptStringA("變態功能設置"), VMProtectDecryptStringA("上帝模式"), 0, lpPath);
	變態功能設置::肢體強化 = GetPrivateProfileInt(VMProtectDecryptStringA("變態功能設置"), VMProtectDecryptStringA("肢體強化"), 0, lpPath);
	變態功能設置::無情瞬殺 = GetPrivateProfileInt(VMProtectDecryptStringA("變態功能設置"), VMProtectDecryptStringA("無情瞬殺"), 0, lpPath);
	變態功能設置::超級連跳 = GetPrivateProfileInt(VMProtectDecryptStringA("變態功能設置"), VMProtectDecryptStringA("超級連跳"), 0, lpPath);
	變態功能設置::跳躍穿牆 = GetPrivateProfileInt(VMProtectDecryptStringA("變態功能設置"), VMProtectDecryptStringA("跳躍穿牆"), 0, lpPath);
	變態功能設置::跳躍高度 = GetPrivateProfileInt(VMProtectDecryptStringA("變態功能設置"), VMProtectDecryptStringA("跳躍高度"), 0, lpPath);
	變態功能設置::瞬移空投 = GetPrivateProfileInt(VMProtectDecryptStringA("變態功能設置"), VMProtectDecryptStringA("瞬移空投"), 0, lpPath);
	變態功能設置::瞬移載具 = GetPrivateProfileInt(VMProtectDecryptStringA("變態功能設置"), VMProtectDecryptStringA("瞬移載具"), 0, lpPath);

	//顯示優化設置
	顯示優化設置::抽幀優化 = GetPrivateProfileInt(VMProtectDecryptStringA("顯示優化設置"), VMProtectDecryptStringA("抽幀優化"), 0, lpPath);
	顯示優化設置::優化延遲 = GetPrivateProfileInt(VMProtectDecryptStringA("顯示優化設置"), VMProtectDecryptStringA("優化延遲"), 0, lpPath);
	顯示優化設置::遊戲透明度 = GetPrivateProfileInt(VMProtectDecryptStringA("顯示優化設置"), VMProtectDecryptStringA("遊戲透明度"), 65, lpPath);
	顯示優化設置::遊戲加碼值 = GetPrivateProfileInt(VMProtectDecryptStringA("顯示優化設置"), VMProtectDecryptStringA("遊戲加碼值"), 0, lpPath);
	顏色::方框顏色參數 = GetPrivateProfileInt(VMProtectDecryptStringA("顯示優化設置"), VMProtectDecryptStringA("方框顏色參數"), 0, lpPath);
	顏色::骨骼顏色參數 = GetPrivateProfileInt(VMProtectDecryptStringA("顯示優化設置"), VMProtectDecryptStringA("骨骼顏色參數"), 0, lpPath);
	顏色::準心顏色參數 = GetPrivateProfileInt(VMProtectDecryptStringA("顯示優化設置"), VMProtectDecryptStringA("準心顏色參數"), 0, lpPath);
	顏色::射線顏色參數 = GetPrivateProfileInt(VMProtectDecryptStringA("顯示優化設置"), VMProtectDecryptStringA("射線顏色參數"), 0, lpPath);
	顏色::預警顏色參數 = GetPrivateProfileInt(VMProtectDecryptStringA("顯示優化設置"), VMProtectDecryptStringA("預警顏色參數"), 0, lpPath);
	顏色::車輛顏色參數 = GetPrivateProfileInt(VMProtectDecryptStringA("顯示優化設置"), VMProtectDecryptStringA("車輛顏色參數"), 0, lpPath);
	顏色::空投顏色參數 = GetPrivateProfileInt(VMProtectDecryptStringA("顯示優化設置"), VMProtectDecryptStringA("空投顏色參數"), 0, lpPath);
	顏色::骨灰盒顏色參數 = GetPrivateProfileInt(VMProtectDecryptStringA("顯示優化設置"), VMProtectDecryptStringA("骨灰盒顏色參數"), 0, lpPath);
	顏色::物品列表顏色參數 = GetPrivateProfileInt(VMProtectDecryptStringA("顯示優化設置"), VMProtectDecryptStringA("物品列表顏色參數"), 0, lpPath);
	顏色::槍械武器顏色參數 = GetPrivateProfileInt(VMProtectDecryptStringA("顯示優化設置"), VMProtectDecryptStringA("槍械武器顏色參數"), 0, lpPath);
	顏色::普通物品顏色參數 = GetPrivateProfileInt(VMProtectDecryptStringA("顯示優化設置"), VMProtectDecryptStringA("普通物品顏色參數"), 0, lpPath);
	顏色::高級物品顏色參數 = GetPrivateProfileInt(VMProtectDecryptStringA("顯示優化設置"), VMProtectDecryptStringA("高級物品顏色參數"), 0, lpPath);
	顯示相關設置::敵人近距離 = GetPrivateProfileInt(VMProtectDecryptStringA("顯示優化設置"), VMProtectDecryptStringA("敵人近距離"), 200, lpPath);
	顏色::敵人近距離顏色參數 = GetPrivateProfileInt(VMProtectDecryptStringA("顯示優化設置"), VMProtectDecryptStringA("敵人近距離顏色參數"), 0, lpPath);
	顯示相關設置::敵人中距離 = GetPrivateProfileInt(VMProtectDecryptStringA("顯示優化設置"), VMProtectDecryptStringA("敵人中距離"), 500, lpPath);
	顏色::敵人中距離顏色參數 = GetPrivateProfileInt(VMProtectDecryptStringA("顯示優化設置"), VMProtectDecryptStringA("敵人中距離顏色參數"), 0, lpPath);
	顯示相關設置::敵人遠距離 = GetPrivateProfileInt(VMProtectDecryptStringA("顯示優化設置"), VMProtectDecryptStringA("敵人遠距離"), 1000, lpPath);
	顏色::敵人遠距離顏色參數 = GetPrivateProfileInt(VMProtectDecryptStringA("顯示優化設置"), VMProtectDecryptStringA("敵人遠距離顏色參數"), 0, lpPath);

	//其他显示筛选
	顯示篩選::腎上腺素 = GetPrivateProfileInt(VMProtectDecryptStringA("其他顯示篩選"), VMProtectDecryptStringA("腎上腺素"), 0, lpPath);
	顯示篩選::飲料 = GetPrivateProfileInt(VMProtectDecryptStringA("其他顯示篩選"), VMProtectDecryptStringA("飲料"), 0, lpPath);
	顯示篩選::繃帶 = GetPrivateProfileInt(VMProtectDecryptStringA("其他顯示篩選"), VMProtectDecryptStringA("繃帶"), 0, lpPath);
	顯示篩選::醫療箱 = GetPrivateProfileInt(VMProtectDecryptStringA("其他顯示篩選"), VMProtectDecryptStringA("醫療箱"), 0, lpPath);
	顯示篩選::急救包 = GetPrivateProfileInt(VMProtectDecryptStringA("其他顯示篩選"), VMProtectDecryptStringA("急救包"), 0, lpPath);
	顯示篩選::止痛藥 = GetPrivateProfileInt(VMProtectDecryptStringA("其他顯示篩選"), VMProtectDecryptStringA("止痛藥"), 0, lpPath);
	顯示篩選::平底鍋 = GetPrivateProfileInt(VMProtectDecryptStringA("其他顯示篩選"), VMProtectDecryptStringA("平底鍋"), 0, lpPath);
	顯示篩選::手榴彈 = GetPrivateProfileInt(VMProtectDecryptStringA("其他顯示篩選"), VMProtectDecryptStringA("手榴彈"), 0, lpPath);
	顯示篩選::煙霧彈 = GetPrivateProfileInt(VMProtectDecryptStringA("其他顯示篩選"), VMProtectDecryptStringA("煙霧彈"), 0, lpPath);
	顯示篩選::閃光彈 = GetPrivateProfileInt(VMProtectDecryptStringA("其他顯示篩選"), VMProtectDecryptStringA("閃光彈"), 0, lpPath);
	顯示篩選::燃燒瓶 = GetPrivateProfileInt(VMProtectDecryptStringA("其他顯示篩選"), VMProtectDecryptStringA("燃燒瓶"), 0, lpPath);
	顯示篩選::二級頭盔 = GetPrivateProfileInt(VMProtectDecryptStringA("其他顯示篩選"), VMProtectDecryptStringA("頭盔Lv.2"), 0, lpPath);
	顯示篩選::三級頭盔 = GetPrivateProfileInt(VMProtectDecryptStringA("其他顯示篩選"), VMProtectDecryptStringA("頭盔Lv.3"), 0, lpPath);
	顯示篩選::二級背包 = GetPrivateProfileInt(VMProtectDecryptStringA("其他顯示篩選"), VMProtectDecryptStringA("背包Lv.2"), 0, lpPath);
	顯示篩選::三級背包 = GetPrivateProfileInt(VMProtectDecryptStringA("其他顯示篩選"), VMProtectDecryptStringA("背包Lv.3"), 0, lpPath);
	顯示篩選::二級防彈衣 = GetPrivateProfileInt(VMProtectDecryptStringA("其他顯示篩選"), VMProtectDecryptStringA("防彈衣Lv.2"), 0, lpPath);
	顯示篩選::三級防彈衣 = GetPrivateProfileInt(VMProtectDecryptStringA("其他顯示篩選"), VMProtectDecryptStringA("防彈衣Lv.3"), 0, lpPath);

	//顯示篩選
	顯示篩選::AKM = GetPrivateProfileInt(VMProtectDecryptStringA("武器顯示篩選"), VMProtectDecryptStringA("AKM"), 0, lpPath);
	顯示篩選::M416 = GetPrivateProfileInt(VMProtectDecryptStringA("武器顯示篩選"), VMProtectDecryptStringA("M416"), 0, lpPath);
	顯示篩選::M16A4 = GetPrivateProfileInt(VMProtectDecryptStringA("武器顯示篩選"), VMProtectDecryptStringA("M16A4"), 0, lpPath);
	顯示篩選::SCAR = GetPrivateProfileInt(VMProtectDecryptStringA("武器顯示篩選"), VMProtectDecryptStringA("SCAR"), 0, lpPath);
	顯示篩選::VSS = GetPrivateProfileInt(VMProtectDecryptStringA("武器顯示篩選"), VMProtectDecryptStringA("VSS"), 0, lpPath);
	顯示篩選::SKS = GetPrivateProfileInt(VMProtectDecryptStringA("武器顯示篩選"), VMProtectDecryptStringA("SKS"), 0, lpPath);
	顯示篩選::MINI14 = GetPrivateProfileInt(VMProtectDecryptStringA("武器顯示篩選"), VMProtectDecryptStringA("MINI14"), 0, lpPath);
	顯示篩選::KAR98K = GetPrivateProfileInt(VMProtectDecryptStringA("武器顯示篩選"), VMProtectDecryptStringA("KAR98K"), 0, lpPath);
	顯示篩選::DP28 = GetPrivateProfileInt(VMProtectDecryptStringA("武器顯示篩選"), VMProtectDecryptStringA("DP28"), 0, lpPath);
	顯示篩選::WIN94 = GetPrivateProfileInt(VMProtectDecryptStringA("武器顯示篩選"), VMProtectDecryptStringA("WIN94"), 0, lpPath);
	顯示篩選::SAWED = GetPrivateProfileInt(VMProtectDecryptStringA("武器顯示篩選"), VMProtectDecryptStringA("SAWED"), 0, lpPath);
	顯示篩選::UZI = GetPrivateProfileInt(VMProtectDecryptStringA("武器顯示篩選"), VMProtectDecryptStringA("UZI"), 0, lpPath);
	顯示篩選::UMP9 = GetPrivateProfileInt(VMProtectDecryptStringA("武器顯示篩選"), VMProtectDecryptStringA("UMP9"), 0, lpPath);
	顯示篩選::VECTOR = GetPrivateProfileInt(VMProtectDecryptStringA("武器顯示篩選"), VMProtectDecryptStringA("VECTOR"), 0, lpPath);
	顯示篩選::TOMMYGUN = GetPrivateProfileInt(VMProtectDecryptStringA("武器顯示篩選"), VMProtectDecryptStringA("TOMMYGUN"), 0, lpPath);
	顯示篩選::S12K = GetPrivateProfileInt(VMProtectDecryptStringA("武器顯示篩選"), VMProtectDecryptStringA("S12K"), 0, lpPath);
	顯示篩選::S686 = GetPrivateProfileInt(VMProtectDecryptStringA("武器顯示篩選"), VMProtectDecryptStringA("S686"), 0, lpPath);
	顯示篩選::S1897 = GetPrivateProfileInt(VMProtectDecryptStringA("武器顯示篩選"), VMProtectDecryptStringA("S1897"), 0, lpPath);
	顯示篩選::CROSSBOW = GetPrivateProfileInt(VMProtectDecryptStringA("武器顯示篩選"), VMProtectDecryptStringA("CROSSBOW"), 0, lpPath);
	顯示篩選::BerylM762 = GetPrivateProfileInt(VMProtectDecryptStringA("武器顯示篩選"), VMProtectDecryptStringA("BerylM762"), 0, lpPath);
	顯示篩選::M24 = GetPrivateProfileInt(VMProtectDecryptStringA("武器顯示篩選"), VMProtectDecryptStringA("M24"), 0, lpPath);
	顯示篩選::Mk47Mutan = GetPrivateProfileInt(VMProtectDecryptStringA("武器顯示篩選"), VMProtectDecryptStringA("Mk47Mutan"), 0, lpPath);
	顯示篩選::QBU = GetPrivateProfileInt(VMProtectDecryptStringA("武器顯示篩選"), VMProtectDecryptStringA("QBU"), 0, lpPath);
	顯示篩選::QBZ = GetPrivateProfileInt(VMProtectDecryptStringA("武器顯示篩選"), VMProtectDecryptStringA("QBZ"), 0, lpPath);
	顯示篩選::SLR = GetPrivateProfileInt(VMProtectDecryptStringA("武器顯示篩選"), VMProtectDecryptStringA("SLR"), 0, lpPath);

	顯示篩選::半截式握把 = GetPrivateProfileInt(VMProtectDecryptStringA("配件顯示篩選"), VMProtectDecryptStringA("半截式握把"), 0, lpPath);
	顯示篩選::輕型握把 = GetPrivateProfileInt(VMProtectDecryptStringA("配件顯示篩選"), VMProtectDecryptStringA("輕型握把"), 0, lpPath);
	顯示篩選::拇指握把 = GetPrivateProfileInt(VMProtectDecryptStringA("配件顯示篩選"), VMProtectDecryptStringA("拇指握把"), 0, lpPath);
	顯示篩選::子彈556 = GetPrivateProfileInt(VMProtectDecryptStringA("配件顯示篩選"), VMProtectDecryptStringA("子彈556"), 0, lpPath);
	顯示篩選::子彈762 = GetPrivateProfileInt(VMProtectDecryptStringA("配件顯示篩選"), VMProtectDecryptStringA("子彈762"), 0, lpPath);
	顯示篩選::雷射瞄準器 = GetPrivateProfileInt(VMProtectDecryptStringA("配件顯示篩選"), VMProtectDecryptStringA("雷射瞄準器"), 0, lpPath);
	顯示篩選::x3 = GetPrivateProfileInt(VMProtectDecryptStringA("配件顯示篩選"), VMProtectDecryptStringA("x3"), 0, lpPath);
	顯示篩選::x6 = GetPrivateProfileInt(VMProtectDecryptStringA("配件顯示篩選"), VMProtectDecryptStringA("x6"), 0, lpPath);
	顯示篩選::x2 = GetPrivateProfileInt(VMProtectDecryptStringA("配件顯示篩選"), VMProtectDecryptStringA("x2"), 0, lpPath);
	顯示篩選::x4 = GetPrivateProfileInt(VMProtectDecryptStringA("配件顯示篩選"), VMProtectDecryptStringA("x4"), 0, lpPath);
	顯示篩選::x8 = GetPrivateProfileInt(VMProtectDecryptStringA("配件顯示篩選"), VMProtectDecryptStringA("x8"), 0, lpPath);
	顯示篩選::全息 = GetPrivateProfileInt(VMProtectDecryptStringA("配件顯示篩選"), VMProtectDecryptStringA("全息"), 0, lpPath);
	顯示篩選::紅點 = GetPrivateProfileInt(VMProtectDecryptStringA("配件顯示篩選"), VMProtectDecryptStringA("紅點"), 0, lpPath);
	顯示篩選::槍托 = GetPrivateProfileInt(VMProtectDecryptStringA("配件顯示篩選"), VMProtectDecryptStringA("槍托"), 0, lpPath);
	顯示篩選::戰術槍托 = GetPrivateProfileInt(VMProtectDecryptStringA("配件顯示篩選"), VMProtectDecryptStringA("戰術槍托"), 0, lpPath);
	顯示篩選::垂直握把 = GetPrivateProfileInt(VMProtectDecryptStringA("配件顯示篩選"), VMProtectDecryptStringA("垂直握把"), 0, lpPath);
	顯示篩選::直角握把 = GetPrivateProfileInt(VMProtectDecryptStringA("配件顯示篩選"), VMProtectDecryptStringA("直角握把"), 0, lpPath);
	顯示篩選::衝鋒消音 = GetPrivateProfileInt(VMProtectDecryptStringA("配件顯示篩選"), VMProtectDecryptStringA("衝鋒消音"), 0, lpPath);
	顯示篩選::衝鋒消焰 = GetPrivateProfileInt(VMProtectDecryptStringA("配件顯示篩選"), VMProtectDecryptStringA("衝鋒消焰"), 0, lpPath);
	顯示篩選::衝鋒補償 = GetPrivateProfileInt(VMProtectDecryptStringA("配件顯示篩選"), VMProtectDecryptStringA("衝鋒補償"), 0, lpPath);
	顯示篩選::衝鋒快擴 = GetPrivateProfileInt(VMProtectDecryptStringA("配件顯示篩選"), VMProtectDecryptStringA("衝鋒快擴"), 0, lpPath);
	顯示篩選::步槍消音 = GetPrivateProfileInt(VMProtectDecryptStringA("配件顯示篩選"), VMProtectDecryptStringA("步槍消音"), 0, lpPath);
	顯示篩選::步槍消焰 = GetPrivateProfileInt(VMProtectDecryptStringA("配件顯示篩選"), VMProtectDecryptStringA("步槍消焰"), 0, lpPath);
	顯示篩選::步槍補償 = GetPrivateProfileInt(VMProtectDecryptStringA("配件顯示篩選"), VMProtectDecryptStringA("步槍補償"), 0, lpPath);
	顯示篩選::步槍快擴 = GetPrivateProfileInt(VMProtectDecryptStringA("配件顯示篩選"), VMProtectDecryptStringA("步槍快擴"), 0, lpPath);
	顯示篩選::狙擊消音 = GetPrivateProfileInt(VMProtectDecryptStringA("配件顯示篩選"), VMProtectDecryptStringA("狙擊消音"), 0, lpPath);
	顯示篩選::狙擊消焰 = GetPrivateProfileInt(VMProtectDecryptStringA("配件顯示篩選"), VMProtectDecryptStringA("狙擊消焰"), 0, lpPath);
	顯示篩選::狙擊補償 = GetPrivateProfileInt(VMProtectDecryptStringA("配件顯示篩選"), VMProtectDecryptStringA("狙擊補償"), 0, lpPath);
	顯示篩選::狙擊快擴 = GetPrivateProfileInt(VMProtectDecryptStringA("配件顯示篩選"), VMProtectDecryptStringA("狙擊快擴"), 0, lpPath);
	顯示篩選::狙擊托腮板 = GetPrivateProfileInt(VMProtectDecryptStringA("配件顯示篩選"), VMProtectDecryptStringA("狙擊托腮板"), 0, lpPath);
	顯示篩選::狙擊子彈袋 = GetPrivateProfileInt(VMProtectDecryptStringA("配件顯示篩選"), VMProtectDecryptStringA("狙擊子彈袋"), 0, lpPath);
	顯示篩選::散彈收束器 = GetPrivateProfileInt(VMProtectDecryptStringA("配件顯示篩選"), VMProtectDecryptStringA("散彈收束器"), 0, lpPath);
	顯示篩選::散彈子彈袋 = GetPrivateProfileInt(VMProtectDecryptStringA("配件顯示篩選"), VMProtectDecryptStringA("散彈子彈袋"), 0, lpPath);

}





#include <Psapi.h>


#define INRANGE(x,a,b)    (x >= a && x <= b) 
#define getBits( x )    (INRANGE((x&(~0x20)),'A','F') ? ((x&(~0x20)) - 'A' + 0xA) : (INRANGE(x,'0','9') ? x - '0' : 0))
#define getByte( x )    (getBits(x[0]) << 4 | getBits(x[1]))


HMODULE Tsl = 0;
MODULEINFO TslInfo;

uintptr_t GetBase() { return (uintptr_t)Tsl; }
uintptr_t GetEnd() { return GetBase() + TslInfo.SizeOfImage; }

uintptr_t FindPattern(const char* pattern)
{
	char* pat = const_cast<char*>(pattern);
	uintptr_t firstMatch = 0;
	uintptr_t rangeEnd = GetEnd();

	for (auto pCur = GetBase(); pCur < rangeEnd; pCur++)
	{
		if (!*pat)
			return firstMatch;

		if (*(BYTE*)pat == '\?' || *(BYTE*)pCur == getByte(pat))
		{
			if (!firstMatch)
				firstMatch = pCur;

			if (!pat[2])
				return firstMatch;

			if (*(BYTE*)pat == '\?')
				pat += 2;
			else
				pat += 3;
		}
		else
		{
			pat = const_cast<char*>(pattern);
			firstMatch = 0;
		}
	}

	return 0;
}

void LoadModule2()
{
	HMODULE hMods[1024];
	DWORD cb;
//	HMODULE MiNFO = GetModuleHandleC("TslGame.exe");
//	cout << hex << MiNFO << endl;
	if (EnumProcessModulesEx(FindWindowA("UnrealWindow", NULL), hMods, sizeof(hMods), &cb, LIST_MODULES_64BIT))
	{
		Tsl = hMods[0];
		GetModuleInformation(FindWindowA("UnrealWindow", NULL), Tsl, &TslInfo, sizeof(MODULEINFO));
		cout << hex << Tsl << endl;
	}
}