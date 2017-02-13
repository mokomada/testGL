#ifndef _PLAYER_H_
#define _PLAYER_H_
//=============================================================================
//
//	�^�C�g��	�v���C���[
//	�t�@�C����	player.h
//	�쐬��		AT13A284_10 �΋���
//	�쐬��		2016/12/5
//
//=============================================================================
#include "scene3DGL.h"
//=============================================================================
//	�}�N����`
//=============================================================================

#define	MODEL_POSX		(SCREEN_WIDTH * 0.5f)	// �|���S���̉���
#define	MODEL_POSY		(SCREEN_HEIGHT * 0.5f)	// �|���S���̏c��
#define	MODEL_SIZE		(30.0f)					// �|���S���̉���
#define	MODEL_TURN		(-0.15f)

#define	MODEL_MOVEMENT	(0.5f)					// �e�N�X�`���̃t�@�C����
#define	MODEL_ROT_STEP	(8)					// �v���C���[�̉�]�X�e�b�v

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

#define	BLINK_TIME (4)						// ��e���G�t�F�N�g�̓_�ł̊Ԋu


//=============================================================================
//	�\����
//=============================================================================
class CSceneModel;
class CLife;
class CParticle;

//=============================================================================
//	�N���X��`
//=============================================================================
class CPlayer : public CScene3DGL
{
public:
	CPlayer(bool ifListAdd = true, int priority = PRIORITY_PLAYER, OBJTYPE objType = OBJTYPE_PLAYER);
	~CPlayer();

	void	Init(uint whatPlayer = 0, VECTOR3 pos = VECTOR3(0.0f, 0.0f, 0.0f));
	void	Uninit(bool isLast = false);
	void	Update(void);
	void	Draw(void);

	static CPlayer	*Create(uint whatPlayer = 0, VECTOR3 pos = VECTOR3(0.0f, 0.0f, 0.0f));

	VECTOR3 GetVec(void) { return m_Move; }
	VECTOR3 GetOldPos(void) { return m_OldPos; }
	float GetGauge(void) { return m_Gauge; }
<<<<<<< HEAD
	void AddGauge(float Gauge) { m_Gauge += Gauge; }
	bool	m_ifMinePlayer;
=======
	void SetGauge(float Gauge) { m_Gauge = Gauge; }
>>>>>>> 79dfdeb1dfe681916cbb082fb4624d0dd8f0a903
	int GetPlayerLife(void);

private:
	uint	m_PlayerNumber;	// �v���C���[�ԍ�

	VECTOR3	m_OldPos;		// �O�t���[���̍��W
	VECTOR3	m_Scale;		// �X�P�[��
	VECTOR3	m_Move;			// �ړ���
	VECTOR3	m_RotMove;		// ��]��
	VECTOR3 m_MoveDirection;// �ړ�����
	bool	m_bJump;		// �W�����v�t���O
	float m_Gauge;
	bool m_FlgLowSpeed;
	int m_HitEffectTime; // ��e�G�t�F�N�g�̎��s����
	bool m_DrawOnOffFlag; // �`���ONOFF�ݒ�
	bool m_DeadFlag;

	CSceneModel* Model;
	CScene3DGL* Scene3D[2];
	CLife* m_pLife;
	CParticle*	m_pParticle;

	void CollisionDetection(void);
	static bool CollisionDetectionSphere(VECTOR3 Pos0, float Radius0, VECTOR3 Pos1, float Radius1);
	static bool CollisionDetectionBox(VECTOR3 Pos1, BOX_DATA* Box1, VECTOR3 Pos2, BOX_DATA* Box2);
	void HitEffect(void);
	void SetHitEffectTime(int time);
};

#endif