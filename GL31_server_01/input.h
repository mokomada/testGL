#ifndef _INPUT_H_
#define _INPUT_H_
//=============================================================================
//
//	タイトル	ヘッダファイル
//	ファイル名	input.h
//	作成者		AT13A284_07 池田達哉
//	作成日		2016/04/26
//
//=============================================================================
#include "d3dx9.h"
#define DIRECTINPUT_VERSION	(0x0800)
#include "dinput.h"

//=============================================================================
//	リンク
//=============================================================================
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dinput8.lib")

//=============================================================================
//	マクロ定義
//=============================================================================
#define KEYSTATE_NUM			(256)	// キー情報の個数

#define REPEAT_TIME				(20)	// リピートまでの時間(ミリ秒)

#define REPEAT_INTERVAL_NORMAL	(1)	// 通常のリピート速度
#define REPEAT_INTERVAL_PAUSE	(10)	// ポーズ時のリピート速度

//=============================================================================
//	構造体
//=============================================================================

//=============================================================================
//	クラス定義
//=============================================================================
class CInput
{
public:
	CInput();
	~CInput();

	static HRESULT	InitInput(HINSTANCE hInstance, HWND hWnd);
	static void	UninitInput(void);
	static void	UpdateInput(void);

	static HRESULT	InitKeyboard(HINSTANCE hInstance, HWND hWnd);
	static void	UpdateKeyboard(void);
	static void	UninitKeyboard(void);
	static void	SetRepeatInterval(int nRepeatInterval){ m_nRepeatInterval = nRepeatInterval; }

	static bool	GetKeyboardPress(int nKey){ return (m_aKeyState[nKey] & 0x80) ? true : false; }
	static bool	GetKeyboardTrigger(int nKey){ return (m_aKeyStateTrigger[nKey] & 0x80) ? true : false; }
	static bool	GetKeyboardRelease(int nKey){ return (m_aKeyStateRelease[nKey] & 0x80) ? true : false; }
	static bool	GetKeyboardRepeat(int nKey){ return (m_aKeyStateRepeat[nKey] & 0x80) ? true : false; }

	static bool	GKP(int nKey){ return (m_aKeyState[nKey] & 0x80) ? true : false; }
	static bool	GKT(int nKey){ return (m_aKeyStateTrigger[nKey] & 0x80) ? true : false; }
	static bool	GKR(int nKey){ return (m_aKeyStateRelease[nKey] & 0x80) ? true : false; }
	static bool	GKRp(int nKey){ return (m_aKeyStateRepeat[nKey] & 0x80) ? true : false; }

private:
	static LPDIRECTINPUT8		m_pInput;				// DirectInputオブジェクトへのポインタ
	static LPDIRECTINPUTDEVICE8	m_pDevKeyboard;			// 入力3Dデバイス(キーボード)へのポインタ

	static BYTE	m_aKeyState[KEYSTATE_NUM];				// キーボードの入力情報ワーク
	static BYTE	m_aKeyStateTrigger[KEYSTATE_NUM];		// キーボードのトリガ情報
	static BYTE	m_aKeyStateRelease[KEYSTATE_NUM];		// キーボードのリリース情報
	static BYTE	m_aKeyStateRepeat[KEYSTATE_NUM];		// キーボードのリピート情報

	static int	m_aKeyStateRepeatCount[KEYSTATE_NUM];	// キーボードのリピートカウント
	static int	m_nRepeatInterval;						// リピート間隔

};

