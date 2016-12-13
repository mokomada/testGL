//=============================================================================
//
//	�^�C�g��	�w�b�_�t�@�C��(2DEffect.cpp)
//	�t�@�C����	2DEffect.h
//	�쐬��		AT13A284_20 �N�����
//	�쐬��		2016/11/21
//
//=============================================================================
//=============================================================================
//	�C���N���[�h�w�b�_
//=============================================================================
#include "main.h"
#include "manager.h"
#include "rendererGL.h"
#include "effect2D.h"
#include"textureManager.h"

//=============================================================================
//	�֐���	:CSceneBillboard()
//	����	:����
//	�߂�l	:����
//	����	:�R���X�g���N�^�B
//=============================================================================
CEffect2D::CEffect2D(bool ifListAdd, int priority, OBJTYPE objType) : CScene2DGL(ifListAdd, priority, objType)
{
	glMatrixIdentity(&m_mtxWorld);
}

//=============================================================================
//	�֐���	:~CSceneBillboard()
//	����	:����
//	�߂�l	:����
//	����	:�f�X�g���N�^�B
//=============================================================================
CEffect2D::~CEffect2D()
{}

//=============================================================================
//	�֐���	:Init
//	����	:VECTOR3 pos(�����ʒu)
//	�߂�l	:����
//	����	:�������������s���Ƌ��ɁA�����ʒu��ݒ肷��B
//=============================================================================
void CEffect2D::Init(VECTOR3 pos, VECTOR2 size, EFFECTTYPE etype)
{
	////	�e��ϐ������ݒ�
	/////////////////////////////////////////////////////////////
	SetPos(VECTOR3(pos.x, pos.y, pos.z));	// ���S�_���W
	SetRot(VECTOR3(0.0f, 0.0f, 0.0f));		// ��]�p�x
	m_Size		= size;						// �g��{��
	m_nAnimCntX = 0;						// ���݂̃A�j���[�V������X�̈ʒu	
	m_nAnimCntY = 0;						// ���݂̃A�j���[�V������Y�̈ʒu
	m_nAnimChangeFrame = 0;					// �A�j���[�V�����؂�ւ��܂ł̃t���[����
	m_nAnimChangeFrameCnt = 0;				// �A�j���[�V�����؂�ւ��܂ł̃t���[���J�E���^
	m_bEndflug = false;						// ���E�t���O

	////	�G�t�F�N�g�^�C�v�ʂ̏���������
	/////////////////////////////////////////////////////////////
	TypeInit(etype);
}

//=============================================================================
//	�֐���	:Uninit
//	����	:����
//	�߂�l	:����
//	����	:�I���������s���B
//=============================================================================
void CEffect2D::Uninit(bool isLast)
{}

//=============================================================================
//	�֐���	:Update
//	����	:����
//	�߂�l	:����
//	����	:�X�V�������s���B
//=============================================================================
void CEffect2D::Update(void)
{
	/* ���t���[�����o�� */
	if(m_nAnimChangeFrameCnt == m_nAnimChangeFrame)
	{
		////	�A�j���[�V�����؂�ւ��p�t���[���J�E���^�����Z�b�g
		/////////////////////////////////////////////////////////////////
		m_nAnimChangeFrameCnt = 0;
		
		////	X���̃A�j���[�V�����J�E���^�����Z
		/////////////////////////////////////////////////////////////////
		m_nAnimCntX++;
		
		////	X���̃A�j���[�V�����J�E���^���萔�𒴂����ꍇ�̏���
		/////////////////////////////////////////////////////////////////
		if(m_nAnimCntX == m_nAnimX)
		{
			// X���̃A�j���[�V�����J�E���^�����Z�b�g
			m_nAnimCntX = 0;
		
			// Y���̃A�j���[�V�����J�E���^�����Z
			m_nAnimCntY++;
		}

		////	Y���̃A�j���[�V�����J�E���^���萔�𒴂����ꍇ
		/////////////////////////////////////////////////////////////////
		if(m_nAnimCntY == m_nAnimY)
		{
			// �I���t���O�����Ă�B
			m_bEndflug = true;
		}
	}

	////	�A�j���[�V�����؂�ւ��p�t���[���J�E���^���Z
	/////////////////////////////////////////////////////////////////
	m_nAnimChangeFrameCnt++;

	////	�I���t���O�������Ă���ꍇ�̏���
	/////////////////////////////////////////////////////////////////
	if(m_bEndflug)
	{
		// �I������
		Release();
	}
}

