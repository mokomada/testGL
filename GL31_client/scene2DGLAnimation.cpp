//=============================================================================
//
//	タイトル	シーンアニメーションファイル(2D)
//	ファイル名	scene2D.cpp
//	作成者		AT13A284_29 塩原聖士
//	作成日		2017/02/13
//
//=============================================================================
//=============================================================================
//	インクルード
//=============================================================================
#include "main.h"
#include "manager.h"
#include "rendererGL.h"
#include "scene2DGLAnimation.h"

//=============================================================================
//	関数名	:CScene2DAnimation()
//	引数	:無し
//	戻り値	:無し
//	説明	:コンストラクタ。
//=============================================================================
CScene2DGLAnimation::CScene2DGLAnimation(bool ifListAdd, int priority, OBJTYPE objType) : CSceneGL(ifListAdd, priority, objType)
{
	m_fLength	= 0.0f;
	m_fAngle	= 0.0f;
}

//=============================================================================
//	関数名	:~CScene2D()
//	引数	:無し
//	戻り値	:無し
//	説明	:デストラクタ。
//=============================================================================
CScene2DGLAnimation::~CScene2DGLAnimation()
{

}

//=============================================================================
//	関数名	:Init
//	引数	:VECTOR3 pos(初期位置)
//	戻り値	:無し
//	説明	:初期化処理を行うと共に、初期位置を設定する。
//=============================================================================
void CScene2DGLAnimation::Init(VECTOR3 pos ,VECTOR2 size , int maxside , int maxlen , int maxanim , int maxtime , char *texName , int tex )
{
	CRendererGL	*renderer	= CManager::GetRendererGL();


	// 各種初期設定
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
		// テクスチャ読込
		m_Texture	= renderer->CreateTextureTGA(texName);
	}
	else
	{
		m_Texture = tex;
	}
}

