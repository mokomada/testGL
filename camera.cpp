/*******************************************************************************
* �^�C�g�� �J��������
* �t�@�C���� camare.cpp
* �쐬�� AT-13A-284 �H�ԗY��
* �쐬�� 2016/04/27
*******************************************************************************/

#include "main.h"
#include "renderer.h"
#include "camera.h"
#include "manager.h"
#include "input.h"
#include "scene.h"
#include "sceneX.h"
#include "player.h"
#include "meshfield.h"
#include "meshwater.h"


/*******************************************************************************
* �O���[�o���ϐ�
*******************************************************************************/



/*******************************************************************************
* �֐����FCCamera
* �����F�Ȃ�
* �߂�l�F�Ȃ�
* �����F�N���X����������
*******************************************************************************/

CCamera::CCamera( ) {

}


/*******************************************************************************
* �֐����F~CCamera
* �����F�Ȃ�
* �߂�l�F�Ȃ�
* �����F�N���X�j��������
*******************************************************************************/

CCamera::~CCamera( ) {

}


/*******************************************************************************
* �֐����FInit
* �����F�Ȃ�
* �߂�l�F�Ȃ�
* �����F�J�����̏�����
*******************************************************************************/

void CCamera::Init(void) {
	// �J���������ݒ�
//	m_camera.posV = D3DXVECTOR3(CAMERA_POSV_X, CAMERA_POSV_Y, CAMERA_POSV_Z);
	m_camera.posR = D3DXVECTOR3(CAMERA_POSR_X, CAMERA_POSR_Y, CAMERA_POSR_Z);
	m_camera.vecU = D3DXVECTOR3(CAMERA_VEC_X, CAMERA_VEC_Y, CAMERA_VEC_Z); // �����͊�{�I�ɕύX���Ȃ�
	m_camera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_camera.fDistance = D3DXVECTOR3(CAMERA_DISTANCE_X, CAMERA_DISTANCE_Y, CAMERA_DISTANCE_Z);
	m_camera.posR_y = 0.0f;
	m_camera.posV_y = 10.0f;
	m_camera.newRot = 0.0f;
	m_camera.rotTime = 0;

	m_camera.posV = D3DXVECTOR3(m_camera.posR.x + sinf(D3DX_PI * m_camera.rot.y) * CAMERA_DISTANCE_Z, CAMERA_POSV_Y, m_camera.posR.z - cosf(D3DX_PI * m_camera.rot.y) * CAMERA_DISTANCE_Z);
}


/*******************************************************************************
* �֐����FUninit
* �����F�Ȃ�
* �߂�l�F�Ȃ�
* �����F�J�����̏I������
*******************************************************************************/

void CCamera::Uninit(void) {

}

/*******************************************************************************
* �֐����FUpdate
* �����F�Ȃ�
* �߂�l�F�Ȃ�
* �����F�J�����̍X�V����
*******************************************************************************/

