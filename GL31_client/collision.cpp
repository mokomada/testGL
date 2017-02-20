//=============================================================================
// ファイル: collision.h
// 作成者:   AT13A284 10 石橋拓巳
// 作成日:   2016/11/17
//=============================================================================
// 更新履歴:　-2016/11/17 石橋拓巳
//　　　　　　-V0.01 Inital Version
//=============================================================================
//=============================================================================
//	インクルード
//=============================================================================
#include "vector.h"
#include "sceneGL.h"
#include "collision.h"

////	当たり判定で使うボックスの情報
//typedef struct
//{
//	float width;
//	float height;
//	float depth;
//} BOX_DATA;

//=============================================================================
// グローバル変数
//=============================================================================
CCollision* CCollision::Instance = NULL;

//=============================================================================
// オブジェクトクラスの生成
//=============================================================================
CCollision::CCollision()
{

}

//=============================================================================
// オブジェクトクラスの破棄
//=============================================================================
CCollision::~CCollision()
{

}

//=============================================================================
//	球と球の当たり判定
//=============================================================================
bool CCollision::SphereToSphere(VECTOR3 Pos, float Radius, VECTOR3 _Pos, float _Radius)
{
	VECTOR3 sub = _Pos - Pos;
	float distance = VECTOR3::dot(sub, sub);
	float radius = Radius + _Radius;

	if (distance <= radius * radius)
	{
		return true;
	}
	return false;
}

//=============================================================================
//	ボックスとボックスの当たり判定
//=============================================================================
bool CCollision::BoxToBox(VECTOR3 Pos, BOX_DATA* Box, VECTOR3 _Pos, BOX_DATA* _Box)
{
	float WidthHalf1 = Box->width * 0.5f;
	float WidthHalf2 = _Box->width * 0.5f;
	if ((Pos.x + WidthHalf1 >= _Pos.x - WidthHalf2) && (Pos.x - WidthHalf1 <= _Pos.x + WidthHalf2))
	{
		float HightHalf1 = Box->height * 0.5f;
		float HightHalf2 = _Box->height * 0.5f;
		if ((Pos.y + HightHalf1 >= _Pos.y - HightHalf2) && (Pos.y - HightHalf1 <= _Pos.y + HightHalf2))
		{
			float DepthHalf1 = Box->depth * 0.5f;
			float DepthHalf2 = _Box->depth * 0.5f;
			if ((Pos.z + DepthHalf1 >= _Pos.z - DepthHalf2) && (Pos.z - DepthHalf1 <= _Pos.z + DepthHalf2))
			{
				return true;
			}
		}
	}

	return false;
}

