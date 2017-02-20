//=============================================================================
// �t�@�C��: collision.h
// �쐬��:   AT13A284 10 �΋���
// �쐬��:   2016/11/17
//=============================================================================
// �X�V����:�@-2016/11/17 �΋���
//�@�@�@�@�@�@-V0.01 Inital Version
//=============================================================================
//=============================================================================
//	�C���N���[�h
//=============================================================================
#include "vector.h"
#include "sceneGL.h"
#include "collision.h"

////	�����蔻��Ŏg���{�b�N�X�̏��
//typedef struct
//{
//	float width;
//	float height;
//	float depth;
//} BOX_DATA;

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
CCollision* CCollision::Instance = NULL;

//=============================================================================
// �I�u�W�F�N�g�N���X�̐���
//=============================================================================
CCollision::CCollision()
{

}

//=============================================================================
// �I�u�W�F�N�g�N���X�̔j��
//=============================================================================
CCollision::~CCollision()
{

}

//=============================================================================
//	���Ƌ��̓����蔻��
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
//	�{�b�N�X�ƃ{�b�N�X�̓����蔻��
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
//	�{�b�N�X�Ƌ��̓����蔻��
//=============================================================================
bool CCollision::SphereToBox(VECTOR3 &Pos, float Radius, VECTOR3 _Pos, BOX_DATA* _Box)
{
	VECTOR3 VtxPos1[6], VtxPos2[6], VtxPos3[6], VtxPos4[6];	//���_�̈ʒu�i�[
	VECTOR3 Nor, Vec, _Vec, Position, Cross1, Cross2, Cross3;
	float Lenght, Dot1, Dot2;
	float WidthHalf = _Box->width * 0.5f;
	float HightHalf = _Box->height * 0.5f;
	float DepthHalf = _Box->depth * 0.5f;

	//=============================================================================
	//��
	VtxPos1[0] = VECTOR3(_Pos.x - WidthHalf, _Pos.y + HightHalf, _Pos.z - DepthHalf);
	VtxPos2[0] = VECTOR3(_Pos.x - WidthHalf, _Pos.y + HightHalf, _Pos.z + DepthHalf);
	VtxPos3[0] = VECTOR3(_Pos.x + WidthHalf, _Pos.y + HightHalf, _Pos.z - DepthHalf);
	VtxPos4[0] = VECTOR3(_Pos.x + WidthHalf, _Pos.y + HightHalf, _Pos.z + DepthHalf);
	//��
	VtxPos1[1] = VECTOR3(_Pos.x - WidthHalf, _Pos.y - HightHalf, _Pos.z + DepthHalf);
	VtxPos2[1] = VECTOR3(_Pos.x - WidthHalf, _Pos.y - HightHalf, _Pos.z - DepthHalf);
	VtxPos3[1] = VECTOR3(_Pos.x + WidthHalf, _Pos.y - HightHalf, _Pos.z + DepthHalf);
	VtxPos4[1] = VECTOR3(_Pos.x + WidthHalf, _Pos.y - HightHalf, _Pos.z - DepthHalf);
	//=============================================================================

	//=============================================================================
	//��
	VtxPos1[2] = VECTOR3(_Pos.x - WidthHalf, _Pos.y - HightHalf, _Pos.z - DepthHalf);
	VtxPos2[2] = VECTOR3(_Pos.x - WidthHalf, _Pos.y - HightHalf, _Pos.z + DepthHalf);
	VtxPos3[2] = VECTOR3(_Pos.x - WidthHalf, _Pos.y + HightHalf, _Pos.z - DepthHalf);
	VtxPos4[2] = VECTOR3(_Pos.x - WidthHalf, _Pos.y + HightHalf, _Pos.z + DepthHalf);
	//�E
	VtxPos1[3] = VECTOR3(_Pos.x + WidthHalf, _Pos.y - HightHalf, _Pos.z + DepthHalf);
	VtxPos2[3] = VECTOR3(_Pos.x + WidthHalf, _Pos.y - HightHalf, _Pos.z - DepthHalf);
	VtxPos3[3] = VECTOR3(_Pos.x + WidthHalf, _Pos.y + HightHalf, _Pos.z + DepthHalf);
	VtxPos4[3] = VECTOR3(_Pos.x + WidthHalf, _Pos.y + HightHalf, _Pos.z - DepthHalf);
	//=============================================================================

	//=============================================================================
	//��O
	VtxPos1[4] = VECTOR3(_Pos.x - WidthHalf, _Pos.y - HightHalf, _Pos.z - DepthHalf);
	VtxPos2[4] = VECTOR3(_Pos.x - WidthHalf, _Pos.y + HightHalf, _Pos.z - DepthHalf);
	VtxPos3[4] = VECTOR3(_Pos.x + WidthHalf, _Pos.y - HightHalf, _Pos.z - DepthHalf);
	VtxPos4[4] = VECTOR3(_Pos.x + WidthHalf, _Pos.y + HightHalf, _Pos.z - DepthHalf);

	//��
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
//	���ƃ|���S���̓����蔻��
//=============================================================================
bool CCollision::SphereToPolygon(VECTOR3 &Pos, float Radius, VECTOR3 VtxPos1, VECTOR3 VtxPos2, VECTOR3 VtxPos3)
{
	VECTOR3 Nor, Vec, _Vec, Position, Cross1, Cross2, Cross3, Sub;
	float Lenght, Dot1, Dot2;

	Nor = VECTOR3::cross((VtxPos2 - VtxPos1), (VtxPos3 - VtxPos2));	//�|���S���̖@��
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
//	�����Ƌ��̓����蔻��
//=============================================================================
bool CCollision::SphereToLine(VECTOR3 &Pos, float Radius, VECTOR3 VtxPos1, VECTOR3 VtxPos2, VECTOR3 VtxPos3)
{
	VECTOR3 Start, Vec, Sub, NearPoint, Nor;
	float rate;	//�ߎ��_�̐����̊���

	Start = VtxPos1;				//�����̊J�n�n�_
	Vec = VtxPos2 - VtxPos1;	//�����̕����x�N�g��

	rate = VECTOR3::dot(Vec, (Pos - Start)) / Vec3Length(Vec);	//�ߎ��_�̐����̊���
	rate = Clamp(rate, 0.0f, 1.0f);												//�ݒ肵���l�𒴂�����ݒ肵���l�ɂ���(����.����ݒ�)

	NearPoint = (Vec * rate) + Start;	// �ߎ��_���Z�o���Ԃ�;

	Sub = Pos - NearPoint;
	if (Vec3Length(Sub) <= Radius * Radius)
	{
		Nor = Sub;
		Pos += (Nor.normalize() * (Radius - Vec3LengthSq(Sub)));
		return true;
	}

	Start = VtxPos2;				//�����̊J�n�n�_
	Vec = VtxPos3 - VtxPos2;	//�����̕����x�N�g��

	rate = VECTOR3::dot(Vec, (Pos - Start)) / Vec3Length(Vec);	//�ߎ��_�̐����̊���
	rate = Clamp(rate, 0.0f, 1.0f);												//�ݒ肵���l�𒴂�����ݒ肵���l�ɂ���(����.����ݒ�)

	NearPoint = (Vec * rate) + Start;	// �ߎ��_���Z�o���Ԃ�;

	Sub = Pos - NearPoint;
	if (Vec3Length(Sub) <= Radius * Radius)
	{
		Nor = Sub;
		float aaa = Vec3LengthSq(Sub);
		Pos += (Nor.normalize() * (Radius - aaa));
		return true;
	}

	Start = VtxPos3;				//�����̊J�n�n�_
	Vec = VtxPos1 - VtxPos3;	//�����̕����x�N�g��

	rate = VECTOR3::dot(Vec, (Pos - Start)) / Vec3Length(Vec);	//�ߎ��_�̐����̊���
	rate = Clamp(rate, 0.0f, 1.0f);												//�ݒ肵���l�𒴂�����ݒ肵���l�ɂ���(����.����ݒ�)

	NearPoint = (Vec * rate) + Start;	// �ߎ��_���Z�o���Ԃ�;

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
////	����AABB(���ɕ��s�ȃ{�b�N�X)�̓����蔻��
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
//		// �e���œ_���ŏ��l�ȉ��������͍ő�l�ȏ�Ȃ�΁A�����l��
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
//	����AABB(���ɕ��s�ȃ{�b�N�X)�̓����蔻��
//=============================================================================
bool CCollision::SphereToAabb(VECTOR3 &Pos, float Radius, VECTOR3 _Pos, BOX_DATA* _Box)
{
	//���̒��S�ɑ΂���ŋߐړ_�ł���AABB��ɂ���_Point��������
	VECTOR3 Point;
	ClosestPtPointAABB(Pos, _Pos, _Box, Point);

	//����AABB����������̂́A���̒��S����_Point�܂ł�(��������)������(��������)���̔��a�����������ꍇ
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
//	�^����ꂽ�_Point�ɑ΂��āAAABB��������͒��ɂ���Point�̍ŋߐړ__Point��Ԃ�
//=============================================================================
void CCollision::ClosestPtPointAABB(VECTOR3 &Pos, VECTOR3 _Pos, BOX_DATA* _Box, VECTOR3& Point)
{
	float point[3] = { Pos.x, Pos.y, Pos.z }, _point[3];
	float min[3] = { _Pos.x - _Box->width * 0.5f, _Pos.y - _Box->height * 0.5f, _Pos.z - _Box->depth * 0.5f };
	float max[3] = { _Pos.x + _Box->width * 0.5f, _Pos.y + _Box->height * 0.5f, _Pos.z + _Box->depth * 0.5f };

	//�e���W���ɑ΂��āA�_�̍��W�l���{�b�N�X�̊O���ɂ���ꍇ��
	//�{�b�N�X�܂œ_���N�����v�A�����łȂ���΂��̂܂�
	for (int count = 0; count < 3; count++)
	{
		if (point[count] < min[count]) point[count] = min[count];	// point[count] = max(point[count], min[i]);
		if (point[count] > max[count]) point[count] = max[count];	// point[count] = min(point[count], max[i]);
		_point[count] = point[count];
	}

	Point = VECTOR3(_point[0], _point[1], _point[2]);
}

