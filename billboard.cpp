/*******************************************************************************
* タイトル ビルボード描画処理
* ファイル名 billboard.cpp
* 作成者 AT-12C-245 秋間雄太
* 作成日 2015/11/17
*******************************************************************************/

#include "main.h"
#include "manager.h"
#include "scene.h"
#include "billboard.h"
#include "renderer.h"
#include "shadow.h"
#include "input.h"
#include "camera.h"
#include "meshfield.h"
#include "game.h"

/*******************************************************************************
* 構造体定義
*******************************************************************************/



/*******************************************************************************
* グローバル変数
*******************************************************************************/


/*******************************************************************************
* 関数名：CManager
* 引数：なし
* 戻り値：なし
* 説明：クラス生成時処理
*******************************************************************************/

CBillboard::CBillboard( ) {

}


/*******************************************************************************
* 関数名：~CManager
* 引数：なし
* 戻り値：なし
* 説明：クラス破棄時処理
*******************************************************************************/

CBillboard::~CBillboard( ) {

}

/*******************************************************************************
* 関数名：Init
* 引数：なし
* 戻り値：なし
* 説明：ビルボード設定の初期化
*******************************************************************************/

void CBillboard::Init(void) {
	// 変数宣言
	int i; // forループ用
	VERTEX_3D *pVtx;

	// 変数の取得
	CRenderer *renderer; // デバイス取得用変数
	renderer= CManager::GetRenderer( ); // レンダラのアドレス取得
	LPDIRECT3DDEVICE9 pDevice = renderer -> GetDevice( );

	// メンバ変数の初期化
	m_pTextureBillboard = NULL;
	m_pVtxBuffBillboard = NULL;

	// 角度初期設定
	m_billboard.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_billboard.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_billboard.scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	// テクスチャ設定
	D3DXCreateTextureFromFile(pDevice, BILLBOARD_TEXTURE_NAME, &m_pTextureBillboard);

	// 頂点バッファの生成
	pDevice -> CreateVertexBuffer(sizeof(VERTEX_3D) * BILLBOARD_VERTEX_NUM, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &m_pVtxBuffBillboard, NULL);

	// 頂点情報へのポインタを取得
	m_pVtxBuffBillboard -> Lock(0, 0, (void**)&pVtx, 0);

	// 座標設定
	pVtx[0].pos = D3DXVECTOR3(-BILLBOARD_WIDTH * 0.5f, BILLBOARD_HEIGHT, 0);
	pVtx[1].pos = D3DXVECTOR3(BILLBOARD_WIDTH * 0.5f, BILLBOARD_HEIGHT, 0);
	pVtx[2].pos = D3DXVECTOR3(-BILLBOARD_WIDTH * 0.5f, 0, 0);
	pVtx[3].pos = D3DXVECTOR3(BILLBOARD_WIDTH * 0.5f, 0, 0);

	for(i = 0; i < BILLBOARD_VERTEX_NUM; i++) {
		pVtx[i].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	}

	// 法線設定
	pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);


	// テクスチャUV座標設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	m_pVtxBuffBillboard -> Unlock( );

	// 影の設定
	m_billboard.shadow_num = SetShadow(&m_billboard.pos, BILLBOARD_WIDTH, BILLBOARD_HEIGHT);
}


/*******************************************************************************
* 関数名：Uninit
* 引数：なし
* 戻り値：なし
* 説明：ビルボードの終了処理
*******************************************************************************/

void CBillboard::Uninit(void) {
	if(m_pTextureBillboard != NULL) {
		m_pTextureBillboard -> Release( ); // テクスチャの開放
		m_pTextureBillboard = NULL;
	}

	if(m_pVtxBuffBillboard != NULL) {
		m_pVtxBuffBillboard -> Release( );
		m_pVtxBuffBillboard = NULL;
	}

	// 影の開放
	DeleteShadow(m_billboard.shadow_num);
}


/*******************************************************************************
* 関数名：Updata
* 引数：なし
* 戻り値：なし
* 説明：ビルボードの情報更新
*******************************************************************************/

