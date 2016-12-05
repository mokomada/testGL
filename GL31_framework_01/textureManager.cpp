/******************************************************************************
*	ファイル：
*	作成者  ：庄司茜
*	作成日  ：
******************************************************************************/
/******************************************************************************
*	インクルードファイル
******************************************************************************/

#include "main.h"
#include "manager.h"
#include "rendererGL.h"
#include "textureManager.h"

/******************************************************************************
*	マクロ定義
******************************************************************************/
/******************************************************************************
*	構造体定義
******************************************************************************/
/******************************************************************************
*	プロトタイプ宣言
******************************************************************************/
/******************************************************************************
*	グローバル変数
******************************************************************************/
int CTextureManager::m_Texture[ TEXTURE_MAX ] = { 0 };		// テクスチャ
char * CTextureManager::m_texName[ TEXTURE_MAX ] = 			//テクスチャの名前
{
	{"./data/TEXTURE/shadow000.png"},
	{"./data/TEXTURE/bullet000.png"}
};
/******************************************************************************
*	関数名：
*	引数  ：なし
*	戻り値：なし
*	説明  ：コンストラクタ
******************************************************************************/
CTextureManager::CTextureManager()
{
}
/******************************************************************************
*	関数名：
*	引数  ：なし
*	戻り値：なし
*	説明  ：デストラクタ
******************************************************************************/
CTextureManager::~CTextureManager()
{
}
/******************************************************************************
*	関数名：
*	引数  ：
*	戻り値：HRESULT
*	説明  ：初期化処理
******************************************************************************/
HRESULT CTextureManager::Init( void )
{
	CRendererGL	*renderer	= CManager::GetRendererGL();

	for( int i = 0; i < TEXTURE_MAX; i++ )
	{
		m_Texture[ i ] = renderer->CreateTextureTGA( m_texName[ i ] );
	}
	return S_OK;
}

/******************************************************************************
*	関数名：
*	引数  ：なし
*	戻り値：なし
*	説明  ：終了処理
******************************************************************************/
void CTextureManager::Uninit( void )
{
	for( int i = 0; i < TEXTURE_MAX; i++ )
	{
		// テクスチャ削除
		if(m_Texture[ i ] != NULL)
		{
			glDeleteTextures( 1 , ( ( GLuint * )m_Texture[ i ] ) );
		}
	}
}
