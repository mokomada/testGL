//=============================================================================
//
//	タイトル	プレイヤー
//	ファイル名	player.cpp
//	作成者		AT13A284_10 石橋拓巳
//	作成日		2016/12/5
//
//=============================================================================

#define _CRT_SECURE_NO_WARNINGS // fscanf/fopenの警告対策

//=============================================================================
//	インクルード
//=============================================================================
#include <stdio.h>
#include "main.h"
#include "manager.h"
#include "rendererGL.h"
#include "game.h"
#include "sceneGL.h"
#include "sceneModel.h"
#include "player.h"
#include "cameraGL.h"
#include "network.h"
#include "bullet.h"
#include "debugProcGL.h"
#include "shadow.h"
#include "life.h"
#include "collision.h"
#include "particle.h"

//=============================================================================
//	関数名	:CScene3D()
//	引数	:無し
//	戻り値	:無し
//	説明	:コンストラクタ。
//=============================================================================
CPlayer::CPlayer(bool ifListAdd, int priority, OBJTYPE objType) : CScene3DGL(ifListAdd, priority, objType)
{

}

//=============================================================================
//	関数名	:~CScene3D()
//	引数	:無し
//	戻り値	:無し
//	説明	:デストラクタ。
//=============================================================================
CPlayer::~CPlayer()
{

}

VECTOR3 g_PosOld = VECTOR3(0.0f,0.0f,0.0f);// 実装され次第消去
//=============================================================================
//	関数名	:Init
//	引数	:VECTOR3 pos(初期位置)
//	戻り値	:無し
//	説明	:初期化処理を行うと共に、初期位置を設定する。
//=============================================================================
void CPlayer::Init(uint whatPlayer, VECTOR3 pos, VECTOR3 rot)
{
	CRendererGL	*renderer	= CManager::GetRendererGL();

	// 自プレイヤーかどうかセット
	m_PlayerNumber = whatPlayer;

	// 各種初期化
	SetPos(pos);
	SetRot(rot);
	m_Move			= VECTOR3(0.0f, 0.0f, 0.0f);
	m_RotMove		= VECTOR3(0.0f, 0.0f, 0.0f);
	m_MoveDirection = rot;
	m_bJump			= false;
	m_Scale			= VECTOR3(1.0f, 1.0f, 1.0f);

	m_Gauge = 100.0f;	//ゲージの初期化
	m_FlgLowSpeed = false;
	m_Radius = 30.0f;
	m_HitEffectTime = 0; // 被弾エフェクト時間の初期化
	m_DrawOnOffFlag = true; // 描画処理のONOFFフラグをONに
	m_DeadFlag = false; // 死亡フラグをOFFに

	switch(m_PlayerNumber)
	{
	case 0:
		Model = CSceneModel::Create("./data/MODEL/car1.obj");
		break;
	case 1:
		Model = CSceneModel::Create("./data/MODEL/car2.obj");
		break;
	case 2:
		Model = CSceneModel::Create("./data/MODEL/car3.obj");
		break;
	case 3:
		Model = CSceneModel::Create("./data/MODEL/car4.obj");
		break;
	default:
		Model = CSceneModel::Create("./data/MODEL/car1.obj");
		break;
	}
	CShadow::Create( m_Pos , 100.0f , 100.0f , this );

	Scene3D[0] = CScene3DGL::Create(VECTOR3(30.0f, 5.0f, 0.0f), VECTOR2(30.0f, 30.0f), "./data/TEXTURE/hane1.png");
	Scene3D[0]->SetRot(VECTOR3(-PI * 0.45f, 0.0f, 0.0f));
	Scene3D[0]->UnlinkList();
	Scene3D[1] = CScene3DGL::Create(VECTOR3(-30.0f, 5.0f, 0.0f), VECTOR2(30.0f, 30.0f), "./data/TEXTURE/hane2.png");
	Scene3D[1]->SetRot(VECTOR3(-PI * 0.45f, 0.0f, 0.0f));
	Scene3D[1]->UnlinkList();

	BOX_DATA Box = { 50.0f, 50.0f, 50.0f };
	SetBox(Box);

	//これで風船を描画します
	//Uninit,Update,Drawにて各関数を呼んでます。
	//ダメージを受けたらCLife内のHitDamage関数を使ってください
	m_pLife = CLife::Create( m_Pos , this , m_PlayerNumber );

	// パーティクルオブジェクト生成
	m_pParticle = CParticle::Create(VECTOR3(m_Pos.x,-100.0f,0.0f), VECTOR2(100.0f,100.0f), PARTICLE_DEADSMOKE, this);

	FILE* fp;

	fp = fopen("./data/ranking.txt", "w");
	fclose(fp);
}

