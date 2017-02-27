//=============================================================================
//
//	タイトル	タイトル処理
//	ファイル名	title.cpp
//	作成者		AT13A284_07 池田達哉
//	作成日		2016/07/12
//
//=============================================================================
//=============================================================================
//	インクルード
//=============================================================================
#include "title.h"
#include "manager.h"
#include "rendererGL.h"

#include "input.h"
#include "fade.h"
#include "scene2DGL.h"
#include "scene2DGLAnimation.h"

//=============================================================================
//	静的メンバ変数
//=============================================================================

//=============================================================================
//	関数名	:Init
//	引数	:無し
//	戻り値	:無し
//	説明	:初期化処理を行う。
//=============================================================================
void CTitle::Init(void)
{
		
	CRendererGL	*renderer	= CManager::GetRendererGL();

	m_TitleBG = CScene2DGL::Create(VECTOR3(SCREEN_WIDTH_HALF, SCREEN_HEIGHT_HALF, 0.0f),
		VECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT) , 
		".\\data\\TEXTURE\\titleback.png");
	
	m_Title = CScene2DGLAnimation::Create(VECTOR3(SCREEN_WIDTH_HALF, SCREEN_HEIGHT * 2.2f, 0.0f),
		VECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT), 1, 1 , 1 , 1 ,
		".\\data\\TEXTURE\\title000.png");
	
	m_Title -> SetStartAnimation( false );

	m_Title -> SetMove( CSceneMove::Create( m_Title -> GetPositionP( ) , m_Title -> GetRotationP( ) , VECTOR3( 0.0f , -10.0f , 0.0f ) , VECTOR3( 0.0f , 0.0f , 0.0f ) , 115 , MOVETYPE_STRAIGHT ) );
			
	m_PushEnter = CScene2DGLAnimation::Create(VECTOR3(SCREEN_WIDTH_HALF, ( SCREEN_HEIGHT * 0.8f), 0.0f),
		VECTOR2((SCREEN_WIDTH * 0.5f), (SCREEN_HEIGHT * 0.6f)) , 2 , 2 , 3 , 4, 
		".\\data\\TEXTURE\\pushbutton01.png");

	//移動補助の追加
	m_PushEnter -> SetMove( CSceneMove::Create( m_PushEnter -> GetPositionP( ) , m_PushEnter -> GetRotationP( ) , VECTOR3( 0.0f , 0.1f , 0.0f ) , VECTOR3( 0.0f , 0.0f , 0.0f ) , 60 , MOVETYPE_LOOP ) );

	m_PushEnter -> SetStartAnimation( false );

	m_BalloonTexture[ 0 ] = renderer->CreateTextureTGA(".\\data\\TEXTURE\\balloon000.png");
	m_BalloonTexture[ 1 ] = renderer->CreateTextureTGA(".\\data\\TEXTURE\\balloon001.png");
	m_BalloonTexture[ 2 ] = renderer->CreateTextureTGA(".\\data\\TEXTURE\\balloon002.png");
	m_BalloonTexture[ 3 ] = renderer->CreateTextureTGA(".\\data\\TEXTURE\\balloon003.png");

	for( int nCntDepth = 0 ; nCntDepth < 1 ; nCntDepth++ )
	{
		for( int nCntBalloon = 0 ; nCntBalloon < TITLE_BALLOON ; nCntBalloon++ )
		{
			for( int nCntLen = 0 ; nCntLen < TITLE_BALLOON_LEN ; nCntLen++ )
			{
				int texnumber = rand( ) % TITLE_BALLOON_COLOR;

				m_Balloon = CScene2DGLAnimation::Create(VECTOR3( ( nCntBalloon * 100.0f ) + ( nCntDepth * SCREEN_WIDTH * 0.2f ), ( SCREEN_HEIGHT * 2.0f) + nCntLen * ( SCREEN_HEIGHT * 0.1f ), 0.0f),
				VECTOR2((SCREEN_WIDTH * 0.2f), (SCREEN_HEIGHT * 0.2f)) , 1 , 1 , 1 , 1, 
				".\\data\\TEXTURE\\balloon002.png" , m_BalloonTexture[ texnumber ] );

				m_Balloon -> SetStartAnimation( false );

				m_Balloon -> SetMove( CSceneMove::Create( m_Balloon -> GetPositionP( ) , m_Balloon -> GetRotationP( ) , VECTOR3( 0.0f , -10.0f , 0.0f ) , VECTOR3( 0.0f , 0.0f , 0.0f ) , 300 , MOVETYPE_STRAIGHT ) );
			}
		}
	}
	m_Alpha = 0.0f;
}

//=============================================================================
//	関数名	:Uninit
//	引数	:無し
//	戻り値	:無し
//	説明	:終了処理を行う。
//=============================================================================
void CTitle::Uninit(void)
{
	CSceneGL::DeleteAll();
}

//=============================================================================
//	関数名	:Update
//	引数	:無し
//	戻り値	:無し
//	説明	:更新処理を行う。
//=============================================================================
void CTitle::Update(void)
{
	// シーン更新
	CSceneGL::UpdateAll();
	if(( KT_ENTER || KT_SPACE || KT_X || KT_J || KT_L ) && CFade::m_FadeState == FS_NONE )
	{
		CFade::Start(new CTutorial, MODE_TUTORIAL, FS_OUT);
		m_PushEnter -> SetStartAnimation( true );
	}
}
   
//=============================================================================
//	関数名	:Draw
//	引数	:無し
//	戻り値	:無し
//	説明	:描画処理を行う。bcb
//=============================================================================
void CTitle::Draw(void)
{
	m_Alpha += 0.05f;
	//m_PushEnter->SetColor((cosf(m_Alpha) * 0.5f + 0.5f), 1.0f, 1.0f, 1.0f);

	// シーン描画
	CSceneGL::DrawAll();
}