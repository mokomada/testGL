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
#include "player.h"
#include <process.h>
#include <mbstring.h>
#ifdef _OPENMP
#include <omp.h>
#endif

#pragma comment(lib, "ws2_32.lib")

//=============================================================================
//	�ÓI�����o�ϐ�
//=============================================================================
CONNECT_PROTOCOL CNetwork::m_ConnectProtocol = { "127.0.0.1", "239.0.0.1", 20000, 20000 };

int			CNetwork::m_PlayerNum = 0;
//CLIENT		CNetwork::m_Client[PLAYER_NUM];
SOCKET		CNetwork::m_ClientSock[PLAYER_NUM];
SOCKET		CNetwork::m_SockSend;
SOCKET		CNetwork::m_SockRecv;
sockaddr_in	CNetwork::m_AddrClient[4];
sockaddr_in	CNetwork::m_RecvClient;
char		CNetwork::m_ReceiveData[65535] = "";
char		CNetwork::m_LastMessage[65535] = "";
uint		CNetwork::m_thIDMatch;
HANDLE		CNetwork::m_hThMatch;
uint		CNetwork::m_thID;
HANDLE		CNetwork::m_hTh;
bool		CNetwork::m_ifInitialize = false;
int			CNetwork::m_ifBindSuccess = -1;

BULLETDATA	CNetwork::m_BulletInstance[PLAYER_NUM][BULLET_NUM_MAX];

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
	if(1)
	{
		m_SockSend = socket(AF_INET, SOCK_STREAM, 0);
		m_SockRecv = socket(AF_INET, SOCK_STREAM, 0);
	}
	else
	{
		m_SockSend = socket(AF_INET, SOCK_DGRAM, 0);
		m_SockRecv = socket(AF_INET, SOCK_DGRAM, 0);
	}

	// �A�h���X�^�C�v�ݒ�
	addr.sin_family	= AF_INET;

	// �|�[�g�ԍ��ݒ�
	addr.sin_port = htons(20010);

	// IP�A�h���X�ݒ�
	addr.sin_addr.s_addr = INADDR_ANY;

	// �o�C���h
	m_ifBindSuccess = bind(m_SockRecv, (sockaddr*)&addr, sizeof(addr));

	// �����ڑ��N���C�A���g���ݒ�
	listen(m_SockRecv, 5);

	for(int i = 0 ; i < PLAYER_NUM ; i++)
	{
		for(int j = 0 ; j < BULLET_NUM_MAX ; j++)
		{
			m_BulletInstance[i][j].Instance	= NULL;
			m_BulletInstance[i][j].Use		= false;
			m_BulletInstance[i][j].IfUninit	= false;
		}
	}

	// ���X���b�h�N����
	m_hThMatch = (HANDLE)_beginthreadex(NULL, 0, MatchThread, NULL, 0, &m_thIDMatch);

	// �������I�����m
	m_ifInitialize = true;
}