//=============================================================================
//	関数名	:Uninit
//	引数	:無し
//	戻り値	:無し
//	説明	:終了処理を行う。
//=============================================================================
void CPlayer::Uninit(bool isLast)
{
	m_pLife = NULL;

	if(Model != NULL) {
		Model->Uninit();
		Model = NULL;
	}

	if(m_pParticle != NULL) {
		m_pParticle->Uninit();
		m_pParticle = NULL;
	}
}

//=============================================================================
//	関数名	:Update
//	引数	:無し
//	戻り値	:無し
//	説明	:更新処理を行う。
//=============================================================================
void CPlayer::Update(void)
{
	CCameraGL	*camera = CManager::GetCamera();	// カメラ
	int life = m_pLife -> GetLife( );

	if (CInput::GetKeyboardTrigger(DIK_SPACE)) m_FlgLowSpeed = true;
	else if (CInput::GetKeyboardRelease(DIK_SPACE)) m_FlgLowSpeed = false;

	// ライフが0以下ならば操作を受け付けない
	if(life > 0) {
		// 自プレイヤーの場合にのみ処理
		if (m_PlayerNumber == CManager::GetWhatPlayer())
		{
			if (CInput::GetKeyboardPress(DIK_W))				// 移動方向に移動
			{
				if (CInput::GetKeyboardPress(DIK_A))				// 左周り
				{
					//回転量の加算
					if (m_FlgLowSpeed == true) m_MoveDirection.y += LOWMOVE_ROT;
					else if (m_FlgLowSpeed == false) m_MoveDirection.y += MOVE_ROT;
				}
				if (CInput::GetKeyboardPress(DIK_D))				// 右回り
				{
					//回転量の加算
					if (m_FlgLowSpeed == true) m_MoveDirection.y -= LOWMOVE_ROT;
					else if (m_FlgLowSpeed == false) m_MoveDirection.y -= MOVE_ROT;
				}

				// 移動量を設定
				if (m_FlgLowSpeed == true)
				{
					m_Move.x += sinf(m_Rot.y) * LOWFMOVE_SPEED;
					m_Move.z += cosf(m_Rot.y) * LOWFMOVE_SPEED;
				}
				if (m_FlgLowSpeed == false)
				{
					m_Move.x += sinf(m_Rot.y) * FMOVE_SPEED;
					m_Move.z += cosf(m_Rot.y) * FMOVE_SPEED;
				}
			}
			if (CInput::GetKeyboardPress(DIK_S))		// 移動方向に移動の反対に移動
			{
				if (CInput::GetKeyboardPress(DIK_A))				// 左周り
				{
					//回転量の加算
					if (m_FlgLowSpeed == true) m_MoveDirection.y -= LOWMOVE_ROT;
					else if (m_FlgLowSpeed == false) m_MoveDirection.y -= MOVE_ROT;
				}
				if (CInput::GetKeyboardPress(DIK_D))				// 右回り
				{
					//回転量の加算
					if (m_FlgLowSpeed == true) m_MoveDirection.y += LOWMOVE_ROT;
					else if (m_FlgLowSpeed == false) m_MoveDirection.y += MOVE_ROT;
				}

				// 移動量を設定
				if (m_FlgLowSpeed == true)
				{
					m_Move.x += sinf(m_Rot.y + PI) * LOWBMOVE_SPEED;
					m_Move.z += cosf(m_Rot.y + PI) * LOWBMOVE_SPEED;
				}
				if (m_FlgLowSpeed == false)
				{
					m_Move.x += sinf(m_Rot.y + PI) * BMOVE_SPEED;
					m_Move.z += cosf(m_Rot.y + PI) * BMOVE_SPEED;
				}
			}
			if (m_bJump == true)
			{
				if (CInput::GetKeyboardPress(DIK_W))				// 移動方向に移動
				{
					if (CInput::GetKeyboardPress(DIK_A))				// 左周り
					{
						//回転量の加算
						if (m_FlgLowSpeed == true) m_MoveDirection.y += LOWMOVE_ROT;
						else if (m_FlgLowSpeed == false) m_MoveDirection.y += MOVE_ROT;
					}
					if (CInput::GetKeyboardPress(DIK_D))				// 右回り
					{
						//回転量の加算
						if (m_FlgLowSpeed == true) m_MoveDirection.y -= LOWMOVE_ROT;
						else if (m_FlgLowSpeed == false) m_MoveDirection.y -= MOVE_ROT;
					}
				}
				else if (CInput::GetKeyboardPress(DIK_S))		// 移動方向に移動の反対に移動
				{
					if (CInput::GetKeyboardPress(DIK_A))				// 左周り
					{
						//回転量の加算
						if (m_FlgLowSpeed == true) m_MoveDirection.y -= LOWMOVE_ROT;
						else if (m_FlgLowSpeed == false) m_MoveDirection.y -= MOVE_ROT;
					}
					if (CInput::GetKeyboardPress(DIK_D))				// 右回り
					{
						//回転量の加算
						if (m_FlgLowSpeed == true) m_MoveDirection.y += LOWMOVE_ROT;
						else if (m_FlgLowSpeed == false) m_MoveDirection.y += MOVE_ROT;
					}
				}
				else
				{
					if (CInput::GetKeyboardPress(DIK_A))				// 左周り
					{
						//回転量の加算
						if (m_FlgLowSpeed == true) m_MoveDirection.y += LOWMOVE_ROT;
						else if (m_FlgLowSpeed == false) m_MoveDirection.y += MOVE_ROT;
					}
					if (CInput::GetKeyboardPress(DIK_D))				// 右回り
					{
						//回転量の加算
						if (m_FlgLowSpeed == true) m_MoveDirection.y -= LOWMOVE_ROT;
						else if (m_FlgLowSpeed == false) m_MoveDirection.y -= MOVE_ROT;
					}
				}
			
			}

			static float rot = 0.0f;
			rot += 0.08f;
			Scene3D[0]->SetRot(VECTOR3(-PI * 0.55f, sinf(rot) * 0.2f, 0.0f));
			Scene3D[1]->SetRot(VECTOR3(-PI * 0.55f, sinf(rot) * -0.2f, 0.0f));

			/*Scene3D[0]->SetPos(VECTOR3(m_Pos.x + cosf(m_Rot.y) * m_Radius, m_Pos.y, m_Pos.z + sinf(m_Rot.y) * m_Radius));
			Scene3D[1]->SetPos(VECTOR3(m_Pos.x + cosf(m_Rot.y + PI) * m_Radius, m_Pos.y, m_Pos.z + sinf(m_Rot.y + PI) * m_Radius));*/

			camera->m_CameraState.posV.x = m_Pos.x + sinf(camera->m_CameraState.Rot.y + m_Rot.y) *camera->m_CameraState.fDistance;
			camera->m_CameraState.posV.z = m_Pos.z + cosf(camera->m_CameraState.Rot.y + m_Rot.y) *camera->m_CameraState.fDistance;

			camera->m_CameraState.posR.x = m_Pos.x + sinf(m_Rot.y) * BMOVE_SPEED;
			camera->m_CameraState.posR.z = m_Pos.z + cosf(m_Rot.y) * BMOVE_SPEED;

			// ジャンプ
			if (CInput::GetKeyboardTrigger(DIK_J) && !m_bJump)
			{
				m_Move.y += PLAYER_JUMP;

				m_bJump = true;
			}
			// 弾発射
			if (CInput::GetKeyboardTrigger(DIK_L))
			{
				if ( m_Gauge > 100 )
				{
					int bulletNum = 0;

					// 取得したデータをセット
					for(int j = 0 ; j < BULLET_NUM_MAX ; j++)
					{
						if(CNetwork::m_BulletInstance[m_PlayerNumber][j].Use == false)
						{
							CNetwork::m_BulletInstance[m_PlayerNumber][j].Instance
								= CBullet::Create(m_PlayerNumber, j, m_Pos, m_Rot, 10.0f, m_PlayerNumber);
							CNetwork::m_BulletInstance[m_PlayerNumber][j].Use = true;
							bulletNum = j;
							break;
						}
					}

					char str[1024] ={ NULL };
					sprintf(str, "TAG:2, %d, %d, POS(%f, %f, %f), ROT(%f, %f, %f), %f",
						m_PlayerNumber, bulletNum, m_Pos.x, m_Pos.y, m_Pos.z, m_Rot.x, m_Rot.y, m_Rot.z, 10.0f);
					CNetwork::SendData(str);

					//CBullet::Create(m_Pos, m_Rot, 10.0f, m_PlayerNumber);
					AddGauge(-100);
				}
			}
		}
		// 回転量補正
		if (m_Rot.y - m_MoveDirection.y > PI)				// 回転量がプラス方向に逆向きの場合
		{
			// 回転量を逆方向に
			m_Rot.y -= (PI * 2.0f);
		}
		else if (m_Rot.y - m_MoveDirection.y < -PI)			// 回転量がマイナス方向に逆向きの場合
		{
			// 回転量を逆方向に
			m_Rot.y += (PI * 2.0f);
		}

		// 回転量を設定
		m_Rot.y += (m_MoveDirection.y - m_Rot.y) * 0.1f;
	}

	//************* HP0時演出テストここから *****************

	if(life <= 0 && !m_DeadFlag) {
		m_Move.y += PLAYER_JUMP * 3;
		m_RotMove.x = (rand() % 40) * 0.01f;
		m_RotMove.y = (rand() % 40) * 0.01f;
		m_RotMove.z = (rand() % 40) * 0.01f;
		m_bJump = true;
		m_DeadFlag = true;


		FILE* fp;

		fp = fopen("./data/ranking.txt", "a");

		fprintf(fp, "%d\n", m_PlayerNumber);

		fclose(fp);
	}

	m_Rot.x += m_RotMove.x;
	m_Rot.y += m_RotMove.y;
	m_Rot.z += m_RotMove.z;


  ////	爆風エフェクト生成(上昇中のみ毎フレーム爆発エフェクトを呼ぶ)
  ///////////////////////////////////////////////////////////
  //	死んでる　＋　空中　＋　上に移動中
  if(m_DeadFlag && m_bJump && g_PosOld.y < m_Pos.y)
  {
    // 前回の位置に今回の位置を入れる
    g_PosOld.y = m_Pos.y;

    // 火柱方向
    float test = (float)(rand()%50 - 100.0f);

    // エフェクト生成
    CEffect2D::Create(VECTOR3(m_Pos.x + test , m_Pos.y , m_Pos.z) , VECTOR2(500.0f -  m_Pos.y , 500.0f -  m_Pos.y) , ETYPE_EXPLODE01);
  }

  // 以下(else if)は同期設定次第で後で消す。
  else if(m_DeadFlag && !m_bJump)
  {
    // 前回の位置を0.0fに
    g_PosOld.y = 0.0f;
  }

	//************* HP0時演出テストここまで *****************


	// 移動量反映
	m_Pos.x += m_Move.x;
	m_Pos.z += m_Move.z;

	//移動量の減衰
	if (m_bJump == true)
	{
		m_Move.x += (-m_Move.x * MODEL_SPEED_DOWNJ);
		m_Move.z += (-m_Move.z * MODEL_SPEED_DOWNJ);
		m_Move.y += (-m_Move.y * MODEL_SPEED_DOWN);
	}
	else
	{
		m_Move += (-m_Move * MODEL_SPEED_DOWN);
	}

	// ジャンプ量の反映
	m_Pos.y += m_Move.y;

	for each (CSceneGL* list in CSceneGL::GetList(PRIORITY_WALL))
	{
		if (CCollision::GetInstance()->SphereToAabb(m_Pos, m_Radius, list->GetPos(), &list->GetBox()))
		{
			CDebugProcGL::DebugProc("HitBox\n");
		}
	}

	for each (CSceneGL* list in CSceneGL::GetList(PRIORITY_PLAYER))
	{
		if (list == this) continue;
		if (CCollision::GetInstance()->PlayerToPlayer(m_Pos, m_Radius, list->GetPos(), list->GetRadius()))
		{
			CDebugProcGL::DebugProc("HitSphere\n");
		}
	}

	//CCollision::GetInstance()->SphereToBoard(m_Pos, m_Radius, VECTOR3(-200.0f, 100.0f, 500.0f), VECTOR3(200.0f, 100.0f, 500.0f), VECTOR3(-200.0f, 0.0f, 0.0f), VECTOR3(200.0f, 0.0f, 0.0f));

	//CCollision::GetInstance()->PlayerToPlayer(m_Pos, m_Radius, VECTOR3(0.0f, 0.0f, 500.0f), 50.0f);

	if (m_PlayerNumber != CManager::GetWhatPlayer())
	{
		for each (CSceneGL* list in CSceneGL::GetList(PRIORITY_BULLET))
		{
			if (CCollision::GetInstance()->SphereToSphere(m_Pos, GetRadius(), list->GetPos(), list->GetRadius()))
			{
				if (m_HitEffectTime <= 0) {
					m_pLife->HitDamage();
					if (life > 1) m_HitEffectTime = 120; // ライフが1の時に被弾する＝吹っ飛びエフェクトに移行するので点滅処理はなし

														 // 球ヒットエフェクト生成
					CEffect2D::Create(m_Pos, VECTOR2(100.0f, 100.0f), ETYPE_EXPLODE01);
					CBullet *bullet = (CBullet*)list;
					bullet->SetLife(-100);
				}
				//				Release();
				//				return;
			}
		}
	}

	// プレイヤーの高さを設定

	if (m_Pos.y < 25.0f)
	{
		m_Pos.y = 25.0f;
		m_Move.y = 0;
		m_RotMove.x = 0;
		m_RotMove.y = 0;
		m_RotMove.z = 0;
		m_bJump = false;
	}
	else
	{
		// ジャンプ量の減衰
		m_Move.y -= PLAYER_GRAVITY;
	}


	//*************************** 被弾エフェクト処理開始 ***************************

	// テスト用 8～0キーで被弾エフェクト それぞれ長さが違う
	// ※8の倍数-4～8の倍数-2に設定すると最初の点滅が3～1フレーム短くなるので注意。基本は4フレーム毎にONOFFを切り替える点滅
/*	デバッグ用機能は出荷よー
	if(CInput::GetKeyboardTrigger(DIK_8) && m_HitEffectTime <= 0) {
		m_HitEffectTime = 30;
	}
	else if(CInput::GetKeyboardTrigger(DIK_9) && m_HitEffectTime <= 0) {
		m_HitEffectTime = 59;
	}
	else if(CInput::GetKeyboardTrigger(DIK_0) && m_HitEffectTime <= 0) {
		m_HitEffectTime = 120;
	}*/

	// 被弾エフェクト処理を実行
	if(m_HitEffectTime > 0) {
		HitEffect( );
	}

	//*************************** 被弾エフェクト処理終了 ***************************


	// 自プレイヤーの場合、位置を送信
	if (m_PlayerNumber == CManager::GetWhatPlayer())
	{
		static char str[1024] = { NULL };
		if(CGame::GetFrame() % 10 == 0)
		{
			memset(str, NULL, sizeof(str));

			sprintf(str, "TAG:1, %d, POS(%f, %f, %f), ROT(%f, %f, %f), VEC(%f, %f, %f)",
				CManager::GetWhatPlayer(), m_Pos.x, m_Pos.y, m_Pos.z, m_Rot.x, m_Rot.y, m_Rot.z, m_Move.x, m_Move.y, m_Move.z);

			CNetwork::SendData(str);
		}
		//CDebugProcGL::DebugProc("%s\n", str);
	}

	//風船更新
	m_pLife->Update();

	// 煙パーティクル発生
	if(m_DeadFlag)
	{
		m_pParticle->Update();
	}

	Model->Update();
}

