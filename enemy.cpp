/*******************************************************************************
* �^�C�g�� GM31 X�t�@�C���`��
* �t�@�C���� sceneX.cpp
* �쐬�� AT-13A-284 �H�ԗY��
* �쐬�� 2016/04/26
*******************************************************************************/

/*******************************************************************************
* �C���N���[�h�t�@�C��
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
// �X�^�e�B�b�N�ϐ��̐���
//*****************************************************************************

//MODEL CEnemy::m_enemy = {D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0), 0};


/*******************************************************************************
* �֐����FCEnemy
* �����F�Ȃ�
* �߂�l�F�Ȃ�
* �����F�N���X����������
*******************************************************************************/

CEnemy::CEnemy(int priority, OBJTYPE objType):CSceneX(priority, objType) {

}


/*******************************************************************************
* �֐����F~CEnemy
* �����F�Ȃ�
* �߂�l�F�Ȃ�
* �����F�N���X�j��������
*******************************************************************************/

CEnemy::~CEnemy( ) {

}


/*******************************************************************************
* �֐����FInit
* �����F�Ȃ�
* �߂�l�F�Ȃ�
* �����F����������
*******************************************************************************/

void CEnemy::Init(void) {
	CRenderer *renderer; // �f�o�C�X�擾�p�ϐ�
	renderer = CManager::GetRenderer( ); // �����_���̃A�h���X�擾
	LPDIRECT3DDEVICE9 device = renderer -> GetDevice( ); // �f�o�C�X�擾
	m_pTexture = NULL;

	D3DXLoadMeshFromX(ENEMY_NAME,
		D3DXMESH_SYSTEMMEM,
		device,
		NULL,
		&m_pBuffMat,
		NULL,
		&m_numMat,
		&m_pMesh);

	// �ϐ��̏�����
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

	// �e�N�X�`���ݒ�
	D3DXCreateTextureFromFile(device, ENEMY_TEXTURE_NAME, &m_pTexture);
}


/*******************************************************************************
* �֐����FUninit
* �����F�Ȃ�
* �߂�l�F�Ȃ�
* �����F�I������
*******************************************************************************/