//=============================================================================
//	�֐���	:ReceiveThread
//	����	:void* p
//	�߂�l	:����
//	����	:�f�[�^��M�X���b�h�B
//=============================================================================
uint __stdcall CNetwork::MatchThread(void* p)
{
	int len;
	sockaddr_in addr;

	while(m_PlayerNum < PLAYER_NUM)
	{
		len = sizeof(m_AddrClient[m_PlayerNum]);

		m_ClientSock[m_PlayerNum] = accept(m_SockRecv, (sockaddr*)&addr, &len);

		// �����ڑ���̏ꍇ�J�E���g���Ȃ�
		int i = 0;
		for(i = 0 ; i < m_PlayerNum ; i++)
		{
			if(m_AddrClient[i].sin_addr.s_addr == addr.sin_addr.s_addr)
			{
				break;
			}
		}

		char buff[1024] ={ NULL };

		if(i < m_PlayerNum)
		{// ��x�ڑ����ꂽ�N���C�A���g�̏ꍇ�A���̃v���C���[�ԍ���ԐM����

			// �d�����Ă���v���C���[�ԍ����Z�b�g
			sprintf(buff, "0, %d", i);

			// �v���C���[�ԍ��𑗐M
			send(m_ClientSock[i], buff, strlen(buff), 0);
		}
		else
		{// �����łȂ��ꍇ�A���݂̃v���C���[�ԍ���ԐM����

			// �N���C�A���g���̓o�^
			m_AddrClient[m_PlayerNum] = addr;

			// ���݂̃v���C���[�ԍ����Z�b�g
			sprintf(buff, "0, %d", m_PlayerNum);

			// �v���C���[�ԍ��̃Z�b�g
			send(m_ClientSock[m_PlayerNum], buff, strlen(buff), 0);

			m_PlayerNum++;
		}
	}

	return 0;
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
	VECTOR3 pos[PLAYER_NUM] = { VEC3_ZERO, VEC3_ZERO, VEC3_ZERO, VEC3_ZERO};
	VECTOR3 rot[PLAYER_NUM] = { VEC3_ZERO, VEC3_ZERO, VEC3_ZERO, VEC3_ZERO };
	VECTOR3 vec[PLAYER_NUM] = { VEC3_ZERO, VEC3_ZERO, VEC3_ZERO, VEC3_ZERO };

	if(CManager::GetModeState() == MODE_GAME)
	{
		for(int i = 0 ; i < m_PlayerNum ; i++)
		{
			pos[i] = CGame::GetPlayer()[i]->GetPos();
			rot[i] = CGame::GetPlayer()[i]->GetRot();
			vec[i] = CGame::GetPlayer()[i]->GetVec();
		}

		SendData("1, POS(%.1f,%.1f,%.1f), ROT(%.1f,%.1f,%.1f), VEC(%.1f,%.1f,%.1f), "
			"POS(%.1f,%.1f,%.1f), ROT(%.1f,%.1f,%.1f), VEC(%.1f,%.1f,%.1f), "
			"POS(%.1f,%.1f,%.1f), ROT(%.1f,%.1f,%.1f), VEC(%.1f,%.1f,%.1f), "
			"POS(%.1f,%.1f,%.1f), ROT(%.1f,%.1f,%.1f), VEC(%.1f,%.1f,%.1f)",

			pos[0].x, pos[0].y, pos[0].z,
			rot[0].x, rot[0].y, rot[0].z,
			vec[0].x, vec[0].y, vec[0].z,

			pos[1].x, pos[1].y, pos[1].z,
			rot[1].x, rot[1].y, rot[1].z,
			vec[1].x, vec[1].y, vec[1].z,

			pos[2].x, pos[2].y, pos[2].z,
			rot[2].x, rot[2].y, rot[2].z,
			vec[2].x, vec[2].y, vec[2].z,

			pos[3].x, pos[3].y, pos[3].z,
			rot[3].x, rot[3].y, rot[3].z,
			vec[3].x, vec[3].y, vec[3].z);
	}
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
	for(int i = 0 ; i < PLAYER_NUM ; i++)
	{
		send(m_ClientSock[m_PlayerNum], str, strlen(str) + 1, 0);
	}
}