void CCamera::Update(void) {
	CInput *input;
	input = CManager::GetInput( ); // ���͏��擾
	float field_height;
	float water_height;

	MODEL model = CPlayer::GetPlayer( ); // ���f�����擾

	if(input -> GetKeyboardPress(DIK_W) || input -> GetKeyboardPress(DIK_A) || input -> GetKeyboardPress(DIK_S) || input -> GetKeyboardPress(DIK_D) || input -> GetKeyboardPress(DIK_Q) || input -> GetKeyboardPress(DIK_E) || input -> GetKeyboardPress(DIK_T) || input -> GetKeyboardPress(DIK_B) ) {
/*		// ���s�ړ�
		if(input -> GetKeyboardPress(DIK_A) ) {
			if(input -> GetKeyboardPress(DIK_W) ) {
				m_camera.posV.x += sinf(D3DX_PI * (m_camera.rot.y - 0.75f) ) * CAMERA_MOVE_SPEED;
				m_camera.posV.z -= cosf(D3DX_PI * (m_camera.rot.y - 0.75f) ) * CAMERA_MOVE_SPEED;
			}
			else if(input -> GetKeyboardPress(DIK_S) ) {
				m_camera.posV.x += sinf(D3DX_PI * (m_camera.rot.y - 0.25f) ) * CAMERA_MOVE_SPEED;
				m_camera.posV.z -= cosf(D3DX_PI * (m_camera.rot.y - 0.25f) ) * CAMERA_MOVE_SPEED;
			}
			else {
				m_camera.posV.x += sinf(D3DX_PI * (m_camera.rot.y - 0.5f) ) * CAMERA_MOVE_SPEED;
				m_camera.posV.z -= cosf(D3DX_PI * (m_camera.rot.y - 0.5f) ) * CAMERA_MOVE_SPEED;
			}
		}
		else if(input -> GetKeyboardPress(DIK_D) ) {
			if(input -> GetKeyboardPress(DIK_W) ) {
				m_camera.posV.x += sinf(D3DX_PI * (m_camera.rot.y + 0.75f) ) * CAMERA_MOVE_SPEED;
				m_camera.posV.z -= cosf(D3DX_PI * (m_camera.rot.y + 0.75f) ) * CAMERA_MOVE_SPEED;
			}
			else if(input -> GetKeyboardPress(DIK_S) ) {
				m_camera.posV.x += sinf(D3DX_PI * (m_camera.rot.y + 0.25f) ) * CAMERA_MOVE_SPEED;
				m_camera.posV.z -= cosf(D3DX_PI * (m_camera.rot.y + 0.25f) ) * CAMERA_MOVE_SPEED;
			}
			else {
				m_camera.posV.x += sinf(D3DX_PI * (m_camera.rot.y + 0.5f) ) * CAMERA_MOVE_SPEED;
				m_camera.posV.z -= cosf(D3DX_PI * (m_camera.rot.y + 0.5f) ) * CAMERA_MOVE_SPEED;
			}
		}
		else if(input -> GetKeyboardPress(DIK_W) ) {
				m_camera.posV.x += sinf(D3DX_PI * (m_camera.rot.y + 1.0f) ) * CAMERA_MOVE_SPEED;
				m_camera.posV.z -= cosf(D3DX_PI * (m_camera.rot.y + 1.0f) ) * CAMERA_MOVE_SPEED;
		}
		else if(input -> GetKeyboardPress(DIK_S) ) {
				m_camera.posV.x += sinf(D3DX_PI * (m_camera.rot.y) ) * CAMERA_MOVE_SPEED;
				m_camera.posV.z -= cosf(D3DX_PI * (m_camera.rot.y) ) * CAMERA_MOVE_SPEED;
		}

		// �����_����
		// ����
		if(input -> GetKeyboardPress(DIK_Q) ) {
			m_camera.rot.y += CAMERA_ROT_SPEED;
		}
		else if(input -> GetKeyboardPress(DIK_E) ) {
			m_camera.rot.y -= CAMERA_ROT_SPEED;
		}*/

		// �㉺�ړ�
		if(input -> GetKeyboardPress(DIK_T) ) {
			m_camera.posR_y += CAMERA_MOVE_SPEED;
		}
		else if(input -> GetKeyboardPress(DIK_B) ) {
			m_camera.posR_y -= CAMERA_MOVE_SPEED;
		}

		// �ړ��̔��f
		m_camera.posR.x = m_camera.posV.x - sinf(D3DX_PI * (m_camera.rot.y + 0.0f) ) * m_camera.fDistance.z;
		m_camera.posR.z = m_camera.posV.z + cosf(D3DX_PI * (m_camera.rot.y + 0.0f) ) * m_camera.fDistance.z;
	}

	if(input -> GetKeyboardPress(DIK_Z) || input -> GetKeyboardPress(DIK_C) || input -> GetKeyboardPress(DIK_U) || input -> GetKeyboardPress(DIK_M) || input -> GetKeyboardPress(DIK_Y) || input -> GetKeyboardPress(DIK_N) ){
		// ���_����
		// ����
		if(input -> GetKeyboardPress(DIK_Z) ) {
			m_camera.rot.y -= CAMERA_ROT_SPEED;
		}
		else if(input -> GetKeyboardPress(DIK_C) ) {
			m_camera.rot.y += CAMERA_ROT_SPEED;
		}

		// �㉺�ړ�
		if(input -> GetKeyboardPress(DIK_Y) ) {
			m_camera.posV_y += CAMERA_MOVE_SPEED;
		}
		else if(input -> GetKeyboardPress(DIK_N) ) {
			m_camera.posV_y -= CAMERA_MOVE_SPEED;
		}

		// �����̕ύX
		if(input -> GetKeyboardPress(DIK_U) || input -> GetKeyboardPress(DIK_M) ) {
			if(input -> GetKeyboardPress(DIK_M) ) {
				m_camera.fDistance.z += CAMERA_CHANGE_DISTANCE;
			}
			else {
				m_camera.fDistance.z -= CAMERA_CHANGE_DISTANCE;
			}
		}

		// �����̗�O����
		if(m_camera.fDistance.z > CAMERA_MAX_DISTANCE) {
			m_camera.fDistance.z = CAMERA_MAX_DISTANCE;
		}
		else if(m_camera.fDistance.z < CAMERA_MIN_DISTANCE) {
			m_camera.fDistance.z = CAMERA_MIN_DISTANCE;
		}

		// �ړ��̔��f
		m_camera.posV.x = m_camera.posR.x + sinf(D3DX_PI * (m_camera.rot.y + 0.0f) ) * m_camera.fDistance.z;
		m_camera.posV.z = m_camera.posR.z - cosf(D3DX_PI * (m_camera.rot.y + 0.0f) ) * m_camera.fDistance.z;
	}

	// �J������荞�ݏ���
	if(input -> GetKeyboardPress(DIK_W) || input -> GetKeyboardPress(DIK_A) || input -> GetKeyboardPress(DIK_S) || input -> GetKeyboardPress(DIK_D) || input -> GetKeyboardPress(DIK_Q) || input -> GetKeyboardPress(DIK_E) ) {
		m_camera.rotTime = CAMERA_ROT_TIME;
	}

	if(m_camera.rotTime > 0) {
		m_camera.rotTime --;
	}

	// ������荞�ݏ����@��~����Ɖ�荞�݁Aif���R�����g�A�E�g�ŏ펞��荞�݁A�S�R�����g�A�E�g�Ŏ�����荞�݂Ȃ�
	if(!m_camera.rotTime) {
		m_camera.newRot = fmod(-model.rot.y + 2.0f, 2.0f) - 1.0f;
		if(abs(m_camera.newRot - m_camera.rot.y) <= 1.0f) {
			m_camera.rot.y += (m_camera.newRot - m_camera.rot.y) * CAMERA_ROT_SPEED;
		}
		if(abs(m_camera.newRot - m_camera.rot.y) > 1.0f) {
			m_camera.rot.y += (fmod(m_camera.newRot + 2.0f, 2.0f) - fmod(m_camera.rot.y + 2.0f, 2.0f) ) * CAMERA_ROT_SPEED;
		}
	}

	// �����̗�O�����i�I�[�o�[�t���[�h�~�j
	if(m_camera.rot.y > 1.0f) {
		m_camera.rot.y -= 2.0f;
	}
	else if(m_camera.rot.y < -1.0f) {
		m_camera.rot.y += 2.0f;
	}

	// �����_�̗�O����
	if(m_camera.posR_y > CAMERA_POSRMAX_Y) {
		m_camera.posR_y = CAMERA_POSRMAX_Y;
	}
	else if(m_camera.posR_y < CAMERA_POSRMIN_Y) {
		m_camera.posR_y = CAMERA_POSRMIN_Y;
	}

	// ���_�̗�O����
	if(m_camera.posV_y > CAMERA_POSVMAX_Y) {
		m_camera.posV_y = CAMERA_POSVMAX_Y;
	}
	else if(m_camera.posV_y < CAMERA_POSVMIN_Y) {
		m_camera.posV_y = CAMERA_POSVMIN_Y;
	}

	// ���f���ǐ�����
	m_camera.posR.x += ( (model.pos.x - sinf(D3DX_PI * (model.rot.y + 0.0f) ) * PLAYER_VIEW_DISTANCE) - m_camera.posR.x) * 0.3f;
	m_camera.posR.z += ( (model.pos.z - cosf(D3DX_PI * (model.rot.y + 0.0f) ) * PLAYER_VIEW_DISTANCE) - m_camera.posR.z) * 0.3f;
	m_camera.posR.y += (m_camera.posR_y + model.pos.y - m_camera.posR.y) * 0.1f;

	m_camera.posV.x += (m_camera.posR.x + sinf(D3DX_PI * (m_camera.rot.y + 0.0f) ) * m_camera.fDistance.z - m_camera.posV.x) * 0.5f;
	m_camera.posV.z += (m_camera.posR.z - cosf(D3DX_PI * (m_camera.rot.y + 0.0f) ) * m_camera.fDistance.z - m_camera.posV.z) * 0.5f;
	m_camera.posV.y += (m_camera.posV_y + m_camera.fDistance.y + model.pos.y - m_camera.posV.y) * 0.1f;

	// �n�ʂ߂肱�ݔ���
	field_height = CMeshfield::GetFieldHeight(m_camera.posV);
	if(m_camera.posV.y < field_height + 0.5f) {
		m_camera.posV.y = field_height + 0.5f;
	}

	// ���ʂ߂肱�ݔ���
	water_height = CMeshwater::GetWaterHeight(m_camera.posV);
	if(m_camera.posV.y < water_height + 0.5f) {
		m_camera.posV.y = water_height + 0.5f;
	}

	// �ʒu�̗�O����
/*	if(m_camera.posV.x < MESHFIELD_FIELD_X) {
		m_camera.posV.x = MESHFIELD_FIELD_X;
	}
	else if(m_camera.posV.x > MESHFIELD_FIELD_X + MESHFIELD_FIELD_WIDTH) {
		m_camera.posV.x = MESHFIELD_FIELD_X + MESHFIELD_FIELD_WIDTH;
	}

	if(m_camera.posV.z < MESHFIELD_FIELD_Z) {
		m_camera.posV.z = MESHFIELD_FIELD_Z;
	}
	else if(m_camera.posV.z > MESHFIELD_FIELD_Z + MESHFIELD_FIELD_HEIGHT) {
		m_camera.posV.z = MESHFIELD_FIELD_Z + MESHFIELD_FIELD_HEIGHT;
	}*/
}


