//=============================================================================
//
//	タイトル	ヘッダファイル(effect2D.cpp)
//	ファイル名	effect2D.h
//	作成者		AT13A284_20 君島弥範
//	作成日		2016/11/21
//
//=============================================================================
//	< 更新履歴 >
// 12/05 煙エフェクト追加
// 
//
///////////////////////////////////////////////////////////////////////////////
//=============================================================================
//	マクロ定義
//=============================================================================
#ifndef _EFFECT2D_H_
#define _EFFECT2D_H_

//=============================================================================
//	インクルードヘッダ
//=============================================================================
#include "scene2DGL.h"
#include "manager.h"
#include "rendererGL.h"

//=============================================================================
//	マクロ定義
//=============================================================================
#define	BILLBOARD_WIDTH		(100.0f)				// ポリゴンの横幅
#define	BILLBOARD_HEIGHT	(100.0f)				// ポリゴンの縦幅

/////////////////////////////////
/*   アニメーショングリッド    */
/////////////////////////////////
#define EXPLODE00_X	(8)
#define EXPLODE00_Y	(1)
#define EXPLODE01_X	(7)
#define EXPLODE01_Y	(1)
#define SMOKE00_X	(10)
#define SMOKE00_Y	(1)

/////////////////
/*   その他    */
/////////////////
#define MOVE_SPEED_PSMOKEX	(0.5f)		// 煙パーティクルの移動スピード(Y軸)
#define MOVE_SPEED_PSMOKEY	(0.5f)		// 煙パーティクルの移動スピード(Y軸)
#define PHEIGHT_LIMIT		(400.0f)	// 煙パーティクルの高度制限
#define PUP_SCALE			(0.5f)		// 煙パーティクルの拡大倍率
#define PALPHA_MINUS		(0.0020f)	// 煙パーティクルのα値減算量


////	アニメーションが切り替わるまでのフレーム数
//////////////////////////////////////////////////////////////
#define DEFAULT_ANIMATION_CHANGE_FRAME	(15)	// デフォルト
#define EXPLODE_ANIMATION_CHANGE_FRAME	(5)		// 爆発
#define SMOKE_ANIMATION_CHANGE_FRAME	(2)		// 土煙

//=============================================================================
//	構造体定義
//=============================================================================
typedef enum
{
	ETYPE_NONE = 0,	// なし
	ETYPE_EXPLODE00,	// 爆発エフェクト(白)
	ETYPE_EXPLODE01,	// 爆発エフェクト(赤)
	ETYPE_SMOKE00,		// 土煙エフェクト(ドリフト)
	ETYPE_SMOKE01,		// 煙エフェクト(プレイヤ死亡時)
}EFFECTTYPE;

typedef struct
{
	float Red;
	float Green;
	float Blue;
	float Alpha;
}EFFTEXCOLOR;

//=============================================================================
//	前方定義
//=============================================================================
class CSceneGL;

//=============================================================================
//	クラス定義
//=============================================================================
class CEffect2D : public CScene2DGL
{
	private:
		VECTOR2 m_Size;						// ポリゴンのサイズ
		uint*	m_Texture;					// テクスチャ
		MATRIX	m_mtxWorld;					// ワールドマトリクス

		/* アニメーション関連 */
		int		m_nAnimX,m_nAnimY;			// 目標アニメーションカウント数
		int		m_nAnimCntX, m_nAnimCntY;	// アニメーションカウンタ
		int		m_nAnimChangeFrame;			// アニメーションの切り変えまでのフレーム数
		int		m_nAnimChangeFrameCnt;		// アニメーションの切り変えまでのフレームカウンタ
		EFFECTTYPE m_Etype;					// エフェクトタイプ
		bool	m_bEndFlugE;				// 最終アニメーション表示後自殺するフラグ(エフェクト)
		bool	m_bEndFlugP;				// 最終アニメーション表示後自殺するフラグ(パーティクル)
		EFFTEXCOLOR m_Color;				// 色データ

	public:
		CEffect2D(bool ifListAdd = true, int priority = PRIORITY_EFFECT, OBJTYPE objType = OBJTYPE_NONE);	// コンストラクタ
		~CEffect2D();													// デストラクタ

		void Init(VECTOR3 pos		= VECTOR3(0.0f, 0.0f, 0.0f),			// 初期化処理
				  VECTOR2 size		= VECTOR2(BILLBOARD_WIDTH, BILLBOARD_HEIGHT),
				  EFFECTTYPE etype	= ETYPE_NONE);

		void Uninit(bool isLast = false);							// 終了処理
		void Update(void);											// 更新処理
		void Draw(void);											// 描画処理
		void DrawPolygon(void);										// 描画処理内のDraw部分
		void TypeInit(EFFECTTYPE etype);							// エフェクトタイプ別の初期化処理
		void TypeUpdate(EFFECTTYPE etype);							// エフェクトタイプ別の更新処理
		bool GetEndFlugE(void);										// エンドフラグ取得(通常エフェクト)
		bool GetEndFlugP(void);										// エンドフラグ取得(パーティクルエフェクト)
		void SetEndFlugE(bool flug);								// エンドフラグ変更(通常エフェクト)
		void SetEndFlugP(bool flug);								// エンドフラグ変更(パーティクルエフェクト)
		
		//static float	m_CheckHeight;
		//static bool CheckHeight(CSceneGL *parent);

		static CEffect2D *Create(VECTOR3 pos = VECTOR3(0.0f, 0.0f, 0.0f),			// 作成関数
								 VECTOR2 size = VECTOR2(BILLBOARD_WIDTH, BILLBOARD_HEIGHT),
								 EFFECTTYPE etype = ETYPE_NONE);
};

#endif