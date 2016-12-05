/*******************************************************************************
* タイトル デバッグ情報描画
* ファイル名 debugProc.cpp
* 作成者 AT-12C-245 秋間雄太
* 作成日 2015/11/26
*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "debugProc.h"
#include "camera.h"
#include "renderer.h"
#include "manager.h"

/*******************************************************************************
* 構造体定義
*******************************************************************************/


/*******************************************************************************
* グローバル変数
*******************************************************************************/

LPD3DXFONT g_pFont = NULL; //フォントへのポインタ
char g_aStrDebug[DEBUGPROC_MAX_CHAR_NUM]; // 文字列格納用
int count_strdebug; // g_aStrDebugの配列番号

/*******************************************************************************
* 関数名：InitDebugProc
* 引数：なし
* 戻り値：なし
* 説明：デバッグ情報の初期化
*******************************************************************************/

HRESULT InitDebugProc(void) {
	CRenderer *renderer;
	renderer = CManager::GetRenderer( );
	LPDIRECT3DDEVICE9 pDevice = renderer -> GetDevice( ); // デバイス取得

	// フォントの初期設定
	D3DXCreateFont(pDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &g_pFont);
	memset(g_aStrDebug, 0, sizeof g_aStrDebug);

	for(int i = 0; i < count_strdebug; i++) {
		g_aStrDebug[i] = '\0';
	}

	count_strdebug = 0;

	return S_OK;
}


/*******************************************************************************
* 関数名：UninitDebugProc
* 引数：なし
* 戻り値：なし
* 説明：デバッグ情報の終了処理
*******************************************************************************/

void UninitDebugProc(void) {
	if(g_pFont != NULL) {
		g_pFont -> Release( ); // フォントの開放
		g_pFont = NULL;
	}
}


/*******************************************************************************
* 関数名：UpdateDebugProc
* 引数：なし
* 戻り値：なし
* 説明：デバッグ情報の更新処理
*******************************************************************************/

void UpdateDebugProc(void) {

}


/*******************************************************************************
* 関数名：DrawDebugProc
* 引数：なし
* 戻り値：なし
* 説明：デバッグ情報の描画処理
*******************************************************************************/

void DrawDebugProc(void) {
#ifdef _DEBUG
	RECT rect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

	char ia[256] = "\n";

	strcat(g_aStrDebug, ia);
	_itoa_s(count_strdebug, ia, 10);
	strcat(g_aStrDebug, ia);

	g_pFont -> DrawText(NULL, &g_aStrDebug[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255) );
	count_strdebug = 0;
	memset(g_aStrDebug, 0, sizeof g_aStrDebug);
#endif
}


/*******************************************************************************
* 関数名：PrintDebugProc
* 引数：描画する文字列と変数
* 戻り値：なし
* 説明：デバッグ情報の描画処理
*******************************************************************************/

void PrintDebugProc(char *fmt, ...) {
#ifdef _DEBUG
	// 変数の宣言
	int d, count_f;
	double f;
	char ia[256], c;

	va_list dpList; // listを用意

	va_start(dpList, fmt); // listの初期化

	while(*fmt) {
		// %の場合変数読み込み
		if(*fmt == '%') {
			*fmt++;
			switch(*fmt) {
			case 'd':
				d = va_arg(dpList, int);
				_itoa_s(d, ia, 10);
				strcat(g_aStrDebug, ia);
				while(d) {
					d /= 10;
					count_strdebug++;
				}
				break;
			case 'f':
				// 整数部分の処理
				f = va_arg(dpList, double); // va_argはfloat未対応のためdoubleを使う
				// 整数部分取り出し
				d = (int)f;
				_itoa_s(d, ia, 10);
				// 正の値の時は半角スペースを加えてプラスマイナスで表示がズレないようにする
				if(d >= 0) {
					strcat(g_aStrDebug, " ");
				}
				// 桁合わせ。1桁や2桁の場合はスペースを挿入して表示がズレないようにする
				for(count_f = 100; count_f > 1; count_f /= 10) {
					if(d / count_f == 0) {
						strcat(g_aStrDebug, " ");
					}
				}
				// 3桁表示するので+3
				count_strdebug += 3;
				strcat(g_aStrDebug, ia);

				// 小数点以下の処理
				// 小数点＋小数点以下3桁表示するので+4
				count_strdebug += 4;
				f -= (int)f;
				f *= 1000;
				d = abs( (int)f);
				_itoa_s(d, ia, 10);
				// 小数点表示
				strcat(g_aStrDebug, ".");
				// 小数点以下表示
				strcat(g_aStrDebug, ia);
				// 桁合わせ。3桁分数値がない場合は0で埋める
				if(d < 100) {
					strcat(g_aStrDebug, "0");
				}
				if(d < 10) {
					strcat(g_aStrDebug, "0");
				}
/*				for(count_f = 0; count_f < 3; count_f++) {
					if(d % 10 == 0) {
						strcat(g_aStrDebug, "0");
					}
					d /= 10;
				}*/
				break;
			case 'c':
				c = (char)va_arg(dpList, int);
				strcat(g_aStrDebug, &c);
				break;
			default:
				break;
			}
		}
		else {
			// %以外の文字列はそのまま格納
			g_aStrDebug[count_strdebug] = *fmt;
		}
		// 次の文字へ
		*fmt++;
		count_strdebug++;
	}

	// 最後に\0を挿入
	g_aStrDebug[count_strdebug] = '\0';

	va_end(dpList);
#endif
}