//=============================================================================
//	�֐���	:Draw
//	����	:����
//	�߂�l	:����
//	����	:�`�揈�����s���B
//=============================================================================
void CEffect2D::Draw(void)
{
	////	���f���r���[�ϊ��s��̑���p
	/////////////////////////////////////////////////////////////
	GLdouble m[16];

	////	���f���r���[�}�g���N�X�̐ݒ�
	/////////////////////////////////////////////////////////////
	glMatrixMode(GL_MODELVIEW);

	////	�}�g���N�X�̑ޔ�
	/////////////////////////////////////////////////////////////
	glPushMatrix();


	////	���[���h�}�g���N�X�̐ݒ�
	/////////////////////////////////////////////////////////////
	glTranslatef(m_Pos.x, m_Pos.y, m_Pos.z);
	glScalef(1.0f, 1.0f, 1.0f);

	// ���݂̃��f���r���[�ϊ��s������o��
	glGetDoublev(GL_MODELVIEW_MATRIX, m);

	// ���� 3x3 �v�f��P�ʍs��ɂ���
	m[0] = m[5] = m[10] = 1.0;
	m[1] = m[2] = m[4] = m[6] = m[8] = m[9] = 0.0;

	// �����������s��������߂�
	glLoadMatrixd(m);

	////	�`�揈��
	/////////////////////////////////////////////////////////////

		////	�e��`��ݒ�
		/////////////////////////////////////////////////////////
		glBindTexture(GL_TEXTURE_2D, *m_Texture);			// �e�N�X�`���o�C���h
		glEnable(GL_TEXTURE_2D);							// �e�N�X�`���L����
		glEnable(GL_DEPTH_TEST);							// �[�x�o�b�t�@�ݒ�
		glDisable(GL_LIGHTING);								// ���C�e�B���O�I�t
		glEnable(GL_BLEND);									// �u�����h�L����
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	// ���u�����h�ݒ�
		glDepthMask(GL_FALSE);								// �[�x�o�b�t�@�ւ̏������݂��֎~����B(�����ǂ����̏d�Ȃ�̉���)

		////	�`��J�n
		/////////////////////////////////////////////////////////
		glBegin(GL_TRIANGLE_STRIP);
		{
			// ���_�F�ݒ�
			glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

			// �`��֐��Ăяo��
			DrawPolygon();
		}

		////	�`��I��
		/////////////////////////////////////////////////////////
		glEnd();


	////	�e��ݒ�����߂�
	/////////////////////////////////////////////////////////////
	glEnable(GL_LIGHTING);			// ���C�e�B���OON
	glDisable(GL_TEXTURE_2D);		// �e�N�X�`������
	glDisable(GL_DEPTH_TEST);		// �[�x�o�b�t�@�ݒ�I�t
	glDisable(GL_BLEND);			// ���u�����hOFF
	glDepthMask(GL_TRUE);			// �[�x�o�b�t�@�ւ̏������݂�����

	////	���f���r���[�}�g���b�N�X�̐ݒ�
	/////////////////////////////////////////////////////////////
	glMatrixMode(GL_MODELVIEW);
	
	////	�ۑ��}�g���b�N�X�̎��o��
	/////////////////////////////////////////////////////////////
	glPopMatrix();
}


