/*******************************************************************************
* �^�C�g�� �r���{�[�h�`�揈��
* �t�@�C���� billboard.cpp
* �쐬�� AT-12C-245 �H�ԗY��
* �쐬�� 2015/11/17
*******************************************************************************/

#include "main.h"
#include "manager.h"
#include "scene.h"
#include "billboard.h"
#include "renderer.h"
#include "shadow.h"
#include "input.h"
#include "camera.h"
#include "meshfield.h"
#include "game.h"

/*******************************************************************************
* �\���̒�`
*******************************************************************************/



/*******************************************************************************
* �O���[�o���ϐ�
*******************************************************************************/


/*******************************************************************************
* �֐����FCManager
* �����F�Ȃ�
* �߂�l�F�Ȃ�
* �����F�N���X����������
*******************************************************************************/

CBillboard::CBillboard( ) {

}


/*******************************************************************************
* �֐����F~CManager
* �����F�Ȃ�
* �߂�l�F�Ȃ�
* �����F�N���X�j��������
*******************************************************************************/

CBillboard::~CBillboard( ) {

}

/*******************************************************************************
* �֐����FInit
* �����F�Ȃ�
* �߂�l�F�Ȃ�
* �����F�r���{�[�h�ݒ�̏�����
*******************************************************************************/

void CBillboard::Init(void) {
	// �ϐ��錾
	int i; // for���[�v�p
	VERTEX_3D *pVtx;

	// �ϐ��̎擾
	CRenderer *renderer; // �f�o�C�X�擾�p�ϐ�
	renderer= CManager::GetRenderer( ); // �����_���̃A�h���X�擾
	LPDIRECT3DDEVICE9 pDevice = renderer -> GetDevice( );

	// �����o�ϐ��̏�����
	m_pTextureBillboard = NULL;
	m_pVtxBuffBillboard = NULL;

	// �p�x�����ݒ�
	m_billboard.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_billboard.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_billboard.scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	// �e�N�X�`���ݒ�
	D3DXCreateTextureFromFile(pDevice, BILLBOARD_TEXTURE_NAME, &m_pTextureBillboard);

	// ���_�o�b�t�@�̐���
	pDevice -> CreateVertexBuffer(sizeof(VERTEX_3D) * BILLBOARD_VERTEX_NUM, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &m_pVtxBuffBillboard, NULL);

	// ���_���ւ̃|�C���^���擾
	m_pVtxBuffBillboard -> Lock(0, 0, (void**)&pVtx, 0);

	// ���W�ݒ�
	pVtx[0].pos = D3DXVECTOR3(-BILLBOARD_WIDTH * 0.5f, BILLBOARD_HEIGHT, 0);
	pVtx[1].pos = D3DXVECTOR3(BILLBOARD_WIDTH * 0.5f, BILLBOARD_HEIGHT, 0);
	pVtx[2].pos = D3DXVECTOR3(-BILLBOARD_WIDTH * 0.5f, 0, 0);
	pVtx[3].pos = D3DXVECTOR3(BILLBOARD_WIDTH * 0.5f, 0, 0);

	for(i = 0; i < BILLBOARD_VERTEX_NUM; i++) {
		pVtx[i].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	}

	// �@���ݒ�
	pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);


	// �e�N�X�`��UV���W�ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	m_pVtxBuffBillboard -> Unlock( );

	// �e�̐ݒ�
	m_billboard.shadow_num = SetShadow(&m_billboard.pos, BILLBOARD_WIDTH, BILLBOARD_HEIGHT);
}


/*******************************************************************************
* �֐����FUninit
* �����F�Ȃ�
* �߂�l�F�Ȃ�
* �����F�r���{�[�h�̏I������
*******************************************************************************/

void CBillboard::Uninit(void) {
	if(m_pTextureBillboard != NULL) {
		m_pTextureBillboard -> Release( ); // �e�N�X�`���̊J��
		m_pTextureBillboard = NULL;
	}

	if(m_pVtxBuffBillboard != NULL) {
		m_pVtxBuffBillboard -> Release( );
		m_pVtxBuffBillboard = NULL;
	}

	// �e�̊J��
	DeleteShadow(m_billboard.shadow_num);
}


