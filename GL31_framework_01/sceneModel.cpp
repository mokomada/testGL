//=============================================================================
//
//	タイトル	シーンファイル(3D)
//	ファイル名	scene3D.cpp
//	作成者		AT13A284_07 池田達哉
//	作成日		2016/04/20
//
//=============================================================================
//=============================================================================
//	インクルード
//=============================================================================
#include <stdio.h>
#include "main.h"
#include "manager.h"
#include "rendererGL.h"
#include "game.h"
#include "sceneModel.h"

//=============================================================================
//	関数名	:CScene3D()
//	引数	:無し
//	戻り値	:無し
//	説明	:コンストラクタ。
//=============================================================================
CSceneModel::CSceneModel(int priority, OBJTYPE objType)
{

}

//=============================================================================
//	関数名	:~CScene3D()
//	引数	:無し
//	戻り値	:無し
//	説明	:デストラクタ。
//=============================================================================
CSceneModel::~CSceneModel()
{

}

//=============================================================================
//	関数名	:Init
//	引数	:VECTOR3 pos(初期位置)
//	戻り値	:無し
//	説明	:初期化処理を行うと共に、初期位置を設定する。
//=============================================================================
void CSceneModel::Init(char* FileName)
{
	CRendererGL	*renderer	= CManager::GetRendererGL();

	// 各種初期化
	m_Frame	= 0;
	m_ExecMotion	= -1;
	m_Scale			= VECTOR3(1.0f, 1.0f, 1.0f);
	m_Texture		= 0;
	
	
	m_Texture = renderer->CreateTextureTGA("./data/TEXTURE/"MODEL_TEXFILENAME000);
	LoadModel(FileName);

	// モーション生成
	m_Motion = new MOTION[MODEL_MOTION_NUM];
	LoadMotion("data/MOTION/miku_01_01.anm", 0);
	//LoadMotion("data/MOTION/miku_01_02.anm", 0);
}

//=============================================================================
//	関数名	:Uninit
//	引数	:無し
//	戻り値	:無し
//	説明	:終了処理を行う。
//=============================================================================
void CSceneModel::Uninit(bool isLast)
{
	// テクスチャの削除
	if(m_Texture != NULL)
	{
		if(isLast)
		glDeleteTextures(1, ((GLuint *)m_Texture));
	}

	// 配列の消去
	for(int nCntParts = 0 ; nCntParts < m_nNumParts ; nCntParts++ )
	{
		// 座標配列消去
		delete[] m_Parts[nCntParts].data.Pos;
		
		// テクスチャ座標配列消去
		delete[] m_Parts[nCntParts].data.Tex;
		
		// 法線配列消去
		delete[] m_Parts[nCntParts].data.Nrm;

		// インデックス配列消去
		for(int nCntIdx = 0 ; nCntIdx < m_Parts[nCntParts].dataNum.Idx ; nCntIdx++)
		{
			delete[] m_Parts[nCntParts].data.Idx[nCntIdx];
			m_Parts[nCntParts].data.Idx[nCntIdx] = NULL;
		}
		delete[] m_Parts[nCntParts].data.Idx;
		m_Parts[nCntParts].data.Idx = NULL;
	}

	// パーツ配列消去
	delete[] m_Parts;


	// モーション消去
	if(m_Motion != NULL)
	{
		for(int nCntMotion = 0 ; nCntMotion < MODEL_MOTION_NUM ; nCntMotion++ )
		{
			if(m_Motion[nCntMotion].Pose != NULL)
			{
				if(m_Motion[nCntMotion].Pose != NULL)
				{
					for(int nCntParts = 0 ; nCntParts < m_nNumParts ; nCntParts++ )
					{
						delete[] m_Motion[nCntMotion].Pose[nCntParts];
					}
					delete[] m_Motion[nCntMotion].Pose;
				}
			}
		}
		delete[] m_Motion;
	}
}

//=============================================================================
//	関数名	:Update
//	引数	:無し
//	戻り値	:無し
//	説明	:更新処理を行う。
//=============================================================================
void CSceneModel::Update(void)
{
	
}

