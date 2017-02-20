//=============================================================================
// ファイル: collision.h
// 作成者:   AT13A284 10 石橋拓巳
// 作成日:   2016/11/17
//=============================================================================
// 更新履歴:　-2016/11/17 石橋拓巳
//　　　　　　-V0.01 Inital Version
//=============================================================================
#ifndef _COLLISION_H_
#define _COLLISION_H_

//=============================================================================
//	インクルード
//=============================================================================
#include "vector.h"
#include "sceneGL.h"

//=============================================================================
//	クラス定義
//=============================================================================
class CCollision
{
public:
	//インスタンスを返す
	static CCollision* GetInstance() { return Instance == NULL ? Instance = new CCollision() : Instance; };
	bool PlayerToPlayer(VECTOR3 &Pos, float Radius, VECTOR3 &_Pos, float _Radius);
	bool SphereToSphere(VECTOR3 Pos, float Radius, VECTOR3 _Pos, float _Radius);
	bool BoxToBox(VECTOR3 Pos, BOX_DATA* Box, VECTOR3 _Pos, BOX_DATA* _Box);
	bool SphereToBox(VECTOR3 &Pos, float Radius, VECTOR3 _Pos, BOX_DATA* _Box);
	bool SphereToPolygon(VECTOR3 &Pos, float Radius, VECTOR3 VtxPos1, VECTOR3 VtxPos2, VECTOR3 VtxPos3);
	bool SphereToLine(VECTOR3 &Pos, float Radius, VECTOR3 VtxPos1, VECTOR3 VtxPos2, VECTOR3 VtxPos3);
	bool SphereToAabb(VECTOR3 &Pos, float Radius, VECTOR3 _Pos, BOX_DATA* _Box);

	void ClosestPtPointAABB(VECTOR3 Pos, VECTOR3 _Pos, BOX_DATA* _Box, VECTOR3& Point);

private:
	static CCollision *Instance;	//インスタンス

	//=============================================================================
	//	aの長さの二乗
	//=============================================================================
	float Vec3Length(const VECTOR3 &a) { return a.x * a.x + a.y * a.y + a.z * a.z; }
	//=============================================================================
	//	aの長さの平方根
	//=============================================================================
	float Vec3LengthSq(const VECTOR3 &a) { return sqrtf(a.x * a.x + a.y * a.y + a.z * a.z); }
	//=============================================================================
	//	最小値と最大値の間にクランプする
	//=============================================================================
	float Clamp(float clamp, float _min, float _max) { return min(max(clamp, _min), _max); }

	//コンストラクタ・デストラクタ
	//=============================================================================
	CCollision();
	~CCollision();
};

#endif