/*******************************************************************************
* �֐����FUpdata
* �����F�Ȃ�
* �߂�l�F�Ȃ�
* �����F�r���{�[�h�̏��X�V
*******************************************************************************/

void CBillboard::Update(void) {
	// �ϐ��̐錾
	float field_height;

	// �J�������擾
	CCamera *get_camera = CGame::GetCamera( );
	CAMERA camera = get_camera -> GetCameraData( );

	// ���͏��擾
	CInput *input;
	input = CManager::GetInput( );

	if(input -> GetKeyboardPress(DIK_L) ) {
		if(input -> GetKeyboardPress(DIK_P) ) { // ����ړ�
			m_billboard.pos.x += sinf(D3DX_PI * (camera.rot.y - 0.75f) ) * BILLBOARD_MOVE_SPEED;
			m_billboard.pos.z -= cosf(D3DX_PI * (camera.rot.y - 0.75f) ) * BILLBOARD_MOVE_SPEED;
		}
		else if(input -> GetKeyboardPress(DIK_SEMICOLON) ) { // �����ړ�
			m_billboard.pos.x += sinf(D3DX_PI * (camera.rot.y - 0.25f) ) * BILLBOARD_MOVE_SPEED;
			m_billboard.pos.z -= cosf(D3DX_PI * (camera.rot.y - 0.25f) ) * BILLBOARD_MOVE_SPEED;
		}
		else { // ���ړ�
			m_billboard.pos.x += sinf(D3DX_PI * (camera.rot.y - 0.5f) ) * BILLBOARD_MOVE_SPEED;
			m_billboard.pos.z -= cosf(D3DX_PI * (camera.rot.y - 0.5f) ) * BILLBOARD_MOVE_SPEED;
		}
	}
	else if(input -> GetKeyboardPress(DIK_COLON) ) {
		if(input -> GetKeyboardPress(DIK_P) ) { // �E��ړ�
			m_billboard.pos.x += sinf(D3DX_PI * (camera.rot.y + 0.75f) ) * BILLBOARD_MOVE_SPEED;
			m_billboard.pos.z -= cosf(D3DX_PI * (camera.rot.y + 0.75f) ) * BILLBOARD_MOVE_SPEED;
		}
		else if(input -> GetKeyboardPress(DIK_SEMICOLON) ) { // �E���ړ�
			m_billboard.pos.x += sinf(D3DX_PI * (camera.rot.y + 0.25f) ) * BILLBOARD_MOVE_SPEED;
			m_billboard.pos.z -= cosf(D3DX_PI * (camera.rot.y + 0.25f) ) * BILLBOARD_MOVE_SPEED;
		}
		else { // �E�ړ�
			m_billboard.pos.x += sinf(D3DX_PI * (camera.rot.y + 0.5f) ) * BILLBOARD_MOVE_SPEED;
			m_billboard.pos.z -= cosf(D3DX_PI * (camera.rot.y + 0.5f) ) * BILLBOARD_MOVE_SPEED;
		}
	}
	else if(input -> GetKeyboardPress(DIK_P) ) {
		m_billboard.pos.x += sinf(D3DX_PI * (camera.rot.y + 1.0f) ) * BILLBOARD_MOVE_SPEED;
		m_billboard.pos.z -= cosf(D3DX_PI * (camera.rot.y + 1.0f) ) * BILLBOARD_MOVE_SPEED;
	}
	else if(input -> GetKeyboardPress(DIK_SEMICOLON) ) {
		m_billboard.pos.x += sinf(D3DX_PI * (camera.rot.y) ) * BILLBOARD_MOVE_SPEED;
		m_billboard.pos.z -= cosf(D3DX_PI * (camera.rot.y) ) * BILLBOARD_MOVE_SPEED;
	}

	// �㏸���~
	if(input -> GetKeyboardPress(DIK_O) ) {
		m_billboard.pos.y += BILLBOARD_MOVE_SPEED;
	}
	if(input -> GetKeyboardPress(DIK_AT) ) {
		m_billboard.pos.y -= BILLBOARD_MOVE_SPEED;
	}

	// �t�B�[���h�����擾
	field_height = CMeshfield::GetFieldHeight(m_billboard.pos);

	// ��������
	m_billboard.pos.y = field_height;
}


