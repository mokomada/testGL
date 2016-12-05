/*******************************************************************************
* タイトル フェード処理
* ファイル名 Fade.cpp
* 作成者 AT-12C-245 秋間雄太
* 作成日 2015/06/03
*******************************************************************************/

/*******************************************************************************
* インクルードファイル
*******************************************************************************/

#include "main.h"
#include "manager.h"
#include "scene.h"
#include "renderer.h"
#include "mode.h"
#include "fade.h"
#include "title.h"
#include "game.h"
#include "result.h"


/*******************************************************************************
* グローバル変数
*******************************************************************************/


FADE CFade::m_fade = FADE_NONE; // フェードの状態
CMode *CFade::m_modeNext = NULL; // 次のモード

/*******************************************************************************
* 関数名：InitFade
* 引数：なし
* 戻り値：なし
* 説明：フェード設定の初期化
*******************************************************************************/

HRESULT CFade::Init(void) {
	/* 変数宣言 */
	int i; // for文ループ用
	VERTEX_2D *pVtx;

	// メンバ変数初期化
	m_pTextureFade = NULL;
	m_pVtxBuffFade = NULL;

	/* 変数の取得 */
	CRenderer *renderer;
	renderer = CManager::GetRenderer( );
	LPDIRECT3DDEVICE9 device = renderer -> GetDevice( );

	/* フェードテクスチャ設定 */
	D3DXCreateTextureFromFile(device, NULL, &m_pTextureFade);

	/* 頂点バッファの生成 */
	if(FAILED(device -> CreateVertexBuffer(sizeof(VERTEX_2D) * FADE_VERTEX_NUM, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuffFade, NULL) ) ) {
		return E_FAIL;
	}

	/* 頂点情報へのポインタを取得 */
	m_pVtxBuffFade -> Lock(0, 0, (void**)&pVtx, 0);

	/* 座標設定 */
	pVtx[0].pos = D3DXVECTOR3(0, 0, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);


	for(i = 0; i < FADE_VERTEX_NUM; i++) {
		pVtx[i].rhw = 1.0f;

		pVtx[i].col = D3DCOLOR_RGBA(0, 0, 0, 255);
	}

	/* テクスチャUV座標設定 */
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	m_pVtxBuffFade -> Unlock( );

	m_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	m_fade = FADE_IN;
	m_modeNext = new CTitle;

	return S_OK;
}


/*******************************************************************************
* 関数名：UninitFade
* 引数：なし
* 戻り値：なし
* 説明：フェード設定の終了処理
*******************************************************************************/

void CFade::Uninit(void) {
	if(m_pTextureFade != NULL) {
		m_pTextureFade -> Release( ); // テクスチャの開放
		m_pTextureFade = NULL;
	}

	if(m_pVtxBuffFade != NULL) {
		m_pVtxBuffFade -> Release( );
		m_pVtxBuffFade = NULL;
	}
}


/*******************************************************************************
* 関数名：UpdataFade
* 引数：なし
* 戻り値：なし
* 説明：フェードの情報更新
*******************************************************************************/

void CFade::Update(void) {
	/* 変数宣言 */
	int i; // for文ループ用
	VERTEX_2D *pVtx;

	if(m_fade == FADE_IN) {
		m_colorFade.a -= FADE_IN_SPEED;
		if(m_colorFade.a <= 0.0) {
			m_colorFade.a = 0.0f;
			m_fade = FADE_NONE;
		}
	}
	else if(m_fade == FADE_OUT) {
		m_colorFade.a += FADE_OUT_SPEED;
		if(m_colorFade.a >= 1.0) {
			m_colorFade.a = 1.0f;
			CManager::SetMode(m_modeNext);
			m_fade = FADE_IN;
		}
	}

	/* 頂点情報へのポインタを取得 */
	m_pVtxBuffFade -> Lock(0, 0, (void**)&pVtx, 0);

	for(i = 0; i < FADE_VERTEX_NUM; i++) {
		pVtx[i].col = m_colorFade;
	}

	m_pVtxBuffFade -> Unlock( );
}


/*******************************************************************************
* 関数名：DrawFade
* 引数：なし
* 戻り値：なし
* 説明：フェードの描画処理
*******************************************************************************/

void CFade::Draw(void) {
	CRenderer *renderer;
	renderer = CManager::GetRenderer( );
	LPDIRECT3DDEVICE9 device = renderer -> GetDevice( );

	// 頂点バッファをデータストリームにバインド
	device -> SetStreamSource(0, m_pVtxBuffFade, 0, sizeof(VERTEX_2D) );

	// 頂点フォーマットの設定
	device -> SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	device -> SetTexture(0, m_pTextureFade);

	// 2Dポリゴンの描画
	device -> DrawPrimitive(
		D3DPT_TRIANGLESTRIP,
		0,
		FADE_TRIANGLE_NUM);
}


/*******************************************************************************
* 関数名：SetFade
* 引数：fade : どのフェードモードに切り替えるか（実質フェードアウトで固定）
		modeNext : フェードアウトが終わった後、どのモードに切り替えるのか
* 戻り値：なし
* 説明：フェード（アウト）の開始処理
*******************************************************************************/

void CFade::SetFade(FADE fade, CMode *modeNext) {
	if(m_fade == FADE_NONE) {
		m_fade = fade;
		m_modeNext = modeNext;
	}
}


/*******************************************************************************
* 関数名：GetFade
* 引数：なし
* 戻り値：現在のフェードの状態
* 説明：フェード状態の取得
*******************************************************************************/

FADE CFade::GetFade(void) {
	return m_fade;
}