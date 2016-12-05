/*******************************************************************************
* ファイル名 sceneX.h
* 作成者 AT-13A-284 秋間雄太
* 作成日 2016/04/26
*******************************************************************************/

/*** インクルードガード開始 ***/
#ifndef _ENEMY_H_
#define _ENEMY_H_


/*******************************************************************************
* マクロ定義
*******************************************************************************/

#define ENEMY_NAME "data/MODEL/dog.x" // 読み込むXファイル名
#define ENEMY_TEXTURE_NAME NULL // テクスチャ名

#define ENEMY_MOVE_SPEED (0.5f) // モデルの移動速度
#define ENEMY_ROT_SPEED (0.03f) // モデルの回転速度
#define ENEMY_JUMP_SPEED (2.0f) // モデルのジャンプ力
#define ENEMY_FALL_SPEED (0.2f) // モデルの落下速度

#define ENEMY_SCALE_X (1.0f) // スケール値 X軸
#define ENEMY_SCALE_Y (1.0f) // スケール値 Y軸
#define ENEMY_SCALE_Z (1.0f) // スケール値 Z軸

#define ENEMY_ROT_X (0.0f) // 回転量 X軸
#define ENEMY_ROT_Y (0.0f) // 回転量 Y軸
#define ENEMY_ROT_Z (0.0f) // 回転量 Z軸

#define ENEMY_POS_X (0.0f) // 位置情報 X軸
#define ENEMY_POS_Y (0.0f) // 位置情報 Y軸
#define ENEMY_POS_Z (0.0f) // 位置情報 Z軸

#define ENEMY_MOVE_MAX (3.0f) // 最大移動量
#define ENEMY_MOVE_REDUCE (0.0f) // 移動量減衰量
#define ENEMY_FALL_REDUCE (0.8f) // 落下速度減衰量

#define ENEMY_VIEW_DISTANCE (0.0f) // モデルの中心点から注視点までの距離

#define ENEMY_MOVE_CHANGE (30) // 移動方向を変更するまでの時間
#define ENEMY_RESPAWN_TIME (300) // リスポーンまでの時間
#define ENEMY_START_DISTANCE (20.0f) // 初期位置のプレイヤーとの最低距離

#define ENEMY_MAX (3) // エネミーの最大数

/*******************************************************************************
* 構造体定義
*******************************************************************************/


/*******************************************************************************
* 3Dポリゴンクラス
*******************************************************************************/

class CEnemy : public CSceneX{
private:
	//LPDIRECT3DTEXTURE9 m_pTexture;
	//LPD3DXMESH m_pMesh; // メッシュ情報
	//LPD3DXBUFFER m_pBuffMat; // マテリアル情報
	//DWORD m_numMat; // マテリアルの数
	//D3DXMATRIX m_mtxWorld; // ワールドマトリックス
	MODEL m_enemy;
	float m_newRot;
	int m_moveChange;
	int m_respawn;
	bool m_moveFlag;
	int m_rnd;

public:
	CEnemy(int priority = 1, OBJTYPE objType = OBJTYPE_ENEMY); // コンストラクタ
	~CEnemy( ); // デストラクタ

	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CEnemy *Create(void); // 必要に応じて初期位置や角度等の引数を
	MODEL GetEnemy(void);
};


#endif
/*** インクルードガード終了 ***/