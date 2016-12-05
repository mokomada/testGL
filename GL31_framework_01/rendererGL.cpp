//=============================================================================
//
//	�^�C�g�� �����_���t�@�C��
//	�t�@�C���� rendererGL.cpp
//	�쐬�� AT13A284_07 �r�c�B��
//	�쐬�� 2016/04/14
//
//=============================================================================
//=============================================================================
//	�C���N���[�h
//=============================================================================
#include "rendererGL.h"
#include <stdio.h>
//#include <GL/glut.h>
//#include <gl/glpng.h>
#include "gl/glpng.h"

//=============================================================================
//	�ÓI�����o�ϐ�
//=============================================================================
VECTOR3	CRendererGL::m_BGColor;

//=============================================================================
//	�֐���:Init
//	����:HWND hWnd
//	�߂�l:����
//	����:�������������s���B
//=============================================================================
void CRendererGL::Init(HWND hWnd)
{
	// �s�N�Z���t�H�[�}�b�g������
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

	// OpenGL���g���f�o�C�X�R���e�L�X�g�Ɏw��̃s�N�Z���t�H�[�}�b�g���Z�b�g
	SetPixelFormat(m_Dc, format, &pfd);

	// OpenGL context���쐬
	m_GlRC = wglCreateContext(m_Dc);

	// �쐬���ꂽ�R���e�L�X�g���J�����g�i���ݎg�p���̃R���e�L�X�g�j���H
	wglMakeCurrent(m_Dc, m_GlRC);

	// �J�����O���s��
	glFrontFace(GL_CW);	//�����v��肪�\
	glEnable(GL_CULL_FACE);	//�J�����OON 

	// ���C�g��L����
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	// �u�����h�ݒ�
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// �w�i�F�ݒ�
	m_BGColor = VECTOR3(0.0f, 0.0f, 0.0f);
}

//=============================================================================
//	�֐���:Uninit
//	����:HWND hWnd
//	�߂�l:����
//	����:�I���������s���B
//=============================================================================
void CRendererGL::Uninit(HWND hWnd)
{
	// �J�����g�R���e�L�X�g�𖳌��ɂ���
	wglMakeCurrent(NULL, NULL);

	// �J�����g�R���e�L�X�g���폜
	wglDeleteContext(m_GlRC);

	// �f�o�C�X�R���e�L�X�g���
	ReleaseDC(hWnd, m_Dc);
}

//=============================================================================
//	�֐���:Update
//	����:����
//	�߂�l:����
//	����:�X�V�������s���B
//=============================================================================
void CRendererGL::Update(void)
{
	
}

//=============================================================================
//	�֐���:Begin
//	����:����
//	�߂�l:����
//	����:�`�揈�����s���B
//=============================================================================
void CRendererGL::Begin(void)
{
	// ��ʏ������J���[�̐ݒ�
	//glClearColor(m_BGColor.x, m_BGColor.y, m_BGColor.z, 1.0f);
	glClearColor(0.5f, 0.5f, 1.0f, 1.0f);
	// ��ʏ�����
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// 2D�`�揀��
	glViewport(0, 0, (GLsizei)SCREEN_WIDTH, (GLsizei)SCREEN_HEIGHT);	// �E�B���h�E�S�̂��r���[�|�[�g�ɂ���
}

//=============================================================================
//	�֐���:End
//	����:����
//	�߂�l:����
//	����:�`�揈�����s���B
//=============================================================================
void CRendererGL::End(void)
{
	glFlush();
	SwapBuffers(m_Dc);
}

