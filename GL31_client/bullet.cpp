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
#include "bullet.h"
#include "game.h"
#include "sceneModel.h"
#include "effect2D.h"
#include "shadow.h"
#include "textureManager.h"
#include "effect.h"
#include "collision.h"
#include "network.h"

/******************************************************************************
*	マクロ定義
******************************************************************************/

#define BULLET_LIFE ( 120 )

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
CBullet::CBullet(bool ifListAdd, int priority, OBJTYPE objType ) : CSceneBillboardGL(ifListAdd, priority , objType)
{
	m_speed = 0;
}
/******************************************************************************
*	関数名：
*	引数  ：なし
*	戻り値：なし
*	説明  ：デストラクタ
******************************************************************************/
CBullet::~CBullet()
{
}

/******************************************************************************
*	関数名：
*	引数  ：
*	戻り値：
*	説明  ：クリエイト
******************************************************************************/
CBullet * CBullet::Create(int playerNum, int bulletNum, VECTOR3 pos , VECTOR3 rot , float speed , int color )
{
	CBullet *bullet = new CBullet();
	bullet->Init(playerNum, bulletNum, pos , rot , speed , color );

	return bullet;
}

/******************************************************************************
*	関数名：
*	引数  ：
*	戻り値：HRESULT
*	説明  ：初期化処理
******************************************************************************/
void CBullet::Init(int playerNum, int bulletNum, VECTOR3 pos , VECTOR3 rot , float speed , int color )
{
	CRendererGL	*renderer = CManager::GetRendererGL();

	// 各種初期化
	SetPos(VECTOR3(pos.x, pos.y, pos.z));
	SetRot(VECTOR3(0.0f, 0.0f, 0.0f));
	m_Size = VECTOR2( 25.0f , 25.0f );
	m_Rot = rot;				//発射角度
	m_speed = speed;			//移動速度
	m_life = BULLET_LIFE;	//弾の寿命
	m_playerNumber = color;
	m_Radius = 10.0f;
	m_PlayerNum = playerNum;
	m_BulletNum = bulletNum;

	// テクスチャ読込
	m_Texture = CTextureManager::GetTexture( TEXTURE_BULLET );

	//影
	m_myShadow = CShadow::Create( m_Pos , 25.0f , 25.0f , this );
}

/******************************************************************************
*	関数名：
*	引数  ：なし
*	戻り値：なし
*	説明  ：終了処理
******************************************************************************/
void CBullet::Uninit( void )
{
	CSceneBillboardGL::Uninit();
}

/******************************************************************************
*	関数名：
*	引数  ：なし
*	戻り値：なし
*	説明  ：更新処理
******************************************************************************/
void CBullet::Update( void )
{
	//エフェクトを生成
	CEffect::Create( m_Pos , m_playerNumber );

	//m_life--;

	m_Pos.x -= -sinf( m_Rot.y ) * m_speed;
	m_Pos.z -= -cosf( m_Rot.y ) * m_speed;

	//当たり判定
	for each ( CSceneGL* list in CSceneGL::GetList(PRIORITY_WALL) )
	{
		if ( CCollision::GetInstance( )->SphereToAabb(m_Pos, m_Radius, list->GetPos( ), &list->GetBox( )) )
		{
			m_life = 0;
		}
	}

	if( m_life <= 0 )	//寿命が尽きたら削除
	{
		if(m_life > -100) CEffect2D::Create( m_Pos , VECTOR3(0.0f,0.0f,0.0f), VECTOR2( 50.0f , 50.0f ) , ETYPE_EXPLODE00 );
		m_myShadow->DeleteFlag( true );	//影の削除フラグをON
		CNetwork::m_BulletInstance[m_PlayerNum][m_BulletNum].Use = false;
		CSceneGL::Release();
	}


}

/******************************************************************************
*	関数名：
*	引数  ：なし
*	戻り値：なし
*	説明  ：描画処理
******************************************************************************/
void CBullet::Draw( void )
{
	CSceneBillboardGL::Draw( *m_Texture );
}