/*******************************************************************************
* �֐����FSetCamera
* �����F�Ȃ�
* �߂�l�F�Ȃ�
* �����F�J�����̐ݒ�
*******************************************************************************/

void CCamera::SetCamera(void) {
	CRenderer *renderer; // �f�o�C�X�擾�p�ϐ�
	renderer = CManager::GetRenderer( ); // �����_���̃A�h���X�擾
	LPDIRECT3DDEVICE9 device = renderer -> GetDevice( ); // �f�o�C�X�擾

	// �v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_camera.mtxProjection);
	// �v���W�F�N�V�����}�g���b�N�X�̍쐬
	D3DXMatrixPerspectiveFovLH(&m_camera.mtxProjection, D3DX_PI * 0.25, float(SCREEN_WIDTH) / float(SCREEN_HEIGHT), 0.5f, 10000.0f);
	// �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	device -> SetTransform(D3DTS_PROJECTION, &m_camera.mtxProjection);

	// �r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_camera.mtxView);
	// �r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&m_camera.mtxView, &m_camera.posV, &m_camera.posR, &m_camera.vecU);
	// �r���[�}�g���b�N�X�̐ݒ�
	device -> SetTransform(D3DTS_VIEW, &m_camera.mtxView);
}

/*******************************************************************************
* �֐����FGetCamera
* �����F�Ȃ�
* �߂�l�Fm_camera : �J�������
* �����F�J�������̎擾
*******************************************************************************/

CAMERA CCamera::GetCameraData( ) {
	return m_camera;
}
