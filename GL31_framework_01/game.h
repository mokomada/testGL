#ifndef _GAME_H_
#define _GAME_H_
//=============================================================================
//
//	タイトル	ヘッダファイル
//	ファイル名	game.h
//	作成者		AT13A284_07 池田達哉
//	作成日		2016/07/12
//
//=============================================================================
#include "mode.h"

//=============================================================================
//	前方宣言
//=============================================================================
class CMeshfield;
class CSceneModel;

//=============================================================================
//	クラス定義
//=============================================================================
class CGame : public CMode
{
public:
	CGame(){}
	~CGame(){}

	void	Init(void);
	void	Uninit(void);
	void	Update(void);
	void	Draw(void);

	static CMeshfield	*GetMeshfield(void){ return m_Meshfield; }
	static CSceneModel	*GetPlayer(void) { return m_Player; }

private:
	static CMeshfield	*m_Meshfield;	// メッシュフィールドのインスタンス
	static CSceneModel	*m_Player;		// プレイヤーのインスタンス
};

#endif