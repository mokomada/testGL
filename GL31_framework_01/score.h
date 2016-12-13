#ifndef _SCORE_H_
#define _SCORE_H_
//=============================================================================
//
//	�^�C�g��	�w�b�_�t�@�C��(score.cpp)
//	�t�@�C����	score.h
//	�쐬��		AT13A284_07 �r�c�B��
//	�쐬��		2016/11/14
//
//=============================================================================
#include "number.h"

//=============================================================================
//	�}�N����`
//=============================================================================

//=============================================================================
//	�\����
//=============================================================================

//=============================================================================
//	�N���X��`
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