/*******************************************************************************
* ファイル名 camera.h
* 作成者 AT-13A-284 秋間雄太
* 作成日 2016/04/27
*******************************************************************************/

/*** インクルードガード開始 ***/
#ifndef _CAMERA_H_
#define _CAMERA_H_

/*******************************************************************************
* マクロ定義
*******************************************************************************/

#define CAMERA_MOVE_SPEED (0.1f) // カメラの移動速度
#define CAMERA_ROT_SPEED (0.01f) // カメラの回転速度
#define CAMERA_ROT_TIME (30) // 操作を止めてから回転を始めるまでのフレーム

#define CAMERA_POSV_X (0.0f) // カメラの視点 X座標
#define CAMERA_POSV_Y (10.0f) // カメラの視点 Y座標
#define CAMERA_POSV_Z (20.0f) // カメラの視点 Z座標

#define CAMERA_POSR_X (0.0f) // カメラの注視点 X座標
#define CAMERA_POSR_Y (0.0f) // カメラの注視点 Y座標
#define CAMERA_POSR_Z (0.0f) // カメラの注視点 Z座標

#define CAMERA_VEC_X (0.0f) // カメラの上方向ベクトル X座標
#define CAMERA_VEC_Y (1.0f) // カメラの上方向ベクトル Y座標
#define CAMERA_VEC_Z (0.0f) // カメラの上方向ベクトル Z座標

#define CAMERA_DISTANCE_X (0.0f) // 視点-注視点の距離(X)
#define CAMERA_DISTANCE_Y (5.0f) // 視点-注視点の距離(Y)
#define CAMERA_DISTANCE_Z (50.0f) // 視点-注視点の距離(Z)

#define CAMERA_CHANGE_DISTANCE (0.5f) // 距離の変更速度
#define CAMERA_MAX_DISTANCE (50.0f) // 距離の最大値
#define CAMERA_MIN_DISTANCE (12.0f) // 距離の最小値

#define CAMERA_POSRMAX_Y (10.0f) // 注視点上下位置の最大値
#define CAMERA_POSRMIN_Y (-10.0f) // 注視点上下位置の最小値

#define CAMERA_POSVMAX_Y (10.0f) // 視点の上下移動最大値
#define CAMERA_POSVMIN_Y (-10.0f) // 視点の上下移動最小値


/*******************************************************************************
* 構造体定義
*******************************************************************************/

typedef struct
{
	D3DXVECTOR3 posV; // 視点
	D3DXVECTOR3 posR; // 注視点
	D3DXVECTOR3 vecU; // 上方向ベクトル
	D3DXMATRIX mtxProjection; // プロジェクションマトリックス
	D3DXMATRIX mtxView; // ビューマトリックス
	D3DXVECTOR3 rot; // 向き取得用
	D3DXVECTOR3 fDistance; // 視点～注視点の距離
	float posR_y; // 注視点の上下移動用
	float posV_y; // 視点の上下移動用
	float newRot;
	int rotTime;
} CAMERA;


/*******************************************************************************
* カメラクラス
*******************************************************************************/

class CCamera{
private:
	CAMERA m_camera; // カメラ設定

public:
	CCamera( ); // コンストラクタ
	~CCamera( ); // デストラクタ

	void Init(void);
	void Uninit(void);
	void Update(void);
	void SetCamera(void);
	CAMERA GetCameraData(void);
};

#endif
/*** インクルードガード終了 ***/