//=============================================================================
//	�֐���	:ReceiveThread
//	����	:void* p
//	�߂�l	:����
//	����	:�f�[�^��M�X���b�h�B
//=============================================================================
uint __stdcall CNetwork::ReceiveThread(void* p)
{
	while(1)
	{
		if(m_ifInitialize)
		{
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
//	�֐���	:ReceiveData
//	����	:char *str	->	���M�f�[�^
//	�߂�l	:����
//	����	:�f�[�^�̑��M���s���B
//=============================================================================
void CNetwork::ReceiveData(void)
{
	// �N���C�A���g���
	int len = sizeof(m_RecvClient);

	// �f�[�^��M
//#pragma omp parallel for
	for(int i = 0 ; i < m_PlayerNum ; i++)
	{
		if(CheckReceivable(m_ClientSock[i]))
		{
			recv(m_ClientSock[i], m_ReceiveData, sizeof(m_ReceiveData), 0);
		}
	}
	//recvfrom(m_SockRecv, m_ReceiveData, sizeof(m_ReceiveData), 0, (sockaddr*)&m_RecvClient, &len);

	// �f�[�^�����M����Ă����ꍇ�L�^
	if(strcmp(m_ReceiveData, ""))
	{
		strcpy(m_LastMessage, m_ReceiveData);
	}
	
	DATA_TAG dataTag = DT_MAX;

	sscanf(m_ReceiveData, "%d, ", &dataTag);
	RemoveDataTag(m_ReceiveData);

	switch(dataTag)
	{
	case 0:	// �V�X�e�����b�Z�[�W
		// �Q�[���G���g���[�m�F
		if(!strcmp(m_ReceiveData, "entry"))
		{
			if(m_PlayerNum < PLAYER_NUM)
			{
				Matching();
			}
		}
		break;

	case 1:	// �v���C���[�f�[�^
		SetPlayerData();
		break;

	case 2:	// �v���C���[�f�[�^
		//CreateBullet();
		break;

	default:
		break;
	}
}

/* �m���u���b�N��recv���s���邩�`�F�b�N���� */
int CNetwork::CheckReceivable(int fd)
{
	fd_set fdset;
	int re;
	struct timeval timeout;
	FD_ZERO(&fdset);
	FD_SET(fd, &fdset);

	/* timeout�͂O�b�B�܂�select�͂����߂��Ă� �� */
	timeout.tv_sec = 0;
	timeout.tv_usec = 0;

	/* read�ł��邩�`�F�b�N */
	re = select(fd + 1, &fdset, NULL, NULL, &timeout);

	return (re == 1) ? TRUE : FALSE;
}

//=============================================================================
//	�֐���	:Matching
//	����	:����
//	�߂�l	:����
//	����	:�}�b�`���O�������s���B
//=============================================================================
void CNetwork::Matching(void)
{
	// �����ڑ���̏ꍇ�J�E���g���Ȃ�
	int i = 0;
	for(i = 0 ; i < PLAYER_NUM ; i++)
	{
		if(m_AddrClient[i].sin_addr.s_addr == m_RecvClient.sin_addr.s_addr)
		{
			break;
		}
	}


	char buff[1024] ={ NULL };

	if(i <= 3)
	{// ��x�ڑ����ꂽ�N���C�A���g�̏ꍇ�A���̃v���C���[�ԍ���ԐM����

		// �d�����Ă���v���C���[�ԍ����Z�b�g
		sprintf(buff, "0, %d", i);

		// �v���C���[�ԍ��𑗐M
		sendto(m_SockSend, buff, strlen(buff), 0, (sockaddr*)&m_AddrClient[i], sizeof(m_AddrClient));
	}
	else
	{// �����łȂ��ꍇ�A���݂̃v���C���[�ԍ���ԐM����

		// �N���C�A���g���̓o�^
		m_AddrClient[m_PlayerNum]			= m_RecvClient;
		m_AddrClient[m_PlayerNum].sin_port	= htons(20010);

		// ���݂̃v���C���[�ԍ����Z�b�g
		sprintf(buff, "%d", m_PlayerNum);

		// �v���C���[�ԍ��𑗐M
		sendto(m_SockSend, buff, strlen(buff), 0, (sockaddr*)&m_AddrClient[m_PlayerNum], sizeof(m_AddrClient));

		// �v���C���[���𑝂₷
		m_PlayerNum++;
	}
}

//=============================================================================
//	�֐���	:SetPlayerData
//	����	:char *str	->	��M�f�[�^
//	�߂�l	:����
//	����	:��M�����v���C���[�̃f�[�^���Z�b�g����B
//=============================================================================
void CNetwork::SetPlayerData(void)
{
	vector<CPlayer*>	player = CGame::GetPlayer();
	int					num = 0;
	VECTOR3				pos = VEC3_ZERO;
	VECTOR3				rot = VEC3_ZERO;
	VECTOR3				vec = VEC3_ZERO;


	// ��M�f�[�^����f�[�^���擾
	sscanf(m_ReceiveData, "%d, %f, %f, %f, %f, %f, %f, %f, %f, %f",
		&num, &pos.x, &pos.y, &pos.z, &rot.x, &rot.y, &rot.z, &vec.x, &vec.y, &vec.z);

	if(num < m_PlayerNum)
	{
		// �擾�����f�[�^���Z�b�g
		player[num]->SetPos(pos);
		player[num]->SetRot(rot);
		//player[i]->SetVec(vec);
	}
}

//=============================================================================
//	�֐���	:CreateBullet
//	����	:����
//	�߂�l	:����
//	����	:�e�̃f�[�^�𐶐��A�������J�n����B
//=============================================================================
void CNetwork::CreateBullet(void)
{
	vector<CPlayer*>	player	= CGame::GetPlayer();
	VECTOR3				pos		= VEC3_ZERO;
	VECTOR3				rot		= VEC3_ZERO;
	float				speed	= 0.0f;


	for(int i = 0 ; i < PLAYER_NUM ; i++)
	{
		if(m_AddrClient[i].sin_addr.s_addr == m_RecvClient.sin_addr.s_addr)
		{
			// ��M�f�[�^����f�[�^���擾
			sscanf(m_ReceiveData, "%f, %f, %f, %f, %f, %f, %f",
				&pos.x, &pos.y, &pos.z, &rot.x, &rot.y, &rot.z, &speed);

			// �擾�����f�[�^���Z�b�g
			for(int j = 0 ; j < BULLET_NUM_MAX ; j++)
			{
				if(m_BulletInstance[i][j].Use = false)
				{
					m_BulletInstance[i][j].Instance = CBullet::Create(pos, rot, speed, i);
					m_BulletInstance[i][j].Use = true;
				}
			}
		}
	}
}

//=============================================================================
//	�֐���	:DeleteBullet
//	����	:����
//	�߂�l	:����
//	����	:��M�����v���C���[�̃f�[�^���Z�b�g����B
//=============================================================================
void CNetwork::DeleteBullet(void)
{

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