//=============================================================================
//	ボックスと球の当たり判定
//=============================================================================
bool CCollision::SphereToBox(VECTOR3 &Pos, float Radius, VECTOR3 _Pos, BOX_DATA* _Box)
{
	VECTOR3 VtxPos1[6], VtxPos2[6], VtxPos3[6], VtxPos4[6];	//頂点の位置格納
	VECTOR3 Nor, Vec, _Vec, Position, Cross1, Cross2, Cross3;
	float Lenght, Dot1, Dot2;
	float WidthHalf = _Box->width * 0.5f;
	float HightHalf = _Box->height * 0.5f;
	float DepthHalf = _Box->depth * 0.5f;

	//=============================================================================
	//上
	VtxPos1[0] = VECTOR3(_Pos.x - WidthHalf, _Pos.y + HightHalf, _Pos.z - DepthHalf);
	VtxPos2[0] = VECTOR3(_Pos.x - WidthHalf, _Pos.y + HightHalf, _Pos.z + DepthHalf);
	VtxPos3[0] = VECTOR3(_Pos.x + WidthHalf, _Pos.y + HightHalf, _Pos.z - DepthHalf);
	VtxPos4[0] = VECTOR3(_Pos.x + WidthHalf, _Pos.y + HightHalf, _Pos.z + DepthHalf);
	//下
	VtxPos1[1] = VECTOR3(_Pos.x - WidthHalf, _Pos.y - HightHalf, _Pos.z + DepthHalf);
	VtxPos2[1] = VECTOR3(_Pos.x - WidthHalf, _Pos.y - HightHalf, _Pos.z - DepthHalf);
	VtxPos3[1] = VECTOR3(_Pos.x + WidthHalf, _Pos.y - HightHalf, _Pos.z + DepthHalf);
	VtxPos4[1] = VECTOR3(_Pos.x + WidthHalf, _Pos.y - HightHalf, _Pos.z - DepthHalf);
	//=============================================================================

	//=============================================================================
	//左
	VtxPos1[2] = VECTOR3(_Pos.x - WidthHalf, _Pos.y - HightHalf, _Pos.z - DepthHalf);
	VtxPos2[2] = VECTOR3(_Pos.x - WidthHalf, _Pos.y - HightHalf, _Pos.z + DepthHalf);
	VtxPos3[2] = VECTOR3(_Pos.x - WidthHalf, _Pos.y + HightHalf, _Pos.z - DepthHalf);
	VtxPos4[2] = VECTOR3(_Pos.x - WidthHalf, _Pos.y + HightHalf, _Pos.z + DepthHalf);
	//右
	VtxPos1[3] = VECTOR3(_Pos.x + WidthHalf, _Pos.y - HightHalf, _Pos.z + DepthHalf);
	VtxPos2[3] = VECTOR3(_Pos.x + WidthHalf, _Pos.y - HightHalf, _Pos.z - DepthHalf);
	VtxPos3[3] = VECTOR3(_Pos.x + WidthHalf, _Pos.y + HightHalf, _Pos.z + DepthHalf);
	VtxPos4[3] = VECTOR3(_Pos.x + WidthHalf, _Pos.y + HightHalf, _Pos.z - DepthHalf);
	//=============================================================================

	//=============================================================================
	//手前
	VtxPos1[4] = VECTOR3(_Pos.x - WidthHalf, _Pos.y - HightHalf, _Pos.z - DepthHalf);
	VtxPos2[4] = VECTOR3(_Pos.x - WidthHalf, _Pos.y + HightHalf, _Pos.z - DepthHalf);
	VtxPos3[4] = VECTOR3(_Pos.x + WidthHalf, _Pos.y - HightHalf, _Pos.z - DepthHalf);
	VtxPos4[4] = VECTOR3(_Pos.x + WidthHalf, _Pos.y + HightHalf, _Pos.z - DepthHalf);

	//奥
	VtxPos1[5] = VECTOR3(_Pos.x - WidthHalf, _Pos.y + HightHalf, _Pos.z + DepthHalf);
	VtxPos2[5] = VECTOR3(_Pos.x - WidthHalf, _Pos.y - HightHalf, _Pos.z + DepthHalf);
	VtxPos3[5] = VECTOR3(_Pos.x + WidthHalf, _Pos.y + HightHalf, _Pos.z + DepthHalf);
	VtxPos4[5] = VECTOR3(_Pos.x + WidthHalf, _Pos.y - HightHalf, _Pos.z + DepthHalf);
	//=============================================================================

	for (int count = 0; count < 6; count++)
	{
		if (SphereToPolygon(Pos, Radius, VtxPos1[count], VtxPos2[count], VtxPos3[count]) == true)
		{
			return true;
		}
		if (SphereToPolygon(Pos, Radius, VtxPos2[count], VtxPos3[count], VtxPos4[count]) == true)
		{
			return true;
		}
	}

	for (int count = 0; count < 6; count++)
	{
		if (SphereToLine(Pos, Radius, VtxPos2[count], VtxPos3[count], VtxPos4[count]) == true)
		{
			return true;
		}
		if (SphereToLine(Pos, Radius, VtxPos2[count], VtxPos3[count], VtxPos4[count]) == true)
		{
			return true;
		}
	}

	return false;
}

