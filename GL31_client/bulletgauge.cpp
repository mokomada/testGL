/*****************************************************************************
�^�C�g��  :�e���ː��䏈��
�t�@�C����:bulletgauge.cpp
�쐬��    :AT-12A-244 24 �ēc���l
�쐬��    :2017/02/01
�X�V����  :
����	  :
******************************************************************************/

/******************************************************************************
�C���N���[�h�t�@�C��
*******************************************************************************/
#include "bulletgauge.h"
#include "scene2DGL.h"
#include "rendererGL.h"
#include "manager.h"
#include "game.h"
#include "player.h"
#include "network.h"

/******************************************************************************
�}�N����`
******************************************************************************/
#define GAUGE_WIDTH 40.0f
#define GAUGE_WIDTH2 60.0f
#define GAUGE_WIDTH3 90.0f
#define GAUGE_HEIGHT 200.0f
#define ADDGAUGE 1.0f
#define BULLETGAUGEMAX 100.0f
#define BULLETGAUGEMAX2 200.0f
#define BULLETGAUGEMAX3 300.0f

/******************************************************************************
�\���̒�`
******************************************************************************/
/******************************************************************************
�O���[�o���ϐ�
******************************************************************************/
/******************************************************************************
�v���g�^�C�v�錾
******************************************************************************/
/******************************************************************************
�֐���:CBulletGauge::CBulletGauge(PRIORITY priority, OBJTYPE objType )
����  :PRIORITY priority, OBJTYPE objType
�߂�l:void
����  :
******************************************************************************/
CBulletGauge::CBulletGauge(bool ifListAdd, int priority, OBJTYPE objType)
{

}

/******************************************************************************
�֐���:CBulletGauge::~CTrickGauge( )
����  :void
�߂�l:void
����  :
******************************************************************************/
CBulletGauge::~CBulletGauge( )
{

}


/******************************************************************************
�֐���:void CBulletGauge::Init(void)
����  :void
�߂�l:void
����  :������
******************************************************************************/
void CBulletGauge::Init(void)
{
	CRendererGL	*renderer = CManager::GetRendererGL( );
	CGame *game;
	game = (CGame*)CManager::GetMode( );
	vector<CPlayer*> sceneModel = game->GetPlayer( );
	sceneModel[0]->GetGauge( );
	//�e�N�X�`���w��
	m_Texture[0] = renderer->CreateTextureTGA(".\\data\\TEXTURE\\gauge.png");
	m_Texture[1] = renderer->CreateTextureTGA(".\\data\\TEXTURE\\gauge.png");
	m_Texture[2] = renderer->CreateTextureTGA(".\\data\\TEXTURE\\gauge.png");
	m_color[0] = VECTOR4(1.0f, 0.0f, 0.0f, 1.0f);
	m_color[1] = VECTOR4(0.0f, 1.0f, 0.0f, 1.0f);
	m_color[2] = VECTOR4(0.0f, 0.0f, 1.0f, 1.0f);
	m_StrPos[0] = VECTOR3(0.0f, 0.0f, 0.0f);
	m_StrPos[1] = VECTOR3(GAUGE_WIDTH, 0.0f, 0.0f);
	m_StrPos[2] = VECTOR3(GAUGE_WIDTH + GAUGE_WIDTH, 0.0f, 0.0f);
	m_GaugeWidth[0] = GAUGE_WIDTH;
	m_GaugeWidth[1] = GAUGE_WIDTH;
	m_GaugeWidth[2] = GAUGE_WIDTH;
	m_GaugeMax[0] = BULLETGAUGEMAX3;
	m_GaugeMax[1] = BULLETGAUGEMAX3;
	m_GaugeMax[2] = BULLETGAUGEMAX3;
}

/******************************************************************************
�֐���:void CBulletGauge::Updete(void)
����  :void
�߂�l:void
����  :�X�V����
******************************************************************************/
void CBulletGauge::Update(void)
{
	CRendererGL	*renderer = CManager::GetRendererGL( );
	CGame *game;
	game = (CGame*)CManager::GetMode( );
	vector<CPlayer*> sceneModel = game->GetPlayer( );

	for(int i = 0 ; i < PLAYER_NUM ; i++)
	{
		m_Gauge = sceneModel[i]->GetGauge();
		if(m_Gauge <= 0)
		{
			m_Pa[0] = 0.0f;
		}
		else if(m_Gauge >= BULLETGAUGEMAX)
		{
			m_Pa[0] = 1.0f;
		}
		else
		{
			//1�ȏ�99�ȉ�
			m_Pa[0] = m_Gauge / BULLETGAUGEMAX;
			//m_Pa[0] = BULLETGAUGEMAX / ( (int)m_Gauge % (int)BULLETGAUGEMAX );
		}

		if(m_Gauge <= BULLETGAUGEMAX)
		{
			m_Pa[1] = 0;
		}
		else if(m_Gauge >= BULLETGAUGEMAX2)
		{
			m_Pa[1] = 1.0f;
		}
		else
		{
			//101�ȏ�199�ȉ�
			m_Pa[1] = m_Gauge / BULLETGAUGEMAX2;
		}

		if(m_Gauge <= BULLETGAUGEMAX2)
		{
			m_Pa[2] = 0;
		}
		else if(m_Gauge >= BULLETGAUGEMAX3)
		{
			m_Pa[2] = 1.0f;
		}
		else
		{
			//201�ȏ�299�ȉ�
			m_Pa[2] = m_Gauge / BULLETGAUGEMAX3;
		}

		if(m_Gauge < 0)
		{
			m_Gauge = 0;
		}
		if(m_Gauge >= BULLETGAUGEMAX3)
		{
			m_Gauge = BULLETGAUGEMAX3;
		}
		else
		{
			//�Q�[�W��
			sceneModel[i]->AddGauge(ADDGAUGE);
		}
	}
}

