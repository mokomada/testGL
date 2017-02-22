#ifndef _SCENE2DANIMATION_H_
#define _SCENE2DANIMATION_H_
//=============================================================================
//
//	�^�C�g��	�w�b�_�t�@�C��(scene2D.cpp)
//	�t�@�C����	scene2D.h
//	�쐬��		AT13A284_07 �r�c�B��
//	�쐬��		2016/04/20
//
//=============================================================================
#include "sceneGL.h"
//=============================================================================
//	�񋓑�
//=============================================================================
typedef enum
{
	MOVETYPE_NONE = 0 ,
	MOVETYPE_LOOP ,
	MOVETYPE_STRAIGHT ,
}MOVETYPE;
//=============================================================================
//	�}�N����`
//=============================================================================
#define	POLYGON2D_WIDTH		(100.0f)				// �|���S���̉���
#define	POLYGON2D_HEIGHT	(100.0f)				// �|���S���̏c��

class CSceneMove;

//=============================================================================
//	�N���X��`
//=============================================================================

//�ړ��⏕�N���X
class CSceneMove
{
	public:
	CSceneMove();
	~CSceneMove();

	static CSceneMove *Create( VECTOR3 *pos , VECTOR3 *rot , VECTOR3 posaccele , VECTOR3 rotaccele , int time , MOVETYPE type );

	void Update();
	void Init(VECTOR3 *pos , VECTOR3 *rot , VECTOR3 posaccele , VECTOR3 rotaccele , int time , MOVETYPE type);

	private:
		VECTOR3 *m_PositionP;
		VECTOR3 *m_RotationP;
		VECTOR3 m_PositionAccele;
		VECTOR3 m_RotationAccele;
		int m_Time;
		int m_MaxTime;
		MOVETYPE m_Type;
		bool m_ReturnSwitch;
};
class CScene2DGLAnimation : public CSceneGL
{
public:
	CScene2DGLAnimation(bool ifListAdd = true, int priority = 0, OBJTYPE objType = OBJTYPE_NONE);
	~CScene2DGLAnimation();

	void	Init(VECTOR3 pos = VECTOR3(0.0f, 0.0f, 0.0f),
				VECTOR2 size = VECTOR2(POLYGON2D_WIDTH, POLYGON2D_HEIGHT ) , int maxside = 0, int maxlen = 0 , int maxanim = 0 , int maxtime = 0,
				char *texName = "./data/TEXTURE/sample_image.tga" , int tex = 0 );
	void	Uninit(bool isLast = false);
	void	Update(void);
	void	Draw(void);
	
	static CScene2DGLAnimation	*Create(VECTOR3 pos = VECTOR3(0.0f, 0.0f, 0.0f),
				VECTOR2 size = VECTOR2(POLYGON2D_WIDTH, POLYGON2D_HEIGHT ) , int maxside = 0, int maxlen = 0 , int maxanim = 0, int maxtime = 0 ,
				char *texName = "./data/TEXTURE/sample_image.tga" , int tex = 0 );

	void	DrawPolygon(void);

	void SetStartAnimation( bool start ){ m_Start = start; };//�J�nor��~�X�C�b�`

	VECTOR3* GetPositionP( void ){ return &m_Position; };

	VECTOR3* GetRotationP( void ){ return &m_Rotation; };

	//�ړ��⏕�̐ݒ�
	void SetMove( CSceneMove *move ){ m_Move = move; };

private:
	VECTOR2 m_Size;		// �|���S���̃T�C�Y
	float	m_fLength;	// �Ίp���̒���
	float	m_fAngle;	// �p�x
	int		m_Texture;	// �e�N�X�`��

	int m_MaxSide; //�ő剡��
	int m_MaxLen; //�ő�c��
	int m_NowAnim; //���݃A�j���[�V�����ԍ�
	int m_MaxAnim; //�ő�A�j���[�V�����ԍ�
	int m_NowTime; //�o�ߎ���
	int m_MaxTime; //�ő厞��

	VECTOR3 m_Position;
	VECTOR3 m_Rotation;
	CSceneMove *m_Move;
	bool m_Use; //�g�p���
	bool m_Start;
};

#endif