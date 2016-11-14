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
#include "manager.h"
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
//	構造体
//=============================================================================
typedef struct{
	bool ModelBeing;	// モデルが表示されているか否か
	bool Wireframe;		// ワイヤフレームモード
	bool Culling;		// カリングモード
	bool Texture;		// テクスチャ貼付の有無
	bool Lighting;		// ライティングの有無
	bool Glid;			// グリッドの表示/非表示
	bool XAxis;			// Ｘ軸
	bool YAxis;			// Ｙ軸
	bool ZAxis;			// Ｚ軸
} FLUG;

//=============================================================================
//	前方宣言
//=============================================================================
class CManager;

//=============================================================================
//	プロトタイプ
//=============================================================================
CManager		*GetManager(void);
FLUG			*GetFlug(void);
float			GetZoomPos(void);
float			GetSizePos(void);
char			*ReadBinaryFile(char *filename);
int				SearchWordByString(char *str, unsigned int offset, char *word);
int				SearchWordNumByString(char *str, unsigned int offset, char *word);
int				SearchWordNumByString(char *str, unsigned int offset, char *word, char *endword);
bool			SearchWordByFile(FILE *fp, char *word);

#endif