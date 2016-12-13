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
list<CSceneGL*>	CSceneGL::m_SceneList[PRIORITY_NUM];

//=============================================================================
//	関数名	:CSceneGL()
//	引数	:無し
//	戻り値	:無し
//	説明	:コンストラクタ。
//=============================================================================
CSceneGL::CSceneGL(bool ifListAdd, int priority, OBJTYPE objType)
{
	// リスト追加フラグがオンの場合、リストに自身を追加
	if(ifListAdd) m_SceneList[priority].push_back(this);

	// オブジェクトタイプを初期化
	m_ObjType = objType;

	// 座標・回転の初期化
	m_Pos = VEC3_ZERO;
	m_Rot = VEC3_ZERO;
}

//=============================================================================
//	関数名	:~CSceneGL()
//	引数	:無し
//	戻り値	:無し
//	説明	:デストラクタ。
//=============================================================================
CSceneGL::~CSceneGL()
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
	list<CSceneGL*>::iterator itr;	// リストのイテレータ

	// 全リストを検索
	for(int i = (PRIORITY_NUM - 1) ; i >= 0 ; i--)
	{
		// リストに登録されている全ての要素に更新処理を行う
		for(itr = m_SceneList[i].begin() ; itr != m_SceneList[i].end() ; itr++)
		{
			// 更新処理
			(*itr)->Update();
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
	list<CSceneGL*>::iterator itr;	// リストのイテレータ

	// 全リストを検索
	for(int i = (PRIORITY_NUM - 1) ; i >= 0 ; i--)
	{
		// リストに登録されている全ての要素に描画処理を行う
		for(itr = m_SceneList[i].begin() ; itr != m_SceneList[i].end() ; itr++)
		{
			// 描画処理
			(*itr)->Draw();
		}
	}
}

//=============================================================================
//	関数名	:DeleteAll
//	引数	:無し
//	戻り値	:無し
//	説明	:リストに追加されている全ての対象を削除する。
//=============================================================================
void CSceneGL::DeleteAll(void)
{
	list<CSceneGL*>::iterator itr;	// リストのイテレータ

	// 全リストを検索
	for(int i = 0 ; i < PRIORITY_NUM ; i++)
	{
		// リストに登録されている全ての要素を削除する
		for(itr = m_SceneList[i].begin() ; itr != m_SceneList[i].end() ; )
		{
			// インスタンスが存在している場合のみ処理
			if(*itr)
			{
				// 終了処理
				(*itr)->Uninit();

				// インスタンス削除
				delete (*itr);
			}

			// リストから削除
			itr = m_SceneList[i].erase(itr);
		}
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
	list<CSceneGL*>::iterator itr;	// リストのイテレータ

	// 全リストを検索
	for(int i = 0 ; i < PRIORITY_NUM ; i++)
	{
		// リストから自身のインスタンスを探索する
		for(itr = m_SceneList[i].begin() ; itr != m_SceneList[i].end() ; itr++)
		{
			// 自身のインスタンスを見つけ、リストから削除
			if(*itr == this)
			{
				if(*itr)
				{
					// 終了処理
					(*itr)->Uninit();

					// インスタンス削除
					delete (*itr);
				}

				// リスト削除
				itr = m_SceneList[i].erase(itr);

				// 処理終了
				break;
			}
		}
	}
}

//=============================================================================
//	関数名	:UnlinkList
//	引数	:無し
//	戻り値	:無し
//	説明	:対象をリストから外す。
//=============================================================================
void CSceneGL::UnlinkList(void)
{
	list<CSceneGL*>::iterator itr;	// リストのイテレータ

	// 全リストを検索
	for(int i = 0 ; i < PRIORITY_NUM ; i++)
	{
		// リストから自身のインスタンスを探索する
		for(itr = m_SceneList[i].begin() ; itr != m_SceneList[i].end() ; itr++)
		{
			// 自身のインスタンスを見つけ、リストから削除
			if(*itr == this)
			{
				// リスト削除
				itr = m_SceneList[i].erase(itr);

				// 処理終了
				break;
			}
		}
	}
}