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
int			CNetwork::m_PlayerNum = 0;
WSADATA		CNetwork::m_Wsadata;
int			CNetwork::m_Sts;
int			CNetwork::m_Errcode;
SOCKET		CNetwork::m_SockTCPRecv;
SOCKET		CNetwork::m_SockUDPSend;
sockaddr_in	CNetwork::m_AddrSend;
sockaddr_in	CNetwork::m_AddrClient[4];
CONNECT_PROTOCOL CNetwork::m_ConnectProtocol;
char		CNetwork::m_LastMessage[1024] = "NO DATA";
uint		CNetwork::m_thID;
HANDLE		CNetwork::m_hTh;
bool		CNetwork::m_ifInitialize = false;

//=============================================================================
//	�֐���	:Init
//	����	:����
//	�߂�l	:����
//	����	:�������������s���B
//=============================================================================
void CNetwork::Init(void)
{
	// ���X���b�h�N����
	m_hTh = (HANDLE)_beginthreadex(NULL, 0, ReceveThread, NULL, 0, &m_thID);

	WSADATA		wsadata;
	int			sts;
	int			errcode;
	sockaddr_in	addr;		// �A�h���X


							// �v�h�m�r�n�b�j��������
	sts = WSAStartup(MAKEWORD(2, 2), &wsadata);
	if(sts != 0) {
		errcode = WSAGetLastError();
		printf("WSAStartup�G���[�ł� %d \n", errcode);
		//return -1;
	}

	// �o�[�W�����`�F�b�N
	if(LOBYTE(wsadata.wVersion) != 2 ||
		HIBYTE(wsadata.wVersion) != 2) {
		printf("�o�[�W�����G���[�ł�\n");
		WSACleanup();
		//return -1;
	}

	// �\�P�b�g����
	m_SockTCPRecv = socket(AF_INET, SOCK_STREAM, 0);

	// �A�h���X�^�C�v�ݒ�
	addr.sin_family = AF_INET;

	// �|�[�g�ԍ��ݒ�
	addr.sin_port = htons(20000);

	// IP�A�h���X�ݒ�
	addr.sin_addr.s_addr = INADDR_ANY;

	// �o�C���h
	bind(m_SockTCPRecv, (sockaddr*)&addr, sizeof(addr));

	// �N���C�A���g����̐ڑ��҂�
	listen(m_SockTCPRecv, 5);

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
	if(m_SockTCPRecv) closesocket(m_SockTCPRecv);
	if(m_SockUDPSend) closesocket(m_SockUDPSend);
	//if(m_SockRecv) closesocket(m_SockRecv);

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
}

uint __stdcall CNetwork::ReceveThread(void *p)
{
	// �N���C�A���g�Ɛڑ�
	SOCKET sock;
	sockaddr_in client;
	int len;

	while(m_PlayerNum < 4)
	{
		if(m_ifInitialize)
		{
			len = sizeof(client);
			sock = accept(m_SockTCPRecv, (sockaddr*)&client, &len);

			// �����ڑ���̏ꍇ�J�E���g���Ȃ�
			int i;
			for(i = 0 ; i < 4 ; i++)
			{
				if(m_AddrClient[i].sin_addr.s_addr == client.sin_addr.s_addr)
				{
					break;
				}
			}

			
			char buff[1024] = { NULL };

			if(i < 4)
			{// ��x�ڑ����ꂽ�N���C�A���g�̏ꍇ�A���̃v���C���[�ԍ���ԐM����

				// �d�����Ă���v���C���[�ԍ����Z�b�g
				sprintf(buff, "%d", i);

				// �v���C���[�ԍ��𑗐M
				send(sock, buff, strlen(buff), 0);
			}
			else
			{// �����łȂ��ꍇ�A���݂̃v���C���[�ԍ���ԐM����

				// �N���C�A���g���̓o�^
				m_AddrClient[m_PlayerNum] = client;

				// ���݂̃v���C���[�ԍ����Z�b�g
				sprintf(buff, "%d", m_PlayerNum);

				// �v���C���[�ԍ��𑗐M
				send(sock, buff, strlen(buff), 0);

				// �v���C���[���𑝂₷
				m_PlayerNum++;
			}

			// �\�P�b�g�I��
			closesocket(sock);
		}
	}

	// ���������I�����Ă���ꍇ�̂ݏ���
	while(1)
	{
		if(m_ifInitialize)
		{
			// �f�[�^��M
			while(1)
			{
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
	sendto(m_SockUDPSend, str, strlen(str) + 1, 0, (SOCKADDR*)&m_AddrSend, sizeof(m_AddrSend));
}

//=============================================================================
//	�֐���	:ReceiveData
//	����	:char *str	->	���M�f�[�^
//	�߂�l	:����
//	����	:�f�[�^�̑��M���s���B
//=============================================================================
void CNetwork::ReceiveData(void)
{
	char data[1024] = { NULL };	// ��M�f�[�^

	// �f�[�^��M
	//if(recvfrom(m_SockRecv, data, strlen(data), 0, (sockaddr*)&m_AddrClient, &m_AddrLen) < 0)
	//if(recv(m_SockRecv, data, strlen(data), 0) < 0)
	{
		//perror("recvfrom");
	}

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