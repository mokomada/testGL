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
//#include "DebugProc.h"
#include "rendererGL.h"
#include "sceneGL.h"
#include "cameraGL.h"
#include "lightGL.h"
#include "scene2DGL.h"

//=============================================================================
//	�ÓI�����o�ϐ�
//=============================================================================
CMode		*CManager::m_Mode;			// ���[�h�N���X
CInput		*CManager::m_Input;			// ���͂̃C���X�^���X
CCameraGL	*CManager::m_Camera;		// �J�����̃C���X�^���X
CLightGL	*CManager::m_Light;			// ���C�g�̃C���X�^���X
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
	m_Mode			= new CTitle();
	m_Input			= new CInput();
	m_Camera		= new CCameraGL();
	m_Light			= new CLightGL();

	// ����������
	m_Mode->Init();
	CFade::Init();
	m_Input->InitKeyboard(hInstance, hWnd);
	m_Camera->Init();
	m_Light->Init();
	CSound::Init();
}

//=============================================================================
//	�֐���	:Uninit
//	����	:����
//	�߂�l	:����
//	����	:�I���������s���B
//=============================================================================
void CManager::Uninit(HWND hWnd)
{
	if(m_Input != NULL)
	{
		m_Input->UninitKeyboard();
		delete m_Input;
		m_Input = NULL;
	}
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

	CSceneGL::DeleteAll(true);
	CSound::Uninit();
}

//=============================================================================
//	�֐���	:Update
//	����	:����
//	�߂�l	:����
//	����	:�X�V�������s���B
//=============================================================================
void CManager::Update(void)
{
	m_Input->UpdateKeyboard();
	m_Camera->Update();
	m_Light->Update();
	m_RendererGL->Update();

	m_Mode->Update();
	CFade::Update();
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
	m_Light->Set();

	// ���[�h�`��
	m_Mode->Draw();

	// �t�F�[�h�`��
	CFade::Draw();

	// �f�o�b�O�v���V�[�W��
	//m_DebugProc->Draw();
#ifdef _DEBUG
	//m_DebugProc->DebugProc("FPS:%d\n", GetFPS());
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
void CManager::SetMode(CMode *mode)
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
		// ���[�h�̏�������
		m_Mode->Init();
	}
}