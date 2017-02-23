#ifndef _TITLE_H_
#define _TITLE_H_
//=============================================================================
//
//	�^�C�g��	�w�b�_�t�@�C��
//	�t�@�C����	title.h
//	�쐬��		AT13A284_07 �r�c�B��( AT13A284_29 �������m )
//	�쐬��		2016/07/12
//
//=============================================================================
#include "mode.h"

//���
#define TITLE_BALLOON_COLOR ( 4 )

//��
#define TITLE_BALLOON ( 15 )

#define TITLE_BALLOON_LEN ( 10 )
class CScene2DGL;
class CScene2DGLAnimation;
//=============================================================================
//	�N���X��`
//=============================================================================
class CTitle : public CMode
{
public:
	CTitle(){}
	~CTitle(){}

	void	Init(void);
	void	Uninit(void);
	void	Update(void);
	void	Draw(void);
private:
	CScene2DGL *m_TitleBG;
	CScene2DGLAnimation	*m_Title;
	CScene2DGLAnimation	*m_PushEnter;
	CScene2DGLAnimation *m_Balloon;
	float		m_Alpha;
	int m_BalloonTexture[ TITLE_BALLOON_COLOR ];
};

#endif