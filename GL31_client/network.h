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

//=============================================================================
//	�}�N����`
//=============================================================================

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

//=============================================================================
//	�N���X��`
//=============================================================================
class CNetwork
{
public:
	static uint __stdcall ReceveThread(void *);

	static void	Init(void);
	static void	Uninit(void);
	static void	Update(void);
	static void	Draw(void);

	static void SendData(char* format, ...);
	static void ReceiveData(void);


private:
	static void RemoveDataTag(char* data);
	static void	ReadConnetProtocol(CONNECT_PROTOCOL *cp);
	static void	SetPlayerData(char *str);
	static CONNECT_PROTOCOL	m_ConnectProtocol;	// ���M����

	static bool	m_ifInitialize;	// Init()���I���������ǂ���
	static bool	m_ifMatched;		// �}�b�`���O���I���������ǂ���

	static SOCKET		m_SockSend;				// UDP�\�P�b�g
	static SOCKET		m_SockRecv;				// UDP�\�P�b�g
	static sockaddr_in	m_AddrServer;		// �T�[�o�̃A�h���X
	static char			m_LastMessage[1024];	// �Ō�ɑ��M����Ă����f�[�^

	static uint			m_thID;	// �X���b�hID1
	static HANDLE		m_hTh;	// �X���b�h�n���h��1
};

#endif