//=============================================================================
//	関数名	:Draw
//	引数	:無し
//	戻り値	:無し
//	説明	:描画処理を行う。
//=============================================================================
void CPlayer::Draw(void)
{
	if(m_DrawOnOffFlag) {
		glMatrixMode(GL_MODELVIEW);		// モデルビューマトリクスの設定
		glPushMatrix();					// マトリクスの退避

		// ワールドマトリクスの設定
		glTranslatef(m_Pos.x, m_Pos.y, m_Pos.z);
		glRotatef((GLfloat)(m_Rot.z * 180.0 / PI), 0.0f, 0.0f, 1.0f);	// 回転マトリックスの設定、角度は度数法で
		glRotatef((GLfloat)(m_Rot.y * 180.0 / PI), 0.0f, 1.0f, 0.0f);	// 回転マトリックスの設定、角度は度数法で
		glRotatef((GLfloat)(m_Rot.x * 180.0 / PI), 1.0f, 0.0f, 0.0f);	// 回転マトリックスの設定、角度は度数法で
		glScalef(m_Scale.x, m_Scale.y, m_Scale.z);

		// モデル描画
		Model->Draw();

		glDisable(GL_CULL_FACE);

		glEnable(GL_DEPTH_TEST);
		glAlphaFunc(GL_GEQUAL, 0.1f);
		glEnable(GL_ALPHA_TEST);
//		glDepthMask(GL_FALSE);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		glEnable(GL_BLEND);
		Scene3D[0]->Draw();
		Scene3D[1]->Draw();
		// 各種設定引き戻し
		glEnable(GL_LIGHTING);
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_ALPHA_TEST);
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_BLEND);
//		glDepthMask(TRUE);
		glDepthMask(GL_TRUE);

		glEnable(GL_CULL_FACE);

		glMatrixMode(GL_MODELVIEW);		// モデルビューマトリックスの設定
		glPopMatrix();					// 保存マトリックスの取り出し
	}

	//風船描画
	m_pLife->Draw();

	//CDebugProcGL::DebugProc("chara:(%.2f:%.2f:%.2f)\n", m_Pos.x, m_Pos.y, m_Pos.z);
}

