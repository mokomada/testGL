#ifndef _LIGHTGL_H_
#define _LIGHTGL_H_
//=============================================================================
//
//	タイトル	ヘッダファイル(scene.cpp)
//	ファイル名	scene.h
//	作成者		AT13A284_07 池田達哉
//	作成日		2016/04/19
//
//=============================================================================
#include "main.h"
//=============================================================================
//	マクロ定義
//=============================================================================
#define	LIGHT_NEARZ				(10.0f)			// NearZ値
#define	LIGHT_FARZ					(10000.0f)		// FarZ値
#define	LIGHT_DEFAULT_DISTANCE		(200.0f)		// 初期の視点―注視点間距離

#define	LIGHT_POSV_MOVEMENT		(2.0f)			// 視点の移動速度
#define	LIGHT_POSR_MOVEMENT_X		(0.005f)			// 注視点の移動量(左右)
#define	LIGHT_POSR_MOVEMENT_Y		(2.0f)			// 注視点の移動量(上下)

//=============================================================================
//	構造体
//=============================================================================

//=============================================================================
//	クラス定義
//=============================================================================
class CLightGL
{
public:
	static void	Init(void);
	static void	Uninit(void);
	static void	Update(void);
	static void	Set(void);

private:

};

#endif