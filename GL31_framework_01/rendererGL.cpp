//=============================================================================
//
//	タイトル レンダラファイル
//	ファイル名 rendererGL.cpp
//	作成者 AT13A284_07 池田達哉
//	作成日 2016/04/14
//
//=============================================================================
//=============================================================================
//	インクルード
//=============================================================================
#include "rendererGL.h"
#include <stdio.h>
//#include <GL/glut.h>
//#include <gl/glpng.h>
#include "gl/glpng.h"

//=============================================================================
//	静的メンバ変数
//=============================================================================
VECTOR3	CRendererGL::m_BGColor;

//=============================================================================
//	関数名:Init
//	引数:HWND hWnd
//	戻り値:無し
//	説明:初期化処理を行う。
//=============================================================================
void CRendererGL::Init(HWND hWnd)
{
	// ピクセルフォーマット初期化
	PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER, //Flags
		PFD_TYPE_RGBA, //The kind of framebuffer. RGBA or palette.
		32, //Colordepth of the framebuffer.
		0, 0, 0, 0, 0, 0,
		0,
		0,
		0,
		0, 0, 0, 0,
		24, //Number of bits for the depthbuffer
		8, //Number of bits for the stencilbuffer
		0, //Number of Aux buffers in the framebuffer.
		PFD_MAIN_PLANE,
		0,
		0, 0, 0
	};
	m_Dc = GetDC(hWnd);
	int format = ChoosePixelFormat(m_Dc, &pfd);

	// OpenGLが使うデバイスコンテキストに指定のピクセルフォーマットをセット
	SetPixelFormat(m_Dc, format, &pfd);

	// OpenGL contextを作成
	m_GlRC = wglCreateContext(m_Dc);

	// 作成されたコンテキストがカレント（現在使用中のコンテキスト）か？
	wglMakeCurrent(m_Dc, m_GlRC);

	// カリングを行う
	glFrontFace(GL_CW);	//反時計回りが表
	glEnable(GL_CULL_FACE);	//カリングON 

	// ライトを有効化
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	// ブレンド設定
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// 背景色設定
	m_BGColor = VECTOR3(0.0f, 0.0f, 0.0f);
}

//=============================================================================
//	関数名:Uninit
//	引数:HWND hWnd
//	戻り値:無し
//	説明:終了処理を行う。
//=============================================================================
void CRendererGL::Uninit(HWND hWnd)
{
	// カレントコンテキストを無効にする
	wglMakeCurrent(NULL, NULL);

	// カレントコンテキストを削除
	wglDeleteContext(m_GlRC);

	// デバイスコンテキスト解放
	ReleaseDC(hWnd, m_Dc);
}

//=============================================================================
//	関数名:Update
//	引数:無し
//	戻り値:無し
//	説明:更新処理を行う。
//=============================================================================
void CRendererGL::Update(void)
{
	
}

//=============================================================================
//	関数名:Begin
//	引数:無し
//	戻り値:無し
//	説明:描画処理を行う。
//=============================================================================
void CRendererGL::Begin(void)
{
	// 画面初期化カラーの設定
	//glClearColor(m_BGColor.x, m_BGColor.y, m_BGColor.z, 1.0f);
	glClearColor(0.5f, 0.5f, 1.0f, 1.0f);
	// 画面初期化
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// 2D描画準備
	glViewport(0, 0, (GLsizei)SCREEN_WIDTH, (GLsizei)SCREEN_HEIGHT);	// ウィンドウ全体をビューポートにする
}

//=============================================================================
//	関数名:End
//	引数:無し
//	戻り値:無し
//	説明:描画処理を行う。
//=============================================================================
void CRendererGL::End(void)
{
	glFlush();
	SwapBuffers(m_Dc);
}

