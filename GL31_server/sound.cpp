//=============================================================================
//
//	�^�C�g��	�T�E���h�t�@�C��
//	�t�@�C����	sound.cpp
//	�쐬��		AT13A284_07 �r�c�B��
//	�쐬��		2016/06/23
//
//=============================================================================
//=============================================================================
//	�C���N���[�h
//=============================================================================
#include "sound.h"
#include "main.h"

//=============================================================================
//	�ÓI�����o�ϐ�
//=============================================================================
ALuint		CSound::m_Buffer[SOUNDLABEL_MAX];		// �o�b�t�@
ALuint		CSound::m_Source[NUM_SOURCE];			// �\�[�X

SOUNDPARAM	CSound::m_Param[SOUNDLABEL_MAX] = {
	{"./data/SOUND/bgm000.wav", -1},				// BGM����1
	{"./data/SOUND/se000.wav", 0},					// SE����1
};	// �T�E���h�p�����[�^

//=============================================================================
//	�֐���	:Init
//	����	:����
//	�߂�l	:����
//	����	:�������������s���B
//=============================================================================
void CSound::Init(void)
{
	alutInit(0, 0);
	alGenSources(NUM_SOURCE, m_Source);

	for(int i = 0 ; i < SOUNDLABEL_MAX ; i++)
	{
		m_Buffer[i] = alutCreateBufferFromFile(m_Param[i].pFilename);
	}
}

//=============================================================================
//	�֐���	:UnInit
//	����	:����
//	�߂�l	:����
//	����	:�I���������s���B
//=============================================================================
void CSound::Uninit(void)
{
	int state;	// �\�[�X�̏��

	// �S�\�[�X���~
	for(int i = 0 ; i < NUM_SOURCE ; i++)
	{
		Stop(i);
	}
	
	// �o�b�t�@�̃A���o�C���h
	for(int i = 0 ; i < NUM_SOURCE ; i++)
	{
		// �\�[�X�̏�Ԃ��擾
		alGetSourcei(m_Source[i], AL_SOURCE_STATE, &state);

		// �\�[�X�̏�Ԃ�����
		if((state != AL_PLAYING) && (state != AL_PAUSED))
		{// �\�[�X���Đ����E�ꎞ��~���łȂ����

			// �o�b�t�@���A���o�C���h
			alSourcei(m_Source[i], AL_BUFFER, NULL);
		}
	}

	// �\�[�X�폜
	alDeleteSources(sizeof(m_Source), m_Source);
	
	// �o�b�t�@�폜
	alDeleteBuffers(sizeof(m_Buffer), m_Buffer);

	// alut�㏈��
	alutExit();
}

//=============================================================================
//	�֐���	:UnInit
//	����	:����
//	�߂�l	:����
//	����	:�X�V�������s���B
//=============================================================================
void CSound::Update(void)
{

}

//=============================================================================
//	�֐���	:Play
//	����	:int index(�Đ�����C���f�b�N�X�ԍ�)
//	�߂�l	:int
//	����	:�C���f�b�N�X�ԍ��Ŏw�肵���T�E���h�t�@�C�����Đ�����B
//=============================================================================
void CSound::Play(ALuint index, float volume)
{
	// �C���f�b�N�X��臒l����
	if(index < SOUNDLABEL_MAX)
	{// �C���f�b�N�X������ȏꍇ�̂ݍĐ��������s��

		// �{�����[����臒l����
		if(volume < 0.0f)
		{// �{�����[���������������ꍇ

			// �{�����[���𐳐���
			volume *= -1;
		}
		if(volume > BOLUME_MAX)
		{// �{�����[�����傫������ꍇ(�����������Ƃ�z��)

			// �K�����ʂɂȂ�܂ŉ��ʂ�����������
			while(volume > BOLUME_MAX)
			{
				volume /= BOLUME_MAX;
			}
		}

		// �Đ������A���g�p�o�b�t�@������
		for(int i = 0 ; i < NUM_SOURCE ; i++)
		{
			int state;	// �\�[�X�̏��
			
			// �\�[�X�̏�Ԃ��擾
			alGetSourcei(m_Source[i], AL_SOURCE_STATE, &state);

			// �T�E���h��Ԃ�����
			if(state != AL_PLAYING)
			{// �Đ����Ă��Ȃ��ꍇ�̂ݍĐ�����

				// �o�b�t�@�ƃ\�[�X���֘A�t��
				alSourcei(m_Source[i], AL_BUFFER, m_Buffer[index]);

				// �{�����[���ݒ�
				alSourcef(m_Source[i], AL_GAIN, volume);

				// ���[�v�ݒ�
				if(m_Param[index].Loop == -1)
				{
					alSourcei(m_Source[i], AL_LOOPING, AL_TRUE);
				}
				else
				{
					alSourcei(m_Source[i], AL_LOOPING, AL_FALSE);
				}

				// �T�E���h�Đ�
				alSourcePlay(m_Source[i]);
				break;
			}
		}
	}
}

//=============================================================================
//	�֐���	:Play
//	����	:int index(��~����C���f�b�N�X�ԍ�)
//	�߂�l	:int
//	����	:�C���f�b�N�X�ԍ��Ŏw�肵���T�E���h�t�@�C�����~����B
//=============================================================================
void CSound::Stop(int index)
{
	// �C���f�b�N�X��臒l����
	if(index < SOUNDLABEL_MAX)
	{// �C���f�b�N�X������ȏꍇ�̂ݒ�~�������s��
		
		int state;	// �T�E���h�̏��

		// �\�[�X�̏�Ԃ��擾
		alGetSourcei(m_Source[index], AL_SOURCE_STATE, &state);

		// �T�E���h��Ԃ�����
		if(state == AL_PLAYING)
		{// �Đ����Ă���ꍇ�̂ݒ�~����

			// �T�E���h��~
			alSourceStop(m_Source[index]);
		}
	}
}