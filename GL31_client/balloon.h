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
#include "sceneBillboardGL.h"
/******************************************************************************
*	�}�N����`
******************************************************************************/
/******************************************************************************
*	�\���̒�`
******************************************************************************/
/******************************************************************************
*	�O���錾
******************************************************************************/
/******************************************************************************
*	�N���X
******************************************************************************/
class CBalloon : public CSceneBillboardGL
{
public:
	CBalloon(bool ifListAdd = true, PRIORITY priority = PRIORITY_BALLOON, OBJTYPE objType = OBJTYPE_NONE);
	~CBalloon();

	static CBalloon * Create( VECTOR3 pos , float r , float g , float b , float a , CSceneGL * parent );

	void Init( VECTOR3 pos , float r , float g , float b , float a , CSceneGL * parent );
	void Uninit( void );
	void Update( void );
	void Draw( void );
	void DrawPolygon( void );

	VECTOR3 GetPos( void ) { return m_Pos; }
	void SetPos( VECTOR3 pos ) { m_Pos = pos; }
	void SetRot( VECTOR3 rot ) { m_Rot = rot; }
	void SetUV( float u ) { m_u += u; }
	void SetDeleteFlag() { m_deleteFlag = true; }
	void SetColor( float r , float g , float b , float a );
private:
	VECTOR3 m_Pos;		// �ʒu
	VECTOR3 m_Rot;		// ��]�p
	VECTOR2 m_Size;		// �|���S���̃T�C�Y
	float m_r;
	float m_g;
	float m_b;
	float m_Alpha;			//�A���t�@�l
	unsigned int *m_Texture;	// �e�N�X�`��
	float m_u;
	bool m_deleteFlag;
	CSceneGL * m_parent;
};
