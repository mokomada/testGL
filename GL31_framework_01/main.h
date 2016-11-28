#ifndef _MAIN_H_
#define _MAIN_H_
//=============================================================================
//
//	タイトル ヘッダファイル(main.cpp)
//	ファイル名 main.h
//	作成者 AT13A284_07 池田達哉
//	作成日 2016/04/14
//
//=============================================================================
#define _CRT_SECURE_NO_WARNINGS
//=============================================================================
//	インクルード
//=============================================================================
#include <stdio.h>
#include <windows.h>
#include <math.h>
#include "vector.h"
#include "matrix.h"
#include "input.h"
#include "readfile.h"
//#include "singleton.h"

//=============================================================================
//	リンク
//=============================================================================
#pragma comment(lib, "winmm.lib")

//=============================================================================
//	マクロ定義
//=============================================================================
#define	CHANGE_SIZE			(5)			// 
#define	SCREEN_WIDTH		(1280.0f * 0.85f)		// ウィンドウの横幅
#define	SCREEN_HEIGHT		(760.0f * 0.85f)		// ウィンドウの縦幅
#define	SCREEN_WIDTH_HALF	(SCREEN_WIDTH * 0.5f)	// ウィンドウの横幅(半分)
#define	SCREEN_HEIGHT_HALF	(SCREEN_HEIGHT * 0.5f)	// ウィンドウの縦幅(半分)
#define	PI					(3.14159265f)			// 円周率

typedef unsigned char uchar;	// unsigned char短縮
typedef unsigned int uint;		// unsigned int短縮

//=============================================================================
//	前方宣言
//=============================================================================
class CManager;

//=============================================================================
//	プロトタイプ
//=============================================================================
float GetFPS(void);

// インスタンス削除関数
template <class INSTANCE>
void SafetyRelease(INSTANCE instance)
{
	if(instance != NULL)
	{
		instance->Release();
		instance = NULL;
	}
}

// インスタンス削除関数(自作クラス版)
template <class INSTANCE>
void SafetyUninit(INSTANCE instance)
{
	if(instance != NULL)
	{
		instance->Uninit();
		delete instance;
		instance = NULL;
	}
}

// データ交換関数
template <class SWAPDATA>
void SwapData(SWAPDATA &data1, SWAPDATA &data2)
{
	SWAPDATA dataBuff;
	dataBuff = data1;
	data1 = data2;
	data2 = dataBuff;
}

// データニ乗関数
template <class POWDATA>
POWDATA PowData(POWDATA data)
{
	return data * data;
}

#endif