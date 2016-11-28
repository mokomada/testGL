//=============================================================================
//
//	タイトル	ヘッダファイル(effect2D.cpp)
//	ファイル名	effect2D.h
//	作成者		AT13A284_20 君島弥範
//	作成日		2016/11/21
//
//=============================================================================
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

/////////////////////
/*   ファイル名    */
/////////////////////
#define	EXPLODE_TEXFILENAME000	"./data/TEXTURE/test.tga"			// 爆発テストエフェクト(4x4)
#define	EXPLODE_TEXFILENAME001	"./data/TEXTURE/explosion000.tga"	// 爆発テストエフェクト(7x1)
#define	NUMBER_TEXFILENAME0000  "./data/TEXTURE/number000.tga"		// 横一列テスト画像(10x1)

/////////////////////////////////
/*   アニメーショングリッド    */
/////////////////////////////////
#define EXPLODE00_X	(4)
#define EXPLODE00_Y	(4)
#define EXPLODE01_X	(7)
#define EXPLODE01_Y	(1)
#define NUMBER_X	(10)
#define NUMBER_Y	(1)

/////////////////
/*   その他    */
/////////////////
#define ANIMATION_CHANGE_FRAME_COUNT	(15)						// アニメーションが切り替わるまでのフレーム数

//=============================================================================
//	構造体定義
//=============================================================================
typedef enum
{
	ETYPE_NONE = 0,	// なし
	ETYPE_EXPLODE00,	// 爆発エフェクト(テスト)
	ETYPE_EXPLODE01,	// 爆発エフェクト
	ETYPE_NUMBER,	// テスト用一列画像
}EFFECTTYPE;

//=============================================================================
//	クラス定義
//=============================================================================
class CEffect2D : public CScene2DGL
{
	public:
		CEffect2D(int priority = 1, OBJTYPE objType = OBJTYPE_NONE);	// コンストラクタ
		~CEffect2D();													// デストラクタ

		void Init(void){}
		void Init(VECTOR3 pos		= VECTOR3(0.0f, 0.0f, 0.0f),			// 初期化処理
				  VECTOR2 size		= VECTOR2(BILLBOARD_WIDTH, BILLBOARD_HEIGHT),
				  EFFECTTYPE etype	= ETYPE_NONE);

		void Uninit(bool isLast = false);							// 終了処理
		void Update(void);											// 更新処理
		void Draw(void);											// 描画処理
		void DrawPolygon(void);										// 描画処理内のDraw部分

		static CEffect2D *Create(VECTOR3 pos = VECTOR3(0.0f, 0.0f, 0.0f),			// 作成関数
								 VECTOR2 size = VECTOR2(BILLBOARD_WIDTH, BILLBOARD_HEIGHT),
								 EFFECTTYPE etype = ETYPE_NONE);
		

	private:
		VECTOR2 m_Size;						// ポリゴンのサイズ
		int		m_Texture;					// テクスチャ
		MATRIX	m_mtxWorld;					// ワールドマトリクス

		/* アニメーション関連 */
		int		m_nAnimX,m_nAnimY;			// 目標アニメーションカウント数
		int		m_nAnimCntX, m_nAnimCntY;	// アニメーションカウンタ
		int		m_nAnimChangeFrameCnt;		// アニメーションの切り変えまでのフレームカウンタ
		bool	m_bEndflug;					// 最終アニメーション表示後自殺するフラグ
};

#endif