//=============================================================================
//	関数名	:Create
//	引数	:VECTOR3 pos(初期位置)
//	戻り値	:無し
//	説明	:インスタンス生成を行うと共に、初期位置を設定する。
//=============================================================================
CPlayer *CPlayer::Create(uint whatPlayer, VECTOR3 pos, VECTOR3 rot)
{
	CPlayer *player;

	player = new CPlayer;

	player->Init(whatPlayer, pos, rot);

	return player;
}

//=============================================================================
//	関数名	:
//	引数	:無し
//	戻り値	:無し
//	説明	:更新処理を行う。
//=============================================================================
void CPlayer::CollisionDetection(void)
{
	int nCnt = 0;

	for each (CSceneGL* list in CSceneGL::GetList(PRIORITY_PLAYER))
	{
		if (list != NULL)
		{
			CPlayer* player = (CPlayer*)list;
			if (player->m_PlayerNumber == CManager::GetWhatPlayer())
			{
				VECTOR3 sub = GetPos() - player->GetPos();
				float distance = VECTOR3::dot(sub, sub);
				float radius = m_Radius + player->m_Radius;

				if (distance <= radius * radius)
				{
					CDebugProcGL::DebugProc("Hit%d\n", nCnt);

					VECTOR3 Pos0 = GetPos(), Pos1 = player->GetPos();
					float Radius = m_Radius + player->m_Radius;
					float Lenght = (Pos1 - Pos0).magnitude();
					VECTOR3 Vec = Pos0 - Pos1;
					Vec.normalize();
					Radius -= Lenght;
					Pos0 += VECTOR3(Vec.x * Radius, Vec.y * Radius, Vec.z * Radius);
					SetPos(Pos0);
				}
			}
		}
		nCnt++;
	}

	/*CGame *game = (CGame*)CManager::GetMode();
	vector<CPlayer*> sceneModel = game->GetPlayer();
	for (int nCnt = 0; nCnt < game->GetPlayer().size(); nCnt++)
	{
		if (sceneModel[nCnt] != NULL)
		{
			if (sceneModel[nCnt]->m_ifMinePlayer == false)
			{
				VECTOR3 sub = GetPos() - sceneModel[nCnt]->GetPos();
				float distance = VECTOR3::dot(sub, sub);
				float radius = m_Radius + sceneModel[nCnt]->m_Radius;

				if (distance <= radius * radius)
				{
					CDebugProcGL::DebugProc("Hit%d\n", nCnt);

					VECTOR3 Pos0 = GetPos(), Pos1 = sceneModel[nCnt]->GetPos();
					float Radius = m_Radius + sceneModel[nCnt]->m_Radius;
					float Lenght = (Pos1 - Pos0).magnitude();
					VECTOR3 Vec = Pos0 - Pos1;
					Vec.normalize();
					Radius -= Lenght;
					Pos0 += VECTOR3(Vec.x * Radius, Vec.y * Radius, Vec.z * Radius);
					SetPos(Pos0);
				}
			}
		}
	}*/
}

