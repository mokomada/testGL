//=============================================================================
//
//	�^�C�g��	�v���C���[
//	�t�@�C����	player.cpp
//	�쐬��		AT13A284_10 �΋���
//	�쐬��		2016/12/5
//
//=============================================================================
//=============================================================================
//	�C���N���[�h
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

//=============================================================================
//	�֐���	:CScene3D()
//	����	:����
//	�߂�l	:����
//	����	:�R���X�g���N�^�B
//=============================================================================
CPlayer::CPlayer(bool ifListAdd, int priority, OBJTYPE objType) : CScene3DGL(ifListAdd, priority, objType)
{

}

//=============================================================================
//	�֐���	:~CScene3D()
//	����	:����
//	�߂�l	:����
//	����	:�f�X�g���N�^�B
//=============================================================================
CPlayer::~CPlayer()
{

}

//=============================================================================
//	�֐���	:Init
//	����	:VECTOR3 pos(�����ʒu)
//	�߂�l	:����
//	����	:�������������s���Ƌ��ɁA�����ʒu��ݒ肷��B
//=============================================================================
void CPlayer::Init(bool ifMinePlayer, VECTOR3 pos)
{
	CRendererGL	*renderer	= CManager::GetRendererGL();
	
	// ���v���C���[���ǂ����Z�b�g
	m_ifMinePlayer = ifMinePlayer;

	// �e�평����
	SetPos(VECTOR3(pos.x, pos.y, pos.z));
	SetRot(VECTOR3(0.0f, 0.0f, 0.0f));
	m_Move			= VECTOR3(0.0f, 0.0f, 0.0f);
	m_RotMove		= VECTOR3(0.0f, 0.0f, 0.0f);
	m_MoveDirection = VECTOR3(0.0f, 0.0f, 0.0f);
	m_bJump			= false;
	m_Scale			= VECTOR3(1.0f, 1.0f, 1.0f);

	m_Gauge = 100.0f;	//�Q�[�W�̏�����
	m_FlgLowSpeed = false;
	m_Radius = 30.0f;
	m_HitEffectTime = 0; // ��e�G�t�F�N�g���Ԃ̏�����
	m_DrawOnOffFlag = true; // �`�揈����ONOFF�t���O��ON��
	m_DeadFlag = false; // ���S�t���O��OFF��

	Model = CSceneModel::Create("./data/MODEL/car.obj");
	CShadow::Create( m_Pos , 100.0f , 100.0f , this );

	BOX_DATA Box = { 50.0f, 50.0f, 50.0f };
	SetBox(Box);

	//����ŕ��D��`�悵�܂�
	//Uninit,Update,Draw�ɂĊe�֐����Ă�ł܂��B
	//�_���[�W���󂯂���CLife����HitDamage�֐����g���Ă�������
	m_pLife = CLife::Create( m_Pos , this );
}

//=============================================================================
//	�֐���	:Uninit
//	����	:����
//	�߂�l	:����
//	����	:�I���������s���B
//=============================================================================
void CPlayer::Uninit(bool isLast)
{
	m_pLife->Uninit();
	Model->Uninit();
}

