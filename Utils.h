#pragma once
#include "crappy.h"
#include "GameData.h"


void UpdateAddresses();
void testoffset();
BOOL CacheNames();
std::string GetNameFromID(ULONG64 GN1, int ID);
Vector3 GetLocalPlayerPos();
Vector3 ȡ���w���˔���(ULONG64 ���w);
float ȡ���wѪ��(ULONG64 pAActor);
float GetLocalPlayerHealth();
float GetActorGroggyHealth(ULONG64 pAActor);
int �Ƿ���(int ID);
int �Ƿ��I܇(int ID);
int �Ƿ�ԽҰ(int ID);
int �Ƿ�Ħ��(int ID);
int �Ƿ��(int ID);
int �Ƿ��[ͧ(int ID);
int �Ƿ��ʿ(int ID);
int �Ƿ�Ƥ��(int ID);
int �Ƿ��Ͷ(int ID);
int �Ƿ񳬼���Ͷ(int ID);
int �Ƿ�ǻҺ�(int ID);
int �Ƿ���܇(int ID);
int �Ƿ��_��(int ID);
int �Ƿ���܇(int ID);
int �Ƿ�����Ħ��(int ID);
int �Ƿ����܇(int ID);
int �Ƿ�����(int ID);
int �Ƿ�ȼ��ƿ(int ID);
int  �Ƿ��w�C(int ID);
void �^�V��Ʒ(std::string name, Vector3 screenloc, int ���x, int onece);
void �^�V������Ʒ(std::string name, Vector3 screenloc, int onece);
ULONG64 FindGnames();

char* BASE64��a(const char *bdata);
void �L�u����(ULONG64 mesh, Color color, int ID);

Vector3 WorldToScreen(Vector3 WorldLocation);
Vector3 WorldToScreen2(Vector3 WorldLocation, Vector3 Rotators);
//FCameraCacheEntry GetCameraCache();
Vector3 GetBoneWithRotation(ULONG64 mesh, int ID);
Vector3 GetBonePos(ULONG64 mesh, int BonePos);
void drawstyle(Vector3 ���w��Ļ����, ULONG64 mesh, Vector3 head, Vector3 Rfoot, int �L, int ��, int ��, int ��, Color �ɫ, int ID);
Vector3 predict(Vector3 TargetPos, float Distance, Vector3 TargetVelocity, float InitialSpeed, Vector3 grav);
Vector3 GetPlayerVelocity(ULONG64 pAActor);
ULONG64 GetVehiclePawn(ULONG64 pActor);
int GetSeatIndex(ULONG64 addr);
Vector3 SubD3DXVECTOR3(Vector3 VecA, Vector3 VecB);
uintptr_t FindPattern(const char* pattern);
void LoadModule2();