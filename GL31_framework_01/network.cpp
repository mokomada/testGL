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
#include "game.h"
#include "sceneModel.h"
#include <process.h>
#include <mbstring.h>

#pragma comment(lib, "ws2_32.lib")
unsigned int __stdcall thread1(void *);

//=============================================================================
//	�ÓI�����o�ϐ�
//=============================================================================
bool		CNetwork::m_ifInitialize = false;
CONNECT_PROTOCOL	CNetwork::m_ConnectProtocol;

SOCKET		CNetwork::m_SockSend;
SOCKET		CNetwork::m_SockRecv;
sockaddr_in	CNetwork::m_AddrServer;
sockaddr_in	CNetwork::m_AddrRecv;
char		CNetwork::m_LastMessage[1024] = "NO DATA";
uint		CNetwork::m_thID;
HANDLE		CNetwork::m_hTh;

//=============================================================================
//	�֐���	:Init
//	����	:����
//	�߂�l	:����
//	����	:�������������s���B
//=============================================================================
void CNetwork::Init(void)
{
	WSADATA		wsadata;
	int			sts;
	int			errcode;
	SOCKET		sock;		// �\�P�b�g

	// ���X���b�h�N����
	m_hTh = (HANDLE)_beginthreadex(NULL, 0, ReceveThread, NULL, 0, &m_thID);

	// �v�h�m�r�n�b�j��������
	sts = WSAStartup(MAKEWORD(2, 2), &wsadata);
	if(sts != 0)
	{
		errcode = WSAGetLastError();
		printf("WSAStartup�G���[�ł� %d \n", errcode);
		//return -1;
	}

	// �o�[�W�����`�F�b�N
	if(LOBYTE(wsadata.wVersion) != 2 || HIBYTE(wsadata.wVersion) != 2)
	{
		printf("�o�[�W�����G���[�ł�\n");
		WSACleanup();
		//return -1;
	}

	// ���M����ǂݎ��
	ReadConnetProtocol(&m_ConnectProtocol);
	
	// �\�P�b�g����
	sock = socket(AF_INET, SOCK_STREAM, 0);
	m_SockSend = socket(AF_INET, SOCK_DGRAM, 0);

	// �A�h���X�^�C�v�ݒ�
	m_AddrServer.sin_family = AF_INET;

	// �|�[�g�ԍ��ݒ�
	m_AddrServer.sin_port = htons(20000);

	// IP�A�h���X�ݒ�
	m_AddrServer.sin_addr.s_addr = inet_addr("127.0.0.1");

	// �T�[�o�ɐڑ�
	connect(sock, (sockaddr*)&m_AddrServer, sizeof(m_AddrServer));

	char data[1024];
	memset(data, 0, sizeof(data));

	// �f�[�^��M
	recv(sock, data, sizeof(data), 0);

	if(strcmp(data, ""))
	{
		int whatplayer = -1;
		sscanf(data, "%d", &whatplayer);
		if(whatplayer >= 0)
		{
			CManager::SetWhatPlayer(whatplayer);
		}
	}

	// �\�P�b�g�I��
	closesocket(sock);


	// �\�P�b�g�I��
	closesocket(sock);

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
	//if(m_SockTCP)	closesocket(m_SockTCP);
	//if(m_SockSend)	closesocket(m_SockSend);
	//if(m_SockRecv)	closesocket(m_SockRecv);

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
#ifdef _DEBUG
	CDebugProcGL::DebugProc("LASTDATA:%s\n", m_LastMessage);
#endif
}

uint __stdcall CNetwork::ReceveThread(void *p)
{
	// �f�[�^��M
	while(1)
	{
		// ���������I�����Ă���ꍇ�̂ݏ���
		if(m_ifInitialize)
		{
			//ReceiveData();
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
	//sendto(m_SockSend, str, strlen(str) + 1, 0, (SOCKADDR*)&m_AddrServer, sizeof(m_AddrServer));
}

//=============================================================================
//	�֐���	:ReceiveData
//	����	:char *str	->	���M�f�[�^
//	�߂�l	:����
//	����	:�f�[�^�̑��M���s���B
//=============================================================================
void CNetwork::ReceiveData(void)
{
	char		data[1024] = { NULL };	// ��M�f�[�^

	
	// �f�[�^��M
	//recv(m_SockTCP, data, strlen(data), 0);
	/*if(recvfrom(m_SockRecv, data, strlen(data), 0, (sockaddr*)&m_AddrClient, &m_AddrLen) < 0)
	{
		perror("recvfrom");
	}*/

	// �f�[�^�����M����Ă����ꍇ�L�^
	if(strcmp(data, ""))
	{
		strcpy(m_LastMessage, data);
	}
	
	DATA_TAG dataTag = DT_MAX;

	sscanf(data, "%d, ", &dataTag);
	RemoveDataTag(data);

	int whatPlayer = -1;

	switch(dataTag)
	{
	case DT_PLAYER_NUM:
		sscanf(data, "%d", &whatPlayer);
		CManager::SetWhatPlayer(whatPlayer);
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