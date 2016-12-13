#ifndef _SCORE_H_
#define _SCORE_H_
//=============================================================================
//
//	タイトル	ヘッダファイル(score.cpp)
//	ファイル名	score.h
//	作成者		AT13A284_07 池田達哉
//	作成日		2016/11/14
//
//=============================================================================
#include "number.h"

//=============================================================================
//	マクロ定義
//=============================================================================

//=============================================================================
//	構造体
//=============================================================================

//=============================================================================
//	クラス定義
//=============================================================================
class CScore : public CScene2DGL
{
public:
	CScore(PRIORITY priority = PRIORITY_NONE, OBJTYPE objtype = OBJTYPE_NONE);
	~CScore();
	
	void	Init(VECTOR3 pos, VECTOR2 size, int figure);
	void	Uninit(bool isLast = false);
	void	Update(void);
	void	Draw(void);

	static CScore	*Create(VECTOR3 pos, VECTOR2 size, int figure);

	void	SetValue(float value);

protected:
	static int		m_NumFigure;

	CNumber	**m_Number;
};

#endif