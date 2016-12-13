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
#include "sceneModel.h"
#include "cameraGL.h"
#include "network.h"
#include "bullet.h"
#include "game.h"
#include "debugProcGL.h"

//=============================================================================
//	関数名	:CScene3D()
//	引数	:無し
//	戻り値	:無し
//	説明	:コンストラクタ。
//=============================================================================
CSceneModel::CSceneModel(bool ifListAdd, int priority, OBJTYPE objType) : CScene3DGL(ifListAdd, priority, objType)
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
void CSceneModel::Init(bool ifMinePlayer, VECTOR3 pos)
{
	CRendererGL	*renderer	= CManager::GetRendererGL();
	
	// 自プレイヤーかどうかセット
	m_ifMinePlayer = ifMinePlayer;

	// 各種初期化
	SetPos(VECTOR3(pos.x, pos.y, pos.z));
	SetRot(VECTOR3(0.0f, 0.0f, 0.0f));
	m_nCntMove		= 0;
	m_Frame	= 0;
	m_ExecMotion	= -1;
	m_Move			= VECTOR3(0.0f, 0.0f, 0.0f);
	m_RotMove		= VECTOR3(0.0f, 0.0f, 0.0f);
	m_MoveDirection = VECTOR3(0.0f, 0.0f, 0.0f);
	m_bJump			= false;
	m_Scale			= VECTOR3(1.0f, 1.0f, 1.0f);
	m_Texture		= 0;
	
	
	m_Texture = renderer->CreateTextureTGA("./data/TEXTURE/"MODEL_TEXFILENAME000);
	LoadModel("./data/MODEL/"MODEL_FILENAME000);

	// モーション生成
	//m_Motion = new MOTION[MODEL_MOTION_NUM];
	//LoadMotion("data/MOTION/miku_01_01.anm", 0);
	//LoadMotion("data/MOTION/miku_01_02.anm", 0);

	m_Gauge = 100.0f;	//ゲージの初期化
	m_FlgLowSpeed = false;
	m_Radius = 30.0f;
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

	// ワールドマトリクスの設定
	glTranslatef(m_Pos.x, m_Pos.y, m_Pos.z);
	glRotatef((GLfloat)(m_Rot.z * 180.0 / PI), 0.0f, 0.0f, 1.0f);	// 回転マトリックスの設定、角度は度数法で
	glRotatef((GLfloat)(m_Rot.y * 180.0 / PI), 0.0f, 1.0f, 0.0f);	// 回転マトリックスの設定、角度は度数法で
	glRotatef((GLfloat)(m_Rot.x * 180.0 / PI), 1.0f, 0.0f, 0.0f);	// 回転マトリックスの設定、角度は度数法で
	//glScalef(m_Scale.x, m_Scale.y, m_Scale.z);

	// 描画処理ここから
	glBindTexture(GL_TEXTURE_2D, m_Texture);

	// 2Dテクスチャ有効化
	glEnable(GL_TEXTURE_2D);
	
	// 深度バッファ有効化
	glEnable(GL_DEPTH_TEST);

	// カリング無効化
	glDisable(GL_CULL_FACE);
	
	// 頂点色設定
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

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

#ifdef _DEBUG
	//CDebugProcGL::DebugProc("chara:(%.2f:%.2f:%.2f)\n", m_Pos.x, m_Pos.y, m_Pos.z);
#endif
}

//=============================================================================
//	関数名	:Create
//	引数	:VECTOR3 pos(初期位置)
//	戻り値	:無し
//	説明	:インスタンス生成を行うと共に、初期位置を設定する。
//=============================================================================
CSceneModel *CSceneModel::Create(bool ifMinePlayer, VECTOR3 pos)
{
	CSceneModel *scene3D;

	scene3D = new CSceneModel;

	scene3D->Init(ifMinePlayer, pos);

	return scene3D;
}

