/*******************************************************************************
* タイトル GM31 Xファイル描画
* ファイル名 sceneX.cpp
* 作成者 AT-13A-284 秋間雄太
* 作成日 2016/04/26
*******************************************************************************/

/*******************************************************************************
* インクルードファイル
*******************************************************************************/

#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "sceneX.h"
#include "enemy.h"
#include "camera.h"
#include "input.h"
#include "meshfield.h"
#include "debugProc.h"
#include "sound.h"
#include "score.h"
#include "player.h"
#include "game.h"


//*****************************************************************************
// スタティック変数の生成
//*****************************************************************************

//MODEL CEnemy::m_enemy = {D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0), 0};


/*******************************************************************************
* 関数名：CEnemy
* 引数：なし
* 戻り値：なし
* 説明：クラス生成時処理
*******************************************************************************/

CEnemy::CEnemy(int priority, OBJTYPE objType):CSceneX(priority, objType) {

}


/*******************************************************************************
* 関数名：~CEnemy
* 引数：なし
* 戻り値：なし
* 説明：クラス破棄時処理
*******************************************************************************/

CEnemy::~CEnemy( ) {

}


/*******************************************************************************
* 関数名：Init
* 引数：なし
* 戻り値：なし
* 説明：初期化処理
*******************************************************************************/

void CEnemy::Init(void) {
	CRenderer *renderer; // デバイス取得用変数
	renderer = CManager::GetRenderer( ); // レンダラのアドレス取得
	LPDIRECT3DDEVICE9 device = renderer -> GetDevice( ); // デバイス取得
	m_pTexture = NULL;

	D3DXLoadMeshFromX(ENEMY_NAME,
		D3DXMESH_SYSTEMMEM,
		device,
		NULL,
		&m_pBuffMat,
		NULL,
		&m_numMat,
		&m_pMesh);

	// 変数の初期化
	m_enemy.pos.x = ENEMY_POS_X + rand( ) % 40 - ENEMY_START_DISTANCE;
	if(m_enemy.pos.x < 0) {
		m_enemy.pos.x -= ENEMY_START_DISTANCE;
	}
	else{
		m_enemy.pos.x += ENEMY_START_DISTANCE;
	}

	m_enemy.pos.y = ENEMY_POS_Y;

	m_enemy.pos.z = ENEMY_POS_Z + rand( ) % 40 - ENEMY_START_DISTANCE;
	if(m_enemy.pos.z < 0) {
		m_enemy.pos.z -= ENEMY_START_DISTANCE;
	}
	else{
		m_enemy.pos.z += ENEMY_START_DISTANCE;
	}

	D3DXQuaternionIdentity(&m_enemy.rot);

	m_enemy.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_enemy.scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	m_enemy.jump = false;

	m_newRot = 0;

	m_moveChange = 0;

	m_respawn = 0;

	m_moveFlag = false;

	m_rnd = 0;

	// テクスチャ設定
	D3DXCreateTextureFromFile(device, ENEMY_TEXTURE_NAME, &m_pTexture);
}


/*******************************************************************************
* 関数名：Uninit
* 引数：なし
* 戻り値：なし
* 説明：終了処理
*******************************************************************************/

void CEnemy::Uninit(void) {
	if(m_pTexture != NULL) {
		m_pTexture -> Release( ); // テクスチャの開放
		m_pTexture = NULL;
	}

	if(m_pMesh != NULL) {
		m_pMesh -> Release( );
		m_pMesh = NULL;
	}

	if(m_pBuffMat != NULL) {
		m_pBuffMat -> Release( );
		m_pBuffMat = NULL;
	}
}


/*******************************************************************************
* 関数名：Update
* 引数：なし
* 戻り値：なし
* 説明：更新処理
*******************************************************************************/