//=============================================================================
//	マクロ定義
//=============================================================================
class CInputPress
{
public:
	#define	KH_A		(CInput::GetKeyboardPress(DIK_A))
	#define	KH_B		(CInput::GetKeyboardPress(DIK_B))
	#define	KH_C		(CInput::GetKeyboardPress(DIK_C))
	#define	KH_D		(CInput::GetKeyboardPress(DIK_D))
	#define	KH_E		(CInput::GetKeyboardPress(DIK_E))
	#define	KH_F		(CInput::GetKeyboardPress(DIK_F))
	#define	KH_G		(CInput::GetKeyboardPress(DIK_G))
	#define	KH_H		(CInput::GetKeyboardPress(DIK_H))
	#define	KH_I		(CInput::GetKeyboardPress(DIK_I))
	#define	KH_J		(CInput::GetKeyboardPress(DIK_J))
	#define	KH_K		(CInput::GetKeyboardPress(DIK_K))
	#define	KH_L		(CInput::GetKeyboardPress(DIK_L))
	#define	KH_M		(CInput::GetKeyboardPress(DIK_M))
	#define	KH_N		(CInput::GetKeyboardPress(DIK_N))
	#define	KH_O		(CInput::GetKeyboardPress(DIK_O))
	#define	KH_P		(CInput::GetKeyboardPress(DIK_P))
	#define	KH_Q		(CInput::GetKeyboardPress(DIK_Q))
	#define	KH_R		(CInput::GetKeyboardPress(DIK_R))
	#define	KH_S		(CInput::GetKeyboardPress(DIK_S))
	#define	KH_T		(CInput::GetKeyboardPress(DIK_T))
	#define	KH_U		(CInput::GetKeyboardPress(DIK_U))
	#define	KH_V		(CInput::GetKeyboardPress(DIK_V))
	#define	KH_W		(CInput::GetKeyboardPress(DIK_W))
	#define	KH_X		(CInput::GetKeyboardPress(DIK_X))
	#define	KH_Y		(CInput::GetKeyboardPress(DIK_Y))
	#define	KH_Z		(CInput::GetKeyboardPress(DIK_Z))
	#define	KH_1		(CInput::GetKeyboardPress(DIK_1))
	#define	KH_2		(CInput::GetKeyboardPress(DIK_2))
	#define	KH_3		(CInput::GetKeyboardPress(DIK_3))
	#define	KH_4		(CInput::GetKeyboardPress(DIK_4))
	#define	KH_5		(CInput::GetKeyboardPress(DIK_5))
	#define	KH_6		(CInput::GetKeyboardPress(DIK_6))
	#define	KH_7		(CInput::GetKeyboardPress(DIK_7))
	#define	KH_8		(CInput::GetKeyboardPress(DIK_8))
	#define	KH_9		(CInput::GetKeyboardPress(DIK_9))
	#define	KH_0		(CInput::GetKeyboardPress(DIK_0))
	#define	KH_UP		(CInput::GetKeyboardPress(DIK_UP))
	#define	KH_DOWN		(CInput::GetKeyboardPress(DIK_DOWN))
	#define	KH_LEFT		(CInput::GetKeyboardPress(DIK_LEFT))
	#define	KH_RIGHT	(CInput::GetKeyboardPress(DIK_RIGHT))
	#define	KH_ENTER	(CInput::GetKeyboardPress(DIK_RETURN))
	#define	KH_SPACE	(CInput::GetKeyboardPress(DIK_SPACE))
};

class CInputTrigger
{
public:
	#define	KT_A		(CInput::GetKeyboardTrigger(DIK_A))
	#define	KT_B		(CInput::GetKeyboardTrigger(DIK_B))
	#define	KT_C		(CInput::GetKeyboardTrigger(DIK_C))
	#define	KT_D		(CInput::GetKeyboardTrigger(DIK_D))
	#define	KT_E		(CInput::GetKeyboardTrigger(DIK_E))
	#define	KT_F		(CInput::GetKeyboardTrigger(DIK_F))
	#define	KT_G		(CInput::GetKeyboardTrigger(DIK_G))
	#define	KT_H		(CInput::GetKeyboardTrigger(DIK_H))
	#define	KT_I		(CInput::GetKeyboardTrigger(DIK_I))
	#define	KT_J		(CInput::GetKeyboardTrigger(DIK_J))
	#define	KT_K		(CInput::GetKeyboardTrigger(DIK_K))
	#define	KT_L		(CInput::GetKeyboardTrigger(DIK_L))
	#define	KT_M		(CInput::GetKeyboardTrigger(DIK_M))
	#define	KT_N		(CInput::GetKeyboardTrigger(DIK_N))
	#define	KT_O		(CInput::GetKeyboardTrigger(DIK_O))
	#define	KT_P		(CInput::GetKeyboardTrigger(DIK_P))
	#define	KT_Q		(CInput::GetKeyboardTrigger(DIK_Q))
	#define	KT_R		(CInput::GetKeyboardTrigger(DIK_R))
	#define	KT_S		(CInput::GetKeyboardTrigger(DIK_S))
	#define	KT_T		(CInput::GetKeyboardTrigger(DIK_T))
	#define	KT_U		(CInput::GetKeyboardTrigger(DIK_U))
	#define	KT_V		(CInput::GetKeyboardTrigger(DIK_V))
	#define	KT_W		(CInput::GetKeyboardTrigger(DIK_W))
	#define	KT_X		(CInput::GetKeyboardTrigger(DIK_X))
	#define	KT_Y		(CInput::GetKeyboardTrigger(DIK_Y))
	#define	KT_Z		(CInput::GetKeyboardTrigger(DIK_Z))
	#define	KT_1		(CInput::GetKeyboardTrigger(DIK_1))
	#define	KT_2		(CInput::GetKeyboardTrigger(DIK_2))
	#define	KT_3		(CInput::GetKeyboardTrigger(DIK_3))
	#define	KT_4		(CInput::GetKeyboardTrigger(DIK_4))
	#define	KT_5		(CInput::GetKeyboardTrigger(DIK_5))
	#define	KT_6		(CInput::GetKeyboardTrigger(DIK_6))
	#define	KT_7		(CInput::GetKeyboardTrigger(DIK_7))
	#define	KT_8		(CInput::GetKeyboardTrigger(DIK_8))
	#define	KT_9		(CInput::GetKeyboardTrigger(DIK_9))
	#define	KT_0		(CInput::GetKeyboardTrigger(DIK_0))
	#define	KT_UP		(CInput::GetKeyboardTrigger(DIK_UP))
	#define	KT_DOWN		(CInput::GetKeyboardTrigger(DIK_DOWN))
	#define	KT_LEFT		(CInput::GetKeyboardTrigger(DIK_LEFT))
	#define	KT_RIGHT	(CInput::GetKeyboardTrigger(DIK_RIGHT))
	#define	KT_ENTER	(CInput::GetKeyboardTrigger(DIK_RETURN))
	#define	KT_SPACE	(CInput::GetKeyboardTrigger(DIK_SPACE))
};

