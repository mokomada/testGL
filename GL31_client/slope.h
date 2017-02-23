#ifndef _SLOPE_H_
#define _SLOPE_H_
//=============================================================================
//
//	タイトル	ヘッダファイル(scene3D.cpp)
//	ファイル名	scene3D.h
//	作成者		AT13A284_02 秋田京
//	作成日		2017/02/22
//
//=============================================================================

//=============================================================================
//	クラス定義
//=============================================================================
class CSlope : public CSceneGL
{
public:
	CSlope(bool ifListAdd = true, int priority = 0, OBJTYPE objType = OBJTYPE_NONE);
	~CSlope();

	void	Init(VECTOR3 vec[4], VECTOR3 pos, char *texName);
	void	Uninit(bool isLast);
	void	Update(void);
	void	Draw(void);

	static CSlope	*Create(VECTOR3 vec[4] , VECTOR3 pos, char *texName);
	void	DrawPolygon(void);

private:
	VECTOR3 m_VtxPos[4];		// ポリゴンのサイズ
	int		m_Texture;	// テクスチャ

	MATRIX	m_mtxWorld; // ワールドマトリックス
};

#endif