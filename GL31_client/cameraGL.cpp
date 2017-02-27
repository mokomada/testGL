//=============================================================================
//
//	�^�C�g��	�J�����t�@�C��
//	�t�@�C����	camera.cpp
//	�쐬��		AT13A284_07 �r�c�B��
//	�쐬��		2016/04/26
//
//=============================================================================
//=============================================================================
//	�C���N���[�h
//=============================================================================
#include "cameraGL.h"
#include "manager.h"
#include "main.h"
#include "rendererGL.h"
//#include "input.h"
//#include "debugproc.h"

//=============================================================================
//	�֐���	:CCameraGL()
//	����	:����
//	�߂�l	:����
//	����	:�R���X�g���N�^�B
//=============================================================================
CCameraGL::CCameraGL()
{

}

//=============================================================================
//	�֐���	:~CCameraGL()
//	����	:����
//	�߂�l	:����
//	����	:�f�X�g���N�^�B
//=============================================================================
CCameraGL::~CCameraGL()
{

}

//=============================================================================
//	�֐���	:Init
//	����	:����
//	�߂�l	:����
//	����	:�������������s���B
//=============================================================================
void CCameraGL::Init(void)
{
	m_CameraState.posV = VECTOR3(0.0f, 150.0f, 300.0f);
	m_CameraState.posR = VECTOR3(0.0f, 80.0f, 0.0f);
	m_CameraState.vecU = VECTOR3(0.0f, 1.0f, 0.0f);
	m_CameraState.Rot = VECTOR3(0.0f, atan2f((m_CameraState.posR.x - m_CameraState.posV.x), (m_CameraState.posR.z - m_CameraState.posV.z)), 0.0f);
	m_CameraState.fDistance = hypotf((m_CameraState.posR.z - m_CameraState.posV.z), (m_CameraState.posR.x - m_CameraState.posV.x));
}

//=============================================================================
//	�֐���	:Uninit
//	����	:����
//	�߂�l	:����
//	����	:�I���������s���B
//=============================================================================
void CCameraGL::Uninit(void)
{

}

