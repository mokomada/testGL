//=============================================================================
//
//	タイトル	スカイボックス
//	ファイル名	skybox.cpp
//	作成者		AT13A284_02 秋田京
//	作成日		2016/11/14
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
#include "skybox.h"


/********************************************
---------------コンストラクタ----------------
*********************************************/
CSkybox::CSkybox(int priority , OBJTYPE objType) : CScene3DGL( priority , objType )
{
}


/********************************************
----------------デストラクタ-----------------
*********************************************/
CSkybox::~CSkybox()
{

}


/********************************************
-----------------初期化処理------------------
********************************************/
void CSkybox::Init(void)
{
	CRendererGL	*renderer	= CManager::GetRendererGL();


	//初期位置
	m_pos.x = 0.0f;
	m_pos.y = 0.0f;
	m_pos.z = 0.0f;

	//初期角度
	m_rot = 0.0f;
	
	m_Texture = renderer->CreateTextureTGA("./data/TEXTURE/skybox001.png");


}

/********************************************
------------------更新処理-------------------
********************************************/
void CSkybox::Update(void)
{

}

/********************************************
------------------描画処理-------------------
*******************************************/
void CSkybox::Draw(void)
{

	//プロジェクションマトリックス
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();					//保存
	
	glEnable(GL_LIGHT0);

	glDisable(GL_CULL_FACE);

	//ワールドマトリックス設定

	glTranslatef(m_pos.x , m_pos.y ,m_pos.z);
	glRotated(m_rot, 0.0, 0.0, 0.0);
	glScalef(1.0f , 1.0f , 1.0f);



	//ポリゴン描画
	glBindTexture(GL_TEXTURE_2D , m_Texture);
	glEnable(GL_TEXTURE_2D);

	//下の面
	glBegin(GL_TRIANGLE_STRIP);

	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2d(0.25f , 0.75f);
	glColor4f( 1.0f, 0.0f, 0.0f, 1.0f );	//色(RGBA)
	glVertex3f( -50000.0f , -50000.0f , -50000.0f );

	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2d(0.5f , 0.75f);
	glColor4f( 1.0f, 0.0f, 0.0f, 1.0f );
	glVertex3f( 50000.0f , -50000.0f , -50000.0f );

	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2d(0.25f , 1.0f);
	glColor4f( 1.0f, 0.0f, 0.0f, 1.0f );
	glVertex3f(-50000.0f , -50000.0f , 50000.0f );

	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2d(0.5f , 1.0f);
	glColor4f( 1.0f, 0.0f, 0.0f, 1.0f );
	glVertex3f( 50000.0f , -50000.0f , 50000.0f );

	glEnd();

	

	//手前の面
	glBegin(GL_TRIANGLE_STRIP);

	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2d(1.0f , 1.0 / 3.0f +  0.001);
	glColor4f( 1.0f, 0.0f, 0.0f, 1.0f );	//色(RGBA)
	glVertex3f( -50000.0f , 50000.0f , 50000.0f );

	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2d(0.75f , 1.0 / 3.0f + 0.001);
	glColor4f( 1.0f, 0.0f, 0.0f, 1.0f );
	glVertex3f( 50000.0f , 50000.0f , 50000.0f );

	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2d(1.0f , 2.0 / 3.0f -  0.001);
	glColor4f( 1.0f, 0.0f, 0.0f, 1.0f );
	glVertex3f(-50000.0f , -50000.0f , 50000.0f );

	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2d(0.75f , 2.0 / 3.0f - 0.001);
	glColor4f( 1.0f, 0.0f, 0.0f, 1.0f );
	glVertex3f( 50000.0f , -50000.0f , 50000.0f );

	glEnd();

//上の面
	glBegin(GL_TRIANGLE_STRIP);

	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2d(0.25f , 1.0 / 3.0f);
	glColor4f( 1.0f, 0.0f, 0.0f, 1.0f );	//色(RGBA)
	glVertex3f( -50000.0f , 50000.0f , -50000.0f );
	

	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2d(0.5f , 1.0 / 3.0f);
	glColor4f( 1.0f, 0.0f, 0.0f, 1.0f );
	glVertex3f( 50000.0f , 50000.0f , -50000.0f );

	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2d(0.25f , 0.0f);
	glColor4f( 1.0f, 0.0f, 0.0f, 1.0f );
	glVertex3f(-50000.0f , 50000.0f , 50000.0f );
	

	glNormal3f(0.0f, 1.0f, 0.01f);
	glTexCoord2d(0.50f , 0.0f);
	glColor4f( 1.0f, 0.0f, 0.0f, 1.0f );
	glVertex3f( 50000.0f , 50000.0f , 50000.0f );
	
	glEnd();

	//奥の面
	glBegin(GL_TRIANGLE_STRIP);

	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2d(0.25f , 1.0 / 3.0f -  0.001);
	glColor4f( 1.0f, 0.0f, 0.0f, 1.0f );	//色(RGBA)
	glVertex3f( -50000.0f , 50000.0f , -50000.0f );
	
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2d(0.50f , 1.0 / 3.0f -  0.001);
	glColor4f( 1.0f, 0.0f, 0.0f, 1.0f );
	glVertex3f( 50000.0f , 50000.0f , -50000.0f );

	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2d(0.25f , 2.0 / 3.0f +  0.001);
	glColor4f( 1.0f, 0.0f, 0.0f, 1.0f );
	glVertex3f(-50000.0f , -50000.0f , -50000.0f );

	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2d(0.5f , 2.0 / 3.0f -  0.001);
	glColor4f( 1.0f, 0.0f, 0.0f, 1.0f );
	glVertex3f( 50000.0f , -50000.0f , -50000.0f );

	glEnd();

	//右の面
	glBegin(GL_TRIANGLE_STRIP);

	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2d(0.5f , 1.0 / 3.0f +  0.001);
	glColor4f( 1.0f, 0.0f, 0.0f, 1.0f );	//色(RGBA)
	glVertex3f( 50000.0f , 50000.0f , -50000.0f );

	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2d(0.75f , 1.0 / 3.0f + 0.001);
	glColor4f( 1.0f, 0.0f, 0.0f, 1.0f );
	glVertex3f( 50000.0f , 50000.0f , 50000.0f );

	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2d(0.5f , 2.0 / 3.0f -  0.001);
	glColor4f( 1.0f, 0.0f, 0.0f, 1.0f );
	glVertex3f( 50000.0f , -50000.0f , -50000.0f );

	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2d(0.75f , 2.0 / 3.0f -  0.001);
	glColor4f( 1.0f, 0.0f, 0.0f, 1.0f );
	glVertex3f( 50000.0f , -50000.0f , 50000.0f );

	glEnd();

	//左の面
	glBegin(GL_TRIANGLE_STRIP);

	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2d(0.25f , 1.0 / 3.0f + 0.001);
	glColor4f( 1.0f, 0.0f, 0.0f, 1.0f );	//色(RGBA)
	glVertex3f( -50000.0f , 50000.0f , -50000.0f );

	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2d(0.0f , 1.0 / 3.0f + 0.001);
	glColor4f( 1.0f, 0.0f, 0.0f, 1.0f );
	glVertex3f( -50000.0f , 50000.0f , 50000.0f );

	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2d(0.25f , 2.0 / 3.0f - 0.001);
	glColor4f( 1.0f, 0.0f, 0.0f, 1.0f );
	glVertex3f( -50000.0f , -50000.0f , -50000.0f );

	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2d(0.00f , 2.0 / 3.0f - 0.001 );
	glColor4f( 1.0f, 0.0f, 0.0f, 1.0f );
	glVertex3f( -50000.0f , -50000.0f , 50000.0f );

	glEnd();

	glEnable(GL_CULL_FACE);

	glDisable(GL_LIGHT0);

	//モデルビューマトリックス
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();					//もどす
	
}


/********************************************
------------------終了処理-------------------
*********************************************/
void CSkybox::Uninit(bool isLast )	
{

}

CSkybox *CSkybox::Create(void)
{
	CSkybox *skybox;		//インスタンス

	//インスタンス作成
	skybox = new CSkybox();

	//初期化作成
	skybox -> Init();

	//インスタンスをreturn
	return skybox;
}