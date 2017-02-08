//=============================================================================
//
//	�^�C�g��	�V�[���t�@�C��(2DGL)
//	�t�@�C����	network.cpp
//	�쐬��		AT13A284_07 �r�c�B��
//	�쐬��		2016/11/14
//
//=============================================================================
//=============================================================================
//	�C���N���[�h
//=============================================================================
#include "network.h"
#include "main.h"
#include "debugProcGL.h"
#include "game.h"
#include "sceneModel.h"
#include <process.h>
#include <mbstring.h>

#pragma comment(lib, "ws2_32.lib")

//=============================================================================
//	�ÓI�����o�ϐ�
//=============================================================================
CONNECT_PROTOCOL CNetwork::m_ConnectProtocol = { "127.0.0.1", "239.0.0.1", 20000, 20000 };

int			CNetwork::m_PlayerNum = 0;
SOCKET		CNetwork::m_SockSend;
SOCKET		CNetwork::m_SockRecv;
sockaddr_in	CNetwork::m_AddrClient[4];
char		CNetwork::m_LastMessage[1024] = "NO DATA";
uint		CNetwork::m_thID;
HANDLE		CNetwork::m_hTh;
bool		CNetwork::m_ifInitialize = false;
int			CNetwork::m_ifBindSuccess = -1;

//=============================================================================
//	�֐���	:Init
//	����	:����
//	�߂�l	:����
//	����	:�������������s���B
//=============================================================================
void CNetwork::Init(void)
{
	// ���X���b�h�N����
	m_hTh = (HANDLE)_beginthreadex(NULL, 0, ReceiveThread, NULL, 0, &m_thID);

	WSADATA		wsadata;	// winsock�f�[�^
	int			sts;		// �X�^�[�g�A�b�v���
	int			errcode;	// �G���[�R�[�h
	sockaddr_in	addr;


	// �v�h�m�r�n�b�j��������
	sts = WSAStartup(MAKEWORD(2, 0), &wsadata);
	if(sts != 0)
	{
		errcode = WSAGetLastError();
		printf("WSAStartup�G���[�ł� %d \n", errcode);
		return;
	}

	// �o�[�W�����`�F�b�N
	if(LOBYTE(wsadata.wVersion) != 2 || HIBYTE(wsadata.wVersion) != 0)
	{
		printf("�o�[�W�����G���[�ł�\n");
		WSACleanup();
		return;
	}

	// �ڑ�����ǂݍ���
	ReadConnetProtocol(&m_ConnectProtocol);

	// �\�P�b�g����
	m_SockSend = socket(AF_INET, SOCK_DGRAM, 0);
	m_SockRecv = socket(AF_INET, SOCK_DGRAM, 0);

	// �A�h���X�^�C�v�ݒ�
	addr.sin_family	= AF_INET;

	// �|�[�g�ԍ��ݒ�
	addr.sin_port = htons(20010);

	// IP�A�h���X�ݒ�
	addr.sin_addr.s_addr = INADDR_ANY;

	// �o�C���h
	m_ifBindSuccess = bind(m_SockRecv, (sockaddr*)&addr, sizeof(addr));

	// �������I�����m
	m_ifInitialize = true;
}

//=============================================================================
//	�֐���	:Uninit
//	����	:����
//	�߂�l	:����
//	����	:�I���������s���B
//=============================================================================
void CNetwork::Uninit(void)
{
	// �\�P�b�g�I��
	if(m_SockSend) closesocket(m_SockSend);
	if(m_SockSend) closesocket(m_SockSend);

	// �v�h�m�r�n�b�j�㏈��
	WSACleanup();
}

//=============================================================================
//	�֐���	:Update
//	����	:����
//	�߂�l	:����
//	����	:�X�V�������s���B
//=============================================================================
void CNetwork::Update(void)
{
	
}

//=============================================================================
//	�֐���	:Draw
//	����	:����
//	�߂�l	:����
//	����	:�`�揈�����s���B
//=============================================================================
void CNetwork::Draw(void)
{
	CDebugProcGL::DebugProc("PLAYER_NUM:%d\n", m_PlayerNum);
	CDebugProcGL::DebugProc("LASTDATA:%s\n", m_LastMessage);
	//CDebugProcGL::DebugProc("BIND:%d\n", m_ifBindSuccess);
}

uint __stdcall CNetwork::ReceiveThread(void *p)
{
	while(1)
	{
		if(m_ifInitialize)
		{
			while(m_PlayerNum < 4)
			{
				// �N���C�A���g���
				sockaddr_in client;

				char data[1024] = { NULL };	// ��M�f�[�^


				// �N���C�A���g���̃T�C�Y�Z�b�g
				int len = sizeof(client);

				// �}�b�`���O�f�[�^��M
				recvfrom(m_SockRecv, data, sizeof(data), 0, (sockaddr*)&client, &len);

				// �}�b�`���O��t
				if(strcmp(data, "match") == 0)
				{
					// �����ڑ���̏ꍇ�J�E���g���Ȃ�
					int i = 0;
					for(i = 0 ; i < 4 ; i++)
					{
						if(m_AddrClient[i].sin_addr.s_addr == client.sin_addr.s_addr)
						{
							break;
						}
					}


					char buff[1024] = { NULL };

					if(i <= 3)
					{// ��x�ڑ����ꂽ�N���C�A���g�̏ꍇ�A���̃v���C���[�ԍ���ԐM����

						// �d�����Ă���v���C���[�ԍ����Z�b�g
						sprintf(buff, "matching %d", i);

						// �v���C���[�ԍ��𑗐M
						sendto(m_SockSend, buff, strlen(buff), 0, (sockaddr*)&m_AddrClient[i], len);
					}
					else
					{// �����łȂ��ꍇ�A���݂̃v���C���[�ԍ���ԐM����

						// �N���C�A���g���̓o�^
						m_AddrClient[m_PlayerNum]			= client;
						m_AddrClient[m_PlayerNum].sin_port	= htons(20010);

						// ���݂̃v���C���[�ԍ����Z�b�g
						sprintf(buff, "%d", m_PlayerNum);

						// �v���C���[�ԍ��𑗐M
						sendto(m_SockSend, buff, strlen(buff), 0, (sockaddr*)&m_AddrClient[m_PlayerNum], len);

						// �v���C���[���𑝂₷
						m_PlayerNum++;
					}
				}
			}

			while(1)
			{
				// �f�[�^��M
				ReceiveData();
			}
		}
	}

	return 0;
}