//=============================================================================
//	�֐���	:Update
//	����	:����
//	�߂�l	:����
//	����	:�X�V�������s���B
//=============================================================================
void CPlayer::Update(void)
{
	CCameraGL	*camera = CManager::GetCamera();	// �J����
	int life = m_pLife -> GetLife( );

	if (CInput::GetKeyboardTrigger(DIK_SPACE)) m_FlgLowSpeed = true;
	else if (CInput::GetKeyboardRelease(DIK_SPACE)) m_FlgLowSpeed = false;

	// ���C�t��0�ȉ��Ȃ�Α�����󂯕t���Ȃ�
	if(life > 0) {
		// ���v���C���[�̏ꍇ�ɂ̂ݏ���
		if (m_ifMinePlayer)
		{
			if (CInput::GetKeyboardPress(DIK_W))				// �ړ������Ɉړ�
			{
				if (CInput::GetKeyboardPress(DIK_A))				// ������
				{
					//��]�ʂ̉��Z
					if (m_FlgLowSpeed == true) m_MoveDirection.y += LOWMOVE_ROT;
					else if (m_FlgLowSpeed == false) m_MoveDirection.y += MOVE_ROT;
				}
				if (CInput::GetKeyboardPress(DIK_D))				// �E���
				{
					//��]�ʂ̉��Z
					if (m_FlgLowSpeed == true) m_MoveDirection.y -= LOWMOVE_ROT;
					else if (m_FlgLowSpeed == false) m_MoveDirection.y -= MOVE_ROT;
				}

				// �ړ��ʂ�ݒ�
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
			if (CInput::GetKeyboardPress(DIK_S))		// �ړ������Ɉړ��̔��΂Ɉړ�
			{
				if (CInput::GetKeyboardPress(DIK_A))				// ������
				{
					//��]�ʂ̉��Z
					if (m_FlgLowSpeed == true) m_MoveDirection.y -= LOWMOVE_ROT;
					else if (m_FlgLowSpeed == false) m_MoveDirection.y -= MOVE_ROT;
				}
				if (CInput::GetKeyboardPress(DIK_D))				// �E���
				{
					//��]�ʂ̉��Z
					if (m_FlgLowSpeed == true) m_MoveDirection.y += LOWMOVE_ROT;
					else if (m_FlgLowSpeed == false) m_MoveDirection.y += MOVE_ROT;
				}

				// �ړ��ʂ�ݒ�
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
				if (CInput::GetKeyboardPress(DIK_W))				// �ړ������Ɉړ�
				{
					if (CInput::GetKeyboardPress(DIK_A))				// ������
					{
						//��]�ʂ̉��Z
						if (m_FlgLowSpeed == true) m_MoveDirection.y += LOWMOVE_ROT;
						else if (m_FlgLowSpeed == false) m_MoveDirection.y += MOVE_ROT;
					}
					if (CInput::GetKeyboardPress(DIK_D))				// �E���
					{
						//��]�ʂ̉��Z
						if (m_FlgLowSpeed == true) m_MoveDirection.y -= LOWMOVE_ROT;
						else if (m_FlgLowSpeed == false) m_MoveDirection.y -= MOVE_ROT;
					}
				}
				else if (CInput::GetKeyboardPress(DIK_S))		// �ړ������Ɉړ��̔��΂Ɉړ�
				{
					if (CInput::GetKeyboardPress(DIK_A))				// ������
					{
						//��]�ʂ̉��Z
						if (m_FlgLowSpeed == true) m_MoveDirection.y -= LOWMOVE_ROT;
						else if (m_FlgLowSpeed == false) m_MoveDirection.y -= MOVE_ROT;
					}
					if (CInput::GetKeyboardPress(DIK_D))				// �E���
					{
						//��]�ʂ̉��Z
						if (m_FlgLowSpeed == true) m_MoveDirection.y += LOWMOVE_ROT;
						else if (m_FlgLowSpeed == false) m_MoveDirection.y += MOVE_ROT;
					}
				}
				else
				{
					if (CInput::GetKeyboardPress(DIK_A))				// ������
					{
						//��]�ʂ̉��Z
						if (m_FlgLowSpeed == true) m_MoveDirection.y += LOWMOVE_ROT;
						else if (m_FlgLowSpeed == false) m_MoveDirection.y += MOVE_ROT;
					}
					if (CInput::GetKeyboardPress(DIK_D))				// �E���
					{
						//��]�ʂ̉��Z
						if (m_FlgLowSpeed == true) m_MoveDirection.y -= LOWMOVE_ROT;
						else if (m_FlgLowSpeed == false) m_MoveDirection.y -= MOVE_ROT;
					}
				}
			
			}

			camera->m_CameraState.posV.x = m_Pos.x + sinf(camera->m_CameraState.Rot.y + m_Rot.y) *camera->m_CameraState.fDistance;
			camera->m_CameraState.posV.z = m_Pos.z + cosf(camera->m_CameraState.Rot.y + m_Rot.y) *camera->m_CameraState.fDistance;

			camera->m_CameraState.posR.x = m_Pos.x + sinf(m_Rot.y) * BMOVE_SPEED;
			camera->m_CameraState.posR.z = m_Pos.z + cosf(m_Rot.y) * BMOVE_SPEED;

			// �W�����v
			if (CInput::GetKeyboardTrigger(DIK_J) && !m_bJump)
			{
				m_Move.y += PLAYER_JUMP;

				m_bJump = true;
			}
			// �e����
			if (CInput::GetKeyboardTrigger(DIK_L))
			{
				CBullet::Create( m_Pos , m_Rot , 10.0f );
			}
		}
		// ��]�ʕ␳
		if (m_Rot.y - m_MoveDirection.y > PI)				// ��]�ʂ��v���X�����ɋt�����̏ꍇ
		{
			// ��]�ʂ��t������
			m_Rot.y -= (PI * 2.0f);
		}
		else if (m_Rot.y - m_MoveDirection.y < -PI)			// ��]�ʂ��}�C�i�X�����ɋt�����̏ꍇ
		{
			// ��]�ʂ��t������
			m_Rot.y += (PI * 2.0f);
		}

		// ��]�ʂ�ݒ�
		m_Rot.y += (m_MoveDirection.y - m_Rot.y) * 0.1f;
	}

	for each (CSceneGL* list in CSceneGL::GetList(PRIORITY_WALL))
	{
		if (CCollision::GetInstance()->SphereToBox(m_Pos, m_Radius, list->GetPos(), &list->GetBox()))
		{
			CDebugProcGL::DebugProc("HitBox\n");
		}
	}

	if (!m_ifMinePlayer)
	{
		for each (CSceneGL* list in CSceneGL::GetList(PRIORITY_BULLET))
		{
			if (CCollision::GetInstance()->SphereToSphere(m_Pos, GetRadius(), list->GetPos(), list->GetRadius()))
			{
				if(m_HitEffectTime <= 0) {
					m_pLife -> HitDamage();
					if(life > 1) m_HitEffectTime = 120; // ���C�t��1�̎��ɔ�e���遁������уG�t�F�N�g�Ɉڍs����̂œ_�ŏ����͂Ȃ�
				}
//				Release();
//				return;
			}
		}
	}


	//************* HP0�����o�e�X�g�������� *****************//

	if(life <= 0 && !m_DeadFlag) {
		m_Move.y += PLAYER_JUMP * 3;
		m_RotMove.x = (rand() % 40) * 0.01f;
		m_RotMove.y = (rand() % 40) * 0.01f;
		m_RotMove.z = (rand() % 40) * 0.01f;
		m_bJump = true;
		m_DeadFlag = true;
	}

	m_Rot.x += m_RotMove.x;
	m_Rot.y += m_RotMove.y;
	m_Rot.z += m_RotMove.z;

	//************* HP0�����o�e�X�g�����܂� *****************//


	// �ړ��ʔ��f
	m_Pos.x += m_Move.x;
	m_Pos.z += m_Move.z;

	//�ړ��ʂ̌���
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

	// �W�����v�ʂ̔��f
	m_Pos.y += m_Move.y;

	if (m_ifMinePlayer)
	{
		CollisionDetection();
	}

	// �v���C���[�̍�����ݒ�
	if (m_Pos.y < 5.0f)
	{
		m_Pos.y = 5.0f;
		m_RotMove.x = 0;
		m_RotMove.y = 0;
		m_RotMove.z = 0;
		m_bJump = false;
	}
	else
	{
		// �W�����v�ʂ̌���
		m_Move.y -= PLAYER_GRAVITY;
	}


	//*************************** ��e�G�t�F�N�g�����J�n ***************************

	// �e�X�g�p 8�`0�L�[�Ŕ�e�G�t�F�N�g ���ꂼ�꒷�����Ⴄ
	// ��8�̔{��-4�`8�̔{��-2�ɐݒ肷��ƍŏ��̓_�ł�3�`1�t���[���Z���Ȃ�̂Œ��ӁB��{��4�t���[������ONOFF��؂�ւ���_��
	if(CInput::GetKeyboardTrigger(DIK_8) && m_HitEffectTime <= 0) {
		m_HitEffectTime = 30;
	}
	else if(CInput::GetKeyboardTrigger(DIK_9) && m_HitEffectTime <= 0) {
		m_HitEffectTime = 59;
	}
	else if(CInput::GetKeyboardTrigger(DIK_0) && m_HitEffectTime <= 0) {
		m_HitEffectTime = 120;
	}

	// ��e�G�t�F�N�g���������s
	if(m_HitEffectTime > 0) {
		HitEffect( );
	}

	//*************************** ��e�G�t�F�N�g�����I�� ***************************
	
	//���D�X�V
	m_pLife->Update();

	Model->Update();

	// ���v���C���[�̏ꍇ�A�ʒu�𑗐M
	if(m_ifMinePlayer && (CManager::m_Frame % 60 == 0))
	{
		// �f�[�^���M
		CNetwork::SendData("player, %d, POS(%.1f %.1f %.1f), ROT(%.1f %.1f %.1f), VEC(%.1f %.1f %.1f)", CManager::GetWhatPlayer(),
			m_Pos.x, m_Pos.y, m_Pos.z,
			m_Rot.x, m_Rot.y, m_Rot.z,
			m_Move.x, m_Move.y, m_Move.z
		);
	}
}

//=============================================================================
//	�֐���	:Draw
//	����	:����
//	�߂�l	:����
//	����	:�`�揈�����s���B
//=============================================================================
void CPlayer::Draw(void)
{
	if(m_DrawOnOffFlag) {
		glMatrixMode(GL_MODELVIEW);		// ���f���r���[�}�g���N�X�̐ݒ�
		glPushMatrix();					// �}�g���N�X�̑ޔ�

		// ���[���h�}�g���N�X�̐ݒ�
		glTranslatef(m_Pos.x, m_Pos.y, m_Pos.z);
		glRotatef((GLfloat)(m_Rot.z * 180.0 / PI), 0.0f, 0.0f, 1.0f);	// ��]�}�g���b�N�X�̐ݒ�A�p�x�͓x���@��
		glRotatef((GLfloat)(m_Rot.y * 180.0 / PI), 0.0f, 1.0f, 0.0f);	// ��]�}�g���b�N�X�̐ݒ�A�p�x�͓x���@��
		glRotatef((GLfloat)(m_Rot.x * 180.0 / PI), 1.0f, 0.0f, 0.0f);	// ��]�}�g���b�N�X�̐ݒ�A�p�x�͓x���@��
		glScalef(m_Scale.x, m_Scale.y, m_Scale.z);

		// ���f���`��
		Model->Draw();

		glMatrixMode(GL_MODELVIEW);		// ���f���r���[�}�g���b�N�X�̐ݒ�
		glPopMatrix();					// �ۑ��}�g���b�N�X�̎��o��
	}

	//���D�`��
	m_pLife->Draw();

	//CDebugProcGL::DebugProc("chara:(%.2f:%.2f:%.2f)\n", m_Pos.x, m_Pos.y, m_Pos.z);
}

//=============================================================================
//	�֐���	:Create
//	����	:VECTOR3 pos(�����ʒu)
//	�߂�l	:����
//	����	:�C���X�^���X�������s���Ƌ��ɁA�����ʒu��ݒ肷��B
//=============================================================================
CPlayer *CPlayer::Create(bool ifMinePlayer, VECTOR3 pos)
{
	CPlayer *player;

	player = new CPlayer;

	player->Init(ifMinePlayer, pos);

	return player;
}

//=============================================================================
//	�֐���	:Update
//	����	:����
//	�߂�l	:����
//	����	:�X�V�������s���B
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
//	�֐���	:Update
//	����	:����
//	�߂�l	:����
//	����	:�X�V�������s���B
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
//	�֐���	:CollisionDetectionBox
//	����	:����
//	�߂�l	:����
//	����	:�{�b�N�X�̓����蔻��
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
//	�֐���	:HitEffect
//	����	:����
//	�߂�l	:����
//	����	:��e�G�t�F�N�g
//=============================================================================

void CPlayer::HitEffect(void) {
	if(m_HitEffectTime % (BLINK_TIME * 2) < BLINK_TIME ) {
		m_DrawOnOffFlag = true;
	}
	else {
		m_DrawOnOffFlag = false;
	}

	// �G�t�F�N�g���Ԃ����炷
	m_HitEffectTime--;
	// �����G�t�F�N�g�̎c�莞�Ԃ�0����������ꍇ�A���Ԃ�0�ɂ��ĕ`��t���O��ON�ɂ���i�N���蓾�Ȃ��͂������Ǖی��j
	if(m_HitEffectTime < 0) {
		m_HitEffectTime = 0;
		m_DrawOnOffFlag = true;
	}
}


//=============================================================================
//	�֐���	:SetHitEffectTime
//	����	:time �G�t�F�N�g���Ԃ̒����i�t���[���P�ʁj
//	�߂�l	:����
//	����	:��e�G�t�F�N�g�ݒ�
//=============================================================================

void CPlayer::SetHitEffectTime(int time) {
	m_HitEffectTime = time;
}