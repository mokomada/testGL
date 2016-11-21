#ifndef _DEBUGPROCGL_H_
#define _DEBUGPROCGL_H_
//=============================================================================
//
//	�^�C�g��	�w�b�_�t�@�C��
//	�t�@�C����	debugProcGL.h
//	�쐬��		AT13A284_07 �r�c�B��
//	�쐬��		2016/07/12
//
//=============================================================================
#include "main.h"
#define	DEBUGSTR_MAX	(65535)	// �z����E
#define	FONT_SIZE		(16)	// �t�H���g�T�C�Y
#define	DEBUGPROC_POSX	(10)	// �����\���ʒu��X���W
#define	DEBUGPROC_POSY	(40)	// �����\���ʒu��Y���W
//=============================================================================
//	�N���X��`
//=============================================================================
class CDebugProcGL
{
public:
	static void	Init(void);
	static void	Uninit(void);
	static void	Update(void);
	static void	Draw(void);

	static void DebugProc(wchar_t *format, ...);

private:
	static HDC		m_hDc;
	static HFONT	m_hFont;
	static wchar_t	m_aStrDebug[DEBUGSTR_MAX];	// �f�o�b�O�p������
};

#endif