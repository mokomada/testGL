#ifndef _MESHFIELD_H_
#define _MESHFIELD_H_
//=============================================================================
//
//	�^�C�g��	�w�b�_�t�@�C��(meshfield.cpp)
//	�t�@�C����	meshfield.h
//	�쐬��		AT13A284_07 �r�c�B��
//	�쐬��		2016/05/06
//
//=============================================================================
#include "scene3DGL.h"
//=============================================================================
//	�}�N����`
//=============================================================================
#define	MESHFIELD_TEX_FILENAME000	"./data/TEXTURE/field000.tga"	// �e�N�X�`���t�@�C����

#define	MESHFIELD_WIDTH		(1000.0f)				// �|���S���̉���
#define	MESHFIELD_HEIGHT	(1000.0f)				// �|���S���̏c��

//=============================================================================
//	�N���X��`
//=============================================================================
class CMeshfield : public CScene3DGL
{
public:
	CMeshfield();
	~CMeshfield();

	void	Init(void){}
	void	Init(VECTOR3 pos = VECTOR3(0.0f, 0.0f, 0.0f),
				VECTOR2 size = VECTOR2(MESHFIELD_WIDTH, MESHFIELD_HEIGHT),
				char *texName = MESHFIELD_TEX_FILENAME000);
	void	Uninit(void);
	void	Update(void);
	void	Draw(void);

	static CMeshfield	*Create(VECTOR3 pos = VECTOR3(0.0f, 0.0f, 0.0f),
								VECTOR2 size = VECTOR2(MESHFIELD_WIDTH, MESHFIELD_HEIGHT),
								char *texName = MESHFIELD_TEX_FILENAME000);
	void	DrawPolygon(void);

private:
	VECTOR2 m_Size;		// �|���S���̃T�C�Y
	int		m_Texture;	// �e�N�X�`��

	MATRIX	m_mtxWorld; // ���[���h�}�g���b�N�X
};

#endif