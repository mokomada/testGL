#ifndef _SOUND_H_
#define _SOUND_H_
//=============================================================================
//
//	タイトル	ヘッダファイル
//	ファイル名	sound.h
//	作成者		AT13A284_07 池田達哉
//	作成日		2016/06/23
//
//=============================================================================
#include "main.h"
#include <al/al.h>
#include <al/alc.h>
#include <al/alut.h>

//=============================================================================
//	リンク
//=============================================================================
#pragma comment(lib, "openAL32.lib")
#pragma comment(lib, "alut.lib")


//=============================================================================
//	マクロ定義
//=============================================================================
#define	NUM_SOURCE	(SOUNDLABEL_MAX * 2)
#define	BOLUME_MAX	(10.0f)

//=============================================================================
//	構造体
//=============================================================================
typedef struct{			// サウンドのパラメータ
	char	*pFilename;	// ファイル名
	int		Loop;		// ループ情報
} SOUNDPARAM;

typedef enum{				// サウンドのラベル
	SOUNDLABEL_BGM000 = 0,	// BGMその１
	SOUNDLABEL_SE000,		// SEその１
	SOUNDLABEL_MAX,
} SOUNDLABEL;

//=============================================================================
//	クラス定義
//=============================================================================
class CSound
{
public:
	static void	Init(void);
	static void	Uninit(void);
	static void	Update(void);

	static void Play(ALuint index, float volume = 1.0f);
	static void Stop(int index);

private:
	static ALuint		m_Buffer[SOUNDLABEL_MAX];
	static ALuint		m_Source[NUM_SOURCE];

	static SOUNDPARAM	m_Param[SOUNDLABEL_MAX];

};

#endif