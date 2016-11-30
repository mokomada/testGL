//=============================================================================
//
//	�^�C�g��	�w�b�_�t�@�C��(effect2D.cpp)
//	�t�@�C����	effect2D.h
//	�쐬��		AT13A284_20 �N�����
//	�쐬��		2016/11/21
//
//=============================================================================
//=============================================================================
//	�}�N����`
//=============================================================================
#ifndef _EFFECT2D_H_
#define _EFFECT2D_H_

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

/////////////////////
/*   �t�@�C����    */
/////////////////////
#define	EXPLODE_TEXFILENAME000	"./data/TEXTURE/explosion000.tga"	// �����e�X�g�G�t�F�N�g(8x1)
#define	EXPLODE_TEXFILENAME001	"./data/TEXTURE/explosion001.tga"	// �����e�X�g�G�t�F�N�g(7x1)
#define	NUMBER_TEXFILENAME0000  "./data/TEXTURE/number000.tga"		// �����e�X�g�摜(10x1)

/////////////////////////////////
/*   �A�j���[�V�����O���b�h    */
/////////////////////////////////
#define EXPLODE00_X	(8)
#define EXPLODE00_Y	(1)
#define EXPLODE01_X	(7)
#define EXPLODE01_Y	(1)
#define NUMBER_X	(10)
#define NUMBER_Y	(1)

/////////////////
/*   ���̑�    */
/////////////////
#define ANIMATION_CHANGE_FRAME_COUNT	(15)						// �A�j���[�V�������؂�ւ��܂ł̃t���[����

//=============================================================================
//	�\���̒�`
//=============================================================================
typedef enum
{
	ETYPE_NONE = 0,	// �Ȃ�
	ETYPE_EXPLODE00,	// �����G�t�F�N�g(�e�X�g)
	ETYPE_EXPLODE01,	// �����G�t�F�N�g
	ETYPE_NUMBER,	// �e�X�g�p���摜
}EFFECTTYPE;

//=============================================================================
//	�N���X��`
//=============================================================================
class CEffect2D : public CScene2DGL
{
	public:
		CEffect2D(int priority = 1, OBJTYPE objType = OBJTYPE_NONE);	// �R���X�g���N�^
		~CEffect2D();													// �f�X�g���N�^

		void Init(void){}
		void Init(VECTOR3 pos		= VECTOR3(0.0f, 0.0f, 0.0f),			// ����������
				  VECTOR2 size		= VECTOR2(BILLBOARD_WIDTH, BILLBOARD_HEIGHT),
				  EFFECTTYPE etype	= ETYPE_NONE);

		void Uninit(bool isLast = false);							// �I������
		void Update(void);											// �X�V����
		void Draw(void);											// �`�揈��
		void DrawPolygon(void);										// �`�揈������Draw����

		static CEffect2D *Create(VECTOR3 pos = VECTOR3(0.0f, 0.0f, 0.0f),			// �쐬�֐�
								 VECTOR2 size = VECTOR2(BILLBOARD_WIDTH, BILLBOARD_HEIGHT),
								 EFFECTTYPE etype = ETYPE_NONE);
		

	private:
		VECTOR2 m_Size;						// �|���S���̃T�C�Y
		int		m_Texture;					// �e�N�X�`��
		MATRIX	m_mtxWorld;					// ���[���h�}�g���N�X

		/* �A�j���[�V�����֘A */
		int		m_nAnimX,m_nAnimY;			// �ڕW�A�j���[�V�����J�E���g��
		int		m_nAnimCntX, m_nAnimCntY;	// �A�j���[�V�����J�E���^
		int		m_nAnimChangeFrameCnt;		// �A�j���[�V�����̐؂�ς��܂ł̃t���[���J�E���^
		bool	m_bEndflug;					// �ŏI�A�j���[�V�����\���㎩�E����t���O
};

#endif