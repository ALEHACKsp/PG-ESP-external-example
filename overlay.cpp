#include <cstdarg>
#include "overlay.h"
#include "GameData.h"
#include "decrypt.hpp"
#include "crappy.hpp"
#include "crappy.cpp"

#pragma comment(lib, "dwmapi")
#pragma comment(lib,"d3d9.lib") 
#pragma comment(lib,"winmm.lib") 
#pragma comment(lib,"d3dx9.lib")
ImVec4 color = ImVec4(0.0f, 0.0f, 0.0f, 0.6f);

ID3D11Device*            g_pd3dDevice = NULL;
ID3D11DeviceContext*     g_pd3dDeviceContext = NULL;
IDXGISwapChain*          g_pSwapChain = NULL;
ID3D11RenderTargetView*  g_mainRenderTargetView = NULL;
ID3D11ShaderResourceView*	ImageBuffer = NULL;


    void CreateRenderTarget()
{
	VMProtectBeginUltra("CreateRenderTarget");
	ID3D11Texture2D* pBackBuffer;
	g_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
	g_pd3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &g_mainRenderTargetView);
	pBackBuffer->Release();
	VMProtectEnd();
}

    void CleanupRenderTarget()
{
	VMProtectBeginUltra("CleanupRenderTarget");
	if (g_mainRenderTargetView) { g_mainRenderTargetView->Release(); g_mainRenderTargetView = NULL; }
	VMProtectEnd();
}

    void CleanupDeviceD3D()
{
	VMProtectBeginUltra("CleanupDeviceD3D");
	CleanupRenderTarget();
	if (g_pSwapChain) { g_pSwapChain->Release(); g_pSwapChain = NULL; }
	if (g_pd3dDeviceContext) { g_pd3dDeviceContext->Release(); g_pd3dDeviceContext = NULL; }
	if (g_pd3dDevice) { g_pd3dDevice->Release(); g_pd3dDevice = NULL; }
	VMProtectEnd();
}

    HRESULT CreateDeviceD3D(HWND Hwnd)
{
	VMProtectBeginUltra("CreateDeviceD3D");
	// Setup swap chain
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 2;
	sd.BufferDesc.Width = s_width;
	sd.BufferDesc.Height = s_height;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = Hwnd;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = TRUE;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	UINT createDeviceFlags = 0;
	//createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
	D3D_FEATURE_LEVEL featureLevel;
	const D3D_FEATURE_LEVEL featureLevelArray[2] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0, };
	if (D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, createDeviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION, &sd, &g_pSwapChain, &g_pd3dDevice, &featureLevel, &g_pd3dDeviceContext) != S_OK)
		return E_FAIL;

	CreateRenderTarget();

	return S_OK;
	VMProtectEnd();
}


extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
		return true;

	switch (msg)
	{
	case WM_SIZE:
		if (g_pd3dDevice != NULL && wParam != SIZE_MINIMIZED)
		{
			ImGui_ImplDX11_InvalidateDeviceObjects();
			CleanupRenderTarget();
			g_pSwapChain->ResizeBuffers(0, (UINT)LOWORD(lParam), (UINT)HIWORD(lParam), DXGI_FORMAT_UNKNOWN, 0);
			CreateRenderTarget();
			ImGui_ImplDX11_CreateDeviceObjects();

		}
		return 0;
	case WM_SYSCOMMAND:
		if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
			return 0;
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}


    void overlay::Begin()
{
	VMProtectBeginUltra("Begin");

	// Start the Dear ImGui frame
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	VMProtectEnd();
}

    void overlay::End()
{


	//VMProtectBeginUltra("DrawEnd");
	ImGui::Render();
	g_pd3dDeviceContext->OMSetRenderTargets(1, &g_mainRenderTargetView, NULL);
	g_pd3dDeviceContext->ClearRenderTargetView(g_mainRenderTargetView, (float*)&color);
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	//g_pSwapChain->Present(1, 0); // Present with vsync
	g_pSwapChain->Present(0, 0); // Present without vsync
	//ImGui::EndFrame(); maybe is here
	//VMProtectEnd();
}

	void overlay::initD3D(HWND hWnd)
	{
		/*
		d3d = Direct3DCreate9(D3D_SDK_VERSION);    // create the Direct3D interface

		D3DPRESENT_PARAMETERS d3dpp;    // create a struct to hold various device information

			ZeroMemory(&d3dpp, sizeof(d3dpp));    // clear out the struct for use
		d3dpp.Windowed = TRUE;    // program windowed, not fullscreen
		d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;    // discard old frames
		d3dpp.hDeviceWindow = hWnd;    // set the window to be used by Direct3D
		d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;     // set the back buffer format to 32-bit
		d3dpp.BackBufferWidth = s_width;    // set the wIDth of the buffer
		d3dpp.BackBufferHeight = s_height;    // set the height of the buffer
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;//»òÕßD3DPRENSENT_INTERVAL_DEFAULT¸üºÃD3DPRESENT_INTERVAL_IMMEDIATE
		d3dpp.EnableAutoDepthStencil = TRUE;
		d3dpp.AutoDepthStencilFormat = D3DFMT_D16;


		// create a device class using this information and the info from the d3dpp stuct
		d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &d3ddev);
		D3DXCreateFontA(d3ddev, 18, 7, FW_HEAVY, 1, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Arial", &pFont);
		D3DXCreateLine(d3ddev, &d3dLine);
		*/
		//initd3d11(hWnd, "arialuni.TTF", 18.0);

		if (CreateDeviceD3D(hWnd) < 0)
		{
			CleanupDeviceD3D();
		
		}
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;	
		io.DeltaTime = 1.0f / 144.0f;//or io.DeltaTime = 1.0f / 144.0f;
		ImGui_ImplWin32_Init(hWnd);	
		ImGui_ImplDX11_Init(g_pd3dDevice, g_pd3dDeviceContext);
		ImGui::StyleColorsDark();
		io.Fonts->AddFontFromFileTTF("arialuni.TTF", 20.0, NULL, io.Fonts->GetGlyphRangesChineseSimplifiedCommon());
		//io.Fonts->AddFontFromFileTTF("msyhbd.ttc", 20.0, NULL, io.Fonts->GetGlyphRangesChineseFull());
	}

	void overlay::DestoryDX11(HWND hwnd) {
		VMProtectBeginUltra("DestoryDX11");
		ImGui_ImplDX11_Shutdown();
		ImGui_ImplWin32_Shutdown();
		ImGui::EndFrame();
		ImGui::DestroyContext();
		CleanupDeviceD3D();
		DestroyWindow(hwnd);
		VMProtectEnd();
	}
	/*
	std::string string_To_UTF8(const std::string & str)
	{
		int nwLen = ::MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);

		wchar_t * pwBuf = new wchar_t[nwLen + 1];
		ZeroMemory(pwBuf, nwLen * 2 + 2);

		::MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.length(), pwBuf, nwLen);

		int nLen = ::WideCharToMultiByte(CP_UTF8, 0, pwBuf, -1, NULL, NULL, NULL, NULL);

		char * pBuf = new char[nLen + 1];
		ZeroMemory(pBuf, nLen + 1);

		::WideCharToMultiByte(CP_UTF8, 0, pwBuf, nwLen, pBuf, nLen, NULL, NULL);

		std::string retStr(pBuf);

		delete[]pwBuf;
		delete[]pBuf;

		pwBuf = NULL;
		pBuf = NULL;

		return retStr;
	}
	*/
	void overlay::ÀLÑuÎÄ×Ö(INT X, INT Y, Color color, LPD3DXFONT pFont, const char *cString, ...)
	{



		CHAR buf[512] = { NULL };
		va_list ArgumentList;
		va_start(ArgumentList, cString);
		_vsnprintf_s(buf, sizeof(buf), sizeof(buf) - strlen(buf), cString, ArgumentList);
		va_end(ArgumentList);
		/*
		HRESULT hRet;
		RECT rc[2];
		SetRect(&rc[0], X, Y, X, 0);
		SetRect(&rc[1], X, Y, X + 50, 50);

		hRet = D3D_OK;

		if (SUCCEEDED(hRet))
		{
			hRet = pFont->DrawTextA(NULL, buf, -1, &rc[1], DT_NOCLIP, D3DCOLOR_ARGB(color.A, color.R, color.G, color.B));
		}
		return hRet;
		*/
		//drawString(X, Y, color.R, color.G, color.B, color.A, buf);

		std::string utf_8_1 = buf;
		//std::string utf_8_1 = string_To_UTF8(buf);
		ImGui::GetOverlayDrawList()->AddText(ImVec2(X, Y), ImGui::ColorConvertFloat4ToU32(ImVec4(color.R / 255.0, color.G / 255.0, color.B / 255.0, color.A / 255.0)), utf_8_1.c_str());
		
	}

	void overlay::ÀLÑuÃèß…ÎÄ×Ö(INT X, INT Y, Color sidecolor, Color textcolor, LPD3DXFONT pFont, const char *cString, ...)
	{

		//¾´æÎÄ×Ö
		char buf[1024] = { 0 };
		// ...áá·½µÄ”µÖµ
		va_list va_alist;
		va_start(va_alist, cString);
		_vsnprintf_s(buf, sizeof(buf), sizeof(buf) - strlen(buf), cString, va_alist);
		va_end(va_alist);
		//drawString(X + 1, Y, sidecolor.R, sidecolor.G, sidecolor.B, sidecolor.A, buf);
		//drawString(X - 1, Y, sidecolor.R, sidecolor.G, sidecolor.B, sidecolor.A, buf);
		//drawString(X, Y + 1, sidecolor.R, sidecolor.G, sidecolor.B, sidecolor.A, buf);
		//drawString(X, Y - 1, sidecolor.R, sidecolor.G, sidecolor.B, sidecolor.A, buf);
		//drawString(X, Y, textcolor.R, textcolor.G, textcolor.B, textcolor.A, buf);
		std::string utf_8_1 = buf;
		//ImGui::GetOverlayDrawList()->AddText(ImVec2(X + 1, Y), ImGui::ColorConvertFloat4ToU32(ImVec4(sidecolor.R / 255.0, sidecolor.G / 255.0, sidecolor.B / 255.0, sidecolor.A / 255.0)), utf_8_1.c_str());
		//ImGui::GetOverlayDrawList()->AddText(ImVec2(X - 1, Y), ImGui::ColorConvertFloat4ToU32(ImVec4(sidecolor.R / 255.0, sidecolor.G / 255.0, sidecolor.B / 255.0, sidecolor.A / 255.0)), utf_8_1.c_str());
		//ImGui::GetOverlayDrawList()->AddText(ImVec2(X, Y + 1), ImGui::ColorConvertFloat4ToU32(ImVec4(sidecolor.R / 255.0, sidecolor.G / 255.0, sidecolor.B / 255.0, sidecolor.A / 255.0)), utf_8_1.c_str());
		//ImGui::GetOverlayDrawList()->AddText(ImVec2(X, Y - 1), ImGui::ColorConvertFloat4ToU32(ImVec4(sidecolor.R / 255.0, sidecolor.G / 255.0, sidecolor.B / 255.0, sidecolor.A / 255.0)), utf_8_1.c_str());
		ImGui::GetOverlayDrawList()->AddText(ImVec2(X, Y), ImGui::ColorConvertFloat4ToU32(ImVec4(textcolor.R / 255.0, textcolor.G / 255.0, textcolor.B / 255.0, textcolor.A / 255.0)), utf_8_1.c_str());
		/*
		CHAR buf[512] = { NULL };
		va_list ArgumentList;
		va_start(ArgumentList, cString);
		_vsnprintf_s(buf, sizeof(buf), sizeof(buf) - strlen(buf), cString, ArgumentList);
		va_end(ArgumentList);

		HRESULT hRet;
		RECT rc[2];
		SetRect(&rc[0], X, Y, X, 0);
		SetRect(&rc[1], X, Y, X + 50, 50);

		hRet = D3D_OK;

		if (SUCCEEDED(hRet))
		{
			hRet = pFont->DrawTextA(NULL, buf, -1, &rc[1], DT_NOCLIP, D3DCOLOR_ARGB(textcolor.A, textcolor.R, textcolor.G, textcolor.B));
		}
		return hRet;
		*/


	}

	void overlay::ÀLÑuˆAÈ¦(int x, int y, Color color,  int °ë¾¶,  int ÇúÂÊ,float ´Ö¼š)
	{
		/*
		float ég¸ô = ¸¡üc¾«¶È * 2.0 / ÇúÂÊ;
		for (float a = 0; a < (¸¡üc¾«¶È*2.0); a += ég¸ô)
		{
			float x1 = °ë¾¶ * cos(a) + x;
			float y1 = °ë¾¶ * sin(a) + y;
			float x2 = °ë¾¶ * cos(a + ég¸ô) + x;
			float y2 = °ë¾¶ * sin(a + ég¸ô) + y;
			ÀLÑu
			
			
			(x1, y1, x2, y2, îÉ«);
		}
		*/
		//drawcircle(x, y, °ë¾¶, color.R, color.G, color.B, color.A, ÇúÂÊ, ´Ö¼š);
		ImGui::GetOverlayDrawList()->AddCircle(ImVec2(x, y), °ë¾¶, ImGui::ColorConvertFloat4ToU32(ImVec4(color.R / 255.0, color.G / 255.0, color.B / 255.0, color.A / 255.0)), ÇúÂÊ, ´Ö¼š);

	}

	void overlay::ÀLÑuÌî³äˆAÈ¦(int x, int y, int °ë¾¶, int ÇúÂÊ, Color color)
	{
		/*
		float ég¸ô = ¸¡üc¾«¶È * 2.0 / ÇúÂÊ;
		for (float a = 0; a < (¸¡üc¾«¶È*2.0); a += ég¸ô)
		{
		float x1 = °ë¾¶ * cos(a) + x;
		float y1 = °ë¾¶ * sin(a) + y;
		float x2 = °ë¾¶ * cos(a + ég¸ô) + x;
		float y2 = °ë¾¶ * sin(a + ég¸ô) + y;
		ÀLÑu¾€—l(x1, y1, x2, y2, îÉ«);
		}
		*/
		//drawcirclefilled(x, y, °ë¾¶, color.R, color.G, color.B, color.A, ÇúÂÊ);
		ImGui::GetOverlayDrawList()->AddCircleFilled(ImVec2(x, y), °ë¾¶, ImGui::ColorConvertFloat4ToU32(ImVec4(color.R / 255.0, color.G / 255.0, color.B / 255.0, color.A / 255.0)), ÇúÂÊ);
	}

	void overlay::ÀLÑu¾€—l(int x, int y, int xx, int yy, Color color, float  thickness)
	{
		/*
		D3DXVECTOR2 dLine[2];

		d3dLine->SetWidth(2);

		dLine[0].x = x;
		dLine[0].y = y;

		dLine[1].x = xx;
		dLine[1].y = yy;

		d3dLine->Draw(dLine, 2, D3DCOLOR_ARGB(color.A, color.R, color.G, color.B));
		*/
		//drawline(x, y, xx, yy, color.R, color.G, color.B, color.A, 2);
		ImGui::GetOverlayDrawList()->AddLine(ImVec2(x, y), ImVec2(xx, yy), ImGui::ColorConvertFloat4ToU32(ImVec4(color.R / 255.0, color.G / 255.0, color.B / 255.0, color.A / 255.0)), thickness);
	}



	void overlay::ÀLÑu·½¿ò(int x, int y, int wIDth, int height, Color color)
	{
		/*
		D3DXVECTOR2 points[5];
		points[0] = D3DXVECTOR2(x, y);
		points[1] = D3DXVECTOR2(x + wIDth, y);
		points[2] = D3DXVECTOR2(x + wIDth, y + height);
		points[3] = D3DXVECTOR2(x, y + height);
		points[4] = D3DXVECTOR2(x, y);
		d3dLine->SetWidth(2);
		d3dLine->Draw(points, 5, D3DCOLOR_ARGB(color.A, color.R, color.G, color.B));
		*/
		//drawrect(x, y, wIDth, height, color.R, color.G, color.B, color.A, 1);
		ImGui::GetOverlayDrawList()->AddRect(ImVec2(x, y), ImVec2(x + wIDth, y + height), ImGui::ColorConvertFloat4ToU32(ImVec4(color.R / 255.0, color.G / 255.0, color.B / 255.0, color.A / 255.0)), 0, 0, 1);

	}

	void overlay::ÀLÑu¾ØÐÎ(int x, int y, int w, int h, Color color)
	{
		/*
		D3DRECT rec = { x, y, x + w, y + h };
		d3ddev->Clear(1, &rec, D3DCLEAR_TARGET, color, 0, 0);
		*/
		ImGui::GetOverlayDrawList()->AddRect(ImVec2(x, y), ImVec2(x + w, y + h), ImGui::ColorConvertFloat4ToU32(ImVec4(color.R / 255.0, color.G / 255.0, color.B / 255.0, color.A / 255.0)), 0, 0, 1);

	}

	void overlay::ÀLÑuÌî³ä¾ØÐÎ(int x, int y, int w, int h, Color color)
	{
		/*
		D3DXVECTOR2 vLine[2];

		d3dLine->SetWidth(abs(w));

		vLine[0].x = x + w / 2;
		vLine[0].y = y;
		vLine[1].x = x + w / 2;
		vLine[1].y = y + h;

		d3dLine->Draw(vLine, 2, D3DCOLOR_RGBA(r, g, b, a));
		*/
		//drawfilledrect(x, y, w, h, color.R, color.G, color.B, color.A);
		ImGui::GetOverlayDrawList()->AddRectFilled(ImVec2(x, y), ImVec2(x + w, y + h), ImGui::ColorConvertFloat4ToU32(ImVec4(0.5, 0.5, 0.5, 0.5)), 0, 0);
	}

	void overlay::ÀLÑuˆDÆ¬(int x, int y, int w, int h, LPCSTR MyImage)
	{

		//drawimage(x, y, w, h, MyImage);
		D3DX11CreateShaderResourceViewFromFileA(g_pd3dDevice, MyImage, 0, 0, &ImageBuffer, 0);
		ImGui::GetOverlayDrawList()->AddImage((ID3D11ShaderResourceView*)ImageBuffer, ImVec2(x, y), ImVec2(x + w, y + h));
	}


float GetDotDistance(int Xx, int Yy, int xX, int yY)
{
	return sqrt((yY - Yy) * (yY - Yy) + (xX - Xx) * (xX - Xx));
}

void DrawHealthBar(int x, int y, int height,float healthbar,Color color)
{


	float flBoxes = std::ceil(healthbar / 10.f);
	float flX = x - 7 - height / 4.f; float flY = y - 1;
	float flHeight = height / 10.f;
	float flMultiplier = 12 / 360.f; flMultiplier *= flBoxes - 1;

//	Color ColHealth = Color{ 255,flMultiplier, 1, 1 };

	render->ÀLÑu¾ØÐÎ(flX, flY, 4, height + 2, Color{ 125,80, 80, 80 });
	render->ÀLÑu¾ØÐÎ(flX, flY, 4, height + 2,  Color{ 255, 240, 240, 240 });
	render->ÀLÑu¾ØÐÎ(flX + 1, flY, 2, flHeight * flBoxes + 1, Color{ 255,255, 0, 0 });

//	for (int i = 0; i < 10; i++)
	//	ÀLÑu¼š¾€—l(flX, flY + i * flHeight, flX + 4, flY + i * flHeight, Color{ 255,0, 0, 0 });
}
