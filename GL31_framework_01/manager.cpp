//=============================================================================
//
//	タイトル	カメラファイル
//	ファイル名	light.cpp
//	作成者		AT13A284_07 池田達哉
//	作成日		2016/04/26
//
//=============================================================================
//=============================================================================
//	インクルード
//=============================================================================
#include <vector>
#include "manager.h"
#include "main.h"
#include "mode.h"
#include "fade.h"
//#include "DebugProc.h"
#include "rendererGL.h"
#include "sceneGL.h"
#include "cameraGL.h"
#include "lightGL.h"
#include "scene2DGL.h"

//=============================================================================
//	静的メンバ変数
//=============================================================================
CMode		*CManager::m_Mode;			// モードクラス
CInput		*CManager::m_Input;			// 入力のインスタンス
CCameraGL	*CManager::m_Camera;		// カメラのインスタンス
CLightGL	*CManager::m_Light;			// ライトのインスタンス
CRendererGL	*CManager::m_RendererGL;	// レンダラ(GL)

//=============================================================================
//	関数名	:Init
//	引数	:無し
//	戻り値	:無し
//	説明	:初期化処理を行う。
//=============================================================================
void CManager::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	// レンダラ初期化
	m_RendererGL = new CRendererGL();
	m_RendererGL->Init(hWnd);

	// 各種インスタンス生成
	m_Mode			= new CTitle();
	m_Input			= new CInput();
	m_Camera		= new CCameraGL();
	m_Light			= new CLightGL();

	// 初期化処理
	m_Mode->Init();
	CFade::Init();
	m_Input->InitKeyboard(hInstance, hWnd);
	m_Camera->Init();
	m_Light->Init();
	CSound::Init();
}

//=============================================================================
//	関数名	:Uninit
//	引数	:無し
//	戻り値	:無し
//	説明	:終了処理を行う。
//=============================================================================
void CManager::Uninit(HWND hWnd)
{
	if(m_Input != NULL)
	{
		m_Input->UninitKeyboard();
		delete m_Input;
		m_Input = NULL;
	}
	if(m_RendererGL != NULL)
	{
		m_RendererGL->Uninit(hWnd);
		delete m_RendererGL;
		m_RendererGL = NULL;
	}
	if(m_Camera != NULL)
	{
		m_Camera->Uninit();
		delete m_Camera;
		m_Camera = NULL;
	}

	CSceneGL::DeleteAll(true);
	CSound::Uninit();
}

//=============================================================================
//	関数名	:Update
//	引数	:無し
//	戻り値	:無し
//	説明	:更新処理を行う。
//=============================================================================
void CManager::Update(void)
{
	m_Input->UpdateKeyboard();
	m_Camera->Update();
	m_Light->Update();
	m_RendererGL->Update();

	m_Mode->Update();
	CFade::Update();
}

//=============================================================================
//	関数名	:Draw
//	引数	:無し
//	戻り値	:無し
//	説明	:描画処理を行う。
//=============================================================================
void CManager::Draw(void)
{
	// 描画シーケンス開始
	m_RendererGL->Begin();

	// カメラの設定
	m_Camera->Set();

	// ライトの設定
	m_Light->Set();

	// モード描画
	m_Mode->Draw();

	// フェード描画
	CFade::Draw();

	// デバッグプロシージャ
	//m_DebugProc->Draw();
#ifdef _DEBUG
	//m_DebugProc->DebugProc("FPS:%d\n", GetFPS());
#endif

	// 描画シーケンス終了
	m_RendererGL->End();
}

//=============================================================================
//	関数名	:SetMode
//	引数	:CMode *mode(クラスのインスタンス)
//	戻り値	:無し
//	説明	:モードを切り替える。
//=============================================================================
void CManager::SetMode(CMode *mode)
{
	if((m_Mode != NULL))
	{
		// モードの終了処理
		m_Mode->Uninit();
		// モードのインスタンスの削除
		delete m_Mode;
	}
	if(mode != NULL)
	{
		// モードの切り替え
		m_Mode = mode;
		// モードの初期処理
		m_Mode->Init();
	}
}