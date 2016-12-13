//=============================================================================
//
//	�^�C�g��	�Q�[������
//	�t�@�C����	title.cpp
//	�쐬��		AT13A284_07 �r�c�B��
//	�쐬��		2016/07/12
//
//=============================================================================
//=============================================================================
//	�C���N���[�h
//=============================================================================
#include "game.h"
#include <process.h>
#include "manager.h"
#include "input.h"
#include "fade.h"
#include "sceneGL.h"
#include "scene2DGL.h"
#include "scene3DGL.h"
#include "sceneModel.h"
#include "sceneBillboardGL.h"
#include "meshfield.h"
#include "score.h"
#include "trickgauge.h"

//=============================================================================
//	�v���g�^�C�v
//=============================================================================

//=============================================================================
//	�ÓI�����o�ϐ�
//=============================================================================
CMeshfield	*CGame::m_Meshfield;	// ���b�V���t�B�[���h
vector<CSceneModel*>	CGame::m_Player;		// �v���C���[�̃C���X�^���X

//=============================================================================
//	�֐���	:Init
//	����	:����
//	�߂�l	:����
//	����	:�������������s���B
//=============================================================================
void CGame::Init(void)
{
	m_Meshfield	= CMeshfield::Create();
	// 3D
	CMeshfield::Create(VECTOR3(0.0f, 0.0f, 0.0f));
	m_Player.resize(4);
	m_Player[0] = CSceneModel::Create(true, VECTOR3(0.0f, 50.0f, 0.0f));
	m_Player[1] = CSceneModel::Create(false, VECTOR3(-100.0f, 50.0f, 0.0f));
	m_Player[2] = CSceneModel::Create(false, VECTOR3(100.0f, 50.0f, 0.0f));
	m_Player[3] = CSceneModel::Create(false, VECTOR3(0.0f, 50.0f, 100.0f));

	CSceneBillboardGL::Create(VECTOR3(0.0f, 0.0f, 0.0f), VECTOR2(100.0f, 100.0f), "./data/TEXTURE/�傿��.png");

	// 2D
	//CScore::Create(VECTOR3(SCREEN_WIDTH_HALF, SCREEN_HEIGHT * 0.1f, 0.0f), VECTOR2(400.0f, 100.0f), 4);
	CTrickGauge::Create( );

	// BGM�Đ�
	CSound::Play(SOUNDLABEL_BGM000);
}

//=============================================================================
//	�֐���	:Uninit
//	����	:����
//	�߂�l	:����
//	����	:�I���������s���B
//=============================================================================
void CGame::Uninit(void)
{
	CSceneGL::DeleteAll();
}

//=============================================================================
//	�֐���	:Update
//	����	:����
//	�߂�l	:����
//	����	:�X�V�������s���B
//=============================================================================
void CGame::Update(void)
{
	// �V�[���X�V
	CSceneGL::UpdateAll();
	if(KT_ENTER)
	{
		CFade::Start(new CResult, MODE_RESULT, FS_OUT);
	}
}

//=============================================================================
//	�֐���	:Draw
//	����	:����
//	�߂�l	:����
//	����	:�`�揈�����s���B
//=============================================================================
void CGame::Draw(void)
{
	// �V�[���`��
	CSceneGL::DrawAll();
}