//=============================================================================
//	�֐���	:Update
//	����	:����
//	�߂�l	:����
//	����	:�X�V�������s���B
//=============================================================================
void CCameraGL::Update(void)
{
	// �J�����ړ�
	if (CInput::GetKeyboardPress(DIK_UP) && !CInput::GetKeyboardPress(DIK_LEFT) && !CInput::GetKeyboardPress(DIK_RIGHT))
	{// �J�����ړ�(��)

		// ���_�ړ�
		m_CameraState.posV.x += sinf(m_CameraState.Rot.y) * CAMERA_POSV_MOVEMENT;
		m_CameraState.posV.z += cosf(m_CameraState.Rot.y) * CAMERA_POSV_MOVEMENT;

		// �����_�ݒ�
		m_CameraState.posR.x = m_CameraState.posV.x + (sinf(m_CameraState.Rot.y) * m_CameraState.fDistance);
		m_CameraState.posR.z = m_CameraState.posV.z + (cosf(m_CameraState.Rot.y) * m_CameraState.fDistance);
	}
	else if (CInput::GetKeyboardPress(DIK_DOWN) && !CInput::GetKeyboardPress(DIK_LEFT) && !CInput::GetKeyboardPress(DIK_RIGHT))
	{// �J�����ړ�(��O)

		// ���_�ړ�
		m_CameraState.posV.x += sinf(m_CameraState.Rot.y + PI) * CAMERA_POSV_MOVEMENT;
		m_CameraState.posV.z += cosf(m_CameraState.Rot.y + PI) * CAMERA_POSV_MOVEMENT;

		// �����_�ݒ�
		m_CameraState.posR.x = m_CameraState.posV.x + (sinf(m_CameraState.Rot.y) * m_CameraState.fDistance);
		m_CameraState.posR.z = m_CameraState.posV.z + (cosf(m_CameraState.Rot.y) * m_CameraState.fDistance);
	}
	else if (CInput::GetKeyboardPress(DIK_LEFT))
	{// �J�����ړ�(��)

		if (CInput::GetKeyboardPress(DIK_UP))
		{// ����

			// ���_�ړ�
			m_CameraState.posV.x += sinf(m_CameraState.Rot.y + (PI * 0.25f)) * CAMERA_POSV_MOVEMENT;
			m_CameraState.posV.z += cosf(m_CameraState.Rot.y + (PI * 0.25f)) * CAMERA_POSV_MOVEMENT;

			// �����_�ݒ�
			m_CameraState.posR.x = m_CameraState.posV.x + (sinf(m_CameraState.Rot.y) * m_CameraState.fDistance);
			m_CameraState.posR.z = m_CameraState.posV.z + (cosf(m_CameraState.Rot.y) * m_CameraState.fDistance);
		}
		else if (CInput::GetKeyboardPress(DIK_DOWN))
		{// ����O

			// ���_�ړ�
			m_CameraState.posV.x += sinf(m_CameraState.Rot.y + (PI * 0.75f)) * CAMERA_POSV_MOVEMENT;
			m_CameraState.posV.z += cosf(m_CameraState.Rot.y + (PI * 0.75f)) * CAMERA_POSV_MOVEMENT;

			// �����_�ݒ�
			m_CameraState.posR.x = m_CameraState.posV.x + (sinf(m_CameraState.Rot.y) * m_CameraState.fDistance);
			m_CameraState.posR.z = m_CameraState.posV.z + (cosf(m_CameraState.Rot.y) * m_CameraState.fDistance);
		}
		else
		{// ��

			// ���_�ړ�
			m_CameraState.posV.x += sinf(m_CameraState.Rot.y + (PI * 0.5f)) * CAMERA_POSV_MOVEMENT;
			m_CameraState.posV.z += cosf(m_CameraState.Rot.y + (PI * 0.5f)) * CAMERA_POSV_MOVEMENT;

			// �����_�ݒ�
			m_CameraState.posR.x = m_CameraState.posV.x + (sinf(m_CameraState.Rot.y) * m_CameraState.fDistance);
			m_CameraState.posR.z = m_CameraState.posV.z + (cosf(m_CameraState.Rot.y) * m_CameraState.fDistance);
		}
	}
	else if(CInput::GetKeyboardPress(DIK_RIGHT))
	{// �J�����ړ�(�E)

		if(CInput::GetKeyboardPress(DIK_UP))
		{// �E��

			// ���_�ړ�
			m_CameraState.posV.x += sinf(m_CameraState.Rot.y - (PI * 0.25f)) * CAMERA_POSV_MOVEMENT;
			m_CameraState.posV.z += cosf(m_CameraState.Rot.y - (PI * 0.25f)) * CAMERA_POSV_MOVEMENT;

			// �����_�ݒ�
			m_CameraState.posR.x = m_CameraState.posV.x + (sinf(m_CameraState.Rot.y) * m_CameraState.fDistance);
			m_CameraState.posR.z = m_CameraState.posV.z + (cosf(m_CameraState.Rot.y) * m_CameraState.fDistance);
		}
		else if (CInput::GetKeyboardPress(DIK_DOWN))
		{// �E��O

			// ���_�ړ�
			m_CameraState.posV.x += sinf(m_CameraState.Rot.y - (PI * 0.75f)) * CAMERA_POSV_MOVEMENT;
			m_CameraState.posV.z += cosf(m_CameraState.Rot.y - (PI * 0.75f)) * CAMERA_POSV_MOVEMENT;

			// �����_�ݒ�
			m_CameraState.posR.x = m_CameraState.posV.x + (sinf(m_CameraState.Rot.y) * m_CameraState.fDistance);
			m_CameraState.posR.z = m_CameraState.posV.z + (cosf(m_CameraState.Rot.y) * m_CameraState.fDistance);
		}
		else
		{// �E

			// ���_�ړ�
			m_CameraState.posV.x += sinf(m_CameraState.Rot.y - (PI * 0.5f)) * CAMERA_POSV_MOVEMENT;
			m_CameraState.posV.z += cosf(m_CameraState.Rot.y - (PI * 0.5f)) * CAMERA_POSV_MOVEMENT;

			// �����_�ݒ�
			m_CameraState.posR.x = m_CameraState.posV.x + (sinf(m_CameraState.Rot.y) * m_CameraState.fDistance);
			m_CameraState.posR.z = m_CameraState.posV.z + (cosf(m_CameraState.Rot.y) * m_CameraState.fDistance);
		}
	}

	// ���_�ړ�
	if(KH_Y && !KH_Z && !KH_C)
	{// ���_�ړ�(��)

		// ���_�ݒ�
		m_CameraState.posV.y += CAMERA_POSR_MOVEMENT_Y;
	}
	else if(KH_N && !KH_Z && !KH_C)
	{// ���_�ړ�(��)

		// ���_�ݒ�
		m_CameraState.posV.y -= CAMERA_POSR_MOVEMENT_Y;
	}
	else if(KH_Z)
	{// ���_�ړ�(��)

		if(KH_Y)
		{// ����

			// ���_�ύX
			m_CameraState.posV.y += CAMERA_POSR_MOVEMENT_Y;
			
			// �p�x����
			m_CameraState.Rot.y -= CAMERA_POSR_MOVEMENT_X;
		}
		else if(KH_N)
		{// ����

			// ���_�ύX
			m_CameraState.posV.y -= CAMERA_POSR_MOVEMENT_Y;
			
			// �p�x����
			m_CameraState.Rot.y -= CAMERA_POSR_MOVEMENT_X;
		}
		else
		{// ��

			// �p�x����
			m_CameraState.Rot.y -= CAMERA_POSR_MOVEMENT_X;
		}
		
		// ���_�����_�ԋ����X�V
		m_CameraState.fDistance = hypotf((m_CameraState.posR.z - m_CameraState.posV.z), (m_CameraState.posR.x - m_CameraState.posV.x));
		
		// ���_�ݒ�
		m_CameraState.posV.x = m_CameraState.posR.x - (sinf(m_CameraState.Rot.y) * m_CameraState.fDistance);
		m_CameraState.posV.z = m_CameraState.posR.z - (cosf(m_CameraState.Rot.y) * m_CameraState.fDistance);
	}
	else if(KH_C)
	{// ���_�ړ�(�E)

		if(KH_Y)
		{// �E��

			// ���_�ύX
			m_CameraState.posV.y += CAMERA_POSR_MOVEMENT_Y * sinf(PI * 0.25);
			
			// �p�x����
			m_CameraState.Rot.y += CAMERA_POSR_MOVEMENT_X * sinf(PI * 0.25);
		}
		else if(KH_N)
		{// �E��

			// ���_�ύX
			m_CameraState.posV.y -= CAMERA_POSR_MOVEMENT_Y * sinf(PI * 0.25);
			
			// �p�x����
			m_CameraState.Rot.y += CAMERA_POSR_MOVEMENT_X * sinf(PI * 0.25);
		}
		else
		{// �E

			// �p�x����
			m_CameraState.Rot.y += CAMERA_POSR_MOVEMENT_X;
		}
			
		// ���_�����_�ԋ����X�V
		m_CameraState.fDistance = hypotf((m_CameraState.posR.z - m_CameraState.posV.z), (m_CameraState.posR.x - m_CameraState.posV.x));
		
		// ���_�ݒ�
		m_CameraState.posV.x = m_CameraState.posR.x - (sinf(m_CameraState.Rot.y) * m_CameraState.fDistance);
		m_CameraState.posV.z = m_CameraState.posR.z - (cosf(m_CameraState.Rot.y) * m_CameraState.fDistance);
	}

	// �����_�ړ�
	if(KH_T && !KH_Q && !KH_E)
	{// �����_�ړ�(��)

		// �����_�ݒ�
		m_CameraState.posR.y += CAMERA_POSR_MOVEMENT_Y;
	}
	else if(KH_B && !KH_Q && !KH_E)
	{// �����_�ړ�(��)

		// �����_�ݒ�
		m_CameraState.posR.y -= CAMERA_POSR_MOVEMENT_Y;
	}
	else if(KH_Q)
	{// �����_�ړ�(��)

		if(KH_T)
		{// ����

			// ���_�ύX
			m_CameraState.posR.y += CAMERA_POSR_MOVEMENT_Y * sinf(PI * 0.25);
			
			// �p�x����
			m_CameraState.Rot.y += CAMERA_POSR_MOVEMENT_X * sinf(PI * 0.25);
		}
		else if(KH_B)
		{// ����

			// ���_�ύX
			m_CameraState.posR.y -= CAMERA_POSR_MOVEMENT_Y * sinf(PI * 0.25);
			
			// �p�x����
			m_CameraState.Rot.y += CAMERA_POSR_MOVEMENT_X * sinf(PI * 0.25);
		}
		else
		{// ��

			// �p�x����
			m_CameraState.Rot.y += CAMERA_POSR_MOVEMENT_X;
		}
			
		// ���_�����_�ԋ����X�V
		m_CameraState.fDistance = hypotf((m_CameraState.posR.z - m_CameraState.posV.z), (m_CameraState.posR.x - m_CameraState.posV.x));
		
		// �����_�ݒ�
		m_CameraState.posR.x = m_CameraState.posV.x + (sinf(m_CameraState.Rot.y) * m_CameraState.fDistance);
		m_CameraState.posR.z = m_CameraState.posV.z + (cosf(m_CameraState.Rot.y) * m_CameraState.fDistance);
	}
	else if(KH_E)
	{// �����_�ړ�(�E)

		if(KH_T)
		{// �E��

			// ���_�ύX
			m_CameraState.posR.y += CAMERA_POSR_MOVEMENT_Y * sinf(PI * 0.25);
			
			// �p�x����
			m_CameraState.Rot.y -= CAMERA_POSR_MOVEMENT_X * sinf(PI * 0.25);
		}
		else if(KH_B)
		{// �E��

			// ���_�ύX
			m_CameraState.posR.y -= CAMERA_POSR_MOVEMENT_Y * sinf(PI * 0.25);
			
			// �p�x����
			m_CameraState.Rot.y -= CAMERA_POSR_MOVEMENT_X * sinf(PI * 0.25);
		}
		else
		{// �E

			// �p�x����
			m_CameraState.Rot.y -= CAMERA_POSR_MOVEMENT_X;
		}
			
		// ���_�����_�ԋ����X�V
		m_CameraState.fDistance = hypotf((m_CameraState.posR.z - m_CameraState.posV.z), (m_CameraState.posR.x - m_CameraState.posV.x));
		
		// �����_�ݒ�
		m_CameraState.posR.x = m_CameraState.posV.x + (sinf(m_CameraState.Rot.y) * m_CameraState.fDistance);
		m_CameraState.posR.z = m_CameraState.posV.z + (cosf(m_CameraState.Rot.y) * m_CameraState.fDistance);
	}
}

