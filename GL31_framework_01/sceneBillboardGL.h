#ifndef _SCENEBILLBOARD_H_
#define _SCENEBILLBOARD_H_
//=============================================================================
//
//	タイトル	ヘッダファイル(sceneBillboard.cpp)
//	ファイル名	sceneBillboard.h
//	作成者		AT13A284_07 池田達哉
//	作成日		2016/05/06
//
//=============================================================================
#include "sceneGL.h"
//=============================================================================
//	マクロ定義
//=============================================================================
#define	BILLBOARD_WIDTH		(100.0f)				// ポリゴンの横幅
#define	BILLBOARD_HEIGHT	(100.0f)				// ポリゴンの縦幅

//=============================================================================
//	クラス定義
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
	VECTOR2 m_Size;		// ポリゴンのサイズ
	uint		m_Texture;	// テクスチャ

	MATRIX	m_mtxWorld;
};

#endif