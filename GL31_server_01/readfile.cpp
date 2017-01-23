//=============================================================================
//
//	�^�C�g��	�t�@�C���ǂݍ��݊֐�
//	�t�@�C����	readfile.cpp
//	�쐬��		AT13A284_07 �r�c�B��
//	�쐬��		2016/06/14
//
//=============================================================================
//=============================================================================
//	�C���N���[�h
//=============================================================================
#include "readfile.h"
#include "main.h"

//=============================================================================
//	�֐���	:ReadBinaryFile
//	����	:unsigned char *str(�t�@�C�����e���i�[���镶����)
//			 char *filename(�t�@�C����)
//	�߂�l	:����
//	����	:�o�C�i���t�@�C���𕶎���ɓǂݍ��݁A���̐擪�A�h���X��Ԃ��B
//=============================================================================
char *CReadFile::ReadBinaryFile(char *filename)
{
	FILE			*fp;			// �t�@�C���|�C���^
	char	*str = NULL;	// �t�@�C�����e�i�[������
	int				cnt = 0;		// �t�@�C���̕������J�E���^
	
	// �t�@�C���I�[�v��
	if((fp = fopen(filename, "rb")) == NULL)
	{// �t�@�C���̃I�[�v���Ɏ��s�����ꍇ
		exit(EXIT_FAILURE);
	}

	// �t�@�C���̕��������J�E���g
	while(fgetc(fp) != EOF)
	{
		cnt++;
	}

	// �t�@�C���w��q���t�@�C���擪��
	fseek(fp, 0, SEEK_SET);

	// �z�񐶐�
	str = new char[cnt];

	// ������Ƀt�@�C�����Z�b�g
	fread(str, sizeof(unsigned char), cnt, fp);

	// �t�@�C���N���[�Y
	fclose(fp);

	return str;
}

//=============================================================================
//	�֐���	:SearchWordByFile
//	����	:char *str(��������Ώۂ̕�����)
//			 char *word(�������郏�[�h)
//	�߂�l	:����
//	����	:�����񒆂̃I�t�Z�b�g�ȍ~�̈ʒu��������Ŏw�肵�����[�h���������A
//			 ���̐擪�̔z��ԍ���Ԃ��B������Ȃ������ꍇ�A-1��Ԃ�
//=============================================================================
int CReadFile::SearchWordByString(char *str, unsigned int offset, char *word)
{
	char *strBuff	= str;	// ������o�b�t�@
	char *wordBuff	= word;	// 
	int nNumCmp		= 0;	// ������J�E���g
	int nCntStr		= 0;	// 

	// �I�t�Z�b�g�̒l���ُ�łȂ����A�������[�h���󔒂łȂ����`�F�b�N
	if((offset < strlen(strBuff)) && (offset >= 0) && (word != "") && (word != NULL))
	{
		// ������̎Q�ƈʒu���ړ�
		for(int i = offset ; strBuff[i] != NULL ; i++)
		{
			// �擪��������v�����ꍇ
			if(strBuff[i] == wordBuff[0])
			{
				for(int j = 1 ; ((strBuff[i + j] != NULL) && (wordBuff[0] != NULL)) ; j++)
				{
					// �����񂪈�v���Ă��邩����
						// �擪�̔z��ԍ���Ԃ�
					if(wordBuff[j] == NULL)
					{// ������𔭌�����(�������[�h�z��̏I�[�ɒB����)
						return i;
					}
					else if(strBuff[i + j] != wordBuff[j])
					{// ������s��v

						// ���[�v�𔲂���
						break;
					}
				}
			}
		}
	}

	// �����񂪌�����Ȃ������ꍇ-1��Ԃ�
	return -1;
}

