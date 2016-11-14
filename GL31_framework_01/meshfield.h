#ifndef _MESHFIELD_H_
#define _MESHFIELD_H_
//=============================================================================
//
//	タイトル	ヘッダファイル(meshfield.cpp)
//	ファイル名	meshfield.h
//	作成者		AT13A284_07 池田達哉
//	作成日		2016/05/06
//
//=============================================================================
#include "scene3DGL.h"
//=============================================================================
//	マクロ定義
//=============================================================================
#define	MESHFIELD_TEX_FILENAME000	"./data/TEXTURE/field000.tga"	// テクスチャファイル名

#define	MESHFIELD_WIDTH		(1000.0f)				// ポリゴンの横幅
#define	MESHFIELD_HEIGHT	(1000.0f)				// ポリゴンの縦幅

//=============================================================================
//	クラス定義
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
	VECTOR2 m_Size;		// ポリゴンのサイズ
	int		m_Texture;	// テクスチャ

	MATRIX	m_mtxWorld; // ワールドマトリックス
};

#endif