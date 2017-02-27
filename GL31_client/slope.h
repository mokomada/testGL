#ifndef _SLOPE_H_
#define _SLOPE_H_
//=============================================================================
//
//	�^�C�g��	�w�b�_�t�@�C��(scene3D.cpp)
//	�t�@�C����	scene3D.h
//	�쐬��		AT13A284_02 �H�c��
//	�쐬��		2017/02/22
//
//=============================================================================

//=============================================================================
//	�N���X��`
//=============================================================================
class CSlope : public CSceneGL
{
public:
	CSlope(bool ifListAdd = true, int priority = 0, OBJTYPE objType = OBJTYPE_NONE);
	~CSlope();

	void	Init(VECTOR3 vec[4], VECTOR3 pos, char *texName);
	void	Uninit(bool isLast);
	void	Update(void);
	void	Draw(void);

	static CSlope	*Create(VECTOR3 vec[4] , VECTOR3 pos, char *texName);
	void	DrawPolygon(void);

private:
	VECTOR3 m_VtxPos[4];		// �|���S���̃T�C�Y
	int		m_Texture;	// �e�N�X�`��

	MATRIX	m_mtxWorld; // ���[���h�}�g���b�N�X
};

#endif