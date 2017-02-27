//=============================================================================
//
//	タイトル	カメラファイル
//	ファイル名	camera.cpp
//	作成者		AT13A284_07 池田達哉
//	作成日		2016/04/26
//
//=============================================================================
//=============================================================================
//	インクルード
//=============================================================================
#include "cameraGL.h"
#include "manager.h"
#include "main.h"
#include "rendererGL.h"
//#include "input.h"
//#include "debugproc.h"

//=============================================================================
//	関数名	:CCameraGL()
//	引数	:無し
//	戻り値	:無し
//	説明	:コンストラクタ。
//=============================================================================
CCameraGL::CCameraGL()
{

}

//=============================================================================
//	関数名	:~CCameraGL()
//	引数	:無し
//	戻り値	:無し
//	説明	:デストラクタ。
//=============================================================================
CCameraGL::~CCameraGL()
{

}

//=============================================================================
//	関数名	:Init
//	引数	:無し
//	戻り値	:無し
//	説明	:初期化処理を行う。
//=============================================================================
void CCameraGL::Init(void)
{
	m_CameraState.posV = VECTOR3(0.0f, 150.0f, 300.0f);
	m_CameraState.posR = VECTOR3(0.0f, 80.0f, 0.0f);
	m_CameraState.vecU = VECTOR3(0.0f, 1.0f, 0.0f);
	m_CameraState.Rot = VECTOR3(0.0f, atan2f((m_CameraState.posR.x - m_CameraState.posV.x), (m_CameraState.posR.z - m_CameraState.posV.z)), 0.0f);
	m_CameraState.fDistance = hypotf((m_CameraState.posR.z - m_CameraState.posV.z), (m_CameraState.posR.x - m_CameraState.posV.x));
}

//=============================================================================
//	関数名	:Uninit
//	引数	:無し
//	戻り値	:無し
//	説明	:終了処理を行う。
//=============================================================================
void CCameraGL::Uninit(void)
{

}

