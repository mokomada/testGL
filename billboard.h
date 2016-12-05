/*******************************************************************************
* ファイル名 billboard.h
* 作成者 AT-13A-284 秋間雄太
* 作成日 2016/06/08
*******************************************************************************/

/*** インクルードガード開始 ***/
#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

/*******************************************************************************
* マクロ定義
*******************************************************************************/

#define BILLBOARD_VERTEX_NUM (4) // 描画する頂点の個数
#define BILLBOARD_TRIANGLE_NUM (2) // 描画する三角形の個数

#define BILLBOARD_TEXTURE_NAME "data/TEXTURE/tree001.png" // テクスチャーに使う画像指定

#define BILLBOARD_WIDTH (41) // ビルボードの幅
#define BILLBOARD_HEIGHT (41) // ビルボードの高さ

#define BILLBOARD_MOVE_SPEED (2) // ビルボードの移動速度



/*******************************************************************************
* ビルボードクラス
*******************************************************************************/

class CBillboard : public CScene{
private:
	typedef struct {
		D3DXVECTOR3 pos; // 位置情報
		D3DXVECTOR3 rot; // 回転情報
		D3DXVECTOR3 scl; // スケール値　基本的に全て1.0fで固定
		int shadow_num; // 影の番号
	} BILLBOARD;

	LPDIRECT3DTEXTURE9 m_pTextureBillboard; // テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffBillboard; //頂点バッファへのポインタ

	BILLBOARD m_billboard; // ビルボード情報

	D3DXMATRIX m_mtxWorldBillboard; // ワールドマトリックス

public:
	CBillboard( );
	~CBillboard( );

	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CBillboard *Create(void);
};

#endif
/*** インクルードガード終了 ***/