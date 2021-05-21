#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include <Dwmapi.h> 
#include <TlHelp32.h>
#include "crappy.hpp"
#pragma comment(lib,"d3d9.lib") 
#pragma comment(lib,"winmm.lib") 
#pragma comment(lib,"d3dx9.lib")





extern int s_width;
extern int s_height;


extern LPDIRECT3D9 d3d;
extern LPDIRECT3DDEVICE9 d3ddev;
extern HWND hWnd;
extern HWND �[�򴰿ھ��;
extern MARGINS  margin;
extern LPD3DXFONT pFont;
extern ID3DXLine* d3dLine;
class overlay
{
public:
	void Begin();
	void End();
	void DestoryDX11(HWND hWnd);
	void �L�u����(INT X, INT Y, Color Color, LPD3DXFONT pFont, const char *cString, ...);
	void �L�u��߅����(INT X, INT Y, Color sidecolor, Color textcolor, LPD3DXFONT pFont, const char *cString, ...);
	void initD3D(HWND hWnd);
	void �L�u�AȦ(int x, int y, Color color, int �뾶, int ����, float �ּ�);
	void �L�u���AȦ(int x, int y, int �뾶, int ����, Color color);
	void �L�u���l(int x, int y, int xx, int yy, Color color, float  thickness);

	void �L�u����(int x, int y, int wIDth, int height, Color color);
	void �L�u������(int x, int y, int w, int h, Color color);
	void �L�u�DƬ(int x, int y, int w, int h, LPCSTR MyImage);
	void �L�u����(int x, int y, int w, int h, Color color);
};

float GetDotDistance(int Xx, int Yy, int xX, int yY);
void DrawHealthBar(int x, int y, int Width, float healthbar, Color color);
LRESULT WINAPI  WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

