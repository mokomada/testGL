/*****************************************************************************
タイトル  :必殺技処理
ファイル名:trickgauge.cpp
作成者    :AT-12A-244 24 柴田健人
作成日    :2016/11/16
更新履歴  :
説明	  :
******************************************************************************/

/******************************************************************************
インクルードファイル
*******************************************************************************/
#include "trickgauge.h"
#include "scene2DGL.h"
#include "rendererGL.h"
#include "manager.h"

/******************************************************************************
マクロ定義
******************************************************************************/
#define GAUGE_WIDTH 100.0f
#define GAUGE_HEIGHT 200.0f
#define GAUGE_MAX 500.0f

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
関数名:CTrickGauge::CTrickGauge(int priority, OBJTYPE objType )
引数  :int priority, OBJTYPE objType
戻り値:void
説明  :
******************************************************************************/
CTrickGauge::CTrickGauge(int priority, OBJTYPE objType)
{

}

/******************************************************************************
関数名:CTrickGauge::~CTrickGauge( )
引数  :void
戻り値:void
説明  :
******************************************************************************/
CTrickGauge::~CTrickGauge( )
{

}


/******************************************************************************
関数名:void CTrickGauge::Init(void)
引数  :void
戻り値:void
説明  :初期化
******************************************************************************/
void CTrickGauge::Init(void)
{
	CManager	*manager = GetManager( );
	CRendererGL	*renderer = manager->GetRendererGL( );
	//テクスチャ指定
	m_Texture = renderer->CreateTextureTGA(".\\data\\TEXTURE\\title000.tga");
	m_StrPos = VECTOR3( 0.0f,0.0f,0.0f );
	m_GaugeMax = 500.0f;
}

/******************************************************************************
関数名:void CTrickGauge::Updete(void)
引数  :void
戻り値:void
説明  :更新処理
******************************************************************************/
void CTrickGauge::Update(void)
{
	//現在のゲージ
	m_Gauge = 200.0f;
	m_Pa = m_Gauge / m_GaugeMax;
	if ( CInput::GetKeyboardPress(DIK_K) )
	{
		m_Gauge++;
	}
	if ( CInput::GetKeyboardPress(DIK_M) )
	{
		m_Gauge--;
	}
	if ( m_Gauge < 0 )
	{
		m_Gauge = 0;
	}
	if ( m_Gauge > GAUGE_MAX )
	{
		m_Gauge = GAUGE_MAX;
	}
}

/******************************************************************************
関数名:void CTrickGauge::Draw(void)
引数  :void
戻り値:void
説明  :
******************************************************************************/
void CTrickGauge::Draw(void)
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

	// 描画処理ここから
	glBindTexture(GL_TEXTURE_2D, m_Texture);

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
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);//RGBA
	glVertex3f(0, 200.0f, 0.0f);//XYZ

	//ポリゴンカラー
	//テクスチャ座標
	glTexCoord2d(0, 1);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);//RGBA
	//ポリゴン座標
	glVertex3f(0, 100.0f, 0.0f);//XYZ

	//テクスチャ座標
	glTexCoord2d(1, 0);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);//RGBA
	glVertex3f(GAUGE_WIDTH * m_Pa, GAUGE_HEIGHT, 0.0f);//XYZ

	//ポリゴンカラー
	//テクスチャ座標
	glTexCoord2d(1, 1);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);//RGBA
	glVertex3f(GAUGE_WIDTH * m_Pa, GAUGE_HEIGHT, 0.0f);//XYZ



	glEnd( );

	// テクスチャマッピング無効化
	glDisable(GL_TEXTURE_2D);

	// ブレンド無効化
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
関数名:CTrickGauge CTrickGauge::*Create( void )
引数  :void
戻り値:void
説明  :
******************************************************************************/
CTrickGauge *CTrickGauge::Create(void)
{
	CTrickGauge *TrickGauge;

	TrickGauge = new CTrickGauge;

	TrickGauge->Init();

	return TrickGauge;
}