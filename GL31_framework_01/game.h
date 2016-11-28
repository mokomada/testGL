#ifndef _GAME_H_
#define _GAME_H_
//=============================================================================
//
//	�^�C�g��	�w�b�_�t�@�C��
//	�t�@�C����	game.h
//	�쐬��		AT13A284_07 �r�c�B��
//	�쐬��		2016/07/12
//
//=============================================================================
#include "mode.h"

//=============================================================================
//	�O���錾
//=============================================================================
class CMeshfield;
class CSceneModel;

//=============================================================================
//	�N���X��`
//=============================================================================
class CGame : public CMode
{
public:
	CGame(){}
	~CGame(){}

	void	Init(void);
	void	Uninit(void);
	void	Update(void);
	void	Draw(void);

	static CMeshfield	*GetMeshfield(void){ return m_Meshfield; }
	static CSceneModel	*GetPlayer1(void) { return m_Player1; }
	static CSceneModel	*GetPlayer2(void) { return m_Player2; }

private:
	static CMeshfield	*m_Meshfield;	// ���b�V���t�B�[���h�̃C���X�^���X
	static CSceneModel	*m_Player1;		// �v���C���[�̃C���X�^���X
	static CSceneModel	*m_Player2;		// �v���C���[�̃C���X�^���X
};

#endif