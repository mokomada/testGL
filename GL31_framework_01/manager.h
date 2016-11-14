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

//=============================================================================
//	�}�N����`
//=============================================================================
#define	SCENE_NUM		(2)		// �V�[����

//=============================================================================
//	�O���錾
//=============================================================================
class CMode;
class CInput;
class CDebugProc;
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
	
	static CInput		*GetInput(void){ return m_Input; }
	static CRendererGL	*GetRendererGL(void){ return m_RendererGL; }
	static CCameraGL	*GetCamera(void){ return m_Camera; }

	static void			SetMode(CMode *mode);

private:
	static CMode		*m_Mode;		// ���[�h�̃C���X�^���X
	static CInput		*m_Input;		// ���͂̃C���X�^���X
	static CCameraGL	*m_Camera;		// �J�����̃C���X�^���X
	static CLightGL		*m_Light;		// ���C�g�̃C���X�^���X
//	static CDebugProc	*m_DebugProc;	// �f�o�b�O�v���V�[�W���N���X
	static CRendererGL	*m_RendererGL;	// �����_��(GL)
	
	void	LoadScript(char *fileName);
};

#endif