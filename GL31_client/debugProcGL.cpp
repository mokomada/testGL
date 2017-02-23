//=============================================================================
//
//	タイトル	タイトル処理
//	ファイル名	debugProcGL.cpp
//	作成者		AT13A284_07 池田達哉
//	作成日		2016/07/12
//
//=============================================================================
//=============================================================================
//	インクルード
//=============================================================================
#include "debugProcGL.h"
#include <gl/glut.h>
#include <vector>
#include <mbstring.h>

//=============================================================================
//	静的メンバ変数
//=============================================================================
HDC		CDebugProcGL::m_hDc;
HFONT	CDebugProcGL::m_hFont;
char	CDebugProcGL::m_aStrDebug[DEBUGSTR_MAX];

//=============================================================================
//	関数名	:Init
//	引数	:無し
//	戻り値	:無し
//	説明	:初期化処理を行う。
//=============================================================================
void CDebugProcGL::Init(void)
{
	m_hFont = CreateFontW(
		FONT_SIZE,					//フォント高さ
		0,							//文字幅
		0,							//テキストの角度
		0,							//ベースラインとｘ軸との角度
		FW_REGULAR,					//フォントの太さ
		FALSE,						//イタリック体
		FALSE,						//アンダーライン
		FALSE,						//打ち消し線
		SHIFTJIS_CHARSET,			//文字セット
		OUT_DEFAULT_PRECIS,			//出力精度
		CLIP_DEFAULT_PRECIS,		//クリッピング精度
		ANTIALIASED_QUALITY,		//出力品質
		FIXED_PITCH | FF_MODERN,	//ピッチとファミリー
		L"ＭＳ明朝");				//書体名

	m_hDc = wglGetCurrentDC();
	SelectObject(m_hDc, m_hFont);
}

//=============================================================================
//	関数名	:Uninit
//	引数	:無し
//	戻り値	:無し
//	説明	:終了処理を行う。
//=============================================================================
void CDebugProcGL::Uninit(void)
{
	// フォント破棄。 
	DeleteObject(m_hFont);
}

//=============================================================================
//	関数名	:Update
//	引数	:無し
//	戻り値	:無し
//	説明	:更新処理を行う。
//=============================================================================
void CDebugProcGL::Update(void)
{

}

//=============================================================================
//	関数名	:Draw
//	引数	:無し
//	戻り値	:無し
//	説明	:描画処理を行う。
//=============================================================================
void CDebugProcGL::Draw(void)
{
	int Length = 0;
	int list = 0;
	std::vector<int> parag;					// 改行情報
	std::vector<int>::iterator itrParag;	// イテレータ
	std::vector<int> bytelen;				// バイト長情報
	std::vector<int>::iterator itrBytelen;	// イテレータ
	VECTOR2 pos = VECTOR2(DEBUGPROC_POSX, DEBUGPROC_POSY);	// 文字表示位置

	// モデルビューマトリックスの設定(投影変換)
	glMatrixMode(GL_PROJECTION);
	// マトリックスの保存
	glPushMatrix();
	// 変換行列の初期化
	glLoadIdentity();

	// 平行射影or正射影
	glOrtho(0, (GLdouble)SCREEN_WIDTH, (GLdouble)SCREEN_HEIGHT, 0, -100.0, 100.0);
	// ワールド座標系の表示領域を，ビューポートの大きさに比例させる

	// モデルビューマトリックスの設定
	glMatrixMode(GL_MODELVIEW);
	// マトリックスの保存
	glPushMatrix();
	// 変換行列の初期化
	glLoadIdentity();

	Length = strlen(m_aStrDebug);
	list = glGenLists(Length);

	

	// ビットマップイメージ使用箇所指定
	for(int i = 0; i < Length; i++)
	{
		// 改行判定
		if(m_aStrDebug[i] == (wchar_t)10)
		{
			// 改行位置の記録
			parag.push_back(i);
		}

		bytelen.push_back((((int)m_aStrDebug[i] < 1000) ? 1 : 2));

		wglUseFontBitmapsW(m_hDc, m_aStrDebug[i], 1, list + (DWORD)i);
	}

	glPushAttrib(GL_ENABLE_BIT);
	glDisable(GL_LIGHTING);

	// 文字色設定
	glColor3f(0.0f, 0.0f, 0.0f);

	itrBytelen = bytelen.begin();

	//ディスプレイリストで描画
	for(int i = 0 ; i < Length ; i++)
	{
		// 改行の追加
		for(itrParag = parag.begin() ; itrParag != parag.end() ; itrParag++)
		{
			if(*itrParag == i)
			{
				pos.y += FONT_SIZE;
				pos.x = DEBUGPROC_POSX;
				pos.x -= (float)FONT_SIZE * 0.5f;
			}
		}

		// 座標指定
		glRasterPos2i((int)pos.x, (int)pos.y);

		// ディスプレイリスト実行
		glCallList(list + i);

		// 文字間隔調整
		pos.x += (*itrBytelen == 1) ? (FONT_SIZE * 0.5f) : FONT_SIZE;

		// イテレータを進める
		itrBytelen++;
	}

	glEnable(GL_LIGHTING);

	//ディスプレイリスト破棄
	glDeleteLists(list, Length);

	list = 0;
	Length = 0;

	// モデルビューマトリックスの設定(投影変換)
	glMatrixMode(GL_PROJECTION);
	// 保存マトリックスの取り出し
	glPopMatrix();

	// モデルビューマトリックスの設定
	glMatrixMode(GL_MODELVIEW);
	// 保存マトリックスの取り出し
	glPopMatrix();

	glPopAttrib();
	
	// メモリ初期化
	memset(m_aStrDebug, 0, sizeof(m_aStrDebug));
}

//=============================================================================
//	関数名	:DrawStringW
//	引数	:無し
//	戻り値	:無し
//	説明	:文字列を描画する。
//=============================================================================
void CDebugProcGL::DebugProc(char* format, ...)
{
	va_list list;
	char str[65535];

	va_start(list, format);

	vsprintf_s(str, format, list);

	strcat_s(m_aStrDebug, str);

	va_end(list);
}
