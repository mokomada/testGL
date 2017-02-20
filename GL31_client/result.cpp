//=============================================================================
//
//	�^�C�g��	�^�C�g������
//	�t�@�C����	result.cpp
//	�쐬��		AT13A284_07 �r�c�B��
//	�쐬��		2016/07/12
//
//=============================================================================
//=============================================================================
//	�C���N���[�h
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
//	�֐���	:Init
//	����	:����
//	�߂�l	:����
//	����	:�������������s���B
//=============================================================================
void CResult::Init(void)
{
	CCameraGL	*camera = CManager::GetCamera();	// �J����

	camera->m_CameraState.posV = VECTOR3(20.0f, 90.0f, 0.0f);
	camera->m_CameraState.posR = VECTOR3(20.0f, 70.0f, 0.0f);
	
	CTextureManager::Init();
	int A[4] = { 3 , 2 , 1 , 0};	//4��,3��,2��,1��

	CMeshfield::Create(VECTOR3(0.0f, 0.0f, 0.0f));
	m_Model[0] = CSceneModel::Create("./data/MODEL/car1.obj" , VEC3_ZERO);
	m_Model[1] = CSceneModel::Create("./data/MODEL/car2.obj" , VEC3_ZERO);
	m_Model[2] = CSceneModel::Create("./data/MODEL/car3.obj" , VEC3_ZERO);
	m_Model[3] = CSceneModel::Create("./data/MODEL/car4.obj" , VEC3_ZERO);

	m_Model[ A[0] ] ->SetPos(VECTOR3(0.0f , 100.0f , 0.0f));	//���
	m_Model[ A[1] ] ->SetPos(VECTOR3(75.0f , 70.0f , 0.0f));	//���
	m_Model[ A[2] ] ->SetPos(VECTOR3(-75.0f ,50.0f , 0.0f));	//�O��
	m_Model[ A[3] ] ->SetPos(VECTOR3(-300.0f , 0.0f , -400.0f));	//�l��

		// �p�[�e�B�N���I�u�W�F�N�g����
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
	--------------�\����------------------
	*************************************/
	CPodium::Create(VECTOR3(0.0f, 37.5f, 0.0f) , VECTOR3(75.0f ,75.0f ,75.0f) ,"", VECTOR4(1.0f ,1.0f ,0.0f, 1.0f));		//1��
	CPodium::Create(VECTOR3(76.0f, 20.0f, 0.0f) , VECTOR3(75.0f ,40.0f ,75.0f) ,"", VECTOR4(0.0f ,1.0f ,1.0f, 1.0f));		//2��
	CPodium::Create(VECTOR3(-76.0f, 12.5f, 0.0f) , VECTOR3(75.0f ,25.0f ,75.0f) ,"", VECTOR4(0.0f ,0.0f ,1.0f, 1.0f));		//3��
	//---------------------------
	m_Alpha = 0.0f;
}

//=============================================================================
//	�֐���	:Uninit
//	����	:����
//	�߂�l	:����
//	����	:�I���������s���B
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
//	�֐���	:Update
//	����	:����
//	�߂�l	:����
//	����	:�X�V�������s���B
//=============================================================================
void CResult::Update(void)
{	
	CCameraGL	*camera = CManager::GetCamera();	// �J����

	camera->m_CameraState.posV = VECTOR3(0.0f, 90.0f, 450.0f);
	camera->m_CameraState.posR = VECTOR3(0.0f, 70.0f, 0.0f);
	
	m_Particle->Update();
	// �V�[���X�V
	CSceneGL::UpdateAll();
	if(KT_ENTER)
	{
		CFade::Start(new CTitle, MODE_TITLE, FS_OUT);
	}
}

//=============================================================================
//	�֐���	:Draw
//	����	:����
//	�߂�l	:����
//	����	:�`�揈�����s���B
//=============================================================================
void CResult::Draw(void)
{
	m_Alpha += 0.1f;
	//m_PushEnter->SetColor(sinf(m_Alpha), 1.0f, 1.0f, 1.0f);
	for(int i = 0 ; i < 4 ; i++)
	{
		m_Model[i] ->Draw();
	}
	// �V�[���`��
	CSceneGL::DrawAll();
}