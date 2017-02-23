//=============================================================================
//
//	タイトル	紙吹雪
//	ファイル名	confetti.cpp
//	作成者		AT13A284_29 塩原聖士
//	作成日		2016/11/16
//
//=============================================================================
//=============================================================================
//	インクルード
//=============================================================================
#include "sceneGL.h"
#include "scene3DGL.h"
#include "confetti.h"
#include "manager.h"
#include "main.h"
#include "rendererGL.h"

//=============================================================================
//	マクロ定義
//=============================================================================

//紙吹雪限界位置
#define CONFETTI_LIMIT_POSY ( /*-100.0f*/ 0.0f )



//横移動開始位置
#define CONFETTI_RAND_START ( CONFETTI_START_POSY )

//重力
#define CONFETTI_GRAVITY ( /*-4.8f*/ -2.8f )
#define CONFETTI_RESISTANCE_X ( 0.0f )

#define CONFETTI_RANDPOS_X ( 5 )
#define CONFETTI_RANDPOS_Y ( 300 )
#define CONFETTI_RANDANGLE ( 10 )
#define CONFETTI_RANDANGLE_MIN ( 1.0f )
#define CONFETTI_RANDVEC_X ( 10 )

//重力抵抗値
#define CONFETTI_GRAVITYRESISTANCE_Y ( 0.8f )

//ずらす確率
#define CONFETTI_RANDSHIFT ( 3 )
#define CONFETTI_SHIFTPOWER ( 1.0f )

#define CONFETTI_TIME ( 300 )

int g_ConfettiTexture = 0;
//=============================================================================
//	関数名	:CConfetti()
//	引数	:無し
//	戻り値	:無し
//	説明	:コンストラクタ。
//=============================================================================
CConfetti::CConfetti(bool ifListAdd, int priority, OBJTYPE objtype) : CScene3DGL( ifListAdd , priority , objtype )
{

}

//=============================================================================
//	関数名	:~CConfetti()
//	引数	:無し
//	戻り値	:無し
//	説明	:デストラクタ。
//=============================================================================
CConfetti::~CConfetti()
{

}


//=============================================================================
//	関数名	:Init
//	引数	:VECTOR3 pos(初期位置)
//	戻り値	:無し
//	説明	:初期化処理を行うと共に、初期位置を設定する。
//=============================================================================
void CConfetti::Init(VECTOR3 pos, VECTOR2 size , VECTOR3 resistance , VECTOR3 rotaxis , float r , float g , float b , float a , char* texName)
{
	CRendererGL	*renderer = CManager::GetRendererGL();

	m_RandStart = false;
	m_MoveStart = false;

	// 各種初期設定
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
		// テクスチャ読込
		g_ConfettiTexture = renderer->CreateTextureTGA(texName);
	
		m_Texture = g_ConfettiTexture;
	}

}

//=============================================================================
//	関数名	:Uninit
//	引数	:無し
//	戻り値	:無し
//	説明	:終了処理を行う。
//=============================================================================
void CConfetti::Uninit(bool isLast)
{

}

