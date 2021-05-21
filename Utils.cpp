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
HWND �[�򴰿ھ��;
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
int ��Ʒ[2];
int ����[3];
int �I܇[4];
int Ħ��[8];
int ԽҰ[10];
int ��ʿ[5];
int Ƥ��[12];
int ��[2];
int �[ͧ[4];
int ��܇[12];
int �_��[5];
int ��܇[5];
int ����Ħ��[6];
int �w�C[7];
int ��Ͷ[1];
int ������Ͷ[1];
int ����܇[3];
int Grenade[1];
int Molotov[1];
int �ǻҺ�;



D3DXMATRIX Matrix(Vector3 rot, Vector3 origin = Vector3(0, 0, 0))
{
	float radPitch = (rot.x * float(���c����) / 180.f);
	float radYaw = (rot.y * float(���c����) / 180.f);
	float radRoll = (rot.z * float(���c����) / 180.f);

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
	ULONG64 Camera_Cache = ȫ��׃��::PlayerCameraManager;

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
		//	cout << "���Ƴɹ�" << endl;
		//}
		//}


	}



	return Screenlocation;
}
Vector3 WorldToScreen(Vector3 WorldLocation) {
	RECT rc;

	Vector3 Screenlocation = Vector3(0, 0, 0);
	ULONG64 Camera_Cache = ȫ��׃��::PlayerCameraManager;
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
		//	cout << "���Ƴɹ�" << endl;
		//}
		//}


	}



	return Screenlocation;
}


Vector3 GetLocalPlayerPos()
{
	Vector3 ���w���˔���;
	if (!driver)
		return ���w���˔���;
	auto rootcomp = DecryptGeneral(driver->RPM<ULONG64>(ȫ��׃��::pPawn + actor::RootComponent));

	���w���˔��� = driver->RPM<Vector3>(rootcomp + actor::_Pos);

	return ���w���˔���;
}

Vector3 ȡ���w���˔���(ULONG64 ���w)
{
	Vector3 ���w���˔���;
	if (!driver)
		return ���w���˔���;

	auto rootcomp = DecryptGeneral(driver->RPM<ULONG64>(���w + actor::RootComponent));

	���w���˔��� = driver->RPM<Vector3>(rootcomp + actor::_Pos);


	return ���w���˔���;
}

float GetLocalPlayerHealth()
{
	if (!driver)
		return 0.f;
	auto pawn = ȫ��׃��::pPawn;
	return driver->RPM<float>(pawn + actor::health);
}

float ȡ���wѪ��(ULONG64 pAActor)
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

	
	ULONG64 tmp = driver->RPM<ULONG64>(ȫ��׃��::pGameBase + offset::GNames);
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
	


	//return  driver->RPM<ULONG64>(ȫ��׃��::pGameBase + offset::GNames);
}



