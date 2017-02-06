/******************************************************************************
*	�t�@�C���F���D
*	�쐬��  �F���i��
*	�쐬��  �F
******************************************************************************/
/******************************************************************************
*	�C���N���[�h�t�@�C��
******************************************************************************/

#include "main.h"
#include "manager.h"
#include "rendererGL.h"
#include "balloon.h"
#include "game.h"
#include "sceneModel.h"
#include "effect2D.h"
#include "shadow.h"
#include "textureManager.h"

/******************************************************************************
*	�}�N����`
******************************************************************************/

#define BULLET_LIFE ( 120 )

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
CBalloon::CBalloon(PRIORITY priority, OBJTYPE objType) : CSceneBillboardGL(priority, objType)
{
	m_deleteFlag = false;
	m_u = 0.0f;
}
/******************************************************************************
*	�֐����F
*	����  �F�Ȃ�
*	�߂�l�F�Ȃ�
*	����  �F�f�X�g���N�^
******************************************************************************/
CBalloon::~CBalloon()
{
}

/******************************************************************************
*	�֐����F
*	����  �F
*	�߂�l�F
*	����  �F�N���G�C�g
******************************************************************************/
CBalloon * CBalloon::Create( VECTOR3 pos , float r , float g , float b , float a , CSceneGL * parent )
{
	CBalloon *balloon = new CBalloon;
	balloon->Init( pos , r , g , b , a , parent );

	return balloon;
}

/******************************************************************************
*	�֐����F
*	����  �F
*	�߂�l�FHRESULT
*	����  �F����������
******************************************************************************/
void CBalloon::Init( VECTOR3 pos , float r , float g , float b , float a , CSceneGL * parent )
{
	CRendererGL	*renderer = CManager::GetRendererGL();

	m_Pos = pos;
	m_r = r;
	m_g = g;
	m_b = b;
	m_Alpha = a;
	m_Size = VECTOR2( 60.0f , 60.0f );
	m_deleteFlag = false;
	m_u = 0.0f;
	m_parent = parent;
	
	// �e�N�X�`���Ǎ�
	m_Texture = CTextureManager::GetTexture( TEXTURE_BALLOON );
}

/******************************************************************************
*	�֐����F
*	����  �F�Ȃ�
*	�߂�l�F�Ȃ�
*	����  �F�I������
******************************************************************************/
void CBalloon::Uninit( void )
{
}

/******************************************************************************
*	�֐����F
*	����  �F�Ȃ�
*	�߂�l�F�Ȃ�
*	����  �F�X�V����
******************************************************************************/
void CBalloon::Update( void )
{
}

/******************************************************************************
*	�֐����F
*	����  �F�Ȃ�
*	�߂�l�F�Ȃ�
*	����  �F�`�揈��
******************************************************************************/
void CBalloon::Draw( void )
{
	// ���f���r���[�ϊ��s��̑���p
	GLdouble m[16];

	// ���f���r���[�}�g���N�X�̐ݒ�
	glMatrixMode(GL_MODELVIEW);
	// �}�g���N�X�̑ޔ�
	glPushMatrix();

	// ���[���h�}�g���N�X�̐ݒ�
	glTranslatef(m_Pos.x, m_Pos.y, m_Pos.z);
	glRotatef((GLfloat)(m_Rot.z * 180.0 / PI), 0.0f, 0.0f, 1.0f);	// ��]�}�g���b�N�X�̐ݒ�A�p�x�͓x���@��
	glRotatef((GLfloat)(m_Rot.y * 180.0 / PI), 0.0f, 1.0f, 0.0f);	// ��]�}�g���b�N�X�̐ݒ�A�p�x�͓x���@��
	glRotatef((GLfloat)(m_Rot.x * 180.0 / PI), 1.0f, 0.0f, 0.0f);	// ��]�}�g���b�N�X�̐ݒ�A�p�x�͓x���@��
	glScalef(1.0f, 1.0f, 1.0f);

	// ���݂̃��f���r���[�ϊ��s������o��
	glGetDoublev(GL_MODELVIEW_MATRIX, m);

	// ���� 3x3 �v�f��P�ʍs��ɂ���
	m[0] = m[5] = m[10] = 1.0;
	m[1] = m[2] = m[4] = m[6] = m[8] = m[9] = 0.0;

	// �����������s��������߂�
	glLoadMatrixd(m);


	// �`�揈����������
	glBindTexture(GL_TEXTURE_2D, *m_Texture);
	glEnable(GL_TEXTURE_2D);

	// �[�x�o�b�t�@�ݒ�
	glEnable(GL_DEPTH_TEST);

	// ���C�e�B���O�I�t
	glDisable(GL_LIGHTING);
	glEnable(GL_BLEND);
	glAlphaFunc(GL_GEQUAL, 0.5);
	glEnable(GL_ALPHA_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glDepthMask( FALSE );
	glBegin(GL_TRIANGLE_STRIP);
	{
		// ���_�F�ݒ�
		glColor4f( m_r , m_g , m_b , m_Alpha );

		DrawPolygon();
	}
	glEnd();

	// �e��ݒ�����߂�
	glEnable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_ALPHA_TEST);
	glDisable(GL_BLEND);
	glDepthMask( TRUE );
	// ���f���r���[�}�g���b�N�X�̐ݒ�
	glMatrixMode(GL_MODELVIEW);
	// �ۑ��}�g���b�N�X�̎��o��
	glPopMatrix();
}

/******************************************************************************
*	�֐����F
*	����  �F�Ȃ�
*	�߂�l�F�Ȃ�
*	����  �F�`�揈��
******************************************************************************/
void CBalloon::DrawPolygon( void )
{
	// �`��p�̖@���E�e�N�X�`�����W�E���_���W�ݒ�
	// ����
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2d( m_u , 0.0f );
	glVertex3f(( - (m_Size.x * 0.5f)), ((m_Size.y * 0.5f)), 0.0f);

	// �E��
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2d( m_u + 0.33f , 0.0f );
	glVertex3f(((m_Size.x * 0.5f)), ( (m_Size.y * 0.5f)), 0.0f);

	// ����
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2d( m_u , 1.0f );
	glVertex3f(( - (m_Size.x * 0.5f)), ( - (m_Size.y * 0.5f)), 0.0f);

	// �E��
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2d( m_u + 0.33f , 1.0f );
	glVertex3f(( (m_Size.x * 0.5f)), (- (m_Size.y * 0.5f)), 0.0f);
}

/******************************************************************************
*	�֐����Fvoid CBalloon::SetColor( float r , float g , float b , float a )
*	����  �F�Ȃ�
*	�߂�l�F�Ȃ�
*	����  �F
******************************************************************************/
void CBalloon::SetColor( float r , float g , float b , float a )
{
	m_r = r;
	m_g = g;
	m_b = b;
	m_Alpha = a;
}
