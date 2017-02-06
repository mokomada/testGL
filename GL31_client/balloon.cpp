/******************************************************************************
*	ファイル：風船
*	作成者  ：庄司茜
*	作成日  ：
******************************************************************************/
/******************************************************************************
*	インクルードファイル
******************************************************************************/

#include "main.h"
#include "manager.h"
#include "rendererGL.h"
#include "balloon.h"
#include "game.h"
#include "sceneModel.h"
#include "effect2D.h"
#include "shadow.h"
#include "textureManager.h"

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
CBalloon::CBalloon(PRIORITY priority, OBJTYPE objType) : CSceneBillboardGL(priority, objType)
{
	m_deleteFlag = false;
	m_u = 0.0f;
}
/******************************************************************************
*	関数名：
*	引数  ：なし
*	戻り値：なし
*	説明  ：デストラクタ
******************************************************************************/
CBalloon::~CBalloon()
{
}

/******************************************************************************
*	関数名：
*	引数  ：
*	戻り値：
*	説明  ：クリエイト
******************************************************************************/
CBalloon * CBalloon::Create( VECTOR3 pos , float r , float g , float b , float a , CSceneGL * parent )
{
	CBalloon *balloon = new CBalloon;
	balloon->Init( pos , r , g , b , a , parent );

	return balloon;
}

/******************************************************************************
*	関数名：
*	引数  ：
*	戻り値：HRESULT
*	説明  ：初期化処理
******************************************************************************/
void CBalloon::Init( VECTOR3 pos , float r , float g , float b , float a , CSceneGL * parent )
{
	CRendererGL	*renderer = CManager::GetRendererGL();

	m_Pos = pos;
	m_r = r;
	m_g = g;
	m_b = b;
	m_Alpha = a;
	m_Size = VECTOR2( 60.0f , 60.0f );
	m_deleteFlag = false;
	m_u = 0.0f;
	m_parent = parent;
	
	// テクスチャ読込
	m_Texture = CTextureManager::GetTexture( TEXTURE_BALLOON );
}

/******************************************************************************
*	関数名：
*	引数  ：なし
*	戻り値：なし
*	説明  ：終了処理
******************************************************************************/
void CBalloon::Uninit( void )
{
}

/******************************************************************************
*	関数名：
*	引数  ：なし
*	戻り値：なし
*	説明  ：更新処理
******************************************************************************/
void CBalloon::Update( void )
{
}

/******************************************************************************
*	関数名：
*	引数  ：なし
*	戻り値：なし
*	説明  ：描画処理
******************************************************************************/
void CBalloon::Draw( void )
{
	// モデルビュー変換行列の操作用
	GLdouble m[16];

	// モデルビューマトリクスの設定
	glMatrixMode(GL_MODELVIEW);
	// マトリクスの退避
	glPushMatrix();

	// ワールドマトリクスの設定
	glTranslatef(m_Pos.x, m_Pos.y, m_Pos.z);
	glRotatef((GLfloat)(m_Rot.z * 180.0 / PI), 0.0f, 0.0f, 1.0f);	// 回転マトリックスの設定、角度は度数法で
	glRotatef((GLfloat)(m_Rot.y * 180.0 / PI), 0.0f, 1.0f, 0.0f);	// 回転マトリックスの設定、角度は度数法で
	glRotatef((GLfloat)(m_Rot.x * 180.0 / PI), 1.0f, 0.0f, 0.0f);	// 回転マトリックスの設定、角度は度数法で
	glScalef(1.0f, 1.0f, 1.0f);

	// 現在のモデルビュー変換行列を取り出す
	glGetDoublev(GL_MODELVIEW_MATRIX, m);

	// 左上 3x3 要素を単位行列にする
	m[0] = m[5] = m[10] = 1.0;
	m[1] = m[2] = m[4] = m[6] = m[8] = m[9] = 0.0;

	// 書き換えた行列を書き戻す
	glLoadMatrixd(m);


	// 描画処理ここから
	glBindTexture(GL_TEXTURE_2D, *m_Texture);
	glEnable(GL_TEXTURE_2D);

	// 深度バッファ設定
	glEnable(GL_DEPTH_TEST);

	// ライティングオフ
	glDisable(GL_LIGHTING);
	glEnable(GL_BLEND);
	glAlphaFunc(GL_GEQUAL, 0.5);
	glEnable(GL_ALPHA_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glDepthMask( FALSE );
	glBegin(GL_TRIANGLE_STRIP);
	{
		// 頂点色設定
		glColor4f( m_r , m_g , m_b , m_Alpha );

		DrawPolygon();
	}
	glEnd();

	// 各種設定引き戻し
	glEnable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_ALPHA_TEST);
	glDisable(GL_BLEND);
	glDepthMask( TRUE );
	// モデルビューマトリックスの設定
	glMatrixMode(GL_MODELVIEW);
	// 保存マトリックスの取り出し
	glPopMatrix();
}

/******************************************************************************
*	関数名：
*	引数  ：なし
*	戻り値：なし
*	説明  ：描画処理
******************************************************************************/
void CBalloon::DrawPolygon( void )
{
	// 描画用の法線・テクスチャ座標・頂点座標設定
	// 左上
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2d( m_u , 0.0f );
	glVertex3f(( - (m_Size.x * 0.5f)), ((m_Size.y * 0.5f)), 0.0f);

	// 右上
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2d( m_u + 0.33f , 0.0f );
	glVertex3f(((m_Size.x * 0.5f)), ( (m_Size.y * 0.5f)), 0.0f);

	// 左下
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2d( m_u , 1.0f );
	glVertex3f(( - (m_Size.x * 0.5f)), ( - (m_Size.y * 0.5f)), 0.0f);

	// 右下
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2d( m_u + 0.33f , 1.0f );
	glVertex3f(( (m_Size.x * 0.5f)), (- (m_Size.y * 0.5f)), 0.0f);
}

/******************************************************************************
*	関数名：void CBalloon::SetColor( float r , float g , float b , float a )
*	引数  ：なし
*	戻り値：なし
*	説明  ：
******************************************************************************/
void CBalloon::SetColor( float r , float g , float b , float a )
{
	m_r = r;
	m_g = g;
	m_b = b;
	m_Alpha = a;
}
