/*****************************************************************************
タイトル	壁
ファイル名	wall.cpp
作成者		AT-13A-284 31 柴田健人
作成日		2016/11/28
更新履歴
説明		フィールドの壁です
解説
******************************************************************************/

/******************************************************************************
インクルードファイル
*******************************************************************************/
#include "wall.h"
#include "manager.h"
#include "rendererGL.h"
#include "game.h"

/******************************************************************************
マクロ定義
******************************************************************************/

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
関数名:CWall::CWall( )
引数  :void
戻り値:void
説明  :
******************************************************************************/
CWall::CWall( )
{

}

/******************************************************************************
関数名:CWall::~CWall( )
引数  :void
戻り値:void
説明  :
******************************************************************************/
CWall::~CWall( )
{

}

/******************************************************************************
関数名: void CWall::Init()
引数  :void
戻り値:void
説明  :初期化
******************************************************************************/
void CWall::Init(char *texName)
{
	CRendererGL	*renderer = CManager::GetRendererGL( );
	m_Texture = renderer->CreateTextureTGA("./data/TEXTURE/主ちゃ.png");
	CScene3DGL::Init(m_Pos, VECTOR2(m_WallBox.width, m_WallBox.height),"renderer->CreateTextureTGA(texName);");

}

/******************************************************************************
関数名: void CWall::Updata()
引数  :void
戻り値:void
説明  :更新
******************************************************************************/
void CWall::Updete( )
{

}

/******************************************************************************
関数名:CWall *Create()
引数  :void
戻り値:void
説明  :
******************************************************************************/
void CWall::Draw()
{
	// モデルビューマトリクスの設定
	glMatrixMode(GL_MODELVIEW);
	// マトリクスの退避
	glPushMatrix( );

	// ワールドマトリクスの設定
	glTranslatef(m_Pos.x, m_Pos.y, m_Pos.z);
	glRotatef(( m_Rot.x * 180 / PI ), 1.0f, 0.0f, 0.0f);
	glRotatef(( m_Rot.y * 180 / PI ), 0.0f, 1.0f, 0.0f);
	glRotatef(( m_Rot.z * 180 / PI ), 0.0f, 0.0f, 1.0f);
	glScalef(1.0f, 1.0f, 1.0f);

	// 描画処理ここから
	glBindTexture(GL_TEXTURE_2D, m_Texture);
	glEnable(GL_TEXTURE_2D);

	// 深度バッファ設定
	glEnable(GL_DEPTH_TEST);

	// ライティングオフ
	glDisable(GL_LIGHTING);

	//両面描画
	glDisable(GL_CULL_FACE);

	glBegin(GL_TRIANGLE_STRIP);
	{
		// 頂点色設定
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

		DrawPolygon( );
	}
	glEnd( );

	// 各種設定引き戻し
	glEnable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	// モデルビューマトリックスの設定
	glMatrixMode(GL_MODELVIEW);
	// 保存マトリックスの取り出し
	glPopMatrix( );
}
//=============================================================================
//	関数名	:Create
//	引数	:無し
//	戻り値	:無し
//	説明	:生成処理を行う。
//=============================================================================
CWall *CWall::Create(VECTOR3 pos, VECTOR3 rot, float width, float height,float depth, char *texName)
{
	CWall *wall;
	wall = new CWall;
	wall->m_Pos = pos;
	wall->m_Rot = rot;
	wall->m_WallBox.depth = depth;
	wall->m_WallBox.height = height;
	wall->m_WallBox.width = width;
	wall->Init(texName);
	return wall;
}

//=============================================================================
//	関数名	:GetWallBox
//	引数	:無し
//	戻り値	:無し
//	説明	:BOX_DATAゲット
//=============================================================================
BOX_DATA CWall::GetWallBox( )
{	
	return m_WallBox;
}