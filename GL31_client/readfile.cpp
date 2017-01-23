//=============================================================================
//
//	タイトル	ファイル読み込み関数
//	ファイル名	readfile.cpp
//	作成者		AT13A284_07 池田達哉
//	作成日		2016/06/14
//
//=============================================================================
//=============================================================================
//	インクルード
//=============================================================================
#include "readfile.h"
#include "main.h"

//=============================================================================
//	関数名	:ReadBinaryFile
//	引数	:unsigned char *str(ファイル内容を格納する文字列)
//			 char *filename(ファイル名)
//	戻り値	:無し
//	説明	:バイナリファイルを文字列に読み込み、その先頭アドレスを返す。
//=============================================================================
char *CReadFile::ReadBinaryFile(char *filename)
{
	FILE			*fp;			// ファイルポインタ
	char	*str = NULL;	// ファイル内容格納文字列
	int				cnt = 0;		// ファイルの文字数カウンタ
	
	// ファイルオープン
	if((fp = fopen(filename, "rb")) == NULL)
	{// ファイルのオープンに失敗した場合
		exit(EXIT_FAILURE);
	}

	// ファイルの文字数をカウント
	while(fgetc(fp) != EOF)
	{
		cnt++;
	}

	// ファイル指定子をファイル先頭へ
	fseek(fp, 0, SEEK_SET);

	// 配列生成
	str = new char[cnt];

	// 文字列にファイルをセット
	fread(str, sizeof(unsigned char), cnt, fp);

	// ファイルクローズ
	fclose(fp);

	return str;
}

//=============================================================================
//	関数名	:SearchWordByFile
//	引数	:char *str(検索する対象の文字列)
//			 char *word(検索するワード)
//	戻り値	:無し
//	説明	:文字列中のオフセット以降の位置から引数で指定したワードを検索し、
//			 その先頭の配列番号を返す。見つからなかった場合、-1を返す
//=============================================================================
int CReadFile::SearchWordByString(char *str, unsigned int offset, char *word)
{
	char *strBuff	= str;	// 文字列バッファ
	char *wordBuff	= word;	// 
	int nNumCmp		= 0;	// 文字列カウント
	int nCntStr		= 0;	// 

	// オフセットの値が異常でないか、検索ワードが空白でないかチェック
	if((offset < strlen(strBuff)) && (offset >= 0) && (word != "") && (word != NULL))
	{
		// 文字列の参照位置を移動
		for(int i = offset ; strBuff[i] != NULL ; i++)
		{
			// 先頭文字が一致した場合
			if(strBuff[i] == wordBuff[0])
			{
				for(int j = 1 ; ((strBuff[i + j] != NULL) && (wordBuff[0] != NULL)) ; j++)
				{
					// 文字列が一致しているか走査
						// 先頭の配列番号を返す
					if(wordBuff[j] == NULL)
					{// 文字列を発見した(検索ワード配列の終端に達した)
						return i;
					}
					else if(strBuff[i + j] != wordBuff[j])
					{// 文字列不一致

						// ループを抜ける
						break;
					}
				}
			}
		}
	}

	// 文字列が見つからなかった場合-1を返す
	return -1;
}

//=============================================================================
//	関数名	:SearchWordNumByFile
//	引数	:char *str(検索する対象の文字列)
//			 int  offset(検索開始位置)
//			 char *word(検索するワード)
//	戻り値	:無し
//	説明	:文字列中のオフセット以降の位置から引数で指定したワードが、
//			 いくつ存在するかを返す。見つからなかった場合、-1を返す
//=============================================================================
int CReadFile::SearchWordNumByString(char *str, unsigned int offset, char *word)
{
	char	*strBuff	= str;	// 文字列バッファ
	char	*wordBuff	= word;	// 検索文字退避文字列
	int		nNumCmp		= 0;	// 文字列カウント
	int		nNumWard	= 0;	// 発見した文字列の個数

	// オフセットの値が異常でないか、検索ワードが空白でないかチェック
	if((offset < strlen(strBuff)) && (offset >= 0) && (word != "") && (word != NULL))
	{
		// 文字列の参照位置を移動
		for(int i = offset ; strBuff[i] != NULL ; i++)
		{
			// 先頭文字が一致した場合
			if(strBuff[i] == wordBuff[0])
			{
				for(int j = 1 ; ((strBuff[i + j] != NULL) && (wordBuff[0] != NULL)) ; j++)
				{
					// 文字列が一致しているか走査
					if(wordBuff[j] == NULL)
					{// 文字列を発見した(検索ワード配列の終端に達した)
						nNumWard++;
						break;
					}
					else if(strBuff[i + j] != wordBuff[j])
					{// 文字列不一致

						// ループを抜ける
						break;
					}
				}
			}
		}
	}

	if(nNumWard > 0)
	{
		return nNumWard;
	}
	else
	{
		// 文字列が見つからなかった場合-1を返す
		return nNumWard;
	}
}

