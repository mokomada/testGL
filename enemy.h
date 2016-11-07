/*******************************************************************************
* �t�@�C���� sceneX.h
* �쐬�� AT-13A-284 �H�ԗY��
* �쐬�� 2016/04/26
*******************************************************************************/

/*** �C���N���[�h�K�[�h�J�n ***/
#ifndef _ENEMY_H_
#define _ENEMY_H_


/*******************************************************************************
* �}�N����`
*******************************************************************************/

#define ENEMY_NAME "data/MODEL/dog.x" // �ǂݍ���X�t�@�C����
#define ENEMY_TEXTURE_NAME NULL // �e�N�X�`����

#define ENEMY_MOVE_SPEED (0.5f) // ���f���̈ړ����x
#define ENEMY_ROT_SPEED (0.03f) // ���f���̉�]���x
#define ENEMY_JUMP_SPEED (2.0f) // ���f���̃W�����v��
#define ENEMY_FALL_SPEED (0.2f) // ���f���̗������x

#define ENEMY_SCALE_X (1.0f) // �X�P�[���l X��
#define ENEMY_SCALE_Y (1.0f) // �X�P�[���l Y��
#define ENEMY_SCALE_Z (1.0f) // �X�P�[���l Z��

#define ENEMY_ROT_X (0.0f) // ��]�� X��
#define ENEMY_ROT_Y (0.0f) // ��]�� Y��
#define ENEMY_ROT_Z (0.0f) // ��]�� Z��

#define ENEMY_POS_X (0.0f) // �ʒu��� X��
#define ENEMY_POS_Y (0.0f) // �ʒu��� Y��
#define ENEMY_POS_Z (0.0f) // �ʒu��� Z��

#define ENEMY_MOVE_MAX (3.0f) // �ő�ړ���
#define ENEMY_MOVE_REDUCE (0.0f) // �ړ��ʌ�����
#define ENEMY_FALL_REDUCE (0.8f) // �������x������

#define ENEMY_VIEW_DISTANCE (0.0f) // ���f���̒��S�_���璍���_�܂ł̋���

#define ENEMY_MOVE_CHANGE (30) // �ړ�������ύX����܂ł̎���
#define ENEMY_RESPAWN_TIME (300) // ���X�|�[���܂ł̎���
#define ENEMY_START_DISTANCE (20.0f) // �����ʒu�̃v���C���[�Ƃ̍Œ዗��

#define ENEMY_MAX (3) // �G�l�~�[�̍ő吔

/*******************************************************************************
* �\���̒�`
*******************************************************************************/


/*******************************************************************************
* 3D�|���S���N���X
*******************************************************************************/

class CEnemy : public CSceneX{
private:
	//LPDIRECT3DTEXTURE9 m_pTexture;
	//LPD3DXMESH m_pMesh; // ���b�V�����
	//LPD3DXBUFFER m_pBuffMat; // �}�e���A�����
	//DWORD m_numMat; // �}�e���A���̐�
	//D3DXMATRIX m_mtxWorld; // ���[���h�}�g���b�N�X
	MODEL m_enemy;
	float m_newRot;
	int m_moveChange;
	int m_respawn;
	bool m_moveFlag;
	int m_rnd;

public:
	CEnemy(int priority = 1, OBJTYPE objType = OBJTYPE_ENEMY); // �R���X�g���N�^
	~CEnemy( ); // �f�X�g���N�^

	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CEnemy *Create(void); // �K�v�ɉ����ď����ʒu��p�x���̈�����
	MODEL GetEnemy(void);
};


#endif
/*** �C���N���[�h�K�[�h�I�� ***/