//=============================================================================
//	�֐���	:SearchWordNumByFile
//	����	:char *str(��������Ώۂ̕�����)
//			 int  offset(�����J�n�ʒu)
//			 char *word(�������郏�[�h)
//	�߂�l	:����
//	����	:�����񒆂̃I�t�Z�b�g�ȍ~�̈ʒu��������Ŏw�肵�����[�h���A
//			 �������݂��邩��Ԃ��B������Ȃ������ꍇ�A-1��Ԃ�
//=============================================================================
int CReadFile::SearchWordNumByString(char *str, unsigned int offset, char *word)
{
	char	*strBuff	= str;	// ������o�b�t�@
	char	*wordBuff	= word;	// ���������ޔ𕶎���
	int		nNumCmp		= 0;	// ������J�E���g
	int		nNumWard	= 0;	// ��������������̌�

	// �I�t�Z�b�g�̒l���ُ�łȂ����A�������[�h���󔒂łȂ����`�F�b�N
	if((offset < strlen(strBuff)) && (offset >= 0) && (word != "") && (word != NULL))
	{
		// ������̎Q�ƈʒu���ړ�
		for(int i = offset ; strBuff[i] != NULL ; i++)
		{
			// �擪��������v�����ꍇ
			if(strBuff[i] == wordBuff[0])
			{
				for(int j = 1 ; ((strBuff[i + j] != NULL) && (wordBuff[0] != NULL)) ; j++)
				{
					// �����񂪈�v���Ă��邩����
					if(wordBuff[j] == NULL)
					{// ������𔭌�����(�������[�h�z��̏I�[�ɒB����)
						nNumWard++;
						break;
					}
					else if(strBuff[i + j] != wordBuff[j])
					{// ������s��v

						// ���[�v�𔲂���
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
		// �����񂪌�����Ȃ������ꍇ-1��Ԃ�
		return nNumWard;
	}
}

//=============================================================================
//	�֐���	:SearchWordNumByFile
//	����	:char *str(��������Ώۂ̕�����)
//			 int  offset(�����J�n�ʒu)
//			 char *word(�������郏�[�h)
//			 char *endword(�����I������)
//	�߂�l	:����
//	����	:�����񒆂̃I�t�Z�b�g�ȍ~�̈ʒu��������Ŏw�肵�����[�h���A
//			 �������݂��邩��Ԃ��B������Ȃ������ꍇ�A-1��Ԃ�
//			 �����I�������������ꍇ�A�J�E���g���I������
//=============================================================================
int CReadFile::SearchWordNumByString(char *str, unsigned int offset, char *word, char *endword)
{
	char	*strBuff	= str;		// ������o�b�t�@
	char	*wordBuff	= word;		// ���������ޔ𕶎���
	char	*endwordBuff= endword;	// �����I�������ޔ𕶎���
	int		nNumWard	= 0;		// ��������������̌�


	// �I�t�Z�b�g�̒l���ُ�łȂ����A�������[�h���󔒂łȂ����`�F�b�N
	if((offset < strlen(strBuff)) && (offset >= 0) && (word != "") && (word != NULL))
	{
		// ������̎Q�ƈʒu���ړ�
		for(int i = offset ; strBuff[i] != NULL ; i++)
		{
			// �擪��������v�����ꍇ
			if(strBuff[i] == wordBuff[0])
			{
				for(int j = 1 ; ((strBuff[i + j] != NULL) && (wordBuff[0] != NULL)) ; j++)
				{
					// �����񂪈�v���Ă��邩����
					if(wordBuff[j] == NULL)
					{// ������𔭌�����(�������[�h�z��̏I�[�ɒB����)

						// �J�E���^����
						nNumWard++;
						break;
					}
					else if(strBuff[i + j] != wordBuff[j])
					{// ������s��v

						// ���[�v�𔲂���
						break;
					}
				}
			}
			
			if(strBuff[i] == endwordBuff[0])
			{
				for(int j = 1 ; ((strBuff[i + j] != NULL) && (endwordBuff[0] != NULL)) ; j++)
				{
					// �����񂪈�v���Ă��邩����
					if(endwordBuff[j] == NULL)
					{// ������𔭌�����(�������[�h�z��̏I�[�ɒB����)

						// �֐��𔲂���
						// �������[�h�������������ǂ���
						if(nNumWard > 0)
						{// ���������ꍇ

							// ���̌���Ԃ�
							return nNumWard;
						}
						else
						{// ������Ȃ������ꍇ

							// -1��Ԃ�
							return -1;
						}
					}
					else if(strBuff[i + j] != endwordBuff[j])
					{// ������s��v

						// ���[�v�𔲂���
						break;
					}
				}
			}
		}
	}

	// �������[�h�������������ǂ���
	if(nNumWard > 0)
	{// ���������ꍇ

		// ���̌���Ԃ�
		return nNumWard;
	}
	else
	{// ������Ȃ������ꍇ

		// -1��Ԃ�
		return -1;
	}
}

//=============================================================================
//	�֐���	:SearchWordByFile
//	����	:FILE *fp(�t�@�C���|�C���^)
//			 char *word(�������郏�[�h)
//	�߂�l	:����
//	����	:�t�@�C������������Ŏw�肵�����[�h���������A�t�@�C���ʒu�w��q�����[�h�̌��Ɉړ�����B
//	����	:�t�@�C�����I�[�v�����Ă��鎞�ɌĂяo�����ƁB
//=============================================================================
bool CReadFile::SearchWordByFile(FILE *fp, char *word)
{
	char *strCal = word;
	char strBuff[65535] = {0};		// ������o�b�t�@
	int nNumCmp = 0;		// ������J�E���g
	int nCntStr = 0;

	// �t�@�C�����J����Ă���ꍇ�̂ݏ��������s����
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

					// ������𔭌������ꍇtrue��Ԃ�
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

	// �����񂪌�����Ȃ������܂��̓t�@�C���|�C���^��NULL�̏ꍇfalse��Ԃ�
	return false;
}