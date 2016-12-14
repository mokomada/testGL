#ifndef _SCENE2D_H_
#define _SCENE2D_H_
//=============================================================================
//
//	タイトル	ヘッダファイル(scene2D.cpp)
//	ファイル名	scene2D.h
//	作成者		AT13A284_07 池田達哉
//	作成日		2016/04/20
//
//=============================================================================
#include "sceneGL.h"
//=============================================================================
//	マクロ定義
//=============================================================================
#define	POLYGON2D_WIDTH		(100.0f)				// ポリゴンの横幅
#define	POLYGON2D_HEIGHT	(100.0f)				// ポリゴンの縦幅

//=============================================================================
//	クラス定義
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
	VECTOR2 m_Size;		// ポリゴンのサイズ
	float	m_fLength;	// 対角線の長さ
	float	m_fAngle;	// 角度
	int		m_Texture;	// テクスチャ
};

#endif