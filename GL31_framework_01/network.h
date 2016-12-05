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

//=============================================================================
//	�N���X��`
//=============================================================================
class CNetwork
{
public:
	static void	Init(void);
	static void	Uninit(void);
	static void	Update(void);
	static void	Draw(void);

	static void SendData(char *str);
	static void ReceiveData(void);

	static bool			m_ifInitialize;	// Init()���I���������ǂ���

private:
	static WSADATA		m_Wsadata;
	static int			m_Sts;
	static int			m_Errcode;
	static SOCKET		m_Sock;			// �\�P�b�g
	static sockaddr_in	m_Addr;			// �A�h���X
	static int			m_AddrLen;		// ���M���A�h���X�T�C�Y
	static sockaddr_in	m_AddrClient;	// ���M�����

	static uint			thID1;	// �X���b�hID1
	static HANDLE		hTh1;	// �X���b�h�n���h��1

	static void			SetPlayerData(char *str);

};

#endif