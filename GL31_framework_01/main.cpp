//=============================================================================
//
//	タイトル	メインファイル
//	ファイル名	main.cpp
//	作成者		AT13A284_07 池田達哉
//	作成日		2016/04/21
//
//=============================================================================
//=============================================================================
//	インクルード
//=============================================================================
#include "main.h"
#include "manager.h"
#include "cameraGL.h"
#include <string.h>
#include "resource.h"
#include <commctrl.h>
//#include <afxwin.h>
#include "sceneModel.h"

#pragma once
#pragma comment(lib, "ComCtl32.lib") //ライブラリのリンク

//=============================================================================
//	プロトタイプ
//=============================================================================
LRESULT	CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//=============================================================================
//	グローバル変数
//=============================================================================
static float	g_fCountFPS;	// FPSカウンタ

//=============================================================================
//	関数名:WinMain
//	引数:HINSTANCE hInstance
//		:HINSTANCE hPrevInstance
//		:LPSTR lpCmdLine
//		:int nCmdShow
//	戻り値:int
//	説明:メイン関数
//=============================================================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wcex = {
		sizeof(WNDCLASSEX), CS_CLASSDC, WndProc, 0, 0, hInstance,
		(HICON)LoadImage(hInstance, MAKEINTRESOURCE(IDI_ICON1), IMAGE_ICON, NULL, NULL, (LR_DEFAULTCOLOR | LR_SHARED)),
		LoadCursor(NULL, IDC_ARROW), (HBRUSH)(COLOR_WINDOW + 1), NULL, "NullWindow", NULL
	};
	MSG		msg;
	RECT	rect = { 0, 0, (LONG)SCREEN_WIDTH, (LONG)SCREEN_HEIGHT };
	DWORD	dwFrameCount;
	DWORD	dwCurrentTime;
	DWORD	dwExecLastTime;
	DWORD	dwFPSLastTime;
	HWND	hWnd;			// メインウィンドウハンドル
	

	timeBeginPeriod(1);
	dwFrameCount =
	dwCurrentTime = 0;
	dwExecLastTime =
	dwFPSLastTime = timeGetTime();
	
	RegisterClassEx(&wcex);
	hWnd = CreateWindowEx(
		0, "NullWindow", "GL31_framework", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		(SCREEN_WIDTH  + GetSystemMetrics(SM_CXFIXEDFRAME) * 2),
		(SCREEN_HEIGHT + GetSystemMetrics(SM_CYFIXEDFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION)),
		NULL, NULL, hInstance, NULL);
	if(!hWnd)
	{
		return false;
	}

	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);
	rect.right -= rect.left;
	rect.bottom -= rect.top;

	// 初期化処理
	CManager::Init(hInstance, hWnd, TRUE);

	// ウィンドウ初期化
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	// 無限ループ
	while(1)
	{
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{
			if(msg.message == WM_QUIT)
			{
				break;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			// FPS固定化(60FPS)
			dwCurrentTime = timeGetTime();
			if((dwCurrentTime - dwFPSLastTime) >= 500)
			{
				g_fCountFPS = (dwFrameCount * 1000.0f) / (dwCurrentTime - dwFPSLastTime);
				dwFPSLastTime = dwCurrentTime;
				dwFrameCount = 0;
			}
			if((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{
				dwExecLastTime = dwCurrentTime;

				// Update処理
				CManager::Update();
				
				// Draw処理
				CManager::Draw();

				dwFrameCount++;
			}
		}
	}
	UnregisterClass("NullWindow", wcex.hInstance);
	
	// レンダラ破棄
	CManager::Uninit(hWnd);


	timeEndPeriod(1);


	return (int)msg.wParam;
}

//=============================================================================
//	関数名:WndProc
//	引数:HINSTANCE hWnd(ウィンドウハンドル)
//		:UINT uMsg
//		:WPARAM wParam
//		:LPARAM lParam
//	戻り値:LRESULT
//	説明:ウィンドウプロシージャ
//=============================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int	nID;
	int	a = 0;
	

	switch(uMsg)
	{
	case WM_CREATE:
		break;

	case WM_SIZE:
		SendMessage(hWnd, uMsg, wParam, lParam);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch(wParam)
		{
		case VK_ESCAPE:
			nID = MessageBox(hWnd, "ウィンドウを閉じますか？", "ウィンドウの終了", MB_YESNO);
			if(nID == IDYES)
			{
				DestroyWindow(hWnd);
			}
			break;
		}
		break;
	default:
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//=============================================================================
//	関数名	:GetFPS
//	引数	:無し
//	戻り値	:int
//	説明	:FPSの値を受け渡す
//=============================================================================
float GetFPS(void)
{
	return g_fCountFPS;
}