/*******************************************************************************
* �t�@�C���� game.h
* �쐬�� AT-13A-284 �H�ԗY��
* �쐬�� 2016/07/19
*******************************************************************************/

/*** �C���N���[�h�K�[�h�J�n ***/
#ifndef _GAME_H_
#define _GAME_H_

#include "mode.h"

/*******************************************************************************
* �}�N����`
*******************************************************************************/


/*******************************************************************************
* �v���g�^�C�v�錾
*******************************************************************************/

class CScene; // �O���錾
class CCamera; // �O���錾
class CLight; // �O���錾
class CScore; // �O���錾
class CPlayer; // �O���錾
class CEnemy; // �O���錾



/*******************************************************************************
* �v���g�^�C�v�錾
*******************************************************************************/
class CGame : public CMode{
private:
	static CCamera *m_camera; // �J����
	static CLight *m_light; // ���C�g
	static CScore *m_score; // �X�R�A���
	static CPlayer *m_player; // �v���C���[���
	static CEnemy *m_enemy[ ]; // �G���
public:
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CCamera *GetCamera(void);
	static CPlayer *GetPlayer(void);
	static CEnemy *GetEnemy(void);
};

#endif
/*** �C���N���[�h�K�[�h�I�� ***/