void CBillboard::Update(void) {
	// 変数の宣言
	float field_height;

	// カメラ情報取得
	CCamera *get_camera = CGame::GetCamera( );
	CAMERA camera = get_camera -> GetCameraData( );

	// 入力情報取得
	CInput *input;
	input = CManager::GetInput( );

	if(input -> GetKeyboardPress(DIK_L) ) {
		if(input -> GetKeyboardPress(DIK_P) ) { // 左上移動
			m_billboard.pos.x += sinf(D3DX_PI * (camera.rot.y - 0.75f) ) * BILLBOARD_MOVE_SPEED;
			m_billboard.pos.z -= cosf(D3DX_PI * (camera.rot.y - 0.75f) ) * BILLBOARD_MOVE_SPEED;
		}
		else if(input -> GetKeyboardPress(DIK_SEMICOLON) ) { // 左下移動
			m_billboard.pos.x += sinf(D3DX_PI * (camera.rot.y - 0.25f) ) * BILLBOARD_MOVE_SPEED;
			m_billboard.pos.z -= cosf(D3DX_PI * (camera.rot.y - 0.25f) ) * BILLBOARD_MOVE_SPEED;
		}
		else { // 左移動
			m_billboard.pos.x += sinf(D3DX_PI * (camera.rot.y - 0.5f) ) * BILLBOARD_MOVE_SPEED;
			m_billboard.pos.z -= cosf(D3DX_PI * (camera.rot.y - 0.5f) ) * BILLBOARD_MOVE_SPEED;
		}
	}
	else if(input -> GetKeyboardPress(DIK_COLON) ) {
		if(input -> GetKeyboardPress(DIK_P) ) { // 右上移動
			m_billboard.pos.x += sinf(D3DX_PI * (camera.rot.y + 0.75f) ) * BILLBOARD_MOVE_SPEED;
			m_billboard.pos.z -= cosf(D3DX_PI * (camera.rot.y + 0.75f) ) * BILLBOARD_MOVE_SPEED;
		}
		else if(input -> GetKeyboardPress(DIK_SEMICOLON) ) { // 右下移動
			m_billboard.pos.x += sinf(D3DX_PI * (camera.rot.y + 0.25f) ) * BILLBOARD_MOVE_SPEED;
			m_billboard.pos.z -= cosf(D3DX_PI * (camera.rot.y + 0.25f) ) * BILLBOARD_MOVE_SPEED;
		}
		else { // 右移動
			m_billboard.pos.x += sinf(D3DX_PI * (camera.rot.y + 0.5f) ) * BILLBOARD_MOVE_SPEED;
			m_billboard.pos.z -= cosf(D3DX_PI * (camera.rot.y + 0.5f) ) * BILLBOARD_MOVE_SPEED;
		}
	}
	else if(input -> GetKeyboardPress(DIK_P) ) {
		m_billboard.pos.x += sinf(D3DX_PI * (camera.rot.y + 1.0f) ) * BILLBOARD_MOVE_SPEED;
		m_billboard.pos.z -= cosf(D3DX_PI * (camera.rot.y + 1.0f) ) * BILLBOARD_MOVE_SPEED;
	}
	else if(input -> GetKeyboardPress(DIK_SEMICOLON) ) {
		m_billboard.pos.x += sinf(D3DX_PI * (camera.rot.y) ) * BILLBOARD_MOVE_SPEED;
		m_billboard.pos.z -= cosf(D3DX_PI * (camera.rot.y) ) * BILLBOARD_MOVE_SPEED;
	}

	// 上昇下降
	if(input -> GetKeyboardPress(DIK_O) ) {
		m_billboard.pos.y += BILLBOARD_MOVE_SPEED;
	}
	if(input -> GetKeyboardPress(DIK_AT) ) {
		m_billboard.pos.y -= BILLBOARD_MOVE_SPEED;
	}

	// フィールド高さ取得
	field_height = CMeshfield::GetFieldHeight(m_billboard.pos);

	// 高さ処理
	m_billboard.pos.y = field_height;
}


/*******************************************************************************
* 関数名：Draw
* 引数：なし
* 戻り値：なし
* 説明：ビルボードの描画処理
*******************************************************************************/

void CBillboard::Draw(void) {
/*	CRenderer *renderer; // デバイス取得用変数
	renderer= CManager::GetRenderer( ); // レンダラのアドレス取得
	LPDIRECT3DDEVICE9 pDevice = renderer -> GetDevice( );
	D3DXMATRIX mtxScl, mtxRot, mtxTrans; // 計算用
	D3DXMATRIX mtxView;

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorldBillboard);

	// ビューマトリックスを取得
	pDevice -> GetTransform(D3DTS_VIEW, &mtxView);

	// 逆行列の計算
	D3DXMatrixInverse(&m_mtxWorldBillboard, NULL, &mtxView);

	// 移動情報の削除
	m_mtxWorldBillboard._41 = 0.0f;
	m_mtxWorldBillboard._42 = 0.0f;
	m_mtxWorldBillboard._43 = 0.0f;

	// ワールドマトリックスの作成
	// スケールを反映
	D3DXMatrixScaling(&mtxScl, m_billboard.scl.x, m_billboard.scl.y, m_billboard.scl.z);
	D3DXMatrixMultiply(&m_mtxWorldBillboard, &m_mtxWorldBillboard, &mtxScl);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_billboard.rot.y, m_billboard.rot.x, m_billboard.rot.z); // ※※※ y, x, z の順番に注意！！！ ※※※
	D3DXMatrixMultiply(&m_mtxWorldBillboard, &m_mtxWorldBillboard, &mtxRot);

	// 移動を反映
	D3DXMatrixTranslation(&mtxTrans, m_billboard.pos.x, m_billboard.pos.y, m_billboard.pos.z);
	D3DXMatrixMultiply(&m_mtxWorldBillboard, &m_mtxWorldBillboard, &mtxTrans);

	// ワールドマトリックスの設定
	pDevice -> SetTransform(D3DTS_WORLD, &m_mtxWorldBillboard);

	// 頂点バッファをデータストリームにバインド
	pDevice -> SetStreamSource(0, m_pVtxBuffBillboard, 0, sizeof(VERTEX_3D) );

	// 頂点フォーマットの設定
	pDevice -> SetFVF(FVF_VERTEX_3D);

	// テクスチャの設定
	pDevice -> SetTexture(0, m_pTextureBillboard);

	// ライト設定オフ
	pDevice -> SetRenderState(D3DRS_LIGHTING, FALSE);

	// アルファテスト設定
	pDevice -> SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice -> SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice -> SetRenderState(D3DRS_ALPHAREF, 0);

	// ポリゴンの描画
	pDevice -> DrawPrimitive(
		D3DPT_TRIANGLESTRIP,
		0,
		BILLBOARD_TRIANGLE_NUM);

	// ライト設定オン
	pDevice -> SetRenderState(D3DRS_LIGHTING, TRUE);

	// アルファテスト設定を元に戻す
	pDevice -> SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice -> SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice -> SetRenderState(D3DRS_ALPHAREF, 0);*/
}

/*******************************************************************************
* 関数名：Create
* 引数：billboard : アドレス
* 戻り値：なし
* 説明：オブジェクトの生成
*******************************************************************************/

CBillboard *CBillboard::Create(void) {
	CBillboard *billboard;
	billboard = new CBillboard;
	billboard -> Init( );
	return billboard;
}