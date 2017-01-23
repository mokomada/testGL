#ifndef _COUNTDOWN_H_
#define _COUNTDOWN_H_
//=============================================================================
//
//	�^�C�g��	�w�b�_�t�@�C��(countdown.cpp)
//	�t�@�C����	countdown.h
//	�쐬��		AT13A284_29 �������m
//	�쐬��		2016/11/14
//
//=============================================================================
#include "number.h"

//=============================================================================
//	�}�N����`
//=============================================================================
#define COUNTDOWN_TIMING ( 90 ) //�^�C�~���O
#define COUNTDOWN_ADDSIZE ( 10.0f )//�g��T�C�Y��
#define COUNTDOWN_FACE ( 5 )//�\�����J�n����^�C�~���O
//=============================================================================
//	�\����
//=============================================================================
//=============================================================================
//	�N���X��`
//=============================================================================
class CCountDown : public CScene2DGL
{
public:
	CCountDown(bool ifListAdd = true, int priority = 1, OBJTYPE objtype = OBJTYPE_NONE);
	~CCountDown();
	
	void	Init(VECTOR3 pos, VECTOR2 size, int figure);
	void	Uninit(bool isLast = false);
	void	Update(void);
	void	Draw(void);

	static CCountDown	*Create(VECTOR3 pos, VECTOR2 size, int figure);

	void	SetValue(float value);

	void	SetCountDown( float countdown ){ m_Value = countdown; };//���l���Z�b�g����

	bool	GetStartFlag( void ){ return m_Start; };//�J�n�t���O��n��

protected:
	static int		m_NumFigure;

	CNumber	**m_Number;


private :
	float m_Value;//���l
	int m_Frame;//���Z�^�C�~���O
	bool m_CountDown;//�J�E���g�_�E���J�n�t���O
	bool m_Start;//�J�E���g�_�E�����I���������ǂ���

	VECTOR2 m_BaseSize;//�g��O�T�C�Y
	
};

#endif