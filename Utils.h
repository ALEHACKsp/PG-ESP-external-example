#pragma once
#include "crappy.h"
#include "GameData.h"


void UpdateAddresses();
void testoffset();
BOOL CacheNames();
std::string GetNameFromID(ULONG64 GN1, int ID);
Vector3 GetLocalPlayerPos();
Vector3 取實體座標數據(ULONG64 實體);
float 取實體血量(ULONG64 pAActor);
float GetLocalPlayerHealth();
float GetActorGroggyHealth(ULONG64 pAActor);
int 是否吉普(int ID);
int 是否轎車(int ID);
int 是否越野(int ID);
int 是否摩托(int ID);
int 是否大船(int ID);
int 是否遊艇(int ID);
int 是否巴士(int ID);
int 是否皮卡(int ID);
int 是否空投(int ID);
int 是否超級空投(int ID);
int 是否骨灰盒(int ID);
int 是否跑車(int ID);
int 是否羅尼(int ID);
int 是否嘟嘟車(int ID);
int 是否迷你摩托(int ID);
int 是否防彈車(int ID);
int 是否手雷(int ID);
int 是否燃燒瓶(int ID);
int  是否飛機(int ID);
void 過濾物品(std::string name, Vector3 screenloc, int 距離, int onece);
void 過濾盒子物品(std::string name, Vector3 screenloc, int onece);
ULONG64 FindGnames();

char* BASE64解碼(const char *bdata);
void 繪製骨骼(ULONG64 mesh, Color color, int ID);

Vector3 WorldToScreen(Vector3 WorldLocation);
Vector3 WorldToScreen2(Vector3 WorldLocation, Vector3 Rotators);
//FCameraCacheEntry GetCameraCache();
Vector3 GetBoneWithRotation(ULONG64 mesh, int ID);
Vector3 GetBonePos(ULONG64 mesh, int BonePos);
void drawstyle(Vector3 實體屏幕座標, ULONG64 mesh, Vector3 head, Vector3 Rfoot, int 長, int 中, int 高, int 寬, Color 顏色, int ID);
Vector3 predict(Vector3 TargetPos, float Distance, Vector3 TargetVelocity, float InitialSpeed, Vector3 grav);
Vector3 GetPlayerVelocity(ULONG64 pAActor);
ULONG64 GetVehiclePawn(ULONG64 pActor);
int GetSeatIndex(ULONG64 addr);
Vector3 SubD3DXVECTOR3(Vector3 VecA, Vector3 VecB);
uintptr_t FindPattern(const char* pattern);
void LoadModule2();