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

typedef struct {
	VECTOR3 Pos;
	VECTOR3 Nor;
	VECTOR2 Tex;
}MESH;

//=============================================================================
//	�}�N����`
//=============================================================================
#define	MESHFIELD_TEX_FILENAME000	"./data/TEXTURE/field000.tga"	// �e�N�X�`���t�@�C����

#define	MESHFIELD_VERTICAL		(5)				// ���b�V���t�B�[���h�̏c�u���b�N��
#define	MESHFIELD_HORIZONTAL	(5)				// ���b�V���t�B�[���h�̉��u���b�N��
#define	MESHFIELD_WIDTH			(1000.0f)			// �|���S���̉���
#define	MESHFIELD_HEIGHT		(1000.0f)			// �|���S���̏c��

const int MESHFIELD_POLYGON_NUM	= ((MESHFIELD_HORIZONTAL * 2) * MESHFIELD_VERTICAL + ((MESHFIELD_VERTICAL - 1) * 2));		// �|���S����
const int MESHFIELD_INDEX_NUM	= (((MESHFIELD_HORIZONTAL + 1) * 2) * MESHFIELD_VERTICAL + ((MESHFIELD_VERTICAL - 1) * 2));	// ���_�C���f�b�N�X��

const int MESHFIELD_VERTEX_NUM		= ((MESHFIELD_VERTICAL + 1) * (MESHFIELD_HORIZONTAL + 1));	// ���_��
const int MESHFIELD_INDEX_STANDARD	= ((MESHFIELD_HORIZONTAL + 1) * 2 + 2);						// �C���f�b�N�X�̊�l

//=============================================================================
//	�N���X��`
//=============================================================================
class CMeshfield : public CScene3DGL
{
public:
	CMeshfield();
	~CMeshfield();

	void	Init(VECTOR3 pos = VECTOR3(0.0f, 0.0f, 0.0f),
				VECTOR2 size = VECTOR2(MESHFIELD_WIDTH, MESHFIELD_HEIGHT),
				char *texName = MESHFIELD_TEX_FILENAME000);
	void	Uninit(void);
	void	Update(void);
	void	Draw(void);

	static CMeshfield	*Create(VECTOR3 pos = VECTOR3(0.0f, 0.0f, 0.0f),
								VECTOR2 size = VECTOR2(MESHFIELD_WIDTH, MESHFIELD_HEIGHT),
								char *texName = MESHFIELD_TEX_FILENAME000);

private:
	void SetMeshData(void);
	void SetMeshIndex(uint *idxBuff, const int horizontal, const int vertical);

	VECTOR2 m_Size;		// �|���S���̃T�C�Y
	int		m_Texture;	// �e�N�X�`��

	MATRIX	m_mtxWorld; // ���[���h�}�g���b�N�X
	uint	m_Index[MESHFIELD_INDEX_NUM];
	MESH	m_Mesh[MESHFIELD_VERTEX_NUM];
};

#endif