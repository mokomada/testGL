//=============================================================================
//
//	�^�C�g��	�V�[���t�@�C��(2D)
//	�t�@�C����	scene2D.cpp
//	�쐬��		AT13A284_07 �r�c�B��
//	�쐬��		2016/11/14
//
//=============================================================================
//=============================================================================
//	�C���N���[�h
//=============================================================================
#include "main.h"
#include "manager.h"
#include "rendererGL.h"
#include "scene2DGL.h"

//=============================================================================
//	�֐���	:CScene2D()
//	����	:����
//	�߂�l	:����
//	����	:�R���X�g���N�^�B
//=============================================================================
CScene2DGL::CScene2DGL(bool ifListAdd, int priority, OBJTYPE objType) : CSceneGL(ifListAdd, priority, objType)
{
	m_fLength	= 0.0f;
	m_fAngle	= 0.0f;
}

//=============================================================================
//	�֐���	:~CScene2D()
//	����	:����
//	�߂�l	:����
//	����	:�f�X�g���N�^�B
//=============================================================================
CScene2DGL::~CScene2DGL()
{

}

//=============================================================================
//	�֐���	:Init
//	����	:VECTOR3 pos(�����ʒu)
//	�߂�l	:����
//	����	:�������������s���Ƌ��ɁA�����ʒu��ݒ肷��B
//=============================================================================
void CScene2DGL::Init(VECTOR3 pos, VECTOR2 size, char *texName)
{
	CRendererGL	*renderer	= CManager::GetRendererGL();


	// �e�평���ݒ�
	SetPos(VECTOR3(pos.x, pos.y, pos.z));
	SetRot(VECTOR3(0.0f, 0.0f, 0.0f));
	m_Size		= size;
	m_fAngle	= atan2f(m_Size.x, m_Size.y);
	m_fLength	= hypotf(m_Size.x, m_Size.y) * 0.5f;

	// �e�N�X�`���Ǎ�
	m_Texture	= renderer->CreateTextureTGA(texName);
}

//=============================================================================
//	�֐���	:Uninit
//	����	:����
//	�߂�l	:����
//	����	:�I���������s���B
//=============================================================================
void CScene2DGL::Uninit(bool isLast)
{
	// �e�N�X�`���폜
	if(m_Texture != NULL)
	{
		if(isLast)
		glDeleteTextures(1, ((GLuint *)m_Texture));
	}
}

//=============================================================================
//	�֐���	:Update
//	����	:����
//	�߂�l	:����
//	����	:�X�V�������s���B
//=============================================================================
void CScene2DGL::Update(void)
{

}

//=============================================================================
//	�֐���	:Draw
//	����	:����
//	�߂�l	:����
//	����	:�`�揈�����s���B
//=============================================================================
void CScene2DGL::Draw(void)
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

		// ���_���ݒ�
		DrawPolygon();
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
CScene2DGL *CScene2DGL::Create(VECTOR3 pos, VECTOR2 size, char *texName)
{
	CScene2DGL *scene2D;

	scene2D = new CScene2DGL;

	scene2D->Init(pos, size, texName);

	return scene2D;
}

//=============================================================================
//	�֐���	:DrawPolygon
//	����	:����
//	�߂�l	:����
//	����	:�|���S���̒��_�����Z�b�g����B
//=============================================================================
void CScene2DGL::DrawPolygon(void)
{
	// �ΐ��̒����v�Z
	m_fLength	= hypotf(m_Size.x, m_Size.y) * 0.5f;

	// �`��p�̃e�N�X�`�����W�E���_���W�ݒ�
	// ���㒸�_
	glTexCoord2d(0.0, 0.0);
	glVertex3f((m_Pos.x - (sinf(m_fAngle + m_Rot.z) * m_fLength)), (m_Pos.y + (cosf(m_fAngle + m_Rot.z + PI) * m_fLength)), 0.0f);

	// �E�㒸�_
	glTexCoord2d(1.0, 0.0);
	glVertex3f((m_Pos.x - (sinf(-m_fAngle + m_Rot.z) * m_fLength)), (m_Pos.y + (cosf(-m_fAngle + m_Rot.z + PI) * m_fLength)), 0.0f);

	// �������_
	glTexCoord2d(0.0, 1.0);
	glVertex3f((m_Pos.x - (sinf(-m_fAngle + m_Rot.z + PI) * m_fLength)), (m_Pos.y + (cosf(-m_fAngle + m_Rot.z) * m_fLength)), 0.0f);

	// �E�����_
	glTexCoord2d(1.0, 1.0);
	glVertex3f((m_Pos.x - (sinf(m_fAngle + m_Rot.z - PI) * m_fLength)), (m_Pos.y + (cosf(m_fAngle + m_Rot.z) * m_fLength)), 0.0f);
}