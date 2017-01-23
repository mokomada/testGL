//=============================================================================
//
//	�^�C�g��	�J�����t�@�C��
//	�t�@�C����	light.cpp
//	�쐬��		AT13A284_07 �r�c�B��
//	�쐬��		2016/04/26
//
//=============================================================================
//=============================================================================
//	�C���N���[�h
//=============================================================================
#include <vector>
#include "manager.h"
#include "main.h"
#include "mode.h"
#include "fade.h"
#include "rendererGL.h"
#include "network.h"
#include "sceneGL.h"
#include "cameraGL.h"
#include "lightGL.h"
#include "scene2DGL.h"
#include "textureManager.h"

//=============================================================================
//	�ÓI�����o�ϐ�
//=============================================================================
CMode		*CManager::m_Mode;			// ���[�h�N���X
int			CManager::m_ModeState;		// ���[�h���
int			CManager::m_WhatPlayer = -1;
CCameraGL	*CManager::m_Camera;		// �J�����̃C���X�^���X
CRendererGL	*CManager::m_RendererGL;	// �����_��(GL)

//=============================================================================
//	�֐���	:Init
//	����	:����
//	�߂�l	:����
//	����	:�������������s���B
//=============================================================================
void CManager::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	// �����_��������
	m_RendererGL = new CRendererGL();
	m_RendererGL->Init(hWnd);

	// �e��C���X�^���X����
	m_Mode			= new CTutorial();
	m_Camera		= new CCameraGL();

	// ����������
	m_Mode->Init();
	CFade::Init();
	CInput::InitKeyboard(hInstance, hWnd);
	m_Camera->Init();
	CLightGL::Init();
	CSound::Init();
	CNetwork::Init();
	CDebugProcGL::Init();

	// �T�[�o�ɃG���g���[���b�Z�[�W�𑗂�
}

//=============================================================================
//	�֐���	:Uninit
//	����	:����
//	�߂�l	:����
//	����	:�I���������s���B
//=============================================================================
void CManager::Uninit(HWND hWnd)
{
	if(m_RendererGL != NULL)
	{
		m_RendererGL->Uninit(hWnd);
		delete m_RendererGL;
		m_RendererGL = NULL;
	}
	if(m_Camera != NULL)
	{
		m_Camera->Uninit();
		delete m_Camera;
		m_Camera = NULL;
	}

	CSceneGL::DeleteAll();
	CTextureManager::Uninit();
	CSound::Uninit();
	CNetwork::Uninit();
}

//=============================================================================
//	�֐���	:Update
//	����	:����
//	�߂�l	:����
//	����	:�X�V�������s���B
//=============================================================================
void CManager::Update(void)
{
	CInput::UpdateKeyboard();
	m_Camera->Update();
	CLightGL::Update();
	m_RendererGL->Update();

	m_Mode->Update();
	CFade::Update();
	CNetwork::Update();
	CDebugProcGL::Update();
}

//=============================================================================
//	�֐���	:Draw
//	����	:����
//	�߂�l	:����
//	����	:�`�揈�����s���B
//=============================================================================
void CManager::Draw(void)
{
	// �`��V�[�P���X�J�n
	m_RendererGL->Begin();

	// �J�����̐ݒ�
	m_Camera->Set();

	// ���C�g�̐ݒ�
	CLightGL::Set();

	// ���[�h�`��
	m_Mode->Draw();

	// �t�F�[�h�`��
	CFade::Draw();

	CNetwork::Draw();

	// �f�o�b�O�v���V�[�W��
	CDebugProcGL::Draw();
#ifdef _DEBUG
	//int i = 12;	�g�p��
	//CDebugProcGL::DebugProc(L"����%d����\n", i);
	CDebugProcGL::DebugProc("FPS:%d\n", GetFPS());
#endif

	// �`��V�[�P���X�I��
	m_RendererGL->End();
}

//=============================================================================
//	�֐���	:SetMode
//	����	:CMode *mode(�N���X�̃C���X�^���X)
//	�߂�l	:����
//	����	:���[�h��؂�ւ���B
//=============================================================================
void CManager::SetMode(CMode *mode, int modeState)
{
	if((m_Mode != NULL))
	{
		// ���[�h�̏I������
		m_Mode->Uninit();
		// ���[�h�̃C���X�^���X�̍폜
		delete m_Mode;
	}
	if(mode != NULL)
	{
		// ���[�h�̐؂�ւ�
		m_Mode = mode;

		// �ǂ̃��[�h���Z�b�g
		m_ModeState = modeState;

		// ���[�h�̏�������
		m_Mode->Init();
	}
}