//=============================================================================
//	球とポリゴンの当たり判定
//=============================================================================
bool CCollision::SphereToPolygon(VECTOR3 &Pos, float Radius, VECTOR3 VtxPos1, VECTOR3 VtxPos2, VECTOR3 VtxPos3)
{
	VECTOR3 Nor, Vec, _Vec, Position, Cross1, Cross2, Cross3, Sub;
	float Lenght, Dot1, Dot2;

	Nor = VECTOR3::cross((VtxPos2 - VtxPos1), (VtxPos3 - VtxPos2));	//ポリゴンの法線
	Nor.normalize();

	Vec = Pos - VtxPos1;
	Lenght = VECTOR3::dot(Nor, Vec);
	Position = Pos - (Nor * Lenght);

	Vec = VtxPos2 - VtxPos1;
	_Vec = Position - VtxPos1;
	Cross1 = VECTOR3::cross(Vec, _Vec);

	Vec = VtxPos3 - VtxPos2;
	_Vec = Position - VtxPos2;
	Cross2 = VECTOR3::cross(Vec, _Vec);

	Vec = VtxPos1 - VtxPos3;
	_Vec = Position - VtxPos3;
	Cross3 = VECTOR3::cross(Vec, _Vec);

	Dot1 = VECTOR3::dot(Cross1, Cross2);
	Dot2 = VECTOR3::dot(Cross1, Cross3);

	if (Dot1 >= 0 && Dot2 >= 0)
	{
		Sub = Pos - Position;
		if (fabs(Lenght) <= Radius)
		{
			Pos += (Sub.normalize() * (Radius - fabs(Lenght)));
			return true;
		}
	}
	return false;
}

//=============================================================================
//	線分と球の当たり判定
//=============================================================================
bool CCollision::SphereToLine(VECTOR3 &Pos, float Radius, VECTOR3 VtxPos1, VECTOR3 VtxPos2, VECTOR3 VtxPos3)
{
	VECTOR3 Start, Vec, Sub, NearPoint, Nor;
	float rate;	//近時点の線分の割合

	Start = VtxPos1;				//線分の開始地点
	Vec = VtxPos2 - VtxPos1;	//線分の方向ベクトル

	rate = VECTOR3::dot(Vec, (Pos - Start)) / Vec3Length(Vec);	//近時点の線分の割合
	rate = Clamp(rate, 0.0f, 1.0f);												//設定した値を超えたら設定した値にする(下限.上限設定)

	NearPoint = (Vec * rate) + Start;	// 近時点を算出し返す;

	Sub = Pos - NearPoint;
	if (Vec3Length(Sub) <= Radius * Radius)
	{
		Nor = Sub;
		Pos += (Nor.normalize() * (Radius - Vec3LengthSq(Sub)));
		return true;
	}

	Start = VtxPos2;				//線分の開始地点
	Vec = VtxPos3 - VtxPos2;	//線分の方向ベクトル

	rate = VECTOR3::dot(Vec, (Pos - Start)) / Vec3Length(Vec);	//近時点の線分の割合
	rate = Clamp(rate, 0.0f, 1.0f);												//設定した値を超えたら設定した値にする(下限.上限設定)

	NearPoint = (Vec * rate) + Start;	// 近時点を算出し返す;

	Sub = Pos - NearPoint;
	if (Vec3Length(Sub) <= Radius * Radius)
	{
		Nor = Sub;
		float aaa = Vec3LengthSq(Sub);
		Pos += (Nor.normalize() * (Radius - aaa));
		return true;
	}

	Start = VtxPos3;				//線分の開始地点
	Vec = VtxPos1 - VtxPos3;	//線分の方向ベクトル

	rate = VECTOR3::dot(Vec, (Pos - Start)) / Vec3Length(Vec);	//近時点の線分の割合
	rate = Clamp(rate, 0.0f, 1.0f);												//設定した値を超えたら設定した値にする(下限.上限設定)

	NearPoint = (Vec * rate) + Start;	// 近時点を算出し返す;

	Sub = Pos - NearPoint;
	if (Vec3Length(Sub) <= Radius * Radius)
	{
		Nor = Sub;
		Pos += (Nor.normalize() * (Radius - Vec3LengthSq(Sub)));
		return true;
	}

	return false;
}

