#ifndef _SCENE3D_H_
#define _SCENE3D_H_
//=============================================================================
//
//	タイトル	ヘッダファイル(scene3D.cpp)
//	ファイル名	scene3D.h
//	作成者		AT13A284_07 池田達哉
//	作成日		2016/05/06
//
//=============================================================================
#include "sceneGL.h"
//=============================================================================
//	マクロ定義
//=============================================================================
#define	POLYGON3D_WIDTH		(100.0f)				// ポリゴンの横幅
#define	POLYGON3D_HEIGHT	(100.0f)				// ポリゴンの縦幅

//=============================================================================
//	クラス定義
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
	VECTOR2 m_Size;		// ポリゴンのサイズ
	int		m_Texture;	// テクスチャ

	MATRIX	m_mtxWorld; // ワールドマトリックス
};

#endif