//=============================================================================
//	関数名	:CreateTextureTGA
//	引数	:char *filename(読み込むファイル名)
//	戻り値	:int
//	説明	:TGAファイルからテクスチャを読み込む。
//=============================================================================
int CRendererGL::CreateTextureTGA(char *filename)
{
	FILE	*fp;
	GLubyte	header[18]		= {NULL};
	GLubyte	*image			= 0;
	GLuint	width			= 0;	// 横のピクセル数
	GLuint	height			= 0;	// 縦のピクセル数
	GLuint	bpp				= 0;// 1ピクセルあたり24バイトか32バイトか
	GLubyte	byteperpixel	= 0;	// 1ピクセルあたりのバイト数
	GLuint	texID			= 0;	// テクスチャID

	// ファイル拡張子判別
	char strBuff[256];		// 文字列バッファ
	char strFileOP[5];		// 文字列バッファ
	int nNumCmp = 0;		// 文字列カウント
	int nCntStr = 0;

	if(fp = fopen(filename, "rb"))
	{
		memset(strFileOP, 0, sizeof(strFileOP));
		strcpy(strBuff, filename);

		// ファイルが開かれている場合のみ処理を実行する
		for(int nCntLoad = 0 ; (nCntLoad < 256) || (strBuff[nCntLoad] != NULL) ; nCntLoad++)
		{
			if(strBuff[nCntLoad] == '.')
			{
				nCntLoad++;
				if(strBuff[nCntLoad] != '\\')
				{
					for(int i = 0 ; i < 5 ; i++)
					{
						if(strBuff[nCntLoad] != NULL)
						{
							strFileOP[i] = strBuff[nCntLoad];
							nCntLoad++;
						}
						else
						{
							strFileOP[i] = NULL;
							break;
						}
					}
				}
			}
		}

		if(strcmp(strFileOP, "tga") == 0)
		{
			fread(header, 1, sizeof(header), fp);
			width	= header[13] * 256 + header[12];
			height	= header[15] * 256 + header[14];
			bpp		= header[16];
			byteperpixel = bpp / 8;

			image	= new GLubyte[ width * height * byteperpixel ];
			for(int y = 0 ; y < (int)height ; y++)
			{
				for(int x = 0 ; x < (int)width ; x++)
				{
					if(byteperpixel == 4)		// RGBA
					{
						image[(y * width + x) * byteperpixel + 2] = fgetc(fp);
						image[(y * width + x) * byteperpixel + 1] = fgetc(fp);
						image[(y * width + x) * byteperpixel + 0] = fgetc(fp);
						image[(y * width + x) * byteperpixel + 3] = fgetc(fp);
					}
					else if(byteperpixel == 3)	// RGB
					{
						image[(y * width + x) * byteperpixel + 2] = fgetc(fp);
						image[(y * width + x) * byteperpixel + 1] = fgetc(fp);
						image[(y * width + x) * byteperpixel + 0] = fgetc(fp);
					}
				}
			}
			fclose(fp);
	
			// テクスチャ作成 IDで分ける
			glGenTextures(1, &texID);                                            
	
			// テクスチャのバインド
			glBindTexture(GL_TEXTURE_2D, texID);
			
			if(bpp == 32)		// RGBA
			{
				// 色情報格納単位設定
				glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
			}
			else if(bpp == 24)	// RGB
			{
				// 色情報格納単位設定
				glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
			}
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			if(bpp == 32)		// RGBA
			{
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
			}
			else if(bpp == 24)	// RGB
			{
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
			}

			glBindTexture(GL_TEXTURE_2D, 0);


			delete[] image;
		}
		else if(strcmp(strFileOP, "bmp") == 0)
		{
			fread(header, 1, sizeof(header), fp);
			width	= header[13] * 256 + header[12];
			height	= header[15] * 256 + header[14];
			bpp		= header[16];
			byteperpixel = bpp / 8;

			image	= new GLubyte[width * height * byteperpixel];

			for(int y = (height - 1) ; y >= 0 ; y--)
			{
				for(int x = 0 ; x < (int)width ; x++)
				{
					if(byteperpixel == 4)		// RGBA
					{
						image[(y * width + x) * byteperpixel + 3] = fgetc(fp);
						image[(y * width + x) * byteperpixel + 2] = fgetc(fp);
						image[(y * width + x) * byteperpixel + 1] = fgetc(fp);
						image[(y * width + x) * byteperpixel + 0] = fgetc(fp);
					}
					else if(byteperpixel == 3)	// RGB
					{
						image[(y * width + x) * byteperpixel + 2] = fgetc(fp);
						image[(y * width + x) * byteperpixel + 1] = fgetc(fp);
						image[(y * width + x) * byteperpixel + 0] = fgetc(fp);
					}
				}
			}
			fclose(fp);
	
			//テクスチャ作成 IDで分ける
			glGenTextures(1, &texID);                                            
	
			//バインドなど
			glBindTexture(GL_TEXTURE_2D, texID);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			
			// アルファの有無
			if(bpp == 32)		// RGBA
			{// アルファ付きTGA画像
				
				// テクスチャイメージ作成
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
			}
			else if(bpp == 24)	// RGB
			{// アルファ無しTGA画像
				
				// テクスチャイメージ作成
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
			}

			// テクスチャのバインド解除
			glBindTexture(GL_TEXTURE_2D, 0);

			// インスタンスの削除
			delete[] image;
		}
		else if(strcmp(strFileOP, "png") == 0)
		{
			pngInfo info;
			texID = pngBind(filename, PNG_NOMIPMAP, PNG_ALPHA, &info, GL_CLAMP, GL_NEAREST, GL_NEAREST);
		}

		// テクスチャIDをリターン
		return texID;
	}

	// テクスチャが見つからない
	return 0;
}

