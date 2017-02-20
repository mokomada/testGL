//=============================================================================
// �t�@�C��: collision.h
// �쐬��:   AT13A284 10 �΋���
// �쐬��:   2016/11/17
//=============================================================================
// �X�V����:�@-2016/11/17 �΋���
//�@�@�@�@�@�@-V0.01 Inital Version
//=============================================================================
#ifndef _COLLISION_H_
#define _COLLISION_H_

//=============================================================================
//	�C���N���[�h
//=============================================================================
#include "vector.h"
#include "sceneGL.h"

//=============================================================================
//	�N���X��`
//=============================================================================
class CCollision
{
public:
	//�C���X�^���X��Ԃ�
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
	static CCollision *Instance;	//�C���X�^���X

	//=============================================================================
	//	a�̒����̓��
	//=============================================================================
	float Vec3Length(const VECTOR3 &a) { return a.x * a.x + a.y * a.y + a.z * a.z; }
	//=============================================================================
	//	a�̒����̕�����
	//=============================================================================
	float Vec3LengthSq(const VECTOR3 &a) { return sqrtf(a.x * a.x + a.y * a.y + a.z * a.z); }
	//=============================================================================
	//	�ŏ��l�ƍő�l�̊ԂɃN�����v����
	//=============================================================================
	float Clamp(float clamp, float _min, float _max) { return min(max(clamp, _min), _max); }

	//�R���X�g���N�^�E�f�X�g���N�^
	//=============================================================================
	CCollision();
	~CCollision();
};

#endif