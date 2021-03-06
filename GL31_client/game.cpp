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
#include "square.h"
#include "player.h"
#include "sceneBillboardGL.h"
#include "meshfield.h"
#include "score.h"
#include "trickgauge.h"
#include "effect2D.h"
#include "countdown.h"
#include "confetti.h"
#include "wall.h"
#include "textureManager.h"
#include "skybox.h"
#include "bulletgauge.h"
#include "slope.h"
#include "network.h"

//=============================================================================
//	プロトタイプ
//=============================================================================

//=============================================================================
//	静的メンバ変数
//=============================================================================
CMeshfield			*CGame::m_Meshfield;	// メッシュフィールド
vector<CPlayer*>	CGame::m_Player;		// プレイヤーのインスタンス
int					CGame::m_GamaFrame;

//=============================================================================
//	関数名	:Init
//	引数	:無し
//	戻り値	:無し
//	説明	:初期化処理を行う。
//=============================================================================
void CGame::Init(void)
{
	CTextureManager::Init();
	CSkybox::Create();
	//m_Meshfield	= CMeshfield::Create();
	//3D
	CMeshfield::Create(VECTOR3(0.0f, 0.0f, 0.0f));

	m_Player.push_back(CPlayer::Create(0, VECTOR3(0.0f, 50.0f, -1300.0f) , VECTOR3(0.0f,0.0f,0.0f)));
	m_Player.push_back(CPlayer::Create(1, VECTOR3(-1300.0f, 50.0f, 0.0f) , VECTOR3(0.0f, PI * 0.5f, 0.0f) ));
	m_Player.push_back(CPlayer::Create(2, VECTOR3(1300.0f, 50.0f, 0.0f) , VECTOR3(0.0f, -PI * 0.5f, 0.0f) ));
	m_Player.push_back(CPlayer::Create(3, VECTOR3(0.0f, 50.0f, 1300.0f) , VECTOR3(0.0f, PI, 0.0f) ));

	//VECTOR3 Pos[4] = {VECTOR3(-200, 100, 500), VECTOR3(200, 100, 500) , VECTOR3(-200, 0, 0), VECTOR3(200, 0, 0) };
	//CSlope::Create(Pos, VECTOR3(0, 0, 0), "./data/TEXTURE/rocklong.png");

	//CSceneBillboardGL::Create(VECTOR3(0.0f, 0.0f, 0.0f), VECTOR2(100.0f, 100.0f), "./data/TEXTURE/rock.png");

	CSquare::Create(VECTOR3(0.0f, 50.0f, 1500.0f), VECTOR3(3000.0f, 100.0f, 1.0f), "./data/TEXTURE/rock.png", VECTOR4(1.0f, 1.0f, 1.0f, 1.0f));
	CSquare::Create(VECTOR3(0.0f, 50.0f, -1500.0f), VECTOR3(3000.0f, 100.0f, 1.0f), "./data/TEXTURE/rock.png", VECTOR4(1.0f, 1.0f, 1.0f, 1.0f));
	CSquare::Create(VECTOR3(1500.0f, 50.0f, 0.0f), VECTOR3(1.0f, 100.0f, 3000.0f), "./data/TEXTURE/rock.png", VECTOR4(1.0f, 1.0f, 1.0f, 1.0f));
	CSquare::Create(VECTOR3(-1500.0f, 50.0f, 0.0f), VECTOR3(1.0f, 100.0f, 3000.0f), "./data/TEXTURE/rock.png", VECTOR4(1.0f, 1.0f, 1.0f, 1.0f));

	CSquare::Create(VECTOR3(700.0f, 50.0f, 1200.0f), VECTOR3(800.0f, 100.0f, 50.0f), "./data/TEXTURE/rock.png", VECTOR4(1.0f, 1.0f, 1.0f, 1.0f));
	CSquare::Create(VECTOR3(-700.0f, 50.0f, 1200.0f), VECTOR3(800.0f, 100.0f, 50.0f), "./data/TEXTURE/rock.png", VECTOR4(1.0f, 1.0f, 1.0f, 1.0f));
	CSquare::Create(VECTOR3(700.0f, 50.0f, -1200.0f), VECTOR3(800.0f, 100.0f, 50.0f), "./data/TEXTURE/rock.png", VECTOR4(1.0f, 1.0f, 1.0f, 1.0f));
	CSquare::Create(VECTOR3(-700.0f, 50.0f, -1200.0f), VECTOR3(800.0f, 100.0f, 50.0f), "./data/TEXTURE/rock.png", VECTOR4(1.0f, 1.0f, 1.0f, 1.0f));

	CSquare::Create(VECTOR3(1200.0f, 50.0f, -700.0f), VECTOR3(50.0f, 100.0f, 800.0f), "./data/TEXTURE/rock.png", VECTOR4(1.0f, 1.0f, 1.0f, 1.0f));
	CSquare::Create(VECTOR3(1200.0f, 50.0f, 700.0f), VECTOR3(50.0f, 100.0f, 800.0f), "./data/TEXTURE/rock.png", VECTOR4(1.0f, 1.0f, 1.0f, 1.0f));

	CSquare::Create(VECTOR3(-1200.0f, 50.0f, -700.0f), VECTOR3(50.0f, 100.0f, 800.0f), "./data/TEXTURE/rock.png", VECTOR4(1.0f, 1.0f, 1.0f, 1.0f));
	CSquare::Create(VECTOR3(-1200.0f, 50.0f, 700.0f), VECTOR3(50.0f, 100.0f, 800.0f), "./data/TEXTURE/rock.png", VECTOR4(1.0f, 1.0f, 1.0f, 1.0f));

	CSquare::Create(VECTOR3( 0.0f, 50.0f, 800.0f), VECTOR3(1000.0f, 100.0f, 50.0f), "./data/TEXTURE/rock.png", VECTOR4(1.0f, 1.0f, 1.0f, 1.0f));
	CSquare::Create(VECTOR3(0.0f, 50.0f, -800.0f), VECTOR3(1000.0f, 100.0f, 50.0f), "./data/TEXTURE/rock.png", VECTOR4(1.0f, 1.0f, 1.0f, 1.0f));

	CSquare::Create(VECTOR3(800.0f, 50.0f, 0.0f), VECTOR3(50.0f, 100.0f, 1000.0f), "./data/TEXTURE/rock.png", VECTOR4(1.0f, 1.0f, 1.0f, 1.0f));
	CSquare::Create(VECTOR3(-800.0f, 50.0f, 0.0f), VECTOR3(50.0f, 100.0f, 1000.0f), "./data/TEXTURE/rock.png", VECTOR4(1.0f, 1.0f, 1.0f, 1.0f));

	CSquare::Create(VECTOR3(0.0f, 50.0f, 0.0f), VECTOR3(300.0f, 100.0f, 300.0f), "./data/TEXTURE/rock.png", VECTOR4(1.0f, 1.0f, 1.0f, 1.0f));

	//CWall::Create(VECTOR3(0.0f, 0.0f, 0.0f), VECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 50.0f, 50.0f, "./data/TEXTURE/rock.png");

	// カウントダウン。起動する度にカウントダウンされると煩わしいためコメントアウト。タイマーが残り5秒になったらこれ呼んで下さい
//	CCountDown::Create(VECTOR3(SCREEN_WIDTH_HALF, SCREEN_HEIGHT * 0.5f, 0.0f), VECTOR2(200.0f, 100.0f), 1) ->SetCountDown( 9 );
//	CConfetti::MasterCreate( );

	// 2D
	//CScore::Create(VECTOR3(SCREEN_WIDTH_HALF, SCREEN_HEIGHT * 0.1f, 0.0f), VECTOR2(400.0f, 100.0f), 4);
	CBulletGauge::Create( );
	//CTrickGauge::Create( );

	// BGM再生
	CSound::Play(SOUNDLABEL_BGM000);

	CNetwork::Clear();
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
	CTextureManager::Uninit();
	m_Player.clear();
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

	m_GamaFrame++;
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