//=============================================================================
//	関数名	:CreateTextureBMP
//	引数	:char *filename(読み込むファイル名)
//	戻り値	:int
//	説明	:BMPファイルからテクスチャを読み込む。
//=============================================================================
int CRendererGL::CreateTextureBMP(char *filename)
{
	FILE	*fp = fopen(filename, "rb");
	GLubyte	header[18];
	GLubyte	*image;
	GLuint	width;			// 横のピクセル数
	GLuint	height;			// 縦のピクセル数
	GLuint	bpp;			// 1ピクセルあたり24バイトか32バイトか
	GLubyte	byteperpixel;	// 1ピクセルあたりのバイト数
	GLuint	texID;			// テクスチャID

	// ファイル拡張子判別
	char strBuff[256];		// 文字列バッファ
	char strFileOP[5];		// 文字列バッファ
	int nNumCmp = 0;		// 文字列カウント
	int nCntStr = 0;

	memset(strFileOP, 0, sizeof(strFileOP));
	strcpy(strBuff, filename);

	// ファイルが開かれている場合のみ処理を実行する
	for(int nCntLoad = 0 ; (nCntLoad < 256) || (strBuff[nCntLoad] != NULL) ; nCntLoad++)
	{
		if(strBuff[nCntLoad] == '.')
		{
			nCntLoad++;
			if(strBuff[nCntLoad] != '\\')
			{
				for(int i = 0 ; i < 5 ; i++)
				{
					if(strBuff[nCntLoad] != NULL)
					{
						strFileOP[i] = strBuff[nCntLoad];
						nCntLoad++;
					}
					else
					{
						strFileOP[i] = NULL;
						break;
					}
				}
			}
		}
	}

	if(strcmp(strFileOP, "bmp") == 0)
	{
		fread(header, 1, sizeof(header), fp);
		width	= header[13] * 256 + header[12];
		height	= header[15] * 256 + header[14];
		bpp		= header[16];
		byteperpixel = bpp / 8;

		image	= new GLubyte[width * height * byteperpixel];

		for(int y = (height - 1) ; y >= 0 ; y--)
		{
			for(int x = 0 ; x < (int)width ; x++)
			{
				if(byteperpixel == 4)		// RGBA
				{
					image[(y * width + x) * byteperpixel + 3] = fgetc(fp);
					image[(y * width + x) * byteperpixel + 2] = fgetc(fp);
					image[(y * width + x) * byteperpixel + 1] = fgetc(fp);
					image[(y * width + x) * byteperpixel + 0] = fgetc(fp);
				}
				else if(byteperpixel == 3)	// RGB
				{
					image[(y * width + x) * byteperpixel + 2] = fgetc(fp);
					image[(y * width + x) * byteperpixel + 1] = fgetc(fp);
					image[(y * width + x) * byteperpixel + 0] = fgetc(fp);
				}
			}
		}
		fclose(fp);
	
		//テクスチャ作成 IDで分ける
		glGenTextures(1, &texID);                                            
	
		//バインドなど
	
		glBindTexture(GL_TEXTURE_2D, texID);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		if(bpp == 32)		// RGBA
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
		}
		else if(bpp == 24)	// RGB
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		}

		glBindTexture(GL_TEXTURE_2D, 0);


		delete[] image;
	}

	return texID;
}