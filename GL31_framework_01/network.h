#ifndef _NETWORK_H_
#define _NETWORK_H_
//=============================================================================
//
//	タイトル	ヘッダファイル(network.cpp)
//	ファイル名	network.h
//	作成者		AT13A284_07 池田達哉
//	作成日		2016/11/14
//
//=============================================================================
#include "number.h"

//=============================================================================
//	マクロ定義
//=============================================================================

//=============================================================================
//	構造体
//=============================================================================

//=============================================================================
//	クラス定義
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

	static bool			m_ifInitialize;	// Init()が終了したかどうか

private:
	static WSADATA		m_Wsadata;
	static int			m_Sts;
	static int			m_Errcode;
	static SOCKET		m_Sock;			// ソケット
	static sockaddr_in	m_Addr;			// アドレス
	static int			m_AddrLen;		// 送信元アドレスサイズ
	static sockaddr_in	m_AddrClient;	// 送信元情報

	static uint			thID1;	// スレッドID1
	static HANDLE		hTh1;	// スレッドハンドル1

	static void			SetPlayerData(char *str);

};

#endif