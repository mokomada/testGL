/*******************************************************************************
* �t�@�C���� billboard.h
* �쐬�� AT-13A-284 �H�ԗY��
* �쐬�� 2016/06/08
*******************************************************************************/

/*** �C���N���[�h�K�[�h�J�n ***/
#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

/*******************************************************************************
* �}�N����`
*******************************************************************************/

#define BILLBOARD_VERTEX_NUM (4) // �`�悷�钸�_�̌�
#define BILLBOARD_TRIANGLE_NUM (2) // �`�悷��O�p�`�̌�

#define BILLBOARD_TEXTURE_NAME "data/TEXTURE/tree001.png" // �e�N�X�`���[�Ɏg���摜�w��

#define BILLBOARD_WIDTH (41) // �r���{�[�h�̕�
#define BILLBOARD_HEIGHT (41) // �r���{�[�h�̍���

#define BILLBOARD_MOVE_SPEED (2) // �r���{�[�h�̈ړ����x



/*******************************************************************************
* �r���{�[�h�N���X
*******************************************************************************/

class CBillboard : public CScene{
private:
	typedef struct {
		D3DXVECTOR3 pos; // �ʒu���
		D3DXVECTOR3 rot; // ��]���
		D3DXVECTOR3 scl; // �X�P�[���l�@��{�I�ɑS��1.0f�ŌŒ�
		int shadow_num; // �e�̔ԍ�
	} BILLBOARD;

	LPDIRECT3DTEXTURE9 m_pTextureBillboard; // �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffBillboard; //���_�o�b�t�@�ւ̃|�C���^

	BILLBOARD m_billboard; // �r���{�[�h���

	D3DXMATRIX m_mtxWorldBillboard; // ���[���h�}�g���b�N�X

public:
	CBillboard( );
	~CBillboard( );

	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CBillboard *Create(void);
};

#endif
/*** �C���N���[�h�K�[�h�I�� ***/