/******************************************************************************
*	�t�@�C���F
*	�쐬��  �F���i��
*	�쐬��  �F
******************************************************************************/
/******************************************************************************
*	�w�b�_�[�t�@�C���̑��d�C���N���[�h�h�~
******************************************************************************/

#pragma once

/******************************************************************************
*	�C���N���[�h�t�@�C��
******************************************************************************/
#include "sceneGL.h"
/******************************************************************************
*	�}�N����`
******************************************************************************/
#define LIFE_NUM ( 1 )
/******************************************************************************
*	�\���̒�`
******************************************************************************/
/******************************************************************************
*	�O���錾
******************************************************************************/

class CBalloon;
class CSceneGL;

/******************************************************************************
*	�N���X
******************************************************************************/
class CLife : public CSceneGL
{
public:
	CLife(PRIORITY priority = PRIORITY_NONE, OBJTYPE objType = OBJTYPE_NONE);
	~CLife();

	static CLife * Create( VECTOR3 pos , CSceneGL *parent );

	void Init( VECTOR3 pos , CSceneGL *parent );
	void Uninit( void );
	void Update( void );
	void Draw( void );

	void HitDamage( void );	//�_���[�W���󂯂���
	void SetBalloonColor( void );
	int GetLife( void ); // HP�c�ʂ̎擾

private:
	CBalloon *m_balloon;
	CSceneGL *m_parent;	//�e�̃A�h���X
	int m_life;
};