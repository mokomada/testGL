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
CMeshfield::CMeshfield() : CScene3DGL(true, PRIORITY_FIELD, OBJTYPE_NONE)
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

	// メッシュのセッティング
	SetMeshData();
	SetMeshIndex(m_Index, MESHFIELD_HORIZONTAL, MESHFIELD_VERTICAL);
}

//=============================================================================
//	関数名	:SetMeshData
//	引数	:無し
//	戻り値	:無し
//	説明	:ポリゴンの頂点情報をセットする。
//=============================================================================
void CMeshfield::SetMeshData(void)
{
	// 座標設定
	for(int y = 0 ; y <= MESHFIELD_VERTICAL ; y++)
	{
		for(int x = 0 ; x <= MESHFIELD_HORIZONTAL ; x++)
		{
			m_Mesh[(y * (MESHFIELD_HORIZONTAL + 1) + x)].Pos.x
				= (-(MESHFIELD_WIDTH * 0.5f * MESHFIELD_HORIZONTAL)) + (MESHFIELD_WIDTH * x);

			m_Mesh[(y * (MESHFIELD_HORIZONTAL + 1) + x)].Pos.y = 0.0f;

			m_Mesh[(y * (MESHFIELD_HORIZONTAL + 1) + x)].Pos.z
				= -((MESHFIELD_HEIGHT * 0.5f * MESHFIELD_VERTICAL) - (MESHFIELD_HEIGHT * y));
		}
	}

	// 法線設定
	for(int y = 0 ; y <= MESHFIELD_VERTICAL ; y++)
	{
		for(int x = 0 ; x <= MESHFIELD_HORIZONTAL ; x++)
		{
			if((y != 0) && (y != (MESHFIELD_VERTICAL))
				&& (x != 0) && (x != (MESHFIELD_HORIZONTAL)))
			{
				// 法線設定
				VECTOR3 nor, n1, n2, n3, n4, n5, n6, v01, v02, v03, v04, v05, v06;
				v01 = m_Mesh[(y * (MESHFIELD_HORIZONTAL + 1) + (x - 1))].Pos - m_Mesh[(y * (MESHFIELD_HORIZONTAL + 1) + x)].Pos;
				v02 = m_Mesh[((y - 1) * (MESHFIELD_HORIZONTAL + 1) + (x - 1))].Pos - m_Mesh[(y * (MESHFIELD_HORIZONTAL + 1) + x)].Pos;
				v03 = m_Mesh[((y - 1) * (MESHFIELD_HORIZONTAL + 1) + x)].Pos - m_Mesh[(y * (MESHFIELD_HORIZONTAL + 1) + x)].Pos;
				v04 = m_Mesh[((y) * (MESHFIELD_HORIZONTAL + 1) + (x + 1))].Pos - m_Mesh[(y * (MESHFIELD_HORIZONTAL + 1) + x)].Pos;
				v05 = m_Mesh[((y + 1) * (MESHFIELD_HORIZONTAL + 1) + x)].Pos - m_Mesh[(y * (MESHFIELD_HORIZONTAL + 1) + x)].Pos;
				v06 = m_Mesh[((y + 1) * (MESHFIELD_HORIZONTAL + 1) + (x + 1))].Pos - m_Mesh[(y * (MESHFIELD_HORIZONTAL + 1) + x)].Pos;
				n1 = VECTOR3::cross(v01, v02);
				n1.normalize();
				n2 = VECTOR3::cross(v02, v03);
				n2.normalize();
				n3 = VECTOR3::cross(v03, v04);
				n3.normalize();
				n4 = VECTOR3::cross(v04, v05);
				n4.normalize();
				n5 = VECTOR3::cross(v05, v06);
				n5.normalize();
				n6 = VECTOR3::cross(v06, v01);
				n6.normalize();
				nor = (n1 + n2 + n3 + n4 + n5 + n6) / 6.0f;
				nor.normalize();
				m_Mesh[(y * (MESHFIELD_HORIZONTAL + 1) + x)].Nor = nor;
			}
			else
			{
				m_Mesh[(y * (MESHFIELD_HORIZONTAL + 1) + x)].Nor = VECTOR3(0.0f, 1.0f, 0.0f);
			}
		}
	}

	// テクスチャ座標設定
	for(int y = 0 ; y <= MESHFIELD_VERTICAL ; y++)
	{
		for(int x = 0 ; x <= MESHFIELD_HORIZONTAL ; x++)
		{
			m_Mesh[(y * (MESHFIELD_HORIZONTAL + 1) + x)].Tex.x = (float)x * 10.0f;
			m_Mesh[(y * (MESHFIELD_HORIZONTAL + 1) + x)].Tex.y = (float)y * 10.0f;
		}
	}
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
	if(0)
	{
		// 法線設定
		for(int y = 0 ; y <= MESHFIELD_VERTICAL ; y++)
		{
			for(int x = 0 ; x <= MESHFIELD_HORIZONTAL ; x++)
			{
				if((y != 0) && (y != (MESHFIELD_VERTICAL))
					&& (x != 0) && (x != (MESHFIELD_HORIZONTAL)))
				{
					// 法線設定
					VECTOR3 nor;
					VECTOR3 n1, n2, n3, n4, n5, n6, v01, v02, v03, v04, v05, v06;


					v01 = m_Mesh[(y * (MESHFIELD_HORIZONTAL + 1) + (x - 1))].Pos - m_Mesh[(y * (MESHFIELD_HORIZONTAL + 1) + x)].Pos;
					v02 = m_Mesh[((y - 1) * (MESHFIELD_HORIZONTAL + 1) + (x - 1))].Pos - m_Mesh[(y * (MESHFIELD_HORIZONTAL + 1) + x)].Pos;
					v03 = m_Mesh[((y - 1) * (MESHFIELD_HORIZONTAL + 1) + x)].Pos - m_Mesh[(y * (MESHFIELD_HORIZONTAL + 1) + x)].Pos;
					v04 = m_Mesh[((y) * (MESHFIELD_HORIZONTAL + 1) + (x + 1))].Pos - m_Mesh[(y * (MESHFIELD_HORIZONTAL + 1) + x)].Pos;
					v05 = m_Mesh[((y + 1) * (MESHFIELD_HORIZONTAL + 1) + x)].Pos - m_Mesh[(y * (MESHFIELD_HORIZONTAL + 1) + x)].Pos;
					v06 = m_Mesh[((y + 1) * (MESHFIELD_HORIZONTAL + 1) + (x + 1))].Pos - m_Mesh[(y * (MESHFIELD_HORIZONTAL + 1) + x)].Pos;

					n1 = VECTOR3::cross(v01, v02).normalize();
					n2 = VECTOR3::cross(v02, v03).normalize();
					n3 = VECTOR3::cross(v03, v04).normalize();
					n4 = VECTOR3::cross(v04, v05).normalize();
					n5 = VECTOR3::cross(v05, v06).normalize();
					n6 = VECTOR3::cross(v06, v01).normalize();

					nor = ((n1 + n2 + n3 + n4 + n5 + n6) / 6.0f).normalize();
					m_Mesh[(y * (MESHFIELD_HORIZONTAL + 1) + x)].Nor = nor;
				}
				else
				{
					m_Mesh[(y * (MESHFIELD_HORIZONTAL + 1) + x)].Nor = VECTOR3(0.0f, 1.0f, 0.0f);
				}
			}
		}
	}
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
	//glDisable(GL_LIGHTING);

	glBegin(GL_TRIANGLE_STRIP);
	{
		// 頂点色設定
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

		// ポリゴン描画
		for(int i = 0 ; i < MESHFIELD_INDEX_NUM ; i++)
		{
			glNormal3f(0.0f, 1.0f, 0.0f);
			glTexCoord2d(m_Mesh[m_Index[i]].Tex.x, m_Mesh[m_Index[i]].Tex.y);
			glVertex3f(m_Mesh[m_Index[i]].Pos.x, m_Mesh[m_Index[i]].Pos.y, m_Mesh[m_Index[i]].Pos.z);
		}
	}
	glEnd();

	// 各種設定引き戻し
	//glEnable(GL_LIGHTING);
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
//	関数名	:SetMeshIndex
//	引数	:uint *idx	->	インデックス
//			:int x		->	メッシュの横ブロック数
//			:int y		->	メッシュの縦ブロック数
//	戻り値	:無し
//	説明	:メッシュのインデックスをセットする。
//=============================================================================
void CMeshfield::SetMeshIndex(uint *idxBuff, const int horizontal, const int vertical)
{
	int	idxNum = ((horizontal + 1) * 2) * vertical + ((vertical - 1) * 2);
	int	idxStd = ((horizontal + 1) * 2 + 2);
	int	idxVtxNum = (horizontal + 1) * (vertical + 1);


	int buff = (idxVtxNum / (vertical + 1));

	for(int nCntVertical = 0 ; nCntVertical < vertical ; nCntVertical++)
	{
		for(int nCntIdx = 0 ; nCntIdx < idxStd ; nCntIdx++)
		{
			if((nCntVertical == (vertical - 1)) && (nCntIdx == (idxStd - 2)))
			{// 処理打ち切り
				break;
			}

			if(nCntIdx == (idxStd - 1))
			{
				buff += (horizontal + 2);
				idxBuff[nCntVertical * idxStd + nCntIdx] = buff;
			}
			else if(nCntIdx == (idxStd - 2))
			{
				idxBuff[nCntVertical * idxStd + nCntIdx] = buff;
			}
			else
			{
				idxBuff[nCntVertical * idxStd + nCntIdx] = buff;

				if(nCntIdx % 2 == 0)
				{
					buff -= (horizontal + 1);
				}
				else
				{
					if(nCntIdx != (idxStd - 3))
					{
						buff += (horizontal + 2);
					}
				}
			}
		}
	}
}