//=============================================================================
//	�֐���	:CreateTextureTGA
//	����	:char *filename(�ǂݍ��ރt�@�C����)
//	�߂�l	:int
//	����	:TGA�t�@�C������e�N�X�`����ǂݍ��ށB
//=============================================================================
int CRendererGL::CreateTextureTGA(char *filename)
{
	FILE	*fp;
	GLubyte	header[18]		= {NULL};
	GLubyte	*image			= 0;
	GLuint	width			= 0;	// ���̃s�N�Z����
	GLuint	height			= 0;	// �c�̃s�N�Z����
	GLuint	bpp				= 0;// 1�s�N�Z��������24�o�C�g��32�o�C�g��
	GLubyte	byteperpixel	= 0;	// 1�s�N�Z��������̃o�C�g��
	GLuint	texID			= 0;	// �e�N�X�`��ID

	// �t�@�C���g���q����
	char strBuff[256];		// ������o�b�t�@
	char strFileOP[5];		// ������o�b�t�@
	int nNumCmp = 0;		// ������J�E���g
	int nCntStr = 0;

	if(fp = fopen(filename, "rb"))
	{
		memset(strFileOP, 0, sizeof(strFileOP));
		strcpy(strBuff, filename);

		// �t�@�C�����J����Ă���ꍇ�̂ݏ��������s����
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
	
			// �e�N�X�`���쐬 ID�ŕ�����
			glGenTextures(1, &texID);                                            
	
			// �e�N�X�`���̃o�C���h
			glBindTexture(GL_TEXTURE_2D, texID);
			
			if(bpp == 32)		// RGBA
			{
				// �F���i�[�P�ʐݒ�
				glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
			}
			else if(bpp == 24)	// RGB
			{
				// �F���i�[�P�ʐݒ�
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
	
			//�e�N�X�`���쐬 ID�ŕ�����
			glGenTextures(1, &texID);                                            
	
			//�o�C���h�Ȃ�
			glBindTexture(GL_TEXTURE_2D, texID);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			
			// �A���t�@�̗L��
			if(bpp == 32)		// RGBA
			{// �A���t�@�t��TGA�摜
				
				// �e�N�X�`���C���[�W�쐬
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
			}
			else if(bpp == 24)	// RGB
			{// �A���t�@����TGA�摜
				
				// �e�N�X�`���C���[�W�쐬
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
			}

			// �e�N�X�`���̃o�C���h����
			glBindTexture(GL_TEXTURE_2D, 0);

			// �C���X�^���X�̍폜
			delete[] image;
		}
		else if(strcmp(strFileOP, "png") == 0)
		{
			pngInfo info;
			texID = pngBind(filename, PNG_NOMIPMAP, PNG_ALPHA, &info, GL_CLAMP, GL_NEAREST, GL_NEAREST);
		}

		// �e�N�X�`��ID�����^�[��
		return texID;
	}

	// �e�N�X�`����������Ȃ�
	return 0;
}

//=============================================================================
//	�֐���	:CreateTextureBMP
//	����	:char *filename(�ǂݍ��ރt�@�C����)
//	�߂�l	:int
//	����	:BMP�t�@�C������e�N�X�`����ǂݍ��ށB
//=============================================================================
int CRendererGL::CreateTextureBMP(char *filename)
{
	FILE	*fp = fopen(filename, "rb");
	GLubyte	header[18];
	GLubyte	*image;
	GLuint	width;			// ���̃s�N�Z����
	GLuint	height;			// �c�̃s�N�Z����
	GLuint	bpp;			// 1�s�N�Z��������24�o�C�g��32�o�C�g��
	GLubyte	byteperpixel;	// 1�s�N�Z��������̃o�C�g��
	GLuint	texID;			// �e�N�X�`��ID

	// �t�@�C���g���q����
	char strBuff[256];		// ������o�b�t�@
	char strFileOP[5];		// ������o�b�t�@
	int nNumCmp = 0;		// ������J�E���g
	int nCntStr = 0;

	memset(strFileOP, 0, sizeof(strFileOP));
	strcpy(strBuff, filename);

	// �t�@�C�����J����Ă���ꍇ�̂ݏ��������s����
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
	
		//�e�N�X�`���쐬 ID�ŕ�����
		glGenTextures(1, &texID);                                            
	
		//�o�C���h�Ȃ�
	
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