/******************************************************************************
*	ファイル：弾
*	作成者  ：庄司茜
*	作成日  ：
******************************************************************************/
/******************************************************************************
*	インクルードファイル
******************************************************************************/

#include "main.h"
#include "manager.h"
#include "rendererGL.h"
#include "life.h"
#include "game.h"
#include "sceneModel.h"
#include "effect2D.h"
#include "shadow.h"
#include "textureManager.h"
#include "balloon.h"
#include "player.h"

/******************************************************************************
*	マクロ定義
******************************************************************************/
/******************************************************************************
*	構造体定義
******************************************************************************/
/******************************************************************************
*	プロトタイプ宣言
******************************************************************************/
/******************************************************************************
*	グローバル変数
******************************************************************************/

/******************************************************************************
*	関数名：
*	引数  ：なし
*	戻り値：なし
*	説明  ：コンストラクタ
******************************************************************************/
CLife::CLife(bool ifListAdd, int priority, OBJTYPE objType) : CSceneGL(ifListAdd, priority, objType)
{
}
/******************************************************************************
*	関数名：
*	引数  ：なし
*	戻り値：なし
*	説明  ：デストラクタ
******************************************************************************/
CLife::~CLife()
{
}

/******************************************************************************
*	関数名：
*	引数  ：
*	戻り値：
*	説明  ：クリエイト
******************************************************************************/
CLife * CLife::Create( VECTOR3 pos , CSceneGL *parent , int color )
{
	CLife *bullet = new CLife;
	bullet->Init( pos , parent , color );

	return bullet;
}

/******************************************************************************
*	関数名：
*	引数  ：
*	戻り値：HRESULT
*	説明  ：初期化処理
******************************************************************************/
void CLife::Init( VECTOR3 pos , CSceneGL *parent , int color )
{
	m_parent = parent;
	m_Pos = pos;

	float r , g , b , a;
	
	switch( color )
	{
		case 0:
		{
			r = 1.0f;
			g = 0.0f;
			b = 0.0f;
			a = 1.0f;
			break;
		}
		case 1:
		{
			r = 0.0f;
			g = 0.0f;
			b = 1.0f;
			a = 1.0f;
			break;
		}
		case 2:
		{
			r = 0.0f;
			g = 1.0f;
			b = 0.0f;
			a = 1.0f;
			break;
		}
		case 3:
		{
			r = 1.0f;
			g = 1.0f;
			b = 0.0f;
			a = 1.0f;
			break;
		}
		default:
		{
			r = 1.0f;
			g = 1.0f;
			b = 1.0f;
			a = 1.0f;
			break;
		}
	}

	m_balloon = CBalloon::Create( VECTOR3( pos.x , pos.y + 60.0f , pos.z ) , r , g , b , a  , parent );

	m_life = 3;
}

/******************************************************************************
*	関数名：
*	引数  ：なし
*	戻り値：なし
*	説明  ：終了処理
******************************************************************************/
void CLife::Uninit( void )
{
	m_balloon = NULL;
}

/******************************************************************************
*	関数名：
*	引数  ：なし
*	戻り値：なし
*	説明  ：更新処理
******************************************************************************/
void CLife::Update( void )
{
	CPlayer* player = ( CPlayer* )m_parent;

	//仮の処理
	//if( player->m_ifMinePlayer )
	{
		if (CInput::GetKeyboardTrigger(DIK_O))	
		{
			this->HitDamage();
		}
	}
	/////////////////////////////////////////

	SetBalloonColor();


}

/******************************************************************************
*	関数名：
*	引数  ：なし
*	戻り値：なし
*	説明  ：描画処理
******************************************************************************/
void CLife::Draw( void )
{
	//if( m_balloon != NULL )
	//{
	//	m_balloon->Draw();
	//}
}
/******************************************************************************
*	関数名：void CLife::HitDamage( void )
*	引数  ：なし
*	戻り値：なし
*	説明  ：風船を減らす処理
******************************************************************************/
void CLife::HitDamage( void )
{
	m_life--;

	if( m_life > 0 )
	{
		m_balloon->SetUV( 0.33f );
	}
	else
	{
		m_balloon->SetColor( 1.0f , 1.0f , 1.0f , 0.0f ); 

	}
}

/******************************************************************************
*	関数名：void CLife::SetBalloonColor( void )
*	引数  ：なし
*	戻り値：なし
*	説明  ：風船の色を設定
******************************************************************************/
void CLife::SetBalloonColor( void )
{
	int color = CManager::GetWhatPlayer();
	float r , g , b , a;
	
	switch( color )
	{
		case 0:
		{
			r = 1.0f;
			g = 0.0f;
			b = 0.0f;
			a = 1.0f;
			break;
		}
		case 1:
		{
			r = 0.0f;
			g = 1.0f;
			b = 0.0f;
			a = 1.0f;
			break;
		}
		case 2:
		{
			r = 0.0f;
			g = 0.0f;
			b = 1.0f;
			a = 1.0f;
			break;
		}
		case 3:
		{
			r = 1.0f;
			g = 1.0f;
			b = 0.0f;
			a = 1.0f;
			break;
		}
		default:
		{
			r = 1.0f;
			g = 1.0f;
			b = 1.0f;
			a = 1.0f;
			break;
		}
	}

	if( !m_balloon )
	{
		m_balloon->SetColor( r , g , b , a );
	}

}


/******************************************************************************
*	関数名：int CLife::GetLife( void )
*	引数  ：なし
*	戻り値：m_life
*	説明  ：現在のライフ残量を返す
******************************************************************************/

int CLife::GetLife( void ) {
	return m_life;
}