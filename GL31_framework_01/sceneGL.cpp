//=============================================================================
//
//	�^�C�g��	�V�[���t�@�C��
//	�t�@�C����	scene.cpp
//	�쐬��		AT13A284_07 �r�c�B��
//	�쐬��		2016/04/19
//
//=============================================================================
//=============================================================================
//	�C���N���[�h
//=============================================================================
#include "sceneGL.h"
#include "main.h"
#include "rendererGL.h"
#include "scene2DGL.h"

//=============================================================================
//	�ÓI�����o�ϐ�
//=============================================================================
CSceneGL *CSceneGL::m_pTop;
CSceneGL *CSceneGL::m_pCur;

//=============================================================================
//	�֐���	:CSceneGL()
//	����	:����
//	�߂�l	:����
//	����	:�R���X�g���N�^�B
//=============================================================================
CSceneGL::CSceneGL(int priority, OBJTYPE objType)
{
	// �I�u�W�F�N�g�^�C�v�E�v���C�I���e�B�Z�b�g
	m_ObjType	= objType;
	m_Priority	= priority;

	if(m_pTop == NULL)
	{// ���X�g�ɉ����o�^����ĂȂ��ꍇ

		// ���g�̃|�C���^�����X�g�擪�ɓo�^
		m_pTop = this;

		// �擪�֓o�^
		m_pPrev = NULL;
	}
	else
	{// ���X�g�ɑ��ɒǉ�����Ă���ꍇ

		// �O���ڂ��Q�Ɛ��
		m_pPrev = m_pCur;

		// �O���ڂ̎��Q�Ɛ�����g��
		m_pPrev->m_pNext = this;
	}
		
	// ���X�g�̏I�[�|�C���^�Ɏ��g��o�^
	m_pCur = this;

	// ���̍��ڂ͖���
	m_pNext = NULL;

	// ���W�E��]�̏�����
	SetPos(VECTOR3(0.0f, 0.0f, 0.0f));
	SetRot(VECTOR3(0.0f, 0.0f, 0.0f));
}

//=============================================================================
//	�֐���	:~CSceneGL()
//	����	:����
//	�߂�l	:����
//	����	:�f�X�g���N�^�B
//=============================================================================
CSceneGL::~CSceneGL()
{
	CSceneGL *pScene = m_pTop;		// �Q�Ɛ�o�b�t�@
	CSceneGL *pSceneNext = NULL;	// ���Q�Ɛ�o�b�t�@
	CSceneGL *pScenePrev = NULL;	// �O�Q�Ɛ�o�b�t�@

	// �S�ẴV�[�����Q��
	while(pScene)
	{
		// ���Q�Ɛ�ƑO�Q�Ɛ��ޔ�
		pSceneNext = pScene->m_pNext;
		pScenePrev = pScene->m_pPrev;

		if(pScene == this)
		{
			// �O�Q�Ɛ悪���݂���ꍇ
			if(pScene->m_pPrev)
			{
				// �O�Q�Ɛ���X�V
				pScene->m_pPrev->m_pNext = pScene->m_pNext;
			}

			// ���Q�Ɛ悪���݂���ꍇ
			if(pScene->m_pNext)
			{
				// ���Q�Ɛ���X�V
				pScene->m_pNext->m_pPrev = pScene->m_pPrev;
			}

			// ���X�g�̐擪�̏ꍇ
			if(pScene == m_pTop)
			{
				// ���X�g�̐擪���X�V
				m_pTop = pSceneNext;
			}

			// ���X�g�̏I�[�̏ꍇ
			if(pScene == m_pCur)
			{
				// ���X�g�̏I�[���X�V
				m_pCur = pScenePrev;
			}
		}

		// ���Q�Ɛ���Z�b�g
		pScene = pSceneNext;
	}
}

//=============================================================================
//	�֐���	:UpdateAll
//	����	:����
//	�߂�l	:����
//	����	:���X�g�ɒǉ�����Ă���S�Ă̑Ώۂ��X�V����B
//=============================================================================
void CSceneGL::UpdateAll(void)
{
	CSceneGL *scene = m_pTop;	// ���X�g�̐擪�|�C���^
	CSceneGL *sceneNext;		// ���X�g�̎��Q�Ɛ�o�b�t�@

	// ���X�g�̍Ō�ɓ��B����܂ōX�V�𑱂���
	while(scene != NULL)
	{
		// ���Q�Ɛ���X�V
		sceneNext = scene->m_pNext;

		// �V�[�����X�V
		scene->Update();

		// ���̍��ڂ�
		scene = sceneNext;
	}
}

//=============================================================================
//	�֐���	:DrawAll
//	����	:����
//	�߂�l	:����
//	����	:���X�g�ɒǉ�����Ă���S�Ă̑Ώۂ�`�悷��B
//=============================================================================
void CSceneGL::DrawAll(void)
{
	CSceneGL *scene = m_pTop;	// ���X�g�̐擪�|�C���^
	
	// ���X�g�̍Ō�ɓ��B����܂ŕ`��𑱂���
	while(scene != NULL)
	{
		// �V�[����`��
		scene->Draw();

		// ���̍��ڂ�
		scene = scene->m_pNext;
	}
}

//=============================================================================
//	�֐���	:DeleteAll
//	����	:����
//	�߂�l	:����
//	����	:���X�g�ɒǉ�����Ă���S�Ă̑Ώۂ��폜����B
//=============================================================================
void CSceneGL::DeleteAll(bool isLast)
{
	CSceneGL *pScene = m_pTop;	// ���X�g�̐擪�|�C���^
	CSceneGL *pSceneNext;		// ���Q�Ɛ�
	
	while(pScene != NULL)
	{
		// ���Q�Ɛ��ޔ�
		pSceneNext = pScene->m_pNext;

		// �I������
		pScene->Uninit(isLast);

		// �C���X�^���X�폜
		if(pScene != NULL)
		{
			delete pScene;
		}

		// ���Q�Ɛ���Z�b�g
		pScene = pSceneNext;
	}
}

//=============================================================================
//	�֐���	:Release
//	����	:����
//	�߂�l	:����
//	����	:�Ώۂ��폜����B
//=============================================================================
void CSceneGL::Release(void)
{
	// �I������
	Uninit();

	if(this == m_pTop)
	{// ���X�g�̐擪�̏ꍇ

		// ���X�g�̐擪�����݂̎����ڂ�
		m_pTop = m_pNext;
	}
	else
	{// ���X�g�̐擪�łȂ��ꍇ

		// �O���ڂ̎��Q�Ɛ�����݂̎��Q�Ɛ��
		m_pPrev->m_pNext = m_pNext;
	}

	if(this == m_pCur)
	{// ���X�g�̏I�[�̏ꍇ

		// ���X�g�̏I�[�����݂̑O���ڂ�
		m_pCur = m_pPrev;
	}
	else
	{// ���X�g�̏I�[�łȂ��ꍇ

		// �����ڂ̑O�Q�Ɛ�����݂̑O�Q�Ɛ��
		m_pNext->m_pPrev = m_pPrev;
	}

	// �C���X�^���X�폜
	delete this;
}