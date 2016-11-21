#ifndef _DEBUGPROCGL_H_
#define _DEBUGPROCGL_H_
//=============================================================================
//
//	タイトル	ヘッダファイル
//	ファイル名	debugProcGL.h
//	作成者		AT13A284_07 池田達哉
//	作成日		2016/07/12
//
//=============================================================================
#include "main.h"
#define	DEBUGSTR_MAX	(65535)	// 配列限界
#define	FONT_SIZE		(16)	// フォントサイズ
#define	DEBUGPROC_POSX	(10)	// 文字表示位置のX座標
#define	DEBUGPROC_POSY	(40)	// 文字表示位置のY座標
//=============================================================================
//	クラス定義
//=============================================================================
class CDebugProcGL
{
public:
	static void	Init(void);
	static void	Uninit(void);
	static void	Update(void);
	static void	Draw(void);

	static void DebugProc(wchar_t *format, ...);

private:
	static HDC		m_hDc;
	static HFONT	m_hFont;
	static wchar_t	m_aStrDebug[DEBUGSTR_MAX];	// デバッグ用文字列
};

#endif