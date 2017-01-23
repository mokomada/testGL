//=============================================================================
//
//	�^�C�g��	�t�F�[�h����
//	�t�@�C����	fade.cpp
//	�쐬��		AT13A284_07 �r�c�B��
//	�쐬��		2016/07/12
//
//=============================================================================
//=============================================================================
//	�C���N���[�h
//=============================================================================
#include "fade.h"
#include "manager.h"
#include "input.h"
#include "scene2DGL.h"

//=============================================================================
//	�ÓI�����o�ϐ�
//=============================================================================
CMode		*CFade::m_NextMode;
int			CFade::m_NextModeState;
FADE_STATE	CFade::m_FadeState;
int			CFade::m_FadeTime;
float		CFade::m_Alpha;

//=============================================================================
//	�֐���	:Init
//	����	:����
//	�߂�l	:����
//	����	:�������������s���B
//=============================================================================
void CFade::Init(void)
{
	m_Alpha = 1.0f;
	m_FadeTime = 0;
	m_FadeState = FS_FIRST;
}

//=============================================================================
//	�֐���	:Uninit
//	����	:����
//	�߂�l	:����
//	����	:�I���������s���B
//=============================================================================
void CFade::Uninit(void)
{

}

//=============================================================================
//	�֐���	:Update
//	����	:����
//	�߂�l	:����
//	����	:�X�V�������s���B
//=============================================================================
void CFade::Update(void)
{
	if(m_FadeState == FS_FIRST)
	{// �����t�F�[�Y
		m_Alpha -= (1.0f / FADE_TIME);

		if(m_Alpha < 0.0f)
		{
			m_Alpha = 0.0f;
			m_FadeState = FS_NONE;
		}
	}
	else if(m_FadeState == FS_IN)
	{// �t�F�[�h�C���̎�

		m_Alpha -= (1.0f / FADE_TIME);

		if(m_Alpha < 0.0f)
		{
			m_Alpha = 0.0f;
			m_FadeState = FS_NONE;
		}
	}
	else if(m_FadeState == FS_OUT)
	{// �t�F�[�h�A�E�g�̎�

		m_Alpha += (1.0f / FADE_TIME);
		

		if(m_Alpha > 1.0f)
		{// �t�F�[�h�����������ꍇ

			m_Alpha = 1.0f;

			m_FadeState = FS_IN;
			
			if(m_NextMode != NULL)
			{
				CManager::SetMode(m_NextMode, m_NextModeState);
				m_NextMode = NULL;
			}
		}
	}

}

//=============================================================================
//	�֐���	:Draw
//	����	:����
//	�߂�l	:����
//	����	:�`�揈�����s���B
//=============================================================================
void CFade::Draw(void)
{
	// ���f���r���[�}�g���b�N�X�̐ݒ�(���e�ϊ�)
	glMatrixMode(GL_PROJECTION);
	// �}�g���b�N�X�̕ۑ�
	glPushMatrix();
	// �ϊ��s��̏�����
	glLoadIdentity();

	// ���s�ˉeor���ˉe
	glOrtho(0, (GLdouble)SCREEN_WIDTH, (GLdouble)SCREEN_HEIGHT, 0, -100.0, 100.0);
	// ���[���h���W�n�̕\���̈���C�r���[�|�[�g�̑傫���ɔ�Ⴓ����

	// ���f���r���[�}�g���b�N�X�̐ݒ�
	glMatrixMode(GL_MODELVIEW);
	// �}�g���b�N�X�̕ۑ�
	glPushMatrix();
	// �ϊ��s��̏�����
	glLoadIdentity();

	// �u�����h�L����
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// ���C�g������
	glDisable(GL_LIGHTING);

	// �|���S���`��
	glBegin(GL_TRIANGLE_STRIP);
	{
		// ���_�F�ݒ�
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);


		// �`��p�̃e�N�X�`�����W�E���_���W�ݒ�
		// ���㒸�_
		glColor4f(0.0f, 0.0f, 0.0f, m_Alpha);
		glTexCoord2d(0.0, 1.0);
		glVertex3f(0.0f, 0.0f, 0.0f);

		// �E�㒸�_
		glColor4f(0.0f, 0.0f, 0.0f, m_Alpha);
		glTexCoord2d(1.0, 1.0);
		glVertex3f(SCREEN_WIDTH, 0.0f, 0.0f);

		// �������_
		glColor4f(0.0f, 0.0f, 0.0f, m_Alpha);
		glTexCoord2d(0.0, 0.0);
		glVertex3f(0.0f, SCREEN_HEIGHT, 0.0f);

		// �E�����_
		glColor4f(0.0f, 0.0f, 0.0f, m_Alpha);
		glTexCoord2d(1.0, 0.0);
		glVertex3f(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
	}
	glEnd();

	// �u�����h������
	glDisable(GL_BLEND);

	// ���C�g�L����
	glEnable(GL_LIGHTING);

	// ���f���r���[�}�g���b�N�X�̐ݒ�(���e�ϊ�)
	glMatrixMode(GL_PROJECTION);
	// �ۑ��}�g���b�N�X�̎��o��
	glPopMatrix();

	// ���f���r���[�}�g���b�N�X�̐ݒ�
	glMatrixMode(GL_MODELVIEW);
	// �ۑ��}�g���b�N�X�̎��o��
	glPopMatrix();

}

//=============================================================================
//	�֐���	:Start
//	����	:����
//	�߂�l	:����
//	����	:�t�F�[�h���J�n����B
//=============================================================================
void CFade::Start(CMode *nextMode, int nextModeState, FADE_STATE fadeState)
{
	if((nextMode != NULL) && (m_FadeState == FS_NONE))
	{
		m_NextMode = nextMode;
		m_NextModeState = nextModeState;
		m_FadeState = fadeState;
	}
}