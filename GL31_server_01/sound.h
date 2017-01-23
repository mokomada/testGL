#ifndef _SOUND_H_
#define _SOUND_H_
//=============================================================================
//
//	�^�C�g��	�w�b�_�t�@�C��
//	�t�@�C����	sound.h
//	�쐬��		AT13A284_07 �r�c�B��
//	�쐬��		2016/06/23
//
//=============================================================================
#include "main.h"
#include <al/al.h>
#include <al/alc.h>
#include <al/alut.h>

//=============================================================================
//	�����N
//=============================================================================
#pragma comment(lib, "openAL32.lib")
#pragma comment(lib, "alut.lib")


//=============================================================================
//	�}�N����`
//=============================================================================
#define	NUM_SOURCE	(SOUNDLABEL_MAX * 2)
#define	BOLUME_MAX	(10.0f)

//=============================================================================
//	�\����
//=============================================================================
typedef struct{			// �T�E���h�̃p�����[�^
	char	*pFilename;	// �t�@�C����
	int		Loop;		// ���[�v���
} SOUNDPARAM;

typedef enum{				// �T�E���h�̃��x��
	SOUNDLABEL_BGM000 = 0,	// BGM���̂P
	SOUNDLABEL_SE000,		// SE���̂P
	SOUNDLABEL_MAX,
} SOUNDLABEL;

//=============================================================================
//	�N���X��`
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