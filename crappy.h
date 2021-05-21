#pragma once

#include "KReader.hpp"
#include "overlay.h"
#include "Global.h"

#include <List>
#include <String>
#include <Thread>
#include <Vector>

using namespace std;

class Vector3
{
public:
	Vector3() : x(0.f), y(0.f), z(0.f) {}

	Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}

	~Vector3() {}

	float x;
	float y;
	float z;

	inline Vector3 ToFRotator()
	{
		float RADPI = (float)(180 / 浮點精度);
		float Yaw = (float)atan2f(y, x) * RADPI;
		float Pitch = (float)atan2f(z, sqrtf(powf(x, 2.0) + powf(y, 2.0))) * RADPI;
		float Roll = 0;
		return  Vector3(Pitch, Yaw, Roll);
	}

	inline float Dot(Vector3 v)
	{
		return x * v.x + y * v.y + z * v.z;
	}

	inline float Distance(Vector3 v)
	{
		return float(sqrtf(powf(v.x - x, 2.0) + powf(v.y - y, 2.0) + powf(v.z - z, 2.0)));
	}

	inline float Length()
	{
		return float(sqrtf(powf(x, 2.0) + powf(y, 2.0) + powf(z, 2.0)));
	}

	Vector3 operator+(Vector3 v)
	{
		return Vector3(x + v.x, y + v.y, z + v.z);
	}

	Vector3 operator-(Vector3 v)
	{
		return Vector3(x - v.x, y - v.y, z - v.z);
	}


	Vector3 operator+(float r)
	{
		return Vector3(x + r, y + r, z + r);
	}

	Vector3 operator-(float r)
	{
		return Vector3(x - r, y - r, z - r);
	}

	Vector3 operator/(float r)
	{
		return Vector3(x / r, y / r, z / r);
	}

	Vector3 operator*(float r)
	{
		return Vector3(x * r, y * r, z * r);
	}

	Vector3 operator*(double r)
	{
		return Vector3(x * r, y * r, z * r);
	}

	Vector3 operator*(int r)
	{
		return Vector3(x * r, y * r, z * r);
	}
	/*
	Vector3& operator/=(float fl)
	{
		float oofl = 1.0f / fl;
		x *= oofl;
		y *= oofl;
		z *= oofl;
		return *this;
	}

	Vector3& operator+=(const Vector3& v)
	{
		x += v.x; y += v.y; z += v.z;
		return *this;
	}

	Vector3& operator+=(float v)
	{
		x += v; y += v; z += v;
		return *this;
	}

	Vector3& operator-=(const Vector3& v)
	{
		x -= v.x; y -= v.y; z -= v.z;
		return *this;
	}

	Vector3& operator*=(float fl)
	{
		x *= fl;
		y *= fl;
		z *= fl;
		return *this;
	}

	Vector3& operator*=(const Vector3& v)
	{
		x *= v.x;
		y *= v.y;
		z *= v.z;
		return *this;
	}
	*/
};

class Vector2
{
public:
	Vector2() : x(0.f), y(0.f) {}

	Vector2(float _x, float _y) : x(_x), y(_y) {}

	~Vector2() {}

	float x;
	float y;



	inline float Dot(Vector2 v)
	{
		return x * v.x + y * v.y ;
	}

	inline float Distance(Vector2 v)
	{
		return float(sqrtf(powf(v.x - x, 2.0) + powf(v.y - y, 2.0)));
	}

	inline float Length()
	{
		return float(sqrtf(powf(x, 2.0) + powf(y, 2.0)));
	}

	Vector2 operator+(Vector2 v)
	{
		return Vector2(x + v.x, y + v.y);
	}

	Vector2 operator-(Vector2 v)
	{
		return Vector2(x - v.x, y - v.y);
	}
};
struct FQuat
{
	float x;
	float y;
	float z;
	float w;
};

struct FTransform
{
	FQuat rot;
	Vector3 translation;
	char pad[4];
	Vector3 scale;
	char pad1[4];
	D3DMATRIX ToMatrixWithScale()
	{
		D3DMATRIX m;
		m._41 = translation.x;
		m._42 = translation.y;
		m._43 = translation.z;

		float x2 = rot.x + rot.x;
		float y2 = rot.y + rot.y;
		float z2 = rot.z + rot.z;

		float xx2 = rot.x * x2;
		float yy2 = rot.y * y2;
		float zz2 = rot.z * z2;
		m._11 = (1.0f - (yy2 + zz2)) * scale.x;
		m._22 = (1.0f - (xx2 + zz2)) * scale.y;
		m._33 = (1.0f - (xx2 + yy2)) * scale.z;

		float yz2 = rot.y * z2;
		float wx2 = rot.w * x2;
		m._32 = (yz2 - wx2) * scale.z;
		m._23 = (yz2 + wx2) * scale.y;

		float xy2 = rot.x * y2;
		float wz2 = rot.w * z2;
		m._21 = (xy2 - wz2) * scale.y;
		m._12 = (xy2 + wz2) * scale.x;

		float xz2 = rot.x * z2;
		float wy2 = rot.w * y2;
		m._31 = (xz2 + wy2) * scale.z;
		m._13 = (xz2 - wy2) * scale.x;

		m._14 = 0.0f;
		m._24 = 0.0f;
		m._34 = 0.0f;
		m._44 = 1.0f;

		return m;
	}
};


