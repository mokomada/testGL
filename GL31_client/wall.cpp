/*****************************************************************************
�^�C�g��	��
�t�@�C����	wall.cpp
�쐬��		AT-13A-284 31 �ēc���l
�쐬��		2016/11/28
�X�V����
����		�t�B�[���h�̕ǂł�
���
******************************************************************************/

/******************************************************************************
�C���N���[�h�t�@�C��
*******************************************************************************/
#include "wall.h"
#include "manager.h"
#include "rendererGL.h"
#include "sceneGL.h"
#include "game.h"

/******************************************************************************
�}�N����`
******************************************************************************/

/******************************************************************************
�\���̒�`
******************************************************************************/

/******************************************************************************
�O���[�o���ϐ�
******************************************************************************/
/******************************************************************************
�v���g�^�C�v�錾
******************************************************************************/
/******************************************************************************
�֐���:CWall::CWall( )
����  :void
�߂�l:void
����  :
******************************************************************************/
CWall::CWall(bool ifListAdd, int priority, OBJTYPE objType) : CScene3DGL(ifListAdd, priority, objType)
{

}

/******************************************************************************
�֐���:CWall::~CWall( )
����  :void
�߂�l:void
����  :
******************************************************************************/
CWall::~CWall( )
{

}

/******************************************************************************
�֐���: void CWall::Init()
����  :void
�߂�l:void
����  :������
******************************************************************************/
void CWall::Init(char *texName)
{
	CRendererGL	*renderer = CManager::GetRendererGL( );
	m_Texture = renderer->CreateTextureTGA("./data/TEXTURE/test.png");
	CScene3DGL::Init(m_Pos, VECTOR2(m_Box.width, m_Box.height),"renderer->CreateTextureTGA(texName);");

}

/******************************************************************************
�֐���: void CWall::Updata()
����  :void
�߂�l:void
����  :�X�V
******************************************************************************/
void CWall::Updete( )
{

}

/******************************************************************************
�֐���:CWall *Create()
����  :void
�߂�l:void
����  :
******************************************************************************/
void CWall::Draw()
{
	// ���f���r���[�}�g���N�X�̐ݒ�
	glMatrixMode(GL_MODELVIEW);
	// �}�g���N�X�̑ޔ�
	glPushMatrix( );

	// ���[���h�}�g���N�X�̐ݒ�
	glTranslatef(m_Pos.x, m_Pos.y, m_Pos.z);
	glRotatef(( m_Rot.x * 180 / PI ), 1.0f, 0.0f, 0.0f);
	glRotatef(( m_Rot.y * 180 / PI ), 0.0f, 1.0f, 0.0f);
	glRotatef(( m_Rot.z * 180 / PI ), 0.0f, 0.0f, 1.0f);
	glScalef(1.0f, 1.0f, 1.0f);

	// �`�揈����������
	glBindTexture(GL_TEXTURE_2D, m_Texture);
	glEnable(GL_TEXTURE_2D);

	// �[�x�o�b�t�@�ݒ�
	glEnable(GL_DEPTH_TEST);

	// ���C�e�B���O�I�t
	glDisable(GL_LIGHTING);

	//���ʕ`��
	glDisable(GL_CULL_FACE);

	glBegin(GL_TRIANGLE_STRIP);
	{
		// ���_�F�ݒ�
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

		DrawPolygon( );
	}
	glEnd( );

	// �e��ݒ�����߂�
	glEnable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	// ���f���r���[�}�g���b�N�X�̐ݒ�
	glMatrixMode(GL_MODELVIEW);
	// �ۑ��}�g���b�N�X�̎��o��
	glPopMatrix( );
}
//=============================================================================
//	�֐���	:Create
//	����	:����
//	�߂�l	:����
//	����	:�����������s���B
//=============================================================================
CWall *CWall::Create(VECTOR3 pos, VECTOR3 rot, float width, float height,float depth, char *texName)
{
	CWall *wall;
	wall = new CWall;
	wall->m_Pos = pos;
	wall->m_Rot = rot;
	wall->m_Box.depth = depth;
	wall->m_Box.height = height;
	wall->m_Box.width = width;
	wall->Init(texName);
	return wall;
}