#ifndef _NETWORK_H_
#define _NETWORK_H_
//=============================================================================
//
//	�^�C�g��	�w�b�_�t�@�C��(network.cpp)
//	�t�@�C����	network.h
//	�쐬��		AT13A284_07 �r�c�B��
//	�쐬��		2016/11/14
//
//=============================================================================
#include "number.h"
#include "bullet.h"

//=============================================================================
//	�}�N����`
//=============================================================================
const int PLAYER_NUM		= 4;
const int BULLET_NUM_MAX	= 20;

//=============================================================================
//	�\����
//=============================================================================
typedef enum {
	DT_ENTRY = 0,
	DT_PLAYER_NUM,
	DT_PLAYER,
	DT_BULLET,
	DT_MAX
} DATA_TAG;

typedef struct {
	char	Addr[16];	// �ʐM��IP�A�h���X
	char	MAddr[16];	// �}���`�L���X�g��IP�A�h���X
	int		SendPort;	// ���M�|�[�g
	int		RecvPort;	// ��M�|�[�g
} CONNECT_PROTOCOL;		// �ʐM���

typedef struct {
	SOCKET		Sock;	// TCP�\�P�b�g
	sockaddr_in	Addr;	// �A�h���X���
} CLIENT;				// �N���C�A���g���

typedef struct {
	CBullet*	Instance;
	bool		IfUninit;
	bool		Use;
}BULLETDATA;

//=============================================================================
//	�N���X��`
//=============================================================================
class CNetwork
{
public:
	static uint __stdcall MatchThread(void*);
	static uint __stdcall ReceiveThread(void*);

	static void	Init(void);
	static void	Uninit(void);
	static void	Update(void);
	static void	Draw(void);

	static void SendData(char* format, ...);
	static void ReceiveData(void);

	static bool	m_ifInitialize;	// Init()���I���������ǂ���

	static BULLETDATA m_BulletInstance[PLAYER_NUM][BULLET_NUM_MAX];

private:
	static void Matching(int playerNum);
	static void	SetPlayerData(void);
	static void	CreateBullet(void);
	static void	DeleteBullet(void);
	static void RemoveDataTag(char* data);
	static void	ReadConnetProtocol(CONNECT_PROTOCOL* cp);
	static int CheckReceivable(int fd);

	static int			m_PlayerNum;	// �v���C���[��
	static CONNECT_PROTOCOL	m_ConnectProtocol;	// ���M����

	//static CLIENT		m_ClientSock[PLAYER_NUM];		// �N���C�A���g���
	static SOCKET		m_ClientSock[PLAYER_NUM];		// �N���C�A���g���
	static SOCKET		m_SockSend;					// UDP�\�P�b�g
	static SOCKET		m_SockRecv;					// UDP�\�P�b�g
	static sockaddr_in	m_AddrClient[PLAYER_NUM];	// ���M�A�h���X���
	static sockaddr_in	m_RecvClient;				// ��M�����f�[�^�̑��M�����
	static char			m_ReceiveData[65535];		// ��M�f�[�^
	static char			m_LastMessage[65535];		// �Ō�ɑ��M����Ă����f�[�^

	static uint			m_thIDMatch;	// �X���b�hID1
	static HANDLE		m_hThMatch;	// �X���b�h�n���h��1
	static uint			m_thID;	// �X���b�hID1
	static HANDLE		m_hTh;	// �X���b�h�n���h��1

	static int m_ifBindSuccess;
};

#endif