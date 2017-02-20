/******************************************************************************
*	�t�@�C���F
*	�쐬��  �F���i��
*	�쐬��  �F
******************************************************************************/
/******************************************************************************
*	�C���N���[�h�t�@�C��
******************************************************************************/

#include "main.h"
#include "manager.h"
#include "rendererGL.h"
#include "shadow.h"
#include "sceneModel.h"
#include "game.h"
#include "textureManager.h"
#include "player.h"

/******************************************************************************
*	�}�N����`
******************************************************************************/
/******************************************************************************
*	�\���̒�`
******************************************************************************/
/******************************************************************************
*	�v���g�^�C�v�錾
******************************************************************************/
/******************************************************************************
*	�O���[�o���ϐ�
******************************************************************************/

/******************************************************************************
*	�֐����F
*	����  �F�Ȃ�
*	�߂�l�F�Ȃ�
*	����  �F�R���X�g���N�^
******************************************************************************/
CShadow::CShadow()
{
}

/******************************************************************************
*	�֐����F
*	����  �F�Ȃ�
*	�߂�l�F�Ȃ�
*	����  �F�f�X�g���N�^
******************************************************************************/
CShadow::~CShadow()
{
}

/******************************************************************************
*	�֐����F
*	����  �F
*	�߂�l�F
*	����  �F�N���G�C�g
******************************************************************************/
CShadow * CShadow::Create( VECTOR3 pos , float width , float height , CSceneGL *parent )
{
	CShadow * shadow = new CShadow;
	shadow->Init( pos , width , height , parent );
	return shadow;
}

/******************************************************************************
*	�֐����F
*	����  �F
*	�߂�l�FHRESULT
*	����  �F����������
******************************************************************************/
void CShadow::Init( VECTOR3 pos , float width , float height , CSceneGL *parent )
{
	CRendererGL	*renderer	= CManager::GetRendererGL();

	// �e�평����
	SetPos(VECTOR3(pos.x, 0.1f, pos.z));
	SetRot(VECTOR3(0.0f, 0.0f, 0.0f));
	m_Size = VECTOR2( width , height );
	m_parent = parent;
	m_deleteFlag = false;	//�폜����Ƃ��ɂ��������ɂ���

	// �e�N�X�`���Ǎ�
	m_Texture = CTextureManager::GetTexture( TEXTURE_SHADOW );
}

/******************************************************************************
*	�֐����F
*	����  �F�Ȃ�
*	�߂�l�F�Ȃ�
*	����  �F�I������
******************************************************************************/
void CShadow::Uninit( bool isLast )
{
	//// �e�N�X�`���폜
	//if(m_Texture != NULL)
	//{
	//	if(isLast)
	//	glDeleteTextures(1, ((GLuint *)m_Texture));
	//}
}

/******************************************************************************
*	�֐����F
*	����  �F�Ȃ�
*	�߂�l�F�Ȃ�
*	����  �F�X�V����
******************************************************************************/
void CShadow::Update( void )
{
	VECTOR3 pos = m_parent->GetPos();
	VECTOR3 rot = m_parent->GetRot();

	SetPos( VECTOR3( pos.x , 0.1f , pos.z ) );
	if( m_parent -> GetObjtype() != OBJTYPE_PLAYER )
	{ 
		SetRot( rot );
	}
	else if( ( (CPlayer*)m_parent) -> GetPlayerLife() > 0 )
	{
		SetRot( rot );
	}

	if( m_deleteFlag )
	{
		CScene3DGL::Release();
	}
}

/******************************************************************************
*	�֐����F
*	����  �F�Ȃ�
*	�߂�l�F�Ȃ�
*	����  �F�`�揈��
******************************************************************************/
void CShadow::Draw( void )
{
	// ���f���r���[�}�g���N�X�̐ݒ�
	glMatrixMode(GL_MODELVIEW);
	// �}�g���N�X�̑ޔ�
	glPushMatrix();

	// ���[���h�}�g���N�X�̐ݒ�
	glTranslatef(m_Pos.x, m_Pos.y, m_Pos.z);
	glRotatef((m_Rot.x * 180 / PI), 1.0f, 0.0f, 0.0f);
	glRotatef((m_Rot.y * 180 / PI), 0.0f, 1.0f, 0.0f);
	glRotatef((m_Rot.z * 180 / PI), 0.0f, 0.0f, 1.0f);
	glScalef(1.0f, 1.0f, 1.0f);

	// �`�揈����������
	glBindTexture(GL_TEXTURE_2D, *m_Texture);
	glEnable(GL_TEXTURE_2D);
	
	// �[�x�o�b�t�@�ݒ�
	glEnable(GL_DEPTH_TEST);

	// ���C�e�B���O�I�t
	glDisable(GL_LIGHTING);
	//�A���t�@�u�����h
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glBegin(GL_TRIANGLE_STRIP);
	{
		// ���_�F�ݒ�
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

		// �`��p�̖@���E�e�N�X�`�����W�E���_���W�ݒ�
		// ����
		glNormal3f(0.0f, 1.0f, 0.0f);
		glTexCoord2d(0.0, 1.0);
		glVertex3f(( - (m_Size.x * 0.5f)), 0.0f , -(m_Size.y * 0.5f));

		// �E��
		glNormal3f(0.0f, 1.0f, 0.0f);
		glTexCoord2d(1.0, 1.0);
		glVertex3f(( (m_Size.x * 0.5f)), 0.0f , -(m_Size.y * 0.5f));

		// ����
		glNormal3f(0.0f, 1.0f, 0.0f);
		glTexCoord2d(0.0, 0.0);
		glVertex3f((- (m_Size.x * 0.5f)), 0.0f ,  (m_Size.y * 0.5f));

		// �E��
		glNormal3f(0.0f, 1.0f, 0.0f);
		glTexCoord2d(1.0, 0.0);
		glVertex3f(( (m_Size.x * 0.5f)), 0.0f, (m_Size.y * 0.5f));
	}
	glEnd();

	// �e��ݒ�����߂�
	glEnable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
	// ���f���r���[�}�g���b�N�X�̐ݒ�
	glMatrixMode(GL_MODELVIEW);
	// �ۑ��}�g���b�N�X�̎��o��
	glPopMatrix();
}