//=============================================================================
//	関数名	:
//	引数	:無し
//	戻り値	:無し
//	説明	:更新処理を行う。
//=============================================================================
bool CPlayer::CollisionDetectionSphere(VECTOR3 Pos0, float Radius0, VECTOR3 Pos1, float Radius1)
{
	VECTOR3 sub = Pos1 - Pos0;
	float distance = VECTOR3::dot(sub, sub);
	float radius = Radius0 + Radius1;

	if (distance <= radius * radius)
	{
		return true;
	}
	return false;
}


//=============================================================================
//	関数名	:CollisionDetectionBox
//	引数	:無し
//	戻り値	:無し
//	説明	:ボックスの当たり判定
//=============================================================================
bool CPlayer::CollisionDetectionBox(VECTOR3 Pos1, BOX_DATA* Box1, VECTOR3 Pos2, BOX_DATA* Box2)
{
	bool HitBox = false;

	float WidthHalf1 = Box1->width * 0.5f;
	float WidthHalf2 = Box2->width * 0.5f;

	if ((Pos1.x + WidthHalf1 >= Pos2.x - WidthHalf2) && (Pos1.x - WidthHalf1 <= Pos2.x + WidthHalf2))
	{
		float HightHalf1 = Box1->height * 0.5f;
		float HightHalf2 = Box2->height * 0.5f;
		if ((Pos1.y + HightHalf1 >= Pos2.y - HightHalf2) && (Pos1.y - HightHalf1 <= Pos2.y + HightHalf2))
		{
			float DepthHalf1 = Box1->depth * 0.5f;
			float DepthHalf2 = Box2->depth * 0.5f;
			if ((Pos1.z + DepthHalf1 >= Pos2.z - DepthHalf2) && (Pos1.z - DepthHalf1 <= Pos2.z + DepthHalf2))
			{
				HitBox = true;
			}
		}
	}

	return HitBox;
}


