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
//	�O���錾
//=============================================================================
class CManager;

//=============================================================================
//	�v���g�^�C�v
//=============================================================================
float GetFPS(void);

// �C���X�^���X�폜�֐�
template <class INSTANCE>
void SafetyRelease(INSTANCE instance)
{
	if(instance != NULL)
	{
		instance->Release();
		instance = NULL;
	}
}

// �C���X�^���X�폜�֐�(����N���X��)
template <class INSTANCE>
void SafetyUninit(INSTANCE instance)
{
	if(instance != NULL)
	{
		instance->Uninit();
		delete instance;
		instance = NULL;
	}
}

// �f�[�^�����֐�
template <class SWAPDATA>
void SwapData(SWAPDATA &data1, SWAPDATA &data2)
{
	SWAPDATA dataBuff;
	dataBuff = data1;
	data1 = data2;
	data2 = dataBuff;
}

// �f�[�^�j��֐�
template <class POWDATA>
POWDATA PowData(POWDATA data)
{
	return data * data;
}

#endif