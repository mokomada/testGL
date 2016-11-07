/*******************************************************************************
* �t�@�C���� camera.h
* �쐬�� AT-13A-284 �H�ԗY��
* �쐬�� 2016/04/27
*******************************************************************************/

/*** �C���N���[�h�K�[�h�J�n ***/
#ifndef _CAMERA_H_
#define _CAMERA_H_

/*******************************************************************************
* �}�N����`
*******************************************************************************/

#define CAMERA_MOVE_SPEED (0.1f) // �J�����̈ړ����x
#define CAMERA_ROT_SPEED (0.01f) // �J�����̉�]���x
#define CAMERA_ROT_TIME (30) // ������~�߂Ă����]���n�߂�܂ł̃t���[��

#define CAMERA_POSV_X (0.0f) // �J�����̎��_ X���W
#define CAMERA_POSV_Y (10.0f) // �J�����̎��_ Y���W
#define CAMERA_POSV_Z (20.0f) // �J�����̎��_ Z���W

#define CAMERA_POSR_X (0.0f) // �J�����̒����_ X���W
#define CAMERA_POSR_Y (0.0f) // �J�����̒����_ Y���W
#define CAMERA_POSR_Z (0.0f) // �J�����̒����_ Z���W

#define CAMERA_VEC_X (0.0f) // �J�����̏�����x�N�g�� X���W
#define CAMERA_VEC_Y (1.0f) // �J�����̏�����x�N�g�� Y���W
#define CAMERA_VEC_Z (0.0f) // �J�����̏�����x�N�g�� Z���W

#define CAMERA_DISTANCE_X (0.0f) // ���_-�����_�̋���(X)
#define CAMERA_DISTANCE_Y (5.0f) // ���_-�����_�̋���(Y)
#define CAMERA_DISTANCE_Z (50.0f) // ���_-�����_�̋���(Z)

#define CAMERA_CHANGE_DISTANCE (0.5f) // �����̕ύX���x
#define CAMERA_MAX_DISTANCE (50.0f) // �����̍ő�l
#define CAMERA_MIN_DISTANCE (12.0f) // �����̍ŏ��l

#define CAMERA_POSRMAX_Y (10.0f) // �����_�㉺�ʒu�̍ő�l
#define CAMERA_POSRMIN_Y (-10.0f) // �����_�㉺�ʒu�̍ŏ��l

#define CAMERA_POSVMAX_Y (10.0f) // ���_�̏㉺�ړ��ő�l
#define CAMERA_POSVMIN_Y (-10.0f) // ���_�̏㉺�ړ��ŏ��l


/*******************************************************************************
* �\���̒�`
*******************************************************************************/

typedef struct
{
	D3DXVECTOR3 posV; // ���_
	D3DXVECTOR3 posR; // �����_
	D3DXVECTOR3 vecU; // ������x�N�g��
	D3DXMATRIX mtxProjection; // �v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX mtxView; // �r���[�}�g���b�N�X
	D3DXVECTOR3 rot; // �����擾�p
	D3DXVECTOR3 fDistance; // ���_�`�����_�̋���
	float posR_y; // �����_�̏㉺�ړ��p
	float posV_y; // ���_�̏㉺�ړ��p
	float newRot;
	int rotTime;
} CAMERA;


/*******************************************************************************
* �J�����N���X
*******************************************************************************/

class CCamera{
private:
	CAMERA m_camera; // �J�����ݒ�

public:
	CCamera( ); // �R���X�g���N�^
	~CCamera( ); // �f�X�g���N�^

	void Init(void);
	void Uninit(void);
	void Update(void);
	void SetCamera(void);
	CAMERA GetCameraData(void);
};

#endif
/*** �C���N���[�h�K�[�h�I�� ***/