//=============================================================================
//
//	タイトル	シーンファイル(2D)
//	ファイル名	scene2D.cpp
//	作成者		AT13A284_07 池田達哉
//	作成日		2016/11/14
//
//=============================================================================
//=============================================================================
//	インクルード
//=============================================================================
#include "main.h"
#include "manager.h"
#include "rendererGL.h"
#include "scene2DGL.h"

//=============================================================================
//	関数名	:CScene2D()
//	引数	:無し
//	戻り値	:無し
//	説明	:コンストラクタ。
//=============================================================================
CScene2DGL::CScene2DGL(bool ifListAdd, int priority, OBJTYPE objType) : CSceneGL(ifListAdd, priority, objType)
{
	m_fLength	= 0.0f;
	m_fAngle	= 0.0f;
}

//=============================================================================
//	関数名	:~CScene2D()
//	引数	:無し
//	戻り値	:無し
//	説明	:デストラクタ。
//=============================================================================
CScene2DGL::~CScene2DGL()
{

}

//=============================================================================
//	関数名	:Init
//	引数	:VECTOR3 pos(初期位置)
//	戻り値	:無し
//	説明	:初期化処理を行うと共に、初期位置を設定する。
//=============================================================================
void CScene2DGL::Init(VECTOR3 pos, VECTOR2 size, char *texName)
{
	CRendererGL	*renderer	= CManager::GetRendererGL();


	// 各種初期設定
	SetPos(VECTOR3(pos.x, pos.y, pos.z));
	SetRot(VECTOR3(0.0f, 0.0f, 0.0f));
	m_Size		= size;
	m_fAngle	= atan2f(m_Size.x, m_Size.y);
	m_fLength	= hypotf(m_Size.x, m_Size.y) * 0.5f;

	// テクスチャ読込
	m_Texture	= renderer->CreateTextureTGA(texName);
}

//=============================================================================
//	関数名	:Uninit
//	引数	:無し
//	戻り値	:無し
//	説明	:終了処理を行う。
//=============================================================================
void CScene2DGL::Uninit(bool isLast)
{
	// テクスチャ削除
	if(m_Texture != NULL)
	{
		if(isLast)
		glDeleteTextures(1, ((GLuint *)m_Texture));
	}
}

//=============================================================================
//	関数名	:Update
//	引数	:無し
//	戻り値	:無し
//	説明	:更新処理を行う。
//=============================================================================
void CScene2DGL::Update(void)
{

}

//=============================================================================
//	関数名	:Draw
//	引数	:無し
//	戻り値	:無し
//	説明	:描画処理を行う。
//=============================================================================
void CScene2DGL::Draw(void)
{
	// モデルビューマトリックスの設定(投影変換)
	glMatrixMode(GL_PROJECTION);
	// マトリックスの保存
	glPushMatrix();
	// 変換行列の初期化
	glLoadIdentity();

	// 平行射影or正射影
	glOrtho(0, (GLdouble)SCREEN_WIDTH, (GLdouble)SCREEN_HEIGHT, 0, -100.0, 100.0);
	// ワールド座標系の表示領域を，ビューポートの大きさに比例させる

	// モデルビューマトリックスの設定
	glMatrixMode(GL_MODELVIEW);
	// マトリックスの保存
	glPushMatrix();
	// 変換行列の初期化
	glLoadIdentity();
	
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
	{
		// 頂点色設定
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

		// 頂点情報設定
		DrawPolygon();
	}
	glEnd();

	// テクスチャマッピング無効化
	glDisable(GL_TEXTURE_2D);
	
	// ブレンド無効化
	glDisable(GL_BLEND);

	// ライト有効化
	glEnable(GL_LIGHTING);
	
	// モデルビューマトリックスの設定(投影変換)
	glMatrixMode(GL_PROJECTION);
	// 保存マトリックスの取り出し
	glPopMatrix();

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
CScene2DGL *CScene2DGL::Create(VECTOR3 pos, VECTOR2 size, char *texName)
{
	CScene2DGL *scene2D;

	scene2D = new CScene2DGL;

	scene2D->Init(pos, size, texName);

	return scene2D;
}

//=============================================================================
//	関数名	:DrawPolygon
//	引数	:無し
//	戻り値	:無し
//	説明	:ポリゴンの頂点情報をセットする。
//=============================================================================
void CScene2DGL::DrawPolygon(void)
{
	// 斜線の長さ計算
	m_fLength	= hypotf(m_Size.x, m_Size.y) * 0.5f;

	// 描画用のテクスチャ座標・頂点座標設定
	// 左上頂点
	glTexCoord2d(0.0, 0.0);
	glVertex3f((m_Pos.x - (sinf(m_fAngle + m_Rot.z) * m_fLength)), (m_Pos.y + (cosf(m_fAngle + m_Rot.z + PI) * m_fLength)), 0.0f);

	// 右上頂点
	glTexCoord2d(1.0, 0.0);
	glVertex3f((m_Pos.x - (sinf(-m_fAngle + m_Rot.z) * m_fLength)), (m_Pos.y + (cosf(-m_fAngle + m_Rot.z + PI) * m_fLength)), 0.0f);

	// 左下頂点
	glTexCoord2d(0.0, 1.0);
	glVertex3f((m_Pos.x - (sinf(-m_fAngle + m_Rot.z + PI) * m_fLength)), (m_Pos.y + (cosf(-m_fAngle + m_Rot.z) * m_fLength)), 0.0f);

	// 右下頂点
	glTexCoord2d(1.0, 1.0);
	glVertex3f((m_Pos.x - (sinf(m_fAngle + m_Rot.z - PI) * m_fLength)), (m_Pos.y + (cosf(m_fAngle + m_Rot.z) * m_fLength)), 0.0f);
}