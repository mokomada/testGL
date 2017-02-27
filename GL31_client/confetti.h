#ifndef _CONFETTI_H_
#define _CONFETTI_H_
//=============================================================================
//
//	タイトル	ヘッダファイル(confetti.cpp)
//	ファイル名	confetti.h
//	作成者		AT13A284_29 塩原聖士
//	作成日		2016/11/16
//
//=============================================================================
#include "scene2DGL.h"
//=============================================================================
//	マクロ定義
//=============================================================================
//紙吹雪開始位置
#define CONFETTI_START_POSY ( 200.0f )

//=============================================================================
//	構造体
//=============================================================================
typedef struct
{
	float w;
	float x;
	float y;
	float z;
}Quat;

typedef struct
{
	float r;
	float g;
	float b;
	float a;
}COLOR;

//=============================================================================
//	クラス定義
//=============================================================================
class CConfetti : public CScene3DGL
{
public:
	CConfetti(bool ifListAdd = true, int priority = 1, OBJTYPE objtype = OBJTYPE_NONE);
	~CConfetti();
	
	void	Init(VECTOR3 pos, VECTOR2 size , VECTOR3 resistance, VECTOR3 rotaxis , float r , float g , float b , float a ,char* texName );
	void	Uninit(bool isLast = false);
	void	Update(void);
	void	Draw( void );
	static CConfetti	*Create(VECTOR3 pos, VECTOR2 size, VECTOR3 resistance , VECTOR3 rotaxis , float r = 1.0f , float g = 1.0f  , float b = 1.0f , float a = 1.0f , char* texName = NULL );
	static void CConfetti::MultiCreate(VECTOR3 pos, VECTOR2 size, VECTOR3 resistance  , int num , float r = 1.0f , float g = 1.0f  , float b = 1.0f , float a = 1.0f , char* texName = NULL );
	void QuatToMatrix( float *mat , Quat *quat );
	void CreateQuat(Quat *quat ,  float rot, float x, float y, float z);
	static void MasterCreate( );
	//色の設定とその構造体変数を渡す
	COLOR SetColor( float r , float g , float b , float a ){ COLOR col; col.r = r ; col.g = g; col.b = b; col.a = a; return col;};
	float CConfetti::Absolutef( float num );
protected:


private :
	VECTOR3 m_Pos;//座標
	VECTOR3 m_Rot;//角度
	VECTOR2 m_Size;		// ポリゴンのサイズ
	float m_VecX;
	float m_VecXAdd;
	float m_VecZ;

	float m_RotVec;
	float	m_Angle;	// 角度
	VECTOR3 m_Axis;
	int		m_Texture;// テクスチャ
	
	float m_BasePositionX;
	float m_BasePositionZ;
	COLOR m_Color;

	bool m_MoveStart;
	bool m_RandStart;
	int m_WaitTime;
	//重力加速度
	float m_Gravity;

	//重力落下抵抗率
	VECTOR3 m_GravityResistance;
	float m_GravityResistanceVector;
	float m_Matrix[ 16 ];
	Quat m_Quat;
	int m_Time;
};

#endif