//=============================================================================
//	関数名	:Draw
//	引数	:無し
//	戻り値	:無し
//	説明	:描画処理を行う。
//=============================================================================
void CSceneModel::Draw(void)
{
	glMatrixMode(GL_MODELVIEW);		// モデルビューマトリクスの設定
	glPushMatrix();					// マトリクスの退避

	// 描画処理ここから
	glBindTexture(GL_TEXTURE_2D, m_Texture);

	// 2Dテクスチャ有効化
	glEnable(GL_TEXTURE_2D);
	
	// 深度バッファ有効化
	glEnable(GL_DEPTH_TEST);

	// カリング無効化
	glDisable(GL_CULL_FACE);
	
	// 頂点色設定
	switch(CManager::GetWhatPlayer())
	{
	case 0:	// 1P
		glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
		break;
	case 1:	// 2P
		glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
		break;
	case 2:	// 3P
		glColor4f(0.0f, 1.0f, 1.0f, 1.0f);
		break;
	case 3:	// 4P
		glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
		break;
	default:
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		break;
	}

	// モデル描画
	DrawModel();
	
	// 2Dテクスチャ無効化
	glDisable(GL_TEXTURE_2D);
	
	// 深度バッファ無効化
	glDisable(GL_DEPTH_TEST);

	// カリング有効化
	glEnable(GL_CULL_FACE);

	glMatrixMode(GL_MODELVIEW);		// モデルビューマトリックスの設定
	glPopMatrix();					// 保存マトリックスの取り出し
}

//=============================================================================
//	関数名	:Create
//	引数	:VECTOR3 pos(初期位置)
//	戻り値	:無し
//	説明	:インスタンス生成を行うと共に、初期位置を設定する。
//=============================================================================
CSceneModel *CSceneModel::Create(char* FileName)
{
	CSceneModel *model;

	model = new CSceneModel;

	model->Init(FileName);

	return model;
}

