//=============================================================================
//
//	ƒ^ƒCƒgƒ‹	ƒV[ƒ“ƒtƒ@ƒCƒ‹
//	ƒtƒ@ƒCƒ‹–¼	scene.cpp
//	ì¬Ò		AT13A284_07 ’r“c’BÆ
//	ì¬“ú		2016/04/19
//
//=============================================================================
//=============================================================================
//	ƒCƒ“ƒNƒ‹[ƒh
//=============================================================================
#include "sceneGL.h"
#include "main.h"
#include "rendererGL.h"
#include "scene2DGL.h"

//=============================================================================
//	Ã“Iƒƒ“ƒo•Ï”
//=============================================================================
CSceneGL *CSceneGL::m_pTop;
CSceneGL *CSceneGL::m_pCur;

//=============================================================================
//	ŠÖ”–¼	:CSceneGL()
//	ˆø”	:–³‚µ
//	–ß‚è’l	:–³‚µ
//	à–¾	:ƒRƒ“ƒXƒgƒ‰ƒNƒ^B
//=============================================================================
CSceneGL::CSceneGL(int priority, OBJTYPE objType)
{
	// ï¿½Iï¿½uï¿½Wï¿½Fï¿½Nï¿½gï¿½^ï¿½Cï¿½vï¿½Eï¿½vï¿½ï¿½ï¿½Cï¿½Iï¿½ï¿½ï¿½eï¿½Bï¿½Zï¿½bï¿½g
	m_ObjType	= objType;
	m_Priority	= priority;

	if(m_pTop == NULL)
	{// ƒŠƒXƒg‚É‰½‚à“o˜^‚³‚ê‚Ä‚È‚¢ê‡

		// ©g‚Ìƒ|ƒCƒ“ƒ^‚ğƒŠƒXƒgæ“ª‚É“o˜^
		m_pTop = this;

		// æ“ª‚Ö“o˜^
		m_pPrev = NULL;
	}
	else
	{// ƒŠƒXƒg‚É‘¼‚É’Ç‰Á‚³‚ê‚Ä‚¢‚éê‡

		// ‘O€–Ú‚ğQÆæ‚É
		m_pPrev = m_pCur;

		// ‘O€–Ú‚ÌŸQÆæ‚ğ©g‚É
		m_pPrev->m_pNext = this;
	}
		
	// ƒŠƒXƒg‚ÌI’[ƒ|ƒCƒ“ƒ^‚É©g‚ğ“o˜^
	m_pCur = this;

	// Ÿ‚Ì€–Ú‚Í–³‚¢
	m_pNext = NULL;

	// À•WE‰ñ“]‚Ì‰Šú‰»
	SetPos(VECTOR3(0.0f, 0.0f, 0.0f));
	SetRot(VECTOR3(0.0f, 0.0f, 0.0f));
}

//=============================================================================
//	ŠÖ”–¼	:~CSceneGL()
//	ˆø”	:–³‚µ
//	–ß‚è’l	:–³‚µ
//	à–¾	:ƒfƒXƒgƒ‰ƒNƒ^B
//=============================================================================
CSceneGL::~CSceneGL()
{
	CSceneGL *pScene = m_pTop;		// QÆæƒoƒbƒtƒ@
	CSceneGL *pSceneNext = NULL;	// ŸQÆæƒoƒbƒtƒ@
	CSceneGL *pScenePrev = NULL;	// ‘OQÆæƒoƒbƒtƒ@

	// ‘S‚Ä‚ÌƒV[ƒ“‚ğQÆ
	while(pScene)
	{
		// ŸQÆæ‚Æ‘OQÆæ‚ğ‘Ş”ğ
		pSceneNext = pScene->m_pNext;
		pScenePrev = pScene->m_pPrev;

		if(pScene == this)
		{
			// ‘OQÆæ‚ª‘¶İ‚·‚éê‡
			if(pScene->m_pPrev)
			{
				// ‘OQÆæ‚ğXV
				pScene->m_pPrev->m_pNext = pScene->m_pNext;
			}

			// ŸQÆæ‚ª‘¶İ‚·‚éê‡
			if(pScene->m_pNext)
			{
				// ŸQÆæ‚ğXV
				pScene->m_pNext->m_pPrev = pScene->m_pPrev;
			}

			// ƒŠƒXƒg‚Ìæ“ª‚Ìê‡
			if(pScene == m_pTop)
			{
				// ƒŠƒXƒg‚Ìæ“ª‚ğXV
				m_pTop = pSceneNext;
			}

			// ƒŠƒXƒg‚ÌI’[‚Ìê‡
			if(pScene == m_pCur)
			{
				// ƒŠƒXƒg‚ÌI’[‚ğXV
				m_pCur = pScenePrev;
			}
		}

		// ŸQÆæ‚ğƒZƒbƒg
		pScene = pSceneNext;
	}
}

