//=============================================================================
//
//	�^�C�g��	�l�p�`
//	�t�@�C����	podium.cpp
//	�쐬��		AT13A284_02 �H�c��
//	�쐬��		2016/12/07
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
#include "square.h"

#define SQUARE_SIZE_MAX (50.0f)


/********************************************
---------------�R���X�g���N�^----------------
*********************************************/
CSquare::CSquare(bool ifListAdd , int priority , OBJTYPE objType) : CScene3DGL( ifListAdd , priority , objType )
{
}


/********************************************
----------------�f�X�g���N�^-----------------
*********************************************/
CSquare::~CSquare()
{

}


/********************************************
-----------------����������------------------
********************************************/
void CSquare::Init(VECTOR3 pos , VECTOR3 size , char* TexName, VECTOR4 color)
{
	CRendererGL	*renderer	= CManager::GetRendererGL();

	//�����ʒu
	m_Pos = pos;

	

	//�傫�����w��
	m_Square.pos = VECTOR3(size.x * 0.5f, size.y * 0.5f, size.z *0.5f );

	CSquare::m_Box.width = size.x;
	CSquare::m_Box.height = size.y;
	CSquare::m_Box.depth = size.z;




	//�F�̎w��
	m_Color = color;
	//�����p�x
	m_Rot = VECTOR3(0.0f, 0.0f, 0.0f);
	
	m_Texture = renderer->CreateTextureTGA(TexName);
}

