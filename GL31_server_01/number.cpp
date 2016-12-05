//=============================================================================
//
//	�^�C�g��	�����`��
//	�t�@�C����	number.cpp
//	�쐬��		AT13A284_07 �r�c�B��
//	�쐬��		2016/11/14
//
//=============================================================================
//=============================================================================
//	�C���N���[�h
//=============================================================================
#include "number.h"
#include "manager.h"
#include "main.h"
#include "rendererGL.h"

//=============================================================================
//	�ÓI�����o�ϐ�
//=============================================================================

//=============================================================================
//	�֐���	:CNumber()
//	����	:����
//	�߂�l	:����
//	����	:�R���X�g���N�^�B
//=============================================================================
CNumber::CNumber(int priority, OBJTYPE objtype) : CSceneGL(priority, objtype)
{
	m_fLength	= 0.0f;
	m_fAngle	= 0.0f;
}

//=============================================================================
//	�֐���	:~CNumber()
//	����	:����
//	�߂�l	:����
//	����	:�f�X�g���N�^�B
//=============================================================================
CNumber::~CNumber()
{

}

//=============================================================================
//	�֐���	:Init
//	����	:VECTOR3 pos(�����ʒu)
//	�߂�l	:����
//	����	:�������������s���Ƌ��ɁA�����ʒu��ݒ肷��B
//=============================================================================
void CNumber::Init(VECTOR3 pos, VECTOR2 size, int value, char *texName)
{
	CRendererGL	*renderer = CManager::GetRendererGL();


	// �e�평���ݒ�
	SetPos(VECTOR3(pos.x, pos.y, pos.z));
	SetRot(VECTOR3(0.0f, 0.0f, 0.0f));
	m_Size		= size;
	m_fAngle	= atan2f(m_Size.x, m_Size.y);
	m_fLength	= hypotf(m_Size.x, m_Size.y) * 0.5f;
	m_Number	= 0;

	// �e�N�X�`���Ǎ�
	m_Texture = renderer->CreateTextureTGA(texName);

}

//=============================================================================
//	�֐���	:Uninit
//	����	:����
//	�߂�l	:����
//	����	:�I���������s���B
//=============================================================================
void CNumber::Uninit(bool isLast)
{

}

//=============================================================================
//	�֐���	:Update
//	����	:����
//	�߂�l	:����
//	����	:�X�V�������s���B
//=============================================================================
void CNumber::Update(void)
{

}

//=============================================================================
//	�֐���	:Draw
//	����	:����
//	�߂�l	:����
//	����	:�`�揈�����s���B
//=============================================================================
void CNumber::Draw(void)
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

	// �`�揈����������
	glBindTexture(GL_TEXTURE_2D, m_Texture);

	// �e�N�X�`���}�b�s���O�L����
	glEnable(GL_TEXTURE_2D);

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

		// �ΐ��̒����v�Z
		m_fLength = hypotf(m_Size.x, m_Size.y) * 0.5f;

		// �`��p�̃e�N�X�`�����W�E���_���W�ݒ�
		// ���㒸�_
		glTexCoord2d((m_Number * 0.1f), 1.0);
		glVertex3f((m_Pos.x - (sinf(m_fAngle + m_Rot.z) * m_fLength)), (m_Pos.y + (cosf(m_fAngle + m_Rot.z + PI) * m_fLength)), 0.0f);

		// �E�㒸�_
		glTexCoord2d((m_Number * 0.1f + 0.1f), 1.0);
		glVertex3f((m_Pos.x - (sinf(-m_fAngle + m_Rot.z) * m_fLength)), (m_Pos.y + (cosf(-m_fAngle + m_Rot.z + PI) * m_fLength)), 0.0f);

		// �������_
		glTexCoord2d((m_Number * 0.1f), 0.0);
		glVertex3f((m_Pos.x - (sinf(-m_fAngle + m_Rot.z + PI) * m_fLength)), (m_Pos.y + (cosf(-m_fAngle + m_Rot.z) * m_fLength)), 0.0f);

		// �E�����_
		glTexCoord2d((m_Number * 0.1f + 0.1f), 0.0);
		glVertex3f((m_Pos.x - (sinf(m_fAngle + m_Rot.z - PI) * m_fLength)), (m_Pos.y + (cosf(m_fAngle + m_Rot.z) * m_fLength)), 0.0f);
	}
	glEnd();

	// �e�N�X�`���}�b�s���O������
	glDisable(GL_TEXTURE_2D);

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
//	�֐���	:Create
//	����	:VECTOR3 pos(�����ʒu)
//	�߂�l	:����
//	����	:�C���X�^���X�������s���Ƌ��ɁA�����ʒu��ݒ肷��B
//=============================================================================
CNumber *CNumber::Create(VECTOR3 pos, VECTOR2 size, int value, char *texName)
{
	CNumber *number;	// �C���X�^���X
	
	// �C���X�^���X����
	number = new CNumber;
	
	// ����������
	number->Init(pos, size, value, texName);
	
	// �C���X�^���X�����^�[��
	return number;
}

//=============================================================================
//	�֐���	:Create
//	����	:int value(���l)
//	�߂�l	:����
//	����	:�����l�A���邢�͏����_���̑��̋L�����Z�b�g����B
//=============================================================================
void CNumber::SetNumber(int value)
{
	// 臒l�`�F�b�N
	if(value < -1)
	{
		value = 0;
	}
	else if(value > 9)
	{
		value = 9;
	}

	m_Number = value;
}