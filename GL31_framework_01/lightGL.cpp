//=============================================================================
//
//	�^�C�g��	���C�g
//	�t�@�C����	light.cpp
//	�쐬��		AT13A284_07 �r�c�B��
//	�쐬��		2016/05/26
//
//=============================================================================
//=============================================================================
//	�C���N���[�h
//=============================================================================
#include "lightGL.h"
#include "manager.h"
#include "main.h"
#include "rendererGL.h"

//=============================================================================
//	�֐���	:CLightGL()
//	����	:����
//	�߂�l	:����
//	����	:�R���X�g���N�^�B
//=============================================================================
CLightGL::CLightGL()
{

}

//=============================================================================
//	�֐���	:~CLightGL()
//	����	:����
//	�߂�l	:����
//	����	:�f�X�g���N�^�B
//=============================================================================
CLightGL::~CLightGL()
{

}

//=============================================================================
//	�֐���	:Init
//	����	:����
//	�߂�l	:����
//	����	:�������������s���B
//=============================================================================
void CLightGL::Init(void)
{

}

//=============================================================================
//	�֐���	:Uninit
//	����	:����
//	�߂�l	:����
//	����	:�I���������s���B
//=============================================================================
void CLightGL::Uninit(void)
{

}

//=============================================================================
//	�֐���	:Update
//	����	:����
//	�߂�l	:����
//	����	:�X�V�������s���B
//=============================================================================
void CLightGL::Update(void)
{

}

//=============================================================================
//	�֐���	:Set
//	����	:����
//	�߂�l	:����
//	����	:�J������ݒ肷��B
//=============================================================================
void CLightGL::Set(void)
{
	GLfloat lightPos1[4]	= { 0.0f, 1.0f, 1.0f, 0.0f };
	GLfloat lightCol[4]		= {1.0f, 1.0f, 1.0f, 1.0f};

	glLightfv(GL_LIGHT0, GL_POSITION, lightPos1);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightCol);
}