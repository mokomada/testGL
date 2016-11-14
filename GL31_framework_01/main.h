#ifndef _MAIN_H_
#define _MAIN_H_
//=============================================================================
//
//	�^�C�g�� �w�b�_�t�@�C��(main.cpp)
//	�t�@�C���� main.h
//	�쐬�� AT13A284_07 �r�c�B��
//	�쐬�� 2016/04/14
//
//=============================================================================
#define _CRT_SECURE_NO_WARNINGS
//=============================================================================
//	�C���N���[�h
//=============================================================================
#include <stdio.h>
#include <windows.h>
#include <math.h>
#include "vector.h"
#include "matrix.h"
#include "input.h"
#include "manager.h"
#include "readfile.h"
//#include "singleton.h"

//=============================================================================
//	�����N
//=============================================================================
#pragma comment(lib, "winmm.lib")

//=============================================================================
//	�}�N����`
//=============================================================================
#define	CHANGE_SIZE			(5)			// 
#define	SCREEN_WIDTH		(1280.0f * 0.85f)		// �E�B���h�E�̉���
#define	SCREEN_HEIGHT		(760.0f * 0.85f)		// �E�B���h�E�̏c��
#define	SCREEN_WIDTH_HALF	(SCREEN_WIDTH * 0.5f)	// �E�B���h�E�̉���(����)
#define	SCREEN_HEIGHT_HALF	(SCREEN_HEIGHT * 0.5f)	// �E�B���h�E�̏c��(����)
#define	PI					(3.14159265f)			// �~����

typedef unsigned char uchar;	// unsigned char�Z�k
typedef unsigned int uint;		// unsigned int�Z�k



//=============================================================================
//	�\����
//=============================================================================
typedef struct{
	bool ModelBeing;	// ���f�����\������Ă��邩�ۂ�
	bool Wireframe;		// ���C���t���[�����[�h
	bool Culling;		// �J�����O���[�h
	bool Texture;		// �e�N�X�`���\�t�̗L��
	bool Lighting;		// ���C�e�B���O�̗L��
	bool Glid;			// �O���b�h�̕\��/��\��
	bool XAxis;			// �w��
	bool YAxis;			// �x��
	bool ZAxis;			// �y��
} FLUG;

//=============================================================================
//	�O���錾
//=============================================================================
class CManager;

//=============================================================================
//	�v���g�^�C�v
//=============================================================================
CManager		*GetManager(void);
FLUG			*GetFlug(void);
float			GetZoomPos(void);
float			GetSizePos(void);
char			*ReadBinaryFile(char *filename);
int				SearchWordByString(char *str, unsigned int offset, char *word);
int				SearchWordNumByString(char *str, unsigned int offset, char *word);
int				SearchWordNumByString(char *str, unsigned int offset, char *word, char *endword);
bool			SearchWordByFile(FILE *fp, char *word);

#endif