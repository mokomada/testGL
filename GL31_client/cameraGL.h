#ifndef _CAMERAGL_H_
#define _CAMERAGL_H_
//=============================================================================
//
//	タイトル	ヘッダファイル(scene.cpp)
//	ファイル名	scene.h
//	作成者		AT13A284_07 池田達哉
//	作成日		2016/04/19
//
//=============================================================================
#include "main.h"
//=============================================================================
//	マクロ定義
//=============================================================================
#define	CAMERA_NEARZ				(10.0f)			// NearZ値
#define	CAMERA_FARZ					(10000.0f)		// FarZ値
#define	CAMERA_DEFAULT_DISTANCE		(200.0f)		// 初期の視点―注視点間距離

#define	CAMERA_POSV_MOVEMENT		(3.0f)			// 視点の移動速度
#define	CAMERA_POSR_MOVEMENT_X		(0.025f)			// 注視点の移動量(左右)
#define	CAMERA_POSR_MOVEMENT_Y		(3.0f)			// 注視点の移動量(上下)


#define	CAMERA_POSV_XSET	300.0f,	100.0f,	0.0f		// X方向からのカメラ
#define	CAMERA_POSV_YSET	0.0f,	300.0f,	1.0f		// Y方向からのカメラ
#define	CAMERA_POSV_ZSET	0.0f,	100.0f,	300.0f		// Z方向からのカメラ

//=============================================================================
//	構造体
//=============================================================================
typedef struct{	// カメラ情報
	VECTOR3	posV;			// 視点
	VECTOR3	posR;			// 注視点
	VECTOR3	vecU;			// 上方向ベクトル
	MATRIX	mtxPojection;	// プロジェクションマトリックス
	MATRIX	mtxView;		// ビューマトリックス
	VECTOR3 Rot;			// 回転角
	float	fDistance;		// 視点―注視点間距離
	float	fDisMax;		// 視点―注視点間最大距離
}CAMERA;

//=============================================================================
//	クラス定義
//=============================================================================
class CCameraGL
{
public:
	CCameraGL();
	~CCameraGL();

	void	Init(void);
	void	Uninit(void);
	void	Update(void);
	void	Set(void);
	void	SetPosV(VECTOR3 pos){ 
		m_CameraState.posV = pos;
		m_CameraState.Rot.y = atan2f((m_CameraState.posR.x - m_CameraState.posV.x), (m_CameraState.posR.z - m_CameraState.posV.z)); }

	void	SetPosR(VECTOR3 pos) {
		m_CameraState.posR = pos;
		m_CameraState.Rot.y = atan2f((m_CameraState.posR.x - m_CameraState.posV.x), (m_CameraState.posR.z - m_CameraState.posV.z));
	}
	
	CAMERA	m_CameraState;			// カメラ

protected:


};

#endif