class FRotator
{
public:
	FRotator() : Pitch(0.f), Yaw(0.f), Roll(0.f) {}

	FRotator(float _pitch, float _yaw, float _roll) : Pitch(_pitch), Yaw(_yaw), Roll(_roll) {}

	~FRotator() {}

	float Pitch;
	float Yaw;
	float Roll;

	inline double Length()
	{
		return sqrtf(powf(Pitch, 2.0) + powf(Yaw, 2.0) + powf(Roll, 2.0));
	};

	void Clamp()
	{
		if (Pitch > 180)
			Pitch -= 360;

		else if (Pitch < -180)
			Pitch += 360;

		if (Yaw > 180)
			Yaw -= 360;

		else if (Yaw < -180)
			Yaw += 360;

		if (Pitch < -89)
			Pitch = -89;

		if (Pitch > 89)
			Pitch = 89;

		while (Yaw < -180.0f)
			Yaw += 360.0f;

		while (Yaw > 180.0f)
			Yaw -= 360.0f;

		Roll = 0;
		return;
	}

	Vector3  ToVECTOR()
	{
		float radPitch = (float)(Pitch * 浮點精度 / 180.f);
		float radYaw = (float)(Yaw * 浮點精度 / 180.f);

		float SP = (float)sinf(radPitch);
		float CP = (float)cosf(radPitch);
		float SY = (float)sinf(radYaw);
		float CY = (float)cosf(radYaw);

		return  Vector3(CP * CY, CP * SY, SP);
	}

	D3DMATRIX GetAxes()
	{
		auto tempMatrix = Matrix();
		return tempMatrix;
	}

