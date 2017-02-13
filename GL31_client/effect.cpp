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
#include "textureManager.h"
#include "effect.h"

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
CEffect::CEffect( bool ifListAdd , int priority , OBJTYPE objType ) : CSceneBillboardGL( ifListAdd , priority , objType )
{
}
/******************************************************************************
*	�֐����F
*	����  �F�Ȃ�
*	�߂�l�F�Ȃ�
*	����  �F�f�X�g���N�^
******************************************************************************/
CEffect::~CEffect()
{
}
/******************************************************************************
*	�֐����F
*	����  �F
*	�߂�l�F
*	����  �F�N���G�C�g
******************************************************************************/
CEffect * CEffect::Create( VECTOR3 pos , int playerNumber)
{
	CEffect * effect = new CEffect;
	effect->Init( pos , playerNumber );
	return effect;
}
/******************************************************************************
*	�֐����F
*	����  �F
*	�߂�l�FHRESULT
*	����  �F����������
******************************************************************************/
void CEffect::Init( VECTOR3 pos , int playerNumber )
{
	CRendererGL	*renderer = CManager::GetRendererGL();

	// �e�평����
	SetPos(VECTOR3(pos.x, pos.y, pos.z));
	SetRot(VECTOR3(0.0f, 0.0f, 0.0f));
	m_Size = VECTOR2( 25.0f , 25.0f );

	float r , g , b ,a;

	playerNumber == 0 ? r = 1.0f : r = 0.5f;
	playerNumber == 1 ? b = 1.0f : b = 0.5f;
	playerNumber == 2 ? g = 1.0f : g = 0.5f;
	playerNumber == 3 ? r = 1.0f , g = 1.0f : a = 0;

	m_color = VECTOR4( r , g , b , 1.0f );
	m_Radius = 10.0f;

	// �e�N�X�`���Ǎ�
	m_Texture = CTextureManager::GetTexture( TEXTURE_EFFECT );
}

/******************************************************************************
*	�֐����F
*	����  �F�Ȃ�
*	�߂�l�F�Ȃ�
*	����  �F�I������
******************************************************************************/
void CEffect::Uninit( void )
{
	CSceneBillboardGL::Uninit();
}
/******************************************************************************
*	�֐����F
*	����  �F�Ȃ�
*	�߂�l�F�Ȃ�
*	����  �F�X�V����
******************************************************************************/
void CEffect::Update( void )
{
	m_color.w -= 0.03f;
	m_Size.x -= 0.4f;
	m_Size.y -= 0.4f;

	if( m_color.w < 0.0f )
	{
		CSceneGL::Release();
	}
}
/******************************************************************************
*	�֐����F
*	����  �F�Ȃ�
*	�߂�l�F�Ȃ�
*	����  �F�`�揈��
******************************************************************************/
void CEffect::Draw( void )
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
	glBindTexture( GL_TEXTURE_2D , *m_Texture );
	glEnable(GL_TEXTURE_2D);

	//// �[�x�o�b�t�@�ݒ�
	//glDisable(GL_DEPTH_TEST);
	glEnable(GL_DEPTH_TEST);
	glAlphaFunc(GL_GEQUAL, 0.1 );
	glEnable( GL_ALPHA_TEST );
	glDepthMask( GL_FALSE );
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glEnable(GL_BLEND);


	//// ���C�e�B���O�I�t
	glDisable(GL_LIGHTING);




	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glBegin(GL_TRIANGLE_STRIP);
	{
		// ���_�F�ݒ�
		glColor4f( m_color.x , m_color.y , m_color.z , m_color.w );

		DrawPolygon();
	}
	glEnd();

	glDisable(GL_ALPHA_TEST);

	// �e��ݒ�����߂�
	glEnable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	glDisable( GL_ALPHA_TEST );
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
	glDepthMask( TRUE );
	glDepthMask(GL_TRUE);
	// ���f���r���[�}�g���b�N�X�̐ݒ�
	glMatrixMode(GL_MODELVIEW);
	// �ۑ��}�g���b�N�X�̎��o��
	glPopMatrix();
}