void CEnemy::Uninit(void) {
	if(m_pTexture != NULL) {
		m_pTexture -> Release( ); // �e�N�X�`���̊J��
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
* �֐����FUpdate
* �����F�Ȃ�
* �߂�l�F�Ȃ�
* �����F�X�V����
*******************************************************************************/

void CEnemy::Update(void) {
	CCamera *get_camera;
	get_camera = CGame::GetCamera( ); // �J�������擾
	CAMERA camera = get_camera -> GetCameraData( );
	MODEL old_model = m_enemy; // ���ݏ��ێ�
	float field_height; // �n�ʂ̍���
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

	// ���f���̈ړ�����
		if(m_rnd < 3) {
			if(m_rnd == 1) { // ����ړ�
				m_enemy.move.x += sinf(D3DX_PI * (camera.rot.y - 0.75f) ) * ENEMY_MOVE_SPEED;
				m_enemy.move.z -= cosf(D3DX_PI * (camera.rot.y - 0.75f) ) * ENEMY_MOVE_SPEED;
				m_newRot = -camera.rot.y + 0.75f;
			}
			else if(m_rnd == 2) { // �����ړ�
				m_enemy.move.x += sinf(D3DX_PI * (camera.rot.y - 0.25f) ) * ENEMY_MOVE_SPEED;
				m_enemy.move.z -= cosf(D3DX_PI * (camera.rot.y - 0.25f) ) * ENEMY_MOVE_SPEED;
				m_newRot = -camera.rot.y + 0.25f;
			}
			else { // ���ړ�
				m_enemy.move.x += sinf(D3DX_PI * (camera.rot.y - 0.5f) ) * ENEMY_MOVE_SPEED;
				m_enemy.move.z -= cosf(D3DX_PI * (camera.rot.y - 0.5f) ) * ENEMY_MOVE_SPEED;
				m_newRot = -camera.rot.y + 0.5f;
			}
		}
		// ��ړ�
		else if(m_rnd == 3) {
			m_enemy.move.x += sinf(D3DX_PI * (camera.rot.y + 1.0f) ) * ENEMY_MOVE_SPEED;
			m_enemy.move.z -= cosf(D3DX_PI * (camera.rot.y + 1.0f) ) * ENEMY_MOVE_SPEED;
			m_newRot = -camera.rot.y + 1.0f;
		}
		else if(m_rnd < 7) {
			if(m_rnd == 6) { // �E��ړ�
				m_enemy.move.x += sinf(D3DX_PI * (camera.rot.y + 0.75f) ) * ENEMY_MOVE_SPEED;
				m_enemy.move.z -= cosf(D3DX_PI * (camera.rot.y + 0.75f) ) * ENEMY_MOVE_SPEED;
				m_newRot = -camera.rot.y - 0.75f;
			}
			else if(m_rnd == 5) { // �E���ړ�
				m_enemy.move.x += sinf(D3DX_PI * (camera.rot.y + 0.25f) ) * ENEMY_MOVE_SPEED;
				m_enemy.move.z -= cosf(D3DX_PI * (camera.rot.y + 0.25f) ) * ENEMY_MOVE_SPEED;
				m_newRot = -camera.rot.y - 0.25f;
			}
			else { // �E�ړ�
				m_enemy.move.x += sinf(D3DX_PI * (camera.rot.y + 0.5f) ) * ENEMY_MOVE_SPEED;
				m_enemy.move.z -= cosf(D3DX_PI * (camera.rot.y + 0.5f) ) * ENEMY_MOVE_SPEED;
				m_newRot = -camera.rot.y - 0.5f;
			}
		}
		// ���ړ�
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


	// �W�����v���ł���Η������x�����Z
	if(m_enemy.jump) {
		m_enemy.move.y -= ENEMY_FALL_SPEED;
	}

	// �ړ��ʔ��f
	m_enemy.pos.x += (m_enemy.move.x * 0.9f);
	m_enemy.pos.y += (m_enemy.move.y * 0.9f);
	m_enemy.pos.z += (m_enemy.move.z * 0.9f);

	// �ړ��ʌ���
	m_enemy.move.x *= ENEMY_MOVE_REDUCE;
	m_enemy.move.y *= ENEMY_FALL_REDUCE;
	m_enemy.move.z *= ENEMY_MOVE_REDUCE;

	// ���E�̉ʂĔ��� �������������Ă������
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

	// �t�B�[���h�����擾
	field_height = CMeshfield::GetFieldHeight(m_enemy.pos);

	// ��������
	if(m_enemy.jump == false) {
		m_enemy.pos.y = field_height;
	}

	// �t�B�[���h�߂荞�ݏ���
	if(m_enemy.pos.y < field_height ){
		m_enemy.pos.y = field_height;
		m_enemy.move.y = 0.0f;
		m_enemy.jump = false;
	}

	// m_newRot����
	if(m_newRot > 1.0f) {
		m_newRot -= 2.0f;
	}
	else if(m_newRot < -1.0f) {
		m_newRot += 2.0f;
	}

	// ���f���̕����␳
	if(abs(m_newRot - m_enemy.rot.y) <= 1.0f) {
		m_enemy.rot.y += (m_newRot - m_enemy.rot.y) * 0.1f;
	}
	if(abs(m_newRot - m_enemy.rot.y) > 1.0f) {
		m_enemy.rot.y += (fmod(m_newRot + 2.0f, 2.0f) - fmod(m_enemy.rot.y + 2.0f, 2.0f) ) * 0.1f;
	}

/*	D3DXQuaternionRotationAxis(&quat, &axis, 0.0f);
	D3DXQuaternionMultiply(&m_enemy.rot, &m_enemy.rot, &quat);*/

	// ��]�p�̗�O����
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

	// �ڐG����
	if( sqrt( (m_enemy.pos.x - player.pos.x) * (m_enemy.pos.x - player.pos.x) + (m_enemy.pos.z - player.pos.z) * (m_enemy.pos.z - player.pos.z) ) < 2.0f && m_respawn == 0) {
		CSound::PlaySound(SOUND_LABEL_SE_HIT);
		CScore::AddScore(10);
		m_respawn += ENEMY_RESPAWN_TIME;
	}
}


/*******************************************************************************
* �֐����FDraw
* �����F�Ȃ�
* �߂�l�F�Ȃ�
* �����F�`�揈��
*******************************************************************************/

void CEnemy::Draw(void) {
	if(m_respawn == 0) {
		CRenderer *renderer;
		renderer = CManager::GetRenderer( );
		LPDIRECT3DDEVICE9 device = renderer -> GetDevice( ); // �f�o�C�X�擾
		D3DXMATRIX mtxScl, mtxRot, mtxTrans; // �v�Z�p
		D3DXMATERIAL *pMat;
		D3DMATERIAL9 matDef; // �}�e���A�����ۑ��p

		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&m_mtxWorld);
		// ���[���h�}�g���b�N�X�̍쐬
		// �X�P�[���𔽉f
		D3DXMatrixScaling(&mtxScl, ENEMY_SCALE_X, ENEMY_SCALE_Y, ENEMY_SCALE_Z);
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxScl);

		// ��]�𔽉f
	//	D3DXMatrixRotationQuaternion(&mtxRot, &m_enemy.rot); // ������ y, x, z �̏��Ԃɒ��ӁI�I�I ������
		D3DXMatrixRotationYawPitchRoll(&mtxRot, m_enemy.rot.y * D3DX_PI, m_enemy.rot.x * D3DX_PI, m_enemy.rot.z * D3DX_PI);
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

		// �ړ��𔽉f
		D3DXMatrixTranslation(&mtxTrans, m_enemy.pos.x, m_enemy.pos.y, m_enemy.pos.z);
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

		// ���[���h�}�g���b�N�X�̐ݒ�
		device -> SetTransform(D3DTS_WORLD, &m_mtxWorld);

		// ���݃}�e���A�����擾
		device -> GetMaterial(&matDef);

		// �}�e���A���ݒ�
		pMat = (D3DXMATERIAL*)m_pBuffMat -> GetBufferPointer( );
		for(int nCntMat = 0; nCntMat < (int)m_numMat; nCntMat++) {
			device -> SetMaterial(&pMat[nCntMat].MatD3D);
			device -> SetTexture(0, m_pTexture);
			m_pMesh -> DrawSubset(nCntMat);
		}

		// �}�e���A���̐ݒ��߂�
		device -> SetMaterial(&matDef);
	}
}


/*******************************************************************************
* �֐����FCreate
* �����FsceneX : �A�h���X
* �߂�l�F�Ȃ�
* �����F�I�u�W�F�N�g�̐���
*******************************************************************************/

CEnemy *CEnemy::Create(void) {
	CEnemy *sceneX;
	sceneX = new CEnemy;
	sceneX -> Init( );
	return sceneX;
}


/*******************************************************************************
* �֐����FGetEnemy
* �����F�Ȃ�
* �߂�l�Fm_enemy
* �����F���f���̏���Ԃ�
*******************************************************************************/

MODEL CEnemy::GetEnemy(void) {
	return m_enemy;
}
