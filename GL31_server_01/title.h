#ifndef _TITLE_H_
#define _TITLE_H_
//=============================================================================
//
//	タイトル	ヘッダファイル
//	ファイル名	title.h
//	作成者		AT13A284_07 池田達哉
//	作成日		2016/07/12
//
//=============================================================================
#include "mode.h"
class CScene2DGL;
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
	CScene2DGL	*m_TitleBG;
	CScene2DGL	*m_PushEnter;
	float		m_Alpha;
};

#endif