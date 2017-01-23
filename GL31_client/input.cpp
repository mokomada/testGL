//=============================================================================
//
//	�^�C�g��	�V�[���t�@�C��(3D)
//	�t�@�C����	input.cpp
//	�쐬��		AT13A284_07 �r�c�B��
//	�쐬��		2016/04/20
//
//=============================================================================
//=============================================================================
//	�C���N���[�h
//=============================================================================
#include "input.h"
#include "main.h"

//=============================================================================
//	�ÓI�����o�ϐ�
//=============================================================================
LPDIRECTINPUT8			CInput::m_pInput;				// DirectInput�I�u�W�F�N�g�ւ̃|�C���^
LPDIRECTINPUTDEVICE8	CInput::m_pDevKeyboard;			// ����3D�f�o�C�X(�L�[�{�[�h)�ւ̃|�C���^

BYTE	CInput::m_aKeyState[KEYSTATE_NUM];				// �L�[�{�[�h�̓��͏�񃏁[�N
BYTE	CInput::m_aKeyStateTrigger[KEYSTATE_NUM];		// �L�[�{�[�h�̃g���K���
BYTE	CInput::m_aKeyStateRelease[KEYSTATE_NUM];		// �L�[�{�[�h�̃����[�X���
BYTE	CInput::m_aKeyStateRepeat[KEYSTATE_NUM];		// �L�[�{�[�h�̃��s�[�g���

int		CInput::m_aKeyStateRepeatCount[KEYSTATE_NUM];	// �L�[�{�[�h�̃��s�[�g�J�E���g
int		CInput::m_nRepeatInterval;						// ���s�[�g�Ԋu

//=============================================================================
//	�֐���	:CInput
//	����	:����
//	�߂�l	:����
//	����	:�R���X�g���N�^�B
//=============================================================================
CInput::CInput(void)
{
	m_pInput			= NULL;
	m_pDevKeyboard		= NULL;

	memset(m_aKeyState, 0, sizeof(m_aKeyState));
	memset(m_aKeyStateTrigger, 0, sizeof(m_aKeyStateTrigger));
	memset(m_aKeyStateRelease, 0, sizeof(m_aKeyStateRelease));
	memset(m_aKeyStateRepeat, 0, sizeof(m_aKeyStateRepeat));

	memset(m_aKeyStateRepeatCount, 0, sizeof(m_aKeyStateRepeatCount));
	m_nRepeatInterval	= NULL;
}

//=============================================================================
//	�֐���	:~CInput
//	����	:����
//	�߂�l	:����
//	����	:�f�X�g���N�^�B
//=============================================================================
CInput::~CInput(void)
{

}

//=============================================================================
//	�֐���	:InitInput
//	����	:����
//	�߂�l	:����
//	����	:�������������s���B
//=============================================================================
HRESULT CInput::InitInput(HINSTANCE hInstance, HWND hWnd)
{
	if(m_pInput == NULL)
	{
		if(FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, NULL)))
		{
			MessageBox(hWnd, "�E�B���h�E����܂����H", "�E�B���h�E�̏I��", MB_YESNO);
			return E_FAIL;
		}
	}

	return S_OK;
}

//=============================================================================
//	�֐���	:UnInitInput
//	����	:����
//	�߂�l	:����
//	����	:���͂̏I���������s���B
//=============================================================================
void CInput::UninitInput(void)
{
	if(m_pInput != NULL)
	{
		m_pInput->Release();
		m_pInput = NULL;
	}
}

//=============================================================================
//	�֐���	:UpdateInput
//	����	:����
//	�߂�l	:����
//	����	:���͂̍X�V�������s���B
//=============================================================================
void CInput::UpdateInput(void)
{
	UpdateKeyboard();
}

