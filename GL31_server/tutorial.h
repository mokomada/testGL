#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_
//=============================================================================
//
//	�^�C�g��	�w�b�_�t�@�C��
//	�t�@�C����	tutorial.h
//	�쐬��		AT13A284_07 �r�c�B��
//	�쐬��		2016/07/12
//
//=============================================================================
#include "mode.h"
class CScene2DGL;
//=============================================================================
//	�N���X��`
//=============================================================================
class CTutorial : public CMode
{
public:
	CTutorial(){}
	~CTutorial(){}

	void	Init(void);
	void	Uninit(void);
	void	Update(void);
	void	Draw(void);
private:
	CScene2DGL	*m_TutorialBG;
	CScene2DGL	*m_PushEnter;
	float		m_Alpha;
};

#endif