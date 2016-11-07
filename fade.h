/*******************************************************************************
* ファイル名 fade.h
* 作成者 AT-13A-284 秋間雄太
* 作成日 2016/07/19
*******************************************************************************/

/*** インクルードガード開始 ***/
#ifndef _FADE_H_
#define _FADE_H_

/*******************************************************************************
* マクロ定義
*******************************************************************************/

#define FADE_VERTEX_NUM (4) // 描画する頂点の個数
#define FADE_TRIANGLE_NUM (2) // 描画する三角形の個数

#define FADE_IN_SPEED (0.05f) // フェードイン速度
#define FADE_OUT_SPEED (0.01f) // フェードアウト速度


/*******************************************************************************
* 構造体の宣言
*******************************************************************************/

typedef enum{
	FADE_NONE = 0,	// 何もしていない
	FADE_IN,		// フェードイン
	FADE_OUT,		// フェードアウト
	FADE_MAX
} FADE;

/*******************************************************************************
* プロトタイプ宣言
*******************************************************************************/

class CMode;

class CFade{
private:
	LPDIRECT3DTEXTURE9 m_pTextureFade; // フェード用テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffFade; //頂点バッファへのポインタ
	D3DXCOLOR m_colorFade; // フェード色
	static FADE m_fade; // フェードの状態
	static CMode *m_modeNext; // 次のモード

public:
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static void SetFade(FADE fade, CMode *modeNext);
	FADE GetFade(void);
};

#endif
/*** インクルードガード終了 ***/