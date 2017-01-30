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
#include "square.h"
#include "player.h"
#include "sceneBillboardGL.h"
#include "meshfield.h"
#include "score.h"
#include "trickgauge.h"
#include "effect2D.h"
#include "countdown.h"
#include "confetti.h"
#include "wall.h"
#include "textureManager.h"
#include "skybox.h"
//=============================================================================
//	�v���g�^�C�v
//=============================================================================

//=============================================================================
//	�ÓI�����o�ϐ�
//=============================================================================
CMeshfield	*CGame::m_Meshfield;	// ���b�V���t�B�[���h
vector<CPlayer*>	CGame::m_Player;		// �v���C���[�̃C���X�^���X

//=============================================================================
//	�֐���	:Init
//	����	:����
//	�߂�l	:����
//	����	:�������������s���B
//=============================================================================
void CGame::Init(void)
{
	CTextureManager::Init();
	CSkybox::Create();
	m_Meshfield	= CMeshfield::Create();
	// 3D
	CMeshfield::Create(VECTOR3(0.0f, 0.0f, 0.0f));
	m_Player.resize(4);
	m_Player[0] = CPlayer::Create(true, VECTOR3(0.0f, 50.0f, -100.0f));
	m_Player[1] = CPlayer::Create(false, VECTOR3(-100.0f, 50.0f, 0.0f));
	m_Player[2] = CPlayer::Create(false, VECTOR3(100.0f, 50.0f, 0.0f));
	m_Player[3] = CPlayer::Create(false, VECTOR3(0.0f, 50.0f, 100.0f));

	//CSceneBillboardGL::Create(VECTOR3(0.0f, 0.0f, 0.0f), VECTOR2(100.0f, 100.0f), "./data/TEXTURE/�傿��.png");
	CSquare::Create(VECTOR3(0.0f, 0.0f, 0.0f), VECTOR3(50.0f, 100.0f, 50.0f), "./data/TEXTURE/�傿��.png" , VECTOR4(1.0f, 1.0f, 1.0f, 1.0f));

	//CWall::Create(VECTOR3(0.0f, 0.0f, 0.0f), VECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 50.0f, 50.0f, "./data/TEXTURE/�傿��.png");

	// �J�E���g�_�E���B�N������x�ɃJ�E���g�_�E�������Ɣς킵�����߃R�����g�A�E�g�B�^�C�}�[���c��5�b�ɂȂ����炱��Ă�ŉ�����
//	CCountDown::Create(VECTOR3(SCREEN_WIDTH_HALF, SCREEN_HEIGHT * 0.5f, 0.0f), VECTOR2(200.0f, 100.0f), 1) ->SetCountDown( 9 );
	CConfetti::MasterCreate( );

	// 2D
	CScore::Create(VECTOR3(SCREEN_WIDTH_HALF, SCREEN_HEIGHT * 0.1f, 0.0f), VECTOR2(400.0f, 100.0f), 4);
	//CTrickGauge::Create( );

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
	CTextureManager::Uninit();
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