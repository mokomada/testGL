#ifndef _SCENEGL_H_
#define _SCENEGL_H_
//=============================================================================
//
//	タイトル	ヘッダファイル(scene.cpp)
//	ファイル名	scene.h
//	作成者		AT13A284_07 池田達哉
//	作成日		2016/04/19
//
//=============================================================================
#include "main.h"

//=============================================================================
//	構造体・列挙体
//=============================================================================
typedef enum
{
	PRIORITY_NONE = 0,
	PRIORITY_2D,
	PRIORITY_3D,
	PRIORITY_PLAYER,
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

//	当たり判定で使うボックスの情報
typedef struct
{
	float width;
	float height;
	float depth;
} BOX_DATA;

//=============================================================================
//	マクロ定義
//=============================================================================
#define	PRIORITY_NUM	(4)

//=============================================================================
//	クラス定義
//=============================================================================
class CSceneGL
{
public:
	CSceneGL(bool ifListAdd = true, int priority = 1, OBJTYPE objType = OBJTYPE_NONE);
	~CSceneGL();

	virtual void	Init(void) {};
	virtual void	Uninit(bool isLast = false) {};
	virtual void	Update(void) {};
	virtual void	Draw(void) {};

	static void	UpdateAll(void);
	static void	DrawAll(void);
	static void	DeleteAll(void);
	void		Release(void);
	void		UnlinkList(void);

	void		AddPos(VECTOR3 pos) { m_Pos += pos; }
	void		AddPos(float x, float y, float z) { m_Pos += VECTOR3(x, y, z); }
	void		AddRot(VECTOR3 rot) { m_Rot += rot; }
	void		AddRot(float x, float y, float z) { m_Rot += VECTOR3(x, y, z); }
	void		SetPos(VECTOR3 pos) { m_Pos = pos; }
	void		SetPos(float x, float y, float z) { m_Pos = VECTOR3(x, y, z); }
	void		SetRot(VECTOR3 rot) { m_Rot = rot; }
	void		SetRot(float x, float y, float z) { m_Rot = VECTOR3(x, y, z); }
	VECTOR3	GetPos(void) { return m_Pos; }
	VECTOR3	GetRot(void) { return m_Rot; }
	
	static void	glMatrixIdentity(MATRIX *matrix){	matrix->_11 = 1; matrix->_12 = 0; matrix->_13 = 0; matrix->_14 = 0;
													matrix->_21 = 0; matrix->_22 = 1; matrix->_23 = 0; matrix->_24 = 0;
													matrix->_31 = 0; matrix->_32 = 0; matrix->_33 = 1; matrix->_34 = 0;
													matrix->_41 = 0; matrix->_42 = 0; matrix->_43 = 0; matrix->_44 = 1;}

	static list<CSceneGL*> GetList(void) { return m_SceneList[0]; }
	static list<CSceneGL*> GetList(int priority) { return (priority < PRIORITY_NUM) ? m_SceneList[priority] : m_SceneList[0]; }

protected:
	static list<CSceneGL*>	m_SceneList[PRIORITY_NUM];	// リスト

	OBJTYPE	m_ObjType;		// オブジェクトタイプ

	int	m_Texture;		// テクスチャへのポインタ

	VECTOR3 m_Pos;		// 位置
	VECTOR3 m_Rot;		// 回転角
};

#endif