//=============================================================================
//
//	�^�C�g��	�^�C�g������
//	�t�@�C����	debugProcGL.cpp
//	�쐬��		AT13A284_07 �r�c�B��
//	�쐬��		2016/07/12
//
//=============================================================================
//=============================================================================
//	�C���N���[�h
//=============================================================================
#include "debugProcGL.h"
#include <gl/glut.h>
#include <vector>
#include <mbstring.h>

//=============================================================================
//	�ÓI�����o�ϐ�
//=============================================================================
HDC		CDebugProcGL::m_hDc;
HFONT	CDebugProcGL::m_hFont;
char	CDebugProcGL::m_aStrDebug[DEBUGSTR_MAX];

//=============================================================================
//	�֐���	:Init
//	����	:����
//	�߂�l	:����
//	����	:�������������s���B
//=============================================================================
void CDebugProcGL::Init(void)
{
	m_hFont = CreateFontW(
		FONT_SIZE,					//�t�H���g����
		0,							//������
		0,							//�e�L�X�g�̊p�x
		0,							//�x�[�X���C���Ƃ����Ƃ̊p�x
		FW_REGULAR,					//�t�H���g�̑���
		FALSE,						//�C�^���b�N��
		FALSE,						//�A���_�[���C��
		FALSE,						//�ł�������
		SHIFTJIS_CHARSET,			//�����Z�b�g
		OUT_DEFAULT_PRECIS,			//�o�͐��x
		CLIP_DEFAULT_PRECIS,		//�N���b�s���O���x
		ANTIALIASED_QUALITY,		//�o�͕i��
		FIXED_PITCH | FF_MODERN,	//�s�b�`�ƃt�@�~���[
		L"�l�r����");				//���̖�

	m_hDc = wglGetCurrentDC();
	SelectObject(m_hDc, m_hFont);
}

//=============================================================================
//	�֐���	:Uninit
//	����	:����
//	�߂�l	:����
//	����	:�I���������s���B
//=============================================================================
void CDebugProcGL::Uninit(void)
{
	// �t�H���g�j���B 
	DeleteObject(m_hFont);
}

//=============================================================================
//	�֐���	:Update
//	����	:����
//	�߂�l	:����
//	����	:�X�V�������s���B
//=============================================================================
void CDebugProcGL::Update(void)
{

}

//=============================================================================
//	�֐���	:Draw
//	����	:����
//	�߂�l	:����
//	����	:�`�揈�����s���B
//=============================================================================
void CDebugProcGL::Draw(void)
{
	int Length = 0;
	int list = 0;
	std::vector<int> parag;					// ���s���
	std::vector<int>::iterator itrParag;	// �C�e���[�^
	std::vector<int> bytelen;				// �o�C�g�����
	std::vector<int>::iterator itrBytelen;	// �C�e���[�^
	VECTOR2 pos = VECTOR2(DEBUGPROC_POSX, DEBUGPROC_POSY);	// �����\���ʒu

	// ���f���r���[�}�g���b�N�X�̐ݒ�(���e�ϊ�)
	glMatrixMode(GL_PROJECTION);
	// �}�g���b�N�X�̕ۑ�
	glPushMatrix();
	// �ϊ��s��̏�����
	glLoadIdentity();

	// ���s�ˉeor���ˉe
	glOrtho(0, (GLdouble)SCREEN_WIDTH, (GLdouble)SCREEN_HEIGHT, 0, -100.0, 100.0);
	// ���[���h���W�n�̕\���̈���C�r���[�|�[�g�̑傫���ɔ�Ⴓ����

	// ���f���r���[�}�g���b�N�X�̐ݒ�
	glMatrixMode(GL_MODELVIEW);
	// �}�g���b�N�X�̕ۑ�
	glPushMatrix();
	// �ϊ��s��̏�����
	glLoadIdentity();

	Length = strlen(m_aStrDebug);
	list = glGenLists(Length);

	

	// �r�b�g�}�b�v�C���[�W�g�p�ӏ��w��
	for(int i = 0; i < Length; i++)
	{
		// ���s����
		if(m_aStrDebug[i] == (wchar_t)10)
		{
			// ���s�ʒu�̋L�^
			parag.push_back(i);
		}

		bytelen.push_back((((int)m_aStrDebug[i] < 1000) ? 1 : 2));

		wglUseFontBitmapsW(m_hDc, m_aStrDebug[i], 1, list + (DWORD)i);
	}

	glPushAttrib(GL_ENABLE_BIT);
	glDisable(GL_LIGHTING);

	// �����F�ݒ�
	glColor3f(0.0f, 0.0f, 0.0f);

	itrBytelen = bytelen.begin();

	//�f�B�X�v���C���X�g�ŕ`��
	for(int i = 0 ; i < Length ; i++)
	{
		// ���s�̒ǉ�
		for(itrParag = parag.begin() ; itrParag != parag.end() ; itrParag++)
		{
			if(*itrParag == i)
			{
				pos.y += FONT_SIZE;
				pos.x = DEBUGPROC_POSX;
				pos.x -= (float)FONT_SIZE * 0.5f;
			}
		}

		// ���W�w��
		glRasterPos2i((int)pos.x, (int)pos.y);

		// �f�B�X�v���C���X�g���s
		glCallList(list + i);

		// �����Ԋu����
		pos.x += (*itrBytelen == 1) ? (FONT_SIZE * 0.5f) : FONT_SIZE;

		// �C�e���[�^��i�߂�
		itrBytelen++;
	}

	glEnable(GL_LIGHTING);

	//�f�B�X�v���C���X�g�j��
	glDeleteLists(list, Length);

	list = 0;
	Length = 0;

	// ���f���r���[�}�g���b�N�X�̐ݒ�(���e�ϊ�)
	glMatrixMode(GL_PROJECTION);
	// �ۑ��}�g���b�N�X�̎��o��
	glPopMatrix();

	// ���f���r���[�}�g���b�N�X�̐ݒ�
	glMatrixMode(GL_MODELVIEW);
	// �ۑ��}�g���b�N�X�̎��o��
	glPopMatrix();

	glPopAttrib();

	// ������������
	memset(m_aStrDebug, 0, sizeof(m_aStrDebug));
}

//=============================================================================
//	�֐���	:DrawStringW
//	����	:����
//	�߂�l	:����
//	����	:�������`�悷��B
//=============================================================================
void CDebugProcGL::DebugProc(char* format, ...)
{
	va_list list;
	char str[256];

	va_start(list, format);

	vsprintf_s(str, format, list);

	strcat_s(m_aStrDebug, str);

	va_end(list);
}