////=============================================================================
////	球とAABB(軸に平行なボックス)の当たり判定
////=============================================================================
//bool CCollision::SphereToAabb(VECTOR3 &Pos, float Radius, VECTOR3 _Pos, BOX_DATA* _Box)
//{
//	float WidthHalf = _Box->width * 0.5f, HightHalf = _Box->height * 0.5f, DepthHalf = _Box->depth * 0.5f;
//	float pos[3] = { Pos.x, Pos.y, Pos.z },
//		min[3] = { _Pos.x - WidthHalf, _Pos.y - HightHalf, _Pos.z - DepthHalf },
//		max[3] = { _Pos.x + WidthHalf, _Pos.y + HightHalf, _Pos.z + DepthHalf }, length = 0.0f;
//
//	for (int count = 0; count<3; count++)
//	{
//		// 各軸で点が最小値以下もしくは最大値以上ならば、差を考慮
//		if (pos[count] < min[count])
//		{
//			length += (pos[count] - min[count]) * (pos[count] - min[count]);
//		}
//		if (pos[count] > max[count])
//		{
//			length += (pos[count] - max[count]) * (pos[count] - max[count]);
//		}
//	}
//
//	length = sqrt(length);
//	if (length <= Radius)
//	{
//		/*VECTOR3 Sub = Pos - _Pos;
//		Pos += Sub.normalize() * (Radius - length);*/
//		SphereToBox(Pos, Radius, _Pos, _Box);
//		return true;
//	}
//
//	return false;
//}

//=============================================================================
//	球とAABB(軸に平行なボックス)の当たり判定
//=============================================================================
bool CCollision::SphereToAabb(VECTOR3 &Pos, float Radius, VECTOR3 _Pos, BOX_DATA* _Box)
{
	//球の中心に対する最近接点であるAABB上にある点Pointを見つける
	VECTOR3 Point;
	ClosestPtPointAABB(Pos, _Pos, _Box, Point);

	//球とAABBが交差するのは、球の中心から点Pointまでの(平方した)距離が(平方した)球の半径よりも小さい場合
	VECTOR3 vec = Point - Pos;
	if (Vec3Length(vec) <= Radius * Radius)
	{
		float sub = Vec3LengthSq(vec) - Radius;
		Pos += vec.normalize() * sub;
		return true;
	}

	return false;
}

//=============================================================================
//	与えられた点Pointに対して、AABB上もしくは中にあるPointの最近接点_Pointを返す
//=============================================================================
void CCollision::ClosestPtPointAABB(VECTOR3 &Pos, VECTOR3 _Pos, BOX_DATA* _Box, VECTOR3& Point)
{
	float point[3] = { Pos.x, Pos.y, Pos.z }, _point[3];
	float min[3] = { _Pos.x - _Box->width * 0.5f, _Pos.y - _Box->height * 0.5f, _Pos.z - _Box->depth * 0.5f };
	float max[3] = { _Pos.x + _Box->width * 0.5f, _Pos.y + _Box->height * 0.5f, _Pos.z + _Box->depth * 0.5f };

	//各座標軸に対して、点の座標値がボックスの外側にある場合に
	//ボックスまで点をクランプ、そうでなければそのまま
	for (int count = 0; count < 3; count++)
	{
		if (point[count] < min[count]) point[count] = min[count];	// point[count] = max(point[count], min[i]);
		if (point[count] > max[count]) point[count] = max[count];	// point[count] = min(point[count], max[i]);
		_point[count] = point[count];
	}

	Point = VECTOR3(_point[0], _point[1], _point[2]);
}

