//=============================================================================
//
//	�^�C�g��	�V�[���t�@�C��(3D)
//	�t�@�C����	sceneBillboard.cpp
//	�쐬��		AT13A284_07 �r�c�B��
//	�쐬��		2016/04/20
//
//=============================================================================
//=============================================================================
//	�C���N���[�h
//=============================================================================
#include "main.h"
#include "manager.h"
#include "rendererGL.h"
#include "sceneBillboardGL.h"

//=============================================================================
//	�֐���	:CSceneBillboard()
//	����	:����
//	�߂�l	:����
//	����	:�R���X�g���N�^�B
//=============================================================================
CSceneBillboardGL::CSceneBillboardGL(bool ifListAdd, int priority, OBJTYPE objType) : CSceneGL(ifListAdd, priority, objType)
{

	glMatrixIdentity(&m_mtxWorld);
}

//=============================================================================
//	�֐���	:~CSceneBillboard()
//	����	:����
//	�߂�l	:����
//	����	:�f�X�g���N�^�B
//=============================================================================
CSceneBillboardGL::~CSceneBillboardGL()
{

}

//=============================================================================
//	�֐���	:Init
//	����	:VECTOR3 pos(�����ʒu)
//	�߂�l	:����
//	����	:�������������s���Ƌ��ɁA�����ʒu��ݒ肷��B
//=============================================================================
void CSceneBillboardGL::Init(VECTOR3 pos, VECTOR2 size, char *texName)
{
	CRendererGL	*renderer = CManager::GetRendererGL();


	// �e�평����
	SetPos(VECTOR3(pos.x, pos.y, pos.z));
	SetRot(VECTOR3(0.0f, 0.0f, 0.0f));
	m_Size = size;
	
	// �e�N�X�`���Ǎ�
	m_Texture = renderer->CreateTextureTGA(texName);
}

//=============================================================================
//	�֐���	:Uninit
//	����	:����
//	�߂�l	:����
//	����	:�I���������s���B
//=============================================================================
void CSceneBillboardGL::Uninit( bool isLast )
{
	// �e�N�X�`���폜
	if(m_Texture != NULL)
	{
		glDeleteTextures(1, &m_Texture);
	}
}

//=============================================================================
//	�֐���	:Update
//	����	:����
//	�߂�l	:����
//	����	:�X�V�������s���B
//=============================================================================
void CSceneBillboardGL::Update(void)
{

}

//=============================================================================
//	�֐���	:Draw
//	����	:����
//	�߂�l	:����
//	����	:�`�揈�����s���B
//=============================================================================
void CSceneBillboardGL::Draw(void)
{
	// ���f���r���[�ϊ��s��̑���p
	GLdouble m[16];

	// ���f���r���[�}�g���N�X�̐ݒ�
	glMatrixMode(GL_MODELVIEW);
	// �}�g���N�X�̑ޔ�
	glPushMatrix();


	// ���[���h�}�g���N�X�̐ݒ�
	glTranslatef(m_Pos.x, m_Pos.y, m_Pos.z);
	glScalef(1.0f, 1.0f, 1.0f);

	// ���݂̃��f���r���[�ϊ��s������o��
	glGetDoublev(GL_MODELVIEW_MATRIX, m);

	// ���� 3x3 �v�f��P�ʍs��ɂ���
	m[0] = m[5] = m[10] = 1.0;
	m[1] = m[2] = m[4] = m[6] = m[8] = m[9] = 0.0;

	// �����������s��������߂�
	glLoadMatrixd(m);


	// �`�揈����������
	glBindTexture(GL_TEXTURE_2D, m_Texture);
	glEnable(GL_TEXTURE_2D);

	// �[�x�o�b�t�@�ݒ�
	glEnable(GL_DEPTH_TEST);

	// ���C�e�B���O�I�t
	glDisable(GL_LIGHTING);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthMask( FALSE );
	glBegin(GL_TRIANGLE_STRIP);
	{
		// ���_�F�ݒ�
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

		DrawPolygon();
	}
	glEnd();


	// �e��ݒ�����߂�
	glEnable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
	glDepthMask( TRUE );
	// ���f���r���[�}�g���b�N�X�̐ݒ�
	glMatrixMode(GL_MODELVIEW);
	// �ۑ��}�g���b�N�X�̎��o��
	glPopMatrix();
}

//=============================================================================
//	�֐���	:Draw
//	����	:�e�N�X�`���̃A�h���X
//	�߂�l	:����
//	����	:�`�揈�����s���B
//=============================================================================
void CSceneBillboardGL::Draw( uint texture )
{
	// ���f���r���[�ϊ��s��̑���p
	GLdouble m[16];

	// ���f���r���[�}�g���N�X�̐ݒ�
	glMatrixMode(GL_MODELVIEW);
	// �}�g���N�X�̑ޔ�
	glPushMatrix();


	// ���[���h�}�g���N�X�̐ݒ�
	glTranslatef(m_Pos.x, m_Pos.y, m_Pos.z);
	glScalef(1.0f, 1.0f, 1.0f);

	// ���݂̃��f���r���[�ϊ��s������o��
	glGetDoublev(GL_MODELVIEW_MATRIX, m);

	// ���� 3x3 �v�f��P�ʍs��ɂ���
	m[0] = m[5] = m[10] = 1.0;
	m[1] = m[2] = m[4] = m[6] = m[8] = m[9] = 0.0;

	// �����������s��������߂�
	glLoadMatrixd(m);


	// �`�揈����������
	glBindTexture(GL_TEXTURE_2D, texture);
	glEnable(GL_TEXTURE_2D);

	// �[�x�o�b�t�@�ݒ�
	glEnable(GL_DEPTH_TEST);

	// ���C�e�B���O�I�t
	glDisable(GL_LIGHTING);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthMask( FALSE );
	glBegin(GL_TRIANGLE_STRIP);
	{
		// ���_�F�ݒ�
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

		DrawPolygon();
	}
	glEnd();


	// �e��ݒ�����߂�
	glEnable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
	glDepthMask( TRUE );
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
CSceneBillboardGL *CSceneBillboardGL::Create(VECTOR3 pos, VECTOR2 size, char *texName)
{
	CSceneBillboardGL *sceneBillboard;

	sceneBillboard = new CSceneBillboardGL;

	sceneBillboard->Init(pos, size, texName);

	return sceneBillboard;
}

//=============================================================================
//	�֐���	:DrawPolygon
//	����	:����
//	�߂�l	:����
//	����	:�|���S���̒��_�����Z�b�g����B
//=============================================================================
void CSceneBillboardGL::DrawPolygon(void)
{
	// �`��p�̖@���E�e�N�X�`�����W�E���_���W�ݒ�
	// ����
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2d(0.0, 1.0);
	glVertex3f(( - (m_Size.x * 0.5f)), ((m_Size.y * 0.5f)), 0.0f);

	// �E��
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2d(1.0, 1.0);
	glVertex3f(((m_Size.x * 0.5f)), ( (m_Size.y * 0.5f)), 0.0f);

	// ����
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2d(0.0, 0.0);
	glVertex3f(( - (m_Size.x * 0.5f)), ( - (m_Size.y * 0.5f)), 0.0f);

	// �E��
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2d(1.0, 0.0);
	glVertex3f(( (m_Size.x * 0.5f)), (- (m_Size.y * 0.5f)), 0.0f);
}