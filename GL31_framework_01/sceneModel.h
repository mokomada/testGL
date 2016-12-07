#ifndef _SCENEMODEL_H_
#define _SCENEMODEL_H_
//=============================================================================
//
//	タイトル	ヘッダファイル(scene3D.cpp)
//	ファイル名	scene3D.h
//	作成者		AT13A284_07 池田達哉
//	作成日		2016/05/06
//
//=============================================================================
#include "scene3DGL.h"
#include "game.h"

//=============================================================================
//	マクロ定義
//=============================================================================
#define	MODEL_TEXFILENAME000	"miku_01.tga"	// ポリゴンのファイル名
#define	MODEL_MOTION_NUM		(1)				// モーション数
#define	MODEL_POWER				(50.0f)			// モデルのデータ倍率

//=============================================================================
//	構造体
//=============================================================================
// インデックス
typedef struct{
	int	vtx;	// 頂点
	int	tex;	// テクスチャ座標
	int	nrm;	// 法線
} MODEL_INDEX;

// モデル情報
typedef struct{
	VECTOR3		*Pos;	// 座標
	VECTOR3		*Nrm;	// 法線
	VECTOR2		*Tex;	// テクスチャ座標
//	マテリアル
	MODEL_INDEX	**Idx;// インデックス
} MODEL_DATA;

// モデル情報
typedef struct{
	int	Pos;	// 座標
	int	Nrm;	// 法線
	int	Tex;	// テクスチャ座標
	int	Idx;	// インデックス
} MODEL_DATA_NUM;

typedef struct{
	int		Parents;	// 親オブジェクト

	VECTOR3	Pos;		// 位置
	VECTOR3	Rot;		// 回転
	VECTOR3	Move;		// 移動量
	VECTOR3	RotMove;	// 回転量
	MODEL_DATA		data;
	MODEL_DATA_NUM	dataNum;
} PARTS;

typedef struct{
	float	PosX, PosY, PosZ;	// 位置
	float	RotX, RotY, RotZ;	// 回転
} POSE;

typedef struct{
	int		Frame;		// フレーム数
	POSE	**Pose;	// モーションデータ
} MOTION;

//=============================================================================
//	クラス定義
//=============================================================================
class CSceneModel
{
public:
	CSceneModel(int priority = 1, OBJTYPE objType = OBJTYPE_NONE);
	~CSceneModel();

	void	Init(void){}
	void	Init(char* FileName);
	void	Uninit(bool isLast = false);
	void	Update(void);
	void	Draw(void);

	void	LoadModel(char *fileName);
	void	LoadMotion(char *fileName, int nNumMotion);
	void	DrawModel(void);

	static CSceneModel	*Create(char* FileName);
private:
	int		m_Texture;		// テクスチャ
	PARTS	*m_Parts;		// モデル情報
	MOTION	*m_Motion;		// モーション情報
	int		m_nNumParts;	// パーツ数
	VECTOR3	m_Scale;		// スケール

	int		m_Frame;	// モーションカウンタ
	int		m_ExecMotion;	// 実行中のモーション
};

#endif