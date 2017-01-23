//=============================================================================
//
//	タイトル	シーンファイル(3D)
//	ファイル名	sceneBillboard.cpp
//	作成者		AT13A284_07 池田達哉
//	作成日		2016/04/20
//
//=============================================================================
//=============================================================================
//	インクルード
//=============================================================================
#include "main.h"
#include "manager.h"
#include "rendererGL.h"
#include "sceneBillboardGL.h"

//=============================================================================
//	関数名	:CSceneBillboard()
//	引数	:無し
//	戻り値	:無し
//	説明	:コンストラクタ。
//=============================================================================
CSceneBillboardGL::CSceneBillboardGL(bool ifListAdd, int priority, OBJTYPE objType) : CSceneGL(ifListAdd, priority, objType)
{

	glMatrixIdentity(&m_mtxWorld);
}

//=============================================================================
//	関数名	:~CSceneBillboard()
//	引数	:無し
//	戻り値	:無し
//	説明	:デストラクタ。
//=============================================================================
CSceneBillboardGL::~CSceneBillboardGL()
{

}

//=============================================================================
//	関数名	:Init
//	引数	:VECTOR3 pos(初期位置)
//	戻り値	:無し
//	説明	:初期化処理を行うと共に、初期位置を設定する。
//=============================================================================
void CSceneBillboardGL::Init(VECTOR3 pos, VECTOR2 size, char *texName)
{
	CRendererGL	*renderer = CManager::GetRendererGL();


	// 各種初期化
	SetPos(VECTOR3(pos.x, pos.y, pos.z));
	SetRot(VECTOR3(0.0f, 0.0f, 0.0f));
	m_Size = size;
	
	// テクスチャ読込
	m_Texture = renderer->CreateTextureTGA(texName);
}

//=============================================================================
//	関数名	:Uninit
//	引数	:無し
//	戻り値	:無し
//	説明	:終了処理を行う。
//=============================================================================
void CSceneBillboardGL::Uninit( bool isLast )
{
	// テクスチャ削除
	if(m_Texture != NULL)
	{
		glDeleteTextures(1, &m_Texture);
	}
}

//=============================================================================
//	関数名	:Update
//	引数	:無し
//	戻り値	:無し
//	説明	:更新処理を行う。
//=============================================================================
void CSceneBillboardGL::Update(void)
{

}

//=============================================================================
//	関数名	:Draw
//	引数	:無し
//	戻り値	:無し
//	説明	:描画処理を行う。
//=============================================================================
void CSceneBillboardGL::Draw(void)
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
	glBindTexture(GL_TEXTURE_2D, m_Texture);
	glEnable(GL_TEXTURE_2D);

	// 深度バッファ設定
	glEnable(GL_DEPTH_TEST);

	// ライティングオフ
	glDisable(GL_LIGHTING);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthMask( FALSE );
	glBegin(GL_TRIANGLE_STRIP);
	{
		// 頂点色設定
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

		DrawPolygon();
	}
	glEnd();


	// 各種設定引き戻し
	glEnable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
	glDepthMask( TRUE );
	// モデルビューマトリックスの設定
	glMatrixMode(GL_MODELVIEW);
	// 保存マトリックスの取り出し
	glPopMatrix();
}

//=============================================================================
//	関数名	:Draw
//	引数	:テクスチャのアドレス
//	戻り値	:無し
//	説明	:描画処理を行う。
//=============================================================================
void CSceneBillboardGL::Draw( uint texture )
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
	glBindTexture(GL_TEXTURE_2D, texture);
	glEnable(GL_TEXTURE_2D);

	// 深度バッファ設定
	glEnable(GL_DEPTH_TEST);

	// ライティングオフ
	glDisable(GL_LIGHTING);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthMask( FALSE );
	glBegin(GL_TRIANGLE_STRIP);
	{
		// 頂点色設定
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

		DrawPolygon();
	}
	glEnd();


	// 各種設定引き戻し
	glEnable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
	glDepthMask( TRUE );
	// モデルビューマトリックスの設定
	glMatrixMode(GL_MODELVIEW);
	// 保存マトリックスの取り出し
	glPopMatrix();
}

//=============================================================================
//	関数名	:Create
//	引数	:VECTOR3 pos(初期位置)
//	戻り値	:無し
//	説明	:インスタンス生成を行うと共に、初期位置を設定する。
//=============================================================================
CSceneBillboardGL *CSceneBillboardGL::Create(VECTOR3 pos, VECTOR2 size, char *texName)
{
	CSceneBillboardGL *sceneBillboard;

	sceneBillboard = new CSceneBillboardGL;

	sceneBillboard->Init(pos, size, texName);

	return sceneBillboard;
}

//=============================================================================
//	関数名	:DrawPolygon
//	引数	:無し
//	戻り値	:無し
//	説明	:ポリゴンの頂点情報をセットする。
//=============================================================================
void CSceneBillboardGL::DrawPolygon(void)
{
	// 描画用の法線・テクスチャ座標・頂点座標設定
	// 左上
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2d(0.0, 1.0);
	glVertex3f(( - (m_Size.x * 0.5f)), ((m_Size.y * 0.5f)), 0.0f);

	// 右上
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2d(1.0, 1.0);
	glVertex3f(((m_Size.x * 0.5f)), ( (m_Size.y * 0.5f)), 0.0f);

	// 左下
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2d(0.0, 0.0);
	glVertex3f(( - (m_Size.x * 0.5f)), ( - (m_Size.y * 0.5f)), 0.0f);

	// 右下
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2d(1.0, 0.0);
	glVertex3f(( (m_Size.x * 0.5f)), (- (m_Size.y * 0.5f)), 0.0f);
}