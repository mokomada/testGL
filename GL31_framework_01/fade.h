#ifndef _FADE_H_
#define _FADE_H_
//=============================================================================
//
//	�^�C�g��	�w�b�_�t�@�C��
//	�t�@�C����	fade.h
//	�쐬��		AT13A284_07 �r�c�B��
//	�쐬��		2016/11/14
//
//=============================================================================
#include "rendererGL.h"
class CMode;
class CScene2DGL;

//=============================================================================
//	�}�N����`
//=============================================================================
#define	FADE_CLOSETIME	(60)		// �t�F�[�h�̕��Ă��鎞��
#define	FADE_TIME		(60)		// �t�F�[�h�̎���

//=============================================================================
//	�\����
//=============================================================================
typedef enum{
	FS_NONE = 0,// �������Ă��Ȃ�
	FS_FIRST,	// �����t�F�[�h
	FS_IN,		// �t�F�[�h�C��
	FS_OUT,		// �t�F�[�h�A�E�g
	FS_MAX		// �t�F�[�h��
}FADE_STATE;

//=============================================================================
//	�N���X��`
//=============================================================================
class CFade
{
public:
	static void	Init(void);
	static void	Uninit(void);
	static void	Update(void);
	static void	Draw(void);

	static void			Start(CMode *nextMode, FADE_STATE fadeState = FS_OUT);

private:
	static CMode		*m_NextMode;
	static FADE_STATE	m_FadeState;
	static int			m_FadeTime;		// �t�F�[�h�̎���

	static float		m_Alpha;
};


#endif