//=============================================================================
//
//	�^�C�g��	�w�b�_�t�@�C��(Particle.h)
//	�t�@�C����	Particle.h
//	�쐬��		AT13A284_20 �N�����
//	�쐬��		2016/12/13
//
//=============================================================================
//=============================================================================
//	�}�N����`
//=============================================================================
#ifndef _PARTICLE_H_
#define _PARTICLE_H_

//=============================================================================
//	�C���N���[�h�w�b�_
//=============================================================================
#include "scene2DGL.h"
#include "manager.h"
#include "rendererGL.h"
#include "effect2D.h"

//=============================================================================
//	�}�N����`
//=============================================================================
#define MAX_PARTICLE		(1000)		// �p�[�e�B�N���̍ő吔		
#define GENERATE_TIME		(60)		// �����Ԋu
#define LIFE				(1000)		// �ő唭����(���̐�������������)
#define	PARTICLE_WIDTH		(100.0f)	// �|���S���̉���
#define	PARTICLE_HEIGHT		(100.0f)	// �|���S���̏c��

//=============================================================================
//	�\���̒�`
//=============================================================================
typedef enum
{
	PARTICLE_NONE = 0,	// �Ȃ�
	PARTICLE_EXPLODE,	// �����G�t�F�N�g
	PARTICLE_SMOKE,		// ��
}PARTICLE_TYPE;

typedef struct 
{
	MATRIX	m_mtxWorld;					// ���[���h�}�g���N�X
	VECTOR3 pos;						// �����ʒu
	VECTOR2 move;						// �ړ�����&���x
	VECTOR2 m_Size;						// �|���S���̃T�C�Y
	int nGenerateTime;					// �����^�C�}�J�E���^
	int nLife;							// ����
	PARTICLE_TYPE pType;				// �p�[�e�B�N���̃^�C�v
}PARTICLE;


//=============================================================================
//	�N���X��`
//=============================================================================
class CParticle
{
	private:
		PARTICLE m_Particle;
		CSceneGL* m_Parent;

	public:
		CParticle(PRIORITY priority = PRIORITY_NONE, OBJTYPE objType = OBJTYPE_NONE);				// �R���X�g���N�^
		~CParticle();																				// �f�X�g���N�^
		void Init(VECTOR3 pos,VECTOR2 size,PARTICLE_TYPE pType,CSceneGL *parent);					// ����������
		void Uninit();																				// �I������
		void Update(void);																			// �X�V����
		void Draw(void);																			// �`�揈��
		static CParticle *Create(VECTOR3 pos,VECTOR2 size,PARTICLE_TYPE pType,CSceneGL *parent);	// �쐬�֐�
};

#endif