/********************************************
------------------�`�揈��-------------------
*******************************************/
void CSquare::Draw(void)
{

	//�v���W�F�N�V�����}�g���b�N�X
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();					//�ۑ�
	
	// �[�x�o�b�t�@�L����
	glEnable(GL_DEPTH_TEST);

	glDisable(GL_LIGHTING);

	glDisable(GL_CULL_FACE);

	//���[���h�}�g���b�N�X�ݒ�

	glTranslatef(m_Pos.x , m_Pos.y ,m_Pos.z);
	glRotatef(( m_Rot.x * 180 / PI ), 1.0f, 0.0f, 0.0f);
	glRotatef(( m_Rot.y * 180 / PI ), 0.0f, 1.0f, 0.0f);
	glRotatef(( m_Rot.z * 180 / PI ), 0.0f, 0.0f, 1.0f);
	glScalef(1.0f , 1.0f , 1.0f);

	//�|���S���`��
	glBindTexture(GL_TEXTURE_2D , m_Texture);
	glEnable(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//���̖�
	glBegin(GL_TRIANGLE_STRIP);

	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2d(0.0f, 0.0f);
	glColor4f( m_Color.x, m_Color.y, m_Color.z, m_Color.w );	//�F(RGBA)
	glVertex3f( -m_Square.pos.x , -m_Square.pos.y , -m_Square.pos.z );

	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2d(m_Square.pos.x / SQ_SIZE_MAX, 0.0f);
	glColor4f( m_Color.x, m_Color.y, m_Color.z, m_Color.w );	//�F(RGBA)
	glVertex3f( m_Square.pos.x , -m_Square.pos.y , -m_Square.pos.z );

	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2d(0.0f, m_Square.pos.z / SQ_SIZE_MAX);
	glColor4f( m_Color.x, m_Color.y, m_Color.z, m_Color.w );	//�F(RGBA)
	glVertex3f(-m_Square.pos.x , -m_Square.pos.y , m_Square.pos.z );

	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2d(m_Square.pos.x / SQ_SIZE_MAX, m_Square.pos.z / SQ_SIZE_MAX);
	glColor4f( m_Color.x, m_Color.y, m_Color.z, m_Color.w );	//�F(RGBA)
	glVertex3f( m_Square.pos.x , -m_Square.pos.y , m_Square.pos.z );

	glEnd();

	

	//��O�̖�
	glBegin(GL_TRIANGLE_STRIP);

	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2d(0.0f, 0.0f);
	glColor4f( m_Color.x, m_Color.y, m_Color.z, m_Color.w );	//�F(RGBA)
	glVertex3f( -m_Square.pos.x , m_Square.pos.y , m_Square.pos.z );

	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2d(m_Square.pos.x / SQ_SIZE_MAX, 0.0f);
	glColor4f( m_Color.x, m_Color.y, m_Color.z, m_Color.w );	//�F(RGBA)
	glVertex3f( m_Square.pos.x , m_Square.pos.y , m_Square.pos.z );

	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2d(0.0f, m_Square.pos.y / SQ_SIZE_MAX);
	glColor4f( m_Color.x, m_Color.y, m_Color.z, m_Color.w );	//�F(RGBA)
	glVertex3f(-m_Square.pos.x , -m_Square.pos.y , m_Square.pos.z );

	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2d(m_Square.pos.x / SQ_SIZE_MAX, m_Square.pos.y / SQ_SIZE_MAX);
	glColor4f( m_Color.x, m_Color.y, m_Color.z, m_Color.w );	//�F(RGBA)
	glVertex3f( m_Square.pos.x , -m_Square.pos.y , m_Square.pos.z );

	glEnd();

//��̖�
	glBegin(GL_TRIANGLE_STRIP);

	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2d(0.0f, 0.0f);
	glColor4f( m_Color.x, m_Color.y, m_Color.z, m_Color.w );	//�F(RGBA)
	glVertex3f( -m_Square.pos.x , m_Square.pos.y , -m_Square.pos.z );
	

	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2d(m_Square.pos.x / SQ_SIZE_MAX, 0.0f);
	glColor4f( m_Color.x, m_Color.y, m_Color.z, m_Color.w );	//�F(RGBA)
	glVertex3f( m_Square.pos.x , m_Square.pos.y , -m_Square.pos.z );

	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2d(0.0f, m_Square.pos.z / SQ_SIZE_MAX);
	glColor4f( m_Color.x, m_Color.y, m_Color.z, m_Color.w );	//�F(RGBA)
	glVertex3f(-m_Square.pos.x , m_Square.pos.y , m_Square.pos.z );
	

	glNormal3f(0.0f, 1.0f, 0.01f);
	glTexCoord2d(m_Square.pos.x / SQ_SIZE_MAX, m_Square.pos.z / SQ_SIZE_MAX);
	glColor4f( m_Color.x, m_Color.y, m_Color.z, m_Color.w );	//�F(RGBA)
	glVertex3f( m_Square.pos.x , m_Square.pos.y , m_Square.pos.z );
	
	glEnd();

	//���̖�
	glBegin(GL_TRIANGLE_STRIP);

	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2d(0.0f, 0.0f);
	glColor4f( m_Color.x, m_Color.y, m_Color.z, m_Color.w );	//�F(RGBA)
	glVertex3f( -m_Square.pos.x , m_Square.pos.y , -m_Square.pos.z );
	
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2d(m_Square.pos.x / SQ_SIZE_MAX, 0.0f);
	glColor4f( m_Color.x, m_Color.y, m_Color.z, m_Color.w );	//�F(RGBA)
	glVertex3f( m_Square.pos.x , m_Square.pos.y , -m_Square.pos.z );

	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2d(0.0f, m_Square.pos.y / SQ_SIZE_MAX);
	glColor4f( m_Color.x, m_Color.y, m_Color.z, m_Color.w );	//�F(RGBA)
	glVertex3f(-m_Square.pos.x , -m_Square.pos.y , -m_Square.pos.z );

	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2d(m_Square.pos.x / SQ_SIZE_MAX, m_Square.pos.y / SQ_SIZE_MAX);
	glColor4f( m_Color.x, m_Color.y, m_Color.z, m_Color.w );	//�F(RGBA)
	glVertex3f( m_Square.pos.x , -m_Square.pos.y , -m_Square.pos.z );

	glEnd();

	//�E�̖�
	glBegin(GL_TRIANGLE_STRIP);

	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2d(0.0f, 0.0f);
	glColor4f( m_Color.x, m_Color.y, m_Color.z, m_Color.w );	//�F(RGBA)
	glVertex3f( m_Square.pos.x , m_Square.pos.y , -m_Square.pos.z );

	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2d(m_Square.pos.z / SQ_SIZE_MAX, 0.0f);
	glColor4f( m_Color.x, m_Color.y, m_Color.z, m_Color.w );	//�F(RGBA)
	glVertex3f( m_Square.pos.x , m_Square.pos.y , m_Square.pos.z );

	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2d(0.0f, m_Square.pos.y / SQ_SIZE_MAX);
	glColor4f( m_Color.x, m_Color.y, m_Color.z, m_Color.w );	//�F(RGBA)
	glVertex3f( m_Square.pos.x , -m_Square.pos.y , -m_Square.pos.z );

	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2d(m_Square.pos.z / SQ_SIZE_MAX, m_Square.pos.y / SQ_SIZE_MAX);
	glColor4f( m_Color.x, m_Color.y, m_Color.z, m_Color.w );	//�F(RGBA)
	glVertex3f( m_Square.pos.x , -m_Square.pos.y , m_Square.pos.z );

	glEnd();

	//���̖�
	glBegin(GL_TRIANGLE_STRIP);

	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2d(0.0f , 0.0f);
	glColor4f( m_Color.x, m_Color.y, m_Color.z, m_Color.w );	//�F(RGBA)
	glVertex3f( -m_Square.pos.x , m_Square.pos.y , -m_Square.pos.z );

	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2d(m_Square.pos.z / SQ_SIZE_MAX, 0.0f);
	glColor4f( m_Color.x, m_Color.y, m_Color.z, m_Color.w );	//�F(RGBA)
	glVertex3f( -m_Square.pos.x , m_Square.pos.y , m_Square.pos.z );

	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2d(0.0f, m_Square.pos.y / SQ_SIZE_MAX);
	glColor4f( m_Color.x, m_Color.y, m_Color.z, m_Color.w );	//�F(RGBA)
	glVertex3f( -m_Square.pos.x , -m_Square.pos.y , -m_Square.pos.z );

	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2d(m_Square.pos.z / SQ_SIZE_MAX, m_Square.pos.y / SQ_SIZE_MAX);
	glColor4f( m_Color.x, m_Color.y, m_Color.z, m_Color.w );	//�F(RGBA)
	glVertex3f( -m_Square.pos.x , -m_Square.pos.y , m_Square.pos.z );

	glEnd();

	glEnable(GL_CULL_FACE);

	glEnable(GL_LIGHTING);

	glDisable(GL_DEPTH_TEST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	//���f���r���[�}�g���b�N�X
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();					//���ǂ�
	
}



/********************************************
------------------�I������-------------------
*********************************************/
void CSquare::Uninit(bool isLast )
{

}


CSquare *CSquare::Create(VECTOR3 pos , VECTOR3 size , char* TexName, VECTOR4 color)
{
	CSquare *square;		//�C���X�^���X

	//�C���X�^���X�쐬
	square = new CSquare();

	//�������쐬	//�ʒu�A�傫���A�F
	square -> Init(pos, size, TexName, color);

	//�C���X�^���X��return
	return square;
}