//=============================================================================
//	ŠÖ”–¼	:UpdateAll
//	ˆø”	:–³‚µ
//	–ß‚è’l	:–³‚µ
//	à–¾	:ƒŠƒXƒg‚É’Ç‰Á‚³‚ê‚Ä‚¢‚é‘S‚Ä‚Ì‘ÎÛ‚ğXV‚·‚éB
//=============================================================================
void CSceneGL::UpdateAll(void)
{
	CSceneGL *scene = m_pTop;	// ƒŠƒXƒg‚Ìæ“ªƒ|ƒCƒ“ƒ^
	CSceneGL *sceneNext;		// ƒŠƒXƒg‚ÌŸQÆæƒoƒbƒtƒ@

	// ƒŠƒXƒg‚ÌÅŒã‚É“’B‚·‚é‚Ü‚ÅXV‚ğ‘±‚¯‚é
	while(scene != NULL)
	{
		// ŸQÆæ‚ğXV
		sceneNext = scene->m_pNext;

		// ƒV[ƒ“‚ğXV
		scene->Update();

		// Ÿ‚Ì€–Ú‚Ö
		scene = sceneNext;
	}
}

//=============================================================================
//	ŠÖ”–¼	:DrawAll
//	ˆø”	:–³‚µ
//	–ß‚è’l	:–³‚µ
//	à–¾	:ƒŠƒXƒg‚É’Ç‰Á‚³‚ê‚Ä‚¢‚é‘S‚Ä‚Ì‘ÎÛ‚ğ•`‰æ‚·‚éB
//=============================================================================
void CSceneGL::DrawAll(void)
{
	CSceneGL *scene = m_pTop;	// ƒŠƒXƒg‚Ìæ“ªƒ|ƒCƒ“ƒ^
	
	// ƒŠƒXƒg‚ÌÅŒã‚É“’B‚·‚é‚Ü‚Å•`‰æ‚ğ‘±‚¯‚é
	while(scene != NULL)
	{
		// ƒV[ƒ“‚ğ•`‰æ
		scene->Draw();

		// Ÿ‚Ì€–Ú‚Ö
		scene = scene->m_pNext;
	}
}

//=============================================================================
//	ŠÖ”–¼	:DeleteAll
//	ˆø”	:–³‚µ
//	–ß‚è’l	:–³‚µ
//	à–¾	:ƒŠƒXƒg‚É’Ç‰Á‚³‚ê‚Ä‚¢‚é‘S‚Ä‚Ì‘ÎÛ‚ğíœ‚·‚éB
//=============================================================================
void CSceneGL::DeleteAll(bool isLast)
{
	CSceneGL *pScene = m_pTop;	// ƒŠƒXƒg‚Ìæ“ªƒ|ƒCƒ“ƒ^
	CSceneGL *pSceneNext;		// ŸQÆæ
	
	while(pScene != NULL)
	{
		// ŸQÆæ‚ğ‘Ş”ğ
		pSceneNext = pScene->m_pNext;

		// I—¹ˆ—
		pScene->Uninit(isLast);

		// ƒCƒ“ƒXƒ^ƒ“ƒXíœ
		if(pScene != NULL)
		{
			delete pScene;
		}

		// ŸQÆæ‚ğƒZƒbƒg
		pScene = pSceneNext;
	}
}

//=============================================================================
//	ŠÖ”–¼	:Release
//	ˆø”	:–³‚µ
//	–ß‚è’l	:–³‚µ
//	à–¾	:‘ÎÛ‚ğíœ‚·‚éB
//=============================================================================
void CSceneGL::Release(void)
{
	// I—¹ˆ—
	Uninit();

	if(this == m_pTop)
	{// ƒŠƒXƒg‚Ìæ“ª‚Ìê‡

		// ƒŠƒXƒg‚Ìæ“ª‚ğŒ»İ‚ÌŸ€–Ú‚Ö
		m_pTop = m_pNext;
	}
	else
	{// ƒŠƒXƒg‚Ìæ“ª‚Å‚È‚¢ê‡

		// ‘O€–Ú‚ÌŸQÆæ‚ğŒ»İ‚ÌŸQÆæ‚Ö
		m_pPrev->m_pNext = m_pNext;
	}

	if(this == m_pCur)
	{// ƒŠƒXƒg‚ÌI’[‚Ìê‡

		// ƒŠƒXƒg‚ÌI’[‚ğŒ»İ‚Ì‘O€–Ú‚Ö
		m_pCur = m_pPrev;
	}
	else
	{// ƒŠƒXƒg‚ÌI’[‚Å‚È‚¢ê‡

		// Ÿ€–Ú‚Ì‘OQÆæ‚ğŒ»İ‚Ì‘OQÆæ‚Ö
		m_pNext->m_pPrev = m_pPrev;
	}

	// ƒCƒ“ƒXƒ^ƒ“ƒXíœ
	delete this;
}