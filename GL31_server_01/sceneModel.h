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
//=============================================================================
//	マクロ定義
//=============================================================================
#define	MODEL_FILENAME000		"car.obj"	// モデルファイルのファイル名
#define	MODEL_TEXFILENAME000	"miku_01.tga"	// ポリゴンのファイル名
#define	MODEL_MOTION_NUM		(1)				// モーション数
#define	MODEL_POWER				(50.0f)			// モデルのデータ倍率

#define	MODEL_POSX		(SCREEN_WIDTH * 0.5f)	// ポリゴンの横幅
#define	MODEL_POSY		(SCREEN_HEIGHT * 0.5f)	// ポリゴンの縦幅
#define	MODEL_SIZE		(30.0f)					// ポリゴンの横幅
#define	MODEL_TURN		(-0.15f)

#define	MODEL_MOVEMENT	(0.5f)					// テクスチャのファイル名
#define	MODEL_ROT_STEP	(8)					// プレイヤーの回転ステップ
#define	GAUGE_MAX		(300.0f)			// プレイヤーのゲージマックス

#define	MODEL_SPEED_DOWN	(0.1f)			// プレイヤーの回転ステップ
#define	MODEL_SPEED_DOWNJ	(0.25f)			// プレイヤーの回転ステップ
#define	PLAYER_JUMP			(10.0f)			// プレイヤーの回転ステップ
#define	PLAYER_GRAVITY		(0.8f)			// プレイヤーの回転ステップ
#define	MOVE_ROT		(0.02f)				// プレイヤーの回転量
#define	MOVE_ROTJ		(0.01f)				// ジャンプ中のプレイヤーの回転量
#define	LOWMOVE_ROT		(0.005f)			// 低速中のプレイヤーの回転量
#define	LOWMOVE_ROTJ	(0.001f)			// 低速中のジャンプ中のプレイヤーの回転量
#define	FMOVE_SPEED		(0.8f)				// プレイヤーの前方移動量
#define	BMOVE_SPEED		(0.4f)				// プレイヤーの後方移動量
#define	LOWBMOVE_SPEED		(0.1f)			// 低速中のプレイヤーの後方移動量
#define	LOWFMOVE_SPEED		(0.2f)			// 低速中のプレイヤーの前方移動量


//=============================================================================
//	構造体
//=============================================================================
// インデックス
typedef struct{
	int	vtx;	// 頂点
	int	tex;	// テクスチャ座標
	int	nrm;	// 法線
	void IdxRight(void) { vtx -= 1; tex -= 1; nrm -= 1; }
} MODEL_INDEX;

// モデル情報
typedef struct{
	vector<VECTOR3>	Vtx;	// 座標
	vector<VECTOR3>	Nrm;	// 法線
	vector<VECTOR2>	Tex;	// テクスチャ座標
//	マテリアル
	vector<vector<MODEL_INDEX>> Idx;// インデックス
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
class CSceneModel : public CScene3DGL
{
public:
	CSceneModel(int priority = 1, OBJTYPE objType = OBJTYPE_NONE);
	~CSceneModel();

	void	Init(void){}
	void	Init(bool ifMinePlayer = false, VECTOR3 pos = VECTOR3(0.0f, 0.0f, 0.0f));
	void	Uninit(bool isLast = false);
	void	Update(void);
	void	Draw(void);

	static CSceneModel	*Create(bool ifMinePlayer = false, VECTOR3 pos = VECTOR3(0.0f, 0.0f, 0.0f));
	
	void	LoadModel(char *fileName);
	void	LoadMotion(char *fileName, int nNumMotion);
	void	DrawModel(void);

	float GetGauge(void) { return m_Gauge; }
	void SetGauge(float Gauge) { m_Gauge = Gauge; }
	bool	m_ifMinePlayer;

	float m_Radius;	//当たり判定の半径

private:
	int		m_Texture;		// テクスチャ
	vector<PARTS>	m_Parts;		// モデル情報
	MOTION	*m_Motion;		// モーション情報
	int		m_nNumParts;	// パーツ数
	VECTOR3	m_Scale;		// スケール
	
	int		m_Frame;	// モーションカウンタ
	int		m_ExecMotion;	// 実行中のモーション
	int		m_nCntMove;		// 回転カウンタ
	VECTOR3	m_Move;			// 移動量
	VECTOR3	m_RotMove;		// 回転量
	VECTOR3 m_MoveDirection;// 移動方向
	bool	m_bJump;		// ジャンプフラグ
	float m_Gauge;
	bool m_FlgLowSpeed;

	void CollisionDetection(void);
};

#endif