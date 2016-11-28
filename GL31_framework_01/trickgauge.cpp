/*****************************************************************************
�^�C�g��  :�K�E�Z����
�t�@�C����:trickgauge.cpp
�쐬��    :AT-12A-244 24 �ēc���l
�쐬��    :2016/11/16
�X�V����  :
����	  :
******************************************************************************/

/******************************************************************************
�C���N���[�h�t�@�C��
*******************************************************************************/
#include "trickgauge.h"
#include "scene2DGL.h"
#include "rendererGL.h"
#include "manager.h"

/******************************************************************************
�}�N����`
******************************************************************************/
#define GAUGE_WIDTH 100.0f
#define GAUGE_HEIGHT 200.0f
#define GAUGE_MAX 500.0f

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
�֐���:CTrickGauge::CTrickGauge(int priority, OBJTYPE objType )
����  :int priority, OBJTYPE objType
�߂�l:void
����  :
******************************************************************************/
CTrickGauge::CTrickGauge(int priority, OBJTYPE objType)
{

}

/******************************************************************************
�֐���:CTrickGauge::~CTrickGauge( )
����  :void
�߂�l:void
����  :
******************************************************************************/
CTrickGauge::~CTrickGauge( )
{

}


/******************************************************************************
�֐���:void CTrickGauge::Init(void)
����  :void
�߂�l:void
����  :������
******************************************************************************/
void CTrickGauge::Init(void)
{
	CManager	*manager = GetManager( );
	CRendererGL	*renderer = manager->GetRendererGL( );
	//�e�N�X�`���w��
	m_Texture = renderer->CreateTextureTGA(".\\data\\TEXTURE\\title000.tga");
	m_StrPos = VECTOR3( 0.0f,0.0f,0.0f );
	m_GaugeMax = 500.0f;
}

/******************************************************************************
�֐���:void CTrickGauge::Updete(void)
����  :void
�߂�l:void
����  :�X�V����
******************************************************************************/
void CTrickGauge::Update(void)
{
	//���݂̃Q�[�W
	m_Gauge = 200.0f;
	m_Pa = m_Gauge / m_GaugeMax;
	if ( CInput::GetKeyboardPress(DIK_K) )
	{
		m_Gauge++;
	}
	if ( CInput::GetKeyboardPress(DIK_M) )
	{
		m_Gauge--;
	}
	if ( m_Gauge < 0 )
	{
		m_Gauge = 0;
	}
	if ( m_Gauge > GAUGE_MAX )
	{
		m_Gauge = GAUGE_MAX;
	}
}

/******************************************************************************
�֐���:void CTrickGauge::Draw(void)
����  :void
�߂�l:void
����  :
******************************************************************************/
void CTrickGauge::Draw(void)
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

	// �`�揈����������
	glBindTexture(GL_TEXTURE_2D, m_Texture);

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
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);//RGBA
	glVertex3f(0, 200.0f, 0.0f);//XYZ

	//�|���S���J���[
	//�e�N�X�`�����W
	glTexCoord2d(0, 1);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);//RGBA
	//�|���S�����W
	glVertex3f(0, 100.0f, 0.0f);//XYZ

	//�e�N�X�`�����W
	glTexCoord2d(1, 0);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);//RGBA
	glVertex3f(GAUGE_WIDTH * m_Pa, GAUGE_HEIGHT, 0.0f);//XYZ

	//�|���S���J���[
	//�e�N�X�`�����W
	glTexCoord2d(1, 1);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);//RGBA
	glVertex3f(GAUGE_WIDTH * m_Pa, GAUGE_HEIGHT, 0.0f);//XYZ



	glEnd( );

	// �e�N�X�`���}�b�s���O������
	glDisable(GL_TEXTURE_2D);

	// �u�����h������
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
�֐���:CTrickGauge CTrickGauge::*Create( void )
����  :void
�߂�l:void
����  :
******************************************************************************/
CTrickGauge *CTrickGauge::Create(void)
{
	CTrickGauge *TrickGauge;

	TrickGauge = new CTrickGauge;

	TrickGauge->Init();

	return TrickGauge;
}