//=============================================================================
//
//	タイトル	シーンファイル
//	ファイル名	scene.cpp
//	作成者		AT13A284_07 池田達哉
//	作成日		2016/04/19
//
//=============================================================================
//=============================================================================
//	インクルード
//=============================================================================
#include "sceneGL.h"
#include "main.h"
#include "rendererGL.h"
#include "scene2DGL.h"

//=============================================================================
//	静的メンバ変数
//=============================================================================
CSceneGL *CSceneGL::m_pTop[PRIORITY_MAX] = { NULL };
CSceneGL *CSceneGL::m_pCur[PRIORITY_MAX] = { NULL };

//=============================================================================
//	関数名	:CSceneGL()
//	引数	:無し
//	戻り値	:無し
//	説明	:コンストラクタ。
//=============================================================================
CSceneGL::CSceneGL(PRIORITY Priority, OBJTYPE objType)
{
	m_Priority = Priority;

	if(m_pTop[Priority] == NULL)
	{// リストに何も登録されてない場合

		// 自身のポインタをリスト先頭に登録
		m_pTop[Priority] = this;

		// 先頭へ登録
		m_pPrev = NULL;
	}
	else
	{// リストに他に追加されている場合

		// 前項目を参照先に
		m_pPrev = m_pCur[Priority];

		// 前項目の次参照先を自身に
		m_pPrev->m_pNext = this;
	}
		
	// リストの終端ポインタに自身を登録
	m_pCur[Priority] = this;

	// 次の項目は無い
	m_pNext = NULL;

	// 座標・回転の初期化
	SetPos(VECTOR3(0.0f, 0.0f, 0.0f));
	SetRot(VECTOR3(0.0f, 0.0f, 0.0f));
}

//=============================================================================
//	関数名	:~CSceneGL()
//	引数	:無し
//	戻り値	:無し
//	説明	:デストラクタ。
//=============================================================================
CSceneGL::~CSceneGL()
{
	for (int nCnt = 0; nCnt < PRIORITY_MAX; nCnt++)
	{
		CSceneGL *pScene = m_pTop[nCnt];		// 参照先バッファ
		CSceneGL *pSceneNext = NULL;	// 次参照先バッファ
		CSceneGL *pScenePrev = NULL;	// 前参照先バッファ

		// 全てのシーンを参照
		while (pScene)
		{
			// 次参照先と前参照先を退避
			pSceneNext = pScene->m_pNext;
			pScenePrev = pScene->m_pPrev;

			if (pScene == this)
			{
				// 前参照先が存在する場合
				if (pScene->m_pPrev)
				{
					// 前参照先を更新
					pScene->m_pPrev->m_pNext = pScene->m_pNext;
				}

				// 次参照先が存在する場合
				if (pScene->m_pNext)
				{
					// 次参照先を更新
					pScene->m_pNext->m_pPrev = pScene->m_pPrev;
				}

				// リストの先頭の場合
				if (pScene == m_pTop[nCnt])
				{
					// リストの先頭を更新
					m_pTop[nCnt] = pSceneNext;
				}

				// リストの終端の場合
				if (pScene == m_pCur[nCnt])
				{
					// リストの終端を更新
					m_pCur[nCnt] = pScenePrev;
				}
			}

			// 次参照先をセット
			pScene = pSceneNext;
		}
	}
}

//=============================================================================
//	関数名	:Init
//	引数	:無し
//	戻り値	:無し
//	説明	:初期化
//=============================================================================
void CSceneGL::Init(void)
{
	
}

//=============================================================================
//	関数名	:UpdateAll
//	引数	:無し
//	戻り値	:無し
//	説明	:リストに追加されている全ての対象を更新する。
//=============================================================================
void CSceneGL::UpdateAll(void)
{
	for (int nCnt = 0; nCnt < PRIORITY_MAX; nCnt++)
	{
		CSceneGL *scene = m_pTop[nCnt];	// リストの先頭ポインタ
		CSceneGL *sceneNext;		// リストの次参照先バッファ

		// リストの最後に到達するまで更新を続ける
		while (scene != NULL)
		{
			// 次参照先を更新
			sceneNext = scene->m_pNext;

			// シーンを更新
			scene->Update();

			// 次の項目へ
			scene = sceneNext;
		}
	}
}

//=============================================================================
//	関数名	:DrawAll
//	引数	:無し
//	戻り値	:無し
//	説明	:リストに追加されている全ての対象を描画する。
//=============================================================================
void CSceneGL::DrawAll(void)
{
	for (int nCnt = 0; nCnt < PRIORITY_MAX; nCnt++)
	{
		CSceneGL *scene = m_pTop[nCnt];	// リストの先頭ポインタ

		// リストの最後に到達するまで描画を続ける
		while (scene != NULL)
		{
			// シーンを描画
			scene->Draw();

			// 次の項目へ
			scene = scene->m_pNext;
		}
	}
}

//=============================================================================
//	関数名	:DeleteAll
//	引数	:無し
//	戻り値	:無し
//	説明	:リストに追加されている全ての対象を削除する。
//=============================================================================
void CSceneGL::DeleteAll(bool isLast)
{
	for (int nCnt = 0; nCnt < PRIORITY_MAX; nCnt++)
	{
		CSceneGL *pScene = m_pTop[nCnt];	// リストの先頭ポインタ
		CSceneGL *pSceneNext;		// 次参照先

		while (pScene != NULL)
		{
			// 次参照先を退避
			pSceneNext = pScene->m_pNext;

			// 終了処理
			pScene->Uninit(isLast);

			// インスタンス削除
			if (pScene != NULL)
			{
				delete pScene;
			}

			// 次参照先をセット
			pScene = pSceneNext;
		}

		m_pTop[nCnt] = NULL;
	}
}

//=============================================================================
//	関数名	:Release
//	引数	:無し
//	戻り値	:無し
//	説明	:対象を削除する。
//=============================================================================
void CSceneGL::Release(void)
{
	// 終了処理
	Uninit();

	if(this == m_pTop[m_Priority])
	{// リストの先頭の場合

		// リストの先頭を現在の次項目へ
		m_pTop[m_Priority] = m_pNext;
	}
	else
	{// リストの先頭でない場合

		// 前項目の次参照先を現在の次参照先へ
		m_pPrev->m_pNext = m_pNext;
	}

	if(this == m_pCur[m_Priority])
	{// リストの終端の場合

		// リストの終端を現在の前項目へ
		m_pCur[m_Priority] = m_pPrev;
	}
	else
	{// リストの終端でない場合

		// 次項目の前参照先を現在の前参照先へ
		m_pNext->m_pPrev = m_pPrev;
	}

	// インスタンス削除
	delete this;
}