void CEnemy::Update(void) {
	CCamera *get_camera;
	get_camera = CGame::GetCamera( ); // カメラ情報取得
	CAMERA camera = get_camera -> GetCameraData( );
	MODEL old_model = m_enemy; // 現在情報保持
	float field_height; // 地面の高さ
	D3DXVECTOR3 axis = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	D3DXQUATERNION quat;
	float PEDistance;

	MODEL player = CPlayer::GetPlayer( );

	PEDistance = sqrt( (m_enemy.pos.x - player.pos.x) * (m_enemy.pos.x - player.pos.x) + (m_enemy.pos.z - player.pos.z) * (m_enemy.pos.z - player.pos.z) );

	if(PEDistance < 50 && m_moveFlag == false) {
		m_moveFlag = true;
	}
	else if(PEDistance >= 200 && m_moveFlag == true) {
		m_moveFlag = false;
	}

	if(m_moveFlag) {
		m_moveChange--;

		if(m_moveChange <= 0) {
			m_rnd = rand( ) % 9;
			m_moveChange = ENEMY_MOVE_CHANGE;
		}

	// モデルの移動処理
		if(m_rnd < 3) {
			if(m_rnd == 1) { // 左上移動
				m_enemy.move.x += sinf(D3DX_PI * (camera.rot.y - 0.75f) ) * ENEMY_MOVE_SPEED;
				m_enemy.move.z -= cosf(D3DX_PI * (camera.rot.y - 0.75f) ) * ENEMY_MOVE_SPEED;
				m_newRot = -camera.rot.y + 0.75f;
			}
			else if(m_rnd == 2) { // 左下移動
				m_enemy.move.x += sinf(D3DX_PI * (camera.rot.y - 0.25f) ) * ENEMY_MOVE_SPEED;
				m_enemy.move.z -= cosf(D3DX_PI * (camera.rot.y - 0.25f) ) * ENEMY_MOVE_SPEED;
				m_newRot = -camera.rot.y + 0.25f;
			}
			else { // 左移動
				m_enemy.move.x += sinf(D3DX_PI * (camera.rot.y - 0.5f) ) * ENEMY_MOVE_SPEED;
				m_enemy.move.z -= cosf(D3DX_PI * (camera.rot.y - 0.5f) ) * ENEMY_MOVE_SPEED;
				m_newRot = -camera.rot.y + 0.5f;
			}
		}
		// 上移動
		else if(m_rnd == 3) {
			m_enemy.move.x += sinf(D3DX_PI * (camera.rot.y + 1.0f) ) * ENEMY_MOVE_SPEED;
			m_enemy.move.z -= cosf(D3DX_PI * (camera.rot.y + 1.0f) ) * ENEMY_MOVE_SPEED;
			m_newRot = -camera.rot.y + 1.0f;
		}
		else if(m_rnd < 7) {
			if(m_rnd == 6) { // 右上移動
				m_enemy.move.x += sinf(D3DX_PI * (camera.rot.y + 0.75f) ) * ENEMY_MOVE_SPEED;
				m_enemy.move.z -= cosf(D3DX_PI * (camera.rot.y + 0.75f) ) * ENEMY_MOVE_SPEED;
				m_newRot = -camera.rot.y - 0.75f;
			}
			else if(m_rnd == 5) { // 右下移動
				m_enemy.move.x += sinf(D3DX_PI * (camera.rot.y + 0.25f) ) * ENEMY_MOVE_SPEED;
				m_enemy.move.z -= cosf(D3DX_PI * (camera.rot.y + 0.25f) ) * ENEMY_MOVE_SPEED;
				m_newRot = -camera.rot.y - 0.25f;
			}
			else { // 右移動
				m_enemy.move.x += sinf(D3DX_PI * (camera.rot.y + 0.5f) ) * ENEMY_MOVE_SPEED;
				m_enemy.move.z -= cosf(D3DX_PI * (camera.rot.y + 0.5f) ) * ENEMY_MOVE_SPEED;
				m_newRot = -camera.rot.y - 0.5f;
			}
		}
		// 下移動
		else if(m_rnd == 7) {
			m_enemy.move.x += sinf(D3DX_PI * (camera.rot.y + 0.0f) ) * ENEMY_MOVE_SPEED;
			m_enemy.move.z -= cosf(D3DX_PI * (camera.rot.y + 0.0f) ) * ENEMY_MOVE_SPEED;
			m_newRot = -camera.rot.y + 0.0f;
		}
		else if(m_rnd == 0) {
			m_enemy.move.x = 0;
			m_enemy.move.z = 0;
		}

		if(m_moveChange == ENEMY_MOVE_CHANGE && PEDistance > sqrt( ( (m_enemy.pos.x + m_enemy.move.x) - player.pos.x) * ( (m_enemy.pos.x + m_enemy.move.x) - player.pos.x) + ( (m_enemy.pos.z + m_enemy.move.z) - player.pos.z) * ( (m_enemy.pos.z + m_enemy.move.z) - player.pos.z) ) ) {
			m_rnd = (m_rnd + 4) % 8;
			m_enemy.move.x = 0.0f;
			m_enemy.move.z = 0.0f;
			m_newRot += 1.0f;
		}
	}

/*	if( (input -> GetKeyboardPress(DIK_J) || input -> GetKeyboardPress(DIK_SPACE) ) && m_enemy.jump == false) {
		m_enemy.move.y += ENEMY_JUMP_SPEED;
		m_enemy.jump = true;
		CSound::PlaySound(SOUND_LABEL_SE_JUMP);
	}*/


	// ジャンプ中であれば落下速度を加算
	if(m_enemy.jump) {
		m_enemy.move.y -= ENEMY_FALL_SPEED;
	}

	// 移動量反映
	m_enemy.pos.x += (m_enemy.move.x * 0.9f);
	m_enemy.pos.y += (m_enemy.move.y * 0.9f);
	m_enemy.pos.z += (m_enemy.move.z * 0.9f);

	// 移動量減衰
	m_enemy.move.x *= ENEMY_MOVE_REDUCE;
	m_enemy.move.y *= ENEMY_FALL_REDUCE;
	m_enemy.move.z *= ENEMY_MOVE_REDUCE;

	// 世界の果て判定 しかっけいっていいよね
	if(m_enemy.pos.x < MESHFIELD_FIELD_X + 1.0f) {
		m_enemy.pos.x = MESHFIELD_FIELD_X + 1.0f;
	}
	else if(m_enemy.pos.x > MESHFIELD_FIELD_X + MESHFIELD_FIELD_WIDTH - 1.0f) {
		m_enemy.pos.x = MESHFIELD_FIELD_X + MESHFIELD_FIELD_WIDTH - 1.0f;
	}

	if(m_enemy.pos.z > MESHFIELD_FIELD_Z - 1.0f) {
		m_enemy.pos.z = MESHFIELD_FIELD_Z - 1.0f;
	}
	else if(m_enemy.pos.z < MESHFIELD_FIELD_Z - MESHFIELD_FIELD_HEIGHT + 1.0f) {
		m_enemy.pos.z = MESHFIELD_FIELD_Z - MESHFIELD_FIELD_HEIGHT + 1.0f;
	}

	// フィールド高さ取得
	field_height = CMeshfield::GetFieldHeight(m_enemy.pos);

	// 高さ処理
	if(m_enemy.jump == false) {
		m_enemy.pos.y = field_height;
	}

	// フィールドめり込み処理
	if(m_enemy.pos.y < field_height ){
		m_enemy.pos.y = field_height;
		m_enemy.move.y = 0.0f;
		m_enemy.jump = false;
	}

	// m_newRot調整
	if(m_newRot > 1.0f) {
		m_newRot -= 2.0f;
	}
	else if(m_newRot < -1.0f) {
		m_newRot += 2.0f;
	}

	// モデルの方向補正
	if(abs(m_newRot - m_enemy.rot.y) <= 1.0f) {
		m_enemy.rot.y += (m_newRot - m_enemy.rot.y) * 0.1f;
	}
	if(abs(m_newRot - m_enemy.rot.y) > 1.0f) {
		m_enemy.rot.y += (fmod(m_newRot + 2.0f, 2.0f) - fmod(m_enemy.rot.y + 2.0f, 2.0f) ) * 0.1f;
	}

/*	D3DXQuaternionRotationAxis(&quat, &axis, 0.0f);
	D3DXQuaternionMultiply(&m_enemy.rot, &m_enemy.rot, &quat);*/

	// 回転角の例外処理
	if(m_enemy.rot.y > 1.0f) {
		m_enemy.rot.y -= 2.0f;
	}
	else if(m_enemy.rot.y < -1.0f) {
		m_enemy.rot.y += 2.0f;
	}

	if(m_respawn) {
		m_respawn--;
		if(m_respawn == 0) {
			CSound::PlaySound(SOUND_LABEL_SE_RESPAWN);
		}
	}

	// 接触判定
	if( sqrt( (m_enemy.pos.x - player.pos.x) * (m_enemy.pos.x - player.pos.x) + (m_enemy.pos.z - player.pos.z) * (m_enemy.pos.z - player.pos.z) ) < 2.0f && m_respawn == 0) {
		CSound::PlaySound(SOUND_LABEL_SE_HIT);
		CScore::AddScore(10);
		m_respawn += ENEMY_RESPAWN_TIME;
	}
}


