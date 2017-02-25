/*****************************************************************************
タイトル  :弾発射制御処理
ファイル名:bulletgauge.cpp
作成者    :AT-12A-244 24 柴田健人
作成日    :2017/02/01
更新履歴  :
説明	  :
******************************************************************************/

/******************************************************************************
インクルードファイル
*******************************************************************************/
#include "bulletgauge.h"
#include "scene2DGL.h"
#include "rendererGL.h"
#include "manager.h"
#include "game.h"
#include "player.h"
#include "network.h"

/******************************************************************************
マクロ定義
******************************************************************************/
#define GAUGE_WIDTH 40.0f
#define GAUGE_WIDTH2 60.0f
#define GAUGE_WIDTH3 90.0f
#define GAUGE_HEIGHT 200.0f
#define ADDGAUGE 1.0f
#define BULLETGAUGEMAX 100.0f
#define BULLETGAUGEMAX2 200.0f
#define BULLETGAUGEMAX3 300.0f

/******************************************************************************
構造体定義
******************************************************************************/
/******************************************************************************
グローバル変数
******************************************************************************/
/******************************************************************************
プロトタイプ宣言
******************************************************************************/
/******************************************************************************
関数名:CBulletGauge::CBulletGauge(PRIORITY priority, OBJTYPE objType )
引数  :PRIORITY priority, OBJTYPE objType
戻り値:void
説明  :
******************************************************************************/
CBulletGauge::CBulletGauge(bool ifListAdd, int priority, OBJTYPE objType)
{

}

/******************************************************************************
関数名:CBulletGauge::~CTrickGauge( )
引数  :void
戻り値:void
説明  :
******************************************************************************/
CBulletGauge::~CBulletGauge( )
{

}


/******************************************************************************
関数名:void CBulletGauge::Init(void)
引数  :void
戻り値:void
説明  :初期化
******************************************************************************/
void CBulletGauge::Init(void)
{
	CRendererGL	*renderer = CManager::GetRendererGL( );
	CGame *game;
	game = (CGame*)CManager::GetMode( );
	vector<CPlayer*> sceneModel = game->GetPlayer( );
	sceneModel[0]->GetGauge( );
	//テクスチャ指定
	m_Texture[0] = renderer->CreateTextureTGA(".\\data\\TEXTURE\\gauge.png");
	m_Texture[1] = renderer->CreateTextureTGA(".\\data\\TEXTURE\\gauge.png");
	m_Texture[2] = renderer->CreateTextureTGA(".\\data\\TEXTURE\\gauge.png");
	m_color[0] = VECTOR4(1.0f, 0.0f, 0.0f, 1.0f);
	m_color[1] = VECTOR4(0.0f, 1.0f, 0.0f, 1.0f);
	m_color[2] = VECTOR4(0.0f, 0.0f, 1.0f, 1.0f);
	m_StrPos[0] = VECTOR3(0.0f, 0.0f, 0.0f);
	m_StrPos[1] = VECTOR3(GAUGE_WIDTH, 0.0f, 0.0f);
	m_StrPos[2] = VECTOR3(GAUGE_WIDTH + GAUGE_WIDTH, 0.0f, 0.0f);
	m_GaugeWidth[0] = GAUGE_WIDTH;
	m_GaugeWidth[1] = GAUGE_WIDTH;
	m_GaugeWidth[2] = GAUGE_WIDTH;
	m_GaugeMax[0] = BULLETGAUGEMAX3;
	m_GaugeMax[1] = BULLETGAUGEMAX3;
	m_GaugeMax[2] = BULLETGAUGEMAX3;
}

/******************************************************************************
関数名:void CBulletGauge::Updete(void)
引数  :void
戻り値:void
説明  :更新処理
******************************************************************************/
void CBulletGauge::Update(void)
{
	CRendererGL	*renderer = CManager::GetRendererGL( );
	CGame *game;
	game = (CGame*)CManager::GetMode( );
	vector<CPlayer*> sceneModel = game->GetPlayer( );

	for(int i = 0 ; i < PLAYER_NUM ; i++)
	{
		m_Gauge = sceneModel[i]->GetGauge();
		if(m_Gauge <= 0)
		{
			m_Pa[0] = 0.0f;
		}
		else if(m_Gauge >= BULLETGAUGEMAX)
		{
			m_Pa[0] = 1.0f;
		}
		else
		{
			//1以上99以下
			m_Pa[0] = m_Gauge / BULLETGAUGEMAX;
			//m_Pa[0] = BULLETGAUGEMAX / ( (int)m_Gauge % (int)BULLETGAUGEMAX );
		}

		if(m_Gauge <= BULLETGAUGEMAX)
		{
			m_Pa[1] = 0;
		}
		else if(m_Gauge >= BULLETGAUGEMAX2)
		{
			m_Pa[1] = 1.0f;
		}
		else
		{
			//101以上199以下
			m_Pa[1] = m_Gauge / BULLETGAUGEMAX2;
		}

		if(m_Gauge <= BULLETGAUGEMAX2)
		{
			m_Pa[2] = 0;
		}
		else if(m_Gauge >= BULLETGAUGEMAX3)
		{
			m_Pa[2] = 1.0f;
		}
		else
		{
			//201以上299以下
			m_Pa[2] = m_Gauge / BULLETGAUGEMAX3;
		}

		if(m_Gauge < 0)
		{
			m_Gauge = 0;
		}
		if(m_Gauge >= BULLETGAUGEMAX3)
		{
			m_Gauge = BULLETGAUGEMAX3;
		}
		else
		{
			//ゲージ回復
			sceneModel[i]->AddGauge(ADDGAUGE);
		}
	}
}

