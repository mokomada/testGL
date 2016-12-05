//=============================================================================
//
//	タイトル	ゲーム処理
//	ファイル名	title.cpp
//	作成者		AT13A284_07 池田達哉
//	作成日		2016/07/12
//
//=============================================================================
//=============================================================================
//	インクルード
//=============================================================================
#include "game.h"
#include <process.h>
#include "manager.h"
#include "input.h"
#include "fade.h"
#include "sceneGL.h"
#include "scene2DGL.h"
#include "scene3DGL.h"
#include "sceneModel.h"
#include "sceneBillboardGL.h"
#include "meshfield.h"
#include "score.h"
#include "trickgauge.h"
#include "effect2D.h"
#include "countdown.h"
//=============================================================================
//	プロトタイプ
//=============================================================================

//=============================================================================
//	静的メンバ変数
//=============================================================================
CMeshfield	*CGame::m_Meshfield;	// メッシュフィールド
vector<CSceneModel*>	CGame::m_Player;		// プレイヤーのインスタンス

//=============================================================================
//	関数名	:Init
//	引数	:無し
//	戻り値	:無し
//	説明	:初期化処理を行う。
//=============================================================================
void CGame::Init(void)
{
	m_Meshfield	= CMeshfield::Create();
	// 3D
	CMeshfield::Create(VECTOR3(0.0f, 0.0f, 0.0f));
	m_Player.resize(4);
	m_Player[0] = CSceneModel::Create(true, VECTOR3(0.0f, 50.0f, 0.0f));
	m_Player[1] = CSceneModel::Create(false, VECTOR3(-100.0f, 50.0f, 0.0f));
	m_Player[2] = CSceneModel::Create(false, VECTOR3(100.0f, 50.0f, 0.0f));
	m_Player[3] = CSceneModel::Create(false, VECTOR3(0.0f, 50.0f, 100.0f));

	CSceneBillboardGL::Create(VECTOR3(0.0f, 0.0f, 0.0f), VECTOR2(100.0f, 100.0f), "./data/TEXTURE/主ちゃ.png");

	// カウントダウン。起動する度にカウントダウンされると煩わしいためコメントアウト。タイマーが残り5秒になったらこれ呼んで下さい
//	CCountDown::Create(VECTOR3(SCREEN_WIDTH_HALF, SCREEN_HEIGHT * 0.5f, 0.0f), VECTOR2(200.0f, 100.0f), 1) ->SetCountDown( 9 );

	// 2D
	CScore::Create(VECTOR3(SCREEN_WIDTH_HALF, SCREEN_HEIGHT * 0.1f, 0.0f), VECTOR2(400.0f, 100.0f), 4);
	CTrickGauge::Create( );

	// BGM再生
	CSound::Play(SOUNDLABEL_BGM000);
}

//=============================================================================
//	関数名	:Uninit
//	引数	:無し
//	戻り値	:無し
//	説明	:終了処理を行う。
//=============================================================================
void CGame::Uninit(void)
{
	CSceneGL::DeleteAll();
}

//=============================================================================
//	関数名	:Update
//	引数	:無し
//	戻り値	:無し
//	説明	:更新処理を行う。
//=============================================================================
void CGame::Update(void)
{
	// シーン更新
	CSceneGL::UpdateAll();
	if(KT_ENTER)
	{
		CFade::Start(new CResult, MODE_RESULT, FS_OUT);
	}

	//	エフェクト表示テスト
	if(KT_E)
	{
		CEffect2D::Create(VECTOR3(0.0f,100.0f,0.0f),VECTOR2(100.0f,100.0f),ETYPE_EXPLODE01);
	}
}

//=============================================================================
//	関数名	:Draw
//	引数	:無し
//	戻り値	:無し
//	説明	:描画処理を行う。
//=============================================================================
void CGame::Draw(void)
{
	// シーン描画
	CSceneGL::DrawAll();
}