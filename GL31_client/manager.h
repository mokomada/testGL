#ifndef _MANAGER_H_
#define _MANAGER_H_
//=============================================================================
//
//	タイトル	ヘッダファイル
//	ファイル名	manager.h
//	作成者		AT13A284_07 池田達哉
//	作成日		2016/05/10
//
//=============================================================================
#include "main.h"
#include "sound.h"
#include "debugProcGL.h"

//=============================================================================
//	マクロ定義
//=============================================================================
#define	SCENE_NUM		(2)		// シーン数

//=============================================================================
//	前方宣言
//=============================================================================
class CMode;
class CRendererGL;
class CSceneGL;
class CCameraGL;
class CLightGL;
class CSceneGL;

//=============================================================================
//	クラス定義
//=============================================================================
class CManager
{
public:
	static void	Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
	static void	Uninit(HWND hWnd);
	static void	Update(void);
	static void	Draw(void);
	
	static CRendererGL	*GetRendererGL(void){ return m_RendererGL; }
	static CCameraGL	*GetCamera(void){ return m_Camera; }

	static CMode		*GetMode(void) { return m_Mode; }
	static int			GetModeState(void) { return m_ModeState; }
	static void			SetWhatPlayer(int playernumber) { m_WhatPlayer = playernumber; }
	static int			GetWhatPlayer(void) { return m_WhatPlayer; }

	static void			SetMode(CMode *mode, int modeState);

	static int	m_Frame;


private:
	static CMode		*m_Mode;		// モードのインスタンス
	static CCameraGL	*m_Camera;		// カメラのインスタンス
	static CRendererGL	*m_RendererGL;	// レンダラ(GL)

	static int	m_ModeState;
	static int	m_WhatPlayer;	// 自分が何Pかどうか
	
	void	LoadScript(char *fileName);
};

#endif