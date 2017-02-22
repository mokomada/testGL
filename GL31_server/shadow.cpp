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
#include "shadow.h"
#include "sceneModel.h"
#include "game.h"
#include "textureManager.h"
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
CShadow::CShadow()
{
}

/******************************************************************************
*	関数名：
*	引数  ：なし
*	戻り値：なし
*	説明  ：デストラクタ
******************************************************************************/
CShadow::~CShadow()
{
}

/******************************************************************************
*	関数名：
*	引数  ：
*	戻り値：
*	説明  ：クリエイト
******************************************************************************/
CShadow * CShadow::Create( VECTOR3 pos , float width , float height , CSceneGL *parent )
{
	CShadow * shadow = new CShadow;
	shadow->Init( pos , width , height , parent );
	return shadow;
}

/******************************************************************************
*	関数名：
*	引数  ：
*	戻り値：HRESULT
*	説明  ：初期化処理
******************************************************************************/
void CShadow::Init( VECTOR3 pos , float width , float height , CSceneGL *parent )
{
	CRendererGL	*renderer	= CManager::GetRendererGL();

	// 各種初期化
	SetPos(VECTOR3(pos.x, 0.1f, pos.z));
	SetRot(VECTOR3(0.0f, 0.0f, 0.0f));
	m_Size = VECTOR2( width , height );
	m_parent = parent;
	m_deleteFlag = false;	//削除するときにｔｒｕｅにする

	// テクスチャ読込
	m_Texture = CTextureManager::GetTexture( TEXTURE_SHADOW );
}

/******************************************************************************
*	関数名：
*	引数  ：なし
*	戻り値：なし
*	説明  ：終了処理
******************************************************************************/
void CShadow::Uninit( bool isLast )
{
	//// テクスチャ削除
	//if(m_Texture != NULL)
	//{
	//	if(isLast)
	//	glDeleteTextures(1, ((GLuint *)m_Texture));
	//}
}

/******************************************************************************
*	関数名：
*	引数  ：なし
*	戻り値：なし
*	説明  ：更新処理
******************************************************************************/
void CShadow::Update( void )
{
	VECTOR3 pos = m_parent->GetPos();
	VECTOR3 rot = m_parent->GetRot();

	SetPos( VECTOR3( pos.x , 0.1f , pos.z ) );
	if( m_parent -> GetObjtype() != OBJTYPE_PLAYER )
	{ 
		SetRot( rot );
	}
	else if( ( (CPlayer*)m_parent) -> GetPlayerLife() > 0 )
	{
		SetRot( rot );
	}

	if( m_deleteFlag )
	{
		CScene3DGL::Release();
	}
}

/******************************************************************************
*	関数名：
*	引数  ：なし
*	戻り値：なし
*	説明  ：描画処理
******************************************************************************/
void CShadow::Draw( void )
{
	// モデルビューマトリクスの設定
	glMatrixMode(GL_MODELVIEW);
	// マトリクスの退避
	glPushMatrix();

	// ワールドマトリクスの設定
	glTranslatef(m_Pos.x, m_Pos.y, m_Pos.z);
	glRotatef((m_Rot.x * 180 / PI), 1.0f, 0.0f, 0.0f);
	glRotatef((m_Rot.y * 180 / PI), 0.0f, 1.0f, 0.0f);
	glRotatef((m_Rot.z * 180 / PI), 0.0f, 0.0f, 1.0f);
	glScalef(1.0f, 1.0f, 1.0f);

	// 描画処理ここから
	glBindTexture(GL_TEXTURE_2D, *m_Texture);
	glEnable(GL_TEXTURE_2D);
	
	// 深度バッファ設定
	glEnable(GL_DEPTH_TEST);

	// ライティングオフ
	glDisable(GL_LIGHTING);
	//アルファブレンド
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glBegin(GL_TRIANGLE_STRIP);
	{
		// 頂点色設定
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

		// 描画用の法線・テクスチャ座標・頂点座標設定
		// 左上
		glNormal3f(0.0f, 1.0f, 0.0f);
		glTexCoord2d(0.0, 1.0);
		glVertex3f(( - (m_Size.x * 0.5f)), 0.0f , -(m_Size.y * 0.5f));

		// 右上
		glNormal3f(0.0f, 1.0f, 0.0f);
		glTexCoord2d(1.0, 1.0);
		glVertex3f(( (m_Size.x * 0.5f)), 0.0f , -(m_Size.y * 0.5f));

		// 左下
		glNormal3f(0.0f, 1.0f, 0.0f);
		glTexCoord2d(0.0, 0.0);
		glVertex3f((- (m_Size.x * 0.5f)), 0.0f ,  (m_Size.y * 0.5f));

		// 右下
		glNormal3f(0.0f, 1.0f, 0.0f);
		glTexCoord2d(1.0, 0.0);
		glVertex3f(( (m_Size.x * 0.5f)), 0.0f, (m_Size.y * 0.5f));
	}
	glEnd();

	// 各種設定引き戻し
	glEnable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
	// モデルビューマトリックスの設定
	glMatrixMode(GL_MODELVIEW);
	// 保存マトリックスの取り出し
	glPopMatrix();
}
