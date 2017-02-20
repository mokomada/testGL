#ifndef _MANAGER_H_
#define _MANAGER_H_
//=============================================================================
//
//	�^�C�g��	�w�b�_�t�@�C��
//	�t�@�C����	manager.h
//	�쐬��		AT13A284_07 �r�c�B��
//	�쐬��		2016/05/10
//
//=============================================================================
#include "main.h"
#include "sound.h"
#include "debugProcGL.h"

//=============================================================================
//	�}�N����`
//=============================================================================
#define	SCENE_NUM		(2)		// �V�[����

//=============================================================================
//	�O���錾
//=============================================================================
class CMode;
class CRendererGL;
class CSceneGL;
class CCameraGL;
class CLightGL;
class CSceneGL;

//=============================================================================
//	�N���X��`
//=============================================================================
class CManager
{
public:
	static void	Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
	static void	Uninit(HWND hWnd);
	static void	Update(void);
	static void	Draw(void);
	
	static CRendererGL	*GetRendererGL(void){ return m_RendererGL; }
	static CCameraGL	*GetCamera(void){ return m_Camera; }

	static CMode		*GetMode(void) { return m_Mode; }
	static int			GetModeState(void) { return m_ModeState; }
	static void			SetWhatPlayer(int playernumber) { m_WhatPlayer = playernumber; }
	static int			GetWhatPlayer(void) { return m_WhatPlayer; }

	static void			SetMode(CMode *mode, int modeState);

	static int	m_Frame;


private:
	static CMode		*m_Mode;		// ���[�h�̃C���X�^���X
	static CCameraGL	*m_Camera;		// �J�����̃C���X�^���X
	static CRendererGL	*m_RendererGL;	// �����_��(GL)

	static int	m_ModeState;
	static int	m_WhatPlayer;	// ��������P���ǂ���
	
	void	LoadScript(char *fileName);
};

#endif