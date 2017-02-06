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
	PRIORITY_2D,
	PRIORITY_3D,
	PRIORITY_PLAYER,
	PRIORITY_BULLET,
	PRIORITY_WALL,
	PRIORITY_FIELD,
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
	virtual void	Init(void) {};
	virtual void	Uninit(bool isLast = false) {};
	virtual void	Update(void) {};
	virtual void	Draw(void) {};

	static void	UpdateAll(void);
	static void	DrawAll(void);
	static void	DeleteAll(void);
	void		Release(void);
	void		UnlinkList(void);
	list<CSceneGL*> GetIterator(void) { ; }

	void		AddPos(VECTOR3 pos) { m_Pos += pos; }
	void		AddPos(float x, float y, float z) { m_Pos += VECTOR3(x, y, z); }
	void		AddRot(VECTOR3 rot) { m_Rot += rot; }
	void		AddRot(float x, float y, float z) { m_Rot += VECTOR3(x, y, z); }
	void		SetPos(VECTOR3 pos) { m_Pos = pos; }
	void		SetPos(float x, float y, float z) { m_Pos = VECTOR3(x, y, z); }
	void		SetRot(VECTOR3 rot) { m_Rot = rot; }
	void		SetRot(float x, float y, float z) { m_Rot = VECTOR3(x, y, z); }
	void SetBox(BOX_DATA Box) { m_Box = Box; }
	void SetRadius(float Radius) { m_Radius = Radius; }
	VECTOR3	GetPos(void) { return m_Pos; }
	VECTOR3	GetRot(void) { return m_Rot; }
	BOX_DATA GetBox(void) { return m_Box; }
	float GetRadius(void) { return m_Radius; }
	OBJTYPE GetObjtype(void) { return m_ObjType; }
	
	static void	glMatrixIdentity(MATRIX *matrix){	matrix->_11 = 1; matrix->_12 = 0; matrix->_13 = 0; matrix->_14 = 0;
													matrix->_21 = 0; matrix->_22 = 1; matrix->_23 = 0; matrix->_24 = 0;
													matrix->_31 = 0; matrix->_32 = 0; matrix->_33 = 1; matrix->_34 = 0;
													matrix->_41 = 0; matrix->_42 = 0; matrix->_43 = 0; matrix->_44 = 1;}

	static list<CSceneGL*> GetList(void) { return m_List[0]; }
	static list<CSceneGL*> GetList(int priority) { return (priority < PRIORITY_MAX) ? m_List[priority] : m_List[0]; }

protected:
	CSceneGL(bool ifListAdd = true, int priority = 1, OBJTYPE objType = OBJTYPE_NONE);
	~CSceneGL();

	static list<CSceneGL*>	m_List[PRIORITY_MAX];	// ���X�g
	static list<CSceneGL*>::iterator m_ListItr;		// ���X�g�̃C�e���[�^

	OBJTYPE	m_ObjType;		// �I�u�W�F�N�g�^�C�v

	int	m_Texture;		// �e�N�X�`���ւ̃|�C���^

	VECTOR3 m_Pos;		// �ʒu
	VECTOR3 m_Rot;		// ��]�p
	BOX_DATA m_Box;	//�����蔻��p�̃{�b�N�X���
	float m_Radius;	//�����蔻��p�̔��a���
};

#endif