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
#include "game.h"

//=============================================================================
//	�}�N����`
//=============================================================================
#define	MODEL_TEXFILENAME000	"miku_01.tga"	// �|���S���̃t�@�C����
#define	MODEL_MOTION_NUM		(1)				// ���[�V������
#define	MODEL_POWER				(50.0f)			// ���f���̃f�[�^�{��

//=============================================================================
//	�\����
//=============================================================================
// �C���f�b�N�X
typedef struct{
	int	vtx;	// ���_
	int	tex;	// �e�N�X�`�����W
	int	nrm;	// �@��
} MODEL_INDEX;

// ���f�����
typedef struct{
	VECTOR3		*Pos;	// ���W
	VECTOR3		*Nrm;	// �@��
	VECTOR2		*Tex;	// �e�N�X�`�����W
//	�}�e���A��
	MODEL_INDEX	**Idx;// �C���f�b�N�X
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
class CSceneModel
{
public:
	CSceneModel(int priority = 1, OBJTYPE objType = OBJTYPE_NONE);
	~CSceneModel();

	void	Init(void){}
	void	Init(char* FileName);
	void	Uninit(bool isLast = false);
	void	Update(void);
	void	Draw(void);

	void	LoadModel(char *fileName);
	void	LoadMotion(char *fileName, int nNumMotion);
	void	DrawModel(void);

	static CSceneModel	*Create(char* FileName);
private:
	int		m_Texture;		// �e�N�X�`��
	PARTS	*m_Parts;		// ���f�����
	MOTION	*m_Motion;		// ���[�V�������
	int		m_nNumParts;	// �p�[�c��
	VECTOR3	m_Scale;		// �X�P�[��

	int		m_Frame;	// ���[�V�����J�E���^
	int		m_ExecMotion;	// ���s���̃��[�V����
};

#endif