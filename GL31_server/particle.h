//=============================================================================
//
//	タイトル	ヘッダファイル(Particle.h)
//	ファイル名	Particle.h
//	作成者		AT13A284_20 君島弥範
//	作成日		2016/12/13
//
//=============================================================================
//=============================================================================
//	マクロ定義
//=============================================================================
#ifndef _PARTICLE_H_
#define _PARTICLE_H_

//=============================================================================
//	インクルードヘッダ
//=============================================================================
#include "scene2DGL.h"
#include "manager.h"
#include "rendererGL.h"
#include "effect2D.h"

//=============================================================================
//	マクロ定義
//=============================================================================
#define MAX_PARTICLE		(1000)		// パーティクルの最大数		
#define GENERATE_TIME		(60)		// 発生間隔
#define LIFE				(1000)		// 最大発生数(この数を作ったら消滅)
#define	PARTICLE_WIDTH		(100.0f)	// ポリゴンの横幅
#define	PARTICLE_HEIGHT		(100.0f)	// ポリゴンの縦幅

//=============================================================================
//	構造体定義
//=============================================================================
typedef enum
{
	PARTICLE_NONE = 0,	// なし
	PARTICLE_EXPLODE,	// 爆発エフェクト
	PARTICLE_SMOKE,		// 煙
}PARTICLE_TYPE;

typedef struct 
{
	MATRIX	m_mtxWorld;					// ワールドマトリクス
	VECTOR3 pos;						// 初期位置
	VECTOR2 move;						// 移動方向&速度
	VECTOR2 m_Size;						// ポリゴンのサイズ
	int nGenerateTime;					// 発生タイマカウンタ
	int nLife;							// 寿命
	PARTICLE_TYPE pType;				// パーティクルのタイプ
}PARTICLE;


//=============================================================================
//	クラス定義
//=============================================================================
class CParticle
{
	private:
		PARTICLE m_Particle;
		CSceneGL* m_Parent;

	public:
		CParticle(PRIORITY priority = PRIORITY_NONE, OBJTYPE objType = OBJTYPE_NONE);				// コンストラクタ
		~CParticle();																				// デストラクタ
		void Init(VECTOR3 pos,VECTOR2 size,PARTICLE_TYPE pType,CSceneGL *parent);					// 初期化処理
		void Uninit();																				// 終了処理
		void Update(void);																			// 更新処理
		void Draw(void);																			// 描画処理
		static CParticle *Create(VECTOR3 pos,VECTOR2 size,PARTICLE_TYPE pType,CSceneGL *parent);	// 作成関数
};

#endif