//=============================================================================
//	関数名	:SearchWordNumByFile
//	引数	:char *str(検索する対象の文字列)
//			 int  offset(検索開始位置)
//			 char *word(検索するワード)
//			 char *endword(検索終了文字)
//	戻り値	:無し
//	説明	:文字列中のオフセット以降の位置から引数で指定したワードが、
//			 いくつ存在するかを返す。見つからなかった場合、-1を返す
//			 検索終了文字が来た場合、カウントを終了する
//=============================================================================
int CReadFile::SearchWordNumByString(char *str, unsigned int offset, char *word, char *endword)
{
	char	*strBuff	= str;		// 文字列バッファ
	char	*wordBuff	= word;		// 検索文字退避文字列
	char	*endwordBuff= endword;	// 検索終了文字退避文字列
	int		nNumWard	= 0;		// 発見した文字列の個数


	// オフセットの値が異常でないか、検索ワードが空白でないかチェック
	if((offset < strlen(strBuff)) && (offset >= 0) && (word != "") && (word != NULL))
	{
		// 文字列の参照位置を移動
		for(int i = offset ; strBuff[i] != NULL ; i++)
		{
			// 先頭文字が一致した場合
			if(strBuff[i] == wordBuff[0])
			{
				for(int j = 1 ; ((strBuff[i + j] != NULL) && (wordBuff[0] != NULL)) ; j++)
				{
					// 文字列が一致しているか走査
					if(wordBuff[j] == NULL)
					{// 文字列を発見した(検索ワード配列の終端に達した)

						// カウンタ増加
						nNumWard++;
						break;
					}
					else if(strBuff[i + j] != wordBuff[j])
					{// 文字列不一致

						// ループを抜ける
						break;
					}
				}
			}
			
			if(strBuff[i] == endwordBuff[0])
			{
				for(int j = 1 ; ((strBuff[i + j] != NULL) && (endwordBuff[0] != NULL)) ; j++)
				{
					// 文字列が一致しているか走査
					if(endwordBuff[j] == NULL)
					{// 文字列を発見した(検索ワード配列の終端に達した)

						// 関数を抜ける
						// 検索ワードが見つかったかどうか
						if(nNumWard > 0)
						{// 見つかった場合

							// その個数を返す
							return nNumWard;
						}
						else
						{// 見つからなかった場合

							// -1を返す
							return -1;
						}
					}
					else if(strBuff[i + j] != endwordBuff[j])
					{// 文字列不一致

						// ループを抜ける
						break;
					}
				}
			}
		}
	}

	// 検索ワードが見つかったかどうか
	if(nNumWard > 0)
	{// 見つかった場合

		// その個数を返す
		return nNumWard;
	}
	else
	{// 見つからなかった場合

		// -1を返す
		return -1;
	}
}

//=============================================================================
//	関数名	:SearchWordByFile
//	引数	:FILE *fp(ファイルポインタ)
//			 char *word(検索するワード)
//	戻り値	:無し
//	説明	:ファイル中から引数で指定したワードを検索し、ファイル位置指定子をワードの後ろに移動する。
//	注意	:ファイルをオープンしている時に呼び出すこと。
//=============================================================================
bool CReadFile::SearchWordByFile(FILE *fp, char *word)
{
	char *strCal = word;
	char strBuff[65535] = {0};		// 文字列バッファ
	int nNumCmp = 0;		// 文字列カウント
	int nCntStr = 0;

	// ファイルが開かれている場合のみ処理を実行する
	if(fp != NULL)
	{
		while(feof(fp) == 0)
		{
			strBuff[nCntStr] = (char)fgetc(fp);
			for(int nCntLoad = 0 ; (nCntLoad < 65535) || (strBuff[nCntLoad] != NULL) ; nCntLoad++)
			{
				if(strBuff[nCntLoad] == *strCal)
				{
					nNumCmp++;
					strCal++;

					// 文字列を発見した場合trueを返す
					if(nNumCmp == strlen(word))
					{
						return true;
					}
				}
				else
				{
					for(int nCntLoad = 0 ; nCntLoad < nNumCmp ; nCntLoad++)
					{
						strCal--;
					}
					nNumCmp = 0;
				}
			}

			nCntStr++;
		}
	}

	// 文字列が見つからなかったまたはファイルポインタがNULLの場合falseを返す
	return false;
}