#ifndef _SCENEBILLBOARD_H_
#define _SCENEBILLBOARD_H_
//=============================================================================
//
//	�^�C�g��	�w�b�_�t�@�C��(sceneBillboard.cpp)
//	�t�@�C����	sceneBillboard.h
//	�쐬��		AT13A284_07 �r�c�B��
//	�쐬��		2016/05/06
//
//=============================================================================
#include "sceneGL.h"
//=============================================================================
//	�}�N����`
//=============================================================================
#define	BILLBOARD_WIDTH		(100.0f)				// �|���S���̉���
#define	BILLBOARD_HEIGHT	(100.0f)				// �|���S���̏c��

//=============================================================================
//	�N���X��`
//=============================================================================
class CSceneBillboardGL : public CSceneGL
{
public:
	CSceneBillboardGL(int priority = 1, OBJTYPE objType = OBJTYPE_NONE);
	~CSceneBillboardGL();

	void	Init(void){}
	void	Init(VECTOR3 pos = VECTOR3(0.0f, 0.0f, 0.0f),
				VECTOR2 size = VECTOR2(BILLBOARD_WIDTH, BILLBOARD_HEIGHT),
				char *texName = "./data/TEXTURE/sample_image.tga");
	void	Uninit(bool isLast = false);
	void	Update(void);
	void	Draw(void);
	void	Draw( uint texture );

	static CSceneBillboardGL	*Create(VECTOR3 pos = VECTOR3(0.0f, 0.0f, 0.0f),
								VECTOR2 size = VECTOR2(BILLBOARD_WIDTH, BILLBOARD_HEIGHT),
								char *texName = "./data/TEXTURE/sample_image.tga");
	void	DrawPolygon(void);

protected:
	VECTOR2 m_Size;		// �|���S���̃T�C�Y
	uint		m_Texture;	// �e�N�X�`��

	MATRIX	m_mtxWorld;
};

#endif