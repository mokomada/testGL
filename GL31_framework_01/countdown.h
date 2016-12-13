#ifndef _COUNTDOWN_H_
#define _COUNTDOWN_H_
//=============================================================================
//
//	タイトル	ヘッダファイル(countdown.cpp)
//	ファイル名	countdown.h
//	作成者		AT13A284_29 塩原聖士
//	作成日		2016/11/14
//
//=============================================================================
#include "number.h"

//=============================================================================
//	マクロ定義
//=============================================================================
#define COUNTDOWN_TIMING ( 90 ) //タイミング
#define COUNTDOWN_ADDSIZE ( 10.0f )//拡大サイズ量
#define COUNTDOWN_FACE ( 5 )//表示を開始するタイミング
//=============================================================================
//	構造体
//=============================================================================
//=============================================================================
//	クラス定義
//=============================================================================
class CCountDown : public CScene2DGL
{
public:
	CCountDown(bool ifListAdd = true, int priority = 1, OBJTYPE objtype = OBJTYPE_NONE);
	~CCountDown();
	
	void	Init(VECTOR3 pos, VECTOR2 size, int figure);
	void	Uninit(bool isLast = false);
	void	Update(void);
	void	Draw(void);

	static CCountDown	*Create(VECTOR3 pos, VECTOR2 size, int figure);

	void	SetValue(float value);

	void	SetCountDown( float countdown ){ m_Value = countdown; };//数値をセットする

	bool	GetStartFlag( void ){ return m_Start; };//開始フラグを渡す

protected:
	static int		m_NumFigure;

	CNumber	**m_Number;


private :
	float m_Value;//数値
	int m_Frame;//減算タイミング
	bool m_CountDown;//カウントダウン開始フラグ
	bool m_Start;//カウントダウンが終了したかどうか

	VECTOR2 m_BaseSize;//拡大前サイズ
	
};

#endif