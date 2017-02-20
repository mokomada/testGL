#ifndef _NUMBER_H_
#define _NUMBER_H_
//=============================================================================
//
//	タイトル	ヘッダファイル(number.cpp)
//	ファイル名	number.h
//	作成者		AT13A284_07 池田達哉
//	作成日		2016/11/14
//
//=============================================================================
#include "sceneGL.h"
#include "manager.h"
#include "rendererGL.h"

//=============================================================================
//	マクロ定義
//=============================================================================
#define	NUMBER_TEXFILENAME000	"number000.png"	// ポリゴンのファイル名

//=============================================================================
//	マクロ定義
//=============================================================================

//=============================================================================
//	クラス定義
//=============================================================================
class CNumber
{
public:
	CNumber();
	~CNumber();
	
	void	Init(VECTOR3 pos = VECTOR3(0.0f, 0.0f, 0.0f), VECTOR2 size = VECTOR2(0.0f, 0.0f),
				int value = 0, char *texName = "./data/TEXTURE/number000.tga");
	void	Uninit(void);
	void	Update(void);
	void	Draw(void);

	static CNumber	*Create(VECTOR3 pos = VECTOR3(0.0f, 0.0f, 0.0f), VECTOR2 size = VECTOR2(0.0f, 0.0f),
							int value = 0, char *texName = "./data/TEXTURE/number000.tga");
	
	static int GetFigure( int num ); //桁数を出す
	void	AddSize( VECTOR2 addsize ){ m_Size += addsize; };//サイズの加算
	void	SetSize( VECTOR2 size ){ m_Size = size; };//サイズの設定

	void	SetNumber(int value = 0);

protected:
	VECTOR3 m_Pos;//座標
	VECTOR3 m_Rot;//角度
	VECTOR2 m_Size;		// ポリゴンのサイズ
	float	m_fLength;	// 対角線の長さ
	float	m_fAngle;	// 角度
	int		m_Texture;	// テクスチャ

	int		m_Number;
};

#endif