//=============================================================================
//	関数名	:Update
//	引数	:無し
//	戻り値	:無し
//	説明	:更新処理を行う。
//=============================================================================
void CCameraGL::Update(void)
{
	// カメラ移動
	if (CInput::GetKeyboardPress(DIK_UP) && !CInput::GetKeyboardPress(DIK_LEFT) && !CInput::GetKeyboardPress(DIK_RIGHT))
	{// カメラ移動(奥)

		// 視点移動
		m_CameraState.posV.x += sinf(m_CameraState.Rot.y) * CAMERA_POSV_MOVEMENT;
		m_CameraState.posV.z += cosf(m_CameraState.Rot.y) * CAMERA_POSV_MOVEMENT;

		// 注視点設定
		m_CameraState.posR.x = m_CameraState.posV.x + (sinf(m_CameraState.Rot.y) * m_CameraState.fDistance);
		m_CameraState.posR.z = m_CameraState.posV.z + (cosf(m_CameraState.Rot.y) * m_CameraState.fDistance);
	}
	else if (CInput::GetKeyboardPress(DIK_DOWN) && !CInput::GetKeyboardPress(DIK_LEFT) && !CInput::GetKeyboardPress(DIK_RIGHT))
	{// カメラ移動(手前)

		// 視点移動
		m_CameraState.posV.x += sinf(m_CameraState.Rot.y + PI) * CAMERA_POSV_MOVEMENT;
		m_CameraState.posV.z += cosf(m_CameraState.Rot.y + PI) * CAMERA_POSV_MOVEMENT;

		// 注視点設定
		m_CameraState.posR.x = m_CameraState.posV.x + (sinf(m_CameraState.Rot.y) * m_CameraState.fDistance);
		m_CameraState.posR.z = m_CameraState.posV.z + (cosf(m_CameraState.Rot.y) * m_CameraState.fDistance);
	}
	else if (CInput::GetKeyboardPress(DIK_LEFT))
	{// カメラ移動(左)

		if (CInput::GetKeyboardPress(DIK_UP))
		{// 左奥

			// 視点移動
			m_CameraState.posV.x += sinf(m_CameraState.Rot.y + (PI * 0.25f)) * CAMERA_POSV_MOVEMENT;
			m_CameraState.posV.z += cosf(m_CameraState.Rot.y + (PI * 0.25f)) * CAMERA_POSV_MOVEMENT;

			// 注視点設定
			m_CameraState.posR.x = m_CameraState.posV.x + (sinf(m_CameraState.Rot.y) * m_CameraState.fDistance);
			m_CameraState.posR.z = m_CameraState.posV.z + (cosf(m_CameraState.Rot.y) * m_CameraState.fDistance);
		}
		else if (CInput::GetKeyboardPress(DIK_DOWN))
		{// 左手前

			// 視点移動
			m_CameraState.posV.x += sinf(m_CameraState.Rot.y + (PI * 0.75f)) * CAMERA_POSV_MOVEMENT;
			m_CameraState.posV.z += cosf(m_CameraState.Rot.y + (PI * 0.75f)) * CAMERA_POSV_MOVEMENT;

			// 注視点設定
			m_CameraState.posR.x = m_CameraState.posV.x + (sinf(m_CameraState.Rot.y) * m_CameraState.fDistance);
			m_CameraState.posR.z = m_CameraState.posV.z + (cosf(m_CameraState.Rot.y) * m_CameraState.fDistance);
		}
		else
		{// 左

			// 視点移動
			m_CameraState.posV.x += sinf(m_CameraState.Rot.y + (PI * 0.5f)) * CAMERA_POSV_MOVEMENT;
			m_CameraState.posV.z += cosf(m_CameraState.Rot.y + (PI * 0.5f)) * CAMERA_POSV_MOVEMENT;

			// 注視点設定
			m_CameraState.posR.x = m_CameraState.posV.x + (sinf(m_CameraState.Rot.y) * m_CameraState.fDistance);
			m_CameraState.posR.z = m_CameraState.posV.z + (cosf(m_CameraState.Rot.y) * m_CameraState.fDistance);
		}
	}
	else if(CInput::GetKeyboardPress(DIK_RIGHT))
	{// カメラ移動(右)

		if(CInput::GetKeyboardPress(DIK_UP))
		{// 右奥

			// 視点移動
			m_CameraState.posV.x += sinf(m_CameraState.Rot.y - (PI * 0.25f)) * CAMERA_POSV_MOVEMENT;
			m_CameraState.posV.z += cosf(m_CameraState.Rot.y - (PI * 0.25f)) * CAMERA_POSV_MOVEMENT;

			// 注視点設定
			m_CameraState.posR.x = m_CameraState.posV.x + (sinf(m_CameraState.Rot.y) * m_CameraState.fDistance);
			m_CameraState.posR.z = m_CameraState.posV.z + (cosf(m_CameraState.Rot.y) * m_CameraState.fDistance);
		}
		else if (CInput::GetKeyboardPress(DIK_DOWN))
		{// 右手前

			// 視点移動
			m_CameraState.posV.x += sinf(m_CameraState.Rot.y - (PI * 0.75f)) * CAMERA_POSV_MOVEMENT;
			m_CameraState.posV.z += cosf(m_CameraState.Rot.y - (PI * 0.75f)) * CAMERA_POSV_MOVEMENT;

			// 注視点設定
			m_CameraState.posR.x = m_CameraState.posV.x + (sinf(m_CameraState.Rot.y) * m_CameraState.fDistance);
			m_CameraState.posR.z = m_CameraState.posV.z + (cosf(m_CameraState.Rot.y) * m_CameraState.fDistance);
		}
		else
		{// 右

			// 視点移動
			m_CameraState.posV.x += sinf(m_CameraState.Rot.y - (PI * 0.5f)) * CAMERA_POSV_MOVEMENT;
			m_CameraState.posV.z += cosf(m_CameraState.Rot.y - (PI * 0.5f)) * CAMERA_POSV_MOVEMENT;

			// 注視点設定
			m_CameraState.posR.x = m_CameraState.posV.x + (sinf(m_CameraState.Rot.y) * m_CameraState.fDistance);
			m_CameraState.posR.z = m_CameraState.posV.z + (cosf(m_CameraState.Rot.y) * m_CameraState.fDistance);
		}
	}

	// 視点移動
	if(KH_Y && !KH_Z && !KH_C)
	{// 視点移動(上)

		// 視点設定
		m_CameraState.posV.y += CAMERA_POSR_MOVEMENT_Y;
	}
	else if(KH_N && !KH_Z && !KH_C)
	{// 視点移動(下)

		// 視点設定
		m_CameraState.posV.y -= CAMERA_POSR_MOVEMENT_Y;
	}
	else if(KH_Z)
	{// 視点移動(左)

		if(KH_Y)
		{// 左上

			// 視点変更
			m_CameraState.posV.y += CAMERA_POSR_MOVEMENT_Y;
			
			// 角度増減
			m_CameraState.Rot.y -= CAMERA_POSR_MOVEMENT_X;
		}
		else if(KH_N)
		{// 左下

			// 視点変更
			m_CameraState.posV.y -= CAMERA_POSR_MOVEMENT_Y;
			
			// 角度増減
			m_CameraState.Rot.y -= CAMERA_POSR_MOVEMENT_X;
		}
		else
		{// 左

			// 角度増減
			m_CameraState.Rot.y -= CAMERA_POSR_MOVEMENT_X;
		}
		
		// 視点注視点間距離更新
		m_CameraState.fDistance = hypotf((m_CameraState.posR.z - m_CameraState.posV.z), (m_CameraState.posR.x - m_CameraState.posV.x));
		
		// 視点設定
		m_CameraState.posV.x = m_CameraState.posR.x - (sinf(m_CameraState.Rot.y) * m_CameraState.fDistance);
		m_CameraState.posV.z = m_CameraState.posR.z - (cosf(m_CameraState.Rot.y) * m_CameraState.fDistance);
	}
	else if(KH_C)
	{// 視点移動(右)

		if(KH_Y)
		{// 右上

			// 視点変更
			m_CameraState.posV.y += CAMERA_POSR_MOVEMENT_Y * sinf(PI * 0.25);
			
			// 角度増減
			m_CameraState.Rot.y += CAMERA_POSR_MOVEMENT_X * sinf(PI * 0.25);
		}
		else if(KH_N)
		{// 右下

			// 視点変更
			m_CameraState.posV.y -= CAMERA_POSR_MOVEMENT_Y * sinf(PI * 0.25);
			
			// 角度増減
			m_CameraState.Rot.y += CAMERA_POSR_MOVEMENT_X * sinf(PI * 0.25);
		}
		else
		{// 右

			// 角度増減
			m_CameraState.Rot.y += CAMERA_POSR_MOVEMENT_X;
		}
			
		// 視点注視点間距離更新
		m_CameraState.fDistance = hypotf((m_CameraState.posR.z - m_CameraState.posV.z), (m_CameraState.posR.x - m_CameraState.posV.x));
		
		// 視点設定
		m_CameraState.posV.x = m_CameraState.posR.x - (sinf(m_CameraState.Rot.y) * m_CameraState.fDistance);
		m_CameraState.posV.z = m_CameraState.posR.z - (cosf(m_CameraState.Rot.y) * m_CameraState.fDistance);
	}

	// 注視点移動
	if(KH_T && !KH_Q && !KH_E)
	{// 注視点移動(上)

		// 注視点設定
		m_CameraState.posR.y += CAMERA_POSR_MOVEMENT_Y;
	}
	else if(KH_B && !KH_Q && !KH_E)
	{// 注視点移動(下)

		// 注視点設定
		m_CameraState.posR.y -= CAMERA_POSR_MOVEMENT_Y;
	}
	else if(KH_Q)
	{// 注視点移動(左)

		if(KH_T)
		{// 左上

			// 視点変更
			m_CameraState.posR.y += CAMERA_POSR_MOVEMENT_Y * sinf(PI * 0.25);
			
			// 角度増減
			m_CameraState.Rot.y += CAMERA_POSR_MOVEMENT_X * sinf(PI * 0.25);
		}
		else if(KH_B)
		{// 左下

			// 視点変更
			m_CameraState.posR.y -= CAMERA_POSR_MOVEMENT_Y * sinf(PI * 0.25);
			
			// 角度増減
			m_CameraState.Rot.y += CAMERA_POSR_MOVEMENT_X * sinf(PI * 0.25);
		}
		else
		{// 左

			// 角度増減
			m_CameraState.Rot.y += CAMERA_POSR_MOVEMENT_X;
		}
			
		// 視点注視点間距離更新
		m_CameraState.fDistance = hypotf((m_CameraState.posR.z - m_CameraState.posV.z), (m_CameraState.posR.x - m_CameraState.posV.x));
		
		// 注視点設定
		m_CameraState.posR.x = m_CameraState.posV.x + (sinf(m_CameraState.Rot.y) * m_CameraState.fDistance);
		m_CameraState.posR.z = m_CameraState.posV.z + (cosf(m_CameraState.Rot.y) * m_CameraState.fDistance);
	}
	else if(KH_E)
	{// 注視点移動(右)

		if(KH_T)
		{// 右上

			// 視点変更
			m_CameraState.posR.y += CAMERA_POSR_MOVEMENT_Y * sinf(PI * 0.25);
			
			// 角度増減
			m_CameraState.Rot.y -= CAMERA_POSR_MOVEMENT_X * sinf(PI * 0.25);
		}
		else if(KH_B)
		{// 右下

			// 視点変更
			m_CameraState.posR.y -= CAMERA_POSR_MOVEMENT_Y * sinf(PI * 0.25);
			
			// 角度増減
			m_CameraState.Rot.y -= CAMERA_POSR_MOVEMENT_X * sinf(PI * 0.25);
		}
		else
		{// 右

			// 角度増減
			m_CameraState.Rot.y -= CAMERA_POSR_MOVEMENT_X;
		}
			
		// 視点注視点間距離更新
		m_CameraState.fDistance = hypotf((m_CameraState.posR.z - m_CameraState.posV.z), (m_CameraState.posR.x - m_CameraState.posV.x));
		
		// 注視点設定
		m_CameraState.posR.x = m_CameraState.posV.x + (sinf(m_CameraState.Rot.y) * m_CameraState.fDistance);
		m_CameraState.posR.z = m_CameraState.posV.z + (cosf(m_CameraState.Rot.y) * m_CameraState.fDistance);
	}
}

//=============================================================================
//	関数名	:Set
//	引数	:無し
//	戻り値	:無し
//	説明	:カメラを設定する。
//=============================================================================
void CCameraGL::Set(void)
{
	// 2D描画準備
	glViewport(0, 0, (GLsizei)SCREEN_WIDTH, (GLsizei)SCREEN_HEIGHT);	// ウィンドウ全体をビューポートにする

	glMatrixMode(GL_PROJECTION);	// モデルビューマトリックスの設定(投影変換)
	glLoadIdentity();				// 変換行列の初期化
	gluPerspective(30.0, ((GLdouble)SCREEN_WIDTH/(GLdouble)SCREEN_HEIGHT), 1.0f, 100000.0f);

	glMatrixMode(GL_MODELVIEW);		// モデルビューマトリックスの設定
	glLoadIdentity();				// 変換行列の初期化
	gluLookAt(	m_CameraState.posV.x, m_CameraState.posV.y ,m_CameraState.posV.z,
				m_CameraState.posR.x, m_CameraState.posR.y ,m_CameraState.posR.z,
				m_CameraState.vecU.x, m_CameraState.vecU.y ,m_CameraState.vecU.z);
}