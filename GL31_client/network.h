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
#include "player.h"

//=============================================================================
//	�}�N����`
//=============================================================================
const int PLAYER_NUM		= 4;
const int BULLET_NUM_MAX	= 1000;

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
	char*	pAddr;	// �ʐM��IP�A�h���X
} CONNECT_PROTOCOL;		// �ʐM���

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
	static uint __stdcall ReceveThread(void *);

	static void	Init(void);
	static void	Clear(void);
	static void	Uninit(void);
	static void	Update(void);
	static void	Draw(void);

	static void SendData(char* format, ...);
	static void ReceiveData(void);

	static BULLETDATA m_BulletInstance[PLAYER_NUM][BULLET_NUM_MAX];
	static vector<int> m_Ranking;

private:
	static void RemoveDataTag(char* data);
	static void	ReadConnetProtocol(CONNECT_PROTOCOL *cp);
	static void	SetPlayerData(void);
	static void	CreateBullet(void);
	static void	DeleteBullet(void);
	static void	PlayerDamage(void);
	static void	GameEnd(void);
	static CONNECT_PROTOCOL	m_ConnectProtocol;	// ���M����

	static bool	m_ifInitialize;	// Init()���I���������ǂ���
	static bool	m_ifMatched;		// �}�b�`���O���I���������ǂ���

	static SOCKET		m_SockSend;				// UDP�\�P�b�g
	static SOCKET		m_SockRecv;				// UDP�\�P�b�g
	static sockaddr_in	m_AddrServer;			// �T�[�o�̃A�h���X
	static char			m_ReceiveData[65535];	// ��M�f�[�^
	static char			m_LastMessage[65535];	// �Ō�ɑ��M����Ă����f�[�^

	static uint			m_thID;	// �X���b�hID1
	static HANDLE		m_hTh;	// �X���b�h�n���h��1
};

#endif