class CInputRelease
{
public:
	#define	KR_A		(CInput::GetKeyboardRelease(DIK_A))
	#define	KR_B		(CInput::GetKeyboardRelease(DIK_B))
	#define	KR_C		(CInput::GetKeyboardRelease(DIK_C))
	#define	KR_D		(CInput::GetKeyboardRelease(DIK_D))
	#define	KR_E		(CInput::GetKeyboardRelease(DIK_E))
	#define	KR_F		(CInput::GetKeyboardRelease(DIK_F))
	#define	KR_G		(CInput::GetKeyboardRelease(DIK_G))
	#define	KR_H		(CInput::GetKeyboardRelease(DIK_H))
	#define	KR_I		(CInput::GetKeyboardRelease(DIK_I))
	#define	KR_J		(CInput::GetKeyboardRelease(DIK_J))
	#define	KR_K		(CInput::GetKeyboardRelease(DIK_K))
	#define	KR_L		(CInput::GetKeyboardRelease(DIK_L))
	#define	KR_M		(CInput::GetKeyboardRelease(DIK_M))
	#define	KR_N		(CInput::GetKeyboardRelease(DIK_N))
	#define	KR_O		(CInput::GetKeyboardRelease(DIK_O))
	#define	KR_P		(CInput::GetKeyboardRelease(DIK_P))
	#define	KR_Q		(CInput::GetKeyboardRelease(DIK_Q))
	#define	KR_R		(CInput::GetKeyboardRelease(DIK_R))
	#define	KR_S		(CInput::GetKeyboardRelease(DIK_S))
	#define	KR_T		(CInput::GetKeyboardRelease(DIK_T))
	#define	KR_U		(CInput::GetKeyboardRelease(DIK_U))
	#define	KR_V		(CInput::GetKeyboardRelease(DIK_V))
	#define	KR_W		(CInput::GetKeyboardRelease(DIK_W))
	#define	KR_X		(CInput::GetKeyboardRelease(DIK_X))
	#define	KR_Y		(CInput::GetKeyboardRelease(DIK_Y))
	#define	KR_Z		(CInput::GetKeyboardRelease(DIK_Z))
	#define	KR_1		(CInput::GetKeyboardRelease(DIK_1))
	#define	KR_2		(CInput::GetKeyboardRelease(DIK_2))
	#define	KR_3		(CInput::GetKeyboardRelease(DIK_3))
	#define	KR_4		(CInput::GetKeyboardRelease(DIK_4))
	#define	KR_5		(CInput::GetKeyboardRelease(DIK_5))
	#define	KR_6		(CInput::GetKeyboardRelease(DIK_6))
	#define	KR_7		(CInput::GetKeyboardRelease(DIK_7))
	#define	KR_8		(CInput::GetKeyboardRelease(DIK_8))
	#define	KR_9		(CInput::GetKeyboardRelease(DIK_9))
	#define	KR_0		(CInput::GetKeyboardRelease(DIK_0))
	#define	KR_UP		(CInput::GetKeyboardRelease(DIK_UP))
	#define	KR_DOWN		(CInput::GetKeyboardRelease(DIK_DOWN))
	#define	KR_LEFT		(CInput::GetKeyboardRelease(DIK_LEFT))
	#define	KR_RIGHT	(CInput::GetKeyboardRelease(DIK_RIGHT))
	#define	KR_ENTER	(CInput::GetKeyboardRelease(DIK_RETURN))
};