/******************************************************************************
�֐���:CBulletGauge Draw( void )
����  :void
�߂�l:void
����  :
******************************************************************************/
void CBulletGauge::Draw(void)
{
	// ���f���r���[�}�g���b�N�X�̐ݒ�(���e�ϊ�)
	glMatrixMode(GL_PROJECTION);
	// �}�g���b�N�X�̕ۑ�
	glPushMatrix( );
	// �ϊ��s��̏�����
	glLoadIdentity( );

	// ���s�ˉeor���ˉe
	glOrtho(0, (GLdouble)SCREEN_WIDTH, (GLdouble)SCREEN_HEIGHT, 0, -100.0, 100.0);
	// ���[���h���W�n�̕\���̈���C�r���[�|�[�g�̑傫���ɔ�Ⴓ����

	// ���f���r���[�}�g���b�N�X�̐ݒ�
	glMatrixMode(GL_MODELVIEW);
	// �}�g���b�N�X�̕ۑ�
	glPushMatrix( );
	// �ϊ��s��̏�����
	glLoadIdentity( );

	for ( int i = 0; i < 3; i++ )
	{
		// �`�揈����������
		glBindTexture(GL_TEXTURE_2D, m_Texture[i]);
		// �e�N�X�`���}�b�s���O�L����
		glEnable(GL_TEXTURE_2D);

		// �u�����h�L����
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		// ���C�g������
		glDisable(GL_LIGHTING);
		// �|���S���`��
		glBegin(GL_TRIANGLE_STRIP);
		//�|���S���J���[
		//�e�N�X�`�����W
		glTexCoord2d(0, 0);
		glColor4f(m_color[i].x, m_color[i].y, m_color[i].z, 1.0f);//RGBA
		glVertex3f(m_StrPos[i].x, GAUGE_HEIGHT, 0.0f);//XYZ

													  //�|���S���J���[
													  //�e�N�X�`�����W
		glTexCoord2d(0, 1);
		glColor4f(m_color[i].x, m_color[i].y, m_color[i].z, 1.0f);//RGBA
										  //�|���S�����W
		glVertex3f(m_StrPos[i].x, 100.0f, 0.0f);//XYZ

												//�e�N�X�`�����W
		glTexCoord2d(1, 0);
		glColor4f(m_color[i].x, m_color[i].y, m_color[i].z, 1.0f);//RGBA
		glVertex3f(m_StrPos[i].x + GAUGE_WIDTH * m_Pa[i], GAUGE_HEIGHT, 0.0f);//XYZ

																			  //�|���S���J���[
																			  //�e�N�X�`�����W
		glTexCoord2d(1, 1);
		glColor4f(m_color[i].x, m_color[i].y, m_color[i].z, 1.0f);//RGBA
		glVertex3f(m_StrPos[i].x + GAUGE_WIDTH * m_Pa[i], 100.0f, 0.0f);//XYZ

		glEnd( );
	}

	// �e�N�X�`���}�b�s���O������
	glDisable(GL_TEXTURE_2D);

	//�u�����h������
	glDisable(GL_BLEND);

	// ���C�g�L����
	glEnable(GL_LIGHTING);

	// ���f���r���[�}�g���b�N�X�̐ݒ�(���e�ϊ�)
	glMatrixMode(GL_PROJECTION);
	// �ۑ��}�g���b�N�X�̎��o��
	glPopMatrix( );

	// ���f���r���[�}�g���b�N�X�̐ݒ�
	glMatrixMode(GL_MODELVIEW);
	// �ۑ��}�g���b�N�X�̎��o��
	glPopMatrix( );
}

/******************************************************************************
�֐���:void CBulletGauge::subtract(float Subtract)
����  :float Subtract
�߂�l:float
����  :�Q�[�W���Z����
******************************************************************************/
float CBulletGauge::SubtractGauge(float Subtract)
{
	//���ݒl�����Z�l��葽��
	if ( m_Gauge > Subtract )
	{
		m_Gauge -= Subtract;
	}
	return m_Gauge;
}

/******************************************************************************
�֐���:void CBulletGauge::GetBulletGauge(void)
����  :void
�߂�l:float
����  :�Q�[�W�Q�b�g����
******************************************************************************/
float CBulletGauge::GetBulletGauge(void)
{
	return m_Gauge;
}
/******************************************************************************
�֐���:CBulletGauge CBulletGauge::*Create( void )
����  :void
�߂�l:void
����  :
******************************************************************************/
CBulletGauge *CBulletGauge::Create(void)
{
	CBulletGauge *BulletGauge;

	BulletGauge = new CBulletGauge;

	BulletGauge->Init( );

	return BulletGauge;
}