//=============================================================================
//
//	タイトル	壁紙
//	ファイル名	podium.cpp
//	作成者		AT13A284_02 秋田京
//	作成日		2016/2/06
//
//=============================================================================

//=============================================================================
//	インクルード
//=============================================================================

#include "manager.h"
#include "main.h"
#include "rendererGL.h"
#include "game.h"
#include "sceneGL.h"
#include "scene3DGL.h"
#include "sceneModel.h"
#include "square.h"
#include "podium.h"


/********************************************
---------------コンストラクタ----------------
*********************************************/
CPodium::CPodium(bool ifListAdd , int priority , OBJTYPE objType) : CSquare( ifListAdd , priority , objType )
{
}


/********************************************
----------------デストラクタ-----------------
*********************************************/
CPodium::~CPodium()
{
}


/********************************************
-----------------初期化処理------------------
********************************************/
void CPodium::Init(VECTOR3 pos , VECTOR3 size , char* TexName, VECTOR4 color)
{
	CRendererGL	*renderer	= CManager::GetRendererGL();
	CSquare::Create(VECTOR3(pos.x, pos.y, pos.z), VECTOR3(size.x, size.y, size.z), TexName , color);	//squareのクリエイトを読んでいる

}

CPodium *CPodium::Create(VECTOR3 pos , VECTOR3 size , char* TexName, VECTOR4 color)
{
	CPodium *podium;		//インスタンス

	//インスタンス作成
	podium = new CPodium();

	//初期化作成	//位置、大きさ、色
	podium -> Init(pos, size, TexName, color);

	//インスタンスをreturn
	return podium;
}