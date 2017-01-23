#ifndef _CAMERAGL_H_
#define _CAMERAGL_H_
//=============================================================================
//
//	�^�C�g��	�w�b�_�t�@�C��(scene.cpp)
//	�t�@�C����	scene.h
//	�쐬��		AT13A284_07 �r�c�B��
//	�쐬��		2016/04/19
//
//=============================================================================
#include "main.h"
//=============================================================================
//	�}�N����`
//=============================================================================
#define	CAMERA_NEARZ				(10.0f)			// NearZ�l
#define	CAMERA_FARZ					(10000.0f)		// FarZ�l
#define	CAMERA_DEFAULT_DISTANCE		(200.0f)		// �����̎��_�\�����_�ԋ���

#define	CAMERA_POSV_MOVEMENT		(3.0f)			// ���_�̈ړ����x
#define	CAMERA_POSR_MOVEMENT_X		(0.025f)			// �����_�̈ړ���(���E)
#define	CAMERA_POSR_MOVEMENT_Y		(3.0f)			// �����_�̈ړ���(�㉺)


#define	CAMERA_POSV_XSET	300.0f,	100.0f,	0.0f		// X��������̃J����
#define	CAMERA_POSV_YSET	0.0f,	300.0f,	1.0f		// Y��������̃J����
#define	CAMERA_POSV_ZSET	0.0f,	100.0f,	300.0f		// Z��������̃J����

//=============================================================================
//	�\����
//=============================================================================
typedef struct{	// �J�������
	VECTOR3	posV;			// ���_
	VECTOR3	posR;			// �����_
	VECTOR3	vecU;			// ������x�N�g��
	MATRIX	mtxPojection;	// �v���W�F�N�V�����}�g���b�N�X
	MATRIX	mtxView;		// �r���[�}�g���b�N�X
	VECTOR3 Rot;			// ��]�p
	float	fDistance;		// ���_�\�����_�ԋ���
	float	fDisMax;		// ���_�\�����_�ԍő勗��
}CAMERA;

//=============================================================================
//	�N���X��`
//=============================================================================
class CCameraGL
{
public:
	CCameraGL();
	~CCameraGL();

	void	Init(void);
	void	Uninit(void);
	void	Update(void);
	void	Set(void);
	void	SetPosV(VECTOR3 pos){ 
		m_CameraState.posV = pos;
		m_CameraState.Rot.y = atan2f((m_CameraState.posR.x - m_CameraState.posV.x), (m_CameraState.posR.z - m_CameraState.posV.z)); }

	void	SetPosR(VECTOR3 pos) {
		m_CameraState.posR = pos;
		m_CameraState.Rot.y = atan2f((m_CameraState.posR.x - m_CameraState.posV.x), (m_CameraState.posR.z - m_CameraState.posV.z));
	}
	
	CAMERA	m_CameraState;			// �J����

protected:


};

#endif