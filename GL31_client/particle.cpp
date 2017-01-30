//=============================================================================
//
//	タイトル	ヘッダファイル(Particle.cpp)
//	ファイル名	Particle.cpp
//	作成者		AT13A284_20 君島弥範
//	作成日		2016/12/13
//
//=============================================================================
//=============================================================================
//	インクルードヘッダ
//=============================================================================
#include "Particle.h"
#include "player.h"

//=============================================================================
//	関数名	:CSceneParticle()
//	引数	:無し
//	戻り値	:無し
//	説明	:コンストラクタ。
//=============================================================================
CParticle::CParticle(PRIORITY priority, OBJTYPE objType)
{}

//=============================================================================
//	関数名	:~CSceneParticle()
//	引数	:無し
//	戻り値	:無し
//	説明	:デストラクタ。
//=============================================================================
CParticle::~CParticle()
{}

//=============================================================================
//	関数名	:Init
//	引数	:VECTOR3 pos(初期位置),VECTOR2 size(サイズ), PARTICLE_TYPE pType(パーティクルタイプ)
//	戻り値	:無し
//	説明	:初期化処理を行うと共に、初期位置を設定する。
//=============================================================================
void CParticle::Init(VECTOR3 pos,VECTOR2 size,PARTICLE_TYPE pType, CSceneGL *parent)
{
	////	各変数の初期化処理
	///////////////////////////////////////////////////////////////////////////////////////
	m_Particle.pos		= pos;					// 初期位置
	m_Particle.move		= VECTOR2(0.0f,0.0f);	// 移動方向&速度
	m_Particle.m_Size	= size;					// ポリゴンのサイズ
	m_Particle.pType	= pType;				// パーティクルのタイプ
	m_Particle.nGenerateTime = 0;
	m_Particle.nLife	= LIFE;
	m_Parent = parent;
}

//=============================================================================
//	関数名	:Uninit
//	引数	:無し
//	戻り値	:無し
//	説明	:終了処理を行う。
//=============================================================================
void CParticle::Uninit(void)
{
}

//=============================================================================
//	関数名	:Update
//	引数	:無し
//	戻り値	:無し
//	説明	:更新処理を行う。
//=============================================================================
void CParticle::Update(void)
{

	//////	更新処理
	/////////////////////////////////////////////////////////////////////////////////////////
	// 位置更新
	CPlayer* player = ( CPlayer* )m_Parent;
	m_Particle.pos = m_Parent->GetPos();
	m_Particle.pos.y = -100.0f;

	//	一定フレーム数に達したら
	if(m_Particle.nGenerateTime >= GENERATE_TIME)
	{
		// 乱数生成
		int RandHosei = rand()%40 - 20;
		
		// パーティクル生成
		CEffect2D::Create(VECTOR3(m_Particle.pos.x + RandHosei,m_Particle.pos.y,m_Particle.pos.z),m_Particle.m_Size,ETYPE_SMOKE00);
		
		// カウンタ初期化
		m_Particle.nGenerateTime = 0;

		// ライフを減らす
		m_Particle.nLife--;
	}

	// カウンタ加算
		m_Particle.nGenerateTime++;
}

//=============================================================================
//	関数名	:Draw
//	引数	:無し
//	戻り値	:無し
//	説明	:描画処理を行う。
//=============================================================================
void CParticle::Draw(void)
{}

//=============================================================================
//	関数名	:Create
//	引数	:VECTOR3 pos(初期位置)
//	戻り値	:無し
//	説明	:インスタンス生成を行うと共に、初期位置を設定する。
//=============================================================================
CParticle *CParticle::Create(VECTOR3 pos, VECTOR2 size, PARTICLE_TYPE ptype,CSceneGL *parent)
{
	CParticle *particle;

	particle = new CParticle;

	particle->Init(pos, size, ptype, parent);

	return particle;
}

