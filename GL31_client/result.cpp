//=============================================================================
//
//	タイトル	タイトル処理
//	ファイル名	result.cpp
//	作成者		AT13A284_07 池田達哉
//	作成日		2016/07/12
//
//=============================================================================
//=============================================================================
//	インクルード
//=============================================================================
#include "result.h"
#include "manager.h"
#include "input.h"
#include "fade.h"
#include "cameraGL.h"
#include "scene2DGL.h"
#include "scene3DGL.h"
#include "particle.h"
#include "sceneModel.h"
#include "player.h"
#include "square.h"
#include "podium.h"
#include "meshfield.h"
#include "effect2D.h"
#include "particle.h"
#include "textureManager.h"
//=============================================================================
//	関数名	:Init
//	引数	:無し
//	戻り値	:無し
//	説明	:初期化処理を行う。
//=============================================================================
void CResult::Init(void)
{
	CCameraGL	*camera = CManager::GetCamera();	// カメラ

	camera->m_CameraState.posV = VECTOR3(20.0f, 90.0f, 0.0f);
	camera->m_CameraState.posR = VECTOR3(20.0f, 70.0f, 0.0f);
	
	CTextureManager::Init();
	int A[4] = { 3 , 2 , 1 , 0};	//4位,3位,2位,1位

	CMeshfield::Create(VECTOR3(0.0f, 0.0f, 0.0f));
	m_Model[0] = CSceneModel::Create("./data/MODEL/car1.obj" , VEC3_ZERO);
	m_Model[1] = CSceneModel::Create("./data/MODEL/car2.obj" , VEC3_ZERO);
	m_Model[2] = CSceneModel::Create("./data/MODEL/car3.obj" , VEC3_ZERO);
	m_Model[3] = CSceneModel::Create("./data/MODEL/car4.obj" , VEC3_ZERO);

	m_Model[ A[0] ] ->SetPos(VECTOR3(0.0f , 100.0f , 0.0f));	//一位
	m_Model[ A[1] ] ->SetPos(VECTOR3(75.0f , 70.0f , 0.0f));	//二位
	m_Model[ A[2] ] ->SetPos(VECTOR3(-75.0f ,50.0f , 0.0f));	//三位
	m_Model[ A[3] ] ->SetPos(VECTOR3(-300.0f , 0.0f , -400.0f));	//四位

		// パーティクルオブジェクト生成
	m_Particle = CParticle::Create(VECTOR3(150.0f , 0.0f , -100.0f), VECTOR2(80.0f,80.0f), PARTICLE_DEADSMOKE, m_Model[0]);

	m_Model[A[3]] ->SetRot(VECTOR3(1.3f ,0.0f,0.0f));
	//CEffect2D::Create(m_Model[A[3]] ->GetPos() , VECTOR2(500.0f -  m_Model[A[3]] ->GetPos().y , 500.0f -  m_Model[A[3]] ->GetPos().y) , ETYPE_EXPLODE01);
	/*m_ResultBG = CScene2DGL::Create(VECTOR3(SCREEN_WIDTH_HALF, SCREEN_HEIGHT_HALF, 0.0f),
		VECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT),
		".\\data\\TEXTURE\\result000.tga");*/
	m_PushEnter = CScene2DGL::Create(VECTOR3(SCREEN_WIDTH_HALF, (SCREEN_HEIGHT * 0.8f), 0.0f),
		VECTOR2((SCREEN_WIDTH * 0.4f), (SCREEN_HEIGHT * 0.05f)),
		".\\data\\TEXTURE\\pushbutton000.tga");
		


	/*************************************
	--------------表彰台------------------
	*************************************/
	CPodium::Create(VECTOR3(0.0f, 37.5f, 0.0f) , VECTOR3(75.0f ,75.0f ,75.0f) ,"", VECTOR4(1.0f ,1.0f ,0.0f, 1.0f));		//1位
	CPodium::Create(VECTOR3(76.0f, 20.0f, 0.0f) , VECTOR3(75.0f ,40.0f ,75.0f) ,"", VECTOR4(0.0f ,1.0f ,1.0f, 1.0f));		//2位
	CPodium::Create(VECTOR3(-76.0f, 12.5f, 0.0f) , VECTOR3(75.0f ,25.0f ,75.0f) ,"", VECTOR4(0.0f ,0.0f ,1.0f, 1.0f));		//3位
	//---------------------------
	m_Alpha = 0.0f;
}

//=============================================================================
//	関数名	:Uninit
//	引数	:無し
//	戻り値	:無し
//	説明	:終了処理を行う。
//=============================================================================
void CResult::Uninit(void)
{
	CTextureManager::Uninit();
	CSceneGL::DeleteAll();
	if(m_Particle != NULL) {
		m_Particle->Uninit();
		m_Particle = NULL;
	}
}

//=============================================================================
//	関数名	:Update
//	引数	:無し
//	戻り値	:無し
//	説明	:更新処理を行う。
//=============================================================================
void CResult::Update(void)
{	
	CCameraGL	*camera = CManager::GetCamera();	// カメラ

	camera->m_CameraState.posV = VECTOR3(0.0f, 90.0f, 450.0f);
	camera->m_CameraState.posR = VECTOR3(0.0f, 70.0f, 0.0f);
	
	m_Particle->Update();
	// シーン更新
	CSceneGL::UpdateAll();
	if(KT_ENTER)
	{
		CFade::Start(new CTitle, MODE_TITLE, FS_OUT);
	}
}

//=============================================================================
//	関数名	:Draw
//	引数	:無し
//	戻り値	:無し
//	説明	:描画処理を行う。
//=============================================================================
void CResult::Draw(void)
{
	m_Alpha += 0.1f;
	//m_PushEnter->SetColor(sinf(m_Alpha), 1.0f, 1.0f, 1.0f);
	for(int i = 0 ; i < 4 ; i++)
	{
		m_Model[i] ->Draw();
	}
	// シーン描画
	CSceneGL::DrawAll();
}