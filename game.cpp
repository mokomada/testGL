/*******************************************************************************
* タイトル ゲーム画面各種処理呼び出し
* ファイル名 game.cpp
* 作成者 AT-13A-284 秋間雄太
* 作成日 2016/07/19
*******************************************************************************/

/*******************************************************************************
* インクルードファイル
*******************************************************************************/

#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "mode.h"
#include "fade.h"
#include "game.h"
#include "result.h"
#include "title.h"
#include "scene.h"
#include "scene2D.h"
#include "scene3D.h"
#include "sceneX.h"
#include "camera.h"
#include "light.h"
#include "input.h"
#include "meshfield.h"
#include "debugProc.h"
#include "billboard.h"
#include "meshwater.h"
#include "meshworld.h"
#include "score.h"
#include "player.h"
#include "enemy.h"
#include "sound.h"


/*******************************************************************************
* スタティック変数初期化
*******************************************************************************/

CCamera *CGame::m_camera = NULL; // カメラ
CLight *CGame::m_light = NULL; // ライト
CPlayer *CGame::m_player = NULL; // プレイヤー情報
CScore *CGame::m_score = NULL; // スコア情報
CEnemy *CGame::m_enemy[ENEMY_MAX] = {NULL}; // 敵情報

/*******************************************************************************
* 関数名：InitGame
* 引数：なし
* 戻り値：true or false : 初期化が成功したか否か
* 説明：ゲーム画面の初期化
*******************************************************************************/

void CGame::Init(void) {
	m_camera = new CCamera;
	m_camera -> Init( );

	m_light = new CLight;
	m_light -> Init( );

	CMeshfield::Create( );

	CSceneX::Create( );

	CBillboard::Create( );

	CMeshwater::Create( );

	CMeshworld::Create( );

	m_score = CScore::Create( );

	m_player = CPlayer::Create( );

	m_enemy[0] = CEnemy::Create( );

	m_enemy[1] = CEnemy::Create( );

	m_enemy[2] = CEnemy::Create( );

	InitDebugProc( );

	CSound::StopSound(SOUND_LABEL_BGM001);
	CSound::PlaySound(SOUND_LABEL_BGM000);
}


/*******************************************************************************
* 関数名：UninitGame
* 引数：なし
* 戻り値：なし
* 説明：ゲーム画面の終了処理
*******************************************************************************/

void CGame::Uninit(void) {
	if(m_camera != NULL) {
		m_camera -> Uninit( );
		delete m_camera;
		m_camera = NULL;
	}

	if(m_light != NULL) {
		m_light -> Uninit( );
		delete m_light;
		m_light = NULL;
	}

	CScene::UninitAll( );

	UninitDebugProc( );
}


/*******************************************************************************
* 関数名：UpdateGame
* 引数：なし
* 戻り値：なし
* 説明：ゲーム画面の更新
*******************************************************************************/

void CGame::Update(void) {
	CInput *input;
	input = CManager::GetInput( );

	CFade *getFade;
	getFade = CManager::GetFade( );
	FADE fade = getFade -> GetFade( );

	m_camera -> Update( );

	if(fade == FADE_NONE) {

		m_light -> Update( );

		CScene::UpdateAll( );

		if(input -> GetKeyboardTrigger(DIK_RETURN) ) {
			CFade::SetFade(FADE_OUT, new CResult);
		}
	}
}


/*******************************************************************************
* 関数名：DrawGame
* 引数：なし
* 戻り値：なし
* 説明：ゲーム画面の描画
*******************************************************************************/

void CGame::Draw(void) {
	m_camera -> SetCamera( );

	CScene::DrawAll( );

	DrawDebugProc( );
}

/*******************************************************************************
* 関数名：GetCamera
* 引数：なし
* 戻り値：m_camera
* 説明：m_cameraのアドレスを返す
*******************************************************************************/

CCamera *CGame::GetCamera(void) {
	return m_camera;
}


/*******************************************************************************
* 関数名：GetPlayer
* 引数：なし
* 戻り値：m_player
* 説明：m_playerのアドレスを返す
*******************************************************************************/

CPlayer *CGame::GetPlayer(void) {
	return m_player;
}


/*******************************************************************************
* 関数名：GetEnemy
* 引数：なし
* 戻り値：m_enemy
* 説明：m_enemyのアドレスを返す
*******************************************************************************/

CEnemy *CGame::GetEnemy(void) {
	return m_enemy[0];
}
