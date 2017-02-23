//=============================================================================
//
//	�^�C�g��	�V�[���A�j���[�V�����t�@�C��(2D)
//	�t�@�C����	scene2D.cpp
//	�쐬��		AT13A284_29 �������m
//	�쐬��		2017/02/13
//
//=============================================================================
//=============================================================================
//	�C���N���[�h
//=============================================================================
#include "main.h"
#include "manager.h"
#include "rendererGL.h"
#include "scene2DGLAnimation.h"

//=============================================================================
//	�֐���	:CScene2DAnimation()
//	����	:����
//	�߂�l	:����
//	����	:�R���X�g���N�^�B
//=============================================================================
CScene2DGLAnimation::CScene2DGLAnimation(bool ifListAdd, int priority, OBJTYPE objType) : CSceneGL(ifListAdd, priority, objType)
{
	m_fLength	= 0.0f;
	m_fAngle	= 0.0f;
}

//=============================================================================
//	�֐���	:~CScene2D()
//	����	:����
//	�߂�l	:����
//	����	:�f�X�g���N�^�B
//=============================================================================
CScene2DGLAnimation::~CScene2DGLAnimation()
{

}

//=============================================================================
//	�֐���	:Init
//	����	:VECTOR3 pos(�����ʒu)
//	�߂�l	:����
//	����	:�������������s���Ƌ��ɁA�����ʒu��ݒ肷��B
//=============================================================================
void CScene2DGLAnimation::Init(VECTOR3 pos ,VECTOR2 size , int maxside , int maxlen , int maxanim , int maxtime , char *texName , int tex )
{
	CRendererGL	*renderer	= CManager::GetRendererGL();


	// �e�평���ݒ�
	m_Position = pos;
	m_Rotation = VECTOR3( 0.0f , 0.0f , 0.0f );

	m_Size		= size;
	m_fAngle	= atan2f(m_Size.x, m_Size.y);
	m_fLength	= hypotf(m_Size.x, m_Size.y) * 0.5f;

	m_MaxSide = maxside;
	m_MaxLen = maxlen;
	m_MaxAnim = maxanim;
	m_NowAnim = 0;
	m_MaxTime = maxtime;
	m_NowTime = 0;
	m_Move = NULL;
	m_Use = true;
	m_Start = true;

	if( tex == 0 )
	{
		// �e�N�X�`���Ǎ�
		m_Texture	= renderer->CreateTextureTGA(texName);
	}
	else
	{
		m_Texture = tex;
	}
}

//=============================================================================
//	�֐���	:Uninit
//	����	:����
//	�߂�l	:����
//	����	:�I���������s���B
//=============================================================================
void CScene2DGLAnimation::Uninit(bool isLast)
{
	// �e�N�X�`���폜
	if(m_Texture != NULL)
	{
		if(isLast)
		glDeleteTextures(1, ((GLuint *)m_Texture));
	}
	if(m_Move != NULL)
	{
		delete m_Move;
		m_Move = NULL;
	}
}

//=============================================================================
//	�֐���	:Update
//	����	:����
//	�߂�l	:����
//	����	:�X�V�������s���B
//=============================================================================
void CScene2DGLAnimation::Update(void)
{
	if( m_Move != NULL )
	{
		m_Move -> Update( );
	}
	if( m_Use == false )return;

	if( m_Start == false )return;

	if( !( m_NowTime = ( m_NowTime + 1 ) % m_MaxTime ) )
	{//�o�ߎ��ԓ��B������
		if( m_NowAnim < m_MaxAnim - 1)
		{
			m_NowAnim += 1;
		}
		else
		{
			m_Use = false;
		}
	}
}

