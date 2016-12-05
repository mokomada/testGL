/*******************************************************************************
* �^�C�g�� �Q�[����ʊe�폈���Ăяo��
* �t�@�C���� game.cpp
* �쐬�� AT-13A-284 �H�ԗY��
* �쐬�� 2016/07/19
*******************************************************************************/

/*******************************************************************************
* �C���N���[�h�t�@�C��
*******************************************************************************/

#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "mode.h"
#include "fade.h"
#include "game.h"
#include "result.h"
#include "title.h"
#include "scene.h"
#include "scene2D.h"
#include "scene3D.h"
#include "sceneX.h"
#include "camera.h"
#include "light.h"
#include "input.h"
#include "meshfield.h"
#include "debugProc.h"
#include "billboard.h"
#include "meshwater.h"
#include "meshworld.h"
#include "score.h"
#include "player.h"
#include "enemy.h"
#include "sound.h"


/*******************************************************************************
* �X�^�e�B�b�N�ϐ�������
*******************************************************************************/

CCamera *CGame::m_camera = NULL; // �J����
CLight *CGame::m_light = NULL; // ���C�g
CPlayer *CGame::m_player = NULL; // �v���C���[���
CScore *CGame::m_score = NULL; // �X�R�A���
CEnemy *CGame::m_enemy[ENEMY_MAX] = {NULL}; // �G���

/*******************************************************************************
* �֐����FInitGame
* �����F�Ȃ�
* �߂�l�Ftrue or false : �������������������ۂ�
* �����F�Q�[����ʂ̏�����
*******************************************************************************/

void CGame::Init(void) {
	m_camera = new CCamera;
	m_camera -> Init( );

	m_light = new CLight;
	m_light -> Init( );

	CMeshfield::Create( );

	CSceneX::Create( );

	CBillboard::Create( );

	CMeshwater::Create( );

	CMeshworld::Create( );

	m_score = CScore::Create( );

	m_player = CPlayer::Create( );

	m_enemy[0] = CEnemy::Create( );

	m_enemy[1] = CEnemy::Create( );

	m_enemy[2] = CEnemy::Create( );

	InitDebugProc( );

	CSound::StopSound(SOUND_LABEL_BGM001);
	CSound::PlaySound(SOUND_LABEL_BGM000);
}


/*******************************************************************************
* �֐����FUninitGame
* �����F�Ȃ�
* �߂�l�F�Ȃ�
* �����F�Q�[����ʂ̏I������
*******************************************************************************/

void CGame::Uninit(void) {
	if(m_camera != NULL) {
		m_camera -> Uninit( );
		delete m_camera;
		m_camera = NULL;
	}

	if(m_light != NULL) {
		m_light -> Uninit( );
		delete m_light;
		m_light = NULL;
	}

	CScene::UninitAll( );

	UninitDebugProc( );
}


/*******************************************************************************
* �֐����FUpdateGame
* �����F�Ȃ�
* �߂�l�F�Ȃ�
* �����F�Q�[����ʂ̍X�V
*******************************************************************************/

void CGame::Update(void) {
	CInput *input;
	input = CManager::GetInput( );

	CFade *getFade;
	getFade = CManager::GetFade( );
	FADE fade = getFade -> GetFade( );

	m_camera -> Update( );

	if(fade == FADE_NONE) {

		m_light -> Update( );

		CScene::UpdateAll( );

		if(input -> GetKeyboardTrigger(DIK_RETURN) ) {
			CFade::SetFade(FADE_OUT, new CResult);
		}
	}
}


/*******************************************************************************
* �֐����FDrawGame
* �����F�Ȃ�
* �߂�l�F�Ȃ�
* �����F�Q�[����ʂ̕`��
*******************************************************************************/

void CGame::Draw(void) {
	m_camera -> SetCamera( );

	CScene::DrawAll( );

	DrawDebugProc( );
}

/*******************************************************************************
* �֐����FGetCamera
* �����F�Ȃ�
* �߂�l�Fm_camera
* �����Fm_camera�̃A�h���X��Ԃ�
*******************************************************************************/

CCamera *CGame::GetCamera(void) {
	return m_camera;
}


/*******************************************************************************
* �֐����FGetPlayer
* �����F�Ȃ�
* �߂�l�Fm_player
* �����Fm_player�̃A�h���X��Ԃ�
*******************************************************************************/

CPlayer *CGame::GetPlayer(void) {
	return m_player;
}


/*******************************************************************************
* �֐����FGetEnemy
* �����F�Ȃ�
* �߂�l�Fm_enemy
* �����Fm_enemy�̃A�h���X��Ԃ�
*******************************************************************************/

CEnemy *CGame::GetEnemy(void) {
	return m_enemy[0];
}
