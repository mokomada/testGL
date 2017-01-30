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

typedef struct {
	VECTOR3 Pos;
	VECTOR3 Nor;
	VECTOR2 Tex;
}MESH;

//=============================================================================
//	マクロ定義
//=============================================================================
#define	MESHFIELD_TEX_FILENAME000	"./data/TEXTURE/field000.tga"	// テクスチャファイル名

#define	MESHFIELD_VERTICAL		(5)				// メッシュフィールドの縦ブロック数
#define	MESHFIELD_HORIZONTAL	(5)				// メッシュフィールドの横ブロック数
#define	MESHFIELD_WIDTH			(1000.0f)			// ポリゴンの横幅
#define	MESHFIELD_HEIGHT		(1000.0f)			// ポリゴンの縦幅

const int MESHFIELD_POLYGON_NUM	= ((MESHFIELD_HORIZONTAL * 2) * MESHFIELD_VERTICAL + ((MESHFIELD_VERTICAL - 1) * 2));		// ポリゴン数
const int MESHFIELD_INDEX_NUM	= (((MESHFIELD_HORIZONTAL + 1) * 2) * MESHFIELD_VERTICAL + ((MESHFIELD_VERTICAL - 1) * 2));	// 頂点インデックス数

const int MESHFIELD_VERTEX_NUM		= ((MESHFIELD_VERTICAL + 1) * (MESHFIELD_HORIZONTAL + 1));	// 頂点数
const int MESHFIELD_INDEX_STANDARD	= ((MESHFIELD_HORIZONTAL + 1) * 2 + 2);						// インデックスの基準値

//=============================================================================
//	クラス定義
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

	VECTOR2 m_Size;		// ポリゴンのサイズ
	int		m_Texture;	// テクスチャ

	MATRIX	m_mtxWorld; // ワールドマトリックス
	uint	m_Index[MESHFIELD_INDEX_NUM];
	MESH	m_Mesh[MESHFIELD_VERTEX_NUM];
};

#endif