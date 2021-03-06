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

#include "scene3DGL.h"

/******************************************************************************
*	マクロ定義
******************************************************************************/
/******************************************************************************
*	構造体定義
******************************************************************************/
/******************************************************************************
*	前方宣言
******************************************************************************/
class CSceneGL;
/******************************************************************************
*	クラス
******************************************************************************/
class CShadow : public CScene3DGL
{
public:
	CShadow();
	~CShadow();

	static CShadow * Create( VECTOR3 pos , float width , float height , CSceneGL *parent );

	void Init( VECTOR3 pos , float width , float height , CSceneGL *parent );
	void Uninit( bool isLast );
	void Update( void );
	void Draw( void );

	void DeleteFlag( bool flag ) { m_deleteFlag = flag; }

private:
	VECTOR2 m_Size;		// ポリゴンのサイズ
	uint		*m_Texture;	// テクスチャ

	MATRIX	m_mtxWorld; // ワールドマトリックス
	CSceneGL *m_parent;	//親のアドレス
	bool m_deleteFlag;	//削除のフラグ

};
