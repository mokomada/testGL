#ifndef _BULLETGAUGE_H_
#define _BULLETGAUGE_H_
/******************************************************************************
�C���N���[�h�t�@�C��
*******************************************************************************/
#include "scene2DGL.h"

/******************************************************************************
�}�N����`
******************************************************************************/
#define BULLETGAUGESubtract 100.0f
#define GAUGENUMBER 3
/******************************************************************************
�\���̒�`
******************************************************************************/
/******************************************************************************
�N���X
*******************************************************************************/
class CBulletGauge :public CScene2DGL
{
public://�N�ł��g����
	CBulletGauge(bool ifListAdd = true, int priority = 1, OBJTYPE objType = OBJTYPE_NONE);
	~CBulletGauge( );
	void Init(void);
	void Update(void);
	void Draw(void);
	float SubtractGauge(float f);
	float GetBulletGauge(void);
	static CBulletGauge *Create( );
private://���������g���Ȃ�
	int	m_Texture[GAUGENUMBER];	// �e�N�X�`��
	VECTOR3 m_StrPos[GAUGENUMBER];//�J�n�ʒu
	int m_Size;		//�T�C�Y
	float m_Pa[GAUGENUMBER];
	//���̃Q�[�W�̃}�b�N�X
	float m_GaugeMax[GAUGENUMBER];
	//�͂�
	float m_GaugeWidth[GAUGENUMBER];
	//���݂̃Q�[�W
	float m_Gauge;
};

#endif