//=============================================================================
//	関数名	:LoadModel
//	引数	:char* filename	->	ファイル名
//	戻り値	:無し
//	説明	:引数で指定したファイル名のモデル情報を読み込む。
//=============================================================================
void CSceneModel::LoadModel(char *fileName)
{
	int		nCntData	= 0;	// 配列生成用カウンタ
	char	*str		= NULL;	// ファイル内容格納文字列
	int		offset		= 0;	// オフセット
	

	// バイナリファイル読み込み
	str = CReadFile::ReadBinaryFile(fileName);

	// パーツ数をカウント
	m_nNumParts = CReadFile::SearchWordNumByString(str, 0, "\ng ");
	// パーツ情報生成
	m_Parts = new PARTS[m_nNumParts];

	// パーツ情報初期化
	for(int i = 0 ; i < m_nNumParts ; i++)
	{
		m_Parts[i].Parents	= -1;
		m_Parts[i].Pos		= VECTOR3(0.0f, 0.0f, 0.0f);
		m_Parts[i].Rot		= VECTOR3(0.0f, 0.0f, 0.0f);
		m_Parts[i].Move		= VECTOR3(0.0f, 0.0f, 0.0f);
		m_Parts[i].RotMove	= VECTOR3(0.0f, 0.0f, 0.0f);
	}

	// 配列生成
	for(int i = 0 ; i < m_nNumParts ; i++)
	{
		// オフセットの初期化
		offset = 0;

		// 検索開始位置をセット
		for(int j = 0 ; j <= i ; j++)
		{
			offset = CReadFile::SearchWordByString(str, offset + 3, "\ng ");
		}

		// 座標数をカウント
		nCntData = CReadFile::SearchWordNumByString(str, offset + 3, "\nv ", "\ng ");
		// 座標数を記録
		m_Parts[i].dataNum.Pos = nCntData;
		// 座標配列生成
		m_Parts[i].data.Pos = new VECTOR3[nCntData];

		// テクスチャ座標数をカウント
		nCntData = CReadFile::SearchWordNumByString(str, offset + 3, "\nvt ", "\ng ");
		// テクスチャ座標数を記録
		m_Parts[i].dataNum.Tex = nCntData;
		// テクスチャ座標配列生成
		m_Parts[i].data.Tex = new VECTOR2[nCntData];

		// 法線数をカウント
		nCntData = CReadFile::SearchWordNumByString(str, offset + 3, "\nvn ", "\ng ");
		// 法線数を記録
		m_Parts[i].dataNum.Nrm = nCntData;
		// 法線配列生成
		m_Parts[i].data.Nrm = new VECTOR3[nCntData];

		// インデックス数をカウント
		nCntData = CReadFile::SearchWordNumByString(str, offset + 3, "\nf ", "\ng ");
		// インデックス数を記録
		m_Parts[i].dataNum.Idx = nCntData;
		// インデックス配列生成
		m_Parts[i].data.Idx = new MODEL_INDEX*[nCntData];
		for(int nCntIdx = 0 ; nCntIdx < nCntData ; nCntIdx++)
		{
			m_Parts[i].data.Idx[nCntIdx] = new MODEL_INDEX[3];
		}
	}

	// 情報読み込み
	for(int nCntParts = 0 ; nCntParts < m_nNumParts ; nCntParts++)
	{
		// オフセットの初期化
		offset = 0;

		// 検索開始位置をセット
		for(int j = 0 ; j <= nCntParts ; j++)
		{
			offset = CReadFile::SearchWordByString(str, offset + 3, "\ng ");
		}

		// 座標情報読み込み
		offset = CReadFile::SearchWordByString(str, offset, "\nv ");
		offset += 1;
		for(int nCntPos = 0 ; nCntPos < m_Parts[nCntParts].dataNum.Pos ; nCntPos++)
		{
			// データ格納
			sscanf_s(&str[offset], "v %f %f %f\n",
				&m_Parts[nCntParts].data.Pos[nCntPos].x,
				&m_Parts[nCntParts].data.Pos[nCntPos].y,
				&m_Parts[nCntParts].data.Pos[nCntPos].z);

			// スケール反映
			m_Parts[nCntParts].data.Pos[nCntPos].x *= MODEL_POWER;
			m_Parts[nCntParts].data.Pos[nCntPos].y *= MODEL_POWER;
			m_Parts[nCntParts].data.Pos[nCntPos].z *= MODEL_POWER;

			// オフセット移動
			offset += 1;
			if(nCntPos != (m_Parts[nCntParts].dataNum.Pos - 1))
			{
				offset = CReadFile::SearchWordByString(str, offset, "\nv ");
				offset += 1;
			}
		}

		// テクスチャ座標情報読み込み
		offset = CReadFile::SearchWordByString(str, offset, "\nvt ");
		offset += 1;
		for(int nCntTex = 0 ; nCntTex < m_Parts[nCntParts].dataNum.Tex ; nCntTex++)
		{
			// データ格納
			sscanf_s(&str[offset], "vt %f %f\n",
				&m_Parts[nCntParts].data.Tex[nCntTex].x,
				&m_Parts[nCntParts].data.Tex[nCntTex].y);

			// オフセット移動
			offset += 1;
			if(nCntTex != (m_Parts[nCntParts].dataNum.Tex - 1))
			{
				offset = CReadFile::SearchWordByString(str, offset, "\nvt ");
				offset += 1;
			}
		}

		// 法線情報読み込み
		offset = CReadFile::SearchWordByString(str, offset, "\nvn ");
		offset += 1;
		for(int nCntNrm = 0 ; nCntNrm < m_Parts[nCntParts].dataNum.Nrm ; nCntNrm++)
		{
			// データ格納
			sscanf_s(&str[offset], "vn %f %f %f\n",
				&m_Parts[nCntParts].data.Nrm[nCntNrm].x,
				&m_Parts[nCntParts].data.Nrm[nCntNrm].y,
				&m_Parts[nCntParts].data.Nrm[nCntNrm].z);
			
			// オフセット移動
			offset += 1;
			if(nCntNrm != (m_Parts[nCntParts].dataNum.Nrm - 1))
			{
				offset = CReadFile::SearchWordByString(str, offset, "\nvn ");
				offset += 1;
			}
		}

		// マテリアル読み込み
		;

		// インデックス情報読み込み
		offset = CReadFile::SearchWordByString(str, offset, "\nf ");
		offset += 1;
		for(int nCntIdx = 0 ; nCntIdx < m_Parts[nCntParts].dataNum.Idx ; nCntIdx++)
		{
			// データ格納
			sscanf_s(&str[offset], "f %d/%d/%d %d/%d/%d %d/%d/%d\n",
				&m_Parts[nCntParts].data.Idx[nCntIdx][0].vtx,
				&m_Parts[nCntParts].data.Idx[nCntIdx][0].tex,
				&m_Parts[nCntParts].data.Idx[nCntIdx][0].nrm,
				&m_Parts[nCntParts].data.Idx[nCntIdx][1].vtx,
				&m_Parts[nCntParts].data.Idx[nCntIdx][1].tex,
				&m_Parts[nCntParts].data.Idx[nCntIdx][1].nrm,
				&m_Parts[nCntParts].data.Idx[nCntIdx][2].vtx,
				&m_Parts[nCntParts].data.Idx[nCntIdx][2].tex,
				&m_Parts[nCntParts].data.Idx[nCntIdx][2].nrm);

			// データ補正
			m_Parts[nCntParts].data.Idx[nCntIdx][0].vtx--;
			m_Parts[nCntParts].data.Idx[nCntIdx][0].tex--;
			m_Parts[nCntParts].data.Idx[nCntIdx][0].nrm--;
			m_Parts[nCntParts].data.Idx[nCntIdx][1].vtx--;
			m_Parts[nCntParts].data.Idx[nCntIdx][1].tex--;
			m_Parts[nCntParts].data.Idx[nCntIdx][1].nrm--;
			m_Parts[nCntParts].data.Idx[nCntIdx][2].vtx--;
			m_Parts[nCntParts].data.Idx[nCntIdx][2].tex--;
			m_Parts[nCntParts].data.Idx[nCntIdx][2].nrm--;
			for(int idx = 0 ; idx < nCntParts ; idx++)
			{
				m_Parts[nCntParts].data.Idx[nCntIdx][0].vtx -= m_Parts[idx].dataNum.Pos;
				m_Parts[nCntParts].data.Idx[nCntIdx][0].tex -= m_Parts[idx].dataNum.Tex;
				m_Parts[nCntParts].data.Idx[nCntIdx][0].nrm -= m_Parts[idx].dataNum.Nrm;
				m_Parts[nCntParts].data.Idx[nCntIdx][1].vtx -= m_Parts[idx].dataNum.Pos;
				m_Parts[nCntParts].data.Idx[nCntIdx][1].tex -= m_Parts[idx].dataNum.Tex;
				m_Parts[nCntParts].data.Idx[nCntIdx][1].nrm -= m_Parts[idx].dataNum.Nrm;
				m_Parts[nCntParts].data.Idx[nCntIdx][2].vtx -= m_Parts[idx].dataNum.Pos;
				m_Parts[nCntParts].data.Idx[nCntIdx][2].tex -= m_Parts[idx].dataNum.Tex;
				m_Parts[nCntParts].data.Idx[nCntIdx][2].nrm -= m_Parts[idx].dataNum.Nrm;
			}

			// オフセット移動
			offset += 1;
			if(nCntIdx != (m_Parts[nCntParts].dataNum.Idx - 1))
			{
				offset = CReadFile::SearchWordByString(str, offset, "\nf ");
				offset += 1;
			}
		}
	}
}

