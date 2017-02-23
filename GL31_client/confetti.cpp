//=============================================================================
//
//	�^�C�g��	������
//	�t�@�C����	confetti.cpp
//	�쐬��		AT13A284_29 �������m
//	�쐬��		2016/11/16
//
//=============================================================================
//=============================================================================
//	�C���N���[�h
//=============================================================================
#include "sceneGL.h"
#include "scene3DGL.h"
#include "confetti.h"
#include "manager.h"
#include "main.h"
#include "rendererGL.h"

//=============================================================================
//	�}�N����`
//=============================================================================

//��������E�ʒu
#define CONFETTI_LIMIT_POSY ( /*-100.0f*/ 0.0f )



//���ړ��J�n�ʒu
#define CONFETTI_RAND_START ( CONFETTI_START_POSY )

//�d��
#define CONFETTI_GRAVITY ( /*-4.8f*/ -2.8f )
#define CONFETTI_RESISTANCE_X ( 0.0f )

#define CONFETTI_RANDPOS_X ( 5 )
#define CONFETTI_RANDPOS_Y ( 300 )
#define CONFETTI_RANDANGLE ( 10 )
#define CONFETTI_RANDANGLE_MIN ( 1.0f )
#define CONFETTI_RANDVEC_X ( 10 )

//�d�͒�R�l
#define CONFETTI_GRAVITYRESISTANCE_Y ( 0.8f )

//���炷�m��
#define CONFETTI_RANDSHIFT ( 3 )
#define CONFETTI_SHIFTPOWER ( 1.0f )

#define CONFETTI_TIME ( 300 )

int g_ConfettiTexture = 0;
//=============================================================================
//	�֐���	:CConfetti()
//	����	:����
//	�߂�l	:����
//	����	:�R���X�g���N�^�B
//=============================================================================
CConfetti::CConfetti(bool ifListAdd, int priority, OBJTYPE objtype) : CScene3DGL( ifListAdd , priority , objtype )
{

}

//=============================================================================
//	�֐���	:~CConfetti()
//	����	:����
//	�߂�l	:����
//	����	:�f�X�g���N�^�B
//=============================================================================
CConfetti::~CConfetti()
{

}


//=============================================================================
//	�֐���	:Init
//	����	:VECTOR3 pos(�����ʒu)
//	�߂�l	:����
//	����	:�������������s���Ƌ��ɁA�����ʒu��ݒ肷��B
//=============================================================================
void CConfetti::Init(VECTOR3 pos, VECTOR2 size , VECTOR3 resistance , VECTOR3 rotaxis , float r , float g , float b , float a , char* texName)
{
	CRendererGL	*renderer = CManager::GetRendererGL();

	m_RandStart = false;
	m_MoveStart = false;

	// �e�평���ݒ�
	m_Pos = pos;

	m_Pos.y += ( float )( rand() % CONFETTI_RANDPOS_Y );

	m_BasePositionX = pos.x;
	m_BasePositionZ = pos.z;
	m_Rot = VECTOR3( 0.0f , 0.0f , 0.0f );
	m_Size = size;
	m_VecX = 0.0f;
	m_VecZ = 0.0f;
	m_VecXAdd = 0.0f;
	m_GravityResistance = resistance;

	m_RotVec = ( float )( rand() % CONFETTI_RANDANGLE ) + CONFETTI_RANDANGLE_MIN;
	m_Axis = rotaxis;
	m_Angle = 0.0f;
	m_Color = SetColor( r , g , b , a );
	m_Time = CONFETTI_TIME;
	m_GravityResistanceVector = 0.0f;

	if( texName == NULL )return;
	
	if( g_ConfettiTexture != 0 )
	{
		m_Texture = g_ConfettiTexture;
	}
	else
	{
		// �e�N�X�`���Ǎ�
		g_ConfettiTexture = renderer->CreateTextureTGA(texName);
	
		m_Texture = g_ConfettiTexture;
	}

}

//=============================================================================
//	�֐���	:Uninit
//	����	:����
//	�߂�l	:����
//	����	:�I���������s���B
//=============================================================================
void CConfetti::Uninit(bool isLast)
{

}

