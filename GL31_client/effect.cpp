/******************************************************************************
*	ファイル：
*	作成者  ：庄司茜
*	作成日  ：
******************************************************************************/
/******************************************************************************
*	インクルードファイル
******************************************************************************/

#include "main.h"
#include "manager.h"
#include "rendererGL.h"
#include "textureManager.h"
#include "effect.h"

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
CEffect::CEffect( bool ifListAdd , int priority , OBJTYPE objType ) : CSceneBillboardGL( ifListAdd , priority , objType )
{
}
/******************************************************************************
*	関数名：
*	引数  ：なし
*	戻り値：なし
*	説明  ：デストラクタ
******************************************************************************/
CEffect::~CEffect()
{
}
/******************************************************************************
*	関数名：
*	引数  ：
*	戻り値：
*	説明  ：クリエイト
******************************************************************************/
CEffect * CEffect::Create( VECTOR3 pos , int playerNumber)
{
	CEffect * effect = new CEffect;
	effect->Init( pos , playerNumber );
	return effect;
}
/******************************************************************************
*	関数名：
*	引数  ：
*	戻り値：HRESULT
*	説明  ：初期化処理
******************************************************************************/
void CEffect::Init( VECTOR3 pos , int playerNumber )
{
	CRendererGL	*renderer = CManager::GetRendererGL();

	// 各種初期化
	SetPos(VECTOR3(pos.x, pos.y, pos.z));
	SetRot(VECTOR3(0.0f, 0.0f, 0.0f));
	m_Size = VECTOR2( 25.0f , 25.0f );

	float r , g , b ,a;

	playerNumber == 0 ? r = 1.0f : r = 0.5f;
	playerNumber == 1 ? b = 1.0f : b = 0.5f;
	playerNumber == 2 ? g = 1.0f : g = 0.5f;
	playerNumber == 3 ? r = 1.0f , g = 1.0f : a = 0;

	m_color = VECTOR4( r , g , b , 1.0f );
	m_Radius = 10.0f;

	// テクスチャ読込
	m_Texture = CTextureManager::GetTexture( TEXTURE_EFFECT );
}

/******************************************************************************
*	関数名：
*	引数  ：なし
*	戻り値：なし
*	説明  ：終了処理
******************************************************************************/
void CEffect::Uninit( void )
{
	CSceneBillboardGL::Uninit();
}
/******************************************************************************
*	関数名：
*	引数  ：なし
*	戻り値：なし
*	説明  ：更新処理
******************************************************************************/
void CEffect::Update( void )
{
	m_color.w -= 0.03f;
	m_Size.x -= 0.4f;
	m_Size.y -= 0.4f;

	if( m_color.w < 0.0f )
	{
		CSceneGL::Release();
	}
}
/******************************************************************************
*	関数名：
*	引数  ：なし
*	戻り値：なし
*	説明  ：描画処理
******************************************************************************/
void CEffect::Draw( void )
{
	// モデルビュー変換行列の操作用
	GLdouble m[16];

	// モデルビューマトリクスの設定
	glMatrixMode(GL_MODELVIEW);
	// マトリクスの退避
	glPushMatrix();


	// ワールドマトリクスの設定
	glTranslatef(m_Pos.x, m_Pos.y, m_Pos.z);
	glScalef(1.0f, 1.0f, 1.0f);

	// 現在のモデルビュー変換行列を取り出す
	glGetDoublev(GL_MODELVIEW_MATRIX, m);

	// 左上 3x3 要素を単位行列にする
	m[0] = m[5] = m[10] = 1.0;
	m[1] = m[2] = m[4] = m[6] = m[8] = m[9] = 0.0;

	// 書き換えた行列を書き戻す
	glLoadMatrixd(m);


	// 描画処理ここから
	glBindTexture( GL_TEXTURE_2D , *m_Texture );
	glEnable(GL_TEXTURE_2D);

	//// 深度バッファ設定
	//glDisable(GL_DEPTH_TEST);
	glEnable(GL_DEPTH_TEST);
	glAlphaFunc(GL_GEQUAL, 0.1 );
	glEnable( GL_ALPHA_TEST );
	glDepthMask( GL_FALSE );
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glEnable(GL_BLEND);


	//// ライティングオフ
	glDisable(GL_LIGHTING);




	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glBegin(GL_TRIANGLE_STRIP);
	{
		// 頂点色設定
		glColor4f( m_color.x , m_color.y , m_color.z , m_color.w );

		DrawPolygon();
	}
	glEnd();

	glDisable(GL_ALPHA_TEST);

	// 各種設定引き戻し
	glEnable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	glDisable( GL_ALPHA_TEST );
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
	glDepthMask( TRUE );
	glDepthMask(GL_TRUE);
	// モデルビューマトリックスの設定
	glMatrixMode(GL_MODELVIEW);
	// 保存マトリックスの取り出し
	glPopMatrix();
}