class CInputRepeat
{
public:
	#define	KRP_A		(CInput::GetKeyboardRepeat(DIK_A))
	#define	KRP_B		(CInput::GetKeyboardRepeat(DIK_B))
	#define	KRP_C		(CInput::GetKeyboardRepeat(DIK_C))
	#define	KRP_D		(CInput::GetKeyboardRepeat(DIK_D))
	#define	KRP_E		(CInput::GetKeyboardRepeat(DIK_E))
	#define	KRP_F		(CInput::GetKeyboardRepeat(DIK_F))
	#define	KRP_G		(CInput::GetKeyboardRepeat(DIK_G))
	#define	KRP_H		(CInput::GetKeyboardRepeat(DIK_H))
	#define	KRP_I		(CInput::GetKeyboardRepeat(DIK_I))
	#define	KRP_J		(CInput::GetKeyboardRepeat(DIK_J))
	#define	KRP_K		(CInput::GetKeyboardRepeat(DIK_K))
	#define	KRP_L		(CInput::GetKeyboardRepeat(DIK_L))
	#define	KRP_M		(CInput::GetKeyboardRepeat(DIK_M))
	#define	KRP_N		(CInput::GetKeyboardRepeat(DIK_N))
	#define	KRP_O		(CInput::GetKeyboardRepeat(DIK_O))
	#define	KRP_P		(CInput::GetKeyboardRepeat(DIK_P))
	#define	KRP_Q		(CInput::GetKeyboardRepeat(DIK_Q))
	#define	KRP_R		(CInput::GetKeyboardRepeat(DIK_R))
	#define	KRP_S		(CInput::GetKeyboardRepeat(DIK_S))
	#define	KRP_T		(CInput::GetKeyboardRepeat(DIK_T))
	#define	KRP_U		(CInput::GetKeyboardRepeat(DIK_U))
	#define	KRP_V		(CInput::GetKeyboardRepeat(DIK_V))
	#define	KRP_W		(CInput::GetKeyboardRepeat(DIK_W))
	#define	KRP_X		(CInput::GetKeyboardRepeat(DIK_X))
	#define	KRP_Y		(CInput::GetKeyboardRepeat(DIK_Y))
	#define	KRP_Z		(CInput::GetKeyboardRepeat(DIK_Z))
	#define	KRP_1		(CInput::GetKeyboardRepeat(DIK_1))
	#define	KRP_2		(CInput::GetKeyboardRepeat(DIK_2))
	#define	KRP_3		(CInput::GetKeyboardRepeat(DIK_3))
	#define	KRP_4		(CInput::GetKeyboardRepeat(DIK_4))
	#define	KRP_5		(CInput::GetKeyboardRepeat(DIK_5))
	#define	KRP_6		(CInput::GetKeyboardRepeat(DIK_6))
	#define	KRP_7		(CInput::GetKeyboardRepeat(DIK_7))
	#define	KRP_8		(CInput::GetKeyboardRepeat(DIK_8))
	#define	KRP_9		(CInput::GetKeyboardRepeat(DIK_9))
	#define	KRP_0		(CInput::GetKeyboardRepeat(DIK_0))
	#define	KRP_UP		(CInput::GetKeyboardRepeat(DIK_UP))
	#define	KRP_DOWN	(CInput::GetKeyboardRepeat(DIK_DOWN))
	#define	KRP_LEFT	(CInput::GetKeyboardRepeat(DIK_LEFT))
	#define	KRP_RIGHT	(CInput::GetKeyboardRepeat(DIK_RIGHT))
	#define	KRP_ENTER	(CInput::GetKeyboardRepeat(DIK_RETURN))
};

#endif