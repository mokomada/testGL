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
#include "sceneGL.h"
/******************************************************************************
*	マクロ定義
******************************************************************************/
#define LIFE_NUM ( 1 )
/******************************************************************************
*	構造体定義
******************************************************************************/
/******************************************************************************
*	前方宣言
******************************************************************************/

class CBalloon;
class CSceneGL;

/******************************************************************************
*	クラス
******************************************************************************/
class CLife : public CSceneGL
{
public:
	CLife(PRIORITY priority = PRIORITY_BALLOON, OBJTYPE objType = OBJTYPE_NONE);
	~CLife();

	static CLife * Create( VECTOR3 pos , CSceneGL *parent );

	void Init( VECTOR3 pos , CSceneGL *parent );
	void Uninit( void );
	void Update( void );
	void Draw( void );

	void HitDamage( void );	//ダメージを受けたら
	void SetBalloonColor( void );

private:
	CBalloon *m_balloon;
	CSceneGL *m_parent;	//親のアドレス
	int m_life;
};
