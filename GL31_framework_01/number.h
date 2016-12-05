#ifndef _NUMBER_H_
#define _NUMBER_H_
//=============================================================================
//
//	�^�C�g��	�w�b�_�t�@�C��(number.cpp)
//	�t�@�C����	number.h
//	�쐬��		AT13A284_07 �r�c�B��
//	�쐬��		2016/11/14
//
//=============================================================================
#include "sceneGL.h"
#include "manager.h"
#include "rendererGL.h"

//=============================================================================
//	�}�N����`
//=============================================================================
#define	NUMBER_TEXFILENAME000	"number000.png"	// �|���S���̃t�@�C����

//=============================================================================
//	�}�N����`
//=============================================================================

//=============================================================================
//	�N���X��`
//=============================================================================
class CNumber
{
public:
	CNumber();
	~CNumber();
	
	void	Init(VECTOR3 pos = VECTOR3(0.0f, 0.0f, 0.0f), VECTOR2 size = VECTOR2(0.0f, 0.0f),
				int value = 0, char *texName = "./data/TEXTURE/number000.tga");
	void	Uninit(void);
	void	Update(void);
	void	Draw(void);

	static CNumber	*Create(VECTOR3 pos = VECTOR3(0.0f, 0.0f, 0.0f), VECTOR2 size = VECTOR2(0.0f, 0.0f),
							int value = 0, char *texName = "./data/TEXTURE/number000.tga");
	
	static int GetFigure( int num ); //�������o��
	void	AddSize( VECTOR2 addsize ){ m_Size += addsize; };//�T�C�Y�̉��Z
	void	SetSize( VECTOR2 size ){ m_Size = size; };//�T�C�Y�̐ݒ�

	void	SetNumber(int value = 0);

protected:
	VECTOR3 m_Pos;//���W
	VECTOR3 m_Rot;//�p�x
	VECTOR2 m_Size;		// �|���S���̃T�C�Y
	float	m_fLength;	// �Ίp���̒���
	float	m_fAngle;	// �p�x
	int		m_Texture;	// �e�N�X�`��

	int		m_Number;
};

#endif