//=============================================================================
//	�֐���	:Update
//	����	:����
//	�߂�l	:����
//	����	:�X�V�������s���B
//=============================================================================
void CConfetti::Update(void)
{
	int shiftrand = 0;

	if( m_Time == 0 )
	{
		m_Pos.y = CONFETTI_START_POSY;
		m_Pos.x = m_BasePositionX;
		m_Pos.z = m_BasePositionZ;
		//�����_���ɂ����Z�l�̍Đݒ�
		m_RandStart = false;
		m_Time = CONFETTI_TIME;
	}
	else
	{
		if( m_Pos.y > CONFETTI_LIMIT_POSY )
		{
			m_Pos += VECTOR3( m_VecX * ( 1.0f - CONFETTI_RESISTANCE_X ) , CONFETTI_GRAVITY * ( 1.0f - m_GravityResistance.y ) , m_VecZ * ( 1.0f - CONFETTI_RESISTANCE_X ) );
			m_Angle += m_RotVec;

			if( m_Angle > 360.0f )
			{
				m_Angle -= 360.0f * 2.0f;/*���������*/
			}
			else if( m_Angle < -360.0f )
			{
				m_Angle += 360.0f * 2.0f;
			}

			if( ( rand( ) % 100 ) == 0 )
			{
				m_GravityResistanceVector = rand( ) % 1000 - 500.0f;
				m_GravityResistanceVector *= 0.00001f;
			}
			m_GravityResistance.y += m_GravityResistanceVector;
			if( m_GravityResistance.y >= 0.9f )
			{
				m_GravityResistance.y = 0.8f;
			}
			if( m_GravityResistance.y <= 0.0f )
			{
				m_GravityResistance.y = 0.0f;
			}
			if( m_Pos.y <= CONFETTI_LIMIT_POSY )
			{

			}
	
			if( Absolutef( m_GravityResistance.y ) > 0.8f && Absolutef( m_VecX ) < 1.0f )
			{//����
				m_VecX *= 1.01f;
			}
			if( Absolutef( m_GravityResistance.y ) > 0.8f && Absolutef( m_VecZ ) < 1.0f )
			{//����
				m_VecZ *= 1.01f;
			}
			if( m_Pos.y <= CONFETTI_RAND_START && m_RandStart == false )
			{
				m_VecX = ( float )( rand( ) % CONFETTI_RANDVEC_X - CONFETTI_RANDVEC_X / 2 );

				if( Absolutef( m_VecX ) == 0.0f )
				{
					m_VecX += ( float )( rand( ) % 10 - 5 );
				}
				m_VecX *= 0.08f;

				m_VecZ = ( float )( rand( ) % CONFETTI_RANDVEC_X - CONFETTI_RANDVEC_X / 2 );

				if( Absolutef( m_VecZ ) == 0.0f )
				{
					m_VecZ += ( float )( rand( ) % 10 - 5 );
				}
				m_VecZ *= 0.08f;

				//���Z�l�̃��Z�b�g
				m_GravityResistanceVector = 0.0f;

				//��b��R�l
				m_GravityResistance.y = CONFETTI_GRAVITYRESISTANCE_Y;
				m_RandStart = true;
			}
			//�p�x�̎w��
			m_Axis.y = 0.5f - ( m_VecX / ( m_VecX + CONFETTI_GRAVITY * ( 1.0f - m_GravityResistance.y ) + 10.0f ) );

			//�p�x�̎w��
			m_Axis.x = ( CONFETTI_GRAVITY * ( 1.0f - m_GravityResistance.y ) + 10.0f  / ( m_VecX + CONFETTI_GRAVITY * ( 1.0f - m_GravityResistance.y ) + 10.0f ) );
		}
		else
		{
			m_Pos.y = CONFETTI_LIMIT_POSY;
			m_Axis.x = 0.0f;
			m_Axis.y = 0.0f;
			m_Time --;
		}

	}
	
	//if( Absolutef( m_GravityResistance.y ) > 0.5f && Absolutef( m_VecX ) < 8.0f )
	//{//�����l���Ⴂ�ꍇ
	//	shiftrand = rand() % CONFETTI_RANDSHIFT;

	//	if( shiftrand == 0 )
	//	{
	//		if( m_VecX != 0 )
	//		{//�}�C�i�X���ʂֈړ�
	//			m_VecXAdd -= ( m_VecX * CONFETTI_SHIFTPOWER );
	//		}
	//		else
	//		{//�l��0.0f�œ������Ȃ��ꍇ
	//			m_VecXAdd -= CONFETTI_SHIFTPOWER;
	//		}
	//	}
	//	if( shiftrand == 1 )
	//	{
	//		if( m_VecX != 0 )
	//		{//�v���X���ʂֈړ�
	//			m_VecXAdd += ( m_VecX * CONFETTI_SHIFTPOWER );
	//		}
	//		else
	//		{//�l��0.0f�œ������Ȃ��ꍇ
	//			m_VecXAdd += CONFETTI_SHIFTPOWER;
	//		}
	//	}
	//}
	//m_Pos += VECTOR3( m_VecX * ( 1.0f - CONFETTI_RESISTANCE_X ) , CONFETTI_GRAVITY * ( 1.0f - m_GravityResistance.y ) , 0.0f );
	//m_VecX *= 0.9f;
	//m_VecX += m_VecXAdd;
	//m_VecXAdd *= 0.9f;
	//m_Angle += m_RotVec;

	//if( m_Pos.y <= CONFETTI_START_POSY )
	//{
	//}


}
//=============================================================================
//	�֐���	:Draw
//	����	:����
//	�߂�l	:����
//	����	:�`�揈�����s���B
//=============================================================================
void CConfetti::Draw(void)
{
	//�ҋ@���Ԍo�߂��Ă��Ȃ��Ȃ�`������Ȃ�
	if( m_Pos.y > CONFETTI_START_POSY )return;

	//���f���r���[�}�g���N�X�̐ݒ�
	glMatrixMode(GL_MODELVIEW);
	// �}�g���N�X�̑ޔ�
	glPushMatrix();

	glDisable(GL_CULL_FACE);//�J�����OOFF

	// ���[���h�}�g���N�X�̐ݒ�
	glTranslatef(m_Pos.x, m_Pos.y, m_Pos.z);

	CreateQuat( &m_Quat , m_Angle , m_Axis.x , m_Axis.y , m_Axis.z );

	glRotatef(m_Angle, m_Axis.x, m_Axis.y, m_Axis.z);
	/*glRotatef(m_Angle, m_Axis.x, m_Axis.y, m_Axis.z);
	glRotatef(m_Angle, m_Axis.x, m_Axis.y, m_Axis.z);
	*/
	/*QuatToMatrix( &m_Matrix[ 0 ] , &m_Quat );

	glMultMatrixf( &m_Matrix[ 0 ] );

	glScalef(1.0f, 1.0f, 1.0f);
*/
	//�A���t�@�u�����h
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// �`�揈����������
	glBindTexture(GL_TEXTURE_2D, m_Texture);
	glEnable(GL_TEXTURE_2D);
	
	// �[�x�o�b�t�@�ݒ�
	glEnable(GL_DEPTH_TEST);

	// ���C�e�B���O�I�t
	glDisable(GL_LIGHTING);

	glBegin(GL_TRIANGLE_STRIP);
	{
		// �e��ݒ�����߂�
		glEnable(GL_LIGHTING);
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_DEPTH_TEST);

		// ���f���r���[�}�g���b�N�X�̐ݒ�
		glMatrixMode(GL_MODELVIEW);

		// �ۑ��}�g���b�N�X�̎��o��
		glPopMatrix();
		

		glNormal3f(0.0f, 1.0f, 0.0f);

		glColor4f( m_Color.r , m_Color.g , m_Color.b , m_Color.a );

		glTexCoord2d(0.0, 1.0);
		glVertex3f(-m_Size.x * 0.5f, m_Size.y * 0.5f, 0.0f);

		// �E��
		glNormal3f(0.0f, 1.0f, 0.0f);
		glTexCoord2d(1.0, 1.0);
		glVertex3f(m_Size.x * 0.5f, m_Size.y * 0.5f, 0.0f);

		// ����
		glNormal3f(0.0f, 1.0f, 0.0f);
		glTexCoord2d(0.0, 0.0);
		glVertex3f(-m_Size.x * 0.5f, -m_Size.y * 0.5f,0.0f);

		// �E��
		glNormal3f(0.0f, 1.0f, 0.0f);
		glTexCoord2d(1.0, 0.0);
		glVertex3f(m_Size.x * 0.5f, -m_Size.y * 0.5f, 0.0f);
	}
	glEnd();

	// �e��ݒ�����߂�
	glEnable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH_TEST);

	// ���f���r���[�}�g���b�N�X�̐ݒ�
	glMatrixMode(GL_MODELVIEW);
	// �ۑ��}�g���b�N�X�̎��o��
	glPopMatrix();

	glDisable(GL_BLEND);

	// �u�����h�ݒ�
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}
//=============================================================================
//	�֐���	:Create
//	����	:pos(�����ʒu) , size(�T�C�Y), resistance(�ړ���R��) , vecX(���ړ���) , rotaxis(��]��) , angle(��]���x) rgba(�F) , texName(�e�N�X�`���p�X)
//	�߂�l	:����
//	����	:�C���X�^���X�������s���Ƌ��ɁA�����ʒu��ݒ肷��B
//=============================================================================
CConfetti *CConfetti::Create(VECTOR3 pos, VECTOR2 size, VECTOR3 resistance , VECTOR3 rotaxis , float r , float g  , float b , float a  ,  char* texName )
{
	//�N���X�ϐ���`
	CConfetti *cConfetti;

	//�N���X�̐���
	cConfetti = new CConfetti;

	//������
	cConfetti -> Init( pos , size , resistance , rotaxis , r , g , b , a , texName );

	//�Ԃ�
	return cConfetti;
}
//=============================================================================
//	�֐���	:������Create
//	����	:pos(�����ʒu) , size(�T�C�Y), resistance(�ړ���R��) , vecX(���ړ���) , rotaxis(��]��) , angle(��]���x) , num(��) , rgba(�F) , texName(�e�N�X�`���p�X)
//	�߂�l	:����
//	����	:�����̃C���X�^���X�������s���Ƌ��ɁA�����ʒu��ݒ肷��B
//=============================================================================
void CConfetti::MultiCreate(VECTOR3 pos, VECTOR2 size, VECTOR3 resistance , int num , float r , float g  , float b , float a , char* texName )
{
	for( int nCntNum = 0 ; nCntNum < num ; nCntNum++ )
	{
		CConfetti::Create( pos , size , resistance , VECTOR3( 0.0f , 0.0f , 0.0f ) , r , g , b , a , texName );
	}
}
//=============================================================================
//	�֐���	:MasterCreate
//	����	:
//	�߂�l	:����
//	����	:�����܂Ƃ�
//=============================================================================
void CConfetti::MasterCreate( )
{
	CConfetti::MultiCreate( VECTOR3( 10.0f , CONFETTI_START_POSY, -10.0f ) , VECTOR2( 3.5f , 1.5f ) , VECTOR3( 0.0f , 0.91f , 0.0f ), 100, 1.0f , 1.0f , 1.0f , 1.0f );
	CConfetti::MultiCreate( VECTOR3( -10.0f , CONFETTI_START_POSY, 10.0f ) , VECTOR2( 3.5f , 1.5f ) , VECTOR3( 0.0f , 0.91f , 0.0f ), 100, 1.0f , 1.0f , 1.0f , 1.0f );
	CConfetti::MultiCreate( VECTOR3( 10.0f , CONFETTI_START_POSY , 10.0f ) , VECTOR2( 3.5f , 1.5f ) , VECTOR3( 0.0f , 0.91f , 0.0f ) , 100, 1.0f , 1.0f , 0.0f , 1.0f );
	CConfetti::MultiCreate( VECTOR3( -10.0f , CONFETTI_START_POSY , -10.0f ) , VECTOR2( 3.5f , 1.5f ) , VECTOR3( 0.0f , 0.91f , 0.0f ) , 100, 1.0f , 1.0f , 0.0f , 1.0f );
}
//=============================================================================
//	�֐���	:Absolutef
//	����	:num( �l )
//	�߂�l	:float�^��Βl
//	����	:��Βl��Ԃ�
//=============================================================================
float CConfetti::Absolutef( float num )
{
	if( num <= 0.0f )
	{
		//�������]
		num *= -1.0f;
	}
	return num;
}
//=============================================================================
//	�֐���	:QuatToMatrix
//	����	:�N�H�[�^�j�I�����}�g���N�X�ɐݒ�
//	�߂�l	:����
//	����	:
//=============================================================================
void CConfetti::QuatToMatrix( float *mat , Quat *quat)
{
	float qw, qx, qy, qz;
	float x2, y2, z2;
	float xy, yz, zx;
	float wx, wy, wz;

	qw = quat->w;
	qx = quat->x;
	qy = quat->y;
	qz = quat->z;

	x2 = 2.0f * qx * qx;
	y2 = 2.0f * qy * qy;
	z2 = 2.0f * qz * qz;

	xy = 2.0f * qx * qy;
	yz = 2.0f * qy * qz;
	zx = 2.0f * qz * qx;

    wx = 2.0f * qw * qx;
    wy = 2.0f * qw * qy;
    wz = 2.0f * qw * qz;

	mat[ 0 ] = 1.0f - y2 - z2;
	mat[ 1 ] = xy - wz;
	mat[ 2 ] = zx + wy;
	mat[ 3 ] = 0.0f;

	mat[ 4 ] = xy + wz;
	mat[ 5 ] = 1.0f - z2 - x2;
	mat[ 6 ] = yz - wx;
	mat[ 7 ] = 0.0f;

	mat[ 8 ] = zx - wy;
	mat[ 9 ] = yz + wx;
	mat[ 10 ] = 1.0f - x2 - y2;
	mat[ 11 ] = 0.0f;

	mat[ 12 ] = mat[ 13 ] = mat[ 14 ] = 0.0f;
	mat[ 15 ] = 1.0f;
}

//=============================================================================
//	�֐���	:QuatToMatrix
//	����	:�N�H�[�^�j�I���̍쐬
//	�߂�l	:����
//	����	:�N�H�[�^�j�I���ϐ��A��]�p�x�A��]���ix,y,z)
//=============================================================================
void CConfetti::CreateQuat(Quat *quat ,  float rot, float x, float y, float z)
{
	quat -> x = x * sin(rot / 2);
	quat -> y = y * sin(rot / 2);
	quat -> z = z * sin(rot / 2);
	quat -> w = cos(rot / 2);
}