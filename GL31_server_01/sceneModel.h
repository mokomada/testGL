#ifndef _SCENEMODEL_H_
#define _SCENEMODEL_H_
//=============================================================================
//
//	�^�C�g��	�w�b�_�t�@�C��(scene3D.cpp)
//	�t�@�C����	scene3D.h
//	�쐬��		AT13A284_07 �r�c�B��
//	�쐬��		2016/05/06
//
//=============================================================================
#include "scene3DGL.h"
//=============================================================================
//	�}�N����`
//=============================================================================
#define	MODEL_FILENAME000		"car.obj"	// ���f���t�@�C���̃t�@�C����
#define	MODEL_TEXFILENAME000	"miku_01.tga"	// �|���S���̃t�@�C����
#define	MODEL_MOTION_NUM		(1)				// ���[�V������
#define	MODEL_POWER				(50.0f)			// ���f���̃f�[�^�{��

#define	MODEL_POSX		(SCREEN_WIDTH * 0.5f)	// �|���S���̉���
#define	MODEL_POSY		(SCREEN_HEIGHT * 0.5f)	// �|���S���̏c��
#define	MODEL_SIZE		(30.0f)					// �|���S���̉���
#define	MODEL_TURN		(-0.15f)

#define	MODEL_MOVEMENT	(0.5f)					// �e�N�X�`���̃t�@�C����
#define	MODEL_ROT_STEP	(8)					// �v���C���[�̉�]�X�e�b�v
#define	GAUGE_MAX		(300.0f)			// �v���C���[�̃Q�[�W�}�b�N�X

#define	MODEL_SPEED_DOWN	(0.1f)			// �v���C���[�̉�]�X�e�b�v
#define	MODEL_SPEED_DOWNJ	(0.25f)			// �v���C���[�̉�]�X�e�b�v
#define	PLAYER_JUMP			(10.0f)			// �v���C���[�̉�]�X�e�b�v
#define	PLAYER_GRAVITY		(0.8f)			// �v���C���[�̉�]�X�e�b�v
#define	MOVE_ROT		(0.02f)				// �v���C���[�̉�]��
#define	MOVE_ROTJ		(0.01f)				// �W�����v���̃v���C���[�̉�]��
#define	LOWMOVE_ROT		(0.005f)			// �ᑬ���̃v���C���[�̉�]��
#define	LOWMOVE_ROTJ	(0.001f)			// �ᑬ���̃W�����v���̃v���C���[�̉�]��
#define	FMOVE_SPEED		(0.8f)				// �v���C���[�̑O���ړ���
#define	BMOVE_SPEED		(0.4f)				// �v���C���[�̌���ړ���
#define	LOWBMOVE_SPEED		(0.1f)			// �ᑬ���̃v���C���[�̌���ړ���
#define	LOWFMOVE_SPEED		(0.2f)			// �ᑬ���̃v���C���[�̑O���ړ���


//=============================================================================
//	�\����
//=============================================================================
// �C���f�b�N�X
typedef struct{
	int	vtx;	// ���_
	int	tex;	// �e�N�X�`�����W
	int	nrm;	// �@��
	void IdxRight(void) { vtx -= 1; tex -= 1; nrm -= 1; }
} MODEL_INDEX;

// ���f�����
typedef struct{
	vector<VECTOR3>	Vtx;	// ���W
	vector<VECTOR3>	Nrm;	// �@��
	vector<VECTOR2>	Tex;	// �e�N�X�`�����W
//	�}�e���A��
	vector<vector<MODEL_INDEX>> Idx;// �C���f�b�N�X
} MODEL_DATA;

// ���f�����
typedef struct{
	int	Pos;	// ���W
	int	Nrm;	// �@��
	int	Tex;	// �e�N�X�`�����W
	int	Idx;	// �C���f�b�N�X
} MODEL_DATA_NUM;

typedef struct{
	int		Parents;	// �e�I�u�W�F�N�g

	VECTOR3	Pos;		// �ʒu
	VECTOR3	Rot;		// ��]
	VECTOR3	Move;		// �ړ���
	VECTOR3	RotMove;	// ��]��
	MODEL_DATA		data;
	MODEL_DATA_NUM	dataNum;
} PARTS;

typedef struct{
	float	PosX, PosY, PosZ;	// �ʒu
	float	RotX, RotY, RotZ;	// ��]
} POSE;

typedef struct{
	int		Frame;		// �t���[����
	POSE	**Pose;	// ���[�V�����f�[�^
} MOTION;

//=============================================================================
//	�N���X��`
//=============================================================================
class CSceneModel : public CScene3DGL
{
public:
	CSceneModel(int priority = 1, OBJTYPE objType = OBJTYPE_NONE);
	~CSceneModel();

	void	Init(void){}
	void	Init(bool ifMinePlayer = false, VECTOR3 pos = VECTOR3(0.0f, 0.0f, 0.0f));
	void	Uninit(bool isLast = false);
	void	Update(void);
	void	Draw(void);

	static CSceneModel	*Create(bool ifMinePlayer = false, VECTOR3 pos = VECTOR3(0.0f, 0.0f, 0.0f));
	
	void	LoadModel(char *fileName);
	void	LoadMotion(char *fileName, int nNumMotion);
	void	DrawModel(void);

	float GetGauge(void) { return m_Gauge; }
	void SetGauge(float Gauge) { m_Gauge = Gauge; }
	bool	m_ifMinePlayer;

	float m_Radius;	//�����蔻��̔��a

private:
	int		m_Texture;		// �e�N�X�`��
	vector<PARTS>	m_Parts;		// ���f�����
	MOTION	*m_Motion;		// ���[�V�������
	int		m_nNumParts;	// �p�[�c��
	VECTOR3	m_Scale;		// �X�P�[��
	
	int		m_Frame;	// ���[�V�����J�E���^
	int		m_ExecMotion;	// ���s���̃��[�V����
	int		m_nCntMove;		// ��]�J�E���^
	VECTOR3	m_Move;			// �ړ���
	VECTOR3	m_RotMove;		// ��]��
	VECTOR3 m_MoveDirection;// �ړ�����
	bool	m_bJump;		// �W�����v�t���O
	float m_Gauge;
	bool m_FlgLowSpeed;

	void CollisionDetection(void);
};

#endif