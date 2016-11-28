//=============================================================================
//
//	�^�C�g��	���C���t�@�C��
//	�t�@�C����	main.cpp
//	�쐬��		AT13A284_07 �r�c�B��
//	�쐬��		2016/04/21
//
//=============================================================================
//=============================================================================
//	�C���N���[�h
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
#pragma comment(lib, "ComCtl32.lib") //���C�u�����̃����N

//=============================================================================
//	�v���g�^�C�v
//=============================================================================
LRESULT	CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//=============================================================================
//	�O���[�o���ϐ�
//=============================================================================
static float	g_fCountFPS;	// FPS�J�E���^

//=============================================================================
//	�֐���:WinMain
//	����:HINSTANCE hInstance
//		:HINSTANCE hPrevInstance
//		:LPSTR lpCmdLine
//		:int nCmdShow
//	�߂�l:int
//	����:���C���֐�
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
	HWND	hWnd;			// ���C���E�B���h�E�n���h��
	

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

	// ����������
	CManager::Init(hInstance, hWnd, TRUE);

	// �E�B���h�E������
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	// �������[�v
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
			// FPS�Œ艻(60FPS)
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

				// Update����
				CManager::Update();
				
				// Draw����
				CManager::Draw();

				dwFrameCount++;
			}
		}
	}
	UnregisterClass("NullWindow", wcex.hInstance);
	
	// �����_���j��
	CManager::Uninit(hWnd);


	timeEndPeriod(1);


	return (int)msg.wParam;
}

//=============================================================================
//	�֐���:WndProc
//	����:HINSTANCE hWnd(�E�B���h�E�n���h��)
//		:UINT uMsg
//		:WPARAM wParam
//		:LPARAM lParam
//	�߂�l:LRESULT
//	����:�E�B���h�E�v���V�[�W��
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
			nID = MessageBox(hWnd, "�E�B���h�E����܂����H", "�E�B���h�E�̏I��", MB_YESNO);
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
//	�֐���	:GetFPS
//	����	:����
//	�߂�l	:int
//	����	:FPS�̒l���󂯓n��
//=============================================================================
float GetFPS(void)
{
	return g_fCountFPS;
}