#ifndef _TITLE_H_
#define _TITLE_H_
//=============================================================================
//
//	タイトル	ヘッダファイル
//	ファイル名	title.h
//	作成者		AT13A284_07 池田達哉( AT13A284_29 塩原聖士 )
//	作成日		2016/07/12
//
//=============================================================================
#include "mode.h"

//種類
#define TITLE_BALLOON_COLOR ( 4 )

//数
#define TITLE_BALLOON ( 15 )

#define TITLE_BALLOON_LEN ( 10 )
class CScene2DGL;
class CScene2DGLAnimation;
//=============================================================================
//	クラス定義
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