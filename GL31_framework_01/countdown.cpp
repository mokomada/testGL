//=============================================================================
//
//	�^�C�g��	�V�[���t�@�C��(2DGL)
//	�t�@�C����	score.cpp
//	�쐬��		AT13A284_07 �r�c�B��
//	�쐬��		2016/11/14
//
//=============================================================================
//=============================================================================
//	�C���N���[�h
//=============================================================================
#include "sceneGL.h"
#include "scene2DGL.h"
#include "countdown.h"
#include "manager.h"
#include "main.h"
#include "rendererGL.h"

//=============================================================================
//	�ÓI�����o�ϐ�
//=============================================================================
int		CCountDown::m_NumFigure;

//=============================================================================
//	�֐���	:CCountDown()
//	����	:����
//	�߂�l	:����
//	����	:�R���X�g���N�^�B
//=============================================================================
CCountDown::CCountDown(PRIORITY priority, OBJTYPE objtype) : CScene2DGL( priority , objtype )
{

}

//=============================================================================
//	�֐���	:~CCountDown()
//	����	:����
//	�߂�l	:����
//	����	:�f�X�g���N�^�B
//=============================================================================
CCountDown::~CCountDown()
{

}


//=============================================================================
//	�֐���	:Init
//	����	:VECTOR3 pos(�����ʒu)
//	�߂�l	:����
//	����	:�������������s���Ƌ��ɁA�����ʒu��ݒ肷��B
//=============================================================================
void CCountDown::Init(VECTOR3 pos, VECTOR2 size, int figure)
{
	// �����i�[
	m_NumFigure = figure;

	m_CountDown = false;

	// ���l������
	m_Value = 0;
	m_Frame = 0;

	m_BaseSize = size;

	// �i���o�[�C���X�^���X�z�񐶐�
	m_Number = new CNumber *[m_NumFigure];

	// ���W������
	SetPos(VECTOR3(pos.x, pos.y, pos.z));
	
	// ��]������
	SetRot(VECTOR3(0.0f, 0.0f, 0.0f));

	// ���W�ݒ�
	for(int i = 0 ; i < m_NumFigure; i++)
	{// �������ݒ�

		//float difference = (size.x * 0.25f) * (i - m_NumFigure / 2 + ((m_NumFigure % 2 == 0) ? 0 : 1));
		float difference = (size.x * 0.25f) * i;

		m_Number[i] = CNumber::Create(VECTOR3((pos.x + difference), pos.y, pos.z), VECTOR2((size.x / m_NumFigure), size.y));
	}
}

//=============================================================================
//	�֐���	:Uninit
//	����	:����
//	�߂�l	:����
//	����	:�I���������s���B
//=============================================================================
void CCountDown::Uninit(bool isLast)
{

}

//=============================================================================
//	�֐���	:Update
//	����	:����
//	�߂�l	:����
//	����	:�X�V�������s���B
//=============================================================================
void CCountDown::Update(void)
{
	if( m_Value <= 0 )
	{
		m_Start = true;
		SetValue(0);
	}
	else
	{
		// �T�C�Y�ύX
		for(int i = 0 ; i < m_NumFigure; i++)
		{
			m_Number[i]->AddSize( VECTOR2( COUNTDOWN_ADDSIZE , COUNTDOWN_ADDSIZE ) );
		}
		//�t���[���������B���Ă��Ȃ�������֐����甲����
		if( ( m_Frame = ( ( m_Frame + 1 ) % COUNTDOWN_TIMING ) ) )
		{
			SetValue(m_Value);
			return;
		}

		m_Value -= 1.0f;

		// �T�C�Y�ύX
		for(int i = 0 ; i < m_NumFigure; i++)
		{
			m_Number[i]->SetSize( m_BaseSize );
		}

		//�����ݒ�
		if( m_Value < 0 )m_Value = 0;

		SetValue(m_Value);
	}
}

//=============================================================================
//	�֐���	:Draw
//	����	:����
//	�߂�l	:����
//	����	:�`�揈�����s���B
//=============================================================================
void CCountDown::Draw(void)
{
	//�`��^�C�~���O�ΏۊO�Ȃ�
	if( m_Value > COUNTDOWN_FACE )return;

	// �i���o�[�`��
	for(int i = 0 ; i < m_NumFigure ; i++)
	{
		m_Number[i]->Draw();
	}
}

//=============================================================================
//	�֐���	:Create
//	����	:VECTOR3 pos(�����ʒu)
//	�߂�l	:����
//	����	:�C���X�^���X�������s���Ƌ��ɁA�����ʒu��ݒ肷��B
//=============================================================================
CCountDown *CCountDown::Create(VECTOR3 pos, VECTOR2 size, int figure)
{
	CCountDown *countdown;	// �C���X�^���X

	// �C���X�^���X����
	countdown = new CCountDown;

	// ����������
	countdown->Init(pos, size, figure);

	// �C���X�^���X�����^�[��
	return countdown;
}

//=============================================================================
//	�֐���	:SetValue
//	����	:����
//	�߂�l	:����
//	����	:���l���Z�b�g����B
//=============================================================================
void CCountDown::SetValue(float value)
{
	float valueCal = value;	// ���l
	float valueUpper = 0.0f;
	float valueLower = 0.0f;


	// �������Z�b�g
	for(int i = 0 ; i < m_NumFigure ; i++)
	{
		if(valueCal >= pow(10.0f, (m_NumFigure - i - 1)))
		{
			m_Number[i]->SetNumber((int)valueCal / (int)pow(10.0f, (m_NumFigure - i - 1)));
		}
		else
		{
			m_Number[i]->SetNumber(0);
		}

		// ������
		valueCal = (float)((int)valueCal % (int)pow(10.0f, (m_NumFigure - i - 1)));
	}
}