//=============================================================================
//	関数名	:LoadMotion
//	引数	:char*	filename	->	ファイル名
//			:int	nNumMotion	->	モーションナンバー
//	戻り値	:無し
//	説明	:引数で指定したファイル名のモーション情報を読み込む。
//=============================================================================
void CSceneModel::LoadMotion(char *fileName, int nNumMotion)
{
	int		nCntData	= 0;	// 配列生成用カウンタ
	char	*str		= NULL;	// ファイル内容格納文字列
	int		offset		= 0;	// オフセット
	int		frame		= 0;
	

	// バイナリファイル読み込み
	str = CReadFile::ReadBinaryFile(fileName);

	// フレーム数をカウント
	frame = CReadFile::SearchWordNumByString(str, 0, "fr ");

	// フレーム数を設定
	m_Motion[nNumMotion].Frame = frame;

	if((m_nNumParts > 0) && (m_Motion[nNumMotion].Frame > 0))
	{
		// 配列生成
		m_Motion[nNumMotion].Pose = new POSE*[m_nNumParts];
		for(int nCntParts = 0 ; nCntParts < m_nNumParts ; nCntParts++)
		{
			m_Motion[nNumMotion].Pose[nCntParts] = new POSE[m_Motion[nNumMotion].Frame];
		}
	
		// オフセットの初期化
		offset = 0;

		// 情報読み込み
		for(int nCntFrame = 0 ; nCntFrame < m_Motion[nNumMotion].Frame ; nCntFrame++)
		{
			// 読み込み開始位置をセット
			offset = CReadFile::SearchWordByString(str, offset, "fr ");

			// パーツごとに情報を読み込み
			for(int nCntParts = 0 ; nCntParts < m_nNumParts ; nCntParts++)
			{
				float a;
				offset = CReadFile::SearchWordByString(str, offset + 1, "ky ");
				// データ格納
				sscanf_s(&str[offset], "ky %f %f %f %f %f %f",
					&m_Motion[nNumMotion].Pose[nCntParts][nCntFrame].PosX,
					&m_Motion[nNumMotion].Pose[nCntParts][nCntFrame].PosY,
					&m_Motion[nNumMotion].Pose[nCntParts][nCntFrame].PosZ,
					&m_Motion[nNumMotion].Pose[nCntParts][nCntFrame].RotX,
					&m_Motion[nNumMotion].Pose[nCntParts][nCntFrame].RotY,
					&m_Motion[nNumMotion].Pose[nCntParts][nCntFrame].RotZ);
				a = m_Motion[nNumMotion].Pose[nCntParts][nCntFrame].PosX;
				a = 0;
			}
		}
	}

	FILE	*fp;

	fopen_s(&fp, "data/MOTION/test.txt", "w");

	// 情報書き込み
	for(int nCntFrame = 0 ; nCntFrame < m_Motion[nNumMotion].Frame ; nCntFrame++)
	{
		fprintf_s(fp, "fr %d\n", nCntFrame);

		// パーツごとに情報を書き込み
		for(int nCntParts = 0 ; nCntParts < m_nNumParts ; nCntParts++)
		{
			// データ格納
			fprintf_s(fp, "ky %f %f %f %f %f %f\n",
				m_Motion[nNumMotion].Pose[nCntParts][nCntFrame].PosX,
				m_Motion[nNumMotion].Pose[nCntParts][nCntFrame].PosY,
				m_Motion[nNumMotion].Pose[nCntParts][nCntFrame].PosZ,
				m_Motion[nNumMotion].Pose[nCntParts][nCntFrame].RotX,
				m_Motion[nNumMotion].Pose[nCntParts][nCntFrame].RotY,
				m_Motion[nNumMotion].Pose[nCntParts][nCntFrame].RotZ);
			m_Motion[nNumMotion].Pose[nCntParts][nCntFrame].PosX *= MODEL_POWER;
			m_Motion[nNumMotion].Pose[nCntParts][nCntFrame].PosY *= MODEL_POWER;
			m_Motion[nNumMotion].Pose[nCntParts][nCntFrame].PosZ *= MODEL_POWER;
		}

		fprintf_s(fp, "\n");
	}

	fclose(fp);
}