//=============================================================================
//	�֐���	:InitKeyboard
//	����	:����
//	�߂�l	:����
//	����	:�������������s���B
//=============================================================================
HRESULT CInput::InitKeyboard(HINSTANCE hInstance, HWND hWnd)
{
	if(FAILED(InitInput(hInstance, hWnd)))
	{
		MessageBox(hWnd, "InitInput�Ɏ��s���܂���", "E_FAIL���Ԃ���܂���", MB_OK);
		return E_FAIL;
	}
	if(FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevKeyboard, NULL)))							// 3D�f�o�C�X�̐���
	{
		MessageBox(hWnd, "m_pInput->CreateDevice�Ɏ��s���܂���", "E_FAIL���Ԃ���܂���", MB_OK);
		return E_FAIL;
	}
	if(FAILED(m_pDevKeyboard->SetDataFormat(&c_dfDIKeyboard)))											// �f�[�^�t�H�[�}�b�g�̐ݒ�
	{
		MessageBox(hWnd, "m_pDevKeyboard->SetDataFormat�Ɏ��s���܂���", "E_FAIL���Ԃ���܂���", MB_OK);
		return E_FAIL;
	}
	if(FAILED(m_pDevKeyboard->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))		// �������[�h�̐ݒ�
	{
		MessageBox(hWnd, "m_pDevKeyboard->SetCooperativeLevel�Ɏ��s���܂���", "E_FAIL���Ԃ���܂���", MB_OK);
		return E_FAIL;
	}
	m_pDevKeyboard->Acquire();		// �A�N�Z�X�����擾

	// �L�[�{�[�h�̃��s�[�g�J�E���g������
	for(int nCntInit = 0 ; nCntInit < KEYSTATE_NUM ; nCntInit++)
	{
		m_aKeyStateRepeatCount[nCntInit] = 0;
	}

	// ���s�[�g�Ԋu�̏�����
	m_nRepeatInterval = REPEAT_INTERVAL_NORMAL;

	return S_OK;
}

//=============================================================================
//	�֐���	:UpdateKeyboard
//	����	:����
//	�߂�l	:����
//	����	:���͂̍X�V�������s���B
//=============================================================================
void CInput::UpdateKeyboard(void)
{
	BYTE aKeyState[KEYSTATE_NUM];

	if(SUCCEEDED(m_pDevKeyboard->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for(int nCntKey = 0 ; nCntKey < KEYSTATE_NUM ; nCntKey++)
		{
			// �g���K����
			m_aKeyStateTrigger[nCntKey] = aKeyState[nCntKey] & (m_aKeyState[nCntKey] ^ aKeyState[nCntKey]);
			
			// �����[�X����
			m_aKeyStateRelease[nCntKey] = m_aKeyState[nCntKey] & (m_aKeyState[nCntKey] ^ aKeyState[nCntKey]);

			// ���s�[�g����
			if(aKeyState[nCntKey])
			{
				m_aKeyStateRepeatCount[nCntKey]++;
				if(m_aKeyStateRepeatCount[nCntKey] > REPEAT_TIME)
				{
					// ���s�[�g�Ԋu�ɂ���ă��s�[�g���s��
					if(m_aKeyStateRepeatCount[nCntKey] % m_nRepeatInterval == 0)
					{
						m_aKeyStateRepeat[nCntKey] = aKeyState[nCntKey];
					}
					else
					{
						m_aKeyStateRepeat[nCntKey] = 0;
					}
				}
			}
			else if(m_aKeyStateRelease[nCntKey])
			{
				m_aKeyStateRepeatCount[nCntKey] = 0;
				m_aKeyStateRepeat[nCntKey] = 0;
			}

			m_aKeyState[nCntKey] = aKeyState[nCntKey];
		}
	}
	else
	{
		m_pDevKeyboard->Acquire();
	}
}

//=============================================================================
//	�֐���	:UnInitKeyboard
//	����	:����
//	�߂�l	:����
//	����	:���͂̏I���������s���B
//=============================================================================
void CInput::UninitKeyboard(void)
{
	if(m_pDevKeyboard != NULL)
	{
		m_pDevKeyboard->Unacquire();	// �A�N�Z�X���̊J��
		m_pDevKeyboard->Release();
		m_pDevKeyboard = NULL;
	}

	UninitInput();
}