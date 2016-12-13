/******************************************************************************
*	ファイル：bullet.h
*	作成者  ：庄司茜
*	作成日  ：2016/11/14
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

class CShadow;

/******************************************************************************
*	クラス
******************************************************************************/
class CBullet : public CSceneBillboardGL
{
public:
	CBullet(PRIORITY priority = PRIORITY_BULLET, OBJTYPE objType = OBJTYPE_BULLET);
	~CBullet();

	static CBullet * Create( VECTOR3 pos , VECTOR3 rot , float speed );

	void Init( VECTOR3 pos , VECTOR3 rot , float speed );
	void Uninit( void );
	void Update( void );
	void Draw( void );

private:
	int m_life;		//弾の寿命
	float m_speed;
	CShadow *m_myShadow;	//自分の影
	unsigned int		*m_Texture;	// テクスチャ
};