//=============================================================================
//	�֐���	:SendData
//	����	:char *format	->	���M�f�[�^
//	�߂�l	:����
//	����	:�f�[�^�̑��M���s���B
//=============================================================================
void CNetwork::SendData(char* format, ...)
{
	va_list list;
	char str[256];

	// �t�H�[�}�b�g�ϊ�
	va_start(list, format);
	vsprintf_s(str, format, list);
	va_end(list);

	// �f�[�^���M
	for(int i = 0 ; i < 4 ; i++)
	{
		sendto(m_SockSend, str, strlen(str) + 1, 0, (SOCKADDR*)&m_AddrClient[i], sizeof(m_AddrClient[i]));
	}
}

//=============================================================================
//	�֐���	:ReceiveData
//	����	:char *str	->	���M�f�[�^
//	�߂�l	:����
//	����	:�f�[�^�̑��M���s���B
//=============================================================================
void CNetwork::ReceiveData(void)
{
	// �N���C�A���g���
	sockaddr_in client;
	int len = sizeof(client);
	char data[1024] = { NULL };	// ��M�f�[�^

	// �f�[�^��M
	recvfrom(m_SockRecv, data, sizeof(data), 0, (sockaddr*)&client, &len);

	// �f�[�^�����M����Ă����ꍇ�L�^
	if(strcmp(data, ""))
	{
		strcpy(m_LastMessage, data);
	}
	
	DATA_TAG dataTag = DT_MAX;

	sscanf(data, "%d, ", &dataTag);
	RemoveDataTag(data);

	switch(dataTag)
	{
	case 0:	// �V�X�e�����b�Z�[�W
		// �Q�[���G���g���[�m�F
		if(!strcmp(data, "entry"))
		{
			char str[1024];

			sprintf(str, "%d %d", DT_PLAYER_NUM, m_PlayerNum);
			m_PlayerNum++;

			// �f�[�^���M
			//sendto(m_SockSend, str, strlen(str) + 1, 0, (SOCKADDR*)&m_AddrClient, sizeof(m_AddrClient));
		}
		break;

	case 1:
		SetPlayerData(data);
		break;

	default:
		break;
	}
}

//=============================================================================
//	�֐���	:SetPlayerData
//	����	:char *str	->	��M�f�[�^
//	�߂�l	:����
//	����	:��M�����v���C���[�̃f�[�^���Z�b�g����B
//=============================================================================
void CNetwork::SetPlayerData(char *str)
{/*
	CSceneModel	*player2 = CGame::GetPlayer2();
	VECTOR3		pos = VECTOR3::zero();

	// �Q�[�����[�h�̎��̂ݏ���
	if(CManager::GetModeState() == MODE_GAME)
	{
		// ��M�f�[�^����v���C���[���W���擾
		sscanf(str, "1, %f, %f, %f", &pos.x, &pos.y, &pos.z);

		// �擾�������W���Z�b�g
		player2->SetPos(pos);
	}*/
}

//=============================================================================
//	�֐���	:RemoveDataTag
//	����	:char *str	->	��M�f�[�^
//	�߂�l	:����
//	����	:��M�����v���C���[�̃f�[�^����^�O�����O���B
//=============================================================================
void CNetwork::RemoveDataTag(char *data)
{
	int offset = 0;

	for(; data[offset] != NULL ; offset++)
	{
		// �󔒂���������
		if(data[offset] == ' ')
		{
			// ��������o��
			strcpy(data, &data[offset + 1]);

			// NULL�ǉ�
			data[strlen(data)] = NULL;

			break;
		}
	}
}

//=============================================================================
//	�֐���	:ReadConnetProtocol
//	����	:CONNECT_PROTOCOL *cp(�R�l�N�g���̃|�C���^)
//	�߂�l	:����
//	����	:IPv4�ʐM�ɕK�v�ȏ����t�@�C������ǂݎ��B
//=============================================================================
void CNetwork::ReadConnetProtocol(CONNECT_PROTOCOL *cp)
{
	FILE	*fp;	// �t�@�C���|�C���^


	// �t�@�C���I�[�v��
	if((fp = fopen("./data/connectprotocol.txt", "rb")) == NULL)
	{// �t�@�C���̃I�[�v���Ɏ��s�����ꍇ
		exit(EXIT_FAILURE);
	}

	// ���ǂݎ��
	fscanf(fp, "SEND_ADDRESS:%s\nMCAST_ADDRESS:%s\nSEND_PORT:%d\nRECV_PORT:%d\n", cp->Addr, cp->MAddr, &cp->SendPort, &cp->RecvPort);

	// �t�@�C���N���[�Y
	fclose(fp);
}