//=============================================================================
//
//	�^�C�g��	�w�b�_�t�@�C��(effect2D.cpp)
//	�t�@�C����	effect2D.h
//	�쐬��		AT13A284_20 �N�����
//	�쐬��		2016/11/21
//
//=============================================================================
//=============================================================================
//	�C���N���[�h�K�[�h
//=============================================================================
#pragma once

//=============================================================================
//	�C���N���[�h�w�b�_
//=============================================================================
#include "scene2DGL.h"
#include "manager.h"
#include "rendererGL.h"

//=============================================================================
//	�}�N����`
//=============================================================================
#define	BILLBOARD_WIDTH		(100.0f)				// �|���S���̉���
#define	BILLBOARD_HEIGHT	(100.0f)				// �|���S���̏c��

//=============================================================================
//	�\���̒�`
//=============================================================================
typedef enum
{
	ETYPE_NONE = 0,		// �Ȃ�
	ETYPE_EXPLODE00,	// �����G�t�F�N�g(��)
	ETYPE_EXPLODE01,	// �����G�t�F�N�g(��)
	ETYPE_SMOKE00,		// �y���G�t�F�N�g(�h���t�g)
	ETYPE_SMOKE01,		// ���G�t�F�N�g(�v���C�����S��)
	ETYPE_SMOKE02,		// ���G�t�F�N�g(�v���C��������)
}EFFECTTYPE;

typedef struct
{
	float Red;
	float Green;
	float Blue;
	float Alpha;
}EFFTEXCOLOR;

//=============================================================================
//	�O����`
//=============================================================================
class CSceneGL;

//=============================================================================
//	�N���X��`
//=============================================================================
class CEffect2D : public CScene2DGL
{
	private:
		VECTOR2 m_Size;						// �|���S���̃T�C�Y
		uint*	m_Texture;					// �e�N�X�`��
		MATRIX	m_mtxWorld;					// ���[���h�}�g���N�X

		/* �A�j���[�V�����֘A */
		int			m_nAnimX,m_nAnimY;			// �ڕW�A�j���[�V�����J�E���g��
		int			m_nAnimCntX, m_nAnimCntY;	// �A�j���[�V�����J�E���^
		int			m_nAnimChangeFrame;			// �A�j���[�V�����̐؂�ς��܂ł̃t���[����
		int			m_nAnimChangeFrameCnt;		// �A�j���[�V�����̐؂�ς��܂ł̃t���[���J�E���^
		EFFECTTYPE	m_Etype;					// �G�t�F�N�g�^�C�v
		bool		m_bEndFlugE;				// �ŏI�A�j���[�V�����\���㎩�E����t���O(�G�t�F�N�g)
		bool		m_bEndFlugP;				// �ŏI�A�j���[�V�����\���㎩�E����t���O(�p�[�e�B�N��)
		bool		m_bKasanFlug;				// ���Z���������t���O
		EFFTEXCOLOR m_aColor;					// �F�f�[�^

	public:		
		CEffect2D(bool ifListAdd = true,		// �R���X�g���N�^
				  int priority = 1,
				  OBJTYPE objType = OBJTYPE_NONE);	
		~CEffect2D();							// �f�X�g���N�^

		void Init(VECTOR3 pos		= VECTOR3(0.0f, 0.0f, 0.0f),	// ����������
				  VECTOR3 rot		= VECTOR3(0.0f, 0.0f, 0.0f),
				  VECTOR2 size		= VECTOR2(BILLBOARD_WIDTH, BILLBOARD_HEIGHT),
				  EFFECTTYPE etype	= ETYPE_NONE);

		void Uninit(bool isLast = false);							// �I������
		void Update(void);											// �X�V����
		void Draw(void);											// �`�揈��
		void DrawPolygon(void);										// �`�揈������Draw����
		void TypeInit(EFFECTTYPE etype);							// �G�t�F�N�g�^�C�v�ʂ̏���������
		void TypeUpdate(EFFECTTYPE etype);							// �G�t�F�N�g�^�C�v�ʂ̍X�V����
		bool GetEndFlugE(void);										// �G���h�t���O�擾(�ʏ�G�t�F�N�g)
		bool GetEndFlugP(void);										// �G���h�t���O�擾(�p�[�e�B�N���G�t�F�N�g)
		void SetEndFlugE(bool flug);								// �G���h�t���O�ύX(�ʏ�G�t�F�N�g)
		void SetEndFlugP(bool flug);								// �G���h�t���O�ύX(�p�[�e�B�N���G�t�F�N�g)
		
		//static float	m_CheckHeight;
		//static bool CheckHeight(CSceneGL *parent);

		static CEffect2D *Create(VECTOR3 pos = VECTOR3(0.0f, 0.0f, 0.0f),	// �쐬�֐�
								 VECTOR3 rot = VECTOR3(0.0f, 0.0f, 0.0f),
								 VECTOR2 size = VECTOR2(BILLBOARD_WIDTH, BILLBOARD_HEIGHT),
								 EFFECTTYPE etype = ETYPE_NONE);
};

//----------------------------------------------------------------------------------------------------------------------------
//														E	O	F
//----------------------------------------------------------------------------------------------------------------------------