//=============================================================================
//	関数名	:Update
//	引数	:無し
//	戻り値	:無し
//	説明	:更新処理を行う。
//=============================================================================
void CConfetti::Update(void)
{
	int shiftrand = 0;

	if( m_Time == 0 )
	{
		m_Pos.y = CONFETTI_START_POSY;
		m_Pos.x = m_BasePositionX;
		m_Pos.z = m_BasePositionZ;
		//ランダムによる加算値の再設定
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
				m_Angle -= 360.0f * 2.0f;/*一周分引く*/
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
			{//増加
				m_VecX *= 1.01f;
			}
			if( Absolutef( m_GravityResistance.y ) > 0.8f && Absolutef( m_VecZ ) < 1.0f )
			{//増加
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

				//加算値のリセット
				m_GravityResistanceVector = 0.0f;

				//基礎抵抗値
				m_GravityResistance.y = CONFETTI_GRAVITYRESISTANCE_Y;
				m_RandStart = true;
			}
			//角度の指定
			m_Axis.y = 0.5f - ( m_VecX / ( m_VecX + CONFETTI_GRAVITY * ( 1.0f - m_GravityResistance.y ) + 10.0f ) );

			//角度の指定
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
	//{//落下値が低い場合
	//	shiftrand = rand() % CONFETTI_RANDSHIFT;

	//	if( shiftrand == 0 )
	//	{
	//		if( m_VecX != 0 )
	//		{//マイナス方面へ移動
	//			m_VecXAdd -= ( m_VecX * CONFETTI_SHIFTPOWER );
	//		}
	//		else
	//		{//値が0.0fで動きがない場合
	//			m_VecXAdd -= CONFETTI_SHIFTPOWER;
	//		}
	//	}
	//	if( shiftrand == 1 )
	//	{
	//		if( m_VecX != 0 )
	//		{//プラス方面へ移動
	//			m_VecXAdd += ( m_VecX * CONFETTI_SHIFTPOWER );
	//		}
	//		else
	//		{//値が0.0fで動きがない場合
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
//	関数名	:Draw
//	引数	:無し
//	戻り値	:無し
//	説明	:描画処理を行う。
//=============================================================================
void CConfetti::Draw(void)
{
	//待機時間経過していないなら描画をしない
	if( m_Pos.y > CONFETTI_START_POSY )return;

	//モデルビューマトリクスの設定
	glMatrixMode(GL_MODELVIEW);
	// マトリクスの退避
	glPushMatrix();

	glDisable(GL_CULL_FACE);//カリングOFF

	// ワールドマトリクスの設定
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
	//アルファブレンド
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// 描画処理ここから
	glBindTexture(GL_TEXTURE_2D, m_Texture);
	glEnable(GL_TEXTURE_2D);
	
	// 深度バッファ設定
	glEnable(GL_DEPTH_TEST);

	// ライティングオフ
	glDisable(GL_LIGHTING);

	glBegin(GL_TRIANGLE_STRIP);
	{
		// 各種設定引き戻し
		glEnable(GL_LIGHTING);
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_DEPTH_TEST);

		// モデルビューマトリックスの設定
		glMatrixMode(GL_MODELVIEW);

		// 保存マトリックスの取り出し
		glPopMatrix();
		

		glNormal3f(0.0f, 1.0f, 0.0f);

		glColor4f( m_Color.r , m_Color.g , m_Color.b , m_Color.a );

		glTexCoord2d(0.0, 1.0);
		glVertex3f(-m_Size.x * 0.5f, m_Size.y * 0.5f, 0.0f);

		// 右上
		glNormal3f(0.0f, 1.0f, 0.0f);
		glTexCoord2d(1.0, 1.0);
		glVertex3f(m_Size.x * 0.5f, m_Size.y * 0.5f, 0.0f);

		// 左下
		glNormal3f(0.0f, 1.0f, 0.0f);
		glTexCoord2d(0.0, 0.0);
		glVertex3f(-m_Size.x * 0.5f, -m_Size.y * 0.5f,0.0f);

		// 右下
		glNormal3f(0.0f, 1.0f, 0.0f);
		glTexCoord2d(1.0, 0.0);
		glVertex3f(m_Size.x * 0.5f, -m_Size.y * 0.5f, 0.0f);
	}
	glEnd();

	// 各種設定引き戻し
	glEnable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH_TEST);

	// モデルビューマトリックスの設定
	glMatrixMode(GL_MODELVIEW);
	// 保存マトリックスの取り出し
	glPopMatrix();

	glDisable(GL_BLEND);

	// ブレンド設定
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}
//=============================================================================
//	関数名	:Create
//	引数	:pos(初期位置) , size(サイズ), resistance(移動抵抗率) , vecX(横移動力) , rotaxis(回転軸) , angle(回転速度) rgba(色) , texName(テクスチャパス)
//	戻り値	:無し
//	説明	:インスタンス生成を行うと共に、初期位置を設定する。
//=============================================================================
CConfetti *CConfetti::Create(VECTOR3 pos, VECTOR2 size, VECTOR3 resistance , VECTOR3 rotaxis , float r , float g  , float b , float a  ,  char* texName )
{
	//クラス変数定義
	CConfetti *cConfetti;

	//クラスの生成
	cConfetti = new CConfetti;

	//初期化
	cConfetti -> Init( pos , size , resistance , rotaxis , r , g , b , a , texName );

	//返し
	return cConfetti;
}
//=============================================================================
//	関数名	:複数のCreate
//	引数	:pos(初期位置) , size(サイズ), resistance(移動抵抗率) , vecX(横移動力) , rotaxis(回転軸) , angle(回転速度) , num(個数) , rgba(色) , texName(テクスチャパス)
//	戻り値	:無し
//	説明	:複数のインスタンス生成を行うと共に、初期位置を設定する。
//=============================================================================
void CConfetti::MultiCreate(VECTOR3 pos, VECTOR2 size, VECTOR3 resistance , int num , float r , float g  , float b , float a , char* texName )
{
	for( int nCntNum = 0 ; nCntNum < num ; nCntNum++ )
	{
		CConfetti::Create( pos , size , resistance , VECTOR3( 0.0f , 0.0f , 0.0f ) , r , g , b , a , texName );
	}
}
//=============================================================================
//	関数名	:MasterCreate
//	引数	:
//	戻り値	:無し
//	説明	:生成まとめ
//=============================================================================
void CConfetti::MasterCreate( )
{
	CConfetti::MultiCreate( VECTOR3( 10.0f , CONFETTI_START_POSY, -10.0f ) , VECTOR2( 3.5f , 1.5f ) , VECTOR3( 0.0f , 0.91f , 0.0f ), 100, 1.0f , 1.0f , 1.0f , 1.0f );
	CConfetti::MultiCreate( VECTOR3( -10.0f , CONFETTI_START_POSY, 10.0f ) , VECTOR2( 3.5f , 1.5f ) , VECTOR3( 0.0f , 0.91f , 0.0f ), 100, 1.0f , 1.0f , 1.0f , 1.0f );
	CConfetti::MultiCreate( VECTOR3( 10.0f , CONFETTI_START_POSY , 10.0f ) , VECTOR2( 3.5f , 1.5f ) , VECTOR3( 0.0f , 0.91f , 0.0f ) , 100, 1.0f , 1.0f , 0.0f , 1.0f );
	CConfetti::MultiCreate( VECTOR3( -10.0f , CONFETTI_START_POSY , -10.0f ) , VECTOR2( 3.5f , 1.5f ) , VECTOR3( 0.0f , 0.91f , 0.0f ) , 100, 1.0f , 1.0f , 0.0f , 1.0f );
}
//=============================================================================
//	関数名	:Absolutef
//	引数	:num( 値 )
//	戻り値	:float型絶対値
//	説明	:絶対値を返す
//=============================================================================
float CConfetti::Absolutef( float num )
{
	if( num <= 0.0f )
	{
		//符号反転
		num *= -1.0f;
	}
	return num;
}
//=============================================================================
//	関数名	:QuatToMatrix
//	引数	:クォータニオンをマトリクスに設定
//	戻り値	:無し
//	説明	:
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
//	関数名	:QuatToMatrix
//	引数	:クォータニオンの作成
//	戻り値	:無し
//	説明	:クォータニオン変数、回転角度、回転軸（x,y,z)
//=============================================================================
void CConfetti::CreateQuat(Quat *quat ,  float rot, float x, float y, float z)
{
	quat -> x = x * sin(rot / 2);
	quat -> y = y * sin(rot / 2);
	quat -> z = z * sin(rot / 2);
	quat -> w = cos(rot / 2);
}