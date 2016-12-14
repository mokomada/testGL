//=============================================================================
//
//	タイトル	プレイヤー
//	ファイル名	player.cpp
//	作成者		AT13A284_10 石橋拓巳
//	作成日		2016/12/5
//
//=============================================================================
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

//=============================================================================
//	関数名	:Init
//	引数	:VECTOR3 pos(初期位置)
//	戻り値	:無し
//	説明	:初期化処理を行うと共に、初期位置を設定する。
//=============================================================================
void CPlayer::Init(bool ifMinePlayer, VECTOR3 pos)
{
	CRendererGL	*renderer	= CManager::GetRendererGL();
	
	// 自プレイヤーかどうかセット
	m_ifMinePlayer = ifMinePlayer;

	// 各種初期化
	SetPos(VECTOR3(pos.x, pos.y, pos.z));
	SetRot(VECTOR3(0.0f, 0.0f, 0.0f));
	m_Move			= VECTOR3(0.0f, 0.0f, 0.0f);
	m_RotMove		= VECTOR3(0.0f, 0.0f, 0.0f);
	m_MoveDirection = VECTOR3(0.0f, 0.0f, 0.0f);
	m_bJump			= false;
	m_Scale			= VECTOR3(1.0f, 1.0f, 1.0f);

	m_Gauge = 100.0f;	//ゲージの初期化
	m_FlgLowSpeed = false;
	m_Radius = 30.0f;

	Model = CSceneModel::Create("./data/MODEL/car.obj");
	CShadow::Create( m_Pos , 100.0f , 100.0f , this );

	BOX_DATA Box = { 50.0f, 50.0f, 50.0f };
	SetBox(Box);
}

//=============================================================================
//	関数名	:Uninit
//	引数	:無し
//	戻り値	:無し
//	説明	:終了処理を行う。
//=============================================================================
void CPlayer::Uninit(bool isLast)
{
	Model->Uninit();
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

	if (CInput::GetKeyboardTrigger(DIK_SPACE)) m_FlgLowSpeed = true;
	else if (CInput::GetKeyboardRelease(DIK_SPACE)) m_FlgLowSpeed = false;

	// 自プレイヤーの場合にのみ処理
	if (m_ifMinePlayer)
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
			CBullet::Create( m_Pos , m_Rot , 10.0f );
		}
	}

	for each (CSceneGL* list in CSceneGL::GetList(PRIORITY_WALL))
	{
		if (CollisionDetectionBox(m_Pos, &GetBox(), list->GetPos(), &list->GetBox()))
		{
			CDebugProcGL::DebugProc("HitBox\n");
		}
	}

	if (!m_ifMinePlayer)
	{
		for each (CSceneGL* list in CSceneGL::GetList(PRIORITY_BULLET))
		{
			if (CollisionDetectionSphere(m_Pos, GetRadius(), list->GetPos(), list->GetRadius()))
			{
				Release();
				return;
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

	if (m_ifMinePlayer)
	{
		CollisionDetection();
	}

	// プレイヤーの高さを設定
	if (m_Pos.y < 20.0f)
	{
		m_Pos.y = 20.0f;
		m_bJump = false;
	}
	else
	{
		// ジャンプ量の減衰
		m_Move.y -= PLAYER_GRAVITY;
	}

	// 自プレイヤーの場合、位置を送信
	if (m_ifMinePlayer)
	{
		char str[1024] = { NULL };

		sprintf(str, "1, %f, %f, %f", m_Pos.x, m_Pos.y, m_Pos.z);

		CNetwork::SendData(str);
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

	glMatrixMode(GL_MODELVIEW);		// モデルビューマトリックスの設定
	glPopMatrix();					// 保存マトリックスの取り出し

	CDebugProcGL::DebugProc("chara:(%.2f:%.2f:%.2f)\n", m_Pos.x, m_Pos.y, m_Pos.z);
}

//=============================================================================
//	関数名	:Create
//	引数	:VECTOR3 pos(初期位置)
//	戻り値	:無し
//	説明	:インスタンス生成を行うと共に、初期位置を設定する。
//=============================================================================
CPlayer *CPlayer::Create(bool ifMinePlayer, VECTOR3 pos)
{
	CPlayer *player;

	player = new CPlayer;

	player->Init(ifMinePlayer, pos);

	return player;
}

//=============================================================================
//	関数名	:Update
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
			if (player->m_ifMinePlayer == false)
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
//	関数名	:Update
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