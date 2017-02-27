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
#include "fade.h"
#include "player.h"
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
char		CNetwork::m_ReceiveData[65535] = "";
char		CNetwork::m_LastMessage[65535] = "";
uint		CNetwork::m_thID;
HANDLE		CNetwork::m_hTh;

BULLETDATA	CNetwork::m_BulletInstance[PLAYER_NUM][BULLET_NUM_MAX];
vector<int> CNetwork::m_Ranking;

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
	addr.sin_family = AF_INET;
	m_AddrServer.sin_family = AF_INET;

	// �|�[�g�ԍ��ݒ�
	addr.sin_port = htons(20010);
	m_AddrServer.sin_port = htons(20010);

	// IP�A�h���X�ݒ�
	addr.sin_addr.s_addr = INADDR_ANY;
	//m_AddrServer.sin_addr.s_addr = inet_addr("127.0.0.1");
	m_AddrServer.sin_addr.s_addr = inet_addr("172.29.33.48");

	// �o�C���h
	bind(m_SockRecv, (sockaddr*)&addr, sizeof(addr));

	Clear();

	// �������I�����m
	m_ifInitialize = true;
	
	// �}�b�`���O�o�^
	connect(m_SockSend, (sockaddr*)&m_AddrServer, sizeof(m_AddrServer));
	//send(m_SockSend, "0, entry", strlen("0, entry") + 1, 0);
}

//=============================================================================
//	�֐���	:Init
//	����	:����
//	�߂�l	:����
//	����	:�������������s���B
//=============================================================================
void CNetwork::Clear(void)
{
	for(int i = 0 ; i < PLAYER_NUM ; i++)
	{
		for(int j = 0 ; j < BULLET_NUM_MAX ; j++)
		{
			m_BulletInstance[i][j].Instance	= NULL;
			m_BulletInstance[i][j].Use		= false;
			m_BulletInstance[i][j].IfUninit	= false;
		}
	}

	m_Ranking.clear();
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
	//CDebugProcGL::DebugProc("LASTDATA:%s\n", m_LastMessage);
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
	send(m_SockSend, str, strlen(str) + 1, 0);
	//sendto(m_SockSend, str, strlen(str) + 1, 0, (SOCKADDR*)&m_AddrServer, sizeof(m_AddrServer));

	memset(str, NULL, sizeof(str));
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
	recv(m_SockSend, m_ReceiveData, sizeof(m_ReceiveData), 0);
	//recvfrom(m_SockRecv, m_ReceiveData, sizeof(m_ReceiveData), 0, (sockaddr*)&m_AddrServer, &len);
	
	// �f�[�^�����M����Ă����ꍇ�L�^
	if(strcmp(m_ReceiveData, ""))
	{
		strcpy(m_LastMessage, m_ReceiveData);
	}
	
	DATA_TAG dataTag = DT_MAX;

	sscanf(m_ReceiveData, "TAG:%d, ", &dataTag);
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
	case 1:
		SetPlayerData();
		break;
	case 2:
		CreateBullet();
		break;
	case 3:
		DeleteBullet();
		break;

	case 10:
		PlayerDamage();
		break;

	case 100:
		GameEnd();
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
void CNetwork::SetPlayerData(void)
{
	vector<CPlayer*>	player = CGame::GetPlayer();
	VECTOR3 pos[4] = { VEC3_ZERO };
	VECTOR3 rot[4] = { VEC3_ZERO };
	VECTOR3 vec[4] = { VEC3_ZERO };

	// ��M�f�[�^����v���C���[���W���擾
	sscanf(m_ReceiveData,
		"POS(%f,%f,%f), ROT(%f,%f,%f), VEC(%f,%f,%f), "
		"POS(%f,%f,%f), ROT(%f,%f,%f), VEC(%f,%f,%f), "
		"POS(%f,%f,%f), ROT(%f,%f,%f), VEC(%f,%f,%f), "
		"POS(%f,%f,%f), ROT(%f,%f,%f), VEC(%f,%f,%f)",
		&pos[0].x, &pos[0].y, &pos[0].z, &rot[0].x, &rot[0].y, &rot[0].z, &vec[0].x, &vec[0].y, &vec[0].z,
		&pos[1].x, &pos[1].y, &pos[1].z, &rot[1].x, &rot[1].y, &rot[1].z, &vec[1].x, &vec[1].y, &vec[1].z,
		&pos[2].x, &pos[2].y, &pos[2].z, &rot[2].x, &rot[2].y, &rot[2].z, &vec[2].x, &vec[2].y, &vec[2].z,
		&pos[3].x, &pos[3].y, &pos[3].z, &rot[3].x, &rot[3].y, &rot[3].z, &vec[3].x, &vec[3].y, &vec[3].z);

	// �擾�������W���Z�b�g
	for(int i = 0 ; i < (int)player.size() ; i++)
	{
		if(i != CManager::GetWhatPlayer())
		{
			player[i]->SetPos(pos[i]);
			//player[i]->SetRot(rot[i]);
			player[i]->SetRotMove(rot[i]);
			//player[i]->SetVec(vec[i]);
		}
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
	int playerNum = 0, bulletNum = 0;

	// ��M�f�[�^����f�[�^���擾
	sscanf(m_ReceiveData, "%d, %d, POS(%f, %f, %f), ROT(%f, %f, %f), %f",
		&playerNum, &bulletNum, &pos.x, &pos.y, &pos.z, &rot.x, &rot.y, &rot.z, &speed);

	if(playerNum != CManager::GetWhatPlayer())
	{
		// �擾�����f�[�^���Z�b�g
		m_BulletInstance[playerNum][bulletNum].Instance = CBullet::Create(playerNum, bulletNum, pos, rot, speed, playerNum);
		m_BulletInstance[playerNum][bulletNum].Use = true;
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
	int playerNum = 0, bulletNum = 0;

	// ��M�f�[�^����f�[�^���擾
	sscanf(m_ReceiveData, "%d, %d",	&playerNum, &bulletNum);

	if(m_BulletInstance[playerNum][bulletNum].Use)
	{
		m_BulletInstance[playerNum][bulletNum].Instance->SetLife(-100);
	}
}

//=============================================================================
//	�֐���	:PlayerDamage
//	����	:����
//	�߂�l	:����
//	����	:�Q�[���̏I�����b�Z�[�W�Ƌ��Ƀ����L���O�����N���C�A���g�Ɉ�đ��M�B
//=============================================================================
void CNetwork::PlayerDamage(void)
{
	int playerNum = -1;

	// ��M�f�[�^����f�[�^���擾
	sscanf(m_ReceiveData, "%d", &playerNum);

	if(playerNum >= 0)
	{
		CGame::GetPlayer()[playerNum]->HitBullet();
	}
}

//=============================================================================
//	�֐���	:GameEnd
//	����	:����
//	�߂�l	:����
//	����	:�Q�[���̏I�����b�Z�[�W�Ƌ��Ƀ����L���O�����N���C�A���g�Ɉ�đ��M�B
//=============================================================================
void CNetwork::GameEnd(void)
{
	int ranking[PLAYER_NUM];

	// ��M�f�[�^����f�[�^���擾
	sscanf(m_ReceiveData, "%d, %d, %d, %d", &ranking[0], &ranking[1], &ranking[2], &ranking[3]);

	m_Ranking.push_back(ranking[0]);
	m_Ranking.push_back(ranking[1]);
	m_Ranking.push_back(ranking[2]);
	m_Ranking.push_back(ranking[3]);

	// ���U���g��
	CFade::Start(new CResult, MODE_RESULT, FS_OUT);
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