#ifndef _MODE_H_
#define _MODE_H_
//=============================================================================
//
//	�^�C�g��	�w�b�_�t�@�C��
//	�t�@�C����	mode.h
//	�쐬��		AT13A284_07 �r�c�B��
//	�쐬��		2016/07/12
//
//=============================================================================

//=============================================================================
//	�N���X��`
//=============================================================================
class CMode
{
public:
	virtual void	Init(void)		= 0;
	virtual void	Uninit(void)	= 0;
	virtual void	Update(void)	= 0;
	virtual void	Draw(void)		= 0;
};
#include "title.h"
#include "tutorial.h"
#include "game.h"
#include "result.h"

#endif