//=============================================================================
//
//	タイトル	サウンドファイル
//	ファイル名	sound.cpp
//	作成者		AT13A284_07 池田達哉
//	作成日		2016/06/23
//
//=============================================================================
//=============================================================================
//	インクルード
//=============================================================================
#include "sound.h"
#include "main.h"

//=============================================================================
//	静的メンバ変数
//=============================================================================
ALuint		CSound::m_Buffer[SOUNDLABEL_MAX];		// バッファ
ALuint		CSound::m_Source[NUM_SOURCE];			// ソース

SOUNDPARAM	CSound::m_Param[SOUNDLABEL_MAX] = {
	{"./data/SOUND/bgm000.wav", -1},				// BGMその1
	{"./data/SOUND/se000.wav", 0},					// SEその1
};	// サウンドパラメータ

//=============================================================================
//	関数名	:Init
//	引数	:無し
//	戻り値	:無し
//	説明	:初期化処理を行う。
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
//	関数名	:UnInit
//	引数	:無し
//	戻り値	:無し
//	説明	:終了処理を行う。
//=============================================================================
void CSound::Uninit(void)
{
	int state;	// ソースの状態

	// 全ソースを停止
	for(int i = 0 ; i < NUM_SOURCE ; i++)
	{
		Stop(i);
	}
	
	// バッファのアンバインド
	for(int i = 0 ; i < NUM_SOURCE ; i++)
	{
		// ソースの状態を取得
		alGetSourcei(m_Source[i], AL_SOURCE_STATE, &state);

		// ソースの状態を検査
		if((state != AL_PLAYING) && (state != AL_PAUSED))
		{// ソースが再生中・一時停止中でなければ

			// バッファをアンバインド
			alSourcei(m_Source[i], AL_BUFFER, NULL);
		}
	}

	// ソース削除
	alDeleteSources(sizeof(m_Source), m_Source);
	
	// バッファ削除
	alDeleteBuffers(sizeof(m_Buffer), m_Buffer);

	// alut後処理
	alutExit();
}

//=============================================================================
//	関数名	:UnInit
//	引数	:無し
//	戻り値	:無し
//	説明	:更新処理を行う。
//=============================================================================
void CSound::Update(void)
{

}

//=============================================================================
//	関数名	:Play
//	引数	:int index(再生するインデックス番号)
//	戻り値	:int
//	説明	:インデックス番号で指定したサウンドファイルを再生する。
//=============================================================================
void CSound::Play(ALuint index, float volume)
{
	// インデックスの閾値検査
	if(index < SOUNDLABEL_MAX)
	{// インデックスが正常な場合のみ再生処理を行う

		// ボリュームの閾値検査
		if(volume < 0.0f)
		{// ボリュームが負数だった場合

			// ボリュームを正数に
			volume *= -1;
		}
		if(volume > BOLUME_MAX)
		{// ボリュームが大きすぎる場合(桁が多いことを想定)

			// 適正音量になるまで音量を小さくする
			while(volume > BOLUME_MAX)
			{
				volume /= BOLUME_MAX;
			}
		}

		// 再生処理、未使用バッファを検索
		for(int i = 0 ; i < NUM_SOURCE ; i++)
		{
			int state;	// ソースの状態
			
			// ソースの状態を取得
			alGetSourcei(m_Source[i], AL_SOURCE_STATE, &state);

			// サウンド状態を検査
			if(state != AL_PLAYING)
			{// 再生していない場合のみ再生する

				// バッファとソースを関連付け
				alSourcei(m_Source[i], AL_BUFFER, m_Buffer[index]);

				// ボリューム設定
				alSourcef(m_Source[i], AL_GAIN, volume);

				// ループ設定
				if(m_Param[index].Loop == -1)
				{
					alSourcei(m_Source[i], AL_LOOPING, AL_TRUE);
				}
				else
				{
					alSourcei(m_Source[i], AL_LOOPING, AL_FALSE);
				}

				// サウンド再生
				alSourcePlay(m_Source[i]);
				break;
			}
		}
	}
}

//=============================================================================
//	関数名	:Play
//	引数	:int index(停止するインデックス番号)
//	戻り値	:int
//	説明	:インデックス番号で指定したサウンドファイルを停止する。
//=============================================================================
void CSound::Stop(int index)
{
	// インデックスの閾値検査
	if(index < SOUNDLABEL_MAX)
	{// インデックスが正常な場合のみ停止処理を行う
		
		int state;	// サウンドの状態

		// ソースの状態を取得
		alGetSourcei(m_Source[index], AL_SOURCE_STATE, &state);

		// サウンド状態を検査
		if(state == AL_PLAYING)
		{// 再生している場合のみ停止する

			// サウンド停止
			alSourceStop(m_Source[index]);
		}
	}
}