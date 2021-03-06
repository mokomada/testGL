#ifndef _TRICKGAUGE_H_
#define _TRICKGAUGE_H_
/******************************************************************************
インクルードファイル
*******************************************************************************/
#include "scene2DGL.h"

/******************************************************************************
マクロ定義
******************************************************************************/
/******************************************************************************
構造体定義
******************************************************************************/
/******************************************************************************
クラス
*******************************************************************************/
class CTrickGauge :public CScene2DGL
{
	public://誰でも使える
		CTrickGauge(bool ifListAdd = true, int priority = 1, OBJTYPE objType = OBJTYPE_NONE);
		~CTrickGauge( );
		void Init(void);
		void Update(void);
		void Draw(void);
		static CTrickGauge *Create( );
	private://自分しか使えない
		int	m_Texture;	// テクスチャ
		VECTOR3 m_StrPos;//開始位置
		int m_Size;		//サイズ
		float m_Pa;
		//そのゲージのマックス
		float m_GaugeMax;
		//現在のゲージ
		float m_Gauge;
	protected://継承先クラスでは使える
};
#endif