//=============================================================================
//	関数名	:Uninit
//	引数	:無し
//	戻り値	:無し
//	説明	:終了処理を行う。
//=============================================================================
void CScene2DGLAnimation::Uninit(bool isLast)
{
	// テクスチャ削除
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
//	関数名	:Update
//	引数	:無し
//	戻り値	:無し
//	説明	:更新処理を行う。
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
	{//経過時間到達したら
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
//	関数名	:Draw
//	引数	:無し
//	戻り値	:無し
//	説明	:描画処理を行う。
//=============================================================================
void CScene2DGLAnimation::Draw(void)
{
	if( m_Use == false )return;

	// モデルビューマトリックスの設定(投影変換)

	glMatrixMode(GL_PROJECTION);
	// マトリックスの保存
	glPushMatrix();
	// 変換行列の初期化
	glLoadIdentity();

	// 平行射影or正射影
	glOrtho(0, (GLdouble)SCREEN_WIDTH, (GLdouble)SCREEN_HEIGHT, 0, -100.0, 100.0);
	// ワールド座標系の表示領域を，ビューポートの大きさに比例させる

	// モデルビューマトリックスの設定
	glMatrixMode(GL_MODELVIEW);
	// マトリックスの保存
	glPushMatrix();
	// 変換行列の初期化
	glLoadIdentity();
	
	// 描画処理ここから
	glBindTexture(GL_TEXTURE_2D, m_Texture);

	// テクスチャマッピング有効化
	glEnable(GL_TEXTURE_2D);

	// ブレンド有効化
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// ライト無効化
	glDisable(GL_LIGHTING);

	// ポリゴン描画
	glBegin(GL_TRIANGLE_STRIP);
	{
		// 頂点色設定
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

		// 頂点情報設定
		DrawPolygon();
	}
	glEnd();

	// テクスチャマッピング無効化
	glDisable(GL_TEXTURE_2D);
	
	// ブレンド無効化
	glDisable(GL_BLEND);

	// ライト有効化
	glEnable(GL_LIGHTING);
	
	// モデルビューマトリックスの設定(投影変換)
	glMatrixMode(GL_PROJECTION);
	// 保存マトリックスの取り出し
	glPopMatrix();

	// モデルビューマトリックスの設定
	glMatrixMode(GL_MODELVIEW);
	// 保存マトリックスの取り出し
	glPopMatrix();
}

//=============================================================================
//	関数名	:Create
//	引数	:VECTOR3 pos(初期位置)
//	戻り値	:無し
//	説明	:インスタンス生成を行うと共に、初期位置を設定する。
//=============================================================================
CScene2DGLAnimation *CScene2DGLAnimation::Create(VECTOR3 pos ,VECTOR2 size , int maxside , int maxlen , int maxanim , int maxtime , char *texName , int tex )
{
	CScene2DGLAnimation *scene2Danimation;

	scene2Danimation = new CScene2DGLAnimation;

	scene2Danimation -> Init(pos, size, maxside , maxlen , maxanim , maxtime , texName , tex );

	return scene2Danimation;
}

//=============================================================================
//	関数名	:DrawPolygon
//	引数	:無し
//	戻り値	:無し
//	説明	:ポリゴンの頂点情報をセットする。
//=============================================================================
void CScene2DGLAnimation::DrawPolygon(void)
{
	// 斜線の長さ計算
	m_fLength	= hypotf(m_Size.x, m_Size.y) * 0.5f;

	// 描画用のテクスチャ座標・頂点座標設定
	// 左上頂点
	glTexCoord2d(( 1 / ( float )m_MaxSide ) * ( m_NowAnim % m_MaxSide ) , ( 1 / ( float )m_MaxLen ) * ( m_NowAnim / m_MaxSide ));
	glVertex3f((m_Position.x - (sinf(m_fAngle + m_Rotation.z) * m_fLength)), (m_Position.y + (cosf(m_fAngle + m_Rotation.z + PI) * m_fLength)), 0.0f);

	// 右上頂点
	glTexCoord2d( ( ( 1 / ( float )m_MaxSide ) * ( m_NowAnim % m_MaxSide + 1 ) ), ( 1 / ( float )m_MaxLen ) * ( m_NowAnim / m_MaxSide ) );
	glVertex3f((m_Position.x - (sinf(-m_fAngle + m_Rotation.z) * m_fLength)), (m_Position.y + (cosf(-m_fAngle + m_Rotation.z + PI) * m_fLength)), 0.0f);

	// 左下頂点
	glTexCoord2d( ( 1 / ( float )m_MaxSide ) * ( m_NowAnim % m_MaxSide ), ( 1 / ( float )m_MaxLen ) * ( ( m_NowAnim / m_MaxSide ) + 1 ));
	glVertex3f((m_Position.x - (sinf(-m_fAngle + m_Rotation.z + PI) * m_fLength)), (m_Position.y + (cosf(-m_fAngle + m_Rotation.z) * m_fLength)), 0.0f);

	// 右下頂点
	glTexCoord2d( ( ( 1 / ( float )m_MaxSide ) * ( m_NowAnim % m_MaxSide + 1 ) ), ( 1 / ( float )m_MaxLen ) * ( ( m_NowAnim / m_MaxSide ) + 1 ));
	glVertex3f((m_Position.x - (sinf(m_fAngle + m_Rotation.z - PI) * m_fLength)), (m_Position.y + (cosf(m_fAngle + m_Rotation.z) * m_fLength)), 0.0f);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------

//=============================================================================
//	関数名	:CSceneMove()
//	引数	:無し
//	戻り値	:無し
//	説明	:コンストラクタ。
//=============================================================================
CSceneMove::CSceneMove()
{
}

//=============================================================================
//	関数名	:~CScenemove()
//	引数	:無し
//	戻り値	:無し
//	説明	:デストラクタ。
//=============================================================================
CSceneMove::~CSceneMove()
{

}

//=============================================================================
//	関数名	:Create
//	引数	:
//	戻り値	:
//	説明	:移動補正の生成
//=============================================================================
CSceneMove* CSceneMove::Create( VECTOR3 *pos , VECTOR3 *rot , VECTOR3 posaccele , VECTOR3 rotaccele , int time , MOVETYPE type )
{
	CSceneMove *scenemove;

	scenemove = new CSceneMove;

	scenemove -> Init( pos, rot , posaccele , rotaccele , time , type );

	return scenemove;
}

//=============================================================================
//	関数名	:Init
//	引数	:
//	戻り値	:
//	説明	:初期化
//=============================================================================
void CSceneMove::Init( VECTOR3 *pos , VECTOR3 *rot , VECTOR3 posaccele , VECTOR3 rotaccele , int time , MOVETYPE type )
{
	m_PositionP = pos;

	m_RotationP = rot;

	m_PositionAccele = posaccele;

	m_RotationAccele = rotaccele;

	m_MaxTime = m_Time = time;

	m_Type = type;

	//非反転状態
	m_ReturnSwitch = false;
}

//=============================================================================
//	関数名	:Update
//	引数	:
//	戻り値	:
//	説明	:更新
//=============================================================================
void CSceneMove::Update( void )
{
	switch( m_Type )
	{
		case MOVETYPE_STRAIGHT:
		{
			//LOOPと同じ
		}
		case MOVETYPE_LOOP:
		{

			//移動
			m_PositionP -> x += m_PositionAccele.x;
			m_PositionP -> y += m_PositionAccele.y;
			m_PositionP -> z += m_PositionAccele.z;
			break;
		}
	}
	//時間減少
	m_Time --;

	if( m_Time == 0 )
	{//制限時間がなくなったら
		switch( m_Type )
		{
			case MOVETYPE_STRAIGHT:
			{
				//無しに設定
				m_Type = MOVETYPE_NONE;
				break;
			}
			case MOVETYPE_LOOP:
			{
				//反転
				m_ReturnSwitch = !m_ReturnSwitch;

				//向き反転
				m_PositionAccele = VECTOR3( -m_PositionAccele.x , -m_PositionAccele.y , -m_PositionAccele.z );
				m_RotationAccele = VECTOR3( -m_RotationAccele.x , -m_RotationAccele.y , -m_RotationAccele.z );

				//制限時間の復元
				m_Time = m_MaxTime;
				break;
			}
		}
	}
}