BOOL CacheNames()
{
	string name = { NULL };
	ȫ��׃��::pGn = FindGnames();
	std::ofstream mycout("C:\\names.txt");//driver->RPM<ULONG64>


	for (int i = 0, c1 = 0, c2 = 0, c3 = 0, c4 = 0, c5 = 0, c6 = 0, c7 = 0, c8 = 0, c9 = 0, c10 = 0, c11 = 0, c12 = 0, c13 = 0, c14 = 0, c15 = 0, c17 = 0,c18 = 0,c19 = 0,c20 = 0,c21 = 0; i < 200000; i++)
	{
		mycout << i << "||" << GetNameFromID(ȫ��׃��::pGn,i) << std::endl;
		if (c1 == 1 && c2 == 3 && c3 == 4 && c4 == 8 && c5 == 10 && c6 == 2 && c7 == 12 && c8 == 5 && c9 == 2 && c10 == 4 && c11 == 12 && c12 == 5 && c13 == 5 && c14 == 6 && c15 == 7 && c17 == 1 && c18==1 &&c19==3 && c20 == 1 && c21 == 1 && �ǻҺ� != 0)
		{
			//	mycout.close();
			cout << "�ɹ��������Ќ��w���Q" << endl;
			return true;
		}
	
		name = GetNameFromID(ȫ��׃��::pGn, i);

		

		//���
		if (name == VMProtectDecryptStringA("BP_PlayerPawnPC_C"))
		{
			
			Actorids[c1++] = i;
		}
		//����
		if (name == VMProtectDecryptStringA("Uaz_A_01_C") || name == VMProtectDecryptStringA("Uaz_B_01_C") || name == VMProtectDecryptStringA("Uaz_C_01_C"))
		{
			//	cout << name << " " << i << endl;
			����[c2++] = i;
		}
		//�I܇
		if (name == VMProtectDecryptStringA("Dacia_A_01_v2_C") || name == VMProtectDecryptStringA("Dacia_A_02_v2_C") || name == VMProtectDecryptStringA("Dacia_A_03_v2_C") || name == VMProtectDecryptStringA("Dacia_A_04_v2_C"))
		{
			//	cout << name << " " << i << endl;
			�I܇[c3++] = i;
		}
		//Ħ��܇
		if (name == VMProtectDecryptStringA("ABP_Motorbike_03_C") || name == VMProtectDecryptStringA("ABP_Motorbike_04_C") || name == VMProtectDecryptStringA("ABP_Motorbike_04_Sidecar_C")		|| name == VMProtectDecryptStringA("BP_Motorbike_03_C") || name == VMProtectDecryptStringA("BP_Motorbike_04_C") || name == VMProtectDecryptStringA("BP_Motorbike_04_Desert_C")	|| name == VMProtectDecryptStringA("BP_Motorbike_04_SideCar_C") || name == VMProtectDecryptStringA("BP_Motorbike_04_SideCar_Desert_C"))
		{
			//	cout << name << " " << i << endl;
			Ħ��[c4++] = i;
		}
		//ԽҰ
		if (name == VMProtectDecryptStringA("Buggy_A_01_C") || name == VMProtectDecryptStringA("Buggy_A_02_C") || name == VMProtectDecryptStringA("Buggy_A_03_C")|| name == VMProtectDecryptStringA("Buggy_A_04_C") || name == VMProtectDecryptStringA("Buggy_A_05_C") || name == VMProtectDecryptStringA("Buggy_A_06_C")|| name == VMProtectDecryptStringA("Buggy_A_Burned_C") || name == VMProtectDecryptStringA("Buggy_C") || name == VMProtectDecryptStringA("ABP_Buggy_02") || name == VMProtectDecryptStringA("ABP_Buggy_02_C"))
		{
			//cout << name << " " << i << endl;
			ԽҰ[c5++] = i;
		}
		//��Ʒ
		if (name == VMProtectDecryptStringA("DroppedItemInteractionComponent") || name == VMProtectDecryptStringA("DroppedItemGroup"))
		{
			//cout << name << " " << i << endl;
			��Ʒ[c6++] = i;
		}
		//Ƥ��
		if (name == VMProtectDecryptStringA("BP_PickupTruck_A_C") || name == VMProtectDecryptStringA("BP_PickupTruck_A_01_C") || name == VMProtectDecryptStringA("BP_PickupTruck_A_02_C")|| name == VMProtectDecryptStringA("BP_PickupTruck_A_03_C") || name == VMProtectDecryptStringA("BP_PickupTruck_A_04_C") || name == VMProtectDecryptStringA("BP_PickupTruck_A_05_C")|| name == VMProtectDecryptStringA("BP_PickupTruck_B_C") || name == VMProtectDecryptStringA("BP_PickupTruck_B_01_C") || name == VMProtectDecryptStringA("BP_PickupTruck_B_02_C")|| name == VMProtectDecryptStringA("BP_PickupTruck_B_03_C") || name == VMProtectDecryptStringA("BP_PickupTruck_B_04_C") || name == VMProtectDecryptStringA("BP_PickupTruck_B_05_C"))
		{
			//cout << name << " " << i << endl;
			Ƥ��[c7++] = i;
		}
		//��ʿ
		if (name == VMProtectDecryptStringA("ABP_Minibus_02_C") || name == VMProtectDecryptStringA("BP_MiniBus_C") || name == VMProtectDecryptStringA("BP_Van_A_01_C")	|| name == VMProtectDecryptStringA("BP_Van_A_02_C") || name == VMProtectDecryptStringA("BP_Van_A_03_C"))
		{
			//cout << name << " " << i << endl;
			��ʿ[c8++] = i;
		}
		//��
		if (name == VMProtectDecryptStringA("Boat_PG117_C") || name == VMProtectDecryptStringA("Boat_PG117_Animation_C"))
		{
			//cout << "�ҵ���(����)"<< name << " " << i << endl;
			��[c9++] = i;
		}
		//�[ͧ
		if (name == VMProtectDecryptStringA("AquaRail_C") || name == VMProtectDecryptStringA("AquaRail_A_01_C") || name == VMProtectDecryptStringA("AquaRail_A_02_C") || name == VMProtectDecryptStringA("AquaRail_A_03_C"))
		{
			//cout << "�ҵ��[ͧ(����)" << name << " " << i << endl;
			�[ͧ[c10++] = i;
		}
		//��܇
		if (name == VMProtectDecryptStringA("ABP_Mirado_C") || name == VMProtectDecryptStringA("BP_Mirado_C") || name == VMProtectDecryptStringA("BP_Mirado_A_01_C")|| name == VMProtectDecryptStringA("BP_Mirado_A_02_C") || name == VMProtectDecryptStringA("BP_Mirado_A_03_C") || name == VMProtectDecryptStringA("BP_Mirado_A_03_Esports_C")|| name == VMProtectDecryptStringA("BP_Mirado_Open_C") || name == VMProtectDecryptStringA("BP_Mirado_Open_01_C") || name == VMProtectDecryptStringA("BP_Mirado_Open_02_C")|| name == VMProtectDecryptStringA("BP_Mirado_Open_03_C") || name == VMProtectDecryptStringA("BP_Mirado_Open_04_C") || name == VMProtectDecryptStringA("BP_Mirado_A_04_C"))
		{
			//cout << name << " " << i << endl;
			��܇[c11++] = i;
		}
		//�_��
		if (name == VMProtectDecryptStringA("ABP_Rony_C") || name == VMProtectDecryptStringA("BP_M_Rony_A_01_C") || name == VMProtectDecryptStringA("BP_Rony_C")|| name == VMProtectDecryptStringA("BP_M_Rony_A_02_C") || name == VMProtectDecryptStringA("BP_M_Rony_A_03_C"))
		{
			//cout << "�_�� " << name << " " << i << endl;
			�_��[c12++] = i;
		}
		//��܇
		if (name == VMProtectDecryptStringA("ABP_TukTuk_C") || name == VMProtectDecryptStringA("BP_TukTukTuk_C") || name == VMProtectDecryptStringA("BP_TukTukTuk_A_01_C")		|| name == VMProtectDecryptStringA("BP_TukTukTuk_A_02_C") || name == VMProtectDecryptStringA("BP_TukTukTuk_A_03_C"))
		{
			//cout<<"��܇ " << name << " " << i << endl;
			��܇[c13++] = i;
		}
		//����Ħ��
		if (name == VMProtectDecryptStringA("ABP_Scooter_C") || name == VMProtectDecryptStringA("BP_Scooter_C") || name == VMProtectDecryptStringA("BP_Scooter_01_A_C")|| name == VMProtectDecryptStringA("BP_Scooter_02_A_C") || name == VMProtectDecryptStringA("BP_Scooter_03_A_C") || name == VMProtectDecryptStringA("BP_Scooter_04_A_C"))
        {
			//cout << "����Ħ�� " << name << " " << i << endl;
			����Ħ��[c14++] = i;
		}
		//�w�C
		//121414��AircraftCarePackage_Test_ChildLowSound_C  TransportAircraft_Seat_C
		if (name == VMProtectDecryptStringA("AircraftCarePackage_Test_C") || name == VMProtectDecryptStringA("TransportAircraft_Seat_C") || name == VMProtectDecryptStringA("DummyTransportAircraft_C")
			|| name == VMProtectDecryptStringA("AircraftCarePackage_Desert_C") | name == VMProtectDecryptStringA("AircraftCarePackage_Test_ChildLowSound_C")
			|| name == VMProtectDecryptStringA("AircraftCarePackage_FlareGun_C") || name == VMProtectDecryptStringA("AircraftCarePackage_Vehicle_C")) {

			//cout << "�w�C " << name << " " << i << endl;
			�w�C[c15++] = i;
		}
		//��Ͷ
		if (name == VMProtectDecryptStringA("Carapackage_RedBox_C")) {
			��Ͷ[c17++] = i;
		}
		//������Ͷ
		if (name == VMProtectDecryptStringA("Carapackage_FlareGun_C")) {

			������Ͷ[c18++] = i;
		}
		//����܇
		if (name == VMProtectDecryptStringA("BP_VehicleDrop_C") || name == VMProtectDecryptStringA("BP_VehicleDrop_UAZ_C") || name == VMProtectDecryptStringA("Uaz_Armored_C") ) {

			����܇[c19++] = i;
		}
		//����
		if (name == VMProtectDecryptStringA("ProjGrenade_C")) {//Weapon_Grenade_C �����е�  ProjGrenade_C�ǁG��ȥ��
			//cout << name << " " << i << endl;
			Grenade[c20++] = i;
		}
		//ȼ��ƿ
		if (name == VMProtectDecryptStringA("ProjMolotov_C")) { //Weapon_Molotov_C �������е� ProjMolotov_C�ǁG��ȥ��
			//cout << name << " " << i << endl;
			Molotov[c21++] = i;
		}
		//�ǻҺ�
		if (name == VMProtectDecryptStringA("DeathDropItemPackage_C")) {
			//cout << name << " " << i << endl;
			�ǻҺ� = i;
		}

	}
	mycout.close();
	return false;
}

int �Ƿ���(int ID)
{
	for (int i = 0; i < 3; i++)
		if (ID == ����[i])
			return 1;
	return 0;
}

int �Ƿ��I܇(int ID)
{
	for (int i = 0; i < 4; i++)
		if (ID == �I܇[i])
			return 1;
	return 0;
}

int �Ƿ�ԽҰ(int ID)
{
	for (int i = 0; i < 10; i++)
		if (ID == ԽҰ[i])
			return 1;
	return 0;
}

int �Ƿ�Ħ��(int ID)
{
	for (int i = 0; i < 8; i++)
		if (ID == Ħ��[i])
			return 1;
	return 0;
}
int �Ƿ�Ƥ��(int ID)
{
	for (int i = 0; i < 12; i++)
		if (ID == Ƥ��[i])
			return 1;
	return 0;
}

int �Ƿ��ʿ(int ID)
{
	for (int i = 0; i < 5; i++)
		if (ID == ��ʿ[i])
			return 1;
	return 0;
}

int �Ƿ��Ͷ(int ID)
{
	for (int i = 0; i < 1; i++)
		if (ID == ��Ͷ[i])
			return 1;
	return 0;
}
int �Ƿ񳬼���Ͷ(int ID)
{
	for (int i = 0; i < 1; i++)
		if (ID == ������Ͷ[i])
			return 1;
	return 0;
}

int �Ƿ�ǻҺ�(int ID)
{
	return ID == �ǻҺ�;
}

int �Ƿ��(int ID)
{
	for (int i = 0; i < 2; i++)
		if (ID == ��[i])
			return 1;
	return 0;
}

int �Ƿ��[ͧ(int ID)
{
	for (int i = 0; i < 4; i++)
		if (ID == �[ͧ[i])
			return 1;
	return 0;
}
int �Ƿ���܇(int ID)
{
	for (int i = 0; i < 12; i++)
		if (ID == ��܇[i])
			return 1;
	return 0;
}
int �Ƿ��_��(int ID)
{
	for (int i = 0; i < 5; i++)
		if (ID == �_��[i])
			return 1;
	return 0;
}
int �Ƿ���܇(int ID)
{
	for (int i = 0; i < 5; i++)
		if (ID == ��܇[i])
			return 1;
	return 0;
}
int �Ƿ�����Ħ��(int ID)
{
	for (int i = 0; i < 6; i++)
		if (ID == ����Ħ��[i])
			return 1;
	return 0;
}
int �Ƿ����܇(int ID)
{
	for (int i = 0; i < 3; i++)
		if (ID == ����܇[i])
			return 1;
	return 0;
}
int �Ƿ�����(int ID)
{
	for (int i = 0; i < 1; i++)
		if (ID == Grenade[i])
			return 1;
	return 0;
}
int �Ƿ�ȼ��ƿ(int ID)
{
	for (int i = 0; i < 1; i++)
		if (ID == Molotov[i])
			return 1;
	return 0;
}
int �Ƿ��w�C(int ID)
{
	for (int i = 0; i < 7; i++)
		if (ID == �w�C[i])
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
void �L�u����(ULONG64 mesh, Color color, int ID) {
	Vector3 neckpos = GetBoneWithRotation(mesh, 6);
	Vector3 neckpos2 = GetBoneWithRotation(mesh, 5);
	render->�L�u���l(neckpos.x, neckpos.y, neckpos2.x, neckpos2.y, color, 1);

}
*/
void �L�u����4(ULONG64 mesh, Color color, int ID)
{

	for (int i = 0; i < 250; i++) {
		Vector3 neckpos = WorldToScreen(GetBoneWithRotation(mesh, i));
		//Vector3 pelvispos = GetBoneWithRotation(mesh, Bones::pelvis);
		//render->�L�u���l(p1.x, p1.y, c1.x, c1.y, color, 1);
		render->�L�u����(neckpos.x, neckpos.y, color, NULL, "%d", i);
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
			render->�L�u���l(p1.x, p1.y, c1.x, c1.y, color, 1);

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
			render->�L�u���l(p1.x, p1.y, c1.x, c1.y, color,1);


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
		render->�L�u����(ȫ��.���������c.x, ȫ��.���������c.y+25, Color{ 255, 0, 255, 0 }, pFont, u8"isLocalPlayerInVehicle");
		auto rootcom = DecryptGeneral(driver->RPM<ULONG64>(GetVehiclePawn(pAActor) + actor::RootComponent)); //m_rootComponent
		return driver->RPM<Vector3>(rootcom + actor::ComponentVelocity);// ComponentVelocity
	} 
	////*
	if (UVehicleRiderComponent_Pawn) {

		render->�L�u����(ȫ��.���������c.x, ȫ��.���������c.y+35, Color{ 255, 0, 255, 0 }, pFont, u8"Rideing");
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


void �L�u����(ULONG64 mesh, Color color, int ID)
{


if (mesh <= 0)
{
return;
}

Vector3 Head, Hip, Neck, Leftshoulder, LeftArm, LeftArm2, Rightshoulder, RightArm, RightArm2, Chest, Chest2, Chest3, Chest4, Leftthigh, Leftthigh2, LeftCalf, LeftCalf2, Leftfoot, Rightthigh, Rightthigh2, RightCalf, RightCalf2, Rightfoot;
/*



�۾�11, 12
�^��9
��6
����13
��� 14
�T��35
���15
�ֱ�36

2����4
3����3
4����2

���V��55
��ƨ��59
��2ƨ��56
��2ƨ��60
��С��57
��С��61
���_58
���_62
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





render->�L�u���l(Head.x, Head.y, Neck.x, Neck.y, color,1);
//render->�L�u���l(Neck.x, Neck.y, Hip.x, Hip.y, color, 1);

//render->�L�u���l(Neck.x, Neck.y, Leftshoulder.x, Leftshoulder.y, color);
//render->�L�u���l(Leftshoulder.x, Leftshoulder.y, Leftshoulder2.x, Leftshoulder2.y, color);
render->�L�u���l(Neck.x, Neck.y, Leftshoulder.x, Leftshoulder.y, color, 1);

render->�L�u���l(Leftshoulder.x, Leftshoulder.y, LeftArm.x, LeftArm.y, color, 1);
render->�L�u���l(LeftArm.x, LeftArm.y, LeftArm2.x, LeftArm2.y, color, 1);



render->�L�u���l(Neck.x, Neck.y, Rightshoulder.x, Rightshoulder.y, color, 1);


render->�L�u���l(Rightshoulder.x, Rightshoulder.y, RightArm.x, RightArm.y, color, 1);
render->�L�u���l(RightArm.x, RightArm.y, RightArm2.x, RightArm2.y, color, 1);

render->�L�u���l(Neck.x, Neck.y, Chest.x, Chest.y, color, 1);
render->�L�u���l(Chest.x, Chest.y, Chest2.x, Chest2.y, color, 1);
render->�L�u���l(Chest2.x, Chest2.y, Chest3.x, Chest3.y, color, 1);
render->�L�u���l(Chest3.x, Chest3.y, Chest4.x, Chest4.y, color, 1);
render->�L�u���l(Chest4.x, Chest4.y, Leftthigh.x, Leftthigh.y, color, 1);
render->�L�u���l(Leftthigh.x, Leftthigh.y, Leftthigh2.x, Leftthigh2.y, color, 1);
render->�L�u���l(Leftthigh2.x, Leftthigh2.y, LeftCalf.x, LeftCalf.y, color, 1);
//render->�L�u���l(LeftCalf.x, LeftCalf.y, LeftCalf2.x, LeftCalf2.y, color, 1);
//render->�L�u���l(LeftCalf2.x, LeftCalf2.y, Leftfoot.x, Leftfoot.y, color, 1);

render->�L�u���l(Chest4.x, Chest4.y, Rightthigh.x, Rightthigh.y, color, 1);
render->�L�u���l(Rightthigh.x, Rightthigh.y, Rightthigh2.x, Rightthigh2.y, color, 1);
render->�L�u���l(Rightthigh2.x, Rightthigh2.y, RightCalf.x, RightCalf.y, color, 1);
//render->�L�u���l(RightCalf.x, RightCalf.y, RightCalf2.x, RightCalf2.y, color, 1);
//render->�L�u���l(RightCalf2.x, RightCalf2.y, Rightfoot.x, Rightfoot.y, color, 1);

}



void UpdateAddresses()
{
	if (!driver)
		return;







	ȫ��׃��::pUWorld = DecryptWorld(driver->RPM<ULONG64>(ȫ��׃��::pGameBase + offset::UWorld));



	ȫ��׃��::persistentLevel = DecryptLevel(driver->RPM<ULONG64>(ȫ��׃��::pUWorld + offset::persistentLevel));

	ȫ��׃��::pGameInstance = DecryptGameInstance(driver->RPM<ULONG64>(ȫ��׃��::pUWorld + offset::GameInstance));

	ȫ��׃��::pLocalPlayerArray = DecryptLocalPlayer(driver->RPM<ULONG64>(driver->RPM<ULONG64>(ȫ��׃��::pGameInstance + offset::LocalPlayerArray)));//+0x0����

	ȫ��׃��::playerController = DecryptPlayerController(driver->RPM<ULONG64>(ȫ��׃��::pLocalPlayerArray + offset::playerController));

	ȫ��׃��::PlayerCameraManager = driver->RPM<ULONG64>(ȫ��׃��::playerController + offset::PlayerCameraManager);

	//ȫ��׃��::pViewportClient = tsl_decrypt_prop(&tsl, ȫ��׃��::pLocalPlayer + offset::ViewportClient);

	//ȫ��׃��::pPawn = DecryptGeneral(driver->RPM<ULONG64>(DecryptPlayerController(driver->RPM<ULONG64>(ȫ��׃��::pLocalPlayerArray + localPlayerAddr::playerController))) + playerController::acknowledgedPawn);
	ȫ��׃��::pPawn = DecryptGeneral(driver->RPM<ULONG64>(ȫ��׃��::playerController + offset::acknowledgedPawn));
	//ȫ��׃��::cameracache = GetCameraCache();

	/*
	ȫ��׃��::pUWorld = driver->RPM<ULONG64>(driver->RPM<ULONG64>(ȫ��׃��::pGameBase + offset::UWorld));

	ȫ��׃��::persistentLevel = DecryptLevel(driver->RPM<ULONG64>(ȫ��׃��::pUWorld + offset::persistentLevel));
	ȫ��׃��::pGameInstance = DecryptGameInstance(driver->RPM<ULONG64>(ȫ��׃��::pUWorld + offset::GameInstance));

	ȫ��׃��::pLocalPlayerArray = DecryptLocalPlayer(driver->RPM<ULONG64>(driver->RPM<ULONG64>(ȫ��׃��::pGameInstance + offset::LocalPlayerArray)));//+0x0����

	ȫ��׃��::playerController = DecryptPlayerController(driver->RPM<ULONG64>(ȫ��׃��::pLocalPlayerArray + offset::playerController));

	ȫ��׃��::PlayerCameraManager = driver->RPM<ULONG64>(ȫ��׃��::playerController + offset::PlayerCameraManager);

	//ȫ��׃��::pViewportClient = tsl_decrypt_prop(&tsl, ȫ��׃��::pLocalPlayer + offset::ViewportClient);

	//ȫ��׃��::pPawn = DecryptGeneral(driver->RPM<ULONG64>(DecryptPlayerController(driver->RPM<ULONG64>(ȫ��׃��::pLocalPlayerArray + localPlayerAddr::playerController))) + playerController::acknowledgedPawn);
	ȫ��׃��::pPawn = DecryptGeneral(driver->RPM<ULONG64>(ȫ��׃��::playerController + offset::acknowledgedPawn));

	//ȫ��׃��::cameracache = GetCameraCache();

	*/
}


void testoffset() {







	

	ȫ��׃��::pUWorld = driver->RPM<ULONG64>(driver->RPM<ULONG64>(ȫ��׃��::pGameBase + offset::UWorld));
	cout << hex << VMProtectDecryptStringA("\n2��:             0x") << ȫ��׃��::pUWorld << endl;


	ȫ��׃��::pUWorld = DecryptWorld(driver->RPM<ULONG64>(driver->RPM<ULONG64>(ȫ��׃��::pGameBase + offset::UWorld)));
	cout << hex << VMProtectDecryptStringA("\n2�ν���:             0x") << ȫ��׃��::pUWorld << endl;


	ȫ��׃��::pUWorld = (driver->RPM<ULONG64>(ȫ��׃��::pGameBase + offset::UWorld));
	cout << hex << VMProtectDecryptStringA("\nһ��b:             0x") << ȫ��׃��::pUWorld << endl;
	

	ȫ��׃��::pUWorld = DecryptWorld(driver->RPM<ULONG64>(ȫ��׃��::pGameBase + offset::UWorld));
	cout << hex << VMProtectDecryptStringA("\naһ�ν���:             0x") << ȫ��׃��::pUWorld << endl;

	ȫ��׃��::persistentLevel = DecryptLevel(driver->RPM<ULONG64>(ȫ��׃��::pUWorld + offset::persistentLevel));

	ȫ��׃��::pGameInstance = DecryptGameInstance(driver->RPM<ULONG64>(ȫ��׃��::pUWorld + offset::GameInstance));

	ȫ��׃��::pLocalPlayerArray = DecryptLocalPlayer(driver->RPM<ULONG64>(driver->RPM<ULONG64>(ȫ��׃��::pGameInstance + offset::LocalPlayerArray)));//+0x0����

	ȫ��׃��::playerController = DecryptPlayerController(driver->RPM<ULONG64>(ȫ��׃��::pLocalPlayerArray + offset::playerController));

	ȫ��׃��::PlayerCameraManager = driver->RPM<ULONG64>(ȫ��׃��::playerController + offset::PlayerCameraManager);

	//ȫ��׃��::pViewportClient = tsl_decrypt_prop(&tsl, ȫ��׃��::pLocalPlayer + offset::ViewportClient);

	//ȫ��׃��::pPawn = DecryptGeneral(driver->RPM<ULONG64>(DecryptPlayerController(driver->RPM<ULONG64>(ȫ��׃��::pLocalPlayerArray + localPlayerAddr::playerController))) + playerController::acknowledgedPawn);
	ȫ��׃��::pPawn = DecryptGeneral(driver->RPM<ULONG64>(ȫ��׃��::playerController + offset::acknowledgedPawn));
	//ȫ��׃��::cameracache = GetCameraCache();
	ULONG64 GN = DecryptGname(driver->RPM<ULONG64>(ȫ��׃��::pGameBase + offset::GNames));

	ULONG64  EncryptEntity = driver->RPM<ULONG64>(DecryptActor(driver->RPM<ULONG64>(ȫ��׃��::persistentLevel + actor::actorList)));
	cout << hex << VMProtectDecryptStringA("\nGN:                  0x") << GN << endl;
	cout << hex << VMProtectDecryptStringA("pUWorld:             0x") << ȫ��׃��::pUWorld << endl;
	cout << hex << VMProtectDecryptStringA("persistentLevel:     0x") << ȫ��׃��::persistentLevel << endl;
	cout << hex << VMProtectDecryptStringA("pGameInstance:       0x") << ȫ��׃��::pGameInstance << endl;
	cout << hex << VMProtectDecryptStringA("pLocalPlayer:        0x") << ȫ��׃��::pLocalPlayerArray << endl;
	cout << hex << VMProtectDecryptStringA("playerController:    0x") << ȫ��׃��::playerController << endl;
	cout << hex << VMProtectDecryptStringA("PlayerCameraManager: 0x") << ȫ��׃��::PlayerCameraManager << endl;
	cout << hex << VMProtectDecryptStringA("pViewportClient:     0x") << ȫ��׃��::pViewportClient << endl;
	cout << hex << VMProtectDecryptStringA("pPawn:               0x") << ȫ��׃��::pPawn << endl;
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
		Distance = 100;//31 ,36 no  34,35 ok   �{��1.34   200�׃ȳ��� 
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

	
	//����һ
	/*
     float speed = sqrt((TargetVelocity.x*TargetVelocity.x) + (TargetVelocity.y * TargetVelocity.y) + (TargetVelocity.z * TargetVelocity.z));//Ӌ�㳯���ٶ�

      float lead = (speed /10) * flytime;  //Ӌ���ٶ� *flytime = ��Ҫ�ᘌ����     Խ��ԽС  Խ�hԽ��   5*0.11  6
	  */
	//������
	  //pred.x = TargetPos.x + TargetVelocity.x *flytime;

	  //���������^��

	  
	
	//pred.x = TargetPos.x + TargetVelocity.x *flytime;//TargetVelocity.x *flytime*temp;//10*5 = 50  10*2=20
	//10   400*5     210               10 10

	pred.x = (TargetPos.x + grav.x)+ TargetVelocity.x *flytime;

	//pred.x = TargetPos.x + grav.x*flytime;
	pred.y = TargetPos.y + TargetVelocity.y *flytime;//(flytime * temp);

   //pred.z = TargetPos.z + 0.5* abs(grav)*flytime*flytime;    //pow(flytime, 2)  *45̫�� * 5.0f�Еr��]��,���r�Ȳ���,   https://www.unknowncheats.me/forum/playerunknown-s-battlegrounds/264334-calculating-bullet-drop-1-0-using-vdragcoefficient-gravity-bulletspeed.html
	///pred.z = TargetPos.z + (9.92665f * 100 / 2 * flytime * flytime + flytime * TargetVelocity.z);//�@��������ֵ ������߀�� �����x�� 

	//pred.z = TargetPos.z + 0.5 * 9.92665f * pow(flytime, 2) + (TargetVelocity.z * flytime) + flytime * 200.f;//�@��������ֵ ������߀�� �����x�� 
	pred.z = TargetPos.z + (0.5 * abs(8.8) *flytime*flytime + (TargetVelocity.z * flytime));
   //���y̫�����x�� pred.zС��ԇԇ��

	
	return pred;
}

void drawstyle(Vector3 ���w��Ļ����, ULONG64 mesh, Vector3 head, Vector3 Rfoot, int �L, int ��, int ��, int ��, Color �ɫ, int ID) {
	//�ǿ�
	if (�@ʾ���P�O��::�@ʾ�����L�� == 1)
	{
		render->�L�u�AȦ(head.x - �� * 0.2, head.y, Color{ 255, 255, 0, 0 }, 0.5*��, 24, 1);
		render->�L�u����(head.x - �� * 0.2, head.y, 0.5*��, 0.5*��, Color{ 255, 255, 0, 0 });
		
		render->�L�u���l(���w��Ļ����.x - ��, head.y, ���w��Ļ����.x - �� + ��, head.y, �ɫ::�ɫ[�ɫ::�����ɫ����],1);
		render->�L�u���l(���w��Ļ����.x - ��, head.y, ���w��Ļ����.x - ��, head.y + ��, �ɫ::�ɫ[�ɫ::�����ɫ����], 1);

		render->�L�u���l(���w��Ļ����.x + �� - ��, head.y, ���w��Ļ����.x + ��, head.y, �ɫ::�ɫ[�ɫ::�����ɫ����], 1);
		render->�L�u���l(���w��Ļ����.x + ��, head.y, ���w��Ļ����.x + ��, head.y + ��, �ɫ::�ɫ[�ɫ::�����ɫ����], 1);

		render->�L�u���l(���w��Ļ����.x - ��, Rfoot.y, ���w��Ļ����.x - �� + ��, Rfoot.y, �ɫ::�ɫ[�ɫ::�����ɫ����], 1);
		render->�L�u���l(���w��Ļ����.x - ��, Rfoot.y, ���w��Ļ����.x - ��, Rfoot.y - ��, �ɫ::�ɫ[�ɫ::�����ɫ����], 1);

		render->�L�u���l(���w��Ļ����.x + �� - ��, Rfoot.y, ���w��Ļ����.x + ��, Rfoot.y, �ɫ::�ɫ[�ɫ::�����ɫ����], 1);
		render->�L�u���l(���w��Ļ����.x + ��, Rfoot.y, ���w��Ļ����.x + ��, Rfoot.y - ��, �ɫ::�ɫ[�ɫ::�����ɫ����], 1);
	}
	//����
	if (�@ʾ���P�O��::�@ʾ�����L�� == 2)
	{


		render->�L�u�AȦ(head.x - �� * 0.2, head.y, Color{ 255, 255, 0, 0 }, 0.5*��, 24, 1);
		render->�L�u����(head.x - �� * 0.2, head.y, 0.5*��, 0.5*��, Color{ 255, 255, 0, 0 });


		render->�L�u������(���w��Ļ����.x - ��, head.y, (�� * 2), (�� * 4), Color{ 100, 105, 105, 105 });
		render->�L�u����(���w��Ļ����.x - �� + 1, head.y + 1, (�� * 2) + 1, (�� * 4) + 1, �ɫ::�ɫ[�ɫ::�����ɫ����]);

	}
	//���^
	if (�@ʾ���P�O��::�@ʾ�����L�� == 3)
	{
		render->�L�u�AȦ(head.x - �� * 0.2, head.y, Color{ 255, 255, 0, 0 }, 0.4*��, 24, 1);
		//render->�L�u����(head.x - �� * 0.2, head.y, 0.5*��, 0.5*��, Color{ 255, 255, 0, 0 });

		//	render->�L�u����(mesh, �ɫ::�ɫ[�ɫ::�����ɫ����]);
		�L�u����(mesh, �ɫ, ID);
	}
	//�C��
	if (�@ʾ���P�O��::�@ʾ�����L�� == 4)
	{
		render->�L�u�AȦ(head.x - �� * 0.2, head.y, Color{ 255, 255, 0, 0 }, 0.5*��, 24, 1);
		render->�L�u����(head.x - �� * 0.2, head.y, 0.5*��, 0.5*��, Color{ 255, 255, 0, 0 });

		render->�L�u������(���w��Ļ����.x - ��, head.y, (�� * 2), (�� * 4), Color{ 100, 105 ,105 ,105 });
		render->�L�u����(���w��Ļ����.x - �� + 1, head.y + 1, (�� * 2) + 1, (�� * 4) + 1, �ɫ::�ɫ[�ɫ::�����ɫ����]);

		�L�u����(mesh, �ɫ, ID);

	}
}

void  �^�V������Ʒ(std::string name, Vector3 screenloc, int onece) {

	if (name == VMProtectDecryptStringA("Item_Ghillie_01_C") || name == VMProtectDecryptStringA("Item_Ghillie_02_C")) {
		render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::�߼���Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"�� ������"));
		addItemYaw += onece;
		//return u8"�� ������";
	}
	if (name == VMProtectDecryptStringA("Item_Ammo_762mm_C")) {
		render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::��ͨ��Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"�� 762�ӏ�"));
		addItemYaw += onece;
		//return u8"�� 762�ӏ�";
	}
	if (name == VMProtectDecryptStringA("Item_Ammo_556mm_C")) {
		render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::��ͨ��Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"�� 556�ӏ�"));
		addItemYaw += onece;
		//return u8"�� 556�ӏ�";
	}
	if (name == VMProtectDecryptStringA("Item_Ammo_Flare_C")) {
		render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::�߼���Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"�� ��̖���ӏ�"));
		addItemYaw += onece;
		//return u8"�� ��̖���ӏ�";
	}
	if (name == VMProtectDecryptStringA("Item_Ammo_300Magnum_C")) {
		render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::�߼���Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"�� AWM�ӏ�"));
		addItemYaw += onece;
		//return u8"�� AWM�ӏ�";
	}

	if (name == VMProtectDecryptStringA("Item_Boost_EnergyDrink_C")) {

		render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::��ͨ��Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"�� �������"));
		addItemYaw += onece;
		//return u8"�� �������";
	}
	if (name == VMProtectDecryptStringA("Item_Boost_PainKiller_C")) {
		render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::��ͨ��Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"�� ֹʹˎ"));
		addItemYaw += onece;
		//return u8"�� ֹʹˎ";
	}
	if (name == VMProtectDecryptStringA("Item_Boost_AdrenalineSyringe_C")) {
		render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::�߼���Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"�� �I������"));
		addItemYaw += onece;
		//return u8"�� �I������";
	}
	if (name == VMProtectDecryptStringA("Item_Heal_Bandage_C")) {
		render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::��ͨ��Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"�� ����"));
		addItemYaw += onece;
		//return u8"�� ����";
	}
	if (name == VMProtectDecryptStringA("Item_Heal_FirstAid_C")) {
		render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::��ͨ��Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"�� ���Ȱ�"));
		addItemYaw += onece;
		//return u8"�� ���Ȱ�";
	}
	if (name == VMProtectDecryptStringA("Item_Heal_MedKit_C")) {
		render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::�߼���Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"�� �t����"));
		addItemYaw += onece;
		//return u8"�� �t����";
	}


	if (name == VMProtectDecryptStringA("Item_Attach_Weapon_Upper_Aimpoint_C")) {
		render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::��ͨ��Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"�� 2x����"));
		addItemYaw += onece;
		//return u8"�� 2x����";
	}
	if (name == VMProtectDecryptStringA("Item_Attach_Weapon_Upper_Scope3x_C")) {
		render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::��ͨ��Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"�� 3x����"));
		addItemYaw += onece;
		//return u8"�� 3x����";
	}
	if (name == VMProtectDecryptStringA("Item_Attach_Weapon_Upper_ACOG_01_C")) {
		render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::�߼���Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"�� 4x����"));
		addItemYaw += onece;
		//return u8"�� 4x����";
	}
	if (name == VMProtectDecryptStringA("Item_Attach_Weapon_Upper_Scope6x_C")) {
		render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::�߼���Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"�� 6x����"));
		addItemYaw += onece;
		//return u8"�� 6x����";
	}
	if (name == VMProtectDecryptStringA("Item_Attach_Weapon_Upper_CQBSS_C")) {
		render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::�߼���Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"�� 8x����"));
		addItemYaw += onece;
		//return u8"�� 8x����";
	}


	if (name == VMProtectDecryptStringA("Item_Weapon_Grenade_C")) {
		render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::��ͨ��Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"�� ����"));
		addItemYaw += onece;
		//return u8"�� ����";
	}
	if (name == VMProtectDecryptStringA("Item_Weapon_Molotov_C")) {
		render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::��ͨ��Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"�� ȼ��ƿ"));
		addItemYaw += onece;
		//return u8"�� ȼ��ƿ";
	}
	if (name == VMProtectDecryptStringA("Item_Weapon_FlashBang_C")) {
		render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::��ͨ��Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"�� �W�⏗"));
		addItemYaw += onece;
		//return u8"�� �W�⏗";
	}
	if (name == VMProtectDecryptStringA("Item_Weapon_SmokeBomb_C")) {
		render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::��ͨ��Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"�� ���F��"));
		addItemYaw += onece;
		//return u8"�� ���F��";
	}
	if (name == VMProtectDecryptStringA("Item_Attach_Weapon_Upper_PM2_01_C")) {
		render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::�߼���Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"�� 15x����"));
		addItemYaw += onece;
		//return u8"�� 15x����";
	}
	if (name == VMProtectDecryptStringA("Item_Attach_Weapon_Stock_SniperRifle_BulletLoops_C")) {
		render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::��ͨ��Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"�� �ѓ��ӏ���"));
		addItemYaw += onece;
		//return u8"�� �ѓ��ӏ���";
	}
	if (name == VMProtectDecryptStringA("Item_Attach_Weapon_Stock_SniperRifle_CheekPad_C")) {
		render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::��ͨ��Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"�� ������"));
		addItemYaw += onece;
		//return u8"�� ������";
	}
	if (name == VMProtectDecryptStringA("Item_Attach_Weapon_Stock_UZI_C")) {
		render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::��ͨ��Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"�� ��Ɲ����"));
		addItemYaw += onece;
		//return u8"�� ��Ɲ����";
	}
	if (name == VMProtectDecryptStringA("Item_Attach_Weapon_Stock_AR_Composite_C")) {
		render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::��ͨ��Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"�� ���g����"));
		addItemYaw += onece;
		//return u8"�� ���g����";
	}
	if (name == VMProtectDecryptStringA("Item_Attach_Weapon_Lower_AngledForeGrip_C")) {
		render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::��ͨ��Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"�� ֱ���հ�"));
		addItemYaw += onece;
		//return u8"�� ֱ���հ�";
	}
	if (name == VMProtectDecryptStringA("Item_Attach_Weapon_Lower_Foregrip_C")) {
		render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::��ͨ��Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"�� ��ֱ�հ�"));
		addItemYaw += onece;
		//return u8"�� ��ֱ�հ�";
	}

	if (name == VMProtectDecryptStringA("Item_Attach_Weapon_Lower_HalfGrip_C")) {
		render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::��ͨ��Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"�� ���ʽ�հ�"));
		addItemYaw += onece;
		//return u8"�� ���ʽ�հ�";
	}
	if (name == VMProtectDecryptStringA("Item_Attach_Weapon_Lower_LightweightForeGrip_C")) {
		render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::��ͨ��Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"�� �p���հ�"));
		addItemYaw += onece;
		//return u8"�� �p���հ�";
	}
	if (name == VMProtectDecryptStringA("Item_Attach_Weapon_Lower_ThumbGrip_C")) {
		render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::��ͨ��Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"�� Ĵָ�հ�"));
		addItemYaw += onece;
		//return u8"�� Ĵָ�հ�";
	}
	if (name == VMProtectDecryptStringA("Item_Attach_Weapon_Lower_LaserPointer_C")) {
		render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::��ͨ��Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"�� ���������"));
		addItemYaw += onece;
		//return u8"�� ���������";
	}
	if (name == VMProtectDecryptStringA("Item_Attach_Weapon_Upper_Holosight_C")) {
		render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::��ͨ��Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"�� ȫϢ"));
		addItemYaw += onece;
		//return u8"�� ȫϢ";
	}
	if (name == VMProtectDecryptStringA("Item_Attach_Weapon_Upper_DotSight_01_C")) {
		render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::��ͨ��Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"�� �t�c"));
		addItemYaw += onece;
		//return u8"�� �t�c";
	}
	if (name == VMProtectDecryptStringA("Item_Attach_Weapon_Magazine_ExtendedQuickDraw_Large_C")) {
		render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::�߼���Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"�� ������U"));
		addItemYaw += onece;
		//return u8"�� ������U";
	}
	if (name == VMProtectDecryptStringA("Item_Attach_Weapon_Magazine_ExtendedQuickDraw_SniperRifle_C")) {
		render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::�߼���Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"�� �ѓ���U"));
		addItemYaw += onece;
		//return u8"�� �ѓ���U";
	}

	if (name == VMProtectDecryptStringA("Item_Attach_Weapon_Muzzle_Compensator_Large_C")) {
		render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::�߼���Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"�� �����a��"));
		addItemYaw += onece;
		//return u8"�� �����a��";
	}
	if (name == VMProtectDecryptStringA("Item_Attach_Weapon_Muzzle_Compensator_SniperRifle_C")) {
		render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::�߼���Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"�� �ѓ��a��"));
		addItemYaw += onece;
		//return u8"�� �ѓ��a��";
	}
	if (name == VMProtectDecryptStringA("Item_Attach_Weapon_Muzzle_Suppressor_Large_C")) {
		render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::�߼���Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"�� ��������"));
		addItemYaw += onece;
		//return u8"�� ��������";
	}
	if (name == VMProtectDecryptStringA("Item_Attach_Weapon_Muzzle_Suppressor_SniperRifle_C")) {
		render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::�߼���Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"�� �ѓ�����"));
		addItemYaw += onece;
		//return u8"�� �ѓ�����";
	}

	if (name == VMProtectDecryptStringA("Item_Armor_D_01_Lv2_C") || name == VMProtectDecryptStringA("Item_Armor_D_02_Lv2_C")) {
		render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::��ͨ��Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"�� �o��Lv.2"));
		addItemYaw += onece;
		//return u8"�� �o��Lv.2";
	}
	if (name == VMProtectDecryptStringA("Item_Armor_C_01_Lv3_C") || name == VMProtectDecryptStringA("Item_Armor_C_02_Lv3_C")) {
		render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::�߼���Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"�� �o��Lv.3"));
		addItemYaw += onece;
		//return u8"�� �o��Lv.3";
	}
	if (name == VMProtectDecryptStringA("Item_Back_F_02_Lv2_C") || name == VMProtectDecryptStringA("Item_Back_F_01_Lv2_C")) {
		render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::��ͨ��Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"�� ����Lv.2"));
		addItemYaw += onece;
		//return u8"�� ����Lv.2";
	}//
	if (name == VMProtectDecryptStringA("Item_Back_C_02_Lv3_C") || name == VMProtectDecryptStringA("Item_Back_C_01_Lv3_C")) {
		render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::�߼���Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"�� ����Lv.3"));
		addItemYaw += onece;
		//return u8"�� ����Lv.3";
	}
	if (name == VMProtectDecryptStringA("Item_Head_F_02_Lv2_C") || name == VMProtectDecryptStringA("Item_Head_F_01_Lv2_C")) {
		render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::��ͨ��Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"�� �^��Lv.2"));
		addItemYaw += onece;
		//return u8"�� �^��Lv.2";
	}
	if (name == VMProtectDecryptStringA("Item_Head_G_02_Lv3_C") || name == VMProtectDecryptStringA("Item_Head_G_01_Lv3_C")) {
		render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::�߼���Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"�� �^��Lv.3"));
		addItemYaw += onece;
		//return u8"�� �^��Lv.3";
	}


	if (name == VMProtectDecryptStringA("Item_Weapon_Winchester_C")) {
		render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::��е�����ɫ����], pFont, VMProtectDecryptStringA(u8"�� S1897"));
		addItemYaw += onece;
		//return u8"�� S1897";
	}
	if (name == VMProtectDecryptStringA("Item_Weapon_Saiga12_C")) {
		render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::��е�����ɫ����], pFont, VMProtectDecryptStringA(u8"�� S12K"));
		addItemYaw += onece;
		//return u8"�� S12K";
	}
	if (name == VMProtectDecryptStringA("Item_Weapon_Berreta686_C")) {
		render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::��е�����ɫ����], pFont, VMProtectDecryptStringA(u8"�� S686ɢ��"));
		addItemYaw += onece;
		//return u8"�� S686ɢ��";
	}

	//�n�h
	if (name == VMProtectDecryptStringA("Item_Weapon_UZI_C")) {
		render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::��е�����ɫ����], pFont, VMProtectDecryptStringA(u8"�� UZI"));
		addItemYaw += onece;
		//return u8"�� UZI";
	}
	if (name == VMProtectDecryptStringA("Item_Weapon_Thompson_C")) {
		render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::��е�����ɫ����], pFont, VMProtectDecryptStringA(u8"�� ��ķ�d�n�h��"));
		addItemYaw += onece;
		//return u8"�� ��ķ�d�n�h��";
	}
	if (name == VMProtectDecryptStringA("Item_Weapon_UMP_C")) {
		render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::��е�����ɫ����], pFont, VMProtectDecryptStringA(u8"�� UMP"));
		addItemYaw += onece;
		//return u8"�� UMP";
	}
	if (name == VMProtectDecryptStringA("Item_Weapon_Vector_C")) {
		render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::��е�����ɫ����], pFont, VMProtectDecryptStringA(u8"�� Vector�n�h��"));
		addItemYaw += onece;
		//return u8"�� Vector�n�h��";
	}


	if (name == VMProtectDecryptStringA("Item_Weapon_Win1894_C")) {
		render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::��е�����ɫ����], pFont, VMProtectDecryptStringA(u8"�� Win94"));
		addItemYaw += onece;

		//return u8"�� Win94";
	}
	if (name == VMProtectDecryptStringA("Item_Weapon_Kar98k_C")) {
		render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::��е�����ɫ����], pFont, VMProtectDecryptStringA(u8"�� Kar98k"));
		addItemYaw += onece;
		//return u8"�� Kar98k";
	}
	if (�@ʾ�Y�x::M24&&name == VMProtectDecryptStringA("Item_Weapon_M24_C")) {
		render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::��е�����ɫ����], pFont, VMProtectDecryptStringA(u8"�� M24"));
		addItemYaw += onece;
		//return u8"�� M24";
	}
	if (name == VMProtectDecryptStringA("Item_Weapon_AWM_C")) {
		render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::��е�����ɫ����], pFont, VMProtectDecryptStringA(u8"�� AWM"));
		addItemYaw += onece;
		//return u8"�� AWM";
	}

	//����
	if (name == VMProtectDecryptStringA("Item_Weapon_VSS_C")) {
		render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::��е�����ɫ����], pFont, VMProtectDecryptStringA(u8"�� VSS"));
		addItemYaw += onece;
		//return u8"�� VSS";
	}
	if (name == VMProtectDecryptStringA("Item_Weapon_Mini14_C")) {
		render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::��е�����ɫ����], pFont, VMProtectDecryptStringA(u8"�� Mini14"));
		addItemYaw += onece;
		//return u8"�� 762�ӏ�";
	}
	if (name == VMProtectDecryptStringA("Item_Weapon_QBU88_C")) {
		render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::��е�����ɫ����], pFont, VMProtectDecryptStringA(u8"�� QBU"));
		addItemYaw += onece;
		//return u8"�� QBU";
	}
	if (name == VMProtectDecryptStringA("Item_Weapon_SKS_C")) {
		render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::��е�����ɫ����], pFont, VMProtectDecryptStringA(u8"�� SKS"));
		addItemYaw += onece;
		//return u8"�� SKS";
	}

	if (name == VMProtectDecryptStringA("Item_Weapon_FNFal_C")) {
		render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::��е�����ɫ����], pFont, VMProtectDecryptStringA(u8"�� SLR(�ѓ�����)"));
		addItemYaw += onece;
		//return u8"�� SLR(�ѓ�����)";
	}
	if (name == VMProtectDecryptStringA("Item_Weapon_Mk47Mutant_C")) {
		render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::��е�����ɫ����], pFont, VMProtectDecryptStringA(u8"�� Mk47Mutant"));
		addItemYaw += onece;
		//return u8"�� Mk47Mutant";
	}
	if (name == VMProtectDecryptStringA("Item_Weapon_DP28_C")) {
		render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::��е�����ɫ����], pFont, VMProtectDecryptStringA(u8"�� DP28"));
		addItemYaw += onece;
		//return u8"�� DP28";
	}
	if (name == VMProtectDecryptStringA("Item_Weapon_BerylM762_C")) {
		render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::��е�����ɫ����], pFont, VMProtectDecryptStringA(u8"�� BerylM762"));
		addItemYaw += onece;
		//return u8"�� BerylM762";
	}
	if (name == VMProtectDecryptStringA("Item_Weapon_AK47_C")) {
		render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::��е�����ɫ����], pFont, VMProtectDecryptStringA(u8"�� AKM"));
		addItemYaw += onece;
		//return u8"�� AKM";
	}
	if (name == VMProtectDecryptStringA("Item_Weapon_M16A4_C")) {
		render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::��е�����ɫ����], pFont, VMProtectDecryptStringA(u8"�� M16A4"));
		addItemYaw += onece;
		//return u8"�� M16A4";
	}
	if (name == VMProtectDecryptStringA("Item_Weapon_SCAR-L_C")) {
		render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::��е�����ɫ����], pFont, VMProtectDecryptStringA(u8"�� SCAR-L"));
		addItemYaw += onece;
		//return u8"�� SCAR-L";
	}
	if (name == VMProtectDecryptStringA("Item_Weapon_QBZ95_C")) {
		render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::��е�����ɫ����], pFont, VMProtectDecryptStringA(u8"�� QBZ"));
		addItemYaw += onece;
		//return u8"�� QBZ";
	}
	if (name == VMProtectDecryptStringA("Item_Weapon_HK416_C")) {


		render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::��е�����ɫ����], pFont, VMProtectDecryptStringA(u8"�� M416"));
		addItemYaw += onece;
		//return u8"�� M416";
	}
	if (name == VMProtectDecryptStringA("Item_Weapon_M249_C")) {
		render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::��е�����ɫ����], pFont, VMProtectDecryptStringA(u8"�� M249"));
		addItemYaw += onece;
		//return u8"�� M249";
	}
	if (name == VMProtectDecryptStringA("Item_Weapon_Mk14_C")) {
		render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::��е�����ɫ����], pFont, VMProtectDecryptStringA(u8"�� MK14"));
		addItemYaw += onece;
		//return u8"�� MK14";
	}
	if (name == VMProtectDecryptStringA("Item_Weapon_AUG_C")) {
		render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::��е�����ɫ����], pFont, VMProtectDecryptStringA(u8"�� AUG"));
		addItemYaw += onece;
		//return u8"�� AUG";
	}
	if (name == VMProtectDecryptStringA("Item_Weapon_Groza_C")) {
		render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::��е�����ɫ����], pFont, VMProtectDecryptStringA(u8"�� Groza"));
		addItemYaw += onece;
		//return u8"�� Groza";
	}


	if (name == VMProtectDecryptStringA("Item_Weapon_Pan_C")) {
		render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::�߼���Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"�� ƽ���"));
		addItemYaw += onece;
		//return u8"�� ƽ���";
	}
	if (name == VMProtectDecryptStringA("Item_Weapon_FlareGun_C")) {
		render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::��е�����ɫ����], pFont, VMProtectDecryptStringA(u8"�� ģʽ��Ҫ����:��̖��"));
		addItemYaw += onece;
		//return u8"�� ģʽ��Ҫ����:��̖��";
	}




}
void  �^�V��Ʒ(std::string name, Vector3 screenloc, int ���x, int onece) {
	//	char name[100] = { NULL };

	//sprintf_s(name, "%s", cache.c_str());
	//cout << "" << name << endl;
	//render->�L�u����(screenloc.x, screenloc.y, Color{ 255, 255, 0, 255 }, pFont, name);


	//�ӏ�
	if (�@ʾ���P�O��::�@ʾ�ӏ�) {
		if (�@ʾ�Y�x::�ӏ�762&&name == VMProtectDecryptStringA("Item_Ammo_762mm_C")) {
			render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::��ͨ��Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"762�ӏ�[%dm]"), ���x);
			addItemYaw += onece;
			//return u8"762�ӏ�";
		}
		if (�@ʾ�Y�x::�ӏ�556&&name == VMProtectDecryptStringA("Item_Ammo_556mm_C")) {
			render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::��ͨ��Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"556�ӏ�[%dm]"), ���x);
			addItemYaw += onece;
			//return u8"556�ӏ�";
		}
		if (name == VMProtectDecryptStringA("Item_Ammo_Flare_C")) {
			render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::�߼���Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"��̖���ӏ�[%dm]"), ���x);
			addItemYaw += onece;
			//return u8"��̖���ӏ�";
		}
		if (name == VMProtectDecryptStringA("Item_Ammo_300Magnum_C")) {
			render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::�߼���Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"AWM�ӏ�[%dm]"), ���x);
			addItemYaw += onece;
			//return u8"AWM�ӏ�";
		}
	}
	//�aƷ
	if (�@ʾ���P�O��::�@ʾˎ) {
		if (�@ʾ�Y�x::���&&name == VMProtectDecryptStringA("Item_Boost_EnergyDrink_C")) {

			render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::��ͨ��Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"�������[%dm]"), ���x);
			addItemYaw += onece;
			//return u8"�������";
		}
		if (�@ʾ�Y�x::ֹʹˎ&&name == VMProtectDecryptStringA("Item_Boost_PainKiller_C")) {
			render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::��ͨ��Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"ֹʹˎ[%dm]"), ���x);
			addItemYaw += onece;
			//return u8"ֹʹˎ";
		}
		if (�@ʾ�Y�x::�I������&&name == VMProtectDecryptStringA("Item_Boost_AdrenalineSyringe_C")) {
			render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::�߼���Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"�I������[%dm]"), ���x);
			addItemYaw += onece;
			//return u8"�I������";
		}
		if (�@ʾ�Y�x::����&&name == VMProtectDecryptStringA("Item_Heal_Bandage_C")) {
			render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::��ͨ��Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"����[%dm]"), ���x);
			addItemYaw += onece;
			//return u8"����";
		}
		if (�@ʾ�Y�x::���Ȱ�&&name == VMProtectDecryptStringA("Item_Heal_FirstAid_C")) {
			render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::��ͨ��Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"���Ȱ�[%dm]"), ���x);
			addItemYaw += onece;
			//return u8"���Ȱ�";
		}
		if (�@ʾ�Y�x::�t����&&name == VMProtectDecryptStringA("Item_Heal_MedKit_C")) {
			render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::�߼���Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"�t����[%dm]"), ���x);
			addItemYaw += onece;
			//return u8"�t����";
		}
	}
	if (�@ʾ���P�O��::�@ʾ���R) {

		if (�@ʾ�Y�x::x2&&name == VMProtectDecryptStringA("Item_Attach_Weapon_Upper_Aimpoint_C")) {
			render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::��ͨ��Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"2x����[%dm]"), ���x);
			addItemYaw += onece;
			//return u8"2x����";
		}
		if (�@ʾ�Y�x::x3&&name == VMProtectDecryptStringA("Item_Attach_Weapon_Upper_Scope3x_C")) {
			render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::��ͨ��Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"3x����[%dm]"), ���x);
			addItemYaw += onece;
			//return u8"3x����";
		}
		if (�@ʾ�Y�x::x4&&name == VMProtectDecryptStringA("Item_Attach_Weapon_Upper_ACOG_01_C")) {
			render->�L�u�DƬ(screenloc.x, screenloc.y - addItemYaw, 70, 70, "C:\\Users\\play2\\Desktop\\p\\bj.png");
			render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::�߼���Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"4x����[%dm]"), ���x);
			addItemYaw += onece;
			//return u8"4x����";
		}
		if (�@ʾ�Y�x::x6&&name == VMProtectDecryptStringA("Item_Attach_Weapon_Upper_Scope6x_C")) {
			render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::�߼���Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"6x����[%dm]"), ���x);
			addItemYaw += onece;
			//return u8"6x����";
		}
		if (�@ʾ�Y�x::x8&&name == VMProtectDecryptStringA("Item_Attach_Weapon_Upper_CQBSS_C")) {
			render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::�߼���Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"8x����[%dm]"), ���x);
			addItemYaw += onece;
			//return u8"8x����";
		}
	}
	//���/�����b��/����
	if (�@ʾ���P�O��::�@ʾ���) {
		//����
		if (�@ʾ�Y�x::����&&name == VMProtectDecryptStringA("Item_Weapon_Grenade_C")) {
			render->�L�u�DƬ(screenloc.x, screenloc.y - addItemYaw, 70, 70, "C:\\Users\\play2\\Desktop\\p\\sl.png");
			render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::��ͨ��Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"����[%dm]"), ���x);
			addItemYaw += onece;
			//return u8"����";
		}
		if (�@ʾ�Y�x::ȼ��ƿ &&name == VMProtectDecryptStringA("Item_Weapon_Molotov_C")) {
			render->�L�u�DƬ(screenloc.x, screenloc.y - addItemYaw, 70, 70, "C:\\Users\\play2\\Desktop\\p\\rsp.png");
			render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::��ͨ��Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"ȼ��ƿ[%dm]"), ���x);
			addItemYaw += onece;
			//return u8"ȼ��ƿ";
		}
		if (�@ʾ�Y�x::�W�⏗&&name == VMProtectDecryptStringA("Item_Weapon_FlashBang_C")) {
			render->�L�u�DƬ(screenloc.x, screenloc.y - addItemYaw, 70, 70, "C:\\Users\\play2\\Desktop\\p\\zbd.png");
			render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::��ͨ��Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"�W�⏗[%dm]"), ���x);
			addItemYaw += onece;
			//return u8"�W�⏗";
		}
		if (�@ʾ�Y�x::���F��&&name == VMProtectDecryptStringA("Item_Weapon_SmokeBomb_C")) {
			render->�L�u�DƬ(screenloc.x, screenloc.y - addItemYaw, 70, 70, "C:\\Users\\play2\\Desktop\\p\\ywd.png");
			render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::��ͨ��Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"���F��[%dm]"), ���x);
			addItemYaw += onece;
			//return u8"���F��";
		}
		//if (�@ʾ�Y�x::����&&name == VMProtectDecryptStringA("Item_Weapon_Grenade_Warmode_C")) {
		//	render->�L�u�DƬ(screenloc.x, screenloc.y - addItemYaw, 70, 70, "C:\\Users\\play2\\Desktop\\p\\sl.png");
		//	render->�L�u����(screenloc.x, screenloc.y  - addItemYaw, �ɫ::�ɫ[�ɫ::��ͨ��Ʒ�ɫ����], pFont,VMProtectDecryptStringA(u8"����(��ģʽ)[%dm]"), ���x);
		//addItemYaw += onece;
		////return u8"����(��ģʽ";}
		//���
		if (name == VMProtectDecryptStringA("Item_Attach_Weapon_Upper_PM2_01_C")) {
			render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::�߼���Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"15x����[%dm]"), ���x);
			addItemYaw += onece;
			//return u8"15x����";
		}

		if (�@ʾ�Y�x::ɢ��������&&name == VMProtectDecryptStringA("Item_Attach_Weapon_Muzzle_Duckbill_C")) {
			render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::��ͨ��Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"������(S12K)[%dm]"), ���x);
			addItemYaw += onece;
			//return u8"������(S12K)";
		}
		if (�@ʾ�Y�x::ɢ��������&&name == VMProtectDecryptStringA("Item_Attach_Weapon_Muzzle_Choke_C")) {
			render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::��ͨ��Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"������[%dm]"), ���x);
			addItemYaw += onece;
			//return u8"������";
		}
		if (�@ʾ�Y�x::ɢ���ӏ���&&name == VMProtectDecryptStringA("Item_Attach_Weapon_Stock_Shotgun_BulletLoops_C")) {
			render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::��ͨ��Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"ɢ���ӏ���[%dm]"), ���x);
			addItemYaw += onece;
			//return u8"ɢ���ӏ���";
		}
		if (�@ʾ�Y�x::�ѓ��ӏ���&&name == VMProtectDecryptStringA("Item_Attach_Weapon_Stock_SniperRifle_BulletLoops_C")) {
			render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::��ͨ��Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"�ѓ��ӏ���[%dm]"), ���x);
			addItemYaw += onece;
			//return u8"�ѓ��ӏ���";
		}
		if (�@ʾ�Y�x::�ѓ�������&&name == VMProtectDecryptStringA("Item_Attach_Weapon_Stock_SniperRifle_CheekPad_C")) {
			render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::��ͨ��Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"������[%dm]"), ���x);
			addItemYaw += onece;
			//return u8"������";
		}
		if (�@ʾ�Y�x::����&&name == VMProtectDecryptStringA("Item_Attach_Weapon_Stock_UZI_C")) {
			render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::��ͨ��Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"��Ɲ����[%dm]"), ���x);
			addItemYaw += onece;
			//return u8"��Ɲ����";
		}
		if (�@ʾ�Y�x::���g����&&name == VMProtectDecryptStringA("Item_Attach_Weapon_Stock_AR_Composite_C")) {
			render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::��ͨ��Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"���g����[%dm]"), ���x);
			addItemYaw += onece;
			//return u8"���g����";
		}
		if (�@ʾ�Y�x::ֱ���հ�&&name == VMProtectDecryptStringA("Item_Attach_Weapon_Lower_AngledForeGrip_C")) {
			render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::��ͨ��Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"ֱ���հ�[%dm]"), ���x);
			addItemYaw += onece;
			//return u8"ֱ���հ�";
		}
		if (�@ʾ�Y�x::��ֱ�հ�&&name == VMProtectDecryptStringA("Item_Attach_Weapon_Lower_Foregrip_C")) {
			render->�L�u�DƬ(screenloc.x, screenloc.y - addItemYaw, 70, 70, "C:\\Users\\play2\\Desktop\\p\\czwb.png");
			render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::��ͨ��Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"��ֱ�հ�[%dm]"), ���x);
			addItemYaw += onece;
			//return u8"��ֱ�հ�";
		}

		if (�@ʾ�Y�x::���ʽ�հ�&&name == VMProtectDecryptStringA("Item_Attach_Weapon_Lower_HalfGrip_C")) {
			render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::��ͨ��Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"���ʽ�հ�[%dm]"), ���x);
			addItemYaw += onece;
			//return u8"���ʽ�հ�";
		}
		if (�@ʾ�Y�x::�p���հ�&&name == VMProtectDecryptStringA("Item_Attach_Weapon_Lower_LightweightForeGrip_C")) {
			render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::��ͨ��Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"�p���հ�[%dm]"), ���x);
			addItemYaw += onece;
			//return u8"�p���հ�";
		}
		if (�@ʾ�Y�x::Ĵָ�հ�&&name == VMProtectDecryptStringA("Item_Attach_Weapon_Lower_ThumbGrip_C")) {
			render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::��ͨ��Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"Ĵָ�հ�[%dm]"), ���x);
			addItemYaw += onece;
			//return u8"Ĵָ�հ�";
		}
		if (�@ʾ�Y�x::���������&&name == VMProtectDecryptStringA("Item_Attach_Weapon_Lower_LaserPointer_C")) {
			render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::��ͨ��Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"���������[%dm]"), ���x);
			addItemYaw += onece;
			//return u8"���������";
		}
		if (�@ʾ�Y�x::ȫϢ&&name == VMProtectDecryptStringA("Item_Attach_Weapon_Upper_Holosight_C")) {
			render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::��ͨ��Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"ȫϢ[%dm]"), ���x);
			addItemYaw += onece;
			//return u8"ȫϢ";
		}
		if (�@ʾ�Y�x::�t�c&&name == VMProtectDecryptStringA("Item_Attach_Weapon_Upper_DotSight_01_C")) {
			render->�L�u�DƬ(screenloc.x, screenloc.y - addItemYaw, 70, 70, "C:\\Users\\play2\\Desktop\\p\\hd.png");
			render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::��ͨ��Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"�t�c[%dm]"), ���x);
			addItemYaw += onece;
			//return u8"�t�c";
		}
		if (�@ʾ�Y�x::�n�h��U&&name == VMProtectDecryptStringA("Item_Attach_Weapon_Magazine_ExtendedQuickDraw_Medium_C")) {
			render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::��ͨ��Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"�n�h��U[%dm]"), ���x);
			addItemYaw += onece;
			//return u8"�n�h��U";
		}
		if (�@ʾ�Y�x::������U&&name == VMProtectDecryptStringA("Item_Attach_Weapon_Magazine_ExtendedQuickDraw_Large_C")) {
			render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::�߼���Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"������U[%dm]"), ���x);
			addItemYaw += onece;
			//return u8"������U";
		}
		if (�@ʾ�Y�x::�ѓ���U&&name == VMProtectDecryptStringA("Item_Attach_Weapon_Magazine_ExtendedQuickDraw_SniperRifle_C")) {
			render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::�߼���Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"�ѓ���U[%dm]"), ���x);
			addItemYaw += onece;
			//return u8"�ѓ���U";
		}
		if (�@ʾ�Y�x::�n�h����&&name == VMProtectDecryptStringA("Item_Attach_Weapon_Muzzle_FlashHider_Medium_C")) {
			render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::��ͨ��Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"�n�h������[%dm]"), ���x);
			addItemYaw += onece;
			//return u8"�n�h������";
		}
		if (�@ʾ�Y�x::��������&&name == VMProtectDecryptStringA("Item_Attach_Weapon_Muzzle_FlashHider_Large_C")) {
			render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::��ͨ��Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"����������[%dm]"), ���x);
			addItemYaw += onece;
			//return u8"����������";
		}
		if (�@ʾ�Y�x::�ѓ�����&&name == VMProtectDecryptStringA("Item_Attach_Weapon_Muzzle_FlashHider_SniperRifle_C")) {
			render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::��ͨ��Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"�ѓ�������[%dm]"), ���x);
			addItemYaw += onece;
			//return u8"�ѓ�������";
		}
		if (�@ʾ�Y�x::�n�h�a��&&name == VMProtectDecryptStringA("Item_Attach_Weapon_Muzzle_Compensator_Medium_C")) {
			render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::��ͨ��Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"�n�h�a��[%dm]"), ���x);
			addItemYaw += onece;
			//return u8"�n�h�a��";
		}
		if (�@ʾ�Y�x::�����a��&&name == VMProtectDecryptStringA("Item_Attach_Weapon_Muzzle_Compensator_Large_C")) {
			render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::�߼���Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"�����a��[%dm]"), ���x);
			addItemYaw += onece;
			//return u8"�����a��";
		}
		if (�@ʾ�Y�x::�ѓ��a��&&name == VMProtectDecryptStringA("Item_Attach_Weapon_Muzzle_Compensator_SniperRifle_C")) {
			render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::�߼���Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"�ѓ��a��[%dm]"), ���x);
			addItemYaw += onece;
			//return u8"�ѓ��a��";
		}
		if (�@ʾ�Y�x::�n�h����&&name == VMProtectDecryptStringA("Item_Attach_Weapon_Muzzle_Suppressor_Medium_C")) {
			render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::��ͨ��Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"�n�h����[%dm]"), ���x);
			addItemYaw += onece;
			//return u8"�n�h����";
		}
		if (�@ʾ�Y�x::��������&&name == VMProtectDecryptStringA("Item_Attach_Weapon_Muzzle_Suppressor_Large_C")) {
			render->�L�u�DƬ(screenloc.x, screenloc.y - addItemYaw, 70, 70, "C:\\Users\\play2\\Desktop\\p\\xsq.png");
			render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::�߼���Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"��������[%dm]"), ���x);
			addItemYaw += onece;
			//return u8"��������";
		}
		if (�@ʾ�Y�x::�ѓ�����&&name == VMProtectDecryptStringA("Item_Attach_Weapon_Muzzle_Suppressor_SniperRifle_C")) {
			render->�L�u�DƬ(screenloc.x, screenloc.y - addItemYaw, 70, 70, "C:\\Users\\play2\\Desktop\\p\\xsq.png");
			render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::�߼���Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"�ѓ�����[%dm]"), ���x);
			addItemYaw += onece;
			//return u8"�ѓ�����";
		}
		//���ϵ��b��
		//if (name == VMProtectDecryptStringA("Item_Armor_E_01_Lv1_C")) {
		//	render->�L�u����(screenloc.x, screenloc.y  - addItemYaw, �ɫ::�ɫ[�ɫ::��ͨ��Ʒ�ɫ����], pFont,VMProtectDecryptStringA(u8"�o��Lv.1[%dm]"), ���x);
		//	addItemYaw += onece;
		////return u8"�o��Lv.1";}
		if (�@ʾ�Y�x::����������&&name == VMProtectDecryptStringA("Item_Armor_D_01_Lv2_C") || �@ʾ�Y�x::����������&&name == VMProtectDecryptStringA("Item_Armor_D_02_Lv2_C")) {
			render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::��ͨ��Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"�o��Lv.2[%dm]"), ���x);
			addItemYaw += onece;
			//return u8"�o��Lv.2";
		}
		if (�@ʾ�Y�x::����������&&name == VMProtectDecryptStringA("Item_Armor_C_01_Lv3_C") || �@ʾ�Y�x::����������&&name == VMProtectDecryptStringA("Item_Armor_C_02_Lv3_C")) {
			render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::�߼���Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"�o��Lv.3[%dm]"), ���x);
			addItemYaw += onece;
			//return u8"�o��Lv.3";
		}
		//if (name == VMProtectDecryptStringA("Item_Back_E_01_Lv1_C" || name == VMProtectDecryptStringA("Item_Back_E_02_Lv1_C")) {
		//	render->�L�u����(screenloc.x, screenloc.y  - addItemYaw, �ɫ::�ɫ[�ɫ::��ͨ��Ʒ�ɫ����], pFont,VMProtectDecryptStringA(u8"����Lv.1[%dm]"), ���x);
		//	addItemYaw += onece;
		////return u8"����Lv.1";}
		if (�@ʾ�Y�x::��������&&name == VMProtectDecryptStringA("Item_Back_F_02_Lv2_C") || �@ʾ�Y�x::��������&& name == VMProtectDecryptStringA("Item_Back_F_01_Lv2_C")) {
			render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::��ͨ��Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"����Lv.2[%dm]"), ���x);
			addItemYaw += onece;
			//return u8"����Lv.2";
		}//
		if (�@ʾ�Y�x::��������&&name == VMProtectDecryptStringA("Item_Back_C_02_Lv3_C") || �@ʾ�Y�x::��������&&name == VMProtectDecryptStringA("Item_Back_C_01_Lv3_C")) {
			render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::�߼���Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"����Lv.3[%dm]"), ���x);
			addItemYaw += onece;
			//return u8"����Lv.3";
		}
		//if (name == VMProtectDecryptStringA("Item_Head_E_02_Lv1_C" || name == VMProtectDecryptStringA("Item_Head_E_01_Lv1_C")) {
		//	render->�L�u����(screenloc.x, screenloc.y  - addItemYaw, �ɫ::�ɫ[�ɫ::��ͨ��Ʒ�ɫ����], pFont,VMProtectDecryptStringA(u8"�^��Lv.1[%dm]"), ���x);
		//	addItemYaw += onece;
		////return u8"�^��Lv.1";}
		if (�@ʾ�Y�x::�����^��&&name == VMProtectDecryptStringA("Item_Head_F_02_Lv2_C") || �@ʾ�Y�x::�����^��&& name == VMProtectDecryptStringA("Item_Head_F_01_Lv2_C")) {
			render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::��ͨ��Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"�^��Lv.2[%dm]"), ���x);
			addItemYaw += onece;
			//return u8"�^��Lv.2";
		}
		if (�@ʾ�Y�x::�����^��&&name == VMProtectDecryptStringA("Item_Head_G_02_Lv3_C") || �@ʾ�Y�x::�����^��&&name == VMProtectDecryptStringA("Item_Head_G_01_Lv3_C")) {
			render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::�߼���Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"�^��Lv.3[%dm]"), ���x);
			addItemYaw += onece;
			//return u8"�^��Lv.3";
		}
	}
	//��
	if (�@ʾ���P�O��::�@ʾ��) {
		//С��

		//if (name == VMProtectDecryptStringA("Item_Weapon_NagantM1895_C")) {
		//	render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::��е�����ɫ����], pFont,VMProtectDecryptStringA(u8"��݆�֘�[%dm]"), ���x);
		//	addItemYaw += onece;
		////return u8"��݆�֘�";}
		//if (name == VMProtectDecryptStringA("Item_Weapon_Rhino_C")) {
		//	render->�L�u����(screenloc.x, screenloc.y  - addItemYaw, �ɫ::�ɫ[�ɫ::��е�����ɫ����], pFont,VMProtectDecryptStringA(u8"R45[%dm]"), ���x);
		//	addItemYaw += onece;
		////return u8"R45";}
		//if (name == VMProtectDecryptStringA("Item_Weapon_M9_C")) {
		//render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::��е�����ɫ����], pFont,VMProtectDecryptStringA(u8"P92[%dm]"), ���x);
		//addItemYaw += onece;
		////return u8"P92";}
		//if (name == VMProtectDecryptStringA("Item_Weapon_G18_C")) {
		//	render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::��е�����ɫ����], pFont,VMProtectDecryptStringA(u8"P18C[%dm]"), ���x);
		////return u8"P18C";}
		//if (name == VMProtectDecryptStringA("Item_Weapon_M1911_C")) {
		//	render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::��е�����ɫ����], pFont,VMProtectDecryptStringA(u8"P1911[%dm]"), ���x);
		//	addItemYaw += onece;
		////return u8"P1911";}
		if (�@ʾ�Y�x::SAWED&&name == VMProtectDecryptStringA("Item_Weapon_Sawnoff_C")) {
			render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::��е�����ɫ����], pFont, VMProtectDecryptStringA(u8"������ɢ����[%dm]"), ���x);
			addItemYaw += onece;
			//return u8"������ɢ����";
		}
		//ɢ��
		if (�@ʾ�Y�x::S1897&&name == VMProtectDecryptStringA("Item_Weapon_Winchester_C")) {
			render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::��е�����ɫ����], pFont, VMProtectDecryptStringA(u8"S1897[%dm]"), ���x);
			addItemYaw += onece;
			//return u8"S1897";
		}
		if (�@ʾ�Y�x::S12K&&name == VMProtectDecryptStringA("Item_Weapon_Saiga12_C")) {
			render->�L�u�DƬ(screenloc.x, screenloc.y - addItemYaw, 70, 70, "C:\\Users\\play2\\Desktop\\p\\s12k.png");
			render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::��е�����ɫ����], pFont, VMProtectDecryptStringA(u8"S12K[%dm]"), ���x);
			addItemYaw += onece;
			//return u8"S12K";
		}
		if (�@ʾ�Y�x::S686&&name == VMProtectDecryptStringA("Item_Weapon_Berreta686_C")) {
			render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::��е�����ɫ����], pFont, VMProtectDecryptStringA(u8"S686ɢ��[%dm]"), ���x);
			addItemYaw += onece;
			//return u8"S686ɢ��";
		}

		//�n�h
		if (�@ʾ�Y�x::UZI&&name == VMProtectDecryptStringA("Item_Weapon_UZI_C")) {
			render->�L�u�DƬ(screenloc.x, screenloc.y - addItemYaw, 70, 70, "C:\\Users\\play2\\Desktop\\p\\uzi.png");
			render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::��е�����ɫ����], pFont, VMProtectDecryptStringA(u8"UZI[%dm]"), ���x);
			addItemYaw += onece;
			//return u8"UZI";
		}
		if (�@ʾ�Y�x::TOMMYGUN&&name == VMProtectDecryptStringA("Item_Weapon_Thompson_C")) {
			render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::��е�����ɫ����], pFont, VMProtectDecryptStringA(u8"��ķ�d�n�h��[%dm]"), ���x);
			addItemYaw += onece;
			//return u8"��ķ�d�n�h��";
		}
		if (�@ʾ�Y�x::UMP9&&name == VMProtectDecryptStringA("Item_Weapon_UMP_C")) {
			render->�L�u�DƬ(screenloc.x, screenloc.y - addItemYaw, 70, 70, "C:\\Users\\play2\\Desktop\\p\\ump9.png");
			render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::��е�����ɫ����], pFont, VMProtectDecryptStringA(u8"UMP[%dm]"), ���x);
			addItemYaw += onece;
			//return u8"UMP";
		}
		if (�@ʾ�Y�x::VECTOR&&name == VMProtectDecryptStringA("Item_Weapon_Vector_C")) {
			render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::��е�����ɫ����], pFont, VMProtectDecryptStringA(u8"Vector�n�h��[%dm]"), ���x);
			addItemYaw += onece;
			//return u8"Vector�n�h��";
		}

		//�ѓ�
		if (�@ʾ�Y�x::CROSSBOW&&name == VMProtectDecryptStringA("Item_Weapon_Crossbow_C")) {
			render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::��е�����ɫ����], pFont, VMProtectDecryptStringA(u8"ʮ�ֹ�[%dm]"), ���x);
			addItemYaw += onece;
			//return u8"ʮ�ֹ�";
		}
		if (�@ʾ�Y�x::WIN94&&name == VMProtectDecryptStringA("Item_Weapon_Win1894_C")) {
			render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::��е�����ɫ����], pFont, VMProtectDecryptStringA(u8"Win94[%dm]"), ���x);
			addItemYaw += onece;

			//return u8"Win94";
		}
		if (�@ʾ�Y�x::KAR98K&&name == VMProtectDecryptStringA("Item_Weapon_Kar98k_C")) {
			render->�L�u�DƬ(screenloc.x, screenloc.y - addItemYaw, 70, 70, "C:\\Users\\play2\\Desktop\\p\\98k.png");
			render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::��е�����ɫ����], pFont, VMProtectDecryptStringA(u8"Kar98k[%dm]"), ���x);
			addItemYaw += onece;
			//return u8"Kar98k";
		}
		if (�@ʾ�Y�x::M24&&name == VMProtectDecryptStringA("Item_Weapon_M24_C")) {
			render->�L�u�DƬ(screenloc.x, screenloc.y - addItemYaw, 70, 70, "C:\\Users\\play2\\Desktop\\p\\m24.png");
			render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::��е�����ɫ����], pFont, VMProtectDecryptStringA(u8"M24[%dm]"), ���x);
			addItemYaw += onece;
			//return u8"M24";
		}
		if (name == VMProtectDecryptStringA("Item_Weapon_AWM_C")) {
			render->�L�u�DƬ(screenloc.x, screenloc.y - addItemYaw, 70, 70, "C:\\Users\\play2\\Desktop\\p\\awm.png");
			render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::��е�����ɫ����], pFont, VMProtectDecryptStringA(u8"AWM[%dm]"), ���x);
			addItemYaw += onece;
			//return u8"AWM";
		}

		//����
		if (�@ʾ�Y�x::VSS&&name == VMProtectDecryptStringA("Item_Weapon_VSS_C")) {
			render->�L�u�DƬ(screenloc.x, screenloc.y - addItemYaw, 70, 70, "C:\\Users\\play2\\Desktop\\p\\vss.png");
			render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::��е�����ɫ����], pFont, VMProtectDecryptStringA(u8"VSS[%dm]"), ���x);
			addItemYaw += onece;
			//return u8"VSS";
		}
		if (�@ʾ�Y�x::MINI14&&name == VMProtectDecryptStringA("Item_Weapon_Mini14_C")) {
			render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::��е�����ɫ����], pFont, VMProtectDecryptStringA(u8"Mini14[%dm]"), ���x);
			addItemYaw += onece;
			//return u8"762�ӏ�";
		}
		if (�@ʾ�Y�x::QBU&&name == VMProtectDecryptStringA("Item_Weapon_QBU88_C")) {
			render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::��е�����ɫ����], pFont, VMProtectDecryptStringA(u8"QBU[%dm]"), ���x);
			addItemYaw += onece;
			//return u8"QBU";
		}
		if (�@ʾ�Y�x::SKS&&name == VMProtectDecryptStringA("Item_Weapon_SKS_C")) {
			render->�L�u�DƬ(screenloc.x, screenloc.y - addItemYaw, 70, 70, "C:\\Users\\play2\\Desktop\\p\\sks.png");
			render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::��е�����ɫ����], pFont, VMProtectDecryptStringA(u8"SKS[%dm]"), ���x);
			addItemYaw += onece;
			//return u8"SKS";
		}

		if (�@ʾ�Y�x::SLR&&name == VMProtectDecryptStringA("Item_Weapon_FNFal_C")) {
			render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::��е�����ɫ����], pFont, VMProtectDecryptStringA(u8"SLR(�ѓ�����)[%dm]"), ���x);
			addItemYaw += onece;
			//return u8"SLR(�ѓ�����)";
		}
		if (�@ʾ�Y�x::Mk47Mutan&&name == VMProtectDecryptStringA("Item_Weapon_Mk47Mutant_C")) {
			render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::��е�����ɫ����], pFont, VMProtectDecryptStringA(u8"Mk47Mutant[%dm]"), ���x);
			addItemYaw += onece;
			//return u8"Mk47Mutant";
		}
		if (�@ʾ�Y�x::DP28&&name == VMProtectDecryptStringA("Item_Weapon_DP28_C")) {
			render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::��е�����ɫ����], pFont, VMProtectDecryptStringA(u8"DP28[%dm]"), ���x);
			addItemYaw += onece;
			//return u8"DP28";
		}
		if (�@ʾ�Y�x::BerylM762&&name == VMProtectDecryptStringA("Item_Weapon_BerylM762_C")) {
			render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::��е�����ɫ����], pFont, VMProtectDecryptStringA(u8"BerylM762[%dm]"), ���x);
			addItemYaw += onece;
			//return u8"BerylM762";
		}
		if (�@ʾ�Y�x::AKM&&name == VMProtectDecryptStringA("Item_Weapon_AK47_C")) {
			render->�L�u�DƬ(screenloc.x, screenloc.y - addItemYaw, 70, 70, "C:\\Users\\play2\\Desktop\\p\\akm.png");
			render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::��е�����ɫ����], pFont, VMProtectDecryptStringA(u8"AKM[%dm]"), ���x);
			addItemYaw += onece;
			//return u8"AKM";
		}
		if (�@ʾ�Y�x::M16A4&&name == VMProtectDecryptStringA("Item_Weapon_M16A4_C")) {
			render->�L�u�DƬ(screenloc.x, screenloc.y - addItemYaw, 70, 70, "C:\\Users\\play2\\Desktop\\p\\m16.png");
			render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::��е�����ɫ����], pFont, VMProtectDecryptStringA(u8"M16A4[%dm]"), ���x);
			addItemYaw += onece;
			//return u8"M16A4";
		}
		if (�@ʾ�Y�x::SCAR&&name == VMProtectDecryptStringA("Item_Weapon_SCAR-L_C")) {
			render->�L�u�DƬ(screenloc.x, screenloc.y - addItemYaw, 70, 70, "C:\\Users\\play2\\Desktop\\p\\scar.png");
			render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::��е�����ɫ����], pFont, VMProtectDecryptStringA(u8"SCAR-L[%dm]"), ���x);
			addItemYaw += onece;
			//return u8"SCAR-L";
		}
		if (�@ʾ�Y�x::QBZ&&name == VMProtectDecryptStringA("Item_Weapon_QBZ95_C")) {
			render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::��е�����ɫ����], pFont, VMProtectDecryptStringA(u8"QBZ[%dm]"), ���x);
			addItemYaw += onece;
			//return u8"QBZ";
		}
		if (�@ʾ�Y�x::M416&&name == VMProtectDecryptStringA("Item_Weapon_HK416_C")) {

			render->�L�u�DƬ(screenloc.x, screenloc.y - addItemYaw, 70, 70, "C:\\Users\\play2\\Desktop\\p\\m416.png");
			render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::��е�����ɫ����], pFont, VMProtectDecryptStringA(u8"M416[%dm]"), ���x);
			addItemYaw += onece;
			//return u8"M416";
		}
		if (name == VMProtectDecryptStringA("Item_Weapon_M249_C")) {
			render->�L�u�DƬ(screenloc.x, screenloc.y - addItemYaw, 70, 70, "C:\\Users\\play2\\Desktop\\p\\m249.png");
			render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::��е�����ɫ����], pFont, VMProtectDecryptStringA(u8"M249[%dm]"), ���x);
			addItemYaw += onece;
			//return u8"M249";
		}
		if (name == VMProtectDecryptStringA("Item_Weapon_Mk14_C")) {
			render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::��е�����ɫ����], pFont, VMProtectDecryptStringA(u8"MK14[%dm]"), ���x);
			addItemYaw += onece;
			//return u8"MK14";
		}
		if (name == VMProtectDecryptStringA("Item_Weapon_AUG_C")) {
			render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::��е�����ɫ����], pFont, VMProtectDecryptStringA(u8"AUG[%dm]"), ���x);
			addItemYaw += onece;
			//return u8"AUG";
		}
		if (name == VMProtectDecryptStringA("Item_Weapon_Groza_C")) {
			render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::��е�����ɫ����], pFont, VMProtectDecryptStringA(u8"Groza[%dm]"), ���x);
			addItemYaw += onece;
			//return u8"Groza";
		}
	}
	//����
	if (�@ʾ���P�O��::�@ʾ��ӆ) {
		//if (name == "tem_JerryCan_C")) {
		//render->�L�u����(screenloc.x, screenloc.y  - addItemYaw, �ɫ::�ɫ[�ɫ::��ͨ��Ʒ�ɫ����], pFont,VMProtectDecryptStringA(u8"��Ͱ[%dm]"), ���x);
		//	//return u8"��Ͱ";}}
		if (�@ʾ�Y�x::ƽ���&&name == VMProtectDecryptStringA("Item_Weapon_Pan_C")) {
			render->�L�u�DƬ(screenloc.x, screenloc.y - addItemYaw, 70, 70, "C:\\Users\\play2\\Desktop\\p\\pdg.png");
			render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::�߼���Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"ƽ���[%dm]"), ���x);
			addItemYaw += onece;
			//return u8"ƽ���";
		}
		if (name == VMProtectDecryptStringA("Item_Weapon_FlareGun_C")) {
			render->�L�u����(screenloc.x, screenloc.y - addItemYaw, �ɫ::�ɫ[�ɫ::��е�����ɫ����], pFont, VMProtectDecryptStringA(u8"ģʽ��Ҫ����:��̖��[%dm]"), ���x);
			addItemYaw += onece;
			//return u8"ģʽ��Ҫ����:��̖��";
		}
	}


	/*
	if (�@ʾ�Y�x::�t���� && !strcmp(������Ʒ, "Med Kit"))
	{
	render->�L�u��߅����(screenloc.x, screenloc.y,Color{255,131,52,255}, �ɫ::�ɫ[�ɫ::��ͨ��Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"�t����[%d��]"), ���x);
	}
	else if (�@ʾ�Y�x::���Ȱ� && !strcmp(������Ʒ, "First Aid Kit"))
	{
	render->�L�u��߅����(screenloc.x, screenloc.y,Color{255,131,52,255}, �ɫ::�ɫ[�ɫ::��ͨ��Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"���Ȱ�[%d��]"), ���x);
	}
	else if (�@ʾ�Y�x::ֹʹˎ && !strcmp(������Ʒ, "Painkiller"))
	{
	render->�L�u��߅����(screenloc.x, screenloc.y,Color{255,131,52,255}, �ɫ::�ɫ[�ɫ::��ͨ��Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"ֹʹˎ[%d��]"), ���x);
	}
	else if (�@ʾ�Y�x::��� && !strcmp(������Ʒ, "Energy Drink"))
	{
	render->�L�u��߅����(screenloc.x, screenloc.y,Color{255,131,52,255}, �ɫ::�ɫ[�ɫ::��ͨ��Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"���[%d��]"), ���x);
	}
	else if (�@ʾ�Y�x::���� && !strcmp(������Ʒ, "Bandage"))
	{
	render->�L�u��߅����(screenloc.x, screenloc.y,Color{255,131,52,255}, �ɫ::�ɫ[�ɫ::��ͨ��Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"����[%d��]"), ���x);
	}
	else if (�@ʾ�Y�x::AKM && !strcmp(������Ʒ, "AKM"))
	{
	render->�L�u��߅����(screenloc.x, screenloc.y,Color{255,131,52,255}, �ɫ::�ɫ[�ɫ::��е�����ɫ����], pFont, VMProtectDecryptStringA(u8"AKM[%d��]"), ���x);
	}
	else if (�@ʾ�Y�x::M416 && !strcmp(������Ʒ, "M416"))
	{
	render->�L�u��߅����(screenloc.x, screenloc.y,Color{255,131,52,255}, �ɫ::�ɫ[�ɫ::��е�����ɫ����], pFont, VMProtectDecryptStringA(u8"M416[%d��]"), ���x);
	}
	else if (�@ʾ�Y�x::M16A4 && !strcmp(������Ʒ, "M16A4"))
	{
	render->�L�u��߅����(screenloc.x, screenloc.y,Color{255,131,52,255}, �ɫ::�ɫ[�ɫ::��е�����ɫ����], pFont, VMProtectDecryptStringA(u8"M16A4[%d��]"), ���x);
	}
	else if (�@ʾ�Y�x::SCAR && !strcmp(������Ʒ, "SCAR-L"))
	{
	render->�L�u��߅����(screenloc.x, screenloc.y,Color{255,131,52,255}, �ɫ::�ɫ[�ɫ::��е�����ɫ����], pFont, VMProtectDecryptStringA(u8"SCAR-L[%d��]"), ���x);
	}
	else if (�@ʾ�Y�x::VSS && !strcmp(������Ʒ, "VSS"))
	{
	render->�L�u��߅����(screenloc.x, screenloc.y,Color{255,131,52,255}, �ɫ::�ɫ[�ɫ::��е�����ɫ����], pFont, VMProtectDecryptStringA(u8"VSS[%d��]"), ���x);
	}
	else if (�@ʾ�Y�x::SKS && !strcmp(������Ʒ, "SKS"))
	{
	render->�L�u��߅����(screenloc.x, screenloc.y,Color{255,131,52,255}, �ɫ::�ɫ[�ɫ::��е�����ɫ����], pFont, VMProtectDecryptStringA(u8"SKS[%d��]"), ���x);
	}
	else if (�@ʾ�Y�x::MINI14 && !strcmp(������Ʒ, "Mini14"))
	{
	render->�L�u��߅����(screenloc.x, screenloc.y,Color{255,131,52,255}, �ɫ::�ɫ[�ɫ::��е�����ɫ����], pFont, VMProtectDecryptStringA(u8"Mini14[%d��]"), ���x);
	}
	else if (�@ʾ�Y�x::KAR98K && !strcmp(������Ʒ, "Kar98k"))
	{
	render->�L�u��߅����(screenloc.x, screenloc.y,Color{255,131,52,255}, �ɫ::�ɫ[�ɫ::��е�����ɫ����], pFont, VMProtectDecryptStringA(u8"Kar98k[%d��]"), ���x);
	}
	else if (�@ʾ�Y�x::WIN94 && !strcmp(������Ʒ, "Win94"))
	{
	render->�L�u��߅����(screenloc.x, screenloc.y,Color{255,131,52,255}, �ɫ::�ɫ[�ɫ::��е�����ɫ����], pFont, VMProtectDecryptStringA(u8"Win94[%d��]"), ���x);
	}
	else if (�@ʾ�Y�x::SAWED && !strcmp(������Ʒ, "Sawed-off"))
	{
	render->�L�u��߅����(screenloc.x, screenloc.y,Color{255,131,52,255}, �ɫ::�ɫ[�ɫ::��е�����ɫ����], pFont, VMProtectDecryptStringA(u8"Sawed-off[%d��]"), ���x);
	}
	else if (�@ʾ�Y�x::DP28 && !strcmp(������Ʒ, "DP-28"))
	{
	render->�L�u��߅����(screenloc.x, screenloc.y,Color{255,131,52,255}, �ɫ::�ɫ[�ɫ::��е�����ɫ����], pFont, VMProtectDecryptStringA(u8"DP-28[%d��]"), ���x);
	}
	else if (�@ʾ�Y�x::UZI && !strcmp(������Ʒ, "Micro UZI"))
	{
	render->�L�u��߅����(screenloc.x, screenloc.y,Color{255,131,52,255}, �ɫ::�ɫ[�ɫ::��е�����ɫ����], pFont, VMProtectDecryptStringA(u8"Micro UZI[%d��]"), ���x);
	}
	else if (�@ʾ�Y�x::UMP9 && !strcmp(������Ʒ, "UMP9"))
	{
	render->�L�u��߅����(screenloc.x, screenloc.y,Color{255,131,52,255}, �ɫ::�ɫ[�ɫ::��е�����ɫ����], pFont, VMProtectDecryptStringA(u8"UMP9[%d��]"), ���x);
	}
	else if (�@ʾ�Y�x::VECTOR && !strcmp(������Ʒ, "Vector"))
	{
	render->�L�u��߅����(screenloc.x, screenloc.y,Color{255,131,52,255}, �ɫ::�ɫ[�ɫ::��е�����ɫ����], pFont, VMProtectDecryptStringA(u8"Vector[%d��]"), ���x);
	}
	else if (�@ʾ�Y�x::S12K && !strcmp(������Ʒ, "S12K"))
	{
	render->�L�u��߅����(screenloc.x, screenloc.y,Color{255,131,52,255}, �ɫ::�ɫ[�ɫ::��е�����ɫ����], pFont, VMProtectDecryptStringA(u8"S12K[%d��]"), ���x);
	}
	else if (�@ʾ�Y�x::S686 && !strcmp(������Ʒ, "S686"))
	{
	render->�L�u��߅����(screenloc.x, screenloc.y,Color{255,131,52,255}, �ɫ::�ɫ[�ɫ::��е�����ɫ����], pFont, VMProtectDecryptStringA(u8"S686[%d��]"), ���x);
	}
	else if (�@ʾ�Y�x::S1897 && !strcmp(������Ʒ, "S1897"))
	{
	render->�L�u��߅����(screenloc.x, screenloc.y,Color{255,131,52,255}, �ɫ::�ɫ[�ɫ::��е�����ɫ����], pFont, VMProtectDecryptStringA(u8"S1897[%d��]"), ���x);
	}
	else if (�@ʾ�Y�x::CROSSBOW && !strcmp(������Ʒ, "Crossbow"))
	{
	render->�L�u��߅����(screenloc.x, screenloc.y,Color{255,131,52,255}, �ɫ::�ɫ[�ɫ::��е�����ɫ����], pFont, VMProtectDecryptStringA(u8"ʮ�ֹ�[%d��]"), ���x);
	}
	else if (�@ʾ�Y�x::TOMMYGUN && !strcmp(������Ʒ, "Tommy Gun"))
	{
	render->�L�u��߅����(screenloc.x, screenloc.y,Color{255,131,52,255}, �ɫ::�ɫ[�ɫ::��е�����ɫ����], pFont, VMProtectDecryptStringA(u8"��ķ�d[%d��]"), ���x);
	}
	else if (�@ʾ�Y�x::ƽ��� && !strcmp(������Ʒ, "Pan"))
	{
	render->�L�u��߅����(screenloc.x, screenloc.y,Color{255,131,52,255}, �ɫ::�ɫ[�ɫ::��ͨ��Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"ƽ���[%d��]"), ���x);
	}
	else if (�@ʾ�Y�x::���� && !strcmp(������Ʒ, "Frag Grenade"))
	{
	render->�L�u��߅����(screenloc.x, screenloc.y,Color{255,131,52,255}, �ɫ::�ɫ[�ɫ::��ͨ��Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"����[%d��]"), ���x);
	}
	else if (�@ʾ�Y�x::���F�� && !strcmp(������Ʒ, "Smoke Grenade"))
	{
	render->�L�u��߅����(screenloc.x, screenloc.y,Color{255,131,52,255}, �ɫ::�ɫ[�ɫ::��ͨ��Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"���F��[%d��]"), ���x);
	}
	else if (�@ʾ�Y�x::�W�⏗ && !strcmp(������Ʒ, "Stun Grenade"))
	{
	render->�L�u��߅����(screenloc.x, screenloc.y,Color{255,131,52,255}, �ɫ::�ɫ[�ɫ::��ͨ��Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"�W�⏗[%d��]"), ���x);
	}
	else if (�@ʾ�Y�x::ȼ��ƿ && !strcmp(������Ʒ, "Molotov Cocktail"))
	{
	render->�L�u��߅����(screenloc.x, screenloc.y,Color{255,131,52,255}, �ɫ::�ɫ[�ɫ::��ͨ��Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"ȼ��ƿ[%d��]"), ���x);
	}
	else if (�@ʾ�Y�x::�����^�� && !strcmp(������Ʒ, "Helmet (Lv.2)"))
	{
	render->�L�u��߅����(screenloc.x, screenloc.y,Color{255,131,52,255}, �ɫ::�ɫ[�ɫ::��ͨ��Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"�^��Lv.2[%d��]"), ���x);
	}
	else if (�@ʾ�Y�x::�����^�� && !strcmp(������Ʒ, "Helmet (Lv.3)"))
	{
	render->�L�u��߅����(screenloc.x, screenloc.y,Color{255,131,52,255}, �ɫ::�ɫ[�ɫ::�߼���Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"�^��Lv.3[%d��]"), ���x);
	}
	else if (�@ʾ�Y�x::�������� && !strcmp(������Ʒ, "Backpack (Lv.2)"))
	{
	render->�L�u��߅����(screenloc.x, screenloc.y,Color{255,131,52,255}, �ɫ::�ɫ[�ɫ::��ͨ��Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"����Lv.2[%d��]"), ���x);
	}
	else if (�@ʾ�Y�x::�������� && !strcmp(������Ʒ, "Backpack (Lv.3)"))
	{
	render->�L�u��߅����(screenloc.x, screenloc.y,Color{255,131,52,255}, �ɫ::�ɫ[�ɫ::�߼���Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"����Lv.3[%d��]"), ���x);
	}
	else if (�@ʾ�Y�x::���������� && !strcmp(������Ʒ, "Police Vest (Lv.2)"))
	{
	render->�L�u��߅����(screenloc.x, screenloc.y,Color{255,131,52,255}, �ɫ::�ɫ[�ɫ::��ͨ��Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"������Lv.2[%d��]"), ���x);
	}
	else if (�@ʾ�Y�x::���������� && !strcmp(������Ʒ, "Military Vest (Lv.3)"))
	{
	render->�L�u��߅����(screenloc.x, screenloc.y,Color{255,131,52,255}, �ɫ::�ɫ[�ɫ::�߼���Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"������Lv.3[%d��]"), ���x);
	}
	else if (�@ʾ�Y�x::x2 && !strcmp(������Ʒ, "2x Scope"))
	{
	render->�L�u��߅����(screenloc.x, screenloc.y,Color{255,131,52,255}, �ɫ::�ɫ[�ɫ::��ͨ��Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"2x ���R[%d��]"), ���x);
	}
	else if (�@ʾ�Y�x::x4 && !strcmp(������Ʒ, "4x Scope"))
	{
	render->�L�u��߅����(screenloc.x, screenloc.y,Color{255,131,52,255}, �ɫ::�ɫ[�ɫ::�߼���Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"4x ���R[%d��]"), ���x);
	}
	else if (�@ʾ�Y�x::x8 && !strcmp(������Ʒ, "8x Scope"))
	{
	render->�L�u��߅����(screenloc.x, screenloc.y,Color{255,131,52,255}, �ɫ::�ɫ[�ɫ::�߼���Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"8x ���R[%d��]"), ���x);
	}
	else if (�@ʾ�Y�x::ȫϢ && !strcmp(������Ʒ, "Holographic Sight"))
	{
	render->�L�u��߅����(screenloc.x, screenloc.y,Color{255,131,52,255}, �ɫ::�ɫ[�ɫ::��ͨ��Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"ȫϢ[%d��]"), ���x);
	}
	else if (�@ʾ�Y�x::�t�c && !strcmp(������Ʒ, "Red Dot Sight"))
	{
	render->�L�u��߅����(screenloc.x, screenloc.y,Color{255,131,52,255}, �ɫ::�ɫ[�ɫ::��ͨ��Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"�t�c[%d��]"), ���x);
	}
	else if (�@ʾ�Y�x::���� && !strcmp(������Ʒ, "Stock (Micro UZI)"))
	{
	render->�L�u��߅����(screenloc.x, screenloc.y,Color{255,131,52,255}, �ɫ::�ɫ[�ɫ::��ͨ��Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"��Ɲ����[%d��]"), ���x);
	}
	else if (�@ʾ�Y�x::���g���� && !strcmp(������Ʒ, "Tactical Stock (M416, Vector)"))
	{
	render->�L�u��߅����(screenloc.x, screenloc.y,Color{255,131,52,255}, �ɫ::�ɫ[�ɫ::��ͨ��Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"���g����[%d��]"), ���x);
	}
	else if (�@ʾ�Y�x::��ֱ�հ� && !strcmp(������Ʒ, "Vertical Foregrip (AR, SMG, SR)"))
	{
	render->�L�u��߅����(screenloc.x, screenloc.y,Color{255,131,52,255}, �ɫ::�ɫ[�ɫ::��ͨ��Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"��ֱ�հ�[%d��]"), ���x);
	}
	else if (�@ʾ�Y�x::ֱ���հ� && !strcmp(������Ʒ, "Angled Foregrip (AR, SMG, SR)"))
	{
	render->�L�u��߅����(screenloc.x, screenloc.y,Color{255,131,52,255}, �ɫ::�ɫ[�ɫ::��ͨ��Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"ֱ���հ�[%d��]"), ���x);
	}
	else if (�@ʾ�Y�x::�n�h���� && !strcmp(������Ʒ, "Suppressor (SMG)"))
	{
	render->�L�u��߅����(screenloc.x, screenloc.y,Color{255,131,52,255}, �ɫ::�ɫ[�ɫ::��ͨ��Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"�n�h����[%d��]"), ���x);
	}
	else if (�@ʾ�Y�x::�������� && !strcmp(������Ʒ, "Suppressor (AR, S12K)"))
	{
	render->�L�u��߅����(screenloc.x, screenloc.y,Color{255,131,52,255}, �ɫ::�ɫ[�ɫ::�߼���Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"��������[%d��]"), ���x);
	}
	else if (�@ʾ�Y�x::�ѓ����� && !strcmp(������Ʒ, "Suppressor (SR)"))
	{
	render->�L�u��߅����(screenloc.x, screenloc.y,Color{255,131,52,255}, �ɫ::�ɫ[�ɫ::�߼���Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"�ѓ�����[%d��]"), ���x);
	}
	else if (�@ʾ�Y�x::�n�h���� && !strcmp(������Ʒ, "Flash Hider (SMG)"))
	{
	render->�L�u��߅����(screenloc.x, screenloc.y,Color{255,131,52,255}, �ɫ::�ɫ[�ɫ::��ͨ��Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"�n�h����[%d��]"), ���x);
	}
	else if (�@ʾ�Y�x::�������� && !strcmp(������Ʒ, "Flash Hider (AR, S12K)"))
	{
	render->�L�u��߅����(screenloc.x, screenloc.y,Color{255,131,52,255}, �ɫ::�ɫ[�ɫ::��ͨ��Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"��������[%d��]"), ���x);
	}
	else if (�@ʾ�Y�x::�ѓ����� && !strcmp(������Ʒ, "Flash Hider (SR)"))
	{
	render->�L�u��߅����(screenloc.x, screenloc.y,Color{255,131,52,255}, �ɫ::�ɫ[�ɫ::��ͨ��Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"�ѓ�����[%d��]"), ���x);
	}
	else if (�@ʾ�Y�x::�n�h��U && !strcmp(������Ʒ, "Ext. QuickDraw Mag (SMG)"))
	{
	render->�L�u��߅����(screenloc.x, screenloc.y,Color{255,131,52,255}, �ɫ::�ɫ[�ɫ::��ͨ��Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"�n�h��U[%d��]"), ���x);
	}
	else if (�@ʾ�Y�x::�ѓ���U && !strcmp(������Ʒ, "Ext. QuickDraw Mag (SR)"))
	{
	render->�L�u��߅����(screenloc.x, screenloc.y,Color{255,131,52,255}, �ɫ::�ɫ[�ɫ::��ͨ��Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"�ѓ���U[%d��]"), ���x);
	}
	else if (�@ʾ�Y�x::������U && !strcmp(������Ʒ, "Ext. QuickDraw Mag (AR, S12K)"))
	{
	render->�L�u��߅����(screenloc.x, screenloc.y,Color{255,131,52,255}, �ɫ::�ɫ[�ɫ::��ͨ��Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"������U[%d��]"), ���x);
	}
	else if (�@ʾ�Y�x::�n�h�a�� && !strcmp(������Ʒ, "Compensator (SMG)"))
	{
	render->�L�u��߅����(screenloc.x, screenloc.y,Color{255,131,52,255}, �ɫ::�ɫ[�ɫ::��ͨ��Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"�n�h�a��[%d��]"), ���x);
	}
	else if (�@ʾ�Y�x::�����a�� && !strcmp(������Ʒ, "Compensator (AR, S12K)"))
	{
	render->�L�u��߅����(screenloc.x, screenloc.y,Color{255,131,52,255}, �ɫ::�ɫ[�ɫ::�߼���Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"�����a��[%d��]"), ���x);
	}
	else if (�@ʾ�Y�x::�ѓ��a�� && !strcmp(������Ʒ, "Compensator (SR)"))
	{
	render->�L�u��߅����(screenloc.x, screenloc.y,Color{255,131,52,255}, �ɫ::�ɫ[�ɫ::�߼���Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"�ѓ��a��[%d��]"), ���x);
	}
	else if (�@ʾ�Y�x::ɢ�������� && !strcmp(������Ʒ, "Shotgun Choke"))
	{
	render->�L�u��߅����(screenloc.x, screenloc.y,Color{255,131,52,255}, �ɫ::�ɫ[�ɫ::��ͨ��Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"ɢ��������[%d��]"), ���x);
	}
	else if (�@ʾ�Y�x::�ѓ������� && !strcmp(������Ʒ, "Cheek Pad (SR)"))
	{
	render->�L�u��߅����(screenloc.x, screenloc.y,Color{255,131,52,255}, �ɫ::�ɫ[�ɫ::��ͨ��Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"�ѓ�������[%d��]"), ���x);
	}
	else if (�@ʾ�Y�x::ɢ���ӏ��� && !strcmp(������Ʒ, "Bullet Loops (SG)"))
	{
	render->�L�u��߅����(screenloc.x, screenloc.y,Color{255,131,52,255}, �ɫ::�ɫ[�ɫ::��ͨ��Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"ɢ���ӏ���[%d��]"), ���x);
	}
	else if (�@ʾ�Y�x::�ѓ��ӏ��� && !strcmp(������Ʒ, "Bullet Loops (Kar98k)"))
	{
	render->�L�u��߅����(screenloc.x, screenloc.y,Color{255,131,52,255}, �ɫ::�ɫ[�ɫ::�߼���Ʒ�ɫ����], pFont, VMProtectDecryptStringA(u8"Kar98K�ӏ���[%d��]"), ���x);
	}
	*/
}
void ��������()
{
	//����
	char str[20000] = "C:\\�o���O��.ini";
	ifstream out(str);
	//����
	ofstream fout;
	fout.open("C:\\�o���O��.ini", ios::trunc);

	//�@ʾ���P�O��
	
	fout << VMProtectDecryptStringA("[�@ʾ���P�O��]") << endl;
	fout << VMProtectDecryptStringA("�@ʾ�����L��=") << �@ʾ���P�O��::�@ʾ�����L�� << endl;
	fout << VMProtectDecryptStringA("�@ʾ����Ѫ�l=") << �@ʾ���P�O��::�@ʾ����Ѫ�l << endl;
	fout << VMProtectDecryptStringA("�@ʾ������x=") << �@ʾ���P�O��::�@ʾ������x << endl;
	fout << VMProtectDecryptStringA("�@ʾ�؈D���_=") << �@ʾ���P�O��::�@ʾ�؈D���_ << endl;
	fout << VMProtectDecryptStringA("���������A���_�P=") << �@ʾ���P�O��::���������A���_�P << endl;
	fout << VMProtectDecryptStringA("���������A�����x=") << �@ʾ���P�O��::���������A�����x << endl;
	fout << VMProtectDecryptStringA("��������@ʾ���x=") << �@ʾ���P�O��::��������@ʾ���x << endl;
	fout << VMProtectDecryptStringA("��Ʒ����@ʾ���x=") << �@ʾ���P�O��::��Ʒ����@ʾ���x << endl;
	fout << VMProtectDecryptStringA("�d������@ʾ���x=") << �@ʾ���P�O��::�d������@ʾ���x << endl;
	fout << VMProtectDecryptStringA("ӍϢ�@ʾ�돽=") << �@ʾ���P�O��::ӍϢ�@ʾ�돽 << endl;
	fout << VMProtectDecryptStringA("��Ʒ͸ҕ=") << �@ʾ���P�O��::��Ʒ͸ҕ << endl;
	fout << VMProtectDecryptStringA("��Ͷ͸ҕ=") << �@ʾ���P�O��::��Ͷ͸ҕ << endl;
	fout << VMProtectDecryptStringA("�ǻҺ�͸ҕ=") << �@ʾ���P�O��::�ǻҺ�͸ҕ << endl;
	fout << VMProtectDecryptStringA("�@ʾ��=") << �@ʾ���P�O��::�@ʾ�� << endl;
	fout << VMProtectDecryptStringA("�@ʾ�ӏ�=") << �@ʾ���P�O��::�@ʾ�ӏ� << endl;
	fout << VMProtectDecryptStringA("�@ʾ���=") << �@ʾ���P�O��::�@ʾ��� << endl;
	fout << VMProtectDecryptStringA("�@ʾˎ=") << �@ʾ���P�O��::�@ʾˎ << endl;
	fout << VMProtectDecryptStringA("�@ʾ���R=") << �@ʾ���P�O��::�@ʾ���R << endl;
	fout << VMProtectDecryptStringA("�@ʾ��ӆ=") << �@ʾ���P�O��::�@ʾ��ӆ << endl;
	//������P�O��
	fout << VMProtectDecryptStringA("��") << endl;
	fout << VMProtectDecryptStringA("[������P�O��]") << endl;
	fout << VMProtectDecryptStringA("�ȴ�����=") << ������P�O��::�ȴ����� << endl;
	fout << VMProtectDecryptStringA("�������=") << ������P�O��::������� << endl;
	fout << VMProtectDecryptStringA("������x=") << ������P�O��::������x << endl;
	fout << VMProtectDecryptStringA("λ�Å���=") << ������P�O��::λ�Å��� << endl;
	fout << VMProtectDecryptStringA("ʮ�֜���=") << ������P�O��::ʮ�֜��� << endl;
	fout << VMProtectDecryptStringA("��ҕ�侀=") << ������P�O��::��ҕ�侀 << endl;
	fout << VMProtectDecryptStringA("�����i�^=") << ������P�O��::�����i�^ << endl;
	fout << VMProtectDecryptStringA("�C��Ŵ�=") << ������P�O��::�C��Ŵ� << endl;
	fout << VMProtectDecryptStringA("�Ŵ�S��=") << ������P�O��::�Ŵ�S�� << endl;
	fout << VMProtectDecryptStringA("�������=") << ������P�O��::������� << endl;
	fout << VMProtectDecryptStringA("�i��׷ۙ=") << ������P�O��::�i��׷ۙ << endl;
	fout << VMProtectDecryptStringA("�Ƿ��i��=") << ������P�O��::�Ƿ��i�� << endl;
	fout << VMProtectDecryptStringA("���I����=") << ������P�O��::���I���� << endl;
	//׃�B�����O��
	fout << VMProtectDecryptStringA("��") << endl;
	fout << VMProtectDecryptStringA("[׃�B�����O��]") << endl;
	fout << VMProtectDecryptStringA("�ϵ�ģʽ=") << ׃�B�����O��::�ϵ�ģʽ << endl;
	fout << VMProtectDecryptStringA("֫�w����=") << ׃�B�����O��::֫�w���� << endl;
	fout << VMProtectDecryptStringA("�o��˲��=") << ׃�B�����O��::�o��˲�� << endl;
	fout << VMProtectDecryptStringA("�����B��=") << ׃�B�����O��::�����B�� << endl;
	fout << VMProtectDecryptStringA("���S����=") << ׃�B�����O��::���S���� << endl;
	fout << VMProtectDecryptStringA("���S�߶�=") << ׃�B�����O��::���S�߶� << endl;
	fout << VMProtectDecryptStringA("˲�ƿ�Ͷ=") << ׃�B�����O��::˲�ƿ�Ͷ << endl;
	fout << VMProtectDecryptStringA("˲���d��=") << ׃�B�����O��::˲���d�� << endl;
	//�����@ʾ�Y�x
	fout << VMProtectDecryptStringA("��") << endl;
	fout << VMProtectDecryptStringA("[�����@ʾ�Y�x]") << endl;
	fout << VMProtectDecryptStringA("AKM=") << �@ʾ�Y�x::AKM << endl;
	fout << VMProtectDecryptStringA("M416=") << �@ʾ�Y�x::M416 << endl;
	fout << VMProtectDecryptStringA("M16A4=") << �@ʾ�Y�x::M16A4 << endl;
	fout << VMProtectDecryptStringA("SCAR=") << �@ʾ�Y�x::SCAR << endl;
	fout << VMProtectDecryptStringA("VSS=") << �@ʾ�Y�x::VSS << endl;
	fout << VMProtectDecryptStringA("SKS=") << �@ʾ�Y�x::SKS << endl;
	fout << VMProtectDecryptStringA("MINI14=") << �@ʾ�Y�x::MINI14 << endl;
	fout << VMProtectDecryptStringA("KAR98K=") << �@ʾ�Y�x::KAR98K << endl;
	fout << VMProtectDecryptStringA("DP28=") << �@ʾ�Y�x::DP28 << endl;
	fout << VMProtectDecryptStringA("WIN94=") << �@ʾ�Y�x::WIN94 << endl;
	fout << VMProtectDecryptStringA("SAWED=") << �@ʾ�Y�x::SAWED << endl;
	fout << VMProtectDecryptStringA("UZI=") << �@ʾ�Y�x::UZI << endl;
	fout << VMProtectDecryptStringA("UMP9=") << �@ʾ�Y�x::UMP9 << endl;
	fout << VMProtectDecryptStringA("VECTOR=") << �@ʾ�Y�x::VECTOR << endl;
	fout << VMProtectDecryptStringA("TOMMYGUN=") << �@ʾ�Y�x::TOMMYGUN << endl;
	fout << VMProtectDecryptStringA("S12K=") << �@ʾ�Y�x::S12K << endl;
	fout << VMProtectDecryptStringA("S686=") << �@ʾ�Y�x::S686 << endl;
	fout << VMProtectDecryptStringA("S1897=") << �@ʾ�Y�x::S1897 << endl;
	fout << VMProtectDecryptStringA("CROSSBOW=") << �@ʾ�Y�x::CROSSBOW << endl;
	fout << VMProtectDecryptStringA("BerylM762=") << �@ʾ�Y�x::BerylM762 << endl;
	fout << VMProtectDecryptStringA("M24=") << �@ʾ�Y�x::M24 << endl;
	fout << VMProtectDecryptStringA("Mk47Mutan=") << �@ʾ�Y�x::Mk47Mutan << endl;
	fout << VMProtectDecryptStringA("QBU=") << �@ʾ�Y�x::QBU << endl;
	fout << VMProtectDecryptStringA("QBZ=") << �@ʾ�Y�x::QBZ << endl;
	fout << VMProtectDecryptStringA("SLR=") << �@ʾ�Y�x::SLR << endl;
	//����@ʾ�Y�x
	fout << VMProtectDecryptStringA("��") << endl;
	fout << VMProtectDecryptStringA("[����@ʾ�Y�x]") << endl;
	fout << VMProtectDecryptStringA("���ʽ�հ�=") << �@ʾ�Y�x::���ʽ�հ� << endl;
	fout << VMProtectDecryptStringA("�p���հ�=") << �@ʾ�Y�x::�p���հ� << endl;
	fout << VMProtectDecryptStringA("Ĵָ�հ�=") << �@ʾ�Y�x::Ĵָ�հ� << endl;
	fout << VMProtectDecryptStringA("�ӏ�556=") << �@ʾ�Y�x::�ӏ�556 << endl;
	fout << VMProtectDecryptStringA("�ӏ�762=") << �@ʾ�Y�x::�ӏ�762 << endl;
	fout << VMProtectDecryptStringA("���������=") << �@ʾ�Y�x::��������� << endl;
	fout << VMProtectDecryptStringA("x3=") << �@ʾ�Y�x::x3 << endl;
	fout << VMProtectDecryptStringA("x6=") << �@ʾ�Y�x::x6 << endl;
	fout << VMProtectDecryptStringA("x2=") << �@ʾ�Y�x::x2 << endl;
	fout << VMProtectDecryptStringA("x4=") << �@ʾ�Y�x::x4 << endl;
	fout << VMProtectDecryptStringA("x8=") << �@ʾ�Y�x::x8 << endl;
	fout << VMProtectDecryptStringA("ȫϢ=") << �@ʾ�Y�x::ȫϢ << endl;
	fout << VMProtectDecryptStringA("�t�c=") << �@ʾ�Y�x::�t�c << endl;
	fout << VMProtectDecryptStringA("����=") << �@ʾ�Y�x::���� << endl;
	fout << VMProtectDecryptStringA("���g����=") << �@ʾ�Y�x::���g���� << endl;
	fout << VMProtectDecryptStringA("��ֱ�հ�=") << �@ʾ�Y�x::��ֱ�հ� << endl;
	fout << VMProtectDecryptStringA("ֱ���հ�=") << �@ʾ�Y�x::ֱ���հ� << endl;
	fout << VMProtectDecryptStringA("�n�h����=") << �@ʾ�Y�x::�n�h���� << endl;
	fout << VMProtectDecryptStringA("�n�h����=") << �@ʾ�Y�x::�n�h���� << endl;
	fout << VMProtectDecryptStringA("�n�h�a��=") << �@ʾ�Y�x::�n�h�a�� << endl;
	fout << VMProtectDecryptStringA("�n�h��U=") << �@ʾ�Y�x::�n�h��U << endl;
	fout << VMProtectDecryptStringA("��������=") << �@ʾ�Y�x::�������� << endl;
	fout << VMProtectDecryptStringA("��������=") << �@ʾ�Y�x::�������� << endl;
	fout << VMProtectDecryptStringA("�����a��=") << �@ʾ�Y�x::�����a�� << endl;
	fout << VMProtectDecryptStringA("������U=") << �@ʾ�Y�x::������U << endl;
	fout << VMProtectDecryptStringA("�ѓ�����=") << �@ʾ�Y�x::�ѓ����� << endl;
	fout << VMProtectDecryptStringA("�ѓ�����=") << �@ʾ�Y�x::�ѓ����� << endl;
	fout << VMProtectDecryptStringA("�ѓ��a��=") << �@ʾ�Y�x::�ѓ��a�� << endl;
	fout << VMProtectDecryptStringA("�ѓ���U=") << �@ʾ�Y�x::�ѓ���U << endl;
	fout << VMProtectDecryptStringA("�ѓ�������=") << �@ʾ�Y�x::�ѓ������� << endl;
	fout << VMProtectDecryptStringA("�ѓ��ӏ���=") << �@ʾ�Y�x::�ѓ��ӏ��� << endl;
	fout << VMProtectDecryptStringA("ɢ��������=") << �@ʾ�Y�x::ɢ�������� << endl;
	fout << VMProtectDecryptStringA("ɢ���ӏ���=") << �@ʾ�Y�x::ɢ���ӏ��� << endl;

	//�����@ʾ�Y�x
	fout << VMProtectDecryptStringA("��") << endl;
	fout << VMProtectDecryptStringA("[�����@ʾ�Y�x]") << endl;
	fout << VMProtectDecryptStringA("�I������=") << �@ʾ�Y�x::�I������ << endl;
	fout << VMProtectDecryptStringA("���=") << �@ʾ�Y�x::��� << endl;
	fout << VMProtectDecryptStringA("����=") << �@ʾ�Y�x::���� << endl;
	fout << VMProtectDecryptStringA("�t����=") << �@ʾ�Y�x::�t���� << endl;
	fout << VMProtectDecryptStringA("���Ȱ�=") << �@ʾ�Y�x::���Ȱ� << endl;
	fout << VMProtectDecryptStringA("ֹʹˎ=") << �@ʾ�Y�x::ֹʹˎ << endl;
	fout << VMProtectDecryptStringA("ƽ���=") << �@ʾ�Y�x::ƽ��� << endl;
	fout << VMProtectDecryptStringA("����=") << �@ʾ�Y�x::���� << endl;
	fout << VMProtectDecryptStringA("���F��=") << �@ʾ�Y�x::���F�� << endl;
	fout << VMProtectDecryptStringA("�W�⏗=") << �@ʾ�Y�x::�W�⏗ << endl;
	fout << VMProtectDecryptStringA("ȼ��ƿ=") << �@ʾ�Y�x::ȼ��ƿ << endl;
	fout << VMProtectDecryptStringA("�^��Lv.2=") << �@ʾ�Y�x::�����^�� << endl;
	fout << VMProtectDecryptStringA("�^��Lv.3=") << �@ʾ�Y�x::�����^�� << endl;
	fout << VMProtectDecryptStringA("����Lv.2=") << �@ʾ�Y�x::�������� << endl;
	fout << VMProtectDecryptStringA("����Lv.3=") << �@ʾ�Y�x::�������� << endl;
	fout << VMProtectDecryptStringA("������Lv.2=") << �@ʾ�Y�x::���������� << endl;
	fout << VMProtectDecryptStringA("������Lv.3=") << �@ʾ�Y�x::���������� << endl;
	//�@ʾ�����O��
	fout << VMProtectDecryptStringA("��") << endl;
	fout << VMProtectDecryptStringA("[�@ʾ�����O��]") << endl;
	fout << VMProtectDecryptStringA("�鎬����=") << �@ʾ�����O��::�鎬���� << endl;
	fout << VMProtectDecryptStringA("�������t=") << �@ʾ�����O��::�������t << endl;
	fout << VMProtectDecryptStringA("�[��͸����=") << �@ʾ�����O��::�[��͸���� << endl;
	fout << VMProtectDecryptStringA("�[��Ӵaֵ=") << �@ʾ�����O��::�[��Ӵaֵ << endl;
	fout << VMProtectDecryptStringA("�����ɫ����=") << �ɫ::�����ɫ���� << endl;
	fout << VMProtectDecryptStringA("�����ɫ����=") << �ɫ::�����ɫ���� << endl;
	fout << VMProtectDecryptStringA("�����ɫ����=") << �ɫ::�����ɫ���� << endl;
	fout << VMProtectDecryptStringA("�侀�ɫ����=") << �ɫ::�侀�ɫ���� << endl;
	fout << VMProtectDecryptStringA("�A���ɫ����=") << �ɫ::�A���ɫ���� << endl;
	fout << VMProtectDecryptStringA("܇�v�ɫ����=") << �ɫ::܇�v�ɫ���� << endl;
	fout << VMProtectDecryptStringA("��Ͷ�ɫ����=") << �ɫ::��Ͷ�ɫ���� << endl;
	fout << VMProtectDecryptStringA("�ǻҺ��ɫ����=") << �ɫ::�ǻҺ��ɫ���� << endl;
	fout << VMProtectDecryptStringA("��Ʒ�б��ɫ����=") << �ɫ::��Ʒ�б��ɫ���� << endl;
	fout << VMProtectDecryptStringA("��е�����ɫ����=") << �ɫ::��е�����ɫ���� << endl;
	fout << VMProtectDecryptStringA("��ͨ��Ʒ�ɫ����=") << �ɫ::��ͨ��Ʒ�ɫ���� << endl;
	fout << VMProtectDecryptStringA("�߼���Ʒ�ɫ����=") << �ɫ::�߼���Ʒ�ɫ���� << endl;
	fout << VMProtectDecryptStringA("���˽����x=") << �@ʾ���P�O��::���˽����x << endl;
	fout << VMProtectDecryptStringA("���˽����x�ɫ����=") << �ɫ::���˽����x�ɫ���� << endl;
	fout << VMProtectDecryptStringA("�����о��x=") << �@ʾ���P�O��::�����о��x << endl;
	fout << VMProtectDecryptStringA("�����о��x�ɫ����=") << �ɫ::�����о��x�ɫ���� << endl;
	fout << VMProtectDecryptStringA("�����h���x=") << �@ʾ���P�O��::�����h���x << endl;
	fout << VMProtectDecryptStringA("�����h���x�ɫ����=") << �ɫ::�����h���x�ɫ���� << endl;


	fout.close();

}
void �xȡ����()
{
	LPTSTR lpPath = new char[MAX_PATH];
	strcpy(lpPath, "C:\\�o���O��.ini");

	//�@ʾ���P�O��
	�@ʾ���P�O��::�@ʾ�����L�� = GetPrivateProfileInt(VMProtectDecryptStringA("�@ʾ���P�O��"), VMProtectDecryptStringA("�@ʾ�����L��"), 0, lpPath);
	�@ʾ���P�O��::�@ʾ����Ѫ�l = GetPrivateProfileInt(VMProtectDecryptStringA("�@ʾ���P�O��"), VMProtectDecryptStringA("�@ʾ����Ѫ�l"), 0, lpPath);
	�@ʾ���P�O��::�@ʾ������x = GetPrivateProfileInt(VMProtectDecryptStringA("�@ʾ���P�O��"), VMProtectDecryptStringA("�@ʾ������x"), 0, lpPath);
	�@ʾ���P�O��::�@ʾ�؈D���_ = GetPrivateProfileInt(VMProtectDecryptStringA("�@ʾ���P�O��"), VMProtectDecryptStringA("�@ʾ�؈D���_"), 0, lpPath);
	�@ʾ���P�O��::���������A���_�P = GetPrivateProfileInt(VMProtectDecryptStringA("�@ʾ���P�O��"), VMProtectDecryptStringA("���������A���_�P"), 0, lpPath);
	�@ʾ���P�O��::���������A�����x = GetPrivateProfileInt(VMProtectDecryptStringA("�@ʾ���P�O��"), VMProtectDecryptStringA("���������A�����x"), 0, lpPath);
	�@ʾ���P�O��::��������@ʾ���x = GetPrivateProfileInt(VMProtectDecryptStringA("�@ʾ���P�O��"), VMProtectDecryptStringA("��������@ʾ���x"), 0, lpPath);
	�@ʾ���P�O��::��Ʒ����@ʾ���x = GetPrivateProfileInt(VMProtectDecryptStringA("�@ʾ���P�O��"), VMProtectDecryptStringA("��Ʒ����@ʾ���x"), 0, lpPath);
	�@ʾ���P�O��::�d������@ʾ���x = GetPrivateProfileInt(VMProtectDecryptStringA("�@ʾ���P�O��"), VMProtectDecryptStringA("�d������@ʾ���x"), 0, lpPath);
	�@ʾ���P�O��::ӍϢ�@ʾ�돽 = GetPrivateProfileInt(VMProtectDecryptStringA("�@ʾ���P�O��"), VMProtectDecryptStringA("ӍϢ�@ʾ�돽"), 0, lpPath);

	�@ʾ���P�O��::��Ʒ͸ҕ = GetPrivateProfileInt(VMProtectDecryptStringA("�@ʾ���P�O��"), VMProtectDecryptStringA("��Ʒ͸ҕ"), 0, lpPath);
	�@ʾ���P�O��::��Ͷ͸ҕ = GetPrivateProfileInt(VMProtectDecryptStringA("�@ʾ���P�O��"), VMProtectDecryptStringA("��Ͷ͸ҕ"), 0, lpPath);
	�@ʾ���P�O��::�ǻҺ�͸ҕ = GetPrivateProfileInt(VMProtectDecryptStringA("�@ʾ���P�O��"), VMProtectDecryptStringA("�ǻҺ�͸ҕ"), 0, lpPath);
	�@ʾ���P�O��::�@ʾ�� = GetPrivateProfileInt(VMProtectDecryptStringA("�@ʾ���P�O��"), VMProtectDecryptStringA("�@ʾ��"), 0, lpPath);
	�@ʾ���P�O��::�@ʾ�ӏ� = GetPrivateProfileInt(VMProtectDecryptStringA("�@ʾ���P�O��"), VMProtectDecryptStringA("�@ʾ�ӏ�"), 0, lpPath);
	�@ʾ���P�O��::�@ʾ��� = GetPrivateProfileInt(VMProtectDecryptStringA("�@ʾ���P�O��"), VMProtectDecryptStringA("�@ʾ���"), 0, lpPath);
	�@ʾ���P�O��::�@ʾˎ = GetPrivateProfileInt(VMProtectDecryptStringA("�@ʾ���P�O��"), VMProtectDecryptStringA("�@ʾˎ"), 0, lpPath);
	�@ʾ���P�O��::�@ʾ���R = GetPrivateProfileInt(VMProtectDecryptStringA("�@ʾ���P�O��"), VMProtectDecryptStringA("�@ʾ���R"), 0, lpPath);
	�@ʾ���P�O��::�@ʾ��ӆ = GetPrivateProfileInt(VMProtectDecryptStringA("�@ʾ���P�O��"), VMProtectDecryptStringA("�@ʾ��ӆ"), 0, lpPath);
	//������P�O��
	������P�O��::�ȴ����� = GetPrivateProfileInt(VMProtectDecryptStringA("������P�O��"), VMProtectDecryptStringA("�ȴ�����"), 0, lpPath);
	������P�O��::������� = GetPrivateProfileInt(VMProtectDecryptStringA("������P�O��"), VMProtectDecryptStringA("�������"), 0, lpPath);
	������P�O��::������x = GetPrivateProfileInt(VMProtectDecryptStringA("������P�O��"), VMProtectDecryptStringA("������x"), 0, lpPath);
	������P�O��::λ�Å��� = GetPrivateProfileInt(VMProtectDecryptStringA("������P�O��"), VMProtectDecryptStringA("λ�Å���"), 0, lpPath);
	������P�O��::ʮ�֜��� = GetPrivateProfileInt(VMProtectDecryptStringA("������P�O��"), VMProtectDecryptStringA("ʮ�֜���"), 0, lpPath);
	������P�O��::��ҕ�侀 = GetPrivateProfileInt(VMProtectDecryptStringA("������P�O��"), VMProtectDecryptStringA("��ҕ�侀"), 0, lpPath);
	������P�O��::�����i�^ = GetPrivateProfileInt(VMProtectDecryptStringA("������P�O��"), VMProtectDecryptStringA("�����i�^"), 0, lpPath);
	������P�O��::�C��Ŵ� = GetPrivateProfileInt(VMProtectDecryptStringA("������P�O��"), VMProtectDecryptStringA("�C��Ŵ�"), 0, lpPath);
	������P�O��::�Ŵ�S�� = GetPrivateProfileInt(VMProtectDecryptStringA("������P�O��"), VMProtectDecryptStringA("�Ŵ�S��"), 0, lpPath);
	������P�O��::������� = GetPrivateProfileInt(VMProtectDecryptStringA("������P�O��"), VMProtectDecryptStringA("�������"), 0, lpPath);
	������P�O��::�i��׷ۙ = GetPrivateProfileInt(VMProtectDecryptStringA("������P�O��"), VMProtectDecryptStringA("�i��׷ۙ"), 0, lpPath);
	������P�O��::�Ƿ��i�� = GetPrivateProfileInt(VMProtectDecryptStringA("������P�O��"), VMProtectDecryptStringA("�Ƿ��i��"), 0, lpPath);
	������P�O��::���I���� = GetPrivateProfileInt(VMProtectDecryptStringA("������P�O��"), VMProtectDecryptStringA("���I����"), 0, lpPath);

	//׃�B�����O��
	׃�B�����O��::�ϵ�ģʽ = GetPrivateProfileInt(VMProtectDecryptStringA("׃�B�����O��"), VMProtectDecryptStringA("�ϵ�ģʽ"), 0, lpPath);
	׃�B�����O��::֫�w���� = GetPrivateProfileInt(VMProtectDecryptStringA("׃�B�����O��"), VMProtectDecryptStringA("֫�w����"), 0, lpPath);
	׃�B�����O��::�o��˲�� = GetPrivateProfileInt(VMProtectDecryptStringA("׃�B�����O��"), VMProtectDecryptStringA("�o��˲��"), 0, lpPath);
	׃�B�����O��::�����B�� = GetPrivateProfileInt(VMProtectDecryptStringA("׃�B�����O��"), VMProtectDecryptStringA("�����B��"), 0, lpPath);
	׃�B�����O��::���S���� = GetPrivateProfileInt(VMProtectDecryptStringA("׃�B�����O��"), VMProtectDecryptStringA("���S����"), 0, lpPath);
	׃�B�����O��::���S�߶� = GetPrivateProfileInt(VMProtectDecryptStringA("׃�B�����O��"), VMProtectDecryptStringA("���S�߶�"), 0, lpPath);
	׃�B�����O��::˲�ƿ�Ͷ = GetPrivateProfileInt(VMProtectDecryptStringA("׃�B�����O��"), VMProtectDecryptStringA("˲�ƿ�Ͷ"), 0, lpPath);
	׃�B�����O��::˲���d�� = GetPrivateProfileInt(VMProtectDecryptStringA("׃�B�����O��"), VMProtectDecryptStringA("˲���d��"), 0, lpPath);

	//�@ʾ�����O��
	�@ʾ�����O��::�鎬���� = GetPrivateProfileInt(VMProtectDecryptStringA("�@ʾ�����O��"), VMProtectDecryptStringA("�鎬����"), 0, lpPath);
	�@ʾ�����O��::�������t = GetPrivateProfileInt(VMProtectDecryptStringA("�@ʾ�����O��"), VMProtectDecryptStringA("�������t"), 0, lpPath);
	�@ʾ�����O��::�[��͸���� = GetPrivateProfileInt(VMProtectDecryptStringA("�@ʾ�����O��"), VMProtectDecryptStringA("�[��͸����"), 65, lpPath);
	�@ʾ�����O��::�[��Ӵaֵ = GetPrivateProfileInt(VMProtectDecryptStringA("�@ʾ�����O��"), VMProtectDecryptStringA("�[��Ӵaֵ"), 0, lpPath);
	�ɫ::�����ɫ���� = GetPrivateProfileInt(VMProtectDecryptStringA("�@ʾ�����O��"), VMProtectDecryptStringA("�����ɫ����"), 0, lpPath);
	�ɫ::�����ɫ���� = GetPrivateProfileInt(VMProtectDecryptStringA("�@ʾ�����O��"), VMProtectDecryptStringA("�����ɫ����"), 0, lpPath);
	�ɫ::�����ɫ���� = GetPrivateProfileInt(VMProtectDecryptStringA("�@ʾ�����O��"), VMProtectDecryptStringA("�����ɫ����"), 0, lpPath);
	�ɫ::�侀�ɫ���� = GetPrivateProfileInt(VMProtectDecryptStringA("�@ʾ�����O��"), VMProtectDecryptStringA("�侀�ɫ����"), 0, lpPath);
	�ɫ::�A���ɫ���� = GetPrivateProfileInt(VMProtectDecryptStringA("�@ʾ�����O��"), VMProtectDecryptStringA("�A���ɫ����"), 0, lpPath);
	�ɫ::܇�v�ɫ���� = GetPrivateProfileInt(VMProtectDecryptStringA("�@ʾ�����O��"), VMProtectDecryptStringA("܇�v�ɫ����"), 0, lpPath);
	�ɫ::��Ͷ�ɫ���� = GetPrivateProfileInt(VMProtectDecryptStringA("�@ʾ�����O��"), VMProtectDecryptStringA("��Ͷ�ɫ����"), 0, lpPath);
	�ɫ::�ǻҺ��ɫ���� = GetPrivateProfileInt(VMProtectDecryptStringA("�@ʾ�����O��"), VMProtectDecryptStringA("�ǻҺ��ɫ����"), 0, lpPath);
	�ɫ::��Ʒ�б��ɫ���� = GetPrivateProfileInt(VMProtectDecryptStringA("�@ʾ�����O��"), VMProtectDecryptStringA("��Ʒ�б��ɫ����"), 0, lpPath);
	�ɫ::��е�����ɫ���� = GetPrivateProfileInt(VMProtectDecryptStringA("�@ʾ�����O��"), VMProtectDecryptStringA("��е�����ɫ����"), 0, lpPath);
	�ɫ::��ͨ��Ʒ�ɫ���� = GetPrivateProfileInt(VMProtectDecryptStringA("�@ʾ�����O��"), VMProtectDecryptStringA("��ͨ��Ʒ�ɫ����"), 0, lpPath);
	�ɫ::�߼���Ʒ�ɫ���� = GetPrivateProfileInt(VMProtectDecryptStringA("�@ʾ�����O��"), VMProtectDecryptStringA("�߼���Ʒ�ɫ����"), 0, lpPath);
	�@ʾ���P�O��::���˽����x = GetPrivateProfileInt(VMProtectDecryptStringA("�@ʾ�����O��"), VMProtectDecryptStringA("���˽����x"), 200, lpPath);
	�ɫ::���˽����x�ɫ���� = GetPrivateProfileInt(VMProtectDecryptStringA("�@ʾ�����O��"), VMProtectDecryptStringA("���˽����x�ɫ����"), 0, lpPath);
	�@ʾ���P�O��::�����о��x = GetPrivateProfileInt(VMProtectDecryptStringA("�@ʾ�����O��"), VMProtectDecryptStringA("�����о��x"), 500, lpPath);
	�ɫ::�����о��x�ɫ���� = GetPrivateProfileInt(VMProtectDecryptStringA("�@ʾ�����O��"), VMProtectDecryptStringA("�����о��x�ɫ����"), 0, lpPath);
	�@ʾ���P�O��::�����h���x = GetPrivateProfileInt(VMProtectDecryptStringA("�@ʾ�����O��"), VMProtectDecryptStringA("�����h���x"), 1000, lpPath);
	�ɫ::�����h���x�ɫ���� = GetPrivateProfileInt(VMProtectDecryptStringA("�@ʾ�����O��"), VMProtectDecryptStringA("�����h���x�ɫ����"), 0, lpPath);

	//������ʾɸѡ
	�@ʾ�Y�x::�I������ = GetPrivateProfileInt(VMProtectDecryptStringA("�����@ʾ�Y�x"), VMProtectDecryptStringA("�I������"), 0, lpPath);
	�@ʾ�Y�x::��� = GetPrivateProfileInt(VMProtectDecryptStringA("�����@ʾ�Y�x"), VMProtectDecryptStringA("���"), 0, lpPath);
	�@ʾ�Y�x::���� = GetPrivateProfileInt(VMProtectDecryptStringA("�����@ʾ�Y�x"), VMProtectDecryptStringA("����"), 0, lpPath);
	�@ʾ�Y�x::�t���� = GetPrivateProfileInt(VMProtectDecryptStringA("�����@ʾ�Y�x"), VMProtectDecryptStringA("�t����"), 0, lpPath);
	�@ʾ�Y�x::���Ȱ� = GetPrivateProfileInt(VMProtectDecryptStringA("�����@ʾ�Y�x"), VMProtectDecryptStringA("���Ȱ�"), 0, lpPath);
	�@ʾ�Y�x::ֹʹˎ = GetPrivateProfileInt(VMProtectDecryptStringA("�����@ʾ�Y�x"), VMProtectDecryptStringA("ֹʹˎ"), 0, lpPath);
	�@ʾ�Y�x::ƽ��� = GetPrivateProfileInt(VMProtectDecryptStringA("�����@ʾ�Y�x"), VMProtectDecryptStringA("ƽ���"), 0, lpPath);
	�@ʾ�Y�x::���� = GetPrivateProfileInt(VMProtectDecryptStringA("�����@ʾ�Y�x"), VMProtectDecryptStringA("����"), 0, lpPath);
	�@ʾ�Y�x::���F�� = GetPrivateProfileInt(VMProtectDecryptStringA("�����@ʾ�Y�x"), VMProtectDecryptStringA("���F��"), 0, lpPath);
	�@ʾ�Y�x::�W�⏗ = GetPrivateProfileInt(VMProtectDecryptStringA("�����@ʾ�Y�x"), VMProtectDecryptStringA("�W�⏗"), 0, lpPath);
	�@ʾ�Y�x::ȼ��ƿ = GetPrivateProfileInt(VMProtectDecryptStringA("�����@ʾ�Y�x"), VMProtectDecryptStringA("ȼ��ƿ"), 0, lpPath);
	�@ʾ�Y�x::�����^�� = GetPrivateProfileInt(VMProtectDecryptStringA("�����@ʾ�Y�x"), VMProtectDecryptStringA("�^��Lv.2"), 0, lpPath);
	�@ʾ�Y�x::�����^�� = GetPrivateProfileInt(VMProtectDecryptStringA("�����@ʾ�Y�x"), VMProtectDecryptStringA("�^��Lv.3"), 0, lpPath);
	�@ʾ�Y�x::�������� = GetPrivateProfileInt(VMProtectDecryptStringA("�����@ʾ�Y�x"), VMProtectDecryptStringA("����Lv.2"), 0, lpPath);
	�@ʾ�Y�x::�������� = GetPrivateProfileInt(VMProtectDecryptStringA("�����@ʾ�Y�x"), VMProtectDecryptStringA("����Lv.3"), 0, lpPath);
	�@ʾ�Y�x::���������� = GetPrivateProfileInt(VMProtectDecryptStringA("�����@ʾ�Y�x"), VMProtectDecryptStringA("������Lv.2"), 0, lpPath);
	�@ʾ�Y�x::���������� = GetPrivateProfileInt(VMProtectDecryptStringA("�����@ʾ�Y�x"), VMProtectDecryptStringA("������Lv.3"), 0, lpPath);

	//�@ʾ�Y�x
	�@ʾ�Y�x::AKM = GetPrivateProfileInt(VMProtectDecryptStringA("�����@ʾ�Y�x"), VMProtectDecryptStringA("AKM"), 0, lpPath);
	�@ʾ�Y�x::M416 = GetPrivateProfileInt(VMProtectDecryptStringA("�����@ʾ�Y�x"), VMProtectDecryptStringA("M416"), 0, lpPath);
	�@ʾ�Y�x::M16A4 = GetPrivateProfileInt(VMProtectDecryptStringA("�����@ʾ�Y�x"), VMProtectDecryptStringA("M16A4"), 0, lpPath);
	�@ʾ�Y�x::SCAR = GetPrivateProfileInt(VMProtectDecryptStringA("�����@ʾ�Y�x"), VMProtectDecryptStringA("SCAR"), 0, lpPath);
	�@ʾ�Y�x::VSS = GetPrivateProfileInt(VMProtectDecryptStringA("�����@ʾ�Y�x"), VMProtectDecryptStringA("VSS"), 0, lpPath);
	�@ʾ�Y�x::SKS = GetPrivateProfileInt(VMProtectDecryptStringA("�����@ʾ�Y�x"), VMProtectDecryptStringA("SKS"), 0, lpPath);
	�@ʾ�Y�x::MINI14 = GetPrivateProfileInt(VMProtectDecryptStringA("�����@ʾ�Y�x"), VMProtectDecryptStringA("MINI14"), 0, lpPath);
	�@ʾ�Y�x::KAR98K = GetPrivateProfileInt(VMProtectDecryptStringA("�����@ʾ�Y�x"), VMProtectDecryptStringA("KAR98K"), 0, lpPath);
	�@ʾ�Y�x::DP28 = GetPrivateProfileInt(VMProtectDecryptStringA("�����@ʾ�Y�x"), VMProtectDecryptStringA("DP28"), 0, lpPath);
	�@ʾ�Y�x::WIN94 = GetPrivateProfileInt(VMProtectDecryptStringA("�����@ʾ�Y�x"), VMProtectDecryptStringA("WIN94"), 0, lpPath);
	�@ʾ�Y�x::SAWED = GetPrivateProfileInt(VMProtectDecryptStringA("�����@ʾ�Y�x"), VMProtectDecryptStringA("SAWED"), 0, lpPath);
	�@ʾ�Y�x::UZI = GetPrivateProfileInt(VMProtectDecryptStringA("�����@ʾ�Y�x"), VMProtectDecryptStringA("UZI"), 0, lpPath);
	�@ʾ�Y�x::UMP9 = GetPrivateProfileInt(VMProtectDecryptStringA("�����@ʾ�Y�x"), VMProtectDecryptStringA("UMP9"), 0, lpPath);
	�@ʾ�Y�x::VECTOR = GetPrivateProfileInt(VMProtectDecryptStringA("�����@ʾ�Y�x"), VMProtectDecryptStringA("VECTOR"), 0, lpPath);
	�@ʾ�Y�x::TOMMYGUN = GetPrivateProfileInt(VMProtectDecryptStringA("�����@ʾ�Y�x"), VMProtectDecryptStringA("TOMMYGUN"), 0, lpPath);
	�@ʾ�Y�x::S12K = GetPrivateProfileInt(VMProtectDecryptStringA("�����@ʾ�Y�x"), VMProtectDecryptStringA("S12K"), 0, lpPath);
	�@ʾ�Y�x::S686 = GetPrivateProfileInt(VMProtectDecryptStringA("�����@ʾ�Y�x"), VMProtectDecryptStringA("S686"), 0, lpPath);
	�@ʾ�Y�x::S1897 = GetPrivateProfileInt(VMProtectDecryptStringA("�����@ʾ�Y�x"), VMProtectDecryptStringA("S1897"), 0, lpPath);
	�@ʾ�Y�x::CROSSBOW = GetPrivateProfileInt(VMProtectDecryptStringA("�����@ʾ�Y�x"), VMProtectDecryptStringA("CROSSBOW"), 0, lpPath);
	�@ʾ�Y�x::BerylM762 = GetPrivateProfileInt(VMProtectDecryptStringA("�����@ʾ�Y�x"), VMProtectDecryptStringA("BerylM762"), 0, lpPath);
	�@ʾ�Y�x::M24 = GetPrivateProfileInt(VMProtectDecryptStringA("�����@ʾ�Y�x"), VMProtectDecryptStringA("M24"), 0, lpPath);
	�@ʾ�Y�x::Mk47Mutan = GetPrivateProfileInt(VMProtectDecryptStringA("�����@ʾ�Y�x"), VMProtectDecryptStringA("Mk47Mutan"), 0, lpPath);
	�@ʾ�Y�x::QBU = GetPrivateProfileInt(VMProtectDecryptStringA("�����@ʾ�Y�x"), VMProtectDecryptStringA("QBU"), 0, lpPath);
	�@ʾ�Y�x::QBZ = GetPrivateProfileInt(VMProtectDecryptStringA("�����@ʾ�Y�x"), VMProtectDecryptStringA("QBZ"), 0, lpPath);
	�@ʾ�Y�x::SLR = GetPrivateProfileInt(VMProtectDecryptStringA("�����@ʾ�Y�x"), VMProtectDecryptStringA("SLR"), 0, lpPath);

	�@ʾ�Y�x::���ʽ�հ� = GetPrivateProfileInt(VMProtectDecryptStringA("����@ʾ�Y�x"), VMProtectDecryptStringA("���ʽ�հ�"), 0, lpPath);
	�@ʾ�Y�x::�p���հ� = GetPrivateProfileInt(VMProtectDecryptStringA("����@ʾ�Y�x"), VMProtectDecryptStringA("�p���հ�"), 0, lpPath);
	�@ʾ�Y�x::Ĵָ�հ� = GetPrivateProfileInt(VMProtectDecryptStringA("����@ʾ�Y�x"), VMProtectDecryptStringA("Ĵָ�հ�"), 0, lpPath);
	�@ʾ�Y�x::�ӏ�556 = GetPrivateProfileInt(VMProtectDecryptStringA("����@ʾ�Y�x"), VMProtectDecryptStringA("�ӏ�556"), 0, lpPath);
	�@ʾ�Y�x::�ӏ�762 = GetPrivateProfileInt(VMProtectDecryptStringA("����@ʾ�Y�x"), VMProtectDecryptStringA("�ӏ�762"), 0, lpPath);
	�@ʾ�Y�x::��������� = GetPrivateProfileInt(VMProtectDecryptStringA("����@ʾ�Y�x"), VMProtectDecryptStringA("���������"), 0, lpPath);
	�@ʾ�Y�x::x3 = GetPrivateProfileInt(VMProtectDecryptStringA("����@ʾ�Y�x"), VMProtectDecryptStringA("x3"), 0, lpPath);
	�@ʾ�Y�x::x6 = GetPrivateProfileInt(VMProtectDecryptStringA("����@ʾ�Y�x"), VMProtectDecryptStringA("x6"), 0, lpPath);
	�@ʾ�Y�x::x2 = GetPrivateProfileInt(VMProtectDecryptStringA("����@ʾ�Y�x"), VMProtectDecryptStringA("x2"), 0, lpPath);
	�@ʾ�Y�x::x4 = GetPrivateProfileInt(VMProtectDecryptStringA("����@ʾ�Y�x"), VMProtectDecryptStringA("x4"), 0, lpPath);
	�@ʾ�Y�x::x8 = GetPrivateProfileInt(VMProtectDecryptStringA("����@ʾ�Y�x"), VMProtectDecryptStringA("x8"), 0, lpPath);
	�@ʾ�Y�x::ȫϢ = GetPrivateProfileInt(VMProtectDecryptStringA("����@ʾ�Y�x"), VMProtectDecryptStringA("ȫϢ"), 0, lpPath);
	�@ʾ�Y�x::�t�c = GetPrivateProfileInt(VMProtectDecryptStringA("����@ʾ�Y�x"), VMProtectDecryptStringA("�t�c"), 0, lpPath);
	�@ʾ�Y�x::���� = GetPrivateProfileInt(VMProtectDecryptStringA("����@ʾ�Y�x"), VMProtectDecryptStringA("����"), 0, lpPath);
	�@ʾ�Y�x::���g���� = GetPrivateProfileInt(VMProtectDecryptStringA("����@ʾ�Y�x"), VMProtectDecryptStringA("���g����"), 0, lpPath);
	�@ʾ�Y�x::��ֱ�հ� = GetPrivateProfileInt(VMProtectDecryptStringA("����@ʾ�Y�x"), VMProtectDecryptStringA("��ֱ�հ�"), 0, lpPath);
	�@ʾ�Y�x::ֱ���հ� = GetPrivateProfileInt(VMProtectDecryptStringA("����@ʾ�Y�x"), VMProtectDecryptStringA("ֱ���հ�"), 0, lpPath);
	�@ʾ�Y�x::�n�h���� = GetPrivateProfileInt(VMProtectDecryptStringA("����@ʾ�Y�x"), VMProtectDecryptStringA("�n�h����"), 0, lpPath);
	�@ʾ�Y�x::�n�h���� = GetPrivateProfileInt(VMProtectDecryptStringA("����@ʾ�Y�x"), VMProtectDecryptStringA("�n�h����"), 0, lpPath);
	�@ʾ�Y�x::�n�h�a�� = GetPrivateProfileInt(VMProtectDecryptStringA("����@ʾ�Y�x"), VMProtectDecryptStringA("�n�h�a��"), 0, lpPath);
	�@ʾ�Y�x::�n�h��U = GetPrivateProfileInt(VMProtectDecryptStringA("����@ʾ�Y�x"), VMProtectDecryptStringA("�n�h��U"), 0, lpPath);
	�@ʾ�Y�x::�������� = GetPrivateProfileInt(VMProtectDecryptStringA("����@ʾ�Y�x"), VMProtectDecryptStringA("��������"), 0, lpPath);
	�@ʾ�Y�x::�������� = GetPrivateProfileInt(VMProtectDecryptStringA("����@ʾ�Y�x"), VMProtectDecryptStringA("��������"), 0, lpPath);
	�@ʾ�Y�x::�����a�� = GetPrivateProfileInt(VMProtectDecryptStringA("����@ʾ�Y�x"), VMProtectDecryptStringA("�����a��"), 0, lpPath);
	�@ʾ�Y�x::������U = GetPrivateProfileInt(VMProtectDecryptStringA("����@ʾ�Y�x"), VMProtectDecryptStringA("������U"), 0, lpPath);
	�@ʾ�Y�x::�ѓ����� = GetPrivateProfileInt(VMProtectDecryptStringA("����@ʾ�Y�x"), VMProtectDecryptStringA("�ѓ�����"), 0, lpPath);
	�@ʾ�Y�x::�ѓ����� = GetPrivateProfileInt(VMProtectDecryptStringA("����@ʾ�Y�x"), VMProtectDecryptStringA("�ѓ�����"), 0, lpPath);
	�@ʾ�Y�x::�ѓ��a�� = GetPrivateProfileInt(VMProtectDecryptStringA("����@ʾ�Y�x"), VMProtectDecryptStringA("�ѓ��a��"), 0, lpPath);
	�@ʾ�Y�x::�ѓ���U = GetPrivateProfileInt(VMProtectDecryptStringA("����@ʾ�Y�x"), VMProtectDecryptStringA("�ѓ���U"), 0, lpPath);
	�@ʾ�Y�x::�ѓ������� = GetPrivateProfileInt(VMProtectDecryptStringA("����@ʾ�Y�x"), VMProtectDecryptStringA("�ѓ�������"), 0, lpPath);
	�@ʾ�Y�x::�ѓ��ӏ��� = GetPrivateProfileInt(VMProtectDecryptStringA("����@ʾ�Y�x"), VMProtectDecryptStringA("�ѓ��ӏ���"), 0, lpPath);
	�@ʾ�Y�x::ɢ�������� = GetPrivateProfileInt(VMProtectDecryptStringA("����@ʾ�Y�x"), VMProtectDecryptStringA("ɢ��������"), 0, lpPath);
	�@ʾ�Y�x::ɢ���ӏ��� = GetPrivateProfileInt(VMProtectDecryptStringA("����@ʾ�Y�x"), VMProtectDecryptStringA("ɢ���ӏ���"), 0, lpPath);

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