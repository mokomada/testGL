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

//=============================================================================
//	�ÓI�����o�ϐ�
//============================================================================
//uint __stdcall CNetwork::ReceveThread(void *);
CONNECT_PROTOCOL	CNetwork::m_ConnectProtocol;

bool		CNetwork::m_ifInitialize	= false;
bool		CNetwork::m_ifMatched		= false;

SOCKET		CNetwork::m_SockSend;
SOCKET		CNetwork::m_SockRecv;
sockaddr_in	CNetwork::m_AddrServer;
char		CNetwork::m_ReceiveData[65535] = "NO DATA";
char		CNetwork::m_LastMessage[65535] = "NO DATA";
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
	sockaddr_in	addr;

	m_ifInitialize	= false;
	m_ifMatched		= false;

	// ���X���b�h�N����
	m_hTh = (HANDLE)_beginthreadex(NULL, 0, ReceveThread, NULL, 0, &m_thID);

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

	// ���M����ǂݎ��
	ReadConnetProtocol(&m_ConnectProtocol);
	
	// �\�P�b�g����
	m_SockSend = socket(AF_INET, SOCK_DGRAM, 0);
	m_SockRecv = socket(AF_INET, SOCK_DGRAM, 0);
	

	// �A�h���X�^�C�v�ݒ�
	addr.sin_family = AF_INET;
	m_AddrServer.sin_family = AF_INET;

	// �|�[�g�ԍ��ݒ�
	addr.sin_port = htons(20010);
	m_AddrServer.sin_port = htons(20010);

	// IP�A�h���X�ݒ�
	addr.sin_addr.s_addr = INADDR_ANY;
	//m_AddrServer.sin_addr.s_addr = inet_addr(m_ConnectProtocol.pAddr);
	m_AddrServer.sin_addr.s_addr = inet_addr("192.168.11.6");

	// �o�C���h
	bind(m_SockRecv, (sockaddr*)&addr, sizeof(addr));
	
	// �}�b�`���O�o�^
	sendto(m_SockSend, "0, entry", strlen("0, entry") + 1, 0, (sockaddr*)&m_AddrServer, sizeof(m_AddrServer));
		
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
	if(m_SockSend)	closesocket(m_SockSend);

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
	char str[65535];

	// �t�H�[�}�b�g�ϊ�
	va_start(list, format);
	vsprintf_s(str, format, list);
	va_end(list);

	// �f�[�^���M
	m_AddrServer.sin_port = htons(20010);
	sendto(m_SockSend, str, strlen(str) + 1, 0, (SOCKADDR*)&m_AddrServer, sizeof(m_AddrServer));
}

//=============================================================================
//	�֐���	:ReceiveData
//	����	:char *str	->	���M�f�[�^
//	�߂�l	:����
//	����	:�f�[�^�̑��M���s���B
//=============================================================================
void CNetwork::ReceiveData(void)
{
	// �T�[�o�A�h���X�̃T�C�Y�Z�b�g
	int len = sizeof(m_AddrServer);

	// �f�[�^��M
	recvfrom(m_SockRecv, m_ReceiveData, sizeof(m_ReceiveData), 0, (sockaddr*)&m_AddrServer, &len);
	
	// �f�[�^�����M����Ă����ꍇ�L�^
	if(strcmp(m_ReceiveData, ""))
	{
		strcpy(m_LastMessage, m_ReceiveData);
	}
	
	DATA_TAG dataTag = DT_MAX;

	sscanf(m_ReceiveData, "%d, ", &dataTag);
	RemoveDataTag(m_ReceiveData);

	int whatPlayer = -1;

	switch(dataTag)
	{
	case 0:	// �}�b�`���O
		if(!m_ifMatched)
		{
			int whatplayer = -1;
			sscanf(m_ReceiveData, "%d", &whatplayer);
			if(whatplayer >= 0)
			{
				CManager::SetWhatPlayer(whatplayer);

				m_ifMatched = true;
			}
		}
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
	fscanf(fp, "SEND_ADDRESS:%s", cp->Addr);
	cp->pAddr = cp->Addr;

	// �t�@�C���N���[�Y
	fclose(fp);
}