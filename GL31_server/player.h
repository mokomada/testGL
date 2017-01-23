#ifndef _PLAYER_H_
#define _PLAYER_H_
//=============================================================================
//
//	タイトル	プレイヤー
//	ファイル名	player.h
//	作成者		AT13A284_10 石橋拓巳
//	作成日		2016/12/5
//
//=============================================================================
#include "scene3DGL.h"
//=============================================================================
//	マクロ定義
//=============================================================================

#define	MODEL_POSX		(SCREEN_WIDTH * 0.5f)	// ポリゴンの横幅
#define	MODEL_POSY		(SCREEN_HEIGHT * 0.5f)	// ポリゴンの縦幅
#define	MODEL_SIZE		(30.0f)					// ポリゴンの横幅
#define	MODEL_TURN		(-0.15f)

#define	MODEL_MOVEMENT	(0.5f)					// テクスチャのファイル名
#define	MODEL_ROT_STEP	(8)					// プレイヤーの回転ステップ
#define	GAUGE_MAX		(300.0f)			// プレイヤーのゲージマックス

#define	MODEL_SPEED_DOWN	(0.1f)			// プレイヤーの回転ステップ
#define	MODEL_SPEED_DOWNJ	(0.25f)			// プレイヤーの回転ステップ
#define	PLAYER_JUMP			(10.0f)			// プレイヤーの回転ステップ
#define	PLAYER_GRAVITY		(0.8f)			// プレイヤーの回転ステップ
#define	MOVE_ROT		(0.02f)				// プレイヤーの回転量
#define	MOVE_ROTJ		(0.01f)				// ジャンプ中のプレイヤーの回転量
#define	LOWMOVE_ROT		(0.005f)			// 低速中のプレイヤーの回転量
#define	LOWMOVE_ROTJ	(0.001f)			// 低速中のジャンプ中のプレイヤーの回転量
#define	FMOVE_SPEED		(0.8f)				// プレイヤーの前方移動量
#define	BMOVE_SPEED		(0.4f)				// プレイヤーの後方移動量
#define	LOWBMOVE_SPEED		(0.1f)			// 低速中のプレイヤーの後方移動量
#define	LOWFMOVE_SPEED		(0.2f)			// 低速中のプレイヤーの前方移動量

#define	BLINK_TIME (4)						// 被弾時エフェクトの点滅の間隔


//=============================================================================
//	構造体
//=============================================================================
class CSceneModel;
class CLife;
//=============================================================================
//	クラス定義
//=============================================================================
class CPlayer : public CScene3DGL
{
public:
	CPlayer(bool ifListAdd = true, int priority = PRIORITY_PLAYER, OBJTYPE objType = OBJTYPE_NONE);
	~CPlayer();

	void	Init(bool ifMinePlayer = false, VECTOR3 pos = VECTOR3(0.0f, 0.0f, 0.0f));
	void	Uninit(bool isLast = false);
	void	Update(void);
	void	Draw(void);

	static CPlayer	*Create(bool ifMinePlayer = false, VECTOR3 pos = VECTOR3(0.0f, 0.0f, 0.0f));

	float GetGauge(void) { return m_Gauge; }
	void SetGauge(float Gauge) { m_Gauge = Gauge; }
	bool	m_ifMinePlayer;

private:
	VECTOR3	m_Scale;		// スケール
	VECTOR3	m_Move;			// 移動量
	VECTOR3	m_RotMove;		// 回転量
	VECTOR3 m_MoveDirection;// 移動方向
	bool	m_bJump;		// ジャンプフラグ
	float m_Gauge;
	bool m_FlgLowSpeed;
	int m_HitEffectTime; // 被弾エフェクトの実行時間
	bool m_DrawOnOffFlag; // 描画のONOFF設定

	CSceneModel* Model;
	CLife* m_pLife;
	void CollisionDetection(void);
	static bool CollisionDetectionSphere(VECTOR3 Pos0, float Radius0, VECTOR3 Pos1, float Radius1);
	static bool CollisionDetectionBox(VECTOR3 Pos1, BOX_DATA* Box1, VECTOR3 Pos2, BOX_DATA* Box2);
	void HitEffect(void);
	void SetHitEffectTime(int time);
};

#endif