//=============================================================================
//	関数名	:LoadModel
//	引数	:char* filename	->	ファイル名
//	戻り値	:無し
//	説明	:引数で指定したファイル名のモデル情報を読み込む。
//=============================================================================
void CSceneModel::LoadModel(char *fileName)
{
	FILE *fp		= NULL;	// ファイルポインタ
	FILE *fpBuff	= NULL;	// ファイルポインタ

	// ファイルオープン
	fp = fopen(fileName, "r");

	// ファイル終了まで読み込み
	while(!feof(fp))
	{
		char str[65535] = { NULL };
		memset(str, NULL, sizeof(str));

		// 単語を取得
		fscanf(fp, "%s", str);

		if(strcmp(str, "g") == 0)
		{// スプライン制御点を追加

			m_Parts.resize((int)m_Parts.size() + 1);

			m_Parts[m_Parts.size() - 1].Parents = -1;
			m_Parts[m_Parts.size() - 1].Pos		= VEC3_ZERO;
			m_Parts[m_Parts.size() - 1].Rot		= VEC3_ZERO;
			m_Parts[m_Parts.size() - 1].Move	= VEC3_ZERO;
			m_Parts[m_Parts.size() - 1].RotMove	= VEC3_ZERO;
		}
		else if(strcmp(str, "v") == 0)
		{// 頂点座標を追加

			VECTOR3 pos = VEC3_ZERO;

			// データ格納
			fscanf_s(fp, " %f %f %f\n", &pos.x, &pos.y, &pos.z);
			pos *= MODEL_POWER;

			m_Parts[m_Parts.size() - 1].data.Vtx.push_back(pos);
		}
		else if(strcmp(str, "vt") == 0)
		{// テクスチャ座標を追加
			
			VECTOR2 tex = VEC2_ZERO;

			// データ格納
			fscanf_s(fp, " %f %f\n", &tex.x, &tex.y);

			m_Parts[m_Parts.size() - 1].data.Tex.push_back(tex);
		}
		else if(strcmp(str, "vn") == 0)
		{// 法線ベクトルを追加

			VECTOR3 nrm = VEC3_ZERO;

			// データ格納
			fscanf_s(fp, " %f %f %f\n", &nrm.x, &nrm.y, &nrm.z);

			m_Parts[m_Parts.size() - 1].data.Nrm.push_back(nrm);
		}
		else if(strcmp(str, "f") == 0)
		{// インデックスを追加

			// インデックス情報配列生成
			m_Parts[m_Parts.size() - 1].data.Idx.resize(m_Parts[m_Parts.size() - 1].data.Idx.size() + 1);
			
			// データ格納
			int idxArray = m_Parts[m_Parts.size() - 1].data.Idx.size() - 1;

			while(*fp->_ptr != '\n')
			{
				MODEL_INDEX idx = { 0 };

				// インデックスの値を読み込み
				fscanf_s(fp, " %d/%d/%d", &idx.vtx, &idx.tex, &idx.nrm);
				// インデックスの値を補正
				idx.IdxRight();
				if((int)m_Parts.size() >= 2)
				{
					for(int j = 2 ; j <= (int)m_Parts.size() ; j++)
					{
						idx.vtx -= m_Parts[m_Parts.size() - j].data.Vtx.size();
						idx.tex -= m_Parts[m_Parts.size() - j].data.Tex.size();
						idx.nrm -= m_Parts[m_Parts.size() - j].data.Nrm.size();
					}
				}
				// 配列生成
				m_Parts[m_Parts.size() - 1].data.Idx[idxArray].push_back(idx);
			}
		}
	}

	// ファイルクローズ
	fclose(fp);
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
	for(int i = 0 ; i < (int)m_Parts.size() ; i++)
	{
		glPushMatrix();	// マトリクスの退避

		// インデックス数だけ面を描画
		for(int j = 0 ; j < (int)m_Parts[i].data.Idx.size() ; j++)
		{
			// 描画シーケンス開始
			glBegin(GL_TRIANGLES);

			// 面の数を取得
			int size = (int)m_Parts[i].data.Idx[j].size();

			// 面の数だけ頂点データをセット
			for(int idx = 0 ; idx < size ; idx++)
			{
				// 頂点色設定
				glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

				// 法線
				glNormal3f(	m_Parts[i].data.Nrm[m_Parts[i].data.Idx[j][idx].nrm].x,
							m_Parts[i].data.Nrm[m_Parts[i].data.Idx[j][idx].nrm].y,
							m_Parts[i].data.Nrm[m_Parts[i].data.Idx[j][idx].nrm].z);

				// テクスチャ座標
				glTexCoord2d(	m_Parts[i].data.Tex[m_Parts[i].data.Idx[j][idx].tex].x,
								m_Parts[i].data.Tex[m_Parts[i].data.Idx[j][idx].tex].y);

				// 座標
				glVertex3f(	m_Parts[i].data.Vtx[m_Parts[i].data.Idx[j][idx].vtx].x,
							m_Parts[i].data.Vtx[m_Parts[i].data.Idx[j][idx].vtx].y,
							m_Parts[i].data.Vtx[m_Parts[i].data.Idx[j][idx].vtx].z);
			}

			// 描画シーケンス終了
			glEnd();

		}
		
		glPopMatrix();		// 保存マトリックスの取り出し
	}
}