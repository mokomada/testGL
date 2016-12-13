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
CSceneGL *CSceneGL::m_pTop[PRIORITY_MAX] = { NULL };
CSceneGL *CSceneGL::m_pCur[PRIORITY_MAX] = { NULL };

//=============================================================================
//	�֐���	:CSceneGL()
//	����	:����
//	�߂�l	:����
//	����	:�R���X�g���N�^�B
//=============================================================================
CSceneGL::CSceneGL(PRIORITY Priority, OBJTYPE objType)
{
	m_Priority = Priority;

	if(m_pTop[Priority] == NULL)
	{// ���X�g�ɉ����o�^����ĂȂ��ꍇ

		// ���g�̃|�C���^�����X�g�擪�ɓo�^
		m_pTop[Priority] = this;

		// �擪�֓o�^
		m_pPrev = NULL;
	}
	else
	{// ���X�g�ɑ��ɒǉ�����Ă���ꍇ

		// �O���ڂ��Q�Ɛ��
		m_pPrev = m_pCur[Priority];

		// �O���ڂ̎��Q�Ɛ�����g��
		m_pPrev->m_pNext = this;
	}
		
	// ���X�g�̏I�[�|�C���^�Ɏ��g��o�^
	m_pCur[Priority] = this;

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
	for (int nCnt = 0; nCnt < PRIORITY_MAX; nCnt++)
	{
		CSceneGL *pScene = m_pTop[nCnt];		// �Q�Ɛ�o�b�t�@
		CSceneGL *pSceneNext = NULL;	// ���Q�Ɛ�o�b�t�@
		CSceneGL *pScenePrev = NULL;	// �O�Q�Ɛ�o�b�t�@

		// �S�ẴV�[�����Q��
		while (pScene)
		{
			// ���Q�Ɛ�ƑO�Q�Ɛ��ޔ�
			pSceneNext = pScene->m_pNext;
			pScenePrev = pScene->m_pPrev;

			if (pScene == this)
			{
				// �O�Q�Ɛ悪���݂���ꍇ
				if (pScene->m_pPrev)
				{
					// �O�Q�Ɛ���X�V
					pScene->m_pPrev->m_pNext = pScene->m_pNext;
				}

				// ���Q�Ɛ悪���݂���ꍇ
				if (pScene->m_pNext)
				{
					// ���Q�Ɛ���X�V
					pScene->m_pNext->m_pPrev = pScene->m_pPrev;
				}

				// ���X�g�̐擪�̏ꍇ
				if (pScene == m_pTop[nCnt])
				{
					// ���X�g�̐擪���X�V
					m_pTop[nCnt] = pSceneNext;
				}

				// ���X�g�̏I�[�̏ꍇ
				if (pScene == m_pCur[nCnt])
				{
					// ���X�g�̏I�[���X�V
					m_pCur[nCnt] = pScenePrev;
				}
			}

			// ���Q�Ɛ���Z�b�g
			pScene = pSceneNext;
		}
	}
}

//=============================================================================
//	�֐���	:Init
//	����	:����
//	�߂�l	:����
//	����	:������
//=============================================================================
void CSceneGL::Init(void)
{
	
}

//=============================================================================
//	�֐���	:UpdateAll
//	����	:����
//	�߂�l	:����
//	����	:���X�g�ɒǉ�����Ă���S�Ă̑Ώۂ��X�V����B
//=============================================================================
void CSceneGL::UpdateAll(void)
{
	for (int nCnt = 0; nCnt < PRIORITY_MAX; nCnt++)
	{
		CSceneGL *scene = m_pTop[nCnt];	// ���X�g�̐擪�|�C���^
		CSceneGL *sceneNext;		// ���X�g�̎��Q�Ɛ�o�b�t�@

		// ���X�g�̍Ō�ɓ��B����܂ōX�V�𑱂���
		while (scene != NULL)
		{
			// ���Q�Ɛ���X�V
			sceneNext = scene->m_pNext;

			// �V�[�����X�V
			scene->Update();

			// ���̍��ڂ�
			scene = sceneNext;
		}
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
	for (int nCnt = 0; nCnt < PRIORITY_MAX; nCnt++)
	{
		CSceneGL *scene = m_pTop[nCnt];	// ���X�g�̐擪�|�C���^

		// ���X�g�̍Ō�ɓ��B����܂ŕ`��𑱂���
		while (scene != NULL)
		{
			// �V�[����`��
			scene->Draw();

			// ���̍��ڂ�
			scene = scene->m_pNext;
		}
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
	for (int nCnt = 0; nCnt < PRIORITY_MAX; nCnt++)
	{
		CSceneGL *pScene = m_pTop[nCnt];	// ���X�g�̐擪�|�C���^
		CSceneGL *pSceneNext;		// ���Q�Ɛ�

		while (pScene != NULL)
		{
			// ���Q�Ɛ��ޔ�
			pSceneNext = pScene->m_pNext;

			// �I������
			pScene->Uninit(isLast);

			// �C���X�^���X�폜
			if (pScene != NULL)
			{
				delete pScene;
			}

			// ���Q�Ɛ���Z�b�g
			pScene = pSceneNext;
		}

		m_pTop[nCnt] = NULL;
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

	if(this == m_pTop[m_Priority])
	{// ���X�g�̐擪�̏ꍇ

		// ���X�g�̐擪�����݂̎����ڂ�
		m_pTop[m_Priority] = m_pNext;
	}
	else
	{// ���X�g�̐擪�łȂ��ꍇ

		// �O���ڂ̎��Q�Ɛ�����݂̎��Q�Ɛ��
		m_pPrev->m_pNext = m_pNext;
	}

	if(this == m_pCur[m_Priority])
	{// ���X�g�̏I�[�̏ꍇ

		// ���X�g�̏I�[�����݂̑O���ڂ�
		m_pCur[m_Priority] = m_pPrev;
	}
	else
	{// ���X�g�̏I�[�łȂ��ꍇ

		// �����ڂ̑O�Q�Ɛ�����݂̑O�Q�Ɛ��
		m_pNext->m_pPrev = m_pPrev;
	}

	// �C���X�^���X�폜
	delete this;
}