/*******************************************************************************
* 関数名：Draw
* 引数：なし
* 戻り値：なし
* 説明：描画処理
*******************************************************************************/

void CEnemy::Draw(void) {
	if(m_respawn == 0) {
		CRenderer *renderer;
		renderer = CManager::GetRenderer( );
		LPDIRECT3DDEVICE9 device = renderer -> GetDevice( ); // デバイス取得
		D3DXMATRIX mtxScl, mtxRot, mtxTrans; // 計算用
		D3DXMATERIAL *pMat;
		D3DMATERIAL9 matDef; // マテリアル情報保存用

		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&m_mtxWorld);
		// ワールドマトリックスの作成
		// スケールを反映
		D3DXMatrixScaling(&mtxScl, ENEMY_SCALE_X, ENEMY_SCALE_Y, ENEMY_SCALE_Z);
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxScl);

		// 回転を反映
	//	D3DXMatrixRotationQuaternion(&mtxRot, &m_enemy.rot); // ※※※ y, x, z の順番に注意！！！ ※※※
		D3DXMatrixRotationYawPitchRoll(&mtxRot, m_enemy.rot.y * D3DX_PI, m_enemy.rot.x * D3DX_PI, m_enemy.rot.z * D3DX_PI);
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

		// 移動を反映
		D3DXMatrixTranslation(&mtxTrans, m_enemy.pos.x, m_enemy.pos.y, m_enemy.pos.z);
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

		// ワールドマトリックスの設定
		device -> SetTransform(D3DTS_WORLD, &m_mtxWorld);

		// 現在マテリアルを取得
		device -> GetMaterial(&matDef);

		// マテリアル設定
		pMat = (D3DXMATERIAL*)m_pBuffMat -> GetBufferPointer( );
		for(int nCntMat = 0; nCntMat < (int)m_numMat; nCntMat++) {
			device -> SetMaterial(&pMat[nCntMat].MatD3D);
			device -> SetTexture(0, m_pTexture);
			m_pMesh -> DrawSubset(nCntMat);
		}

		// マテリアルの設定を戻す
		device -> SetMaterial(&matDef);
	}
}


/*******************************************************************************
* 関数名：Create
* 引数：sceneX : アドレス
* 戻り値：なし
* 説明：オブジェクトの生成
*******************************************************************************/

CEnemy *CEnemy::Create(void) {
	CEnemy *sceneX;
	sceneX = new CEnemy;
	sceneX -> Init( );
	return sceneX;
}


/*******************************************************************************
* 関数名：GetEnemy
* 引数：なし
* 戻り値：m_enemy
* 説明：モデルの情報を返す
*******************************************************************************/

MODEL CEnemy::GetEnemy(void) {
	return m_enemy;
}