//=============================================================================
//	�֐���	:DrawPolygon
//	����	:����
//	�߂�l	:����
//	����	:�|���S���̒��_�����Z�b�g����B
//=============================================================================
void CEffect2D::DrawPolygon(void)
{
	////	�`��p�̖@���E�e�N�X�`�����W�E���_���W�ݒ�
	/////////////////////////////////////////////////////////////

	// ����
	glNormal3f(0.0f, 1.0f, 0.0f);											// �@���x�N�g��	
	glTexCoord2d(float((1.0f / m_nAnimX) * m_nAnimCntX),					// �e�N�X�`�����WX(U)
				 float(1.0f - (1.0f / m_nAnimY * m_nAnimCntY)));			// �e�N�X�`�����WX(V)
	glVertex3f(-m_Size.x * 0.5f , m_Size.y * 0.5f , 0.0f);					// ���_���W

	// �E��
	glNormal3f(0.0f, 1.0f, 0.0f);											// �@���x�N�g��	
	glTexCoord2d(float((1.0f / m_nAnimX) * (m_nAnimCntX + 1)),				// �e�N�X�`�����WX(U)
				 float(1.0f - (1.0f / m_nAnimY * m_nAnimCntY)));			// �e�N�X�`�����WX(V)
	glVertex3f(m_Size.x * 0.5f , m_Size.y * 0.5f , 0.0f);					// ���_���W
																						
	// ����
	glNormal3f(0.0f, 1.0f, 0.0f);											// �@���x�N�g��	
	glTexCoord2d(float((1.0f / m_nAnimX) * m_nAnimCntX),					// �e�N�X�`�����WX(U)
				 float(1.0f - (1.0f / m_nAnimY * (m_nAnimCntY + 1))));		// �e�N�X�`�����WX(V)
	glVertex3f(-m_Size.x * 0.5f , -m_Size.y * 0.5f , 0.0f);					// ���_���W
																						
	// �E��
	glNormal3f(0.0f, 1.0f, 0.0f);											// �@���x�N�g��	
	glTexCoord2d(float((1.0f / m_nAnimX) * (m_nAnimCntX + 1)),				// �e�N�X�`�����WX(U)
				 float(1.0f - (1.0f / m_nAnimY * (m_nAnimCntY + 1))));		// �e�N�X�`�����WX(V)
	glVertex3f(m_Size.x * 0.5f , -m_Size.y * 0.5f , 0.0f);					// ���_���W
}																						

//=============================================================================
//	�֐���	:TypeInit
//	����	:EFFECTTYPE etype(�G�t�F�N�g�쐬���̃G�t�F�N�g�^�C�v)
//	�߂�l	:����
//	����	:�^�C�v�ʂŕ��򂷂鏉�����������s��
//=============================================================================
void CEffect2D::TypeInit(EFFECTTYPE etype)
{
	////	���[�J���ϐ�
	/////////////////////////////////////////////////////////////
	CRendererGL	*renderer = CManager::GetRendererGL();

	////	����������
	/////////////////////////////////////////////////////////////
	switch(etype)
	{
		// �^�C�v�Ȃ�
		case ETYPE_NONE :
			break;

		// �����G�t�F�N�g(��) 8x1 
		case ETYPE_EXPLODE00 :
			m_Texture = CTextureManager::GetTexture( TEXTURE_BULLETEXPLODE );	// �摜�̃A�h���X(�w�b�_�ɒ�`)
			m_nAnimX = EXPLODE00_X;												// X�̕�����(�w�b�_�ɒ�`)
			m_nAnimY = EXPLODE00_Y;												// Y�̕�����(�w�b�_�ɒ�`)
			m_nAnimChangeFrame = EXPLODE_ANIMATION_CHANGE_FRAME;				// �A�j���[�V�����؂�ւ��܂ł̃t���[����
			break;

		// �����G�t�F�N�g(��) 7x1 
		case ETYPE_EXPLODE01 :
			m_Texture = CTextureManager::GetTexture( TEXTURE_PLAYEREXPLODE );	// �摜�̃A�h���X(�w�b�_�ɒ�`)
			m_nAnimX = EXPLODE01_X;												// X�̕�����(�w�b�_�ɒ�`)
			m_nAnimY = EXPLODE01_Y;												// Y�̕�����(�w�b�_�ɒ�`)
			m_nAnimChangeFrame = EXPLODE_ANIMATION_CHANGE_FRAME;				// �A�j���[�V�����؂�ւ��܂ł̃t���[����
			break;
			
		// �y���摜(��)		10x1
		case ETYPE_SMOKE00 :
			m_Texture = CTextureManager::GetTexture( TEXTURE_SMOKE );		// �摜�̃A�h���X(�w�b�_�ɒ�`)
			m_nAnimX = SMOKE00_X;											// X�̕�����(�w�b�_�ɒ�`)
			m_nAnimY = SMOKE00_Y;											// Y�̕�����(�w�b�_�ɒ�`)
			m_nAnimChangeFrame = SMOKE_ANIMATION_CHANGE_FRAME;				// �A�j���[�V�����؂�ւ��܂ł̃t���[����
			break;
	}
}

//=============================================================================
//	�֐���	:Create
//	����	:VECTOR3 pos(�����ʒu)
//	�߂�l	:����
//	����	:�C���X�^���X�������s���Ƌ��ɁA�����ʒu��ݒ肷��B
//=============================================================================
CEffect2D *CEffect2D::Create(VECTOR3 pos, VECTOR2 size, EFFECTTYPE etype)
{
	CEffect2D *effect;

	effect = new CEffect2D;

	effect->Init(pos, size, etype);

	return effect;
}

