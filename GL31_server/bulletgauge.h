#ifndef _BULLETGAUGE_H_
#define _BULLETGAUGE_H_
/******************************************************************************
インクルードファイル
*******************************************************************************/
#include "scene2DGL.h"

/******************************************************************************
マクロ定義
******************************************************************************/
#define BULLETGAUGESubtract 100.0f
#define GAUGENUMBER 3
/******************************************************************************
構造体定義
******************************************************************************/
/******************************************************************************
クラス
*******************************************************************************/
class CBulletGauge :public CScene2DGL
{
public://誰でも使える
	CBulletGauge(bool ifListAdd = true, int priority = 1, OBJTYPE objType = OBJTYPE_NONE);
	~CBulletGauge( );
	void Init(void);
	void Update(void);
	void Draw(void);
	float SubtractGauge(float f);
	float GetBulletGauge(void);
	static CBulletGauge *Create( );
private://自分しか使えない
	int	m_Texture[GAUGENUMBER];	// テクスチャ
	VECTOR3 m_StrPos[GAUGENUMBER];//開始位置
	int m_Size;		//サイズ
	float m_Pa[GAUGENUMBER];
	//そのゲージのマックス
	float m_GaugeMax[GAUGENUMBER];
	//はば
	float m_GaugeWidth[GAUGENUMBER];
	//現在のゲージ
	float m_Gauge;
};

#endif