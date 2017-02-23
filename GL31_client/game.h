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
#include <vector>
using namespace std;

//=============================================================================
//	構造体
//=============================================================================

//=============================================================================
//	前方宣言
//=============================================================================
class CMeshfield;
class CPlayer;

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
	static vector<CPlayer*>	GetPlayer(void) { return m_Player; }
	static int	GetFrame(void) { return m_GamaFrame; }

private:
	static CMeshfield	*m_Meshfield;	// メッシュフィールドのインスタンス
	static vector<CPlayer*>	m_Player;		// プレイヤーのインスタンス

	static int m_GamaFrame;
};

#endif