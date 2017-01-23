#ifndef _SCENE3D_H_
#define _SCENE3D_H_
//=============================================================================
//
//	�^�C�g��	�w�b�_�t�@�C��(scene3D.cpp)
//	�t�@�C����	scene3D.h
//	�쐬��		AT13A284_07 �r�c�B��
//	�쐬��		2016/05/06
//
//=============================================================================
#include "sceneGL.h"
//=============================================================================
//	�}�N����`
//=============================================================================
#define	POLYGON3D_WIDTH		(100.0f)				// �|���S���̉���
#define	POLYGON3D_HEIGHT	(100.0f)				// �|���S���̏c��

//=============================================================================
//	�N���X��`
//=============================================================================
class CScene3DGL : public CSceneGL
{
public:
	CScene3DGL(bool ifListAdd = true, int priority = 2, OBJTYPE objType = OBJTYPE_NONE);
	~CScene3DGL();

	void	Init(void){}
	void	Init(VECTOR3 pos = VECTOR3(0.0f, 0.0f, 0.0f),
				VECTOR2 size = VECTOR2(POLYGON3D_WIDTH, POLYGON3D_HEIGHT),
				char *texName = "./data/TEXTURE/sample_image.tga");
	void	Uninit(bool isLast = false);
	void	Update(void);
	void	Draw(void);

	static CScene3DGL	*Create(VECTOR3 pos = VECTOR3(0.0f, 0.0f, 0.0f),
								VECTOR2 size = VECTOR2(POLYGON3D_WIDTH, POLYGON3D_HEIGHT),
								char *texName = "./data/TEXTURE/sample_image.tga");
	void	DrawPolygon(void);

private:
	VECTOR2 m_Size;		// �|���S���̃T�C�Y
	int		m_Texture;	// �e�N�X�`��

	MATRIX	m_mtxWorld; // ���[���h�}�g���b�N�X
};

#endif