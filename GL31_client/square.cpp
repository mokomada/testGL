//=============================================================================
//
//	タイトル	四角形
//	ファイル名	podium.cpp
//	作成者		AT13A284_02 秋田京
//	作成日		2016/12/07
//
//=============================================================================

//=============================================================================
//	インクルード
//=============================================================================

#include "manager.h"
#include "main.h"
#include "rendererGL.h"
#include "game.h"
#include "sceneGL.h"
#include "scene3DGL.h"
#include "square.h"

#define SQUARE_SIZE_MAX (50.0f)


/********************************************
---------------コンストラクタ----------------
*********************************************/
CSquare::CSquare(bool ifListAdd , int priority , OBJTYPE objType) : CScene3DGL( ifListAdd , priority , objType )
{
}


/********************************************
----------------デストラクタ-----------------
*********************************************/
CSquare::~CSquare()
{

}


/********************************************
-----------------初期化処理------------------
********************************************/
void CSquare::Init(VECTOR3 pos , VECTOR3 size , char* TexName, VECTOR4 color)
{
	CRendererGL	*renderer	= CManager::GetRendererGL();

	//初期位置
	m_Pos = pos;

	

	//大きさを指定
	m_Square.pos = VECTOR3(size.x * 0.5f, size.y * 0.5f, size.z *0.5f );

	CSquare::m_Box.width = size.x;
	CSquare::m_Box.height = size.y;
	CSquare::m_Box.depth = size.z;




	//色の指定
	m_Color = color;
	//初期角度
	m_Rot = VECTOR3(0.0f, 0.0f, 0.0f);
	
	m_Texture = renderer->CreateTextureTGA(TexName);
}

