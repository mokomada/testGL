//=============================================================================
//
//	タイトル	フェード処理
//	ファイル名	fade.cpp
//	作成者		AT13A284_07 池田達哉
//	作成日		2016/07/12
//
//=============================================================================
//=============================================================================
//	インクルード
//=============================================================================
#include "fade.h"
#include "manager.h"
#include "input.h"
#include "scene2DGL.h"

//=============================================================================
//	静的メンバ変数
//=============================================================================
CMode		*CFade::m_NextMode;
int			CFade::m_NextModeState;
FADE_STATE	CFade::m_FadeState;
int			CFade::m_FadeTime;
float		CFade::m_Alpha;

//=============================================================================
//	関数名	:Init
//	引数	:無し
//	戻り値	:無し
//	説明	:初期化処理を行う。
//=============================================================================
void CFade::Init(void)
{
	m_Alpha = 1.0f;
	m_FadeTime = 0;
	m_FadeState = FS_FIRST;
}

//=============================================================================
//	関数名	:Uninit
//	引数	:無し
//	戻り値	:無し
//	説明	:終了処理を行う。
//=============================================================================
void CFade::Uninit(void)
{

}

//=============================================================================
//	関数名	:Update
//	引数	:無し
//	戻り値	:無し
//	説明	:更新処理を行う。
//=============================================================================
void CFade::Update(void)
{
	if(m_FadeState == FS_FIRST)
	{// 初期フェーズ
		m_Alpha -= (1.0f / FADE_TIME);

		if(m_Alpha < 0.0f)
		{
			m_Alpha = 0.0f;
			m_FadeState = FS_NONE;
		}
	}
	else if(m_FadeState == FS_IN)
	{// フェードインの時

		m_Alpha -= (1.0f / FADE_TIME);

		if(m_Alpha < 0.0f)
		{
			m_Alpha = 0.0f;
			m_FadeState = FS_NONE;
		}
	}
	else if(m_FadeState == FS_OUT)
	{// フェードアウトの時

		m_Alpha += (1.0f / FADE_TIME);
		

		if(m_Alpha > 1.0f)
		{// フェードが完了した場合

			m_Alpha = 1.0f;

			m_FadeState = FS_IN;
			
			if(m_NextMode != NULL)
			{
				CManager::SetMode(m_NextMode, m_NextModeState);
				m_NextMode = NULL;
			}
		}
	}

}

//=============================================================================
//	関数名	:Draw
//	引数	:無し
//	戻り値	:無し
//	説明	:描画処理を行う。
//=============================================================================
void CFade::Draw(void)
{
	// モデルビューマトリックスの設定(投影変換)
	glMatrixMode(GL_PROJECTION);
	// マトリックスの保存
	glPushMatrix();
	// 変換行列の初期化
	glLoadIdentity();

	// 平行射影or正射影
	glOrtho(0, (GLdouble)SCREEN_WIDTH, (GLdouble)SCREEN_HEIGHT, 0, -100.0, 100.0);
	// ワールド座標系の表示領域を，ビューポートの大きさに比例させる

	// モデルビューマトリックスの設定
	glMatrixMode(GL_MODELVIEW);
	// マトリックスの保存
	glPushMatrix();
	// 変換行列の初期化
	glLoadIdentity();

	// ブレンド有効化
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// ライト無効化
	glDisable(GL_LIGHTING);

	// ポリゴン描画
	glBegin(GL_TRIANGLE_STRIP);
	{
		// 頂点色設定
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);


		// 描画用のテクスチャ座標・頂点座標設定
		// 左上頂点
		glColor4f(0.0f, 0.0f, 0.0f, m_Alpha);
		glTexCoord2d(0.0, 1.0);
		glVertex3f(0.0f, 0.0f, 0.0f);

		// 右上頂点
		glColor4f(0.0f, 0.0f, 0.0f, m_Alpha);
		glTexCoord2d(1.0, 1.0);
		glVertex3f(SCREEN_WIDTH, 0.0f, 0.0f);

		// 左下頂点
		glColor4f(0.0f, 0.0f, 0.0f, m_Alpha);
		glTexCoord2d(0.0, 0.0);
		glVertex3f(0.0f, SCREEN_HEIGHT, 0.0f);

		// 右下頂点
		glColor4f(0.0f, 0.0f, 0.0f, m_Alpha);
		glTexCoord2d(1.0, 0.0);
		glVertex3f(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
	}
	glEnd();

	// ブレンド無効化
	glDisable(GL_BLEND);

	// ライト有効化
	glEnable(GL_LIGHTING);

	// モデルビューマトリックスの設定(投影変換)
	glMatrixMode(GL_PROJECTION);
	// 保存マトリックスの取り出し
	glPopMatrix();

	// モデルビューマトリックスの設定
	glMatrixMode(GL_MODELVIEW);
	// 保存マトリックスの取り出し
	glPopMatrix();

}

//=============================================================================
//	関数名	:Start
//	引数	:無し
//	戻り値	:無し
//	説明	:フェードを開始する。
//=============================================================================
void CFade::Start(CMode *nextMode, int nextModeState, FADE_STATE fadeState)
{
	if((nextMode != NULL) && (m_FadeState == FS_NONE))
	{
		m_NextMode = nextMode;
		m_NextModeState = nextModeState;
		m_FadeState = fadeState;
	}
}