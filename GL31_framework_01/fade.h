#ifndef _FADE_H_
#define _FADE_H_
//=============================================================================
//
//	タイトル	ヘッダファイル
//	ファイル名	fade.h
//	作成者		AT13A284_07 池田達哉
//	作成日		2016/11/14
//
//=============================================================================
#include "rendererGL.h"
class CMode;
class CScene2DGL;

//=============================================================================
//	マクロ定義
//=============================================================================
#define	FADE_CLOSETIME	(60)		// フェードの閉じている時間
#define	FADE_TIME		(60)		// フェードの時間

//=============================================================================
//	構造体
//=============================================================================
typedef enum{
	FS_NONE = 0,// 何もしていない
	FS_FIRST,	// 初期フェード
	FS_IN,		// フェードイン
	FS_OUT,		// フェードアウト
	FS_MAX		// フェード数
}FADE_STATE;

//=============================================================================
//	クラス定義
//=============================================================================
class CFade
{
public:
	static void	Init(void);
	static void	Uninit(void);
	static void	Update(void);
	static void	Draw(void);

	static void			Start(CMode *nextMode, FADE_STATE fadeState = FS_OUT);

private:
	static CMode		*m_NextMode;
	static FADE_STATE	m_FadeState;
	static int			m_FadeTime;		// フェードの時間

	static float		m_Alpha;
};


#endif