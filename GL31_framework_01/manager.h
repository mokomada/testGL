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

//=============================================================================
//	マクロ定義
//=============================================================================
#define	SCENE_NUM		(2)		// シーン数

//=============================================================================
//	前方宣言
//=============================================================================
class CMode;
class CInput;
class CDebugProc;
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
	
	static CInput		*GetInput(void){ return m_Input; }
	static CRendererGL	*GetRendererGL(void){ return m_RendererGL; }
	static CCameraGL	*GetCamera(void){ return m_Camera; }

	static void			SetMode(CMode *mode);

private:
	static CMode		*m_Mode;		// モードのインスタンス
	static CInput		*m_Input;		// 入力のインスタンス
	static CCameraGL	*m_Camera;		// カメラのインスタンス
	static CLightGL		*m_Light;		// ライトのインスタンス
//	static CDebugProc	*m_DebugProc;	// デバッグプロシージャクラス
	static CRendererGL	*m_RendererGL;	// レンダラ(GL)
	
	void	LoadScript(char *fileName);
};

#endif