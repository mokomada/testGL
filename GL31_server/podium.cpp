//=============================================================================
//
//	�^�C�g��	�ǎ�
//	�t�@�C����	podium.cpp
//	�쐬��		AT13A284_02 �H�c��
//	�쐬��		2016/2/06
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
#include "sceneModel.h"
#include "square.h"
#include "podium.h"


/********************************************
---------------�R���X�g���N�^----------------
*********************************************/
CPodium::CPodium(bool ifListAdd , int priority , OBJTYPE objType) : CSquare( ifListAdd , priority , objType )
{
}


/********************************************
----------------�f�X�g���N�^-----------------
*********************************************/
CPodium::~CPodium()
{
}


/********************************************
-----------------����������------------------
********************************************/
void CPodium::Init(VECTOR3 pos , VECTOR3 size , char* TexName, VECTOR4 color)
{
	CRendererGL	*renderer	= CManager::GetRendererGL();
	CSquare::Create(VECTOR3(pos.x, pos.y, pos.z), VECTOR3(size.x, size.y, size.z), TexName , color);	//square�̃N���G�C�g��ǂ�ł���

}

CPodium *CPodium::Create(VECTOR3 pos , VECTOR3 size , char* TexName, VECTOR4 color)
{
	CPodium *podium;		//�C���X�^���X

	//�C���X�^���X�쐬
	podium = new CPodium();

	//�������쐬	//�ʒu�A�傫���A�F
	podium -> Init(pos, size, TexName, color);

	//�C���X�^���X��return
	return podium;
}