/********************************************
------------------描画処理-------------------
*******************************************/
void CSquare::Draw(void)
{

	//プロジェクションマトリックス
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();					//保存
	
	// 深度バッファ有効化
	glEnable(GL_DEPTH_TEST);

	glDisable(GL_LIGHTING);

	glDisable(GL_CULL_FACE);

	//ワールドマトリックス設定

	glTranslatef(m_Pos.x , m_Pos.y ,m_Pos.z);
	glRotatef(( m_Rot.x * 180 / PI ), 1.0f, 0.0f, 0.0f);
	glRotatef(( m_Rot.y * 180 / PI ), 0.0f, 1.0f, 0.0f);
	glRotatef(( m_Rot.z * 180 / PI ), 0.0f, 0.0f, 1.0f);
	glScalef(1.0f , 1.0f , 1.0f);

	//ポリゴン描画
	glBindTexture(GL_TEXTURE_2D , m_Texture);
	glEnable(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//下の面
	glBegin(GL_TRIANGLE_STRIP);

	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2d(0.0f, 0.0f);
	glColor4f( m_Color.x, m_Color.y, m_Color.z, m_Color.w );	//色(RGBA)
	glVertex3f( -m_Square.pos.x , -m_Square.pos.y , -m_Square.pos.z );

	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2d(m_Square.pos.x / SQ_SIZE_MAX, 0.0f);
	glColor4f( m_Color.x, m_Color.y, m_Color.z, m_Color.w );	//色(RGBA)
	glVertex3f( m_Square.pos.x , -m_Square.pos.y , -m_Square.pos.z );

	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2d(0.0f, m_Square.pos.z / SQ_SIZE_MAX);
	glColor4f( m_Color.x, m_Color.y, m_Color.z, m_Color.w );	//色(RGBA)
	glVertex3f(-m_Square.pos.x , -m_Square.pos.y , m_Square.pos.z );

	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2d(m_Square.pos.x / SQ_SIZE_MAX, m_Square.pos.z / SQ_SIZE_MAX);
	glColor4f( m_Color.x, m_Color.y, m_Color.z, m_Color.w );	//色(RGBA)
	glVertex3f( m_Square.pos.x , -m_Square.pos.y , m_Square.pos.z );

	glEnd();

	

	//手前の面
	glBegin(GL_TRIANGLE_STRIP);

	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2d(0.0f, 0.0f);
	glColor4f( m_Color.x, m_Color.y, m_Color.z, m_Color.w );	//色(RGBA)
	glVertex3f( -m_Square.pos.x , m_Square.pos.y , m_Square.pos.z );

	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2d(m_Square.pos.x / SQ_SIZE_MAX, 0.0f);
	glColor4f( m_Color.x, m_Color.y, m_Color.z, m_Color.w );	//色(RGBA)
	glVertex3f( m_Square.pos.x , m_Square.pos.y , m_Square.pos.z );

	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2d(0.0f, m_Square.pos.y / SQ_SIZE_MAX);
	glColor4f( m_Color.x, m_Color.y, m_Color.z, m_Color.w );	//色(RGBA)
	glVertex3f(-m_Square.pos.x , -m_Square.pos.y , m_Square.pos.z );

	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2d(m_Square.pos.x / SQ_SIZE_MAX, m_Square.pos.y / SQ_SIZE_MAX);
	glColor4f( m_Color.x, m_Color.y, m_Color.z, m_Color.w );	//色(RGBA)
	glVertex3f( m_Square.pos.x , -m_Square.pos.y , m_Square.pos.z );

	glEnd();

//上の面
	glBegin(GL_TRIANGLE_STRIP);

	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2d(0.0f, 0.0f);
	glColor4f( m_Color.x, m_Color.y, m_Color.z, m_Color.w );	//色(RGBA)
	glVertex3f( -m_Square.pos.x , m_Square.pos.y , -m_Square.pos.z );
	

	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2d(m_Square.pos.x / SQ_SIZE_MAX, 0.0f);
	glColor4f( m_Color.x, m_Color.y, m_Color.z, m_Color.w );	//色(RGBA)
	glVertex3f( m_Square.pos.x , m_Square.pos.y , -m_Square.pos.z );

	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2d(0.0f, m_Square.pos.z / SQ_SIZE_MAX);
	glColor4f( m_Color.x, m_Color.y, m_Color.z, m_Color.w );	//色(RGBA)
	glVertex3f(-m_Square.pos.x , m_Square.pos.y , m_Square.pos.z );
	

	glNormal3f(0.0f, 1.0f, 0.01f);
	glTexCoord2d(m_Square.pos.x / SQ_SIZE_MAX, m_Square.pos.z / SQ_SIZE_MAX);
	glColor4f( m_Color.x, m_Color.y, m_Color.z, m_Color.w );	//色(RGBA)
	glVertex3f( m_Square.pos.x , m_Square.pos.y , m_Square.pos.z );
	
	glEnd();

	//奥の面
	glBegin(GL_TRIANGLE_STRIP);

	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2d(0.0f, 0.0f);
	glColor4f( m_Color.x, m_Color.y, m_Color.z, m_Color.w );	//色(RGBA)
	glVertex3f( -m_Square.pos.x , m_Square.pos.y , -m_Square.pos.z );
	
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2d(m_Square.pos.x / SQ_SIZE_MAX, 0.0f);
	glColor4f( m_Color.x, m_Color.y, m_Color.z, m_Color.w );	//色(RGBA)
	glVertex3f( m_Square.pos.x , m_Square.pos.y , -m_Square.pos.z );

	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2d(0.0f, m_Square.pos.y / SQ_SIZE_MAX);
	glColor4f( m_Color.x, m_Color.y, m_Color.z, m_Color.w );	//色(RGBA)
	glVertex3f(-m_Square.pos.x , -m_Square.pos.y , -m_Square.pos.z );

	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2d(m_Square.pos.x / SQ_SIZE_MAX, m_Square.pos.y / SQ_SIZE_MAX);
	glColor4f( m_Color.x, m_Color.y, m_Color.z, m_Color.w );	//色(RGBA)
	glVertex3f( m_Square.pos.x , -m_Square.pos.y , -m_Square.pos.z );

	glEnd();

	//右の面
	glBegin(GL_TRIANGLE_STRIP);

	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2d(0.0f, 0.0f);
	glColor4f( m_Color.x, m_Color.y, m_Color.z, m_Color.w );	//色(RGBA)
	glVertex3f( m_Square.pos.x , m_Square.pos.y , -m_Square.pos.z );

	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2d(m_Square.pos.z / SQ_SIZE_MAX, 0.0f);
	glColor4f( m_Color.x, m_Color.y, m_Color.z, m_Color.w );	//色(RGBA)
	glVertex3f( m_Square.pos.x , m_Square.pos.y , m_Square.pos.z );

	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2d(0.0f, m_Square.pos.y / SQ_SIZE_MAX);
	glColor4f( m_Color.x, m_Color.y, m_Color.z, m_Color.w );	//色(RGBA)
	glVertex3f( m_Square.pos.x , -m_Square.pos.y , -m_Square.pos.z );

	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2d(m_Square.pos.z / SQ_SIZE_MAX, m_Square.pos.y / SQ_SIZE_MAX);
	glColor4f( m_Color.x, m_Color.y, m_Color.z, m_Color.w );	//色(RGBA)
	glVertex3f( m_Square.pos.x , -m_Square.pos.y , m_Square.pos.z );

	glEnd();

	//左の面
	glBegin(GL_TRIANGLE_STRIP);

	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2d(0.0f , 0.0f);
	glColor4f( m_Color.x, m_Color.y, m_Color.z, m_Color.w );	//色(RGBA)
	glVertex3f( -m_Square.pos.x , m_Square.pos.y , -m_Square.pos.z );

	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2d(m_Square.pos.z / SQ_SIZE_MAX, 0.0f);
	glColor4f( m_Color.x, m_Color.y, m_Color.z, m_Color.w );	//色(RGBA)
	glVertex3f( -m_Square.pos.x , m_Square.pos.y , m_Square.pos.z );

	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2d(0.0f, m_Square.pos.y / SQ_SIZE_MAX);
	glColor4f( m_Color.x, m_Color.y, m_Color.z, m_Color.w );	//色(RGBA)
	glVertex3f( -m_Square.pos.x , -m_Square.pos.y , -m_Square.pos.z );

	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2d(m_Square.pos.z / SQ_SIZE_MAX, m_Square.pos.y / SQ_SIZE_MAX);
	glColor4f( m_Color.x, m_Color.y, m_Color.z, m_Color.w );	//色(RGBA)
	glVertex3f( -m_Square.pos.x , -m_Square.pos.y , m_Square.pos.z );

	glEnd();

	glEnable(GL_CULL_FACE);

	glEnable(GL_LIGHTING);

	glDisable(GL_DEPTH_TEST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	//モデルビューマトリックス
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();					//もどす
	
}



/********************************************
------------------終了処理-------------------
*********************************************/
void CSquare::Uninit(bool isLast )
{

}


CSquare *CSquare::Create(VECTOR3 pos , VECTOR3 size , char* TexName, VECTOR4 color)
{
	CSquare *square;		//インスタンス

	//インスタンス作成
	square = new CSquare();

	//初期化作成	//位置、大きさ、色
	square -> Init(pos, size, TexName, color);

	//インスタンスをreturn
	return square;
}