//=============================================================================
//	関数名	:HitEffect
//	引数	:無し
//	戻り値	:無し
//	説明	:被弾エフェクト
//=============================================================================

void CPlayer::HitEffect(void) {
	if(m_HitEffectTime % (BLINK_TIME * 2) < BLINK_TIME ) {
		m_DrawOnOffFlag = true;
	}
	else {
		m_DrawOnOffFlag = false;
	}

	// エフェクト時間を減らす
	m_HitEffectTime--;
	// もしエフェクトの残り時間が0を下回った場合、時間を0にして描画フラグをONにする（起こり得ないはずだけど保険）
	if(m_HitEffectTime < 0) {
		m_HitEffectTime = 0;
		m_DrawOnOffFlag = true;
	}
}


//=============================================================================
//	関数名	:SetHitEffectTime
//	引数	:time エフェクト時間の長さ（フレーム単位）
//	戻り値	:無し
//	説明	:被弾エフェクト設定
//=============================================================================

void CPlayer::SetHitEffectTime(int time) {
	m_HitEffectTime = time;
}


//=============================================================================
//	関数名	:GetPlayerLife
//	引数	:time エフェクト時間の長さ（フレーム単位）
//	戻り値	:無し
//	説明	:被弾エフェクト設定
//=============================================================================

int CPlayer::GetPlayerLife(void) {
	return m_pLife -> GetLife( );
}