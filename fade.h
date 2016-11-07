/*******************************************************************************
* �t�@�C���� fade.h
* �쐬�� AT-13A-284 �H�ԗY��
* �쐬�� 2016/07/19
*******************************************************************************/

/*** �C���N���[�h�K�[�h�J�n ***/
#ifndef _FADE_H_
#define _FADE_H_

/*******************************************************************************
* �}�N����`
*******************************************************************************/

#define FADE_VERTEX_NUM (4) // �`�悷�钸�_�̌�
#define FADE_TRIANGLE_NUM (2) // �`�悷��O�p�`�̌�

#define FADE_IN_SPEED (0.05f) // �t�F�[�h�C�����x
#define FADE_OUT_SPEED (0.01f) // �t�F�[�h�A�E�g���x


/*******************************************************************************
* �\���̂̐錾
*******************************************************************************/

typedef enum{
	FADE_NONE = 0,	// �������Ă��Ȃ�
	FADE_IN,		// �t�F�[�h�C��
	FADE_OUT,		// �t�F�[�h�A�E�g
	FADE_MAX
} FADE;

/*******************************************************************************
* �v���g�^�C�v�錾
*******************************************************************************/

class CMode;

class CFade{
private:
	LPDIRECT3DTEXTURE9 m_pTextureFade; // �t�F�[�h�p�e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffFade; //���_�o�b�t�@�ւ̃|�C���^
	D3DXCOLOR m_colorFade; // �t�F�[�h�F
	static FADE m_fade; // �t�F�[�h�̏��
	static CMode *m_modeNext; // ���̃��[�h

public:
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static void SetFade(FADE fade, CMode *modeNext);
	FADE GetFade(void);
};

#endif
/*** �C���N���[�h�K�[�h�I�� ***/