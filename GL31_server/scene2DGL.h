#ifndef _SCENE2D_H_
#define _SCENE2D_H_
//=============================================================================
//
//	�^�C�g��	�w�b�_�t�@�C��(scene2D.cpp)
//	�t�@�C����	scene2D.h
//	�쐬��		AT13A284_07 �r�c�B��
//	�쐬��		2016/04/20
//
//=============================================================================
#include "sceneGL.h"
//=============================================================================
//	�}�N����`
//=============================================================================
#define	POLYGON2D_WIDTH		(100.0f)				// �|���S���̉���
#define	POLYGON2D_HEIGHT	(100.0f)				// �|���S���̏c��

//=============================================================================
//	�N���X��`
//=============================================================================
class CScene2DGL : public CSceneGL
{
public:
	CScene2DGL(bool ifListAdd = true, int priority = 0, OBJTYPE objType = OBJTYPE_NONE);
	~CScene2DGL();

	void	Init(VECTOR3 pos = VECTOR3(0.0f, 0.0f, 0.0f),
				VECTOR2 size = VECTOR2(POLYGON2D_WIDTH, POLYGON2D_HEIGHT),
				char *texName = "./data/TEXTURE/sample_image.tga");
	void	Uninit(bool isLast = false);
	void	Update(void);
	void	Draw(void);

	static CScene2DGL	*Create(VECTOR3 pos = VECTOR3(0.0f, 0.0f, 0.0f),
								VECTOR2 size = VECTOR2(POLYGON2D_WIDTH, POLYGON2D_HEIGHT),
								char *texName = "./data/TEXTURE/sample_image.tga");

	void	DrawPolygon(void);

private:
	VECTOR2 m_Size;		// �|���S���̃T�C�Y
	float	m_fLength;	// �Ίp���̒���
	float	m_fAngle;	// �p�x
	int		m_Texture;	// �e�N�X�`��
};

#endif