/******************************************************************************
関数名:CBulletGauge Draw( void )
引数  :void
戻り値:void
説明  :
******************************************************************************/
void CBulletGauge::Draw(void)
{
	// モデルビューマトリックスの設定(投影変換)
	glMatrixMode(GL_PROJECTION);
	// マトリックスの保存
	glPushMatrix( );
	// 変換行列の初期化
	glLoadIdentity( );

	// 平行射影or正射影
	glOrtho(0, (GLdouble)SCREEN_WIDTH, (GLdouble)SCREEN_HEIGHT, 0, -100.0, 100.0);
	// ワールド座標系の表示領域を，ビューポートの大きさに比例させる

	// モデルビューマトリックスの設定
	glMatrixMode(GL_MODELVIEW);
	// マトリックスの保存
	glPushMatrix( );
	// 変換行列の初期化
	glLoadIdentity( );

	for ( int i = 0; i < 3; i++ )
	{
		// 描画処理ここから
		glBindTexture(GL_TEXTURE_2D, m_Texture[i]);
		// テクスチャマッピング有効化
		glEnable(GL_TEXTURE_2D);

		// ブレンド有効化
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		// ライト無効化
		glDisable(GL_LIGHTING);
		// ポリゴン描画
		glBegin(GL_TRIANGLE_STRIP);
		//ポリゴンカラー
		//テクスチャ座標
		glTexCoord2d(0, 0);
		glColor4f(m_color[i].x, m_color[i].y, m_color[i].z, 1.0f);//RGBA
		glVertex3f(m_StrPos[i].x, GAUGE_HEIGHT, 0.0f);//XYZ

													  //ポリゴンカラー
													  //テクスチャ座標
		glTexCoord2d(0, 1);
		glColor4f(m_color[i].x, m_color[i].y, m_color[i].z, 1.0f);//RGBA
										  //ポリゴン座標
		glVertex3f(m_StrPos[i].x, 100.0f, 0.0f);//XYZ

												//テクスチャ座標
		glTexCoord2d(1, 0);
		glColor4f(m_color[i].x, m_color[i].y, m_color[i].z, 1.0f);//RGBA
		glVertex3f(m_StrPos[i].x + GAUGE_WIDTH * m_Pa[i], GAUGE_HEIGHT, 0.0f);//XYZ

																			  //ポリゴンカラー
																			  //テクスチャ座標
		glTexCoord2d(1, 1);
		glColor4f(m_color[i].x, m_color[i].y, m_color[i].z, 1.0f);//RGBA
		glVertex3f(m_StrPos[i].x + GAUGE_WIDTH * m_Pa[i], 100.0f, 0.0f);//XYZ

		glEnd( );
	}

	// テクスチャマッピング無効化
	glDisable(GL_TEXTURE_2D);

	//ブレンド無効化
	glDisable(GL_BLEND);

	// ライト有効化
	glEnable(GL_LIGHTING);

	// モデルビューマトリックスの設定(投影変換)
	glMatrixMode(GL_PROJECTION);
	// 保存マトリックスの取り出し
	glPopMatrix( );

	// モデルビューマトリックスの設定
	glMatrixMode(GL_MODELVIEW);
	// 保存マトリックスの取り出し
	glPopMatrix( );
}

/******************************************************************************
関数名:void CBulletGauge::subtract(float Subtract)
引数  :float Subtract
戻り値:float
説明  :ゲージ減算処理
******************************************************************************/
float CBulletGauge::SubtractGauge(float Subtract)
{
	//現在値が減算値より多い
	if ( m_Gauge > Subtract )
	{
		m_Gauge -= Subtract;
	}
	return m_Gauge;
}

/******************************************************************************
関数名:void CBulletGauge::GetBulletGauge(void)
引数  :void
戻り値:float
説明  :ゲージゲット処理
******************************************************************************/
float CBulletGauge::GetBulletGauge(void)
{
	return m_Gauge;
}
/******************************************************************************
関数名:CBulletGauge CBulletGauge::*Create( void )
引数  :void
戻り値:void
説明  :
******************************************************************************/
CBulletGauge *CBulletGauge::Create(void)
{
	CBulletGauge *BulletGauge;

	BulletGauge = new CBulletGauge;

	BulletGauge->Init( );

	return BulletGauge;
}