//=============================================================================
//	関数名	:DrawModel
//	引数	:無し
//	戻り値	:無し
//	説明	:ポリゴンの頂点情報をセットする。
//=============================================================================
void CSceneModel::DrawModel(void)
{
	// パーツ数ぶん描画
	for(int nCntParts = 0 ; nCntParts < m_nNumParts ; nCntParts++)
	{
		glPushMatrix();	// マトリクスの退避
		
		// モーション情報の設定
		if(m_ExecMotion > -1)
		{
			glTranslatef(m_Motion[m_ExecMotion].Pose[nCntParts][m_Frame].PosX,
						m_Motion[m_ExecMotion].Pose[nCntParts][m_Frame].PosY,
						m_Motion[m_ExecMotion].Pose[nCntParts][m_Frame].PosZ);
			glRotatef((GLfloat)m_Motion[m_ExecMotion].Pose[nCntParts][m_Frame].RotZ, 0.0f, 0.0f, 1.0f);
			glRotatef((GLfloat)m_Motion[m_ExecMotion].Pose[nCntParts][m_Frame].RotY, 0.0f, 1.0f, 0.0f);
			glRotatef((GLfloat)m_Motion[m_ExecMotion].Pose[nCntParts][m_Frame].RotX, 1.0f, 0.0f, 0.0f);
		}

		// インデックス数だけ面を描画
		for(int nCntIdx = 0 ; nCntIdx < m_Parts[nCntParts].dataNum.Idx ; nCntIdx++)
		{
			glBegin(GL_TRIANGLES);

			for(int idx = 0 ; idx < 3 ; idx++)
			{
				// 法線
				glNormal3f(	m_Parts[nCntParts].data.Nrm[m_Parts[nCntParts].data.Idx[nCntIdx][idx].nrm].x,
							m_Parts[nCntParts].data.Nrm[m_Parts[nCntParts].data.Idx[nCntIdx][idx].nrm].y,
							m_Parts[nCntParts].data.Nrm[m_Parts[nCntParts].data.Idx[nCntIdx][idx].nrm].z);

				// テクスチャ座標
				glTexCoord2d(	m_Parts[nCntParts].data.Tex[m_Parts[nCntParts].data.Idx[nCntIdx][idx].tex].x,
								m_Parts[nCntParts].data.Tex[m_Parts[nCntParts].data.Idx[nCntIdx][idx].tex].y);

				// 座標
				glVertex3f(	m_Parts[nCntParts].data.Pos[m_Parts[nCntParts].data.Idx[nCntIdx][idx].vtx].x,
							m_Parts[nCntParts].data.Pos[m_Parts[nCntParts].data.Idx[nCntIdx][idx].vtx].y,
							m_Parts[nCntParts].data.Pos[m_Parts[nCntParts].data.Idx[nCntIdx][idx].vtx].z);
			}

			glEnd();

		}
		
		glPopMatrix();		// 保存マトリックスの取り出し
	}
}