//=============================================================================
//	�֐���	:Set
//	����	:����
//	�߂�l	:����
//	����	:�J������ݒ肷��B
//=============================================================================
void CCameraGL::Set(void)
{
	// 2D�`�揀��
	glViewport(0, 0, (GLsizei)SCREEN_WIDTH, (GLsizei)SCREEN_HEIGHT);	// �E�B���h�E�S�̂��r���[�|�[�g�ɂ���

	glMatrixMode(GL_PROJECTION);	// ���f���r���[�}�g���b�N�X�̐ݒ�(���e�ϊ�)
	glLoadIdentity();				// �ϊ��s��̏�����
	gluPerspective(30.0, ((GLdouble)SCREEN_WIDTH/(GLdouble)SCREEN_HEIGHT), 1.0f, 100000.0f);

	glMatrixMode(GL_MODELVIEW);		// ���f���r���[�}�g���b�N�X�̐ݒ�
	glLoadIdentity();				// �ϊ��s��̏�����
	gluLookAt(	m_CameraState.posV.x, m_CameraState.posV.y ,m_CameraState.posV.z,
				m_CameraState.posR.x, m_CameraState.posR.y ,m_CameraState.posR.z,
				m_CameraState.vecU.x, m_CameraState.vecU.y ,m_CameraState.vecU.z);
}