/*******************************************************************************
* �֐����FDraw
* �����F�Ȃ�
* �߂�l�F�Ȃ�
* �����F�r���{�[�h�̕`�揈��
*******************************************************************************/

void CBillboard::Draw(void) {
/*	CRenderer *renderer; // �f�o�C�X�擾�p�ϐ�
	renderer= CManager::GetRenderer( ); // �����_���̃A�h���X�擾
	LPDIRECT3DDEVICE9 pDevice = renderer -> GetDevice( );
	D3DXMATRIX mtxScl, mtxRot, mtxTrans; // �v�Z�p
	D3DXMATRIX mtxView;

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorldBillboard);

	// �r���[�}�g���b�N�X���擾
	pDevice -> GetTransform(D3DTS_VIEW, &mtxView);

	// �t�s��̌v�Z
	D3DXMatrixInverse(&m_mtxWorldBillboard, NULL, &mtxView);

	// �ړ����̍폜
	m_mtxWorldBillboard._41 = 0.0f;
	m_mtxWorldBillboard._42 = 0.0f;
	m_mtxWorldBillboard._43 = 0.0f;

	// ���[���h�}�g���b�N�X�̍쐬
	// �X�P�[���𔽉f
	D3DXMatrixScaling(&mtxScl, m_billboard.scl.x, m_billboard.scl.y, m_billboard.scl.z);
	D3DXMatrixMultiply(&m_mtxWorldBillboard, &m_mtxWorldBillboard, &mtxScl);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_billboard.rot.y, m_billboard.rot.x, m_billboard.rot.z); // ������ y, x, z �̏��Ԃɒ��ӁI�I�I ������
	D3DXMatrixMultiply(&m_mtxWorldBillboard, &m_mtxWorldBillboard, &mtxRot);

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_billboard.pos.x, m_billboard.pos.y, m_billboard.pos.z);
	D3DXMatrixMultiply(&m_mtxWorldBillboard, &m_mtxWorldBillboard, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice -> SetTransform(D3DTS_WORLD, &m_mtxWorldBillboard);

	// ���_�o�b�t�@���f�[�^�X�g���[���Ƀo�C���h
	pDevice -> SetStreamSource(0, m_pVtxBuffBillboard, 0, sizeof(VERTEX_3D) );

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice -> SetFVF(FVF_VERTEX_3D);

	// �e�N�X�`���̐ݒ�
	pDevice -> SetTexture(0, m_pTextureBillboard);

	// ���C�g�ݒ�I�t
	pDevice -> SetRenderState(D3DRS_LIGHTING, FALSE);

	// �A���t�@�e�X�g�ݒ�
	pDevice -> SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice -> SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice -> SetRenderState(D3DRS_ALPHAREF, 0);

	// �|���S���̕`��
	pDevice -> DrawPrimitive(
		D3DPT_TRIANGLESTRIP,
		0,
		BILLBOARD_TRIANGLE_NUM);

	// ���C�g�ݒ�I��
	pDevice -> SetRenderState(D3DRS_LIGHTING, TRUE);

	// �A���t�@�e�X�g�ݒ�����ɖ߂�
	pDevice -> SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice -> SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice -> SetRenderState(D3DRS_ALPHAREF, 0);*/
}

/*******************************************************************************
* �֐����FCreate
* �����Fbillboard : �A�h���X
* �߂�l�F�Ȃ�
* �����F�I�u�W�F�N�g�̐���
*******************************************************************************/

CBillboard *CBillboard::Create(void) {
	CBillboard *billboard;
	billboard = new CBillboard;
	billboard -> Init( );
	return billboard;
}