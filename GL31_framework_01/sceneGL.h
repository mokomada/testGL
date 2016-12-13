#ifndef _SCENEGL_H_
#define _SCENEGL_H_
//=============================================================================
//
//	�^�C�g��	�w�b�_�t�@�C��(scene.cpp)
//	�t�@�C����	scene.h
//	�쐬��		AT13A284_07 �r�c�B��
//	�쐬��		2016/04/19
//
//=============================================================================
#include "main.h"

//=============================================================================
//	�\���́E�񋓑�
//=============================================================================
typedef enum
{
	PRIORITY_NONE = 0,
	PRIORITY_PLAYER,
	PRIORITY_ENEMY,
	PRIORITY_BULLET,
	PRIORITY_MAX,
}PRIORITY; 

typedef enum {
	OBJTYPE_NONE = 0,
	OBJTYPE_PLAYER,
	OBJTYPE_ENEMY,
	OBJTYPE_BULLET,
	OBJTYPE_MAX
} OBJTYPE;

//	�����蔻��Ŏg���{�b�N�X�̏��
typedef struct
{
	float width;
	float height;
	float depth;
} BOX_DATA;


//=============================================================================
//	�}�N����`
//=============================================================================

//=============================================================================
//	�N���X��`
//=============================================================================
class CSceneGL
{
public:
	CSceneGL(PRIORITY Priority = PRIORITY_NONE, OBJTYPE objType = OBJTYPE_NONE);
	~CSceneGL();

	virtual void	Init(void);
	virtual void	Uninit(bool isLast = false)	= 0;
	virtual void	Update(void)				= 0;
	virtual void	Draw(void)					= 0;

	static void	UpdateAll(void);
	static void	DrawAll(void);
	static void	DeleteAll(bool isLast = false);
	void		Release(void);
	
	static void	glMatrixIdentity(MATRIX *matrix){	matrix->_11 = 1; matrix->_12 = 0; matrix->_13 = 0; matrix->_14 = 0;
													matrix->_21 = 0; matrix->_22 = 1; matrix->_23 = 0; matrix->_24 = 0;
													matrix->_31 = 0; matrix->_32 = 0; matrix->_33 = 1; matrix->_34 = 0;
													matrix->_41 = 0; matrix->_42 = 0; matrix->_43 = 0; matrix->_44 = 1;}
	
	void	SetPos(VECTOR3 pos){ m_Pos = pos; }
	void	SetRot(VECTOR3 rot){ m_Rot = rot; }
	void	SetRot(BOX_DATA box) { m_Box = box; }

	VECTOR3	GetPos(void) { return m_Pos; }
	VECTOR3	GetRot(void) { return m_Rot; }
	BOX_DATA GetBox(void) { return m_Box; }

	static CSceneGL *GetList(PRIORITY Priority = PRIORITY_NONE) { return m_pTop[Priority]; }
	CSceneGL *GetNext(void) { return m_pNext; }

protected:
	static CSceneGL *m_pTop[PRIORITY_MAX];	// ���X�g�̐擪�|�C���^
	static CSceneGL *m_pCur[PRIORITY_MAX];	// ���X�g�̏I�[�|�C���^

	CSceneGL *m_pPrev;		// �O�Q�Ɛ�|�C���^
	CSceneGL *m_pNext;		// ��Q�Ɛ�|�C���^

	VECTOR3 m_Pos;		// �ʒu
	VECTOR3 m_Rot;		// ��]�p

	BOX_DATA m_Box;	//�{�b�N�X�̃f�[�^
	PRIORITY m_Priority;
};

#endif