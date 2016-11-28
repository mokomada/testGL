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

#pragma comment(lib, "ws2_32.lib")
unsigned int __stdcall thread1(void *);

//=============================================================================
//	�ÓI�����o�ϐ�
//=============================================================================
WSADATA		CNetwork::m_Wsadata;
int			CNetwork::m_Sts;
int			CNetwork::m_Errcode;
SOCKET		CNetwork::m_Sock;
sockaddr_in	CNetwork::m_Addr;
int			CNetwork::m_AddrLen;
sockaddr_in	CNetwork::m_AddrClient;
uint		CNetwork::thID1;
HANDLE		CNetwork::hTh1;
bool		CNetwork::m_IfInitialize = false;

//=============================================================================
//	�֐���	:Init
//	����	:����
//	�߂�l	:����
//	����	:�������������s���B
//=============================================================================
void CNetwork::Init(void)
{
	// ���X���b�h�N����
	hTh1 = (HANDLE)_beginthreadex(NULL, 0, thread1, NULL, 0, &thID1);


	// �v�h�m�r�n�b�j��������
	m_Sts = WSAStartup(MAKEWORD(2, 2), &m_Wsadata);
	if(m_Sts != 0) {
		m_Errcode = WSAGetLastError();
		printf("WSAStartup�G���[�ł� %d \n", m_Errcode);
		//return -1;
	}

	// �o�[�W�����`�F�b�N
	if(LOBYTE(m_Wsadata.wVersion) != 2 ||
		HIBYTE(m_Wsadata.wVersion) != 2) {
		printf("�o�[�W�����G���[�ł�\n");
		WSACleanup();
		//return -1;
	}

	// �\�P�b�g����
	m_Sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	// �|�[�g�ԍ��ݒ�
	m_Addr.sin_port = htons(20000);

	// �A�h���X�^�C�v�ݒ�
	m_Addr.sin_family = AF_INET;

	// IP�A�h���X�ݒ�
	m_Addr.sin_addr.s_addr = inet_addr("239.0.0.1");


	int value = 1;

	// �u���[�h�L���X�g����
	setsockopt(m_Sock, SOL_SOCKET, SO_BROADCAST, (char *)&value, sizeof(value));

	// �������I�����m
	m_IfInitialize = true;
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
	closesocket(m_Sock);

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

}

unsigned int __stdcall thread1(void *p)
{
	// �f�[�^��M
	while(1)
	{
		// ���������I�����Ă���ꍇ�̂ݏ���
		if(CNetwork::m_IfInitialize)
		{
			CNetwork::ReceiveData();
		}
	}

	return 0;
}

//=============================================================================
//	�֐���	:SendData
//	����	:char *str	->	���M�f�[�^
//	�߂�l	:����
//	����	:�f�[�^�̑��M���s���B
//=============================================================================
void CNetwork::SendData(char *str)
{
	// �f�[�^���M
	sendto(m_Sock, str, strlen(str) + 1, 0, (SOCKADDR*)&m_Addr, sizeof(m_Addr));
}

//=============================================================================
//	�֐���	:ReceiveData
//	����	:char *str	->	���M�f�[�^
//	�߂�l	:����
//	����	:�f�[�^�̑��M���s���B
//=============================================================================
void CNetwork::ReceiveData(void)
{
	char		str[1024] = { NULL };	// ��M�f�[�^

	// �o�C���h
	bind(m_Sock, (sockaddr*)&m_Addr, sizeof(m_Addr));

	// �}���`�L���X�g�O���[�v�ɎQ��
	ip_mreq mreq;

	memset(&mreq, 0, sizeof(mreq));
	mreq.imr_multiaddr.s_addr = inet_addr("239.0.0.1");
	mreq.imr_interface.s_addr = INADDR_ANY;
	setsockopt(m_Sock, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char*)&mreq, sizeof(mreq));


	// �f�[�^��M�ҋ@
	m_AddrLen = sizeof(m_AddrClient);
	// �f�[�^��M
	recvfrom(m_Sock, str, strlen(str), 0, (sockaddr*)&m_AddrClient, &m_AddrLen);
	
	int dataPt = 0;

	sscanf(str, "%d, ", &dataPt);

	switch(dataPt)
	{
	case 1:
		SetPlayerData(str);
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
{
	CSceneModel	*player2 = CGame::GetPlayer2();
	VECTOR3		pos = VECTOR3::zero();

	// �Q�[�����[�h�̎��̂ݏ���
	if(CManager::GetModeState() == MODE_GAME)
	{
		// ��M�f�[�^����v���C���[���W���擾
		sscanf(str, "1, %f, %f, %f", &pos.x, &pos.y, &pos.z);

		// �擾�������W���Z�b�g
		player2->SetPos(pos);
	}
}