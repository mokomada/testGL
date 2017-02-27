//=============================================================================
//
//	タイトル	シーンファイル(3D)
//	ファイル名	scene3D.cpp
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
#include "sceneGL.h"
#include "scene3DGL.h"
#include "slope.h"

//=============================================================================
//	関数名	:CScene3D()
//	引数	:無し
//	戻り値	:無し
//	説明	:コンストラクタ。
//=============================================================================
CSlope::CSlope(bool ifListAdd, int priority, OBJTYPE objType) : CSceneGL(ifListAdd, priority, objType)
{

}

//=============================================================================
//	関数名	:~CScene3D()
//	引数	:無し
//	戻り値	:無し
//	説明	:デストラクタ。
//=============================================================================
CSlope::~CSlope()
{

}

//=============================================================================
//	関数名	:Init
//	引数	:VECTOR3 pos(初期位置)
//	戻り値	:無し
//	説明	:初期化処理を行うと共に、初期位置を設定する。
//=============================================================================
void CSlope::Init(VECTOR3 vec[4] ,VECTOR3 pos , char *texName)
{
	CRendererGL	*renderer = CManager::GetRendererGL();

	for (int count = 0; count < 4; count++)
	{
		m_VtxPos[count] = vec[count];
	}

	// 各種初期化
	SetPos(VECTOR3(pos.x, pos.y, pos.z));
	SetRot(VECTOR3(0.0f, 0.0f, 0.0f));

	// テクスチャ読込
	m_Texture = renderer->CreateTextureTGA(texName);
}

//=============================================================================
//	関数名	:Uninit
//	引数	:無し
//	戻り値	:無し
//	説明	:終了処理を行う。
//=============================================================================
void CSlope::Uninit(bool isLast)
{
	// テクスチャ削除
	if (m_Texture != NULL)
	{
		if (isLast)
			glDeleteTextures(1, ((GLuint *)m_Texture));
	}
}

//=============================================================================
//	関数名	:Update
//	引数	:無し
//	戻り値	:無し
//	説明	:更新処理を行う。
//=============================================================================
void CSlope::Update(void)
{

}

//=============================================================================
//	関数名	:Draw
//	引数	:無し
//	戻り値	:無し
//	説明	:描画処理を行う。
//=============================================================================
void CSlope::Draw(void)
{
	// モデルビューマトリクスの設定
	glMatrixMode(GL_MODELVIEW);

	glDisable(GL_CULL_FACE);
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

	glEnable(GL_CULL_FACE);
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
CSlope *CSlope::Create(VECTOR3 vec[4], VECTOR3 pos, char *texName)
{
	CSlope *slope;

	slope = new CSlope;

	slope->Init(vec , pos, texName);
	return slope;
}

//=============================================================================
//	関数名	:DrawPolygon
//	引数	:無し
//	戻り値	:無し
//	説明	:ポリゴンの頂点情報をセットする。
//=============================================================================
void CSlope::DrawPolygon(void)
{
	// 描画用の法線・テクスチャ座標・頂点座標設定
	// 左上
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2d(0.0, 1.0);
	glVertex3f(m_VtxPos[0].x, m_VtxPos[0].y, m_VtxPos[0].z);

	// 右上
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2d(1.0, 1.0);
	glVertex3f(m_VtxPos[1].x, m_VtxPos[1].y, m_VtxPos[1].z);

	// 左下
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2d(0.0, 0.0);
	glVertex3f(m_VtxPos[2].x, m_VtxPos[2].y, m_VtxPos[2].z);

	// 右下
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2d(1.0, 0.0);
	glVertex3f(m_VtxPos[3].x, m_VtxPos[3].y, m_VtxPos[3].z);

}