	D3DXMATRIX Matrix(Vector3 origin = Vector3(0, 0, 0))
	{
		float radPitch = (Pitch * float(浮點精度) / 180.f);
		float radYaw = (Yaw * float(浮點精度) / 180.f);
		float radRoll = (Roll * float(浮點精度) / 180.f);
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

	FRotator operator+(FRotator v)
	{
		return FRotator(Pitch + v.Pitch, Yaw + v.Yaw, Roll + v.Roll);
	}

	FRotator operator-(FRotator v)
	{
		return FRotator(Pitch - v.Pitch, Yaw - v.Yaw, Roll - v.Roll);
	}

	FRotator operator*(FRotator v)
	{
		return FRotator(Pitch * v.Pitch, Yaw * v.Yaw, Roll * v.Roll);
	}

	FRotator operator/(FRotator v)
	{
		return FRotator(Pitch / v.Pitch, Yaw / v.Yaw, Roll / v.Roll);
	}
};


struct FMinimalViewInfo
{
public:
	class Vector3 Location; // 0x0000(0x000C) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	class FRotator Rotation; // 0x000C(0x000C) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	float FOV; // 0x0018(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	float OrthoWIDth; // 0x001C(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	float OrthoNearClipPlane; // 0x0020(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	float OrthoFarClipPlane; // 0x0024(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	float AspectRatio; // 0x0028(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_IsPlainOldData)
	byte bConstrainAspectRatio; // 0x002C(0x0001) (CPF_Edit, CPF_BlueprintVisible)
	byte bUseFieldOfViewForLOD; // 0x002C(0x0001) (CPF_Edit, CPF_BlueprintVisible)
};

struct FCameraCacheEntry
{
public:
	float TimeStamp; // 0x0000(0x0004) (CPF_ZeroConstructor, CPF_IsPlainOldData)
	unsigned char UnknownData00[0xC]; // 0x0004(0x000C) MISSED OFFSET
	struct FMinimalViewInfo POV; // 0x0010(0x0530)

};



template<typename T>  struct TArray
{
public:
	DWORD_PTR pData;
	int Count;
	int Max;

	T ReadValue(int nIndex, bool bDeref)
	{
		DWORD_PTR ptrData = pData + nIndex * 0x8;

		if (bDeref)
		{
			ptrData = driver->RPM<DWORD_PTR>(ptrData, 0x8);
		}
		driver->RPM<T>(ptrData, sizeof(T));
	}

	void SetValue(T value, int nIndex, bool bDeref)
	{
		DWORD_PTR ptrData = pData + nIndex * 0x8;
		if (bDeref)
		{
			ptrData = driver->RPM<DWORD_PTR>(ptrData, 0x8);
		}
		driver->WPM<T>(ptrData, sizeof(T));
	}
};/*
enum Bone2s : int
{
Root = 0,
Head = 6,
neck_01 = 5,

Spine_3 = 4,
Spine_2 = 3,
Spine_1 = 2,
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
enum Bones : int
{
	Root = 0,
	pelvis = 1,
	spine_01 = 2,
	spine_02 = 3,
	spine_03 = 4,
	neck_01 = 5,
	Head = 6,
	face_root = 7,
	eyebrows_pos_root = 8,
	eyebrows_root = 9,
	eyebrows_r = 10,
	eyebrows_l = 11,
	eyebrow_l = 12,
	eyebrow_r = 13,
	forehead_root = 14,
	forehead = 12,
	jaw_pos_root = 16,
	jaw_root = 17,
	jaw = 18,
	mouth_down_pos_root = 19,
	mouth_down_root = 20,
	lip_bm_01 = 21,
	lip_bm_02 = 22,
	lip_br = 23,
	lip_bl = 24,
	jaw_01 = 25,
	jaw_02 = 26,
	cheek_pos_root = 27,
	cheek_root = 28,
	cheek_r = 29,
	cheek_l = 30,
	nose_sIDe_root = 31,
	nose_sIDe_r_01 = 32,
	nose_sIDe_r_02 = 33,
	nose_sIDe_l_01 = 34,
	nose_sIDe_l_02 = 35,
	eye_pos_r_root = 36,
	eye_r_root = 37,
	eye_rot_r_root = 38,
	eye_lID_u_r = 39,
	eye_r = 40,
	eye_lID_b_r = 41,
	eye_pos_l_root = 42,
	eye_l_root = 43,
	eye_rot_l_root = 44,
	eye_lID_u_l = 45,
	eye_l = 46,
	eye_lID_b_l = 47,
	nose_pos_root = 48,
	nose = 49,
	mouth_up_pos_root = 50,
	mouth_up_root = 51,
	lip_ul = 52,
	lip_um_01 = 53,
	lip_um_02 = 54,
	lip_ur = 55,
	lip_l = 56,
	lip_r = 57,
	hair_root = 58,
	hair_b_01 = 59,
	hair_b_02 = 60,
	hair_l_01 = 61,
	hair_l_02 = 62,
	hair_r_01 = 63,
	hair_r_02 = 64,
	hair_f_02 = 65,
	hair_f_01 = 66,
	hair_b_pt_01 = 67,
	hair_b_pt_02 = 68,
	hair_b_pt_03 = 69,
	hair_b_pt_04 = 70,
	hair_b_pt_05 = 71,
	camera_fpp = 72,
	GunReferencePoint = 73,
	GunRef = 74,
	breast_l = 75,
	breast_r = 76,
	clavicle_l = 77,
	upperarm_l = 78,
	lowerarm_l = 79,
	hand_l = 80,
	thumb_01_l = 81,
	thumb_02_l = 82,
	thumb_03_l = 83,
	thumb_04_l_MBONLY = 84,
	index_01_l = 85,
	index_02_l = 86,
	index_03_l = 87,
	index_04_l_MBONLY = 88,
	mIDdle_01_l = 89,
	mIDdle_02_l = 90,
	mIDdle_03_l = 91,
	mIDdle_04_l_MBONLY = 92,
	ring_01_l = 93,
	ring_02_l = 94,
	ring_03_l = 95,
	ring_04_l_MBONLY = 96,
	pinky_01_l = 97,
	pinky_02_l = 98,
	pinky_03_l = 99,
	pinky_04_l_MBONLY = 100,
	item_l = 101,
	lowerarm_twist_01_l = 102,
	upperarm_twist_01_l = 103,
	clavicle_r = 104,
	upperarm_r = 105,
	lowerarm_r = 106,
	hand_r = 107,
	thumb_01_r = 108,
	thumb_02_r = 109,
	thumb_03_r = 110,
	thumb_04_r_MBONLY = 111,
	index_01_r = 112,
	index_02_r = 113,
	index_03_r = 114,
	index_04_r_MBONLY = 115,
	mIDdle_01_r = 116,
	mIDdle_02_r = 117,
	mIDdle_03_r = 118,
	mIDdle_04_r_MBONLY = 119,
	ring_01_r = 120,
	ring_02_r = 121,
	ring_03_r = 122,
	ring_04_r_MBONLY = 123,
	pinky_01_r = 124,
	pinky_02_r = 125,
	pinky_03_r = 126,
	pinky_04_r_MBONLY = 127,
	item_r = 128,
	lowerarm_twist_01_r = 129,
	upperarm_twist_01_r = 130,
	BackPack = 131,
	backpack_01 = 132,
	backpack_02 = 133,
	Slot_Primary = 134,
	Slot_Secondary = 135,
	Slot_Melee = 136,
	slot_throwable = 137,
	coat_l_01 = 138,
	coat_l_02 = 139,
	coat_l_03 = 140,
	coat_l_04 = 141,
	coat_fl_01 = 142,
	coat_fl_02 = 143,
	coat_fl_03 = 144,
	coat_fl_04 = 145,
	coat_b_01 = 146,
	coat_b_02 = 147,
	coat_b_03 = 148,
	coat_b_04 = 149,
	coat_r_01 = 150,
	coat_r_02 = 151,
	coat_r_03 = 152,
	coat_r_04 = 153,
	coat_fr_01 = 154,
	coat_fr_02 = 155,
	coat_fr_03 = 156,
	coat_fr_04 = 157,
	thigh_l = 158,
	calf_l = 159,
	foot_l = 160,
	ball_l = 161,
	calf_twist_01_l = 162,
	thigh_twist_01_l = 163,
	thigh_r = 164,
	calf_r = 165,
	foot_r = 166,
	ball_r = 167,
	calf_twist_01_r = 168,
	thigh_twist_01_r = 169,
	Slot_SIDeArm = 170,
	skirt_l_01 = 171,
	skirt_l_02 = 172,
	skirt_l_03 = 173,
	skirt_f_01 = 174,
	skirt_f_02 = 175,
	skirt_f_03 = 176,
	skirt_b_01 = 177,
	skirt_b_02 = 178,
	skirt_b_03 = 179,
	skirt_r_01 = 180,
	skirt_r_02 = 181,
	skirt_r_03 = 182,
	ik_hand_root = 183,
	ik_hand_gun = 184,
	ik_hand_r = 185,
	ik_hand_l = 186,
	ik_aim_root = 187,
	ik_aim_l = 188,
	ik_aim_r = 189,
	ik_foot_root = 190,
	ik_foot_l = 191,
	ik_foot_r = 192,
	camera_tpp = 193,
	ik_target_root = 194,
	ik_target_l = 195,
	ik_target_r = 196,
	VB_spine_03_spine_03 = 197,
	VB_upperarm_r_lowerarm_r = 198
};

extern 驅動* driver;
extern int Actorids[1];
extern int 吉普車[3];
extern int 轎車[4];
extern int 摩托[8];
extern int 越野[10];
extern int 巴士[5];
extern int 皮卡[12];
extern int 大船[2];
extern int 遊艇[4];
extern int 跑車[12];
extern int 羅尼[5];
extern int 嘟嘟車[5];
extern int 迷你摩托[6];
extern int 飛機[7];
extern int 空投[1];
extern int 超級空投[1];
extern int 防彈車[3];
extern int Grenade[1];
extern int Molotov[1];
extern int 骨灰盒;
extern int 物品[2];



struct CollisionBitField
{
	unsigned char                                      UnknownData04 : 1;                                        // 0x009E(0x0001)
	unsigned char                                      bActorEnableCollision : 1;                                // 0x009E(0x0001)
	unsigned char                                      UnknownData05 : 1;                                        // 0x009E(0x0001)
	unsigned char                                      bReplicates : 1;                                          // 0x009E(0x0001) (Edit, BlueprintVisible, BlueprintReadOnly, DisableEditOnInstance)
};

struct AActorStruct
{
	unsigned char                                      bHidden : 1;                                              // 0x009C(0x0001) (Edit, BlueprintVisible, BlueprintReadOnly, Net)
	unsigned char                                      bNetTemporary : 1;                                        // 0x009C(0x0001)
	unsigned char                                      bNetStartup : 1;                                          // 0x009C(0x0001)
	unsigned char                                      bOnlyRelevantToOwner : 1;                                 // 0x009C(0x0001) (Edit, BlueprintVisible, BlueprintReadOnly, DisableEditOnInstance)
	unsigned char                                      bAlwaysRelevant : 1;                                      // 0x009C(0x0001) (Edit, BlueprintVisible, DisableEditOnInstance)
	unsigned char                                      bReplicateMovement : 1;                                   // 0x009C(0x0001) (Edit, Net, DisableEditOnInstance)
	unsigned char                                      bTearOff : 1;                                             // 0x009C(0x0001) (Net)
	unsigned char                                      bExchangedRoles : 1;                                      // 0x009C(0x0001) (Transient)
};

//物质结构
struct TArray_UItem
{
	ULONGLONG Items;//8
	int Count;//4
};
