#ifndef _SCENE2DANIMATION_H_
#define _SCENE2DANIMATION_H_
//=============================================================================
//
//	タイトル	ヘッダファイル(scene2D.cpp)
//	ファイル名	scene2D.h
//	作成者		AT13A284_07 池田達哉
//	作成日		2016/04/20
//
//=============================================================================
#include "sceneGL.h"
//=============================================================================
//	列挙体
//=============================================================================
typedef enum
{
	MOVETYPE_NONE = 0 ,
	MOVETYPE_LOOP ,
	MOVETYPE_STRAIGHT ,
}MOVETYPE;
//=============================================================================
//	マクロ定義
//=============================================================================
#define	POLYGON2D_WIDTH		(100.0f)				// ポリゴンの横幅
#define	POLYGON2D_HEIGHT	(100.0f)				// ポリゴンの縦幅

class CSceneMove;

//=============================================================================
//	クラス定義
//=============================================================================

//移動補助クラス
class CSceneMove
{
	public:
	CSceneMove();
	~CSceneMove();

	static CSceneMove *Create( VECTOR3 *pos , VECTOR3 *rot , VECTOR3 posaccele , VECTOR3 rotaccele , int time , MOVETYPE type );

	void Update();
	void Init(VECTOR3 *pos , VECTOR3 *rot , VECTOR3 posaccele , VECTOR3 rotaccele , int time , MOVETYPE type);

	private:
		VECTOR3 *m_PositionP;
		VECTOR3 *m_RotationP;
		VECTOR3 m_PositionAccele;
		VECTOR3 m_RotationAccele;
		int m_Time;
		int m_MaxTime;
		MOVETYPE m_Type;
		bool m_ReturnSwitch;
};
class CScene2DGLAnimation : public CSceneGL
{
public:
	CScene2DGLAnimation(bool ifListAdd = true, int priority = 0, OBJTYPE objType = OBJTYPE_NONE);
	~CScene2DGLAnimation();

	void	Init(VECTOR3 pos = VECTOR3(0.0f, 0.0f, 0.0f),
				VECTOR2 size = VECTOR2(POLYGON2D_WIDTH, POLYGON2D_HEIGHT ) , int maxside = 0, int maxlen = 0 , int maxanim = 0 , int maxtime = 0,
				char *texName = "./data/TEXTURE/sample_image.tga" , int tex = 0 );
	void	Uninit(bool isLast = false);
	void	Update(void);
	void	Draw(void);
	
	static CScene2DGLAnimation	*Create(VECTOR3 pos = VECTOR3(0.0f, 0.0f, 0.0f),
				VECTOR2 size = VECTOR2(POLYGON2D_WIDTH, POLYGON2D_HEIGHT ) , int maxside = 0, int maxlen = 0 , int maxanim = 0, int maxtime = 0 ,
				char *texName = "./data/TEXTURE/sample_image.tga" , int tex = 0 );

	void	DrawPolygon(void);

	void SetStartAnimation( bool start ){ m_Start = start; };//開始or停止スイッチ

	VECTOR3* GetPositionP( void ){ return &m_Position; };

	VECTOR3* GetRotationP( void ){ return &m_Rotation; };

	//移動補助の設定
	void SetMove( CSceneMove *move ){ m_Move = move; };

private:
	VECTOR2 m_Size;		// ポリゴンのサイズ
	float	m_fLength;	// 対角線の長さ
	float	m_fAngle;	// 角度
	int		m_Texture;	// テクスチャ

	int m_MaxSide; //最大横数
	int m_MaxLen; //最大縦数
	int m_NowAnim; //現在アニメーション番号
	int m_MaxAnim; //最大アニメーション番号
	int m_NowTime; //経過時間
	int m_MaxTime; //最大時間

	VECTOR3 m_Position;
	VECTOR3 m_Rotation;
	CSceneMove *m_Move;
	bool m_Use; //使用状態
	bool m_Start;
};

#endif