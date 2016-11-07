/*******************************************************************************
* �^�C�g�� �t�F�[�h����
* �t�@�C���� Fade.cpp
* �쐬�� AT-12C-245 �H�ԗY��
* �쐬�� 2015/06/03
*******************************************************************************/

/*******************************************************************************
* �C���N���[�h�t�@�C��
*******************************************************************************/

#include "main.h"
#include "manager.h"
#include "scene.h"
#include "renderer.h"
#include "mode.h"
#include "fade.h"
#include "title.h"
#include "game.h"
#include "result.h"


/*******************************************************************************
* �O���[�o���ϐ�
*******************************************************************************/


FADE CFade::m_fade = FADE_NONE; // �t�F�[�h�̏��
CMode *CFade::m_modeNext = NULL; // ���̃��[�h

/*******************************************************************************
* �֐����FInitFade
* �����F�Ȃ�
* �߂�l�F�Ȃ�
* �����F�t�F�[�h�ݒ�̏�����
*******************************************************************************/

HRESULT CFade::Init(void) {
	/* �ϐ��錾 */
	int i; // for�����[�v�p
	VERTEX_2D *pVtx;

	// �����o�ϐ�������
	m_pTextureFade = NULL;
	m_pVtxBuffFade = NULL;

	/* �ϐ��̎擾 */
	CRenderer *renderer;
	renderer = CManager::GetRenderer( );
	LPDIRECT3DDEVICE9 device = renderer -> GetDevice( );

	/* �t�F�[�h�e�N�X�`���ݒ� */
	D3DXCreateTextureFromFile(device, NULL, &m_pTextureFade);

	/* ���_�o�b�t�@�̐��� */
	if(FAILED(device -> CreateVertexBuffer(sizeof(VERTEX_2D) * FADE_VERTEX_NUM, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuffFade, NULL) ) ) {
		return E_FAIL;
	}

	/* ���_���ւ̃|�C���^���擾 */
	m_pVtxBuffFade -> Lock(0, 0, (void**)&pVtx, 0);

	/* ���W�ݒ� */
	pVtx[0].pos = D3DXVECTOR3(0, 0, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);


	for(i = 0; i < FADE_VERTEX_NUM; i++) {
		pVtx[i].rhw = 1.0f;

		pVtx[i].col = D3DCOLOR_RGBA(0, 0, 0, 255);
	}

	/* �e�N�X�`��UV���W�ݒ� */
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	m_pVtxBuffFade -> Unlock( );

	m_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	m_fade = FADE_IN;
	m_modeNext = new CTitle;

	return S_OK;
}


/*******************************************************************************
* �֐����FUninitFade
* �����F�Ȃ�
* �߂�l�F�Ȃ�
* �����F�t�F�[�h�ݒ�̏I������
*******************************************************************************/

void CFade::Uninit(void) {
	if(m_pTextureFade != NULL) {
		m_pTextureFade -> Release( ); // �e�N�X�`���̊J��
		m_pTextureFade = NULL;
	}

	if(m_pVtxBuffFade != NULL) {
		m_pVtxBuffFade -> Release( );
		m_pVtxBuffFade = NULL;
	}
}


/*******************************************************************************
* �֐����FUpdataFade
* �����F�Ȃ�
* �߂�l�F�Ȃ�
* �����F�t�F�[�h�̏��X�V
*******************************************************************************/

void CFade::Update(void) {
	/* �ϐ��錾 */
	int i; // for�����[�v�p
	VERTEX_2D *pVtx;

	if(m_fade == FADE_IN) {
		m_colorFade.a -= FADE_IN_SPEED;
		if(m_colorFade.a <= 0.0) {
			m_colorFade.a = 0.0f;
			m_fade = FADE_NONE;
		}
	}
	else if(m_fade == FADE_OUT) {
		m_colorFade.a += FADE_OUT_SPEED;
		if(m_colorFade.a >= 1.0) {
			m_colorFade.a = 1.0f;
			CManager::SetMode(m_modeNext);
			m_fade = FADE_IN;
		}
	}

	/* ���_���ւ̃|�C���^���擾 */
	m_pVtxBuffFade -> Lock(0, 0, (void**)&pVtx, 0);

	for(i = 0; i < FADE_VERTEX_NUM; i++) {
		pVtx[i].col = m_colorFade;
	}

	m_pVtxBuffFade -> Unlock( );
}


/*******************************************************************************
* �֐����FDrawFade
* �����F�Ȃ�
* �߂�l�F�Ȃ�
* �����F�t�F�[�h�̕`�揈��
*******************************************************************************/

void CFade::Draw(void) {
	CRenderer *renderer;
	renderer = CManager::GetRenderer( );
	LPDIRECT3DDEVICE9 device = renderer -> GetDevice( );

	// ���_�o�b�t�@���f�[�^�X�g���[���Ƀo�C���h
	device -> SetStreamSource(0, m_pVtxBuffFade, 0, sizeof(VERTEX_2D) );

	// ���_�t�H�[�}�b�g�̐ݒ�
	device -> SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	device -> SetTexture(0, m_pTextureFade);

	// 2D�|���S���̕`��
	device -> DrawPrimitive(
		D3DPT_TRIANGLESTRIP,
		0,
		FADE_TRIANGLE_NUM);
}


/*******************************************************************************
* �֐����FSetFade
* �����Ffade : �ǂ̃t�F�[�h���[�h�ɐ؂�ւ��邩�i�����t�F�[�h�A�E�g�ŌŒ�j
		modeNext : �t�F�[�h�A�E�g���I�������A�ǂ̃��[�h�ɐ؂�ւ���̂�
* �߂�l�F�Ȃ�
* �����F�t�F�[�h�i�A�E�g�j�̊J�n����
*******************************************************************************/

void CFade::SetFade(FADE fade, CMode *modeNext) {
	if(m_fade == FADE_NONE) {
		m_fade = fade;
		m_modeNext = modeNext;
	}
}


/*******************************************************************************
* �֐����FGetFade
* �����F�Ȃ�
* �߂�l�F���݂̃t�F�[�h�̏��
* �����F�t�F�[�h��Ԃ̎擾
*******************************************************************************/

FADE CFade::GetFade(void) {
	return m_fade;
}