//=============================================================================
//
//	タイトル	シーンファイル(3D)
//	ファイル名	meshfield.cpp
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
#include "meshfield.h"

//=============================================================================
//	関数名	:CMeshfield()
//	引数	:無し
//	戻り値	:無し
//	説明	:コンストラクタ。
//=============================================================================
CMeshfield::CMeshfield()
{
	glMatrixIdentity(&m_mtxWorld);
}

//=============================================================================
//	関数名	:~CMeshfield()
//	引数	:無し
//	戻り値	:無し
//	説明	:デストラクタ。
//=============================================================================
CMeshfield::~CMeshfield()
{

}

//=============================================================================
//	関数名	:Init
//	引数	:VECTOR3 pos(初期位置)
//	戻り値	:無し
//	説明	:初期化処理を行うと共に、初期位置を設定する。
//=============================================================================
void CMeshfield::Init(VECTOR3 pos, VECTOR2 size, char *texName)
{
	CRendererGL	*renderer	= CManager::GetRendererGL();


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
void CMeshfield::Uninit(void)
{
	if(m_Texture != NULL)
	{
		// テクスチャ削除
		glDeleteTextures(1, ((GLuint *)m_Texture));
	}
}

//=============================================================================
//	関数名	:Update
//	引数	:無し
//	戻り値	:無し
//	説明	:更新処理を行う。
//=============================================================================
void CMeshfield::Update(void)
{

}

//=============================================================================
//	関数名	:Draw
//	引数	:無し
//	戻り値	:無し
//	説明	:描画処理を行う。
//=============================================================================
void CMeshfield::Draw(void)
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
	glBindTexture(GL_TEXTURE_2D, m_Texture);
	glEnable(GL_TEXTURE_2D);
	
	// 深度バッファ設定
	glEnable(GL_DEPTH_TEST);

	// ライティングオフ
	glDisable(GL_LIGHTING);

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
CMeshfield *CMeshfield::Create(VECTOR3 pos, VECTOR2 size, char *texName)
{
	CMeshfield *meshfield;

	meshfield = new CMeshfield;

	meshfield->Init(pos, size, texName);

	return meshfield;
}

//=============================================================================
//	関数名	:DrawPolygon
//	引数	:無し
//	戻り値	:無し
//	説明	:ポリゴンの頂点情報をセットする。
//=============================================================================
void CMeshfield::DrawPolygon(void)
{
	// 描画用の法線・テクスチャ座標・頂点座標設定
	// 左上
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2d(0.0, 1.0);
	glVertex3f((m_Pos.x - (m_Size.x * 0.5f)), m_Pos.y, (m_Pos.z - (m_Size.y * 0.5f)));

	// 右上
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2d(1.0, 1.0);
	glVertex3f((m_Pos.x + (m_Size.x * 0.5f)), m_Pos.y, (m_Pos.z - (m_Size.y * 0.5f)));

	// 左下
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2d(0.0, 0.0);
	glVertex3f((m_Pos.x - (m_Size.x * 0.5f)), m_Pos.y, (m_Pos.z + (m_Size.y * 0.5f)));

	// 右下
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2d(1.0, 0.0);
	glVertex3f((m_Pos.x + (m_Size.x * 0.5f)), m_Pos.y, (m_Pos.z + (m_Size.y * 0.5f)));
}