//=============================================================================
//	�֐���	:Draw
//	����	:����
//	�߂�l	:����
//	����	:�`�揈�����s���B
//=============================================================================
void CScene2DGLAnimation::Draw(void)
{
	if( m_Use == false )return;

	// ���f���r���[�}�g���b�N�X�̐ݒ�(���e�ϊ�)

	glMatrixMode(GL_PROJECTION);
	// �}�g���b�N�X�̕ۑ�
	glPushMatrix();
	// �ϊ��s��̏�����
	glLoadIdentity();

	// ���s�ˉeor���ˉe
	glOrtho(0, (GLdouble)SCREEN_WIDTH, (GLdouble)SCREEN_HEIGHT, 0, -100.0, 100.0);
	// ���[���h���W�n�̕\���̈���C�r���[�|�[�g�̑傫���ɔ�Ⴓ����

	// ���f���r���[�}�g���b�N�X�̐ݒ�
	glMatrixMode(GL_MODELVIEW);
	// �}�g���b�N�X�̕ۑ�
	glPushMatrix();
	// �ϊ��s��̏�����
	glLoadIdentity();
	
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
	{
		// ���_�F�ݒ�
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

		// ���_���ݒ�
		DrawPolygon();
	}
	glEnd();

	// �e�N�X�`���}�b�s���O������
	glDisable(GL_TEXTURE_2D);
	
	// �u�����h������
	glDisable(GL_BLEND);

	// ���C�g�L����
	glEnable(GL_LIGHTING);
	
	// ���f���r���[�}�g���b�N�X�̐ݒ�(���e�ϊ�)
	glMatrixMode(GL_PROJECTION);
	// �ۑ��}�g���b�N�X�̎��o��
	glPopMatrix();

	// ���f���r���[�}�g���b�N�X�̐ݒ�
	glMatrixMode(GL_MODELVIEW);
	// �ۑ��}�g���b�N�X�̎��o��
	glPopMatrix();
}

//=============================================================================
//	�֐���	:Create
//	����	:VECTOR3 pos(�����ʒu)
//	�߂�l	:����
//	����	:�C���X�^���X�������s���Ƌ��ɁA�����ʒu��ݒ肷��B
//=============================================================================
CScene2DGLAnimation *CScene2DGLAnimation::Create(VECTOR3 pos ,VECTOR2 size , int maxside , int maxlen , int maxanim , int maxtime , char *texName , int tex )
{
	CScene2DGLAnimation *scene2Danimation;

	scene2Danimation = new CScene2DGLAnimation;

	scene2Danimation -> Init(pos, size, maxside , maxlen , maxanim , maxtime , texName , tex );

	return scene2Danimation;
}

//=============================================================================
//	�֐���	:DrawPolygon
//	����	:����
//	�߂�l	:����
//	����	:�|���S���̒��_�����Z�b�g����B
//=============================================================================
void CScene2DGLAnimation::DrawPolygon(void)
{
	// �ΐ��̒����v�Z
	m_fLength	= hypotf(m_Size.x, m_Size.y) * 0.5f;

	// �`��p�̃e�N�X�`�����W�E���_���W�ݒ�
	// ���㒸�_
	glTexCoord2d(( 1 / ( float )m_MaxSide ) * ( m_NowAnim % m_MaxSide ) , ( 1 / ( float )m_MaxLen ) * ( m_NowAnim / m_MaxSide ));
	glVertex3f((m_Position.x - (sinf(m_fAngle + m_Rotation.z) * m_fLength)), (m_Position.y + (cosf(m_fAngle + m_Rotation.z + PI) * m_fLength)), 0.0f);

	// �E�㒸�_
	glTexCoord2d( ( ( 1 / ( float )m_MaxSide ) * ( m_NowAnim % m_MaxSide + 1 ) ), ( 1 / ( float )m_MaxLen ) * ( m_NowAnim / m_MaxSide ) );
	glVertex3f((m_Position.x - (sinf(-m_fAngle + m_Rotation.z) * m_fLength)), (m_Position.y + (cosf(-m_fAngle + m_Rotation.z + PI) * m_fLength)), 0.0f);

	// �������_
	glTexCoord2d( ( 1 / ( float )m_MaxSide ) * ( m_NowAnim % m_MaxSide ), ( 1 / ( float )m_MaxLen ) * ( ( m_NowAnim / m_MaxSide ) + 1 ));
	glVertex3f((m_Position.x - (sinf(-m_fAngle + m_Rotation.z + PI) * m_fLength)), (m_Position.y + (cosf(-m_fAngle + m_Rotation.z) * m_fLength)), 0.0f);

	// �E�����_
	glTexCoord2d( ( ( 1 / ( float )m_MaxSide ) * ( m_NowAnim % m_MaxSide + 1 ) ), ( 1 / ( float )m_MaxLen ) * ( ( m_NowAnim / m_MaxSide ) + 1 ));
	glVertex3f((m_Position.x - (sinf(m_fAngle + m_Rotation.z - PI) * m_fLength)), (m_Position.y + (cosf(m_fAngle + m_Rotation.z) * m_fLength)), 0.0f);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------

//=============================================================================
//	�֐���	:CSceneMove()
//	����	:����
//	�߂�l	:����
//	����	:�R���X�g���N�^�B
//=============================================================================
CSceneMove::CSceneMove()
{
}

//=============================================================================
//	�֐���	:~CScenemove()
//	����	:����
//	�߂�l	:����
//	����	:�f�X�g���N�^�B
//=============================================================================
CSceneMove::~CSceneMove()
{

}

//=============================================================================
//	�֐���	:Create
//	����	:
//	�߂�l	:
//	����	:�ړ��␳�̐���
//=============================================================================
CSceneMove* CSceneMove::Create( VECTOR3 *pos , VECTOR3 *rot , VECTOR3 posaccele , VECTOR3 rotaccele , int time , MOVETYPE type )
{
	CSceneMove *scenemove;

	scenemove = new CSceneMove;

	scenemove -> Init( pos, rot , posaccele , rotaccele , time , type );

	return scenemove;
}

//=============================================================================
//	�֐���	:Init
//	����	:
//	�߂�l	:
//	����	:������
//=============================================================================
void CSceneMove::Init( VECTOR3 *pos , VECTOR3 *rot , VECTOR3 posaccele , VECTOR3 rotaccele , int time , MOVETYPE type )
{
	m_PositionP = pos;

	m_RotationP = rot;

	m_PositionAccele = posaccele;

	m_RotationAccele = rotaccele;

	m_MaxTime = m_Time = time;

	m_Type = type;

	//�񔽓]���
	m_ReturnSwitch = false;
}

//=============================================================================
//	�֐���	:Update
//	����	:
//	�߂�l	:
//	����	:�X�V
//=============================================================================
void CSceneMove::Update( void )
{
	switch( m_Type )
	{
		case MOVETYPE_STRAIGHT:
		{
			//LOOP�Ɠ���
		}
		case MOVETYPE_LOOP:
		{

			//�ړ�
			m_PositionP -> x += m_PositionAccele.x;
			m_PositionP -> y += m_PositionAccele.y;
			m_PositionP -> z += m_PositionAccele.z;
			break;
		}
	}
	//���Ԍ���
	m_Time --;

	if( m_Time == 0 )
	{//�������Ԃ��Ȃ��Ȃ�����
		switch( m_Type )
		{
			case MOVETYPE_STRAIGHT:
			{
				//�����ɐݒ�
				m_Type = MOVETYPE_NONE;
				break;
			}
			case MOVETYPE_LOOP:
			{
				//���]
				m_ReturnSwitch = !m_ReturnSwitch;

				//�������]
				m_PositionAccele = VECTOR3( -m_PositionAccele.x , -m_PositionAccele.y , -m_PositionAccele.z );
				m_RotationAccele = VECTOR3( -m_RotationAccele.x , -m_RotationAccele.y , -m_RotationAccele.z );

				//�������Ԃ̕���
				m_Time = m_MaxTime;
				break;
			}
		}
	}
}