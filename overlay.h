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
extern HWND ß[‘ò´°¿Ú¾ä±þ;
extern MARGINS  margin;
extern LPD3DXFONT pFont;
extern ID3DXLine* d3dLine;
class overlay
{
public:
	void Begin();
	void End();
	void DestoryDX11(HWND hWnd);
	void ÀLÑuÎÄ×Ö(INT X, INT Y, Color Color, LPD3DXFONT pFont, const char *cString, ...);
	void ÀLÑuÃèß…ÎÄ×Ö(INT X, INT Y, Color sidecolor, Color textcolor, LPD3DXFONT pFont, const char *cString, ...);
	void initD3D(HWND hWnd);
	void ÀLÑuˆAÈ¦(int x, int y, Color color, int °ë¾¶, int ÇúÂÊ, float ´Ö¼š);
	void ÀLÑuÌî³äˆAÈ¦(int x, int y, int °ë¾¶, int ÇúÂÊ, Color color);
	void ÀLÑu¾€—l(int x, int y, int xx, int yy, Color color, float  thickness);

	void ÀLÑu·½¿ò(int x, int y, int wIDth, int height, Color color);
	void ÀLÑuÌî³ä¾ØÐÎ(int x, int y, int w, int h, Color color);
	void ÀLÑuˆDÆ¬(int x, int y, int w, int h, LPCSTR MyImage);
	void ÀLÑu¾ØÐÎ(int x, int y, int w, int h, Color color);
};

float GetDotDistance(int Xx, int Yy, int xX, int yY);
void DrawHealthBar(int x, int y, int Width, float healthbar, Color color);
LRESULT WINAPI  WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

