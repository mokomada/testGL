/*******************************************************************************
* �^�C�g�� �f�o�b�O���`��
* �t�@�C���� debugProc.cpp
* �쐬�� AT-12C-245 �H�ԗY��
* �쐬�� 2015/11/26
*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "debugProc.h"
#include "camera.h"
#include "renderer.h"
#include "manager.h"

/*******************************************************************************
* �\���̒�`
*******************************************************************************/


/*******************************************************************************
* �O���[�o���ϐ�
*******************************************************************************/

LPD3DXFONT g_pFont = NULL; //�t�H���g�ւ̃|�C���^
char g_aStrDebug[DEBUGPROC_MAX_CHAR_NUM]; // ������i�[�p
int count_strdebug; // g_aStrDebug�̔z��ԍ�

/*******************************************************************************
* �֐����FInitDebugProc
* �����F�Ȃ�
* �߂�l�F�Ȃ�
* �����F�f�o�b�O���̏�����
*******************************************************************************/

HRESULT InitDebugProc(void) {
	CRenderer *renderer;
	renderer = CManager::GetRenderer( );
	LPDIRECT3DDEVICE9 pDevice = renderer -> GetDevice( ); // �f�o�C�X�擾

	// �t�H���g�̏����ݒ�
	D3DXCreateFont(pDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &g_pFont);
	memset(g_aStrDebug, 0, sizeof g_aStrDebug);

	for(int i = 0; i < count_strdebug; i++) {
		g_aStrDebug[i] = '\0';
	}

	count_strdebug = 0;

	return S_OK;
}


/*******************************************************************************
* �֐����FUninitDebugProc
* �����F�Ȃ�
* �߂�l�F�Ȃ�
* �����F�f�o�b�O���̏I������
*******************************************************************************/

void UninitDebugProc(void) {
	if(g_pFont != NULL) {
		g_pFont -> Release( ); // �t�H���g�̊J��
		g_pFont = NULL;
	}
}


/*******************************************************************************
* �֐����FUpdateDebugProc
* �����F�Ȃ�
* �߂�l�F�Ȃ�
* �����F�f�o�b�O���̍X�V����
*******************************************************************************/

void UpdateDebugProc(void) {

}


/*******************************************************************************
* �֐����FDrawDebugProc
* �����F�Ȃ�
* �߂�l�F�Ȃ�
* �����F�f�o�b�O���̕`�揈��
*******************************************************************************/

void DrawDebugProc(void) {
#ifdef _DEBUG
	RECT rect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

	char ia[256] = "\n";

	strcat(g_aStrDebug, ia);
	_itoa_s(count_strdebug, ia, 10);
	strcat(g_aStrDebug, ia);

	g_pFont -> DrawText(NULL, &g_aStrDebug[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255) );
	count_strdebug = 0;
	memset(g_aStrDebug, 0, sizeof g_aStrDebug);
#endif
}


/*******************************************************************************
* �֐����FPrintDebugProc
* �����F�`�悷�镶����ƕϐ�
* �߂�l�F�Ȃ�
* �����F�f�o�b�O���̕`�揈��
*******************************************************************************/

void PrintDebugProc(char *fmt, ...) {
#ifdef _DEBUG
	// �ϐ��̐錾
	int d, count_f;
	double f;
	char ia[256], c;

	va_list dpList; // list��p��

	va_start(dpList, fmt); // list�̏�����

	while(*fmt) {
		// %�̏ꍇ�ϐ��ǂݍ���
		if(*fmt == '%') {
			*fmt++;
			switch(*fmt) {
			case 'd':
				d = va_arg(dpList, int);
				_itoa_s(d, ia, 10);
				strcat(g_aStrDebug, ia);
				while(d) {
					d /= 10;
					count_strdebug++;
				}
				break;
			case 'f':
				// ���������̏���
				f = va_arg(dpList, double); // va_arg��float���Ή��̂���double���g��
				// �����������o��
				d = (int)f;
				_itoa_s(d, ia, 10);
				// ���̒l�̎��͔��p�X�y�[�X�������ăv���X�}�C�i�X�ŕ\�����Y���Ȃ��悤�ɂ���
				if(d >= 0) {
					strcat(g_aStrDebug, " ");
				}
				// �����킹�B1����2���̏ꍇ�̓X�y�[�X��}�����ĕ\�����Y���Ȃ��悤�ɂ���
				for(count_f = 100; count_f > 1; count_f /= 10) {
					if(d / count_f == 0) {
						strcat(g_aStrDebug, " ");
					}
				}
				// 3���\������̂�+3
				count_strdebug += 3;
				strcat(g_aStrDebug, ia);

				// �����_�ȉ��̏���
				// �����_�{�����_�ȉ�3���\������̂�+4
				count_strdebug += 4;
				f -= (int)f;
				f *= 1000;
				d = abs( (int)f);
				_itoa_s(d, ia, 10);
				// �����_�\��
				strcat(g_aStrDebug, ".");
				// �����_�ȉ��\��
				strcat(g_aStrDebug, ia);
				// �����킹�B3�������l���Ȃ��ꍇ��0�Ŗ��߂�
				if(d < 100) {
					strcat(g_aStrDebug, "0");
				}
				if(d < 10) {
					strcat(g_aStrDebug, "0");
				}
/*				for(count_f = 0; count_f < 3; count_f++) {
					if(d % 10 == 0) {
						strcat(g_aStrDebug, "0");
					}
					d /= 10;
				}*/
				break;
			case 'c':
				c = (char)va_arg(dpList, int);
				strcat(g_aStrDebug, &c);
				break;
			default:
				break;
			}
		}
		else {
			// %�ȊO�̕�����͂��̂܂܊i�[
			g_aStrDebug[count_strdebug] = *fmt;
		}
		// ���̕�����
		*fmt++;
		count_strdebug++;
	}

	// �Ō��\0��}��
	g_aStrDebug[count_strdebug] = '\0';

	va_end(dpList);
#endif
}