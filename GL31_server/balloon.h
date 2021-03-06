/******************************************************************************
*	ファイル：
*	作成者  ：庄司茜
*	作成日  ：
******************************************************************************/
/******************************************************************************
*	ヘッダーファイルの多重インクルード防止
******************************************************************************/

#pragma once

/******************************************************************************
*	インクルードファイル
******************************************************************************/
#include "sceneBillboardGL.h"
/******************************************************************************
*	マクロ定義
******************************************************************************/
/******************************************************************************
*	構造体定義
******************************************************************************/
/******************************************************************************
*	前方宣言
******************************************************************************/
/******************************************************************************
*	クラス
******************************************************************************/
class CBalloon : public CSceneBillboardGL
{
public:
	CBalloon(PRIORITY priority = PRIORITY_BALLOON, OBJTYPE objType = OBJTYPE_NONE);
	~CBalloon();

	static CBalloon * Create( VECTOR3 pos , float r , float g , float b , float a , CSceneGL * parent );

	void Init( VECTOR3 pos , float r , float g , float b , float a , CSceneGL * parent );
	void Uninit( void );
	void Update( void );
	void Draw( void );
	void DrawPolygon( void );

	VECTOR3 GetPos( void ) { return m_Pos; }
	void SetPos( VECTOR3 pos ) { m_Pos = pos; }
	void SetRot( VECTOR3 rot ) { m_Rot = rot; }
	void SetUV( float u ) { m_u += u; }
	void SetDeleteFlag() { m_deleteFlag = true; }
	void SetColor( float r , float g , float b , float a );
private:
	VECTOR3 m_Pos;		// 位置
	VECTOR3 m_Rot;		// 回転角
	VECTOR2 m_Size;		// ポリゴンのサイズ
	float m_r;
	float m_g;
	float m_b;
	float m_Alpha;			//アルファ値
	unsigned int *m_Texture;	// テクスチャ
	float m_u;
	bool m_deleteFlag;
	CSceneGL * m_parent;
};
