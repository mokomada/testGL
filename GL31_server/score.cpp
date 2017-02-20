//=============================================================================
//
//	タイトル	シーンファイル(2DGL)
//	ファイル名	score.cpp
//	作成者		AT13A284_07 池田達哉
//	作成日		2016/11/14
//
//=============================================================================
//=============================================================================
//	インクルード
//=============================================================================
#include "sceneGL.h"
#include "scene2DGL.h"
#include "score.h"
#include "manager.h"
#include "main.h"
#include "rendererGL.h"

//=============================================================================
//	静的メンバ変数
//=============================================================================
int		CScore::m_NumFigure;

//=============================================================================
//	関数名	:CScore()
//	引数	:無し
//	戻り値	:無し
//	説明	:コンストラクタ。f
//=============================================================================
CScore::CScore(int priority, OBJTYPE objtype) : CScene2DGL(true, priority , objtype )
{

}

//=============================================================================
//	関数名	:~CScore()
//	引数	:無し
//	戻り値	:無し
//	説明	:デストラクタ。
//=============================================================================
CScore::~CScore()
{

}

//=============================================================================
//	関数名	:Init
//	引数	:VECTOR3 pos(初期位置)
//	戻り値	:無し
//	説明	:初期化処理を行うと共に、初期位置を設定する。
//=============================================================================
void CScore::Init(VECTOR3 pos, VECTOR2 size, int figure)
{
	// 桁情報格納
	m_NumFigure = figure;

	// ナンバーインスタンス配列生成
	m_Number = new CNumber *[m_NumFigure];

	SetPos(VECTOR3(pos.x, pos.y, pos.z));
	SetRot(VECTOR3(0.0f, 0.0f, 0.0f));
	
	// 座標設定
	for(int i = 0 ; i < m_NumFigure; i++)
	{// 整数部設定

		//float difference = (size.x * 0.25f) * (i - m_NumFigure / 2 + ((m_NumFigure % 2 == 0) ? 0 : 1));
		float difference = (size.x * 0.25f) * i;

		m_Number[i] = CNumber::Create(VECTOR3((pos.x + difference), pos.y, pos.z), VECTOR2((size.x / m_NumFigure), size.y));
	}
}

//=============================================================================
//	関数名	:Uninit
//	引数	:無し
//	戻り値	:無し
//	説明	:終了処理を行う。
//=============================================================================
void CScore::Uninit(bool isLast)
{

}

//=============================================================================
//	関数名	:Update
//	引数	:無し
//	戻り値	:無し
//	説明	:更新処理を行う。
//=============================================================================
void CScore::Update(void)
{
	static float value = 0.0f;

	value += 1.0f;
	SetValue(value);
}

//=============================================================================
//	関数名	:Draw
//	引数	:無し
//	戻り値	:無し
//	説明	:描画処理を行う。
//=============================================================================
void CScore::Draw(void)
{
	// ナンバー描画
	for(int i = 0 ; i < m_NumFigure ; i++)
	{
		m_Number[i]->Draw();
	}
}

//=============================================================================
//	関数名	:Create
//	引数	:VECTOR3 pos(初期位置)
//	戻り値	:無し
//	説明	:インスタンス生成を行うと共に、初期位置を設定する。
//=============================================================================
CScore *CScore::Create(VECTOR3 pos, VECTOR2 size, int figure)
{
	CScore *score;	// インスタンス

	// インスタンス生成
	score = new CScore();

	// 初期化処理
	score->Init(pos, size, figure);

	// インスタンスをリターン
	return score;
}

//=============================================================================
//	関数名	:SetValue
//	引数	:無し
//	戻り値	:無し
//	説明	:数値をセットする。
//=============================================================================
void CScore::SetValue(float value)
{
	float valueCal = value;	// 数値
	float valueUpper = 0.0f;
	float valueLower = 0.0f;


	// 整数部セット
	for(int i = 0 ; i < m_NumFigure ; i++)
	{
		if(valueCal >= pow(10.0f, (m_NumFigure - i - 1)))
		{
			m_Number[i]->SetNumber((int)valueCal / (int)pow(10.0f, (m_NumFigure - i - 1)));
		}
		else
		{
			m_Number[i]->SetNumber(0);
		}

		// 桁下げ
		valueCal = (float)((int)valueCal % (int)pow(10.0f, (m_NumFigure - i - 1)));
	}
}