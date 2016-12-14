#ifndef _RENDERERGL_H_
#define _RENDERERGL_H_
//=============================================================================
//
//	タイトル ヘッダファイル(rendererGL.cpp)
//	ファイル名 rendererGL.h
//	作成者 AT13A284_07 池田達哉
//	作成日 2016/04/14
//
//=============================================================================
//=============================================================================
//	インクルード
//=============================================================================
#include "main.h"

//=============================================================================
//	リンク
//=============================================================================
#include <gl/GL.h>
//#include <gl/glew.h>
#include <gl/GLU.h>
#pragma comment(lib, "OpenGL32.lib")
#pragma comment(lib, "GLU32.lib")
//#pragma comment(lib, "glew32.lib")

//=============================================================================
//	マクロ定義
//=============================================================================
#define	VEC2_ZERO			(VECTOR2(0.0f, 0.0f))		// 2Dベクトルの0
#define	VEC3_ZERO			(VECTOR3(0.0f, 0.0f, 0.0f))	// 3Dベクトルの0
#define	SCENE_NUM	(2)
#define	BGCOLOR_R	(0.5f)
#define	BGCOLOR_G	(0.5f)
#define	BGCOLOR_B	(1.0f)
#define	BGCOLOR_ADD	(0.1f)

//=============================================================================
//	構造体
//=============================================================================

//=============================================================================
//	前方宣言
//=============================================================================
class CSceneGL;

//=============================================================================
//	クラス定義
//=============================================================================
class CRendererGL
{
public:
	static void	Init(HWND hWnd);
	static void	Uninit(HWND hWnd);
	static void	Update(void);
	static void	Begin(void);
	static void	End(void);
	
	static VECTOR3	GetBGColor(void) { return m_BGColor; }
	static void		SetBGColor(VECTOR3 color) { m_BGColor = color; }
	static void		AddBGColor(VECTOR3 color) { m_BGColor += color; }

	static int CreateTextureTGA(char *filename);
	static int CreateTextureBMP(char *filename);

private:
	static HDC		m_Dc;	// Device Context
	static HGLRC	m_GlRC;	// Handle to openGL Device Context
	
	static CSceneGL	*m_Scene[SCENE_NUM];	// シーンインスタンス
	static VECTOR3	m_BGColor;				// 背景色
};

#endif