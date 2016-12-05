//=============================================================================
//
//	�^�C�g��	�X�J�C�{�b�N�X
//	�t�@�C����	skybox.cpp
//	�쐬��		AT13A284_02 �H�c��
//	�쐬��		2016/11/14
//
//=============================================================================

//=============================================================================
//	�C���N���[�h
//=============================================================================

#include "manager.h"
#include "main.h"
#include "rendererGL.h"
#include "game.h"
#include "sceneGL.h"
#include "scene3DGL.h"
#include "skybox.h"


/********************************************
---------------�R���X�g���N�^----------------
*********************************************/
CSkybox::CSkybox(int priority , OBJTYPE objType) : CScene3DGL( priority , objType )
{
}


/********************************************
----------------�f�X�g���N�^-----------------
*********************************************/
CSkybox::~CSkybox()
{

}


/********************************************
-----------------����������------------------
********************************************/
void CSkybox::Init(void)
{
	CRendererGL	*renderer	= CManager::GetRendererGL();


	//�����ʒu
	m_pos.x = 0.0f;
	m_pos.y = 0.0f;
	m_pos.z = 0.0f;

	//�����p�x
	m_rot = 0.0f;
	
	m_Texture = renderer->CreateTextureTGA("./data/TEXTURE/skybox001.png");


}

/********************************************
------------------�X�V����-------------------
********************************************/
void CSkybox::Update(void)
{

}

/********************************************
------------------�`�揈��-------------------
*******************************************/
void CSkybox::Draw(void)
{

	//�v���W�F�N�V�����}�g���b�N�X
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();					//�ۑ�
	
	glEnable(GL_LIGHT0);

	glDisable(GL_CULL_FACE);

	//���[���h�}�g���b�N�X�ݒ�

	glTranslatef(m_pos.x , m_pos.y ,m_pos.z);
	glRotated(m_rot, 0.0, 0.0, 0.0);
	glScalef(1.0f , 1.0f , 1.0f);



	//�|���S���`��
	glBindTexture(GL_TEXTURE_2D , m_Texture);
	glEnable(GL_TEXTURE_2D);

	//���̖�
	glBegin(GL_TRIANGLE_STRIP);

	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2d(0.25f , 0.75f);
	glColor4f( 1.0f, 0.0f, 0.0f, 1.0f );	//�F(RGBA)
	glVertex3f( -50000.0f , -50000.0f , -50000.0f );

	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2d(0.5f , 0.75f);
	glColor4f( 1.0f, 0.0f, 0.0f, 1.0f );
	glVertex3f( 50000.0f , -50000.0f , -50000.0f );

	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2d(0.25f , 1.0f);
	glColor4f( 1.0f, 0.0f, 0.0f, 1.0f );
	glVertex3f(-50000.0f , -50000.0f , 50000.0f );

	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2d(0.5f , 1.0f);
	glColor4f( 1.0f, 0.0f, 0.0f, 1.0f );
	glVertex3f( 50000.0f , -50000.0f , 50000.0f );

	glEnd();

	

	//��O�̖�
	glBegin(GL_TRIANGLE_STRIP);

	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2d(1.0f , 1.0 / 3.0f +  0.001);
	glColor4f( 1.0f, 0.0f, 0.0f, 1.0f );	//�F(RGBA)
	glVertex3f( -50000.0f , 50000.0f , 50000.0f );

	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2d(0.75f , 1.0 / 3.0f + 0.001);
	glColor4f( 1.0f, 0.0f, 0.0f, 1.0f );
	glVertex3f( 50000.0f , 50000.0f , 50000.0f );

	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2d(1.0f , 2.0 / 3.0f -  0.001);
	glColor4f( 1.0f, 0.0f, 0.0f, 1.0f );
	glVertex3f(-50000.0f , -50000.0f , 50000.0f );

	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2d(0.75f , 2.0 / 3.0f - 0.001);
	glColor4f( 1.0f, 0.0f, 0.0f, 1.0f );
	glVertex3f( 50000.0f , -50000.0f , 50000.0f );

	glEnd();

//��̖�
	glBegin(GL_TRIANGLE_STRIP);

	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2d(0.25f , 1.0 / 3.0f);
	glColor4f( 1.0f, 0.0f, 0.0f, 1.0f );	//�F(RGBA)
	glVertex3f( -50000.0f , 50000.0f , -50000.0f );
	

	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2d(0.5f , 1.0 / 3.0f);
	glColor4f( 1.0f, 0.0f, 0.0f, 1.0f );
	glVertex3f( 50000.0f , 50000.0f , -50000.0f );

	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2d(0.25f , 0.0f);
	glColor4f( 1.0f, 0.0f, 0.0f, 1.0f );
	glVertex3f(-50000.0f , 50000.0f , 50000.0f );
	

	glNormal3f(0.0f, 1.0f, 0.01f);
	glTexCoord2d(0.50f , 0.0f);
	glColor4f( 1.0f, 0.0f, 0.0f, 1.0f );
	glVertex3f( 50000.0f , 50000.0f , 50000.0f );
	
	glEnd();

	//���̖�
	glBegin(GL_TRIANGLE_STRIP);

	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2d(0.25f , 1.0 / 3.0f -  0.001);
	glColor4f( 1.0f, 0.0f, 0.0f, 1.0f );	//�F(RGBA)
	glVertex3f( -50000.0f , 50000.0f , -50000.0f );
	
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2d(0.50f , 1.0 / 3.0f -  0.001);
	glColor4f( 1.0f, 0.0f, 0.0f, 1.0f );
	glVertex3f( 50000.0f , 50000.0f , -50000.0f );

	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2d(0.25f , 2.0 / 3.0f +  0.001);
	glColor4f( 1.0f, 0.0f, 0.0f, 1.0f );
	glVertex3f(-50000.0f , -50000.0f , -50000.0f );

	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2d(0.5f , 2.0 / 3.0f -  0.001);
	glColor4f( 1.0f, 0.0f, 0.0f, 1.0f );
	glVertex3f( 50000.0f , -50000.0f , -50000.0f );

	glEnd();

	//�E�̖�
	glBegin(GL_TRIANGLE_STRIP);

	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2d(0.5f , 1.0 / 3.0f +  0.001);
	glColor4f( 1.0f, 0.0f, 0.0f, 1.0f );	//�F(RGBA)
	glVertex3f( 50000.0f , 50000.0f , -50000.0f );

	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2d(0.75f , 1.0 / 3.0f + 0.001);
	glColor4f( 1.0f, 0.0f, 0.0f, 1.0f );
	glVertex3f( 50000.0f , 50000.0f , 50000.0f );

	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2d(0.5f , 2.0 / 3.0f -  0.001);
	glColor4f( 1.0f, 0.0f, 0.0f, 1.0f );
	glVertex3f( 50000.0f , -50000.0f , -50000.0f );

	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2d(0.75f , 2.0 / 3.0f -  0.001);
	glColor4f( 1.0f, 0.0f, 0.0f, 1.0f );
	glVertex3f( 50000.0f , -50000.0f , 50000.0f );

	glEnd();

	//���̖�
	glBegin(GL_TRIANGLE_STRIP);

	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2d(0.25f , 1.0 / 3.0f + 0.001);
	glColor4f( 1.0f, 0.0f, 0.0f, 1.0f );	//�F(RGBA)
	glVertex3f( -50000.0f , 50000.0f , -50000.0f );

	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2d(0.0f , 1.0 / 3.0f + 0.001);
	glColor4f( 1.0f, 0.0f, 0.0f, 1.0f );
	glVertex3f( -50000.0f , 50000.0f , 50000.0f );

	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2d(0.25f , 2.0 / 3.0f - 0.001);
	glColor4f( 1.0f, 0.0f, 0.0f, 1.0f );
	glVertex3f( -50000.0f , -50000.0f , -50000.0f );

	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2d(0.00f , 2.0 / 3.0f - 0.001 );
	glColor4f( 1.0f, 0.0f, 0.0f, 1.0f );
	glVertex3f( -50000.0f , -50000.0f , 50000.0f );

	glEnd();

	glEnable(GL_CULL_FACE);

	glDisable(GL_LIGHT0);

	//���f���r���[�}�g���b�N�X
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();					//���ǂ�
	
}


/********************************************
------------------�I������-------------------
*********************************************/
void CSkybox::Uninit(bool isLast )	
{

}

CSkybox *CSkybox::Create(void)
{
	CSkybox *skybox;		//�C���X�^���X

	//�C���X�^���X�쐬
	skybox = new CSkybox();

	//�������쐬
	skybox -> Init();

	//�C���X�^���X��return
	return skybox;
}