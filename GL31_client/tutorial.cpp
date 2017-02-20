//=============================================================================
//
//	タイトル	タイトル処理
//	ファイル名	tutorial.cpp
//	作成者		AT13A284_07 池田達哉
//	作成日		2016/07/12
//
//=============================================================================
//=============================================================================
//	インクルード
//=============================================================================
#include "tutorial.h"
#include "manager.h"
#include "input.h"
#include "fade.h"
#include "scene2DGL.h"

//=============================================================================
//	静的メンバ変数
//=============================================================================

//=============================================================================
//	関数名	:Init
//	引数	:無し
//	戻り値	:無し
//	説明	:初期化処理を行う。
//=============================================================================
void CTutorial::Init(void)
{
	m_TutorialBG = CScene2DGL::Create(VECTOR3(SCREEN_WIDTH_HALF, SCREEN_HEIGHT_HALF, 0.0f),
		VECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT),
		".\\data\\TEXTURE\\tutorial000.png");
	//m_PushEnter = CScene2DGL::Create(VECTOR3(SCREEN_WIDTH_HALF, (SCREEN_HEIGHT * 0.8f), 0.0f),
	//	VECTOR2((SCREEN_WIDTH * 0.4f), (SCREEN_HEIGHT * 0.05f)),
	//	".\\data\\TEXTURE\\pushbutton000.tga");

	m_Alpha = 0.0f;
}

//=============================================================================
//	関数名	:Uninit
//	引数	:無し
//	戻り値	:無し
//	説明	:終了処理を行う。
//=============================================================================
void CTutorial::Uninit(void)
{
	CSceneGL::DeleteAll();
}

//=============================================================================
//	関数名	:Update
//	引数	:無し
//	戻り値	:無し
//	説明	:更新処理を行う。
//=============================================================================
void CTutorial::Update(void)
{
	// シーン更新
	CSceneGL::UpdateAll();
	if(KT_ENTER)
	{
		CFade::Start(new CGame, MODE_GAME, FS_OUT);
	}
}

//=============================================================================
//	関数名	:Draw
//	引数	:無し
//	戻り値	:無し
//	説明	:描画処理を行う。
//=============================================================================
void CTutorial::Draw(void)
{
	m_Alpha += 0.05f;
	//m_PushEnter->SetColor((cosf(m_Alpha) * 0.5f + 0.5f), 1.0f